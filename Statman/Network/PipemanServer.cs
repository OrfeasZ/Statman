using System;
using System.Collections.Generic;
using System.IO.Pipes;
using System.Security.Principal;
using Statman.Network.IO;
using Statman.Network.Threading;

namespace Statman.Network
{
    public class PipemanServer
    {
        public event ConnectionEventHandler ClientConnected;
        public event ConnectionEventHandler ClientDisconnected;
        public event ConnectionMessageEventHandler ClientMessage;

        private readonly string m_PipeName;
        private readonly List<PipeConnection> m_Connections = new List<PipeConnection>();

        private int m_NextPipeID;

        private volatile bool m_ShouldKeepRunning;

        public PipemanServer(string p_PipeName)
        {
            m_PipeName = p_PipeName;
        }

        public void Start()
        {
            m_ShouldKeepRunning = true;
            var s_Worker = new Worker();
            s_Worker.DoWork(ListenSync);
        }

        public void PushMessage(PipeMessage p_Message)
        {
            lock (m_Connections)
                foreach (var s_Client in m_Connections)
                    s_Client.PushMessage(p_Message);
        }

        public void Stop()
        {
            m_ShouldKeepRunning = false;

            lock (m_Connections)
                foreach (var s_Client in m_Connections.ToArray())
                    s_Client.Close();

            var s_DummyClient = new PipemanClient(m_PipeName);
            s_DummyClient.Start();
            s_DummyClient.WaitForConnection(TimeSpan.FromSeconds(2));
            s_DummyClient.Stop();
            s_DummyClient.WaitForDisconnection(TimeSpan.FromSeconds(2));
        }

        private void ListenSync()
        {
            while (m_ShouldKeepRunning)
            {
                WaitForConnection(m_PipeName);
            }
        }

        private void WaitForConnection(string p_PipeName)
        {
            NamedPipeServerStream s_HandshakePipe = null;
            NamedPipeServerStream s_DataPipe = null;
            PipeConnection s_Connection = null;

            var s_ConnectionPipeName = GetNextConnectionPipeName(p_PipeName);

            try
            {
                s_HandshakePipe = PipeServerFactory.CreateAndConnectPipe(p_PipeName);
                var s_HandshakeWrapper = new PipeStreamWrapper(s_HandshakePipe);
                s_HandshakeWrapper.WriteMessage(new PipeMessage() { Module = "SM", Type = "HS", Content = s_ConnectionPipeName });
                s_HandshakeWrapper.WaitForPipeDrain();
                s_HandshakeWrapper.Close();

                s_DataPipe = PipeServerFactory.CreatePipe(s_ConnectionPipeName);
                s_DataPipe.WaitForConnection();

                s_Connection = ConnectionFactory.CreateConnection(s_DataPipe);
                s_Connection.ReceiveMessage += ClientOnReceiveMessage;
                s_Connection.Disconnected += ClientOnDisconnected;
                s_Connection.Open();

                lock (m_Connections)
                    m_Connections.Add(s_Connection);

                ClientOnConnected(s_Connection);
            }
            catch (Exception)
            {
                Cleanup(s_HandshakePipe);
                Cleanup(s_DataPipe);
                ClientOnDisconnected(s_Connection);
            }
        }

        private void ClientOnConnected(PipeConnection p_Connection)
        {
            if (ClientConnected != null)
                ClientConnected(p_Connection);
        }

        private void ClientOnReceiveMessage(PipeConnection p_Connection, PipeMessage p_Message)
        {
            if (ClientMessage != null)
                ClientMessage(p_Connection, p_Message);
        }

        private void ClientOnDisconnected(PipeConnection p_Connection)
        {
            if (p_Connection == null)
                return;

            lock (m_Connections)
                m_Connections.Remove(p_Connection);

            if (ClientDisconnected != null)
                ClientDisconnected(p_Connection);
        }

        private string GetNextConnectionPipeName(string p_PipeName)
        {
            return string.Format("{0}_{1}", p_PipeName, ++m_NextPipeID);
        }

        private static void Cleanup(NamedPipeServerStream p_Pipe)
        {
            if (p_Pipe == null) 
                return;

            using (var s_Pipe = p_Pipe)
                s_Pipe.Close();
        }
    }

    static class PipeServerFactory
    {
        public static NamedPipeServerStream CreateAndConnectPipe(string p_PipeName)
        {
            var s_Pipe = CreatePipe(p_PipeName);
            s_Pipe.WaitForConnection();
            return s_Pipe;
        }

        public static NamedPipeServerStream CreatePipe(string p_PipeName)
        {
            var s_Security = new PipeSecurity();
            var s_Identifier = new SecurityIdentifier(WellKnownSidType.WorldSid, null);
            var s_AccessRule = new PipeAccessRule(s_Identifier, PipeAccessRights.ReadWrite, System.Security.AccessControl.AccessControlType.Allow);
            s_Security.AddAccessRule(s_AccessRule);

            return new NamedPipeServerStream(p_PipeName, PipeDirection.InOut, 1, PipeTransmissionMode.Byte, PipeOptions.Asynchronous | PipeOptions.WriteThrough, 1024, 1024, s_Security);
        }
    }
}