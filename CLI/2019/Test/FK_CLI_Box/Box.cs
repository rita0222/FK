using System;
using FK_CLI;

namespace FK_CLI_Box
{
	class Program
	{
		static void Main(string[] args)
		{
            // マテリアル情報の初期化
            fk_Material.InitDefault();

            // ウィンドウ生成
            var win = new fk_AppWindow();

            // ウィンドウサイズ設定
            win.Size = new fk_Dimension(600, 600);

            // Frame Per Second (画面更新速度) の設定
            win.FPS = 60;

			// 直方体モデル生成
			var blockModel = new fk_Model();
			var block = new fk_Block(50.0, 70.0, 40.0);
			blockModel.Shape = block;
			blockModel.Material = fk_Material.Yellow;
			win.Entry(blockModel);

			// 線分モデル生成
			fk_Vector[] pos = new fk_Vector[4];
			pos[0] = new fk_Vector(0.0, 100.0, 0.0);
			pos[1] = new fk_Vector(100.0, 0.0, 0.0);
			pos[2] = -pos[0];
			pos[3] = -pos[1];
			fk_Line[] line = new fk_Line[2];
			fk_Model[] lineModel = new fk_Model[2];
			for(int i = 0; i < 2; i++) {
				line[i] = new fk_Line();
				line[i].PushLine(pos[2*i], pos[2*i + 1]);
				lineModel[i] = new fk_Model();
				lineModel[i].Shape = line[i];
				lineModel[i].Parent = blockModel;
				win.Entry(lineModel[i]);
			}
			lineModel[0].LineColor = new fk_Color(1.0, 0.0, 0.0);
			lineModel[1].LineColor = new fk_Color(0.0, 1.0, 0.0);

			// カメラモデル設定
			var camera = new fk_Model();
			camera.GlMoveTo(0.0, 0.0, 2000.0);
			camera.GlFocus(0.0, 0.0, 0.0);
			camera.GlUpvec(0.0, 1.0, 0.0);
			win.CameraModel = camera;
			win.Open();

			var origin = new fk_Vector(0.0, 0.0, 0.0);
            bool negate = false;

			for(int count = 0; win.Update() == true; count++) {
                // カメラ前進
				camera.GlTranslate(0.0, 0.0, -1.0);

                // ブロックを y 軸中心に回転
                blockModel.GlRotateWithVec(origin, fk_Axis.Y, Math.PI/300.0);

                // カメラの注視点を原点に向ける
                if (camera.Position.z < 0.0 && negate == false)
                {
                    camera.GlFocus(origin);
                    negate = true;
                }

                // カウンターが1000を上回ったらカメラをz軸中心に回転
                if (count >= 1000) camera.LoAngle(new fk_Angle(0.0, 0.0, Math.PI/500.0));
			}
		}
	}
}
