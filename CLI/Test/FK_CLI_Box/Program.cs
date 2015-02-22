using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Box
{
	class Program
	{
		static void Main(string[] args)
		{
			int i;

			// ウィンドウ生成
			var win = new fk_AppWindow();
			fk_Material.InitDefault();

			// 光源生成
			var light = new fk_Light();
			var lightModel = new fk_Model();
			lightModel.setMaterial(fk_Material.TrueWhite);
			lightModel.glMoveTo(0.0, 0.0, 0.0);
			lightModel.glFocus(-1.0, -1.0, -1.0);
			win.Entry(lightModel);

			// 直方体モデル生成
			var blockModel = new fk_Model();
			var block = new fk_Block(50.0, 70.0, 40.0);
			blockModel.setShape(block);
			blockModel.setMaterial(fk_Material.Yellow);
			win.Entry(blockModel);

			// 線分モデル生成
			fk_Vector[] pos = new fk_Vector[4];
			pos[0] = new fk_Vector(0.0, 100.0, 0.0);
			pos[1] = new fk_Vector(100.0, 0.0, 0.0);
			pos[2] = -pos[0];
			pos[3] = -pos[1];
			fk_Line[] line = new fk_Line[2];
			fk_Model[] lineModel = new fk_Model[2];
			for(i = 0; i < 2; i++) {
				line[i] = new fk_Line();
				line[i].PushLine(pos[2*i], pos[2*i + 1]);
				lineModel[i] = new fk_Model();
				lineModel[i].setShape(line[i]);
				lineModel[i].setParent(blockModel);
				win.Entry(lineModel[i]);
			}

			lineModel[0].setLineColor(1.0f, 0.0f, 0.0f);
			lineModel[1].setLineColor(0.0f, 1.0f, 0.0f);

			// カメラモデル生成
			var camera = new fk_Model();
			camera.glMoveTo(0.0, 0.0, 2000.0);
			camera.glFocus(0.0, 0.0, 0.0);
			camera.glUpvec(0.0, 1.0, 0.0);
			win.CameraModel = camera;
			win.Open();

			var origin = new fk_Vector(0.0, 0.0, 0.0);

			for(i = 0; win.Update() == true; i++) {
				camera.glTranslate(0.0, 0.0, -1.0);
				blockModel.glRotateWithVec(origin, fk_Axis.Y, FK.PI/300.0);
				var cPos = camera.getPosition();
				if(cPos.z < -FK.EPS) camera.glFocus(origin);
				if(i >= 1000) camera.loRotateWithVec(origin, fk_Axis.Z, FK.PI/500.0);
			}
		}
	}
}
