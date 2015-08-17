using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace Statman.Engines.H3
{
    class StatTracker
    {
        private static readonly double[] m_Multipliers =
        {
            0.0, 1.0, 1.5, 2.0, 2.5, 3.0, 3.25, 3.5, 3.75, 4.0, 4.1300001, 4.25, 4.3800001, 4.5, 4.6300001, 4.75,
            4.8800001, 5.0, 5.0599999, 5.1300001, 5.1900001, 5.25, 5.3099999, 5.3800001, 5.4400001, 5.5, 5.5599999,
            5.6300001, 5.6900001, 5.75, 5.8099999, 5.8800001, 5.9400001, 6.0
        };

        private static readonly Dictionary<string, string> m_Ratings = new Dictionary<string, string>()
        {
            { "0x0", "Silent Assassin" },
            { "0x1", "Professional" },
            { "0x2", "Hired Killer" },
            { "0x3", "Murderer" },
            { "0x4", "Mugger" },
            { "0x5", "Messy Murderer" },
            { "0x6", "Exhibitionist" },
            { "1x0", "Hitman" },
            { "1x1", "Specialist" },
            { "1x2", "Contract Killer" },
            { "1x3", "Gangster" },
            { "1x4", "Perpetrator" },
            { "1x5", "Fierce Offender" },
            { "1x6", "Clumsy Killer" },
            { "2x0", "Stalker" },
            { "2x1", "The Ghost" },
            { "2x2", "Hoodlum" },
            { "2x3", "The Cleaner" },
            { "2x4", "Thug" },
            { "2x5", "Violent Thug" },
            { "2x6", "Assailant" },
            { "3x0", "Shadow Killer" },
            { "3x1", "Phantom Killer" },
            { "3x2", "The Eraser" },
            { "3x3", "Killer" },
            { "3x4", "Lunatic" },
            { "3x5", "Madman" },
            { "3x6", "Maniac" },
            { "4x0", "Invisible killer" },
            { "4x1", "The Undertaker" },
            { "4x2", "Lean Killer" },
            { "4x3", "Killer" },
            { "4x4", "Loose Cannon" },
            { "4x5", "Mad Butcher" },
            { "4x6", "Berserker" },
            { "5x0", "Serial Killer" },
            { "5x1", "Serial Killer" },
            { "5x2", "Deranged Slayer" },
            { "5x3", "Terrorist" },
            { "5x4", "Armed Madman" },
            { "5x5", "Psychopath" },
            { "5x6", "Psychopath" },
            { "6x0", "Sociopath" },
            { "6x1", "Serial Killer" },
            { "6x2", "Deranged Slayer" },
            { "6x3", "Terrorist" },
            { "6x4", "Psychopath" },
            { "6x5", "Psychopath" },
            { "6x6", "Mass Murderer" }
        };

        public Stats CurrentStats { get; private set; }

        private readonly H3Engine m_Engine;

        public StatTracker(H3Engine p_Engine)
        {
            m_Engine = p_Engine;
        }

        public bool Update()
        {
            var s_StructData = m_Engine.Reader.Read(m_Engine.Reader.Process.MainModule.BaseAddress + 0x005B2538, 0x10C);

            if (s_StructData == null)
                return false;

            try
            {
                var s_Handle = GCHandle.Alloc(s_StructData, GCHandleType.Pinned);
                var p_Stats = (Stats) Marshal.PtrToStructure(s_Handle.AddrOfPinnedObject(), typeof (Stats));
                s_Handle.Free();

                ProcessStats(p_Stats);
                return true;
            }
            catch
            {
                return false;
            }
        }

        private void ProcessStats(Stats p_Stats)
        {
            var s_LevelTime = p_Stats.m_Time / 1000.0;

            var s_Rating0 = CalculateRating0(p_Stats);
            var s_Rating1 = CalculateRating1(p_Stats);

            Trace.WriteLine("Level Rating: " + m_Ratings[s_Rating0 + "x" + s_Rating1]);

            CurrentStats = p_Stats;
        }

        private uint CalculateRating0(Stats p_Stats)
        {
            var s_Rating0 = 0.0;

            // Innocents Killed
            var s_InnocentsKilled = p_Stats.m_InnocentsKilled >= 34 ? 33 : p_Stats.m_InnocentsKilled;
            s_Rating0 += m_Multipliers[s_InnocentsKilled] * 12.0;

            // Innocents Wounded
            var s_InnocentsWounded = p_Stats.m_InnocentsWounded >= 34 ? 33 : p_Stats.m_InnocentsWounded;
            s_Rating0 += m_Multipliers[s_InnocentsWounded] * 6.0;

            // Enemies Killed
            var s_EnemiesKilled = p_Stats.m_EnemiesKilled >= 34 ? 33 : p_Stats.m_EnemiesKilled;
            s_Rating0 += m_Multipliers[s_EnemiesKilled] * 6.0;

            // Enemies Wounded
            var s_EnemiesWounded = p_Stats.m_EnemiesWounded >= 34 ? 33 : p_Stats.m_EnemiesWounded;
            s_Rating0 += m_Multipliers[s_EnemiesWounded] * 3.0;

            // Policemen Killed
            var s_PoliceMenKilled = p_Stats.m_PoliceMenKilled >= 34 ? 33 : p_Stats.m_PoliceMenKilled;
            s_Rating0 += m_Multipliers[s_PoliceMenKilled] * 9.0;

            // Policemen Wounded
            var s_PoliceMenWounded = p_Stats.m_PoliceMenWounded >= 34 ? 33 : p_Stats.m_PoliceMenWounded;
            s_Rating0 += m_Multipliers[s_PoliceMenWounded] * 5.0;

            // Max Rating is 100
            s_Rating0 = s_Rating0 > 100.0 ? 100.0 : s_Rating0;

            return (uint) Math.Ceiling((Math.Round(s_Rating0) / 100.0) * 6.0);
        }

        private uint CalculateRating1(Stats p_Stats)
        {
            var s_Rating1 = 0.0;

            var s_UnknownPtrData = m_Engine.Reader.Read(m_Engine.Reader.Process.MainModule.BaseAddress + 0x41F83C, 4);

            if (s_UnknownPtrData == null)
                return 0;

            var s_UnknownPtr = BitConverter.ToUInt32(s_UnknownPtrData, 0);

            var s_UnknownValue = m_Engine.Reader.Read(s_UnknownPtr + 0x6664, 1);

            if (s_UnknownValue == null)
                return 0;

            // Frisk Failed
            var s_FriskFailed = p_Stats.m_FriskFailed >= 34 ? 33 : p_Stats.m_FriskFailed;
            s_Rating1 += m_Multipliers[s_FriskFailed] * 6.0;

            // Covers Blown
            var s_CoverBlown = p_Stats.m_CoverBlown >= 34 ? 33 : p_Stats.m_CoverBlown;
            s_Rating1 += m_Multipliers[s_CoverBlown] * 6.0;

            // Bodies Found
            int s_BodiesFound;
            if (s_UnknownValue[0] <= 1)
                s_BodiesFound = p_Stats.m_BodiesFound >= 34 ? 33 : p_Stats.m_BodiesFound;
            else
                s_BodiesFound = (p_Stats.m_BodiesFound + p_Stats.m_TargetBodiesFound) >= 34 ? 33 : (p_Stats.m_BodiesFound + p_Stats.m_TargetBodiesFound);

            s_Rating1 += m_Multipliers[s_BodiesFound] * 6.0;

            // Unknown06
            var s_Unknown06 = p_Stats.m_Unknown06 >= 34 ? 33 : p_Stats.m_Unknown06;
            s_Rating1 += m_Multipliers[s_Unknown06] * 6.0;

            // Witnesses
            var s_Witnesses = p_Stats.m_Witnesses >= 34 ? 33 : p_Stats.m_Witnesses;
            s_Rating1 += m_Multipliers[s_Witnesses] * 8.0;

            // CameraCaught
            var s_CameraCaught = p_Stats.m_CameraCaught >= 34 ? 33 : p_Stats.m_CameraCaught;
            s_Rating1 += m_Multipliers[s_CameraCaught] * 10.0;

            // Items Left
            if (s_UnknownValue[0] == 3)
            {
                if (p_Stats.m_CustomWeaponsLeftOnLevel)
                    s_Rating1 += 5.0;

                if (p_Stats.m_SuitLeftOnLevel)
                    s_Rating1 += 5.0;
            }

            // Max Rating is 100
            s_Rating1 = s_Rating1 > 100.0 ? 100.0 : s_Rating1;

            return (uint) Math.Ceiling((Math.Round(s_Rating1) / 100.0) * 6.0);
        }
    }
}
