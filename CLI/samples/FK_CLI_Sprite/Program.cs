using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Sprite
{
	class Program
	{
		static void Main(string[] args)
		{
			fk_Material.InitDefault();

            // 各種変数生成
			var window = new fk_AppWindow();
            var sprite = new fk_SpriteModel();
            var block = new fk_Block(1.0, 1.0, 1.0);
			var model = new fk_Model();
			var origin = new fk_Vector(0.0, 0.0, 0.0);

            // フォントデータ入力
            if(sprite.InitFont("rm1b.ttf") == false) {
				Console.WriteLine("Font Error");
			}

            // フォント設定
            sprite.Text.MonospaceMode = true;
			sprite.Text.MonospaceSize = 12;
			window.Entry(sprite);

            // 立方体設定
            model.Shape = block;
			model.GlMoveTo(0.0, 6.0, 0.0);
			model.Material = fk_Material.Yellow;
            window.Entry(model);

            // ウィンドウ設定
            window.CameraPos = new fk_Vector(0.0, 5.0, 20.0);
			window.CameraFocus = new fk_Vector(0.0, 5.0, 0.0);
			window.Size = new fk_Dimension(800, 600);
			window.BGColor = new fk_Color(0.6, 0.7, 0.8);
			window.ShowGuide(fk_GuideMode.GRID_XZ);
			window.Open();
 
			for(int count = 0;  window.Update() == true; count++) {
                // 文字列生成
                string str = "count = " + count.ToString();

                // 文字列をスプライトに設定
                sprite.DrawText(str, true);

                // スプライト配置設定
                sprite.SetPositionLT(-240.0, 230.0);

                // 立方体を回転させる
                model.GlRotateWithVec(origin, fk_Axis.Y, FK.PI/360.0);
			}
		}
	}
}