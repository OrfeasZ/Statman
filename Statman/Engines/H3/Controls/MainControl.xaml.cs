using System;
using System.Windows.Controls;

namespace Statman.Engines.H3.Controls
{
    public partial class MainControl : UserControl
    {
        public MainControl()
        {
            InitializeComponent();
        }

        public void SetCurrentLevel(string p_Level)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                CurrentLevelLabel.Content = p_Level.Replace("_", "__");
            }));
        }

        public void SetCurrentLevelScene(string p_Scene)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                CurrentLevelSceneLabel.Content = p_Scene.Replace("_", "__");
            }));
        }

        public void SetCurrentTime(double p_Time)
        {
            SetCurrentTime((long)(p_Time * 1000.0));
        }

        public void SetCurrentTime(long p_Time)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                var s_TimeStamp = TimeSpan.FromMilliseconds(p_Time);
                CurrentTimeLabel.Content = s_TimeStamp.ToString("hh\\:mm\\:ss\\.fff");
            }));
        }

        public void SetRating(string p_Rating)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                RatingLabel.Content = p_Rating.Replace("_", "__");
            }));
        }
    }
}
