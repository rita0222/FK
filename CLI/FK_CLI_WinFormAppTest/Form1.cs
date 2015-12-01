using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using FK_CLI;
using FK_FormHelper;

namespace FK_CLI_WinFormAppTest
{
    public partial class Form1 : Form
    {
        private fk_Viewport viewport = null;
        private fk_Viewport viewport2 = null;
        private fk_Scene scene = null;

        public Form1()
        {
            InitializeComponent();
            
            #region MathTest

            var	mat	= new fk_Matrix();
            var vec = new fk_Vector();
            vec.x = 1.0;
            vec.y = 0.0;
            vec.z = 0.0;
            vec.Normalize();
            this.textBox1.Text = vec.ToString();

			mat.MakeRot(FK.PI/6.0, fk_Axis.Z);
			fk_Vector vec2 = mat * vec;			

			this.textBox2.Text = vec2.ToString();			
            var vecA = new fk_Vector();
            var vecB = new fk_Vector();
			
            vecA.x = 2.0;
            vecB.y = 3.0;

            var vecC = vecA + vecB;

			var vecH = new fk_HVector();
			vecH.x = 5.0;
			vecH.y = 2.0;
			vecH.w = 1.0;

			fk_Vector vecD = vecH;
			fk_HVector vecH2 = vecD;
            this.textBox3.Text = vecH2.ToString();

            #endregion

            // ここからアプリケーションロジック

            scene = new fk_Scene();
            viewport = new fk_Viewport(panel1);
            viewport.Scene = scene;

            viewport2 = new fk_Viewport(panel2);
            viewport2.Scene = scene;

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
            viewport.PreDraw += (s, e) =>
            {
                camera.GlTranslate(0.0, 0.0, -1.0);
                blockModel.GlRotateWithVec(origin, fk_Axis.Y, FK.PI / 300.0);
                var cPos = camera.Position;
                if (cPos.z < -FK.EPS) camera.GlFocus(origin);
                if (count >= 1000) camera.LoRotateWithVec(origin, fk_Axis.Z, FK.PI / 500.0);
                ++count;
				this.textBox1.Text = camera.Position.ToString();
            };

            button1.Click += (s, e) =>
            {
                viewport.IsDrawing = !viewport.IsDrawing;
            };

            viewport.Panel.KeyDown += (s, e) =>
            {
                blockModel.Material = fk_Material.Blue;
            };
        }
    }
}
