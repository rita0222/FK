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

			str.Convert("FK日本語");
			texture.Image = textImage;
			if(textImage.InitFont("mona.ttf") == false) {
				System.Console.WriteLine("Font Error");
			}
			textImage.DPI = 96;
			textImage.PTSize = 96;
			textImage.LineSkip = 30;
			textImage.ForeColor = new fk_Color(0.5, 1.0, 0.8, 1.0);
			textImage.BackColor = new fk_Color(0.2, 0.7, 0.8, 0.0);
			textImage.Align = fk_TextAlign.CENTER;
			textImage.LoadUniStr(str);
			texture.TextureSize = new fk_TexCoord(40.0, 10.0);
			strModel.Material = fk_Material.TrueWhite;

			strModel.Shape = texture;
			strModel.GlVec(0.0, 0.0, -1.0);
			strModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.X, FK.PI/2.0);
			win.Entry(strModel); 
			win.Open();
			win.CameraPos = new fk_Vector(0.0, 0.0, 100.0);
			win.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
			while(win.Update() == true) {
				strModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.X, -FK.PI/500.0);
			}
		}
	}
}
