using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Animation;

namespace Statman.Windows
{
    [TemplatePart(Type = typeof(Border), Name = "PART_WindowContent")]
    public class AnimatedWindow : GlassWindow
    {
        public Size OldSize
        {
            get { return (Size) GetValue(OldSizeProperty); }
            set { SetValue(OldSizeProperty, value); }
        }

        public Size NewSize
        {
            get { return (Size) GetValue(NewSizeProperty); }
            set { SetValue(NewSizeProperty, value); }
        }

        public static readonly DependencyProperty NewSizeProperty = DependencyProperty.Register("NewSize", typeof(Size), typeof(AnimatedWindow), new PropertyMetadata(new Size()));
        public static readonly DependencyProperty OldSizeProperty = DependencyProperty.Register("OldSize", typeof(Size), typeof(AnimatedWindow), new PropertyMetadata(new Size()));

        private Border m_Contents;

        static AnimatedWindow()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(AnimatedWindow), new FrameworkPropertyMetadata(typeof(AnimatedWindow)));
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            m_Contents = GetChildControl<Border>("PART_WindowContent");
        }

        public void ApplyResizeAnimation()
        {
            var s_InitialPosition = new Point(Left, Top);

            var s_WidthEasingMode = NewSize.Width > OldSize.Width ? EasingMode.EaseOut : EasingMode.EaseIn;
            var s_HeightEasingMode = NewSize.Height > OldSize.Height ? EasingMode.EaseOut : EasingMode.EaseIn;

            var s_WidthAnimation = new DoubleAnimation(OldSize.Width, NewSize.Width, TimeSpan.FromMilliseconds(350))
            {
                EasingFunction = new SineEase() { EasingMode = s_WidthEasingMode }
            };

            var s_HeightAnimation = new DoubleAnimation(OldSize.Height, NewSize.Height, TimeSpan.FromMilliseconds(350))
            {
                EasingFunction = new SineEase() { EasingMode = s_HeightEasingMode }
            };

            Storyboard.SetTargetProperty(s_WidthAnimation, new PropertyPath(WidthProperty));
            Storyboard.SetTarget(s_WidthAnimation, m_Contents);

            Storyboard.SetTargetProperty(s_HeightAnimation, new PropertyPath(HeightProperty));
            Storyboard.SetTarget(s_HeightAnimation, m_Contents);

            var s_Storyboard = new Storyboard();
            
            s_Storyboard.Children.Add(s_WidthAnimation);
            s_Storyboard.Children.Add(s_HeightAnimation);

            if (NewSize.Width > OldSize.Width)
                Width = NewSize.Width;

            if (NewSize.Height > OldSize.Height)
                Height = NewSize.Height;

            Left = s_InitialPosition.X;
            Top = s_InitialPosition.Y;

            s_Storyboard.Begin();
        }
    }
}
