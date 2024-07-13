using System.Collections.Generic;
using System.IO.Pipes;
using System.Threading;
using Statman.Network.IO;
using Statman.Network.Threading;

namespace Statman.Network
{
    public class PipeConnection
    {
        public int ID { get; private set; }

        public string Name { get; private set; }

        public bool IsConnected { get { return m_StreamWrapper.IsConnected; } }

        public event ConnectionEventHandler Disconnected;

        public event ConnectionMessageEventHandler ReceiveMessage;
        
        private readonly PipeStreamWrapper m_StreamWrapper;

        private readonly AutoResetEvent m_WriteSignal = new AutoResetEvent(false);
        private readonly Queue<PipeMessage> m_WriteQueue = new Queue<PipeMessage>();

        private bool m_NotifiedSucceeded;

        internal PipeConnection(int p_ID, string p_Name, PipeStream p_ServerStream)
        {
            ID = p_ID;
            Name = p_Name;
            m_StreamWrapper = new PipeStreamWrapper(p_ServerStream);
        }

        public void Open()
        {
            var s_ReadWorker = new Worker();
            s_ReadWorker.Succeeded += OnSucceeded;
            s_ReadWorker.DoWork(ReadPipe);

            var s_WriteWorker = new Worker();
            s_WriteWorker.Succeeded += OnSucceeded;
            s_WriteWorker.DoWork(WritePipe);
        }

        public void PushMessage(PipeMessage p_Message)
        {
            m_WriteQueue.Enqueue(p_Message);
            m_WriteSignal.Set();
        }

        public void Close()
        {
            CloseImpl();
        }

        private void CloseImpl()
        {
            m_StreamWrapper.Close();
            m_WriteSignal.Set();
        }

        private void OnSucceeded()
        {
            if (m_NotifiedSucceeded)
                return;

            m_NotifiedSucceeded = true;

            Disconnected?.Invoke(this);
        }

        private void ReadPipe()
        {
            while (IsConnected && m_StreamWrapper.CanRead)
            {
                var s_Message = m_StreamWrapper.ReadMessage();

                if (s_Message == null)
                {
                    CloseImpl();
                    return;
                }

                ReceiveMessage?.Invoke(this, s_Message);
            }
        }

        private void WritePipe()
        {
            while (IsConnected && m_StreamWrapper.CanWrite)
            {
                m_WriteSignal.WaitOne();

                while (m_WriteQueue.Count > 0)
                {
                    m_StreamWrapper.WriteMessage(m_WriteQueue.Dequeue());
                    m_StreamWrapper.WaitForPipeDrain();
                }
            }
        }
    }

    static class ConnectionFactory
    {
        private static int m_LastID;

        public static PipeConnection CreateConnection(PipeStream p_PipeStream)
        {
            return new PipeConnection(++m_LastID, "Client " + m_LastID, p_PipeStream);
        }
    }

    public delegate void ConnectionEventHandler(PipeConnection p_Connection);
    public delegate void ConnectionMessageEventHandler(PipeConnection p_Connection, PipeMessage p_Message);
}