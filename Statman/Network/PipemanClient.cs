using System;
using System.IO.Pipes;
using System.Threading;
using Statman.Network.IO;
using Statman.Network.Threading;

namespace Statman.Network
{
    public class PipemanClient
    {
        public bool AutoReconnect { get; set; }

        public event ConnectionMessageEventHandler ServerMessage;
        public event ConnectionEventHandler Disconnected;

        private readonly string m_PipeName;
        private PipeConnection m_Connection;

        private readonly AutoResetEvent m_Connected = new AutoResetEvent(false);
        private readonly AutoResetEvent m_Disconnected = new AutoResetEvent(false);

        private volatile bool m_ClosedExplicitly;

        public PipemanClient(string p_PipeName)
        {
            m_PipeName = p_PipeName;
            AutoReconnect = true;
        }

        public void Start()
        {
            m_ClosedExplicitly = false;
            var s_Worker = new Worker();
            s_Worker.DoWork(ListenSync);
        }

        public void PushMessage(PipeMessage p_Message)
        {
            if (m_Connection != null)
                m_Connection.PushMessage(p_Message);
        }

        public void Stop()
        {
            m_ClosedExplicitly = true;
            if (m_Connection != null)
                m_Connection.Close();
        }

        public void WaitForConnection()
        {
            m_Connected.WaitOne();
        }

        public void WaitForConnection(int p_MillisecondsTimeout)
        {
            m_Connected.WaitOne(p_MillisecondsTimeout);
        }

        public void WaitForConnection(TimeSpan p_Timeout)
        {
            m_Connected.WaitOne(p_Timeout);
        }

        public void WaitForDisconnection()
        {
            m_Disconnected.WaitOne();
        }

        public void WaitForDisconnection(int p_MillisecondsTimeout)
        {
            m_Disconnected.WaitOne(p_MillisecondsTimeout);
        }

        public void WaitForDisconnection(TimeSpan p_Timeout)
        {
            m_Disconnected.WaitOne(p_Timeout);
        }

        private void ListenSync()
        {
            var s_Handshake = PipeClientFactory.Connect(m_PipeName);
            var s_DataPipeName = s_Handshake.ReadMessage();
            s_Handshake.Close();

            var s_DataPipe = PipeClientFactory.CreateAndConnectPipe(s_DataPipeName.Content);

            m_Connection = ConnectionFactory.CreateConnection(s_DataPipe);
            m_Connection.Disconnected += OnDisconnected;
            m_Connection.ReceiveMessage += OnReceiveMessage;
            m_Connection.Open();

            m_Connected.Set();
        }

        private void OnDisconnected(PipeConnection p_Connection)
        {
            if (Disconnected != null)
                Disconnected(p_Connection);

            m_Disconnected.Set();

            if (AutoReconnect && !m_ClosedExplicitly)
                Start();
        }

        private void OnReceiveMessage(PipeConnection p_Connection, PipeMessage p_Message)
        {
            if (ServerMessage != null)
                ServerMessage(p_Connection, p_Message);
        }
    }

    static class PipeClientFactory
    {
        public static PipeStreamWrapper Connect(string p_PipeName)
        {
            return new PipeStreamWrapper(CreateAndConnectPipe(p_PipeName));
        }

        public static NamedPipeClientStream CreateAndConnectPipe(string p_PipeName)
        {
            var s_Pipe = CreatePipe(p_PipeName);
            s_Pipe.Connect();
            return s_Pipe;
        }

        private static NamedPipeClientStream CreatePipe(string p_PipeName)
        {
            return new NamedPipeClientStream(".", p_PipeName, PipeDirection.InOut, PipeOptions.Asynchronous | PipeOptions.WriteThrough);
        }
    }
}