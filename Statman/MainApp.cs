using Statman.Engines;
using Statman.Windows;

namespace Statman
{
    static class MainApp
    {
        public static MainLoop Loop { get; private set; }
        public static EngineManager EngineManager { get; private set; }
        public static MainWindow MainWindow { get; set; }

        static MainApp()
        {
            // Initialize our main loop at 30Hz.
            Loop = new MainLoop(30);

            // Initialize the engine manager.
            EngineManager = new EngineManager();
            RegisterEngines();
        }

        public static void Close()
        {
            Loop.Dispose();
        }

        public static void RegisterEngines()
        {
            // Register all supported/required engines.
            EngineManager.RegisterEngine(new H3Engine());
        }
    }
}
