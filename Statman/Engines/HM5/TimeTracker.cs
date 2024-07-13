using System;
using System.Runtime.InteropServices;

namespace Statman.Engines.HM5
{
    public class TimeTracker
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
