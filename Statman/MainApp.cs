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
            var s_ForceQuitThread = new Thread(ForceQuit);
            s_ForceQuitThread.Start();

            Loop.Dispose();
            EngineManager.Dispose();
            Pipeman.Stop();
        }

        private static void ForceQuit()
        {
            Thread.Sleep(1000);
            Environment.Exit(0);
        }

        public static void RegisterEngines()
        {
            // Register all supported/required engines.
#if AMD64
            EngineManager.RegisterEngine(new HM5Engine());
#else
            EngineManager.RegisterEngine(new HM3Engine());
#endif
        }
    }
}
