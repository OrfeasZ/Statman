using System;
using System.Threading;
using Statman.Engines;
using Statman.Network;
using Statman.Windows;

namespace Statman
{
    static class MainApp
    {
        public static MainLoop Loop { get; private set; }
        public static EngineManager EngineManager { get; private set; }
        public static MainWindow MainWindow { get; set; }
        public static PipemanServer Pipeman { get; private set; }
        public static bool CheckForUpdates { get; set; }

        static MainApp()
        {
            // Check for updates on start.
            CheckForUpdates = true;

            // Initialize our main loop at 30Hz.
            Loop = new MainLoop(30);

            // Initialize the engine manager.
            EngineManager = new EngineManager();
            RegisterEngines();

            // Initialize the named pipe server.
            Pipeman = new PipemanServer("Statman_IPC");
            Pipeman.ClientMessage += (p_Connection, p_Message) => EngineManager.OnMessage(p_Message);
            Pipeman.Start();
        }

        public static void Close()
        {
            Loop.Dispose();
            EngineManager.Dispose();
            Thread.Sleep(250);
            Pipeman.Stop();
        }

        public static void RegisterEngines()
        {
            // Register all supported/required engines.
            EngineManager.RegisterEngine(new HM5Engine());
            EngineManager.RegisterEngine(new HM3Engine());
        }
    }
}
