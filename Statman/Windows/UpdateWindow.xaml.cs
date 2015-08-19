using System.Diagnostics;
using System.Windows;

namespace Statman.Windows
{
    /// <summary>
    /// Interaction logic for UpdateWindow.xaml
    /// </summary>
    public partial class UpdateWindow : Window
    {
        private readonly string m_ReleaseURL;

        public UpdateWindow(string p_CurrentVersion, string p_LatestVersion, string p_ReleaseURL, bool p_PreRelease)
        {
            InitializeComponent();

            m_ReleaseURL = p_ReleaseURL;
            var s_LatestVersion = p_PreRelease ? p_LatestVersion + " [Pre-Release]" : p_LatestVersion;

            UpdateText.Text =
                "A new update for Statman is available!\n\nYour Version: v" + p_CurrentVersion + "\nLatest Version: v" +
                s_LatestVersion + "\n\nClick OK to be redirected to the download page.";
        }

        private void Window_Loaded(object p_Sender, RoutedEventArgs p_Args)
        {
            Activate();
        }

        private void OKButton_Click(object p_Sender, RoutedEventArgs p_Args)
        {
            Process.Start(m_ReleaseURL);
            Close();
        }

        private void CancelButton_Click(object p_Sender, RoutedEventArgs p_Args)
        {
            Close();
        }
    }
}
