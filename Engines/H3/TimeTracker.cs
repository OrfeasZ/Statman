using System;

namespace Statman.Engines.H3
{
    class TimeTracker
    {
        public double CurrentTime { get; private set; }

        private readonly H3Engine m_Engine;

        public TimeTracker(H3Engine p_Engine)
        {
            m_Engine = p_Engine;
        }

        public bool Update()
        {
            var s_BasePtrData = m_Engine.Reader.Read(m_Engine.Reader.Process.MainModule.BaseAddress + 0x0041F820, 4);

            if (s_BasePtrData == null)
                return false;

            var s_BasePtr = BitConverter.ToUInt32(s_BasePtrData, 0);

            var s_TimeData = m_Engine.Reader.Read(s_BasePtr + 0x48, 4);

            if (s_TimeData == null)
                return false;

            CurrentTime = BitConverter.ToUInt32(s_TimeData, 0) * 0.0009765625;

            return true;
        }
    }
}
