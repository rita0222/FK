using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_TextImage
{
	class Program
	{
		static void Main(string[] args)
		{
			// ウィンドウ生成
			var win = new fk_AppWindow();
			fk_Material.InitDefault();

			var textImage = new fk_TextImage();
			var texture = new fk_RectTexture();
			var str = new fk_UniStr();
			var strModel = new fk_Model();

            // 文字列生成
            str.Convert("FK日本語");

            // フォントデータ入力
            if(textImage.InitFont("rm1b.ttf") == false) {
				System.Console.WriteLine("Font Error");
			}

            // テクスチャに文字列板を設定
            texture.Image = textImage;

            // 一文字あたりのピクセル数は DPI * PTSize となる
            textImage.DPI = 96;
            textImage.PTSize = 96;

            // 文字色
			textImage.ForeColor = new fk_Color(0.5, 1.0, 0.8, 1.0);

            // 背景色
            textImage.BackColor = new fk_Color(0.2, 0.7, 0.8, 0.0);

            // 整列 (今回は中央揃え)
            textImage.Align = fk_TextAlign.CENTER;

            // 等幅モード設定 (本来はデフォルトで true)
            textImage.MonospaceMode = true;

            // 等幅モード時の横幅ピクセルサイズ (PTSizeと同一がよい)
            textImage.MonospaceSize = 96;

            // 文字列を入力し文字列板を生成
            textImage.LoadUniStr(str);

            // テクスチャサイズの設定
            texture.TextureSize = new fk_TexCoord(40.0, 10.0);

            // 文字列板モデルのマテリアル設定
            strModel.Material = fk_Material.TrueWhite;

            // 文字列板モデルの形状を texture に設定
			strModel.Shape = texture;

            // 姿勢制御
            strModel.GlVec(0.0, 0.0, -1.0);
			strModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.X, FK.PI/2.0);

            // モデル登録とウィンドウ生成
            win.Entry(strModel); 
			win.Open();

            // カメラ設定
            win.CameraPos = new fk_Vector(0.0, 0.0, 100.0);
            win.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);

            // メインループ
			while(win.Update() == true) {
                // 文字列板モデル回転
                strModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.X, -FK.PI/500.0);
			}
		}
	}
}
