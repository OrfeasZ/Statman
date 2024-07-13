using System;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using Statman.Engines.HM5.CustomTracking;

namespace Statman.Engines.HM5.Controls
{
    public partial class MainControl : UserControl
    {
        private long m_LastCooldownMs;
        private bool m_LastRatingStatus = true;
        private HM5Engine m_Engine;

        public MainControl(HM5Engine p_Engine)
        {
            m_Engine = p_Engine;
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

        public void SetCooldownTime(long p_Ms)
        {
            var s_CurrentMs = StatTracker.KillCooldown - p_Ms;

            if (s_CurrentMs < 0)
                s_CurrentMs = 0;

            if (s_CurrentMs != m_LastCooldownMs)
            {
                m_LastCooldownMs = s_CurrentMs;

                Dispatcher.Invoke(() =>
                {
                    var s_TimeStamp = TimeSpan.FromMilliseconds(s_CurrentMs);
                    Vanilla.KillCooldownLabel.Content = s_TimeStamp.ToString("s\\.fff");

                    if (s_CurrentMs > 0)
                        Vanilla.KillCooldownLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
                    else
                        Vanilla.KillCooldownLabel.Foreground = (Brush)FindResource("LabelBrush");
                });
            }
        }

        public void SetSpotted(bool p_Spotted)
        {
            Dispatcher.Invoke(() =>
            {
                if (p_Spotted)
                {
                    Vanilla.SpottedLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
                    Vanilla.SpottedLabel.Content = "Yes";
                }
                else
                {
                    Vanilla.SpottedLabel.Foreground = (Brush)FindResource("LabelBrush");
                    Vanilla.SpottedLabel.Content = "No";
                }
            });
        }

        public void SetNoticedKill(bool p_NoticedKill)
        {
            Dispatcher.Invoke(() =>
            {
                if (p_NoticedKill)
                {
                    Vanilla.NoticedKillLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
                    Vanilla.NoticedKillLabel.Content = "Yes";
                }
                else
                {
                    Vanilla.NoticedKillLabel.Foreground = (Brush)FindResource("LabelBrush");
                    Vanilla.NoticedKillLabel.Content = "No";
                }
            });
        }

        public void SetBodyFound(bool p_BodyFound)
        {
            Dispatcher.Invoke(() =>
            {
                if (p_BodyFound)
                {
                    Vanilla.BodyFoundLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
                    Vanilla.BodyFoundLabel.Content = "Yes";
                }
                else
                {
                    Vanilla.BodyFoundLabel.Foreground = (Brush)FindResource("LabelBrush");
                    Vanilla.BodyFoundLabel.Content = "No";
                }
            });
        }
        
        public void SetCaughtOnCamera(bool p_CaughtOnCamera)
        {
            Dispatcher.Invoke(() =>
            {
                if (p_CaughtOnCamera)
                {
                    Vanilla.CaughtOnCameraLabel.Foreground = (Brush) FindResource("AlertLabelBrush");
                    Vanilla.CaughtOnCameraLabel.Content = "Yes";
                }
                else
                {
                    Vanilla.CaughtOnCameraLabel.Foreground = (Brush) FindResource("LabelBrush");
                    Vanilla.CaughtOnCameraLabel.Content = "No";
                }
            });
        }

        public void SetNonTargetKill(bool p_NonTargetKill)
        {
            Dispatcher.Invoke(() =>
            {
                if (p_NonTargetKill)
                {
                    Vanilla.NonTargetKillLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
                    Vanilla.NonTargetKillLabel.Content = "Yes";
                }
                else
                {
                    Vanilla.NonTargetKillLabel.Foreground = (Brush)FindResource("LabelBrush");
                    Vanilla.NonTargetKillLabel.Content = "No";
                }
            });
        }

        public void SetRatingPerfect(bool p_Perfect)
        {
            if (p_Perfect == m_LastRatingStatus)
                return;

            m_LastRatingStatus = p_Perfect;

            Dispatcher.Invoke(() =>
            {
                if (p_Perfect)
                    Vanilla.RatingLabel.Foreground = (Brush)FindResource("LabelBrush");
                else
                    Vanilla.RatingLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
            });
        }

        public void ToggleRatingMode()
        {
            Dispatcher.Invoke(() =>
            {
                if (Vanilla.Visibility == Visibility.Hidden)
                {
                    Advanced.Visibility = Visibility.Hidden;
                    Vanilla.Visibility = Visibility.Visible;
                    Height = 350;
                }
                else
                {
                    Vanilla.Visibility = Visibility.Hidden;
                    Advanced.Visibility = Visibility.Visible;
                    Height = 390;
                }

                m_Engine.ResetControl();
            });
        }

        public void OnRatingEvent(EventType p_Event)
        {
            // Get the attribute for this value.
            var s_Type = typeof(EventType);
            var s_Name = Enum.GetName(s_Type, p_Event);

            var s_Attribute = s_Type.GetField(s_Name)
                .GetCustomAttributes(false)
                .OfType<RatingEventAttribute>()
                .FirstOrDefault();

            if (s_Attribute == null)
                return;

            Dispatcher.Invoke(() =>
            {
                // TODO: Add support for allowing users to customize points and selectively toggle events.
                var s_PointsLabel = s_Attribute.Points.ToString();

                if (s_Attribute.Points >= 0)
                    s_PointsLabel = "+" + s_PointsLabel;

                var s_Control = new RatingChange
                {
                    EventLabel = { Content = s_Attribute.Description },
                    PointsLabel = { Content = s_PointsLabel }
                };

                if (s_Attribute.Points > 0)
                    s_Control.PointsLabel.Foreground = (Brush) FindResource("AlertLabelBrush");

                if (s_Attribute.Points < 0)
                    s_Control.PointsLabel.Foreground = (Brush) FindResource("SuccessLabelBrush");

                Advanced.RatingEventsList.Items.Insert(0, s_Control);
            });
        }

        public void SetNotoriety(long p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                Advanced.NotorietyLabel.Content = p_Value.ToString();

                // TODO: Set rating accordingly.
            });
        }

        public void ResetAdvancedRating()
        {
            Dispatcher.Invoke(() =>
            {
                Advanced.NotorietyLabel.Content = "0";
                Advanced.RatingEventsList.Items.Clear();
                Advanced.RatingLabel.Content = "Silent Assassin";
                Advanced.RatingLabel.Foreground = (Brush) FindResource("LabelBrush");
            });
        }
    }
}
