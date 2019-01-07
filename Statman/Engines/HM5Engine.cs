using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using Statman.Engines.HM5;
using Statman.Engines.HM5.Controls;
using Statman.Engines.HM5.Windows;
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
        public TimeTracker TimeTracker { get; private set; }

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

                var s_LoadScene = new MenuItem()
                {
                    Header = "Load Scene"
                };

                s_LoadScene.Click += LoadSceneOnClick;

                m_MenuItems.Clear();
                m_MenuItems.Add(s_GetStats);
                m_MenuItems.Add(s_LoadScene);
            });
        }

        private void LoadSceneOnClick(object p_Sender, RoutedEventArgs p_RoutedEventArgs)
        {
            var s_Dialog = new SceneLoader();

            if (s_Dialog.ShowDialog() != true)
                return;

            var s_Message = s_Dialog.Scene;

            s_Message += "," + s_Dialog.SceneType;
            s_Message += "," + s_Dialog.CodeNameHint;

            if (s_Dialog.Brick1.Length > 0)
                s_Message += "," + s_Dialog.Brick1;

            if (s_Dialog.Brick2.Length > 0)
                s_Message += "," + s_Dialog.Brick2;

            if (s_Dialog.Brick3.Length > 0)
                s_Message += "," + s_Dialog.Brick3;

            SendMessage("LS", s_Message);
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
                        TimeTracker = new TimeTracker(this);
                        
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
            TimeTracker.Update();

            // Set game time.
            if (StatTracker.InLevel)
            {
                Control.SetGameTime(TimeTracker.GameTime);
                Control.SetRealTime(TimeTracker.RealTime);
            }
        }

        public void OnMessage(string p_Type, string p_Data)
        {
            if (p_Type == "GT")
            {
                // Set the ZGameTimeManager address.
                TimeTracker.SetGameTimeManagerAddr(long.Parse(p_Data));
                return;
            }

            if (p_Type == "SC")
            {
                // Set the ZGameTimeManager address.
                StatTracker.SetEntitySceneManagerAddr(long.Parse(p_Data));
                return;
            }

            if (p_Type == "CS")
            {
                StatTracker.OnContractStart();
                return;
            }

            if (p_Type == "SU")
            {
                var s_Parts = p_Data.Split(':');

                if (s_Parts[0] == "Kill")
                {
                    var s_Data = s_Parts[1].Split(',');
                    StatTracker.OnKill(s_Data[0], s_Data[1] == "true", s_Data[2] == "true");
                }
                else if (s_Parts[0] == "BodyFound")
                {
                    StatTracker.OnBodyFound();
                }
                else if (s_Parts[0] == "NoticedKill")
                {
                    StatTracker.OnNoticedKill();
                }
                else if (s_Parts[0] == "Spotted")
                {
                    var s_Data = s_Parts[1].Split(',');
                    StatTracker.OnSpotted(s_Data);
                }
                else if (s_Parts[0] == "CaughtOnCamera")
                {
                    StatTracker.OnCaughtOnCamera();
                }
                else if (s_Parts[0] == "RecordingsDestroyed")
                {
                    StatTracker.OnRecordingsDestroyed();
                }

                return;
            }
        }
    }
}