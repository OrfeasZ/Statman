using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Statman.Engines.HM5.Windows
{
    /// <summary>
    /// Interaction logic for SceneLoader.xaml
    /// </summary>
    public partial class SceneLoader : Window
    {
        public string Scene => SceneNameText.Text;
        public string Brick1 => Brick1Text.Text;
        public string Brick2 => Brick2Text.Text;
        public string Brick3 => Brick3Text.Text;
        public string SceneType => SceneTypeText.Text;
        public string CodeNameHint => CodeNameHintText.Text;

        public SceneLoader()
        {
            InitializeComponent();
        }

        private void LoadSceneBtn_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }
    }
}
