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
            var s_ActiveEngines = false;

            foreach (var s_Engine in m_Engines)
            {
                s_Engine.Update();

                if (!s_Engine.Active) 
                    continue;

                // Skip updating other engines when an engine is active.
                s_ActiveEngines = true;
                break;
            }

            // Remove any and all engine controls.
            if (!s_ActiveEngines)
                MainApp.MainWindow.ResetEngineControls();
        }
    }
}
