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
using System.Windows.Navigation;
using System.Windows.Shapes;
using FK_CLI;
using FK_FormHelper;
using System.Windows.Threading;

namespace FK_CLI_WpfAppTest
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        private fk_WpfViewport viewport = null;
        private fk_Scene scene = null;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            viewport = new fk_WpfViewport(this.ViewportPanel);

            scene = new fk_Scene();
            viewport.Scene = scene;

            fk_Material.InitDefault();

            // 光源生成
            var light = new fk_Light();
            var lightModel = new fk_Model();
            lightModel.Shape = light;
            lightModel.Material = fk_Material.TrueWhite;
            lightModel.GlMoveTo(0.0, 0.0, 0.0);
            lightModel.GlFocus(-1.0, -1.0, -1.0);
            scene.EntryModel(lightModel);

            // 直方体モデル生成
            var blockModel = new fk_Model();
            var block = new fk_Block(50.0, 70.0, 40.0);
            blockModel.Shape = block;
            blockModel.Material = fk_Material.Yellow;
            blockModel.PickMode = true;
            scene.EntryModel(blockModel);

            // 線分モデル生成
            fk_Vector[] pos = new fk_Vector[4];
            pos[0] = new fk_Vector(0.0, 100.0, 0.0);
            pos[1] = new fk_Vector(100.0, 0.0, 0.0);
            pos[2] = -pos[0];
            pos[3] = -pos[1];
            fk_Line[] line = new fk_Line[2];
            fk_Model[] lineModel = new fk_Model[2];
            for (int i = 0; i < 2; i++)
            {
                line[i] = new fk_Line();
                line[i].PushLine(pos[2 * i], pos[2 * i + 1]);
                lineModel[i] = new fk_Model();
                lineModel[i].Shape = line[i];
                lineModel[i].Parent = blockModel;
                scene.EntryModel(lineModel[i]);
            }

            lineModel[0].LineColor = new fk_Color(1.0, 0.0, 0.0);
            lineModel[1].LineColor = new fk_Color(0.0, 1.0, 0.0);

            // カメラモデル生成
            var camera = new fk_Model();
            camera.GlMoveTo(0.0, 0.0, 2000.0);
            camera.GlFocus(0.0, 0.0, 0.0);
            camera.GlUpvec(0.0, 1.0, 0.0);
            scene.Camera = camera;

            scene.BGColor = new fk_Color(0.5, 0.5, 0.5);

            var origin = new fk_Vector(0.0, 0.0, 0.0);
            int count = 0;
            viewport.Update += (s, ee) =>
            {
                camera.GlTranslate(0.0, 0.0, -1.0);
                blockModel.GlRotateWithVec(origin, fk_Axis.Y, FK.PI / 300.0);
                var cPos = camera.Position;
                if (cPos.z < -FK.EPS) camera.GlFocus(origin);
                if (count >= 1000) camera.LoRotateWithVec(origin, fk_Axis.Z, FK.PI / 500.0);
                ++count;
                this.TextBox1.Text = camera.Position.ToString();
            };

            viewport.Panel.MouseDown += (s, ee) =>
            {
                var result = viewport.GetPickData(ee.X, ee.Y, 1);
                if (result.Any())
                {
                    if (result[0].Model.Equals(blockModel))
                    {
                        result[0].Model.Material = fk_Material.Red;
                    }
                }
            };

            viewport.Panel.KeyDown += (s, ee) =>
            {
                blockModel.Material = fk_Material.Yellow;
            };

            Button1.Click += (s, ee) =>
            {
                viewport.IsDrawing = !viewport.IsDrawing;
            };
        }
    }
}
