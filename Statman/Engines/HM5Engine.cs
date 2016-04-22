#if AMD64
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using Statman.Engines.HM5.Controls;
using Statman.Util;
using Statman.Util.Injection;

namespace Statman.Engines
{
    class HM5Engine : IEngine
    {
        public string Name { get { return "H5"; } }
        public bool Active { get; private set; }

        public ProcessMemoryReader Reader { get; private set; }

        public MainControl Control { get; private set; }
        public string CurrentLevel { get; private set; }
        public bool InGame { get; private set; }

        private Process m_GameProcess;
        //private Injector m_Injector;

        public HM5Engine()
        {
            Active = false;
        }

        public void Dispose()
        {

        }

        public void Update()
        {
            if (m_GameProcess == null || m_GameProcess.HasExited)
            {
                m_GameProcess = null;
                Active = false;

                if (Reader != null)
                {
                    Reader.CloseHandle();
                    Reader = null;
                }

                /*if (m_Injector != null)
                {
                    m_Injector.Dispose();
                    m_Injector = null;
                }*/

                var s_Processes = Process.GetProcessesByName("HITMAN");

                if (s_Processes.Length == 0)
                    return;

                // We always select the first process.
                m_GameProcess = s_Processes[0];

                // Setup our Memory Reader.
                Reader = new ProcessMemoryReader(m_GameProcess);

                try
                {
                    if (Reader.OpenProcess())
                    {
                        m_SkipUpdates = 0;
                        Active = true;

                        // Create our injector and inject our stat module.
                        m_Injector = new Injector(m_GameProcess, false);
                        m_Injector.InjectLibrary("HM3.dll");

                        // Setup our main control.
                        MainApp.MainWindow.Dispatcher.Invoke(() =>
                        {
                            Control = new MainControl();
                        });

                        // Setup our engine-specific classes.
                        StatTracker = new StatTracker(this);
                        TimeTracker = new TimeTracker(this);

                        // Update level labels.
                        CurrentLevel = "No Level";
                        CurrentLevelScene = "No Level";
                        InGame = false;

                        // Set our control in the main window.
                        InitMenuItems();
                        MainApp.MainWindow.SetEngineControl(Control, m_MenuItems);
                    }
                }
                catch (Exception)
                {
                    m_GameProcess = null;
                    Active = false;
                }
            }

            if (!Active)
                return;

            // Update our trackers.
            TimeTracker.Update();
            StatTracker.Update();

            // Set game time.
            if (StatTracker.CurrentStats.m_Time > 0 || !InGame)
                Control.SetCurrentTime(StatTracker.CurrentStats.m_Time);
            else
                Control.SetCurrentTime(TimeTracker.CurrentTime);
        }

        public void OnMessage(string p_Type, string p_Data)
        {
            throw new NotImplementedException();
        }
    }
}
#endif