using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;

namespace Statman.Engines.HM5
{
    class StatTracker
    {
        public const long KillCooldown = 2750;

        private static readonly Dictionary<string, Tuple<string, string>> m_Scenes = new Dictionary<string, Tuple<string, string>>()
        {
            { "assembly:/_pro/scenes/missions/thefacility/_scene_mission_polarbear_intro_firsttime.entity", new Tuple<string, string>("Prologue", "Arrival") },
            { "assembly:/_pro/scenes/missions/thefacility/_scene_mission_polarbear_module_002.entity", new Tuple<string, string>("Prologue", "Guided Training") },
            { "assembly:/_pro/scenes/missions/thefacility/_scene_mission_polarbear_module_002_b.entity", new Tuple<string, string>("Prologue", "Freeform Training") },
            { "assembly:/_pro/scenes/missions/thefacility/_scene_mission_polarbear_module_005.entity", new Tuple<string, string>("Prologue", "The Final Test") },
            { "assembly:/_pro/scenes/missions/paris/_scene_paris.entity", new Tuple<string, string>("Hitman", "Paris") },
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
            { "assembly:/_pro/scenes/missions/hokkaido/scene_mamushi.entity", new Tuple<string, string>("Hitman 2", "Hokkaido Snow Festival") },
        };

        private readonly HM5Engine m_Engine;

        private long m_EntitySceneManagerAddr;

        private readonly HashSet<string> m_Spotters;
        private readonly HashSet<string> m_Witnesses;
        private bool m_NonTargetKill;
        private bool m_BodyFound;
        private bool m_NoticedKill;
        private bool m_CaughtOnCamera;

        private readonly Stopwatch m_KillCooldownStopwatch;

        public bool InLevel { get; private set; }

        public StatTracker(HM5Engine p_Engine)
        {
            m_Engine = p_Engine;
            m_Spotters = new HashSet<string>();
            m_Witnesses = new HashSet<string>();
            m_KillCooldownStopwatch = new Stopwatch();
        }

        public bool Update()
        {
            if (m_EntitySceneManagerAddr == 0)
                return false;

            if (m_KillCooldownStopwatch.ElapsedMilliseconds > 0)
            {
                m_Engine.Control.SetCooldownTime(m_KillCooldownStopwatch.ElapsedMilliseconds);

                if (m_KillCooldownStopwatch.ElapsedMilliseconds > KillCooldown)
                    m_KillCooldownStopwatch.Stop();
            }

            m_Engine.Control.SetRatingPerfect(
                m_Spotters.Count == 0 &&
                m_Witnesses.Count == 0 &&
                !m_BodyFound &&
                !m_NonTargetKill &&
                !m_NoticedKill &&
                !m_CaughtOnCamera &&
                (m_KillCooldownStopwatch.ElapsedMilliseconds == 0 || m_KillCooldownStopwatch.ElapsedMilliseconds > KillCooldown)
            );

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

        public void OnContractStart()
        {
            m_Spotters.Clear();
            m_Witnesses.Clear();
            m_BodyFound = false;
            m_NonTargetKill = false;
            m_NoticedKill = false;
            m_CaughtOnCamera = false;
            m_KillCooldownStopwatch.Reset();

            UpdateRating();
        }

        public void UpdateRating()
        {
            m_Engine.Control.SetSpotted(m_Spotters.Count > 0 || m_Witnesses.Count > 0);
            m_Engine.Control.SetBodyFound(m_BodyFound);
            m_Engine.Control.SetNonTargetKill(m_NonTargetKill);
            m_Engine.Control.SetNoticedKill(m_NoticedKill);
            m_Engine.Control.SetCaughtOnCamera(m_CaughtOnCamera);

            if (m_KillCooldownStopwatch.ElapsedMilliseconds > 0)
            {
                m_Engine.Control.SetCooldownTime(m_KillCooldownStopwatch.ElapsedMilliseconds);

                if (m_KillCooldownStopwatch.ElapsedMilliseconds > KillCooldown)
                    m_KillCooldownStopwatch.Stop();
            }
        }

        public void OnSpotted(IEnumerable<string> p_Spotters)
        {
            foreach (var s_Spotter in p_Spotters)
                m_Spotters.Add(s_Spotter);

            UpdateRating();
        }

        public void OnWitnesses(IEnumerable<string> p_Witnesses)
        {
            foreach (var s_Witness in p_Witnesses)
                m_Witnesses.Add(s_Witness);

            UpdateRating();
        }
        
        public void OnCaughtOnCamera()
        {
            m_CaughtOnCamera = true;

            UpdateRating();
        }

        public void OnRecordingsDestroyed()
        {
            m_CaughtOnCamera = false;

            UpdateRating();
        }

        public void OnKill(string p_NPCID, bool p_Accident, bool p_Target)
        {
            if (!p_Accident)
                m_KillCooldownStopwatch.Restart();

            if (p_Target)
            {
                m_Spotters.Remove(p_NPCID);
                m_Witnesses.Remove(p_NPCID);
            }
            else
            {
                m_NonTargetKill = true;
            }

            UpdateRating();
        }

        public void OnBodyFound()
        {
            m_BodyFound = true;
            UpdateRating();
        }

        public void OnNoticedKill()
        {
            m_NoticedKill = true;
            UpdateRating();
        }
    }
}
