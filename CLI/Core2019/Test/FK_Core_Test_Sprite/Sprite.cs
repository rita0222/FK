using System;
using FK_CLI;

namespace FK_Core_Test_Sprite
{
	class Program
	{
		static void Main(string[] args)
		{
			var window = new fk_AppWindow();
			fk_Material.InitDefault();
			
            // 文字盤用変数の生成
			var sprite = new fk_SpriteModel();

			var block = new fk_Block(1.0, 1.0, 1.0);
			var model = new fk_Model();
			var origin = new fk_Vector(0.0, 0.0, 0.0);
			int count;
			string str, space;
 
            // 文字盤に対するフォントの読み込み
			if(sprite.InitFont("rm1b.ttf") == false) {
				Console.WriteLine("Font Error");
			}

            // 文字盤の表示位置設定
			sprite.SetPositionLT(-330.0, 240.0);

            // 文字盤のフォントを等幅に設定
			sprite.Text.MonospaceMode = true;

            // 文字盤の(等幅)サイズを設定
			sprite.Text.MonospaceSize = 12;
			window.Entry(sprite);
 
			model.Shape = block;
			model.GlMoveTo(0.0, 6.0, 0.0);
			model.Material = fk_Material.Yellow;
			window.Entry(model);
			window.CameraPos = new fk_Vector(0.0, 5.0, 20.0);
			window.CameraFocus = new fk_Vector(0.0, 5.0, 0.0);
			window.Size = new fk_Dimension(800, 600);
			window.BGColor = new fk_Color(0.6, 0.7, 0.8);
            window.TrackBallMode = true;
			window.Open();
			window.ShowGuide(fk_Guide.GRID_XZ);
 
			count = 0;
			while(window.Update() == true) {
                // 数値の桁数によりスペースの個数を調整
                if (count < 10) space = "   ";
				else if(count < 100) space = "  ";
				else if(count < 1000) space = " ";
				else space = "";

                // 「count = 数値」の文字列を生成
				str = "count = " + space + count.ToString();

                // 文字列を文字盤に入力
				sprite.DrawText(str, true);

                // 文字盤表示位置の再設定
                sprite.SetPositionLT(-330.0, 240.0);

				model.GlRotateWithVec(origin, fk_Axis.Y, Math.PI/360.0);
				count++;
			}
		}
	}
}
