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

            // 組込マテリアル初期化
            fk_Material.InitDefault();

			// 直方体モデル生成
			var blockModel = new fk_Model();
			var block = new fk_Block(50.0, 70.0, 40.0);
			blockModel.Shape = block;
			blockModel.Material = fk_Material.Yellow;
			win.Entry(blockModel);

			// 線分モデル生成
			var pos = new fk_Vector[4];
			pos[0] = new fk_Vector(0.0, 100.0, 0.0);
			pos[1] = new fk_Vector(100.0, 0.0, 0.0);
			pos[2] = -pos[0];
			pos[3] = -pos[1];
			var line = new fk_Line[2];
			var lineModel = new fk_Model[2];
			for(i = 0; i < 2; i++) {
				line[i] = new fk_Line();
				line[i].PushLine(pos[2*i], pos[2*i + 1]);
				lineModel[i] = new fk_Model();
				lineModel[i].Shape = line[i];
				lineModel[i].Parent = blockModel;
				win.Entry(lineModel[i]);
			}

			lineModel[0].LineColor = new fk_Color(1.0, 0.0, 0.0);
			lineModel[1].LineColor = new fk_Color(0.0, 1.0, 0.0);

			// カメラモデル生成
			var camera = new fk_Model();
			camera.GlMoveTo(0.0, 0.0, 2000.0);
			camera.GlFocus(0.0, 0.0, 0.0);
			camera.GlUpvec(0.0, 1.0, 0.0);
			win.CameraModel = camera;

            // ウィンドウ生成
			win.Open();

			var origin = new fk_Vector(0.0, 0.0, 0.0);

			for(i = 0; win.Update() == true; i++) {
				camera.GlTranslate(0.0, 0.0, -1.0);
				blockModel.GlRotateWithVec(origin, fk_Axis.Y, FK.PI/300.0);
				var cPos = camera.Position;
				if(cPos.z < -FK.EPS) camera.GlFocus(origin);
				if(i >= 1000) camera.LoRotateWithVec(origin, fk_Axis.Z, FK.PI/500.0);
			}
		}
	}
}
