using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Statman.Engines.HM5
{
    [StructLayout(LayoutKind.Explicit, Pack = 8)]
    struct ZGameTimeManager
    {
        [MarshalAs(UnmanagedType.I8), FieldOffset(0x0010)]
        public long m_tSystemTime;

        [MarshalAs(UnmanagedType.I8), FieldOffset(0x0018)]
        public long m_tLevelTime;

        [MarshalAs(UnmanagedType.I8), FieldOffset(0x0020)]
        public long m_tLastLevelTime;

        [MarshalAs(UnmanagedType.I8), FieldOffset(0x0028)]
        public long m_tLevelTimeDelta;

        [MarshalAs(UnmanagedType.I8), FieldOffset(0x0030)]
        public long m_tRealTime;

        [MarshalAs(UnmanagedType.I8), FieldOffset(0x0038)]
        public long m_tLastRealTime;

        [MarshalAs(UnmanagedType.I8), FieldOffset(0x0040)]
        public long m_tRealTimeDelta;

        [MarshalAs(UnmanagedType.R4), FieldOffset(0x0048)]
        public float m_fTimeMultiplier0;

        [MarshalAs(UnmanagedType.R4), FieldOffset(0x004C)]
        public float m_fTimeMultiplier1;

        [MarshalAs(UnmanagedType.Bool), FieldOffset(0x0070)]
        public bool m_bPaused;

        [MarshalAs(UnmanagedType.U4), FieldOffset(0x0074)]
        public uint m_nRenderedFrames;
    }

    class ZString
    {
        public static string FromAddr(long p_Addr, Util.ProcessMemoryReader p_Reader)
        {
            var s_LenData = p_Reader.Read(new IntPtr(p_Addr), 4);
            var s_PtrData = p_Reader.Read(new IntPtr(p_Addr) + 8, 8);

            if (s_LenData == null || s_PtrData == null)
                return "";

            var s_Len = BitConverter.ToInt32(s_LenData, 0);
            var s_Ptr = BitConverter.ToInt64(s_PtrData, 0);

            var s_StrData = p_Reader.Read(new IntPtr(s_Ptr), s_Len);

            if (s_StrData == null)
                return "";

            return Encoding.UTF8.GetString(s_StrData);
        }
    }
}
