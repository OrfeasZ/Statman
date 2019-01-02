using System;
using System.Windows.Controls;
using System.Windows.Media;

namespace Statman.Engines.HM5.Controls
{
    public partial class MainControl : UserControl
    {
        public MainControl()
        {
            InitializeComponent();
        }

        public void SetCurrentLevel(string p_GameMode, string p_Level)
        {
            Dispatcher.Invoke(() =>
            {
                GameModeLabel.Content = p_GameMode.Replace("_", "__").ToUpperInvariant();
                CurrentLevelLabel.Content = p_Level.Replace("_", "__");
            });
        }
        
        public void SetGameTime(double p_Time)
        {
            SetGameTime((long)(p_Time * 1000.0));
        }

        public void SetGameTime(long p_Time)
        {
            Dispatcher.Invoke(() =>
            {
                var s_TimeStamp = TimeSpan.FromMilliseconds(p_Time);
                GameTimeLabel.Content = s_TimeStamp.ToString("hh\\:mm\\:ss\\.fff");
            });
        }

        public void SetRealTime(double p_Time)
        {
            SetRealTime((long)(p_Time * 1000.0));
        }

        public void SetRealTime(long p_Time)
        {
            Dispatcher.Invoke(() =>
            {
                var s_TimeStamp = TimeSpan.FromMilliseconds(p_Time);
                RealTimeLabel.Content = s_TimeStamp.ToString("hh\\:mm\\:ss\\.fff");
            });
        }

    }
}
