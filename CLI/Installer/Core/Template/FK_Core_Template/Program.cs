using System;
using FK_CLI;

namespace FK_Core_Template
{
    class Program
    {
        static void Main(string[] args)
        {
            var block = new fk_Block(10.0, 20.0, 15.0);
            var model = new fk_Model();
            var window = new fk_AppWindow();

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

            // ウィンドウを開く
            window.Open();

            while (window.Update() == true)
            {
                // 直方体を Y 軸を中心に回転させる。
                model.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, Math.PI / 500.0);
            }
        }
    }
}
