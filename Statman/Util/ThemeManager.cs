using System;
using System.Linq;
using System.Windows;

namespace Statman.Util
{
    public class ThemeResourceDictionary : ResourceDictionary
    {
    }

    public class ThemeManager : DependencyObject
    {
        public static readonly DependencyProperty CurrentThemeProperty =
            DependencyProperty.RegisterAttached("CurrentTheme", typeof (Uri),
                typeof (ThemeManager),
                new UIPropertyMetadata(null, CurrentThemeChanged));

        public static Uri GetCurrentTheme(DependencyObject p_DependencyObject)
        {
            return (Uri) p_DependencyObject.GetValue(CurrentThemeProperty);
        }

        public static void SetCurrentTheme(DependencyObject p_DependencyObject, Uri p_Value)
        {
            p_DependencyObject.SetValue(CurrentThemeProperty, p_Value);
        }

        private static void CurrentThemeChanged(DependencyObject p_DependencyObject, DependencyPropertyChangedEventArgs p_Args)
        {
            var s_Element = p_DependencyObject as FrameworkElement;

            if (s_Element != null)
                ApplyTheme(s_Element, GetCurrentTheme(s_Element));
        }

        private static void ApplyTheme(FrameworkElement p_TargetElement, Uri p_DictionaryUri)
        {
            if (p_TargetElement == null)
                return;

            ThemeResourceDictionary s_ThemeDictionary = null;

            if (p_DictionaryUri != null)
            {
                s_ThemeDictionary = new ThemeResourceDictionary {Source = p_DictionaryUri};
                p_TargetElement.Resources.MergedDictionaries.Insert(0, s_ThemeDictionary);
            }

            var s_ExistingDictionaries =
                (from s_Dictionary in p_TargetElement.Resources.MergedDictionaries.OfType<ThemeResourceDictionary>()
                    select s_Dictionary).ToList();

            foreach (var s_Dictionary in s_ExistingDictionaries.Where(p_Dictionary => s_ThemeDictionary != p_Dictionary))
                p_TargetElement.Resources.MergedDictionaries.Remove(s_Dictionary);
        }
    }
}