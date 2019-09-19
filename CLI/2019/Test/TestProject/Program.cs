using System;
using FK_CLI;

namespace TestProject
{
    class Program
    {
        static void Main(string[] args)
        {
			const int V_NUM = 50;						// 立体の分割数
			const double V_LEN = 50.0;					// 立体の長さ
			int i, j, index;

			var viewer = new fk_ShapeViewer(1000, 1000);	// ビューワー
			var ifs = new fk_IndexFaceSet();					// 立体生成用変数
			var pos = new fk_Vector[4*(V_NUM+1)];		// 頂点配列
			var IFSet = new int[4*4*V_NUM];				// インデックスフェースセット用配列

			// 頂点配列の準備
			for(i = 0; i < 4*(V_NUM+1); i++)
			{
				pos[i] = new fk_Vector();
			}

			// 頂点配列データの生成
			for(i = 0; i <= V_NUM; i++)
			{
				double z = i * V_LEN/V_NUM - V_LEN/2.0;
				pos[i*4].Set(10.0, 10.0, z);
				pos[i*4+1].Set(10.0, -10.0, z);
				pos[i*4+2].Set(-10.0, -10.0, z);
				pos[i*4+3].Set(-10.0, 10.0, z);
			}

			// インデックスフェースセット配列の作成
			for(i = 0; i < V_NUM; i++)
			{
				for(j = 0; j < 4; j++)
				{
					index = i*16 + j*4;
					IFSet[index] = 4*i + j;
					IFSet[index+1] = 4*(i+1) + j;
					if(j != 3)
					{
						IFSet[index+2] = 4*(i+1)+j+1;
						IFSet[index+3] = 4*i+j+1;
					}
					else
					{
						IFSet[index+2] = 4*(i+1);
						IFSet[index+3] = 4*i;
					}
				}
			}

			// 立体形状生成
			ifs.MakeIFSet(4*V_NUM, 4, IFSet, 4*(V_NUM+1), pos);

			// ビューワーの設定
			viewer.SetShape(0, ifs);
			viewer.Scale = 10.0;
            viewer.FPS = 60;
            fk_Material.InitDefault();
            var material = new fk_Material(fk_Material.Yellow);
            material.Specular = new fk_Color(0.0, 0.0, 0.0);
            viewer.SetMaterial(0, material);
            viewer.DrawMode = fk_Draw.LINE| fk_Draw.FACE;

			// 表示処理
			while(viewer.Draw() == true)
			{
			}
        }
    }
}
