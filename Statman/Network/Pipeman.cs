using System;
using System.IO;
using System.IO.Pipes;
using System.Security.AccessControl;
using System.Security.Principal;
using System.Text;
using System.Threading;

namespace Statman.Network
{
    class Pipeman : IDisposable
    {
        readonly string m_PipeName;
        private volatile bool m_Running;

        public Pipeman(string p_PipeName)
        {
            m_PipeName = p_PipeName;
            Listen();
        }

        public void Dispose()
        {
            m_Running = false;
        }

        public void Listen()
        {
            m_Running = true;

            var s_Thread = new Thread(ServerThread);
            s_Thread.Start();
        }

        private void ServerThread()
        {
            while (m_Running)
            {
                var s_Identifier = new SecurityIdentifier(WellKnownSidType.WorldSid, null);
                var s_Security = new PipeSecurity();
                s_Security.SetAccessRule(new PipeAccessRule(s_Identifier, PipeAccessRights.ReadWrite, AccessControlType.Allow));

                var s_PipeServer = new NamedPipeServerStream(m_PipeName, PipeDirection.In, 5, PipeTransmissionMode.Message, PipeOptions.None, 256, 0, s_Security);

                s_PipeServer.WaitForConnection();

                try
                {
                    var s_Reader = new BinaryReader(s_PipeServer);

                    var s_DataLength = s_Reader.ReadUInt32();

                    var s_Data = s_Reader.ReadBytes((int) s_DataLength);
                    MainApp.EngineManager.OnMessage(Encoding.UTF8.GetString(s_Data));
                }
                catch (IOException)
                {
                }

                s_PipeServer.Close();
                Thread.Sleep(5);
            }
        }
    }
}
