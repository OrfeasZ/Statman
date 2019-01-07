using System;
using System.Windows.Controls;
using System.Windows.Media;

namespace Statman.Engines.HM5.Controls
{
    public partial class MainControl : UserControl
    {
        private long m_LastCooldownMs;
        private bool m_LastRatingStatus = true;

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
                    KillCooldownLabel.Content = s_TimeStamp.ToString("s\\.fff");

                    if (s_CurrentMs > 0)
                        KillCooldownLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
                    else
                        KillCooldownLabel.Foreground = (Brush)FindResource("LabelBrush");
                });
            }
        }

        public void SetSpotted(bool p_Spotted)
        {
            Dispatcher.Invoke(() =>
            {
                if (p_Spotted)
                {
                    SpottedLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
                    SpottedLabel.Content = "Yes";
                }
                else
                {
                    SpottedLabel.Foreground = (Brush)FindResource("LabelBrush");
                    SpottedLabel.Content = "No";
                }
            });
        }

        public void SetNoticedKill(bool p_NoticedKill)
        {
            Dispatcher.Invoke(() =>
            {
                if (p_NoticedKill)
                {
                    NoticedKillLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
                    NoticedKillLabel.Content = "Yes";
                }
                else
                {
                    NoticedKillLabel.Foreground = (Brush)FindResource("LabelBrush");
                    NoticedKillLabel.Content = "No";
                }
            });
        }

        public void SetBodyFound(bool p_BodyFound)
        {
            Dispatcher.Invoke(() =>
            {
                if (p_BodyFound)
                {
                    BodyFoundLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
                    BodyFoundLabel.Content = "Yes";
                }
                else
                {
                    BodyFoundLabel.Foreground = (Brush)FindResource("LabelBrush");
                    BodyFoundLabel.Content = "No";
                }
            });
        }
        
        public void SetCaughtOnCamera(bool p_CaughtOnCamera)
        {
            Dispatcher.Invoke(() =>
            {
                if (p_CaughtOnCamera)
                {
                    CaughtOnCameraLabel.Foreground = (Brush) FindResource("AlertLabelBrush");
                    CaughtOnCameraLabel.Content = "Yes";
                }
                else
                {
                    CaughtOnCameraLabel.Foreground = (Brush) FindResource("LabelBrush");
                    CaughtOnCameraLabel.Content = "No";
                }
            });
        }

        public void SetNonTargetKill(bool p_NonTargetKill)
        {
            Dispatcher.Invoke(() =>
            {
                if (p_NonTargetKill)
                {
                    NonTargetKillLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
                    NonTargetKillLabel.Content = "Yes";
                }
                else
                {
                    NonTargetKillLabel.Foreground = (Brush)FindResource("LabelBrush");
                    NonTargetKillLabel.Content = "No";
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
                    RatingLabel.Foreground = (Brush)FindResource("LabelBrush");
                else
                    RatingLabel.Foreground = (Brush)FindResource("AlertLabelBrush");
            });
        }
    }
}
