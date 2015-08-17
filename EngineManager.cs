using System;
using System.Collections.Generic;
using Statman.Engines;

namespace Statman
{
    class EngineManager
    {
        private readonly List<IEngine> m_Engines; 

        public EngineManager()
        {
            m_Engines = new List<IEngine>();
            MainApp.Loop.Update += Update;
        }

        public void RegisterEngine(IEngine p_Engine)
        {
            m_Engines.Add(p_Engine);
        }

        private void Update(object p_Sender, EventArgs p_EventArgs)
        {
            foreach (var s_Engine in m_Engines)
            {
                s_Engine.Update();

                // Skip updating other engines when an engine is active.
                if (s_Engine.Active)
                    break;
            }
        }
    }
}
