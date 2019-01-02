using System;
using System.Diagnostics;
using System.Text;

namespace Statman.Engines.HM5
{
    class StatTracker
    {
        private readonly HM5Engine m_Engine;

        public StatTracker(HM5Engine p_Engine)
        {
            m_Engine = p_Engine;
        }

        public bool Update()
        {
            return true;
        }

        private void ProcessFlags(ulong p_Flags)
        {
        }
    }
}
