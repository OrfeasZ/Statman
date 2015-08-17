using System;
using System.Text;

namespace Statman.Engines.H3
{
    class SceneTracker
    {
        public string CurrentScene { get; private set; }

        private readonly H3Engine m_Engine;

        public SceneTracker(H3Engine p_Engine)
        {
            m_Engine = p_Engine;
        }

        public bool Update()
        {
            try
            {
                var s_BasePtrData = m_Engine.Reader.Read(m_Engine.Reader.Process.MainModule.BaseAddress + 0x004B3FC0, 4);

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

                CurrentScene = s_Scene;

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
    }
}
