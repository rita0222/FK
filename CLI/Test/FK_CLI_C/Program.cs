using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_C
{
	class Program
	{
		static void Main(string[] args)
		{
			samp1();			
		}

		static void samp1()
		{
			int i;

			// ウィンドウ生成
			var win = new fk_AppWindow();
			fk_Material.InitDefault();

			// 光源生成
			var light = new fk_Light();
			var lightModel = new fk_Model();
			lightModel.Material = fk_Material.TrueWhite;
			lightModel.GlMoveTo(0.0, 0.0, 0.0);
			lightModel.GlFocus(-1.0, -1.0, -1.0);
			win.Entry(lightModel);

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
			win.Open();

			var origin = new fk_Vector(0.0, 0.0, 0.0);

			for(i = 0; win.Update() == true; i++) {
				camera.GlTranslate(0.0, 0.0, -1.0);
				var cPos = camera.Position;
				if(cPos.z < -FK.EPS) camera.GlFocus(origin);
				if(i >= 1000) camera.LoRotateWithVec(origin, fk_Axis.Z, FK.PI/500.0);
			}
		}

		static void samp2()
		{
			// ウィンドウ生成
			var win = new fk_AppWindow();
			fk_Material.InitDefault();

			var textImage = new fk_TextImage();
			var texture = new fk_RectTexture();
			var str = new fk_UniStr();
			var strModel = new fk_Model();

			str.convert("FK 日本語");
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
			texture.TextureSize = new fk_TexCoord(40.0, 10.0);
			strModel.Material = fk_Material.TrueWhite;

			strModel.Shape = texture;
			strModel.GlVec(0.0, 0.0, -1.0);
			win.Entry(strModel);
			strModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.X, FK.PI/2.0);
			win.Open();
			win.CameraPos = new fk_Vector(0.0, 0.0, 100.0);
			win.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
			while(win.Update() == true) {
				strModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.X, -FK.PI/500.0);
			}
		}
		static void samp3()
		{
			var window = new fk_AppWindow();
			fk_Material.InitDefault();
			
			var sprite = new fk_SpriteModel();
			var block = new fk_Block(1.0, 1.0, 1.0);
			var model = new fk_Model();
			var origin = new fk_Vector(0.0, 0.0, 0.0);
			int count;
			string str;
 
			if(sprite.initFont("mona.ttf") == false) {
				System.Console.WriteLine("Font Error");
			}

			sprite.setPositionLT(-280.0, 230.0);
			window.Entry(sprite);
 
			model.Shape = block;
			model.GlMoveTo(0.0, 6.0, 0.0);
			model.Material = fk_Material.Yellow;
			window.Entry(model);
 
			window.CameraPos = new fk_Vector(0.0, 5.0, 20.0);
			window.CameraFocus = new fk_Vector(0.0, 5.0, 0.0);
			window.Size = new fk_Dimension(800, 600);
			window.BGColor= new fk_Color(0.6, 0.7, 0.8);
			window.Open();
			window.ShowGuide(fk_GuideMode.GRID_XZ);
 
			count = 0;
			while(window.Update() == true) {
				str = "count = " + count.ToString();
				sprite.drawText(str, true);
				model.GlRotateWithVec(origin, fk_Axis.Y, FK.PI/360.0);
				count++;
			}
		}
	}
}
