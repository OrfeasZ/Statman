using System;

namespace Statman.Engines.HM3
{
    class TimeTracker
    {
        public double CurrentTime { get; private set; }

        private readonly HM3Engine m_Engine;

        public IntPtr TimeAddress = IntPtr.Zero;

        public TimeTracker(HM3Engine p_Engine)
        {
            m_Engine = p_Engine;
        }

        public bool Update()
        {
            try
            {
                var s_BasePtrData = TimeAddress != IntPtr.Zero ? m_Engine.Reader.Read(TimeAddress, 4) : null;

                if (s_BasePtrData == null)
                    return false;

                var s_BasePtr = BitConverter.ToUInt32(s_BasePtrData, 0);

                var s_TimeData = m_Engine.Reader.Read(s_BasePtr + 0x48, 4);

                if (s_TimeData == null)
                    return false;

                CurrentTime = BitConverter.ToUInt32(s_TimeData, 0) * 0.0009765625;

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
    }
}
