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
        
        public void SetDisguiseBroken(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                DisguiseBrokenLabel.Content = p_Value ? "Yes" : "No";
            });
        }
        
        public void SetDisguiseSuspicious(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                DisguiseSuspiciousLabel.Content = p_Value ? "Yes" : "No";
            });
        }
        
        public void SetTrespassing(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                TrespassingLabel.Content = p_Value ? "Yes" : "No";
            });
        }
        
        public void SetDeepTrespassing(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                DeepTrespassingLabel.Content = p_Value ? "Yes" : "No";
            });
        }
        
        public void SetSpottedTrespassing(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                SpottedTrespassingLabel.Content = p_Value ? "Yes" : "No";
            });
        }
        
        public void SetBodyFoundPacify(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                BodyFoundPacifyLabel.Content = p_Value ? "Yes" : "No";
            });
        }
        
        public void SetBodyFoundMurder(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                BodyFoundMurderLabel.Content = p_Value ? "Yes" : "No";
            });
        }
        
        public void SetBodyFoundAccident(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                BodyFoundAccidentLabel.Content = p_Value ? "Yes" : "No";
            });
        }
        
        public void SetBloodPoolFound(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                BloodPoolFoundLabel.Content = p_Value ? "Yes" : "No";
            });
        }
        
        public void SetSpottedEnteringCloset(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                SpottedEnteringClosetLabel.Content = p_Value ? "Yes" : "No";
            });
        }
        
        public void SetDeadBodySeenMurder(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                DeadBodySeenMurderLabel.Content = p_Value ? "Yes" : "No";
            });
        }
        
        public void SetDeadBodySeenAccident(bool p_Value)
        {
            Dispatcher.Invoke(() =>
            {
                DeadBodySeenAccidentLabel.Content = p_Value ? "Yes" : "No";
            });
        }
    }
}
