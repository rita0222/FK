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

			if(tex.ReadBMP("samp.bmp") == false) {
				Console.WriteLine("Image File Read Error.");
				return;
			}

			// テクスチャ画像を置く位置の設定
			tex.TriNum = 4;


			// テクスチャ画像を置く位置の設定

			tex.SetVertexPos(0, 0, -100.0, 100.0, 0.0);
			tex.SetVertexPos(0, 1, -100.0, 0.0, 0.0);
			tex.SetVertexPos(0, 2, 0.0, 100.0, 0.0);
			tex.SetVertexPos(1, 0, -100.0, -100.0, 0.0);
			tex.SetVertexPos(1, 1, 0.0, -100.0, 0.0);
			tex.SetVertexPos(1, 2, -100.0, 0.0, 0.0);
			tex.SetVertexPos(2, 0, 100.0, -100.0, 0.0);
			tex.SetVertexPos(2, 1, 100.0, 0.0, 0.0);
			tex.SetVertexPos(2, 2, 0.0, -100.0, 0.0);
			tex.SetVertexPos(3, 0, 100.0, 100.0, 0.0);
			tex.SetVertexPos(3, 1, 0.0, 100.0, 0.0);
			tex.SetVertexPos(3, 2, 100.0, 0.0, 0.0);

			// テクスチャ座標の設定
			tex.SetTextureCoord(0, 0, 0.0, 1.0);
			tex.SetTextureCoord(0, 1, 0.0, 0.5);
			tex.SetTextureCoord(0, 2, 0.5, 1.0);
			tex.SetTextureCoord(1, 0, 0.0, 0.0);
			tex.SetTextureCoord(1, 1, 0.5, 0.0);
			tex.SetTextureCoord(1, 2, 0.0, 0.5);
			tex.SetTextureCoord(2, 0, 1.0, 0.0);
			tex.SetTextureCoord(2, 1, 1.0, 0.5);
			tex.SetTextureCoord(2, 2, 0.5, 0.0);
			tex.SetTextureCoord(3, 0, 1.0, 1.0);
			tex.SetTextureCoord(3, 1, 0.5, 1.0);
			tex.SetTextureCoord(3, 2, 1.0, 0.5);

			fk_Material.InitDefault();
			var viewer = new fk_ShapeViewer(600, 600);
			viewer.Shape = tex;
			viewer.SetMaterial(0, fk_Material.TrueWhite);

			while(viewer.Draw() == true) { }
		}
	}
}
