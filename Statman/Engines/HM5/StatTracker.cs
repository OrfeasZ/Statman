using System;
using System.Diagnostics;
using System.Text;

namespace Statman.Engines.HM5
{
    class StatTracker
    {
        private ulong m_LastFlags;

        private readonly HM5Engine m_Engine;

        public StatTracker(HM5Engine p_Engine)
        {
            m_Engine = p_Engine;
        }

        public bool Update()
        {
            try
            {
                /*var s_StructData = m_Engine.Reader.Read(m_Engine.Reader.Process.MainModule.BaseAddress + 0x01E0FC20, 0x320);

                if (s_StructData == null)
                    return false;

                var s_Handle = GCHandle.Alloc(s_StructData, GCHandleType.Pinned);
                var s_Stats = (Stats) Marshal.PtrToStructure(s_Handle.AddrOfPinnedObject(), typeof (Stats));
                s_Handle.Free();

                ProcessStats(s_Stats);
                return true;*/

                var s_FlagData = m_Engine.Reader.Read(m_Engine.Reader.Process.MainModule.BaseAddress + 0x01E0FC20 + 0x80 + 0x118, 0x08);
                var s_Flags = BitConverter.ToUInt64(s_FlagData, 0);

                var s_SceneInitPtr = m_Engine.Reader.Read(m_Engine.Reader.Process.MainModule.BaseAddress + 0x026F74C0 + 0x48, 0x08);
                var s_SceneInitPtrOff = BitConverter.ToInt64(s_SceneInitPtr, 0);

                if (s_SceneInitPtrOff != 0)
                {
                    var s_StringData = m_Engine.Reader.Read(new IntPtr(s_SceneInitPtrOff), 0x10);
                    var s_StringLen = BitConverter.ToInt32(s_StringData, 0);
                    var s_StringPtrOff = BitConverter.ToInt64(s_StringData, 8);

                    if (s_StringLen > 0 && s_StringPtrOff != 0)
                    {
                        var s_RealStringData = m_Engine.Reader.Read(new IntPtr(s_StringPtrOff), s_StringLen);
                        var s_RealString = Encoding.Default.GetString(s_RealStringData);

                        m_Engine.Control.SetCurrentLevel(s_RealString);
                    }
                }

                var s_ZGameTimeManagerData = m_Engine.Reader.Read(m_Engine.Reader.Process.MainModule.BaseAddress + 0x0276ED60, 0x70);
                var s_TicksPerSecond = (double) BitConverter.ToInt32(s_ZGameTimeManagerData, 8);
                var s_GameTime = (double) BitConverter.ToInt64(s_ZGameTimeManagerData, 24);

                if (s_TicksPerSecond > 0)
                {
                    var s_Time = s_GameTime * 0.00000095367432;
                    m_Engine.Control.SetCurrentTime(s_Time);
                }

                ProcessFlags(s_Flags);
                return true;
            }
            catch
            {
                return false;
            }
        }

        private void ProcessFlags(ulong p_Flags)
        {
            if (p_Flags == m_LastFlags)
                return;

            m_LastFlags = p_Flags;

            m_Engine.Control.SetDisguiseBroken((p_Flags & 0x01) != 0);
            m_Engine.Control.SetDisguiseSuspicious((p_Flags & 0x02) != 0);
            m_Engine.Control.SetTrespassing((p_Flags & 0x80) != 0);
            m_Engine.Control.SetDeepTrespassing((p_Flags & 0x100) != 0);
            m_Engine.Control.SetSpottedTrespassing((p_Flags & 0x200) != 0);
            m_Engine.Control.SetBodyFoundPacify((p_Flags & 0x10000) != 0);
            m_Engine.Control.SetBodyFoundMurder((p_Flags & 0x20000) != 0);
            m_Engine.Control.SetBodyFoundAccident((p_Flags & 0x40000) != 0);
            m_Engine.Control.SetBloodPoolFound((p_Flags & 0x80000) != 0);
            m_Engine.Control.SetSpottedEnteringCloset((p_Flags & 0x400000) != 0);
            m_Engine.Control.SetBodyFoundMurder((p_Flags & 0x200000000) != 0);
            m_Engine.Control.SetBodyFoundAccident((p_Flags & 0x400000000) != 0);
        }
    }
}
