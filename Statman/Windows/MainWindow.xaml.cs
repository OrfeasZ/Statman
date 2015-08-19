using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Shapes;
using Statman.Util;

namespace Statman.Windows
{
    partial class MainWindow : AnimatedWindow
    {
        private Size m_BaseSize;
        private bool m_HasEngineControl;

        private readonly List<Control> m_DefaultMenuItems;
        private readonly ObservableCollection<Control> m_ContextMenuItems;
        private List<Control> m_EngineMenuItems;

        private bool m_DarkTheme;

        public MainWindow()
        {
            m_DarkTheme = false;
            m_DefaultMenuItems = new List<Control>();
            m_ContextMenuItems = new ObservableCollection<Control>();

            InitContextMenuItems();
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

        public void SetEngineControl(UserControl p_Control, List<Control> p_EngineMenuItems = null)
        {
            Dispatcher.Invoke((Action) (() =>
            {
                m_HasEngineControl = true;
                m_EngineMenuItems = p_EngineMenuItems;

                ContentGrid.Children.Clear();
                ContentGrid.Children.Add(p_Control);

                WaitingLabel.Visibility = Visibility.Hidden;
                ContentGrid.Visibility = Visibility.Visible;

                OldSize = m_BaseSize;
                NewSize = new Size(m_BaseSize.Width, (m_BaseSize.Height - 30) + p_Control.Height);

                ApplyResizeAnimation();
                UpdateContextMenu();
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
                UpdateContextMenu();
            }));
        }

        private void InitContextMenuItems()
        {
            var s_Assembly = Assembly.GetExecutingAssembly();
            var s_VersionInfo = FileVersionInfo.GetVersionInfo(s_Assembly.Location);
            var s_Version = s_VersionInfo.FileVersion;

            var s_Header = new MenuItem() { Header = "Statman v" + s_Version, StaysOpenOnClick = true, IsEnabled = false };

            var s_ToggleTheme = new MenuItem() { Header = "Toggle Theme" };
            s_ToggleTheme.Click += OnToggleTheme;
            
            var s_CheckForUpdates = new MenuItem() { Header = "Check for Updates" };
            s_CheckForUpdates.Click += OnCheckForUpdates;

            var s_Exit = new MenuItem() { Header = "Exit" };
            s_Exit.Click += OnExit;

            m_DefaultMenuItems.Add(s_Header);
            m_DefaultMenuItems.Add(new Separator());
            m_DefaultMenuItems.Add(s_ToggleTheme);
            m_DefaultMenuItems.Add(s_CheckForUpdates);
            m_DefaultMenuItems.Add(s_Exit);
        }

        private void OnToggleTheme(object p_Sender, RoutedEventArgs p_RoutedEventArgs)
        {
            if (m_DarkTheme)
                ThemeManager.SetCurrentTheme(this, new Uri("/Statman;component/Themes/DefaultTheme.xaml", UriKind.Relative));  
            else
                ThemeManager.SetCurrentTheme(this, new Uri("/Statman;component/Themes/DarkTheme.xaml", UriKind.Relative));

            m_DarkTheme = !m_DarkTheme;
        }

        private void OnCheckForUpdates(object p_Sender, RoutedEventArgs p_RoutedEventArgs)
        {
            MessageBox.Show("Checking for updates.");
        }

        private void OnExit(object p_Sender, RoutedEventArgs p_RoutedEventArgs)
        {
            Close();
        }

        private void UpdateContextMenu()
        {
            m_ContextMenuItems.Clear();

            foreach (var s_Item in m_DefaultMenuItems)
                m_ContextMenuItems.Add(s_Item);

            if (!m_HasEngineControl || m_EngineMenuItems == null || m_EngineMenuItems.Count == 0)
                return;

            m_ContextMenuItems.Add(new Separator());

            foreach (var s_Item in m_EngineMenuItems)
                m_ContextMenuItems.Add(s_Item);
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            ThemeManager.SetCurrentTheme(this, new Uri("/Statman;component/Themes/DefaultTheme.xaml", UriKind.Relative));  

            UpdateContextMenu();
    
            // Setup our custom context menu.
            var s_TitleBar = GetChildControl<Rectangle>("PART_TitleBar");
            s_TitleBar.ContextMenu = new ContextMenu { ItemsSource = m_ContextMenuItems };
            s_TitleBar.MouseLeftButtonDown += TitleBarOnMouseUp;
        }

        private void TitleBarOnMouseUp(object p_Sender, MouseButtonEventArgs p_MouseButtonEventArgs)
        {
            if (p_MouseButtonEventArgs.ClickCount == 2)
                OnToggleTheme(null, null);
        }
    }
}
