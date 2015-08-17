using System.Diagnostics;
using Statman.Engines.H3;
using Statman.Util;

namespace Statman.Engines
{
    class H3Engine : IEngine
    {
        public bool Active { get; private set; }
        public ProcessMemoryReader Reader { get; private set; }

        private Process m_GameProcess;

        private StatTracker m_StatTracker;
        private TimeTracker m_TimeTracker;
        private SceneTracker m_SceneTracker;

        private uint m_SkipUpdates;

        public H3Engine()
        {
            Active = false;
        }

        public void Update()
        {
            if (m_GameProcess == null || m_GameProcess.HasExited)
            {
                if (m_SkipUpdates > 0)
                {
                    --m_SkipUpdates;
                    return;
                }

                m_SkipUpdates = 16;

                m_GameProcess = null;
                Active = false;

                if (Reader != null)
                {
                    Reader.CloseHandle();
                    Reader = null;
                }

                var s_Processes = Process.GetProcessesByName("HitmanBloodMoney");

                if (s_Processes.Length == 0)
                    return;

                // We always select the first process.
                m_GameProcess = s_Processes[0];

                // Setup our Memory Reader.
                Reader = new ProcessMemoryReader(m_GameProcess);

                if (Reader.OpenProcess())
                {
                    m_SkipUpdates = 0;
                    Active = true;

                    // Setup our engine-specific classes.
                    m_StatTracker = new StatTracker(this);
                    m_TimeTracker = new TimeTracker(this);
                    m_SceneTracker = new SceneTracker(this);
                }
            }

            if (!Active)
                return;

            m_SceneTracker.Update();
            m_TimeTracker.Update();
            m_StatTracker.Update();
        }
    }
}
