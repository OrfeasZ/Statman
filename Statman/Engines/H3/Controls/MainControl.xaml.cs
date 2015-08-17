using System;
using System.Windows.Controls;
using System.Windows.Media;

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

        public void SetRatingPerfect(bool p_Perfect)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                if (p_Perfect)
                    RatingLabel.Foreground = new SolidColorBrush(new Color() { A = 255, R = 160, G = 160, B = 160 });
                else
                    RatingLabel.Foreground = new SolidColorBrush(new Color() { A = 255, R = 220, G = 64, B = 64 });
            }));
        }

        public void SetShotsFired(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                ShotsFiredLabel.Content = p_Value.ToString();
            }));
        }

        public void SetHeadshots(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                HeadshotsLabel.Content = p_Value.ToString();
            }));
        }

        public void SetAccidents(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                AccidentsLabel.Content = p_Value.ToString();
            }));
        }

        public void SetAlarms(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                AlarmsLabel.Content = p_Value.ToString();
            }));
        }

        public void SetBodiesFound(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                BodiesFoundLabel.Content = p_Value.ToString();
            }));
        }

        public void SetCameraCaught(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                CameraCaughtLabel.Content = p_Value.ToString();
            }));
        }

        public void SetEnemiesKilled(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                EnemiesKilledLabel.Content = p_Value.ToString();
            }));
        }

        public void SetEnemiesWounded(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                EnemiesWoundedLabel.Content = p_Value.ToString();
            }));
        }

        public void SetPolicemenKilled(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                PolicemenKilledLabel.Content = p_Value.ToString();
            }));
        }

        public void SetPolicemenWounded(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                PolicemenWoundedLabel.Content = p_Value.ToString();
            }));
        }

        public void SetInnocentsKilled(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                InnocentsKilledLabel.Content = p_Value.ToString();
            }));
        }

        public void SetInnocentsWounded(int p_Value)
        {
            Dispatcher.Invoke((Action)(() =>
            {
                InnocentsWoundedLabel.Content = p_Value.ToString();
            }));
        }
    }
}
