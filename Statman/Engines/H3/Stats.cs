using System.Runtime.InteropServices;

namespace Statman.Engines.H3
{
    [StructLayout(LayoutKind.Explicit, Pack = 4)]
    struct Stats
    {
        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0000)]
        public int m_Unknown00;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0004)]
        public int m_Rating1;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0008)]
        public int m_Rating0;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x000C)]
        public int m_SpecialRating;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0010)]
        public int m_Rating1Total;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0014)]
        public int m_Rating0Total;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0018)]
        public int m_CurrentLevel;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x001C)]
        public int m_ShotsFired;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0020)]
        public int m_ShotsHit;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0024)]
        public int m_ShotsMissed;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0028)]
        public int m_Headshots;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x002C)]
        public int m_CleanKills;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0030)]
        public int m_TargetCleanKills;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0034)]
        public int m_AccidentKills;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0038)]
        public int m_Alarms;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x003C)]
        public int m_Witnesses;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0040)]
        public int m_EnemiesKilled;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0044)]
        public int m_Unknown01;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0048)]
        public int m_EnemiesWounded;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x004C)]
        public int m_EnemiesPushedToDeath;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0050)]
        public int m_PoliceMenKilled;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0054)]
        public int m_PoliceMenWounded;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0058)]
        public int m_InnocentsKilled;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x005C)]
        public int m_InnocentsWounded;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0060)]
        public int m_Unknown02;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0064)]
        public int m_Unknown03;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0068)]
        public int m_TargetsSniped;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x006C)]
        public int m_TargetsKilled;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0070)]
        public int m_Unknown04;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0074)]
        public int m_FiberwireKills;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0078)]
        public int m_CloseCombatKills;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x007C)]
        public int m_PreferredWeapon;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0080)]
        public int m_Unknown05;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0084)]
        public int m_NoisyShots;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0088)]
        public int m_NumSaves;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x008C)]
        public int m_BodiesHidden;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0090)]
        public int m_DisguisesUsed;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0094)]
        public int m_Impersonations;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x0098)]
        public int m_AgencyPickups;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x009C)]
        public int m_Time;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00A0)]
        public int m_Money;

        [MarshalAs(UnmanagedType.Bool)]
        [FieldOffset(0x00A4)]
        public bool m_SuitLeftOnLevel;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00A8)]
        public int m_Target1KilledWith;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00AC)]
        public int m_Target2KilledWith;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00B0)]
        public int m_Target3KilledWith;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00B4)]
        public int m_Target4KilledWith;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00B8)]
        public int m_Target5KilledWith;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00BC)]
        public int m_Target6KilledWith;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00C0)]
        public int m_MainTargetNumber;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00C4)]
        public int m_TargetsPoisoned;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00C8)]
        public int m_FriskFailed;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00CC)]
        public int m_GhostFailed;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00D0)]
        public int m_BodiesFound;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00D4)]
        public int m_TargetBodiesFound;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00D8)]
        public int m_Unknown06;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00DC)]
        public int m_CoverBlown;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00E0)]
        public int m_Unknown07;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00E4)]
        public int m_Notoriety;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00E8)]
        public int m_TotalNotoriety;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00EC)]
        public int m_CameraCaught;

        [MarshalAs(UnmanagedType.I4)]
        [FieldOffset(0x00F0)]
        public int m_Unknown08;

        [MarshalAs(UnmanagedType.Bool)]
        [FieldOffset(0x00F4)]
        public bool m_CustomWeaponsLeftOnLevel;

        [MarshalAs(UnmanagedType.Bool)]
        [FieldOffset(0x00F8)]
        public bool m_CustomSniperSilenced;

        [MarshalAs(UnmanagedType.Bool)]
        [FieldOffset(0x00FC)]
        public bool m_CustomHardballerSilenced;

        [MarshalAs(UnmanagedType.Bool)]
        [FieldOffset(0x0100)]
        public bool m_CustomSGSilenced;

        [MarshalAs(UnmanagedType.Bool)]
        [FieldOffset(0x0104)]
        public bool m_CustomMGSilenced;

        [MarshalAs(UnmanagedType.Bool)]
        [FieldOffset(0x0108)]
        public bool m_CustomSMGSilenced;
    }
}
