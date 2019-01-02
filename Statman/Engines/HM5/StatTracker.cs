using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;

namespace Statman.Engines.HM5
{
    class StatTracker
    {
        private static readonly Dictionary<string, Tuple<string, string>> m_Scenes = new Dictionary<string, Tuple<string, string>>()
        {
            { "assembly:/_pro/scenes/missions/thefacility/_scene_mission_polarbear_intro_firsttime.entity", new Tuple<string, string>("Prologue", "Arrival") },
            { "assembly:/_pro/scenes/missions/thefacility/_scene_mission_polarbear_module_002.entity", new Tuple<string, string>("Prologue", "Guided Training") },
            { "assembly:/_pro/scenes/missions/thefacility/_scene_mission_polarbear_module_002_b.entity", new Tuple<string, string>("Prologue", "Freeform Training") },
            { "assembly:/_pro/scenes/missions/thefacility/_scene_mission_polarbear_module_005.entity", new Tuple<string, string>("Prologue", "The Final Test") },
            { "assembly:/_pro/scenes/missions/paris/_scene_fashionshowhit_01.entity", new Tuple<string, string>("Hitman", "The Showstopper") },
            { "assembly:/_pro/scenes/missions/coastaltown/mission01.entity", new Tuple<string, string>("Hitman", "World of Tomorrow") },
            { "assembly:/_pro/scenes/missions/marrakesh/_scene_mission_spider.entity", new Tuple<string, string>("Hitman", "A Gilded Cage") },
            { "assembly:/_pro/scenes/missions/bangkok/_scene_mission_tiger.entity", new Tuple<string, string>("Hitman", "Club 27") },
            { "assembly:/_pro/scenes/missions/colorado_2/_scene_mission_bull.entity", new Tuple<string, string>("Hitman", "Freedom Fighters") },
            { "assembly:/_pro/scenes/missions/hokkaido/_scene_mission_snowcrane.entity", new Tuple<string, string>("Hitman", "Situs Inversus") },
            { "assembly:/_pro/scenes/missions/sheep/scene_sheep.entity", new Tuple<string, string>("Hitman 2", "Nightcall") },
            { "assembly:/_pro/scenes/missions/miami/scene_flamingo.entity", new Tuple<string, string>("Hitman 2", "The Finish Line") },
            { "assembly:/_pro/scenes/missions/colombia/scene_hippo.entity", new Tuple<string, string>("Hitman 2", "Three-Headed Serpent") },
            { "assembly:/_pro/scenes/missions/mumbai/scene_mongoose.entity", new Tuple<string, string>("Hitman 2", "Chasing a Ghost") },
            { "assembly:/_pro/scenes/missions/skunk/scene_skunk.entity", new Tuple<string, string>("Hitman 2", "Another Life") },
            { "assembly:/_pro/scenes/missions/theark/scene_magpie.entity", new Tuple<string, string>("Hitman 2", "The Ark Society") },
            { "assembly:/_pro/scenes/missions/bangkok/scene_zika.entity", new Tuple<string, string>("Patient Zero", "The Source") },
            { "assembly:/_pro/scenes/missions/coastaltown/scene_ebola.entity", new Tuple<string, string>("Patient Zero", "The Author") },
            { "assembly:/_pro/scenes/missions/colorado_2/scene_rabies.entity", new Tuple<string, string>("Patient Zero", "The Vector") },
            { "assembly:/_pro/scenes/missions/hokkaido/_scene_flu.entity", new Tuple<string, string>("Patient Zero", "Patient Zero") },
            { "assembly:/_pro/scenes/missions/hawk/scene_hawk.entity", new Tuple<string, string>("Sniper Assassin", "The Last Yardbird") },
            { "assembly:/_pro/scenes/missions/paris/_scene_paris.entity", new Tuple<string, string>("Holiday Content", "Holiday Hoarders") },
        };

        private readonly HM5Engine m_Engine;

        private long m_EntitySceneManagerAddr;

        public bool InLevel { get; private set; }

        public StatTracker(HM5Engine p_Engine)
        {
            m_Engine = p_Engine;
        }

        public bool Update()
        {
            if (m_EntitySceneManagerAddr == 0)
                return false;

            try
            {
                var s_SceneName = ZString.FromAddr(m_EntitySceneManagerAddr + 0x10, m_Engine.Reader);
                if (m_Scenes.TryGetValue(s_SceneName.ToLowerInvariant(), out var s_Level))
                {
                    InLevel = true;
                    m_Engine.Control.SetCurrentLevel(s_Level.Item1, s_Level.Item2);
                }
                else
                {
                    InLevel = false;
                    m_Engine.Control.SetCurrentLevel("Hitman", "No Level");
                }
            }
            catch (Exception)
            {
                return false;
            }

            return true;
        }

        public void SetEntitySceneManagerAddr(long p_Addr)
        {
            m_EntitySceneManagerAddr = p_Addr;
        }
    }
}
