using System;
using System.Collections.Generic;
using System.Text;

namespace Statman.Engines.H3
{
    class SceneTracker
    {
        private static readonly Dictionary<string, Tuple<string, string, bool>> m_SceneNames = new Dictionary
            <string, Tuple<string, string, bool>>()
        {
            { "scenes\\hitmanbloodmoney.gms", new Tuple<string, string, bool>("Main Menu", "Menu", false) },
            { "hitmanbloodmoney", new Tuple<string, string, bool>("Main Menu", "Menu", false) },

            { "saveandcontinue", new Tuple<string, string, bool>("Save & Continue", "Menu", false) },

            { "hideout\\hideout_main", new Tuple<string, string, bool>("Hideout", "In-Game", true) },

            { "m00\\m00_intro", new Tuple<string, string, bool>("Death of a Showman", "Intro", false) },
            { "m00\\m00_main", new Tuple<string, string, bool>("Death of a Showman", "In-Game", true) },
            { "m00\\m00_news", new Tuple<string, string, bool>("Death of a Showman", "News", false) },
            { "m00\\m00_albino", new Tuple<string, string, bool>("Death of a Showman", "Story Intro", false) },

            { "m01\\m01_premission", new Tuple<string, string, bool>("A Vintage Year", "Pre-Mission", false) },
            { "m01\\m01_main", new Tuple<string, string, bool>("A Vintage Year", "In-Game", true) },
            { "m01\\m01_postmission", new Tuple<string, string, bool>("A Vintage Year", "Post-Mission", false) },
            { "m01\\m01_news", new Tuple<string, string, bool>("A Vintage Year", "News", false) },

            { "m03\\m03_premission", new Tuple<string, string, bool>("Curtains Down", "Pre-Mission", false) },
            { "m03\\m03_main", new Tuple<string, string, bool>("Curtains Down", "In-Game", true) },
            { "m03\\m03_postmission", new Tuple<string, string, bool>("Curtains Down", "Post-Mission", false) },
            { "m03\\m03_news", new Tuple<string, string, bool>("Curtains Down", "News", false) },

            { "m04\\m04_premission", new Tuple<string, string, bool>("Flatline", "Pre-Mission", false) },
            { "m04\\m04_main", new Tuple<string, string, bool>("Flatline", "In-Game", true) },
            { "m04\\m04_postmission", new Tuple<string, string, bool>("Flatline", "Post-Mission", false) },
            { "m04\\m04_news", new Tuple<string, string, bool>("Flatline", "News", false) },

            { "m05\\m05_premission", new Tuple<string, string, bool>("A New Life", "Pre-Mission", false) },
            { "m05\\m05_main", new Tuple<string, string, bool>("A New Life", "In-Game", true) },
            { "m05\\m05_postmission", new Tuple<string, string, bool>("A New Life", "Post-Mission", false) },
            { "m05\\m05_news", new Tuple<string, string, bool>("A New Life", "News", false) },

            { "m06\\m06_premission", new Tuple<string, string, bool>("Murder of the Crows", "Pre-Mission", false) },
            { "m06\\m06_main", new Tuple<string, string, bool>("Murder of the Crows", "In-Game", true) },
            { "m06\\m06_postmission", new Tuple<string, string, bool>("Murder of the Crows", "Post-Mission", false) },
            { "m06\\m06_news", new Tuple<string, string, bool>("Murder of the Crows", "News", false) },
            
            { "m02\\m02_premission", new Tuple<string, string, bool>("You Better Watch Out", "Pre-Mission", false) },
            { "m02\\m02_main", new Tuple<string, string, bool>("You Better Watch Out", "In-Game", true) },
            { "m02\\m02_postmission", new Tuple<string, string, bool>("You Better Watch Out", "Post-Mission", false) },
            { "m02\\m02_news", new Tuple<string, string, bool>("You Better Watch Out", "News", false) },

            { "m08\\m08_premission", new Tuple<string, string, bool>("Death on the Mississippi", "Pre-Mission", false) },
            { "m08\\m08_main", new Tuple<string, string, bool>("Death on the Mississippi", "In-Game", true) },
            { "m08\\m08_postmission", new Tuple<string, string, bool>("Death on the Mississippi", "Post-Mission", false) },
            { "m08\\m08_news", new Tuple<string, string, bool>("Death on the Mississippi", "News", false) },

            { "m09\\m09_premission", new Tuple<string, string, bool>("Till Death Do Us Part", "Pre-Mission", false) },
            { "m09\\m09_main", new Tuple<string, string, bool>("Till Death Do Us Part", "In-Game", true) },
            { "m09\\m09_postmission", new Tuple<string, string, bool>("Till Death Do Us Part", "Post-Mission", false) },
            { "m09\\m09_news", new Tuple<string, string, bool>("Till Death Do Us Part", "News", false) },

            { "m10\\m10_premission", new Tuple<string, string, bool>("A House of Cards", "Pre-Mission", false) },
            { "m10\\m10_main", new Tuple<string, string, bool>("A House of Cards", "In-Game", true) },
            { "m10\\m10_postmission", new Tuple<string, string, bool>("A House of Cards", "Post-Mission", false) },
            { "m10\\m10_news", new Tuple<string, string, bool>("A House of Cards", "News", false) },

            { "m11\\m11_premission", new Tuple<string, string, bool>("A Dance with The Devil", "Pre-Mission", false) },
            { "m11\\m11_main", new Tuple<string, string, bool>("A Dance with The Devil", "In-Game", true) },
            { "m11\\m11_postmission", new Tuple<string, string, bool>("A Dance with The Devil", "Post-Mission", false) },
            { "m11\\m11_news", new Tuple<string, string, bool>("A Dance with The Devil", "News", false) },

            { "m12\\m12_premission", new Tuple<string, string, bool>("Amendment XXV", "Pre-Mission", false) },
            { "m12\\m12_main", new Tuple<string, string, bool>("Amendment XXV", "In-Game", true) },
            { "m12\\m12_postmission", new Tuple<string, string, bool>("Amendment XXV", "Post-Mission", false) },
            { "m12\\m12_news", new Tuple<string, string, bool>("Amendment XXV", "News", false) },

            { "m13\\m13_intro", new Tuple<string, string, bool>("Requiem", "Intro", false) },
            { "m13\\m13_main", new Tuple<string, string, bool>("Requiem", "In-Game", true) },
        };

        public string CurrentScene { get; private set; }
        public string CurrentLevel { get; private set; }
        public string CurrentLevelScene { get; private set; }
        public bool InGame { get; private set; }

        private readonly H3Engine m_Engine;

        public SceneTracker(H3Engine p_Engine)
        {
            m_Engine = p_Engine;
        }

        public bool Update()
        {
            try
            {
                var s_BasePtrData = m_Engine.Reader.Read(m_Engine.Reader.Process.MainModule.BaseAddress + 0x00081204, 4);

                if (s_BasePtrData == null)
                    return false;

                var s_BasePtr = BitConverter.ToUInt32(s_BasePtrData, 0);

                var s_ScenePtrData = m_Engine.Reader.Read(s_BasePtr + 0x1BC, 4);

                if (s_ScenePtrData == null)
                    return false;

                var s_ScenePtr = BitConverter.ToUInt32(s_ScenePtrData, 0);

                var s_SceneData = m_Engine.Reader.Read(s_ScenePtr + 2, 64);

                if (s_SceneData == null)
                    return false;

                var s_Scene = Encoding.UTF8.GetString(s_SceneData);

                // Properly terminate string.
                var s_NullIndex = s_Scene.IndexOf('\0');

                if (s_NullIndex >= 0)
                    s_Scene = s_Scene.Remove(s_NullIndex);

                CurrentScene = s_Scene.ToLowerInvariant();

                Tuple<string, string, bool> s_LevelInfo;

                // Get level name, scene, and in-game status.
                if (!m_SceneNames.TryGetValue(CurrentScene, out s_LevelInfo))
                {
                    CurrentScene = "";
                    CurrentLevel = "No Level";
                    CurrentLevelScene = "";
                    InGame = false;
                }
                else
                {
                    CurrentLevel = s_LevelInfo.Item1;
                    CurrentLevelScene = s_LevelInfo.Item2;
                    InGame = s_LevelInfo.Item3;
                }

                // Keep showing the last scene when we're in the 
                // Save & Continue screen.
                if (CurrentScene == "saveandcontinue")
                    return true;

                // Update the UI to reflect the current level/scene.
                m_Engine.Control.SetCurrentLevel(CurrentLevel);
                m_Engine.Control.SetCurrentLevelScene(CurrentLevelScene);

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
    }
}
