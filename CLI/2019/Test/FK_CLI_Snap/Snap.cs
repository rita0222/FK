using System;
using FK_CLI;

namespace FK_CLI_Snap
{
    class Snap
    {
        static void Main(string[] args)
        {
            if(args.Length != 1)
            {
                Console.WriteLine("Max Num Input Error. Please Type Any Key.");
                Console.ReadKey();
                return;
            }

            uint max = uint.Parse(args[0]);
            if(max > 100)
            {
                Console.WriteLine("Number Error. Please Type Any Key.");
                Console.ReadKey();
                return;
            }

            var block = new fk_Block(10.0, 20.0, 15.0);
            var model = new fk_Model();
            var window = new fk_AppWindow();

            // 色パレットの初期化
            fk_Material.InitDefault();

            // モデルに直方体を設定
            model.Shape = block;

            // モデルの色を黄色に設定
            model.Material = fk_Material.Yellow;

            // カメラの位置と方向を設定
            window.CameraPos = new fk_Vector(0.0, 0.0, 100.0);
            window.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);

            // ウィンドウにモデルを設定
            window.Entry(model);

            // ウィンドウのサイズを設定
            window.Size = new fk_Dimension(600, 600);
            window.FPS = 60;

            // ウィンドウを開く
            window.Open();

            int num = 0;
            for(int count = 0; window.Update(); count++)
            {
                // 直方体を Y 軸を中心に回転させる。
                model.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, Math.PI / 500.0);

                if(count % 10 == 0)
                {
                    window.SnapImage("image" + num.ToString("000") + ".bmp");
                    num++;
                    if (num == max) return;
                }
            }
        }
    }
}
