using System;
using System.Windows.Controls;
using System.Windows.Media;

namespace Statman.Engines.HM3.Controls
{
    public partial class MainControl : UserControl
    {
        public MainControl()
        {
            InitializeComponent();
        }

        public void SetCurrentLevel(string p_Level)
        {
            Dispatcher.Invoke(() =>
            {
                CurrentLevelLabel.Content = p_Level.Replace("_", "__");
            });
        }

        public void SetCurrentLevelScene(string p_Scene)
        {
            Dispatcher.Invoke(() =>
            {
                CurrentLevelSceneLabel.Content = p_Scene.Replace("_", "__");
            });
        }

        public void SetCurrentTime(double p_Time)
        {
            SetCurrentTime((long)(p_Time * 1000.0));
        }

        public void SetCurrentTime(long p_Time)
        {
            Dispatcher.Invoke(() =>
            {
                var s_TimeStamp = TimeSpan.FromMilliseconds(p_Time);
                CurrentTimeLabel.Content = s_TimeStamp.ToString("hh\\:mm\\:ss\\.fff");
            });
        }

        public void SetRating(string p_Rating)
        {
            Dispatcher.Invoke(() =>
            {
                RatingLabel.Content = p_Rating.Replace("_", "__");
            });
        }

        public void SetRatingPerfect(bool p_Perfect)
        {
            Dispatcher.Invoke(() =>
            {
                if (p_Perfect)
                    RatingLabel.Foreground = (Brush) FindResource("LightLabelBrush");
                else
                    RatingLabel.Foreground = (Brush) FindResource("AlertLabelBrush");
            });
        }

        public void SetShotsFired(int p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                ShotsFiredLabel.Content = p_Value.ToString();
            });
        }

        public void SetHeadshots(int p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                HeadshotsLabel.Content = p_Value.ToString();
            });
        }

        public void SetAccidents(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                AccidentsLabel.Content = p_Value.ToString();
            }));
        }

        public void SetCloseCombatKills(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                CloseCombatKillsLabel.Content = p_Value.ToString();
            }));
        }

        public void SetBodiesFound(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                BodiesFoundLabel.Content = p_Value.ToString();
            }));
        }

        public void SetCameraCaught(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                CameraCaughtLabel.Content = p_Value.ToString();
            }));
        }

        public void SetEnemiesKilled(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                EnemiesKilledLabel.Content = p_Value.ToString();
            }));
        }

        public void SetEnemiesWounded(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                EnemiesWoundedLabel.Content = p_Value.ToString();
            }));
        }

        public void SetPolicemenKilled(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                PolicemenKilledLabel.Content = p_Value.ToString();
            }));
        }

        public void SetPolicemenWounded(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                PolicemenWoundedLabel.Content = p_Value.ToString();
            }));
        }

        public void SetInnocentsKilled(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                InnocentsKilledLabel.Content = p_Value.ToString();
            }));
        }

        public void SetInnocentsWounded(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                InnocentsWoundedLabel.Content = p_Value.ToString();
            }));
        }

        public void SetWitnesses(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                WitnessesLabel.Content = p_Value.ToString();
            }));
        }

        public void SetTargetsKilled(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                TargetsKilledLabel.Content = p_Value.ToString();
            }));
        }
    }
}
