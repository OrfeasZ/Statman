using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using Statman.Engines.HM5;
using Statman.Engines.HM5.Controls;
using Statman.Network;
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

        public StatTracker StatTracker { get; private set; }

        private Process m_GameProcess;
        private Injector m_Injector;

        private readonly List<Control> m_MenuItems;

        public HM5Engine()
        {
            m_MenuItems = new List<Control>();
            Active = false;
        }

        public void Dispose()
        {
            SendMessage("XX");

            if (Reader != null)
            {
                Reader.CloseHandle();
                Reader = null;
            }

            if (m_Injector != null)
            {
                m_Injector.Dispose();
                m_Injector = null;
            }
        }

        private void InitMenuItems()
        {
            MainApp.MainWindow.Dispatcher.Invoke(() =>
            {
                var s_GetStats = new MenuItem()
                {
                    Header = "Get Stats",
                };

                s_GetStats.Click += GetStatsOnClick;

                m_MenuItems.Clear();
                m_MenuItems.Add(s_GetStats);
            });
        }

        private void GetStatsOnClick(object p_Sender, RoutedEventArgs p_RoutedEventArgs)
        {
            SendMessage("GS");
        }

        public void SendMessage(string p_Type, string p_Contents = "")
        {
            MainApp.Pipeman.PushMessage(new PipeMessage()
            {
                Module = Name,
                Type = p_Type,
                Content = p_Contents
            });
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

                if (m_Injector != null)
                {
                    m_Injector.Dispose();
                    m_Injector = null;
                }

                var s_Processes = Process.GetProcessesByName("HITMAN2");

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
                        Active = true;

                        // Create our injector and inject our stat module.
                        m_Injector = new Injector(m_GameProcess, true);
                        m_Injector.InjectLibrary("HM5.dll");

                        // Setup our main control.
                        MainApp.MainWindow.Dispatcher.Invoke(() =>
                        {
                            Control = new MainControl();
                        });

                        // Setup our engine-specific classes.
                        StatTracker = new StatTracker(this);
                        
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
            StatTracker.Update();
        }

        public void OnMessage(string p_Type, string p_Data)
        {

        }
    }
}