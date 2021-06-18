using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using Statman.Engines.HM3;
using Statman.Engines.HM3.Controls;
using Statman.Network;
using Statman.Util;
using Statman.Util.Injection;

namespace Statman.Engines
{
    class HM3Engine : IEngine
    {
        private static readonly Dictionary<string, Tuple<string, string, bool>> m_SceneNames = new Dictionary
            <string, Tuple<string, string, bool>>()
        {
            { "hitmanbloodmoney", new Tuple<string, string, bool>("Main Menu", "Menu", false) },
            { "scenes\\hitmanbloodmoney.gms", new Tuple<string, string, bool>("Main Menu", "Menu", false) },

            { "saveandcontinue", new Tuple<string, string, bool>("Save & Continue", "Menu", false) },

            { "hideout\\hideout_main", new Tuple<string, string, bool>("Hideout", "In-Game", true) },
            { "scenes\\hideout\\hideout_main.gms", new Tuple<string, string, bool>("Hideout", "In-Game", true) },

            { "m00\\m00_intro", new Tuple<string, string, bool>("Death of a Showman", "Intro", false) },
            { "m00\\m00_main", new Tuple<string, string, bool>("Death of a Showman", "In-Game", true) },
            { "scenes\\m00\\m00_main.gms", new Tuple<string, string, bool>("Death of a Showman", "In-Game", true) },
            { "m00\\m00_news", new Tuple<string, string, bool>("Death of a Showman", "News", false) },
            { "m00\\m00_albino", new Tuple<string, string, bool>("Death of a Showman", "Story Intro", false) },

            { "m01\\m01_premission", new Tuple<string, string, bool>("A Vintage Year", "Pre-Mission", false) },
            { "m01\\m01_main", new Tuple<string, string, bool>("A Vintage Year", "In-Game", true) },
            { "scenes\\m01\\m01_main.gms", new Tuple<string, string, bool>("A Vintage Year", "In-Game", true) },
            { "m01\\m01_postmission", new Tuple<string, string, bool>("A Vintage Year", "Post-Mission", false) },
            { "m01\\m01_news", new Tuple<string, string, bool>("A Vintage Year", "News", false) },

            { "m03\\m03_premission", new Tuple<string, string, bool>("Curtains Down", "Pre-Mission", false) },
            { "m03\\m03_main", new Tuple<string, string, bool>("Curtains Down", "In-Game", true) },
            { "scenes\\m03\\m03_main.gms", new Tuple<string, string, bool>("Curtains Down", "In-Game", true) },
            { "m03\\m03_postmission", new Tuple<string, string, bool>("Curtains Down", "Post-Mission", false) },
            { "m03\\m03_news", new Tuple<string, string, bool>("Curtains Down", "News", false) },

            { "m04\\m04_premission", new Tuple<string, string, bool>("Flatline", "Pre-Mission", false) },
            { "m04\\m04_main", new Tuple<string, string, bool>("Flatline", "In-Game", true) },
            { "scenes\\m04\\m04_main.gms", new Tuple<string, string, bool>("Flatline", "In-Game", true) },
            { "m04\\m04_postmission", new Tuple<string, string, bool>("Flatline", "Post-Mission", false) },
            { "m04\\m04_news", new Tuple<string, string, bool>("Flatline", "News", false) },

            { "m05\\m05_premission", new Tuple<string, string, bool>("A New Life", "Pre-Mission", false) },
            { "m05\\m05_main", new Tuple<string, string, bool>("A New Life", "In-Game", true) },
            { "scenes\\m05\\m05_main.gms", new Tuple<string, string, bool>("A New Life", "In-Game", true) },
            { "m05\\m05_postmission", new Tuple<string, string, bool>("A New Life", "Post-Mission", false) },
            { "m05\\m05_news", new Tuple<string, string, bool>("A New Life", "News", false) },

            { "m06\\m06_premission", new Tuple<string, string, bool>("Murder of the Crows", "Pre-Mission", false) },
            { "m06\\m06_main", new Tuple<string, string, bool>("Murder of the Crows", "In-Game", true) },
            { "scenes\\m06\\m06_main.gms", new Tuple<string, string, bool>("Murder of the Crows", "In-Game", true) },
            { "m06\\m06_postmission", new Tuple<string, string, bool>("Murder of the Crows", "Post-Mission", false) },
            { "m06\\m06_news", new Tuple<string, string, bool>("Murder of the Crows", "News", false) },
            
            { "m02\\m02_premission", new Tuple<string, string, bool>("You Better Watch Out", "Pre-Mission", false) },
            { "m02\\m02_main", new Tuple<string, string, bool>("You Better Watch Out", "In-Game", true) },
            { "scenes\\m02\\m02_main.gms", new Tuple<string, string, bool>("You Better Watch Out", "In-Game", true) },
            { "m02\\m02_postmission", new Tuple<string, string, bool>("You Better Watch Out", "Post-Mission", false) },
            { "m02\\m02_news", new Tuple<string, string, bool>("You Better Watch Out", "News", false) },

            { "m08\\m08_premission", new Tuple<string, string, bool>("Death on the Mississippi", "Pre-Mission", false) },
            { "m08\\m08_main", new Tuple<string, string, bool>("Death on the Mississippi", "In-Game", true) },
            { "scenes\\m08\\m08_main.gms", new Tuple<string, string, bool>("Death on the Mississippi", "In-Game", true) },
            { "m08\\m08_postmission", new Tuple<string, string, bool>("Death on the Mississippi", "Post-Mission", false) },
            { "m08\\m08_news", new Tuple<string, string, bool>("Death on the Mississippi", "News", false) },

            { "m09\\m09_premission", new Tuple<string, string, bool>("Till Death Do Us Part", "Pre-Mission", false) },
            { "m09\\m09_main", new Tuple<string, string, bool>("Till Death Do Us Part", "In-Game", true) },
            { "scenes\\m09\\m09_main.gms", new Tuple<string, string, bool>("Till Death Do Us Part", "In-Game", true) },
            { "m09\\m09_postmission", new Tuple<string, string, bool>("Till Death Do Us Part", "Post-Mission", false) },
            { "m09\\m09_news", new Tuple<string, string, bool>("Till Death Do Us Part", "News", false) },

            { "m10\\m10_premission", new Tuple<string, string, bool>("A House of Cards", "Pre-Mission", false) },
            { "m10\\m10_main", new Tuple<string, string, bool>("A House of Cards", "In-Game", true) },
            { "scenes\\m10\\m10_main.gms", new Tuple<string, string, bool>("A House of Cards", "In-Game", true) },
            { "m10\\m10_postmission", new Tuple<string, string, bool>("A House of Cards", "Post-Mission", false) },
            { "m10\\m10_news", new Tuple<string, string, bool>("A House of Cards", "News", false) },

            { "m11\\m11_premission", new Tuple<string, string, bool>("A Dance with The Devil", "Pre-Mission", false) },
            { "m11\\m11_main", new Tuple<string, string, bool>("A Dance with The Devil", "In-Game", true) },
            { "scenes\\m11\\m11_main.gms", new Tuple<string, string, bool>("A Dance with The Devil", "In-Game", true) },
            { "m11\\m11_postmission", new Tuple<string, string, bool>("A Dance with The Devil", "Post-Mission", false) },
            { "m11\\m11_news", new Tuple<string, string, bool>("A Dance with The Devil", "News", false) },

            { "m12\\m12_premission", new Tuple<string, string, bool>("Amendment XXV", "Pre-Mission", false) },
            { "m12\\m12_main", new Tuple<string, string, bool>("Amendment XXV", "In-Game", true) },
            { "scenes\\m12\\m12_main.gms", new Tuple<string, string, bool>("Amendment XXV", "In-Game", true) },
            { "m12\\m12_postmission", new Tuple<string, string, bool>("Amendment XXV", "Post-Mission", false) },
            { "m12\\m12_news", new Tuple<string, string, bool>("Amendment XXV", "News", false) },

            { "m13\\m13_intro", new Tuple<string, string, bool>("Requiem", "Intro", false) },
            { "m13\\m13_main", new Tuple<string, string, bool>("Requiem", "In-Game", true) },
            { "scenes\\m13\\m13_main.gms", new Tuple<string, string, bool>("Requiem", "In-Game", true) },
        };

        public string Name { get { return "H3"; } }
        public bool Active { get; private set; }

        public ProcessMemoryReader Reader { get; private set; }

        public StatTracker StatTracker { get; private set; }
        public TimeTracker TimeTracker { get; private set; }

        public MainControl Control { get; private set; }

        public string CurrentScene { get; private set; }
        public string CurrentLevel { get; private set; }
        public string CurrentLevelScene { get; private set; }
        public bool InGame { get; private set; }

        private Process m_GameProcess;
        private Injector m_Injector;

        private uint m_SkipUpdates;

        private readonly List<Control> m_MenuItems; 

        public HM3Engine()
        {
            m_MenuItems = new List<Control>();
            Active = false;
        }

        private void InitMenuItems()
        {
            MainApp.MainWindow.Dispatcher.Invoke(() =>
            {
                var s_EnableCheats = new MenuItem()
                {
                    Header = "Enable Cheats",
                    IsCheckable = true,
                    IsChecked = false
                };

                s_EnableCheats.Click += OnEnableCheats;

                var s_UnlimitedSaves = new MenuItem()
                {
                    Header = "Unlimited Saves",
                    IsCheckable = true,
                    IsChecked = false
                };

                s_UnlimitedSaves.Click += OnUnlimitedSaves;

                var s_Hitman2016 = new MenuItem()
                {
                    Header = "Hitman 2016 Mode",
                    IsCheckable = true,
                    IsChecked = false
                };

                s_Hitman2016.Click += OnHitman2016Mode;

                m_MenuItems.Clear();
                m_MenuItems.Add(s_EnableCheats);
                m_MenuItems.Add(s_UnlimitedSaves);
                m_MenuItems.Add(s_Hitman2016);
            });
        }

        private void OnEnableCheats(object p_Sender, RoutedEventArgs p_RoutedEventArgs)
        {
            var s_MenuItem = p_Sender as MenuItem;

            if (s_MenuItem == null) 
                return;

            SendMessage("EC", s_MenuItem.IsChecked ? "true" : "false");
        }

        private void OnUnlimitedSaves(object p_Sender, RoutedEventArgs p_RoutedEventArgs)
        {
            var s_MenuItem = p_Sender as MenuItem;

            if (s_MenuItem == null)
                return;

            SendMessage("US", s_MenuItem.IsChecked ? "true" : "false");
        }

        private void OnHitman2016Mode(object p_Sender, RoutedEventArgs p_RoutedEventArgs)
        {
            var s_MenuItem = p_Sender as MenuItem;

            if (s_MenuItem == null)
                return;

            SendMessage("H2", s_MenuItem.IsChecked ? "true" : "false");
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

                m_SkipUpdates = 4;

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

                var s_Processes = Process.GetProcessesByName("HitmanBloodMoney");

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

                        Control.SetCurrentLevel(CurrentLevel);
                        Control.SetCurrentLevelScene(CurrentLevelScene);

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
            switch (p_Type)
            {
                case "CS":
                {
                    CurrentScene = p_Data.ToLowerInvariant().Replace("/", "\\");

                    Tuple<string, string, bool> s_LevelData;
                    if (!m_SceneNames.TryGetValue(CurrentScene, out s_LevelData))
                    {
                        CurrentLevel = "No Level";
                        CurrentLevelScene = "No Level";
                        InGame = false;
                    }
                    else
                    {
                        CurrentLevel = s_LevelData.Item1;
                        CurrentLevelScene = s_LevelData.Item2;
                        InGame = s_LevelData.Item3;
                    }

                    Control.SetCurrentLevel(CurrentLevel);
                    Control.SetCurrentLevelScene(CurrentLevelScene);

                    break;
                }
                case "SA":
                {
                    int statAddr = 0;
                    if (int.TryParse(p_Data, out statAddr))
                    {
                        StatTracker.StatAddress = new IntPtr(statAddr);
                    }
                    break;
                }
                case "DA":
                {
                    int difficultyAddr = 0;
                    if (int.TryParse(p_Data, out difficultyAddr))
                    {
                        StatTracker.DifficultyAddress = new IntPtr(difficultyAddr);
                    }
                    break;
                }
            }
        }

        public void SendMessage(string p_Type, string p_Contents)
        {
            MainApp.Pipeman.PushMessage(new PipeMessage()
            {
                Module = Name, 
                Type = p_Type, 
                Content = p_Contents
            });
        }

        public void Dispose()
        {
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
    }
}
