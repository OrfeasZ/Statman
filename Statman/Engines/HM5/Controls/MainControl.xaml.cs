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
                    RatingLabel.Foreground = (Brush) FindResource("LabelBrush");
                else
                    RatingLabel.Foreground = (Brush) FindResource("AlertLabelBrush");
            });
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
                CameraCaughtLabel.Content = p_Value > 0 ? "Yes" : "No";
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

        public void SetCoversBlown(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                CoversBlownLabel.Content = p_Value.ToString();
            }));
        }

        public void SetFriskFailed(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                FriskFailedLabel.Content = p_Value > 0 ? "Yes" : "No";
            }));
        }

        public void SetItemsLeft(int p_Weapons, bool p_Suit)
        {
            Dispatcher.Invoke((() =>
            {
                if (p_Weapons == 0 && !p_Suit)
                    ItemsLeftLabel.Content = "No";
                else if (p_Weapons > 0 && !p_Suit)
                    ItemsLeftLabel.Content = "Weapons";
                else if (p_Weapons == 0)
                    ItemsLeftLabel.Content = "Suit";
                else 
                    ItemsLeftLabel.Content = "Weapons & Suit";
            }));
        }

        public void SetDifficulty(int p_Value)
        {
            Dispatcher.Invoke((() =>
            {
                if (p_Value == 0)
                    DifficultyLabel.Content = "Rookie";
                else if (p_Value == 1)
                    DifficultyLabel.Content = "Normal";
                else if (p_Value == 2)
                    DifficultyLabel.Content = "Expert";
                else if (p_Value == 3)
                    DifficultyLabel.Content = "Professional";
            }));
        }
    }
}
