using System;
using System.Collections.Generic;
using System.Windows;
using Statman.Util;

namespace Statman
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application, ISingleInstanceApp
    {
        [STAThread]
        public static void Main()
        {
            // Only allow a single instance of Statman
            // to run at any given point in time.
            if (!SingleInstance<App>.InitializeAsFirstInstance("Statman_4e29fa")) 
                return;

            var s_Application = new App();

            s_Application.InitializeComponent();
            s_Application.Run();

            SingleInstance<App>.Cleanup();
        }

        public bool SignalExternalCommandLineArgs(IList<string> p_Args)
        {
            if (MainApp.MainWindow != null)
                MainApp.MainWindow.Activate();

            return true;
        }
    }
}
