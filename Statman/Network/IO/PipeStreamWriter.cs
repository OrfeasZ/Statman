using System;
using System.IO;
using System.IO.Pipes;
using System.Text;

namespace Statman.Network.IO
{
    public class PipeStreamWriter
    {
        public PipeStream BaseStream { get; private set; }

        public PipeStreamWriter(PipeStream p_Stream)
        {
            BaseStream = p_Stream;
        }

        private byte[] Serialize(PipeMessage p_Message)
        {
            using (var s_Writer = new BinaryWriter(new MemoryStream()))
            {
                s_Writer.Write(Encoding.UTF8.GetBytes(p_Message.Module));
                s_Writer.Write(Encoding.UTF8.GetBytes(p_Message.Type));
                s_Writer.Write(Encoding.UTF8.GetBytes(p_Message.Content));

                return ((MemoryStream) s_Writer.BaseStream).ToArray();
            }
        }

        private void Flush()
        {
            BaseStream.Flush();
        }

        public void WriteMessage(PipeMessage p_Message)
        {
            var s_MessageData = Serialize(p_Message);

            var s_LengthData = BitConverter.GetBytes((int) s_MessageData.Length);
            BaseStream.Write(s_LengthData, 0, 4);

            BaseStream.Write(s_MessageData, 0, s_MessageData.Length);

            Flush();
        }

        public void WaitForPipeDrain()
        {
            BaseStream.WaitForPipeDrain();
        }
    }
}