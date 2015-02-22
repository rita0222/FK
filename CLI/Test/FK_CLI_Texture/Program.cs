using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Texture
{
	class Program
	{
		static void Main(string[] args)
		{
			var tex = new fk_MeshTexture();

			if(tex.readPNG("samp.png") == false) {
				Console.WriteLine("Image File Read Error.");
				return;
			}

			// テクスチャ画像を置く位置の設定
			tex.setTriNum(4);


			// テクスチャ画像を置く位置の設定

			tex.setVertexPos(0, 0, -100.0, 100.0, 0.0);
			tex.setVertexPos(0, 1, -100.0, 0.0, 0.0);
			tex.setVertexPos(0, 2, 0.0, 100.0, 0.0);
			tex.setVertexPos(1, 0, -100.0, -100.0, 0.0);
			tex.setVertexPos(1, 1, 0.0, -100.0, 0.0);
			tex.setVertexPos(1, 2, -100.0, 0.0, 0.0);
			tex.setVertexPos(2, 0, 100.0, -100.0, 0.0);
			tex.setVertexPos(2, 1, 100.0, 0.0, 0.0);
			tex.setVertexPos(2, 2, 0.0, -100.0, 0.0);
			tex.setVertexPos(3, 0, 100.0, 100.0, 0.0);
			tex.setVertexPos(3, 1, 0.0, 100.0, 0.0);
			tex.setVertexPos(3, 2, 100.0, 0.0, 0.0);

			// テクスチャ座標の設定
			tex.setTextureCoord(0, 0, 0.0, 1.0);
			tex.setTextureCoord(0, 1, 0.0, 0.5);
			tex.setTextureCoord(0, 2, 0.5, 1.0);
			tex.setTextureCoord(1, 0, 0.0, 0.0);
			tex.setTextureCoord(1, 1, 0.5, 0.0);
			tex.setTextureCoord(1, 2, 0.0, 0.5);
			tex.setTextureCoord(2, 0, 1.0, 0.0);
			tex.setTextureCoord(2, 1, 1.0, 0.5);
			tex.setTextureCoord(2, 2, 0.5, 0.0);
			tex.setTextureCoord(3, 0, 1.0, 1.0);
			tex.setTextureCoord(3, 1, 0.5, 1.0);
			tex.setTextureCoord(3, 2, 1.0, 0.5);

			fk_Material.InitDefault();
			var viewer = new fk_ShapeViewer(600, 600);
			viewer.setShape(tex);
			viewer.setMaterial(0, fk_Material.TrueWhite);

			while(viewer.draw() == true) { }
		}
	}
}
