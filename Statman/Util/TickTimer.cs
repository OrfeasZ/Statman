using System.Runtime.InteropServices;

namespace Statman.Util
{
    class TickTimer
    {
        [DllImport("kernel32.dll")]
        private static extern long GetTickCount();

        public long Ticks
        {
            get { return GetTickCount() - m_FirstTick; }
        }

        private long m_FirstTick;

        public TickTimer()
        {
            Reset();
        }

        public void Reset()
        {
            m_FirstTick = GetTickCount();
        }
    }
}
