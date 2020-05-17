using System;
using FK_CLI;

namespace FK_Core_Test_Snap
{
    class Snap
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("Usage: {0} angle", Environment.GetCommandLineArgs()[0]);
                Console.WriteLine("Please Type Any Key.");
                Console.ReadKey();
                return;
            }

            int angle = int.Parse(args[0]);

            var block = new fk_Block(10.0, 20.0, 15.0);
            var model = new fk_Model();
            var window = new fk_AppWindow();

            // モデルに直方体を設定
            model.Shape = block;

            // モデルの色を黄色に設定
            model.Material = fk_Material.Yellow;
            model.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, angle * Math.PI / 180.0);

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

            window.Update();
            window.SnapImage("image" + angle.ToString("0000") + ".png", fk_ImageType.PNG);
        }
    }
}
