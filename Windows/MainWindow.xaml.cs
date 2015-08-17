using System.Windows;

namespace Statman.Windows
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            MainApp.Loop.Start();
        }

        private void Window_Closing(object p_Sender, System.ComponentModel.CancelEventArgs p_Args)
        {
            MainApp.Close();
        }
    }
}
