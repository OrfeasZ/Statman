using System;
using System.IO.Pipes;
using System.Text;

namespace Statman.Network.IO
{
    public class PipeStreamReader
    {
        public PipeStream BaseStream { get; private set; }

        public bool IsConnected { get; private set; }

        public PipeStreamReader(PipeStream p_Stream)
        {
            BaseStream = p_Stream;
            IsConnected = p_Stream.IsConnected;
        }
       
        private int ReadLength()
        {
            var s_LengthBytes = new byte[4];

            if (BaseStream.Read(s_LengthBytes, 0, 4) == 4) 
                return BitConverter.ToInt32(s_LengthBytes, 0);
            
            IsConnected = false;
            return 0;
        }

        private PipeMessage ReadMessage(int p_Length)
        {
            var s_Data = new byte[p_Length];

            if (BaseStream.Read(s_Data, 0, p_Length) != p_Length)
                return default(PipeMessage);

            var s_ModuleData = new byte[2];
            var s_TypeData = new byte[2];
            var s_ContentData = new byte[p_Length - 4];

            Buffer.BlockCopy(s_Data, 0, s_ModuleData, 0, 2);
            Buffer.BlockCopy(s_Data, 2, s_TypeData, 0, 2);
            Buffer.BlockCopy(s_Data, 4, s_ContentData, 0, p_Length - 4);

            var s_Message = new PipeMessage()
            {
                Module = Encoding.UTF8.GetString(s_ModuleData),
                Type = Encoding.UTF8.GetString(s_TypeData),
                Content = Encoding.UTF8.GetString(s_ContentData)
            };

            return s_Message;
        }

        public PipeMessage ReadMessage()
        {
            var s_Length = ReadLength();
            return s_Length == 0 ? default(PipeMessage) : ReadMessage(s_Length);
        }
    }
}