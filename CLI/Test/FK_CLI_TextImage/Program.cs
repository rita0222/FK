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
			fk_Material.initDefault();

			var textImage = new fk_TextImage();
			var texture = new fk_RectTexture();
			var str = new fk_UniStr();
			var strModel = new fk_Model();

			str.convert("FK日本語");
			texture.setImage(textImage);
			if(textImage.initFont("mona.ttf") == false) {
				System.Console.WriteLine("Font Error");
			}
			textImage.setDPI(96);
			textImage.setPTSize(96);
			textImage.setLineSkip(30);
			textImage.setForeColor(0.5, 1.0, 0.8, 1.0);
			textImage.setBackColor(0.2, 0.7, 0.8, 0.0);
			textImage.setAlign(fk_TextAlign.CENTER);
			textImage.loadUniStr(str);
			texture.setTextureSize(40.0, 10.0);
			strModel.setMaterial(fk_Material.TrueWhite);			

			strModel.setShape(texture);
			strModel.glVec(0.0, 0.0, -1.0);
			strModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Axis.X, FK.PI/2.0);
			win.entry(strModel); 
			win.open();
			win.setCameraPos(0.0, 0.0, 100.0);
			win.setCameraFocus(0.0, 0.0, 0.0);
			while(win.update() == true) {
				strModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Axis.X, -FK.PI/500.0);
			}
		}
	}
}
