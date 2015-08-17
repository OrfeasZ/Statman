using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;

namespace Statman.Windows
{
    partial class MainWindow : AnimatedWindow
    {
        private Size m_BaseSize;
        private bool m_HasEngineControl;

        public MainWindow()
        {
            InitializeComponent();

            m_HasEngineControl = false;
            MainApp.MainWindow = this;
            MainApp.Loop.Start();
        }

        private void Window_Closing(object p_Sender, CancelEventArgs p_Args)
        {
            MainApp.Close();
        }

        private void AnimationWindow_Loaded(object p_Sender, RoutedEventArgs p_Args)
        {
            m_BaseSize = new Size(Width, Height);
        }

        public void SetEngineControl(UserControl p_Control)
        {
            Dispatcher.Invoke((Action) (() =>
            {
                m_HasEngineControl = true;

                ContentGrid.Children.Clear();
                ContentGrid.Children.Add(p_Control);

                WaitingLabel.Visibility = Visibility.Hidden;
                ContentGrid.Visibility = Visibility.Visible;

                OldSize = m_BaseSize;
                NewSize = new Size(m_BaseSize.Width, (m_BaseSize.Height - 30) + p_Control.Height);
                ApplyResizeAnimation();
            }));
        }

        public void ResetEngineControls()
        {
            Dispatcher.Invoke((Action) (() =>
            {
                if (!m_HasEngineControl)
                    return;

                m_HasEngineControl = false;

                OldSize = new Size(m_BaseSize.Width, (m_BaseSize.Height - 30) + ((UserControl) ContentGrid.Children[0]).Height);

                ContentGrid.Children.Clear();

                ContentGrid.Visibility = Visibility.Hidden;
                WaitingLabel.Visibility = Visibility.Visible;

                NewSize = m_BaseSize;
                ApplyResizeAnimation();
            }));
        }
    }
}
