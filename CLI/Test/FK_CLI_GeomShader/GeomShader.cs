using System;
using FK_CLI;

namespace FK_CLI_GeomShader
{
    class GeomShader
    {
        static void Main(string[] args)
        {
            fk_Material.InitDefault();

            // ウィンドウ生成
            var window = new fk_AppWindow();
            window.Size = new fk_Dimension(600, 600);
            window.CameraPos = new fk_Vector(0.0, 0.0, 500.0);
            window.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);

            // 直方体モデル生成
            var blockModel = new fk_Model();
            var block = new fk_Block(50.0, 70.0, 40.0);
            blockModel.Shape = block;
            blockModel.Material = fk_Material.Yellow;
            window.Entry(blockModel);
            window.Open();

            while (window.Update())
            {
                blockModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, Math.PI / 300.0);
            }
        }
    }
}