using System;
using System.Runtime.InteropServices;

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

    class TimeTracker
    {
        public double GameTime { get; private set; }
        public double RealTime { get; private set; }

        private readonly HM5Engine m_Engine;

        private long m_GameTimeManagerAddr = 0;

        public TimeTracker(HM5Engine p_Engine)
        {
            m_Engine = p_Engine;
        }

        public bool Update()
        {
            if (m_GameTimeManagerAddr == 0)
                return true;

            try
            {
                var s_StructData = m_Engine.Reader.Read(m_GameTimeManagerAddr, 0x80);

                if (s_StructData == null)
                    return false;

                var s_Handle = GCHandle.Alloc(s_StructData, GCHandleType.Pinned);
                var s_GameTimeManager = (ZGameTimeManager) Marshal.PtrToStructure(s_Handle.AddrOfPinnedObject(), typeof(ZGameTimeManager));
                s_Handle.Free();

                GameTime = s_GameTimeManager.m_tLevelTime / 1024.0 / 1024.0;
                RealTime = s_GameTimeManager.m_tRealTime / 1024.0 / 1024.0;

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }

        public void SetGameTimeManagerAddr(long p_Addr)
        {
            m_GameTimeManagerAddr = p_Addr;
        }
    }
}
