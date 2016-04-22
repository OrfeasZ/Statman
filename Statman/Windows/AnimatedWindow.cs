using System;
using System.Diagnostics;
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

        private Storyboard m_SizeUpStoryboard;
        private Storyboard m_SizeDownStoryboard;

        static AnimatedWindow()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(AnimatedWindow), new FrameworkPropertyMetadata(typeof(AnimatedWindow)));
        }

        protected void OnLoaded()
        {
            m_SizeUpStoryboard = FindResource("SizeUp") as Storyboard;
            m_SizeDownStoryboard = FindResource("SizeDown") as Storyboard;

            Storyboard.SetTarget(m_SizeUpStoryboard, this);
            Storyboard.SetTarget(m_SizeDownStoryboard, this);
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            m_Contents = GetChildControl<Border>("PART_WindowContent");
        }

        public void ApplyResizeAnimation()
        {
            var s_InitialPosition = new Point(Left, Top);

            Left = s_InitialPosition.X;
            Top = s_InitialPosition.Y;
            
            if (NewSize.Width > OldSize.Width || NewSize.Height > OldSize.Height)
            {
                (m_SizeUpStoryboard.Children[0] as DoubleAnimation).To = NewSize.Height;
                (m_SizeUpStoryboard.Children[1] as DoubleAnimation).To = NewSize.Width;

                m_SizeUpStoryboard.Begin();
            }
            else
            {
                (m_SizeDownStoryboard.Children[0] as DoubleAnimation).To = NewSize.Height;
                (m_SizeDownStoryboard.Children[1] as DoubleAnimation).To = NewSize.Width;

                m_SizeDownStoryboard.Begin();
            }
        }
    }
}
