using System;
using System.Diagnostics;
using System.Threading;
using System.Windows;
using Statman.Util;
using Statman.Windows;

namespace Statman
{
    class MainLoop : IDisposable
    {
        private readonly int m_Ticks;
        private TickTimer m_Timer;
        private Thread m_Thread;
        private volatile bool m_Running;

        public event EventHandler Update;

        public MainLoop(int p_TickRate)
        {
            // Calculate required ticks for each update.
            m_Ticks = 1000 / p_TickRate;

            m_Timer = new TickTimer();
            m_Running = false;
        }

        public void Dispose()
        {
            m_Running = false;

            if (m_Thread != null)
                m_Thread.Join();
        }

        public void Start()
        {
            if (m_Running)
                return;

            m_Running = true;

            m_Thread = new Thread(DoLoopWork);
            m_Thread.SetApartmentState(ApartmentState.STA);
            m_Thread.Start();
        }

        public void Stop()
        {
            if (!m_Running || m_Thread == null)
            {
                m_Thread = null;
                return;
            }

            m_Running = false;

            m_Thread.Join();
            m_Thread = null;
        }

        protected void DoLoopWork()
        {
            m_Timer = new TickTimer();

            while (m_Running)
            {
                if (MainApp.CheckForUpdates)
                {
                    MainApp.CheckForUpdates = false;

                    // Check for updates.
                    MainApp.MainWindow.SetStatusLabel("Checking for updates...");

                    string s_CurrentVersion, s_LatestVersion, s_ReleaseURL;
                    bool s_PreRelease;

                    if (UpdateChecker.HasNewerVersion(out s_CurrentVersion, out s_LatestVersion, out s_ReleaseURL,
                        out s_PreRelease))
                    {
                        MainApp.MainWindow.Dispatcher.Invoke(() =>
                        {
                            new UpdateWindow(s_CurrentVersion, s_LatestVersion, s_ReleaseURL, s_PreRelease).Show();
                        });
                    }

                    MainApp.MainWindow.SetStatusLabel("Waiting for game...");
                }

                m_Timer.Reset();

                if (Update != null)
                    Update.Invoke(this, null);

                var s_Ticks = m_Timer.Ticks;

                if (s_Ticks >= m_Ticks)
                    continue;

                Thread.Sleep((int) (m_Ticks - s_Ticks));
            }
        }
    }
}
