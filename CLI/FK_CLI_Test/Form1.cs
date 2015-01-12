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

namespace PlugInTestApp
{
    public partial class Form1 : Form
    {
        private fk_Renderer renderer = null;
        private fk_Scene scene = new fk_Scene();

        public Form1()
        {
            InitializeComponent();

			var	mat	= new fk_Matrix();
            var vec = new fk_Vector();
            vec.x = 1.0;
            vec.y = 0.0;
            vec.z = 0.0;
            vec.normalize();
            this.textBox1.Text = vec.ToString();

			mat.makeRot(FK.PI/6.0, fk_Axis.Z);
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

            // ここからアプリケーションロジック

            fk_Material.initDefault();

            // 光源生成
            var light = new fk_Light();
            var lightModel = new fk_Model();
            lightModel.setShape(light);
            lightModel.setMaterial(fk_Material.TrueWhite);
            lightModel.glMoveTo(0.0, 0.0, 0.0);
            lightModel.glFocus(-1.0, -1.0, -1.0);
            scene.entryModel(lightModel);

            // 直方体モデル生成
            var blockModel = new fk_Model();
            var block = new fk_Block(50.0, 70.0, 40.0);
            blockModel.setShape(block);
            blockModel.setMaterial(fk_Material.Yellow);
            scene.entryModel(blockModel);

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
                line[i].pushLine(pos[2 * i], pos[2 * i + 1]);
                lineModel[i] = new fk_Model();
                lineModel[i].setShape(line[i]);
                lineModel[i].setParent(blockModel);
                scene.entryModel(lineModel[i]);
            }

            lineModel[0].setLineColor(1.0f, 0.0f, 0.0f);
            lineModel[1].setLineColor(0.0f, 1.0f, 0.0f);

            // カメラモデル生成
            var camera = new fk_Model();
            camera.glMoveTo(0.0, 0.0, 2000.0);
            camera.glFocus(0.0, 0.0, 0.0);
            camera.glUpvec(0.0, 1.0, 0.0);
            scene.entryCamera(camera);

            scene.setBGColor(0.5f, 0.5f, 0.5f);

            var origin = new fk_Vector(0.0, 0.0, 0.0);
            int count = 0;
            this.timer1.Interval = 8;
            this.timer1.Enabled = true;
            this.timer1.Tick += (s, e) =>
            {
                camera.glTranslate(0.0, 0.0, -1.0);
                blockModel.glRotateWithVec(origin, fk_Axis.Y, FK.PI / 300.0);
                var cPos = camera.getPosition();
                if (cPos.z < -FK.EPS) camera.glFocus(origin);
                if (count >= 1000) camera.loRotateWithVec(origin, fk_Axis.Z, FK.PI / 500.0);
                ++count;
				this.textBox1.Text = camera.getPosition().ToString();
            };
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            renderer.Draw();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            renderer.Draw();
        }

        private void panel1_Resize(object sender, EventArgs e)
        {
            var loc = this.panel1.Size;
            renderer.Resize(loc.Width, loc.Height);
            renderer.Draw();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            var loc = this.panel1.Size;
            renderer = new fk_Renderer();
            renderer.Initialize(this.panel1.Handle, loc.Width, loc.Height);
            renderer.SetScene(scene);
        }
    }
}
