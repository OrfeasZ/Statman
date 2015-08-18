using System.IO.Pipes;

namespace Statman.Network.IO
{
    public class PipeStreamWrapper
    {
        public PipeStream BaseStream { get; private set; }

        public bool IsConnected
        {
            get { return BaseStream.IsConnected && m_Reader.IsConnected; }
        }

        public bool CanRead
        {
            get { return BaseStream.CanRead; }
        }

        public bool CanWrite
        {
            get { return BaseStream.CanWrite; }
        }

        private readonly PipeStreamReader m_Reader;
        private readonly PipeStreamWriter m_Writer;

        public PipeStreamWrapper(PipeStream p_Stream)
        {
            BaseStream = p_Stream;
            m_Reader = new PipeStreamReader(BaseStream);
            m_Writer = new PipeStreamWriter(BaseStream);
        }

        public PipeMessage ReadMessage()
        {
            return m_Reader.ReadMessage();
        }

        public void WriteMessage(PipeMessage p_Message)
        {
            m_Writer.WriteMessage(p_Message);
        }

        public void WaitForPipeDrain()
        {
            m_Writer.WaitForPipeDrain();
        }

        public void Close()
        {
            BaseStream.Close();
        }
    }
}