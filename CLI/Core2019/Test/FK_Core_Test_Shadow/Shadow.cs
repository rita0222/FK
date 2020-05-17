using System;
using FK_CLI;

namespace FK_Core_Test_Shadow
{
    class Shadow
    {
        static void ModelSetup(fk_Model argModel, fk_Material argMat, fk_Vector argPos)
        {
            argModel.Material = argMat;
            argModel.SmoothMode = true;
            argModel.GlMoveTo(argPos);
        }

        static void BallMove(fk_AppWindow argWindow, fk_Model argModel)
        {
            const double STEP = 0.5;

            if (argWindow.GetSpecialKeyStatus(fk_Key.UP, fk_Switch.PRESS))
            {
                argModel.GlTranslate(0.0, 0.0, -STEP);
            }
            if (argWindow.GetSpecialKeyStatus(fk_Key.DOWN, fk_Switch.PRESS))
            {
                argModel.GlTranslate(0.0, 0.0, STEP);
            }
            if (argWindow.GetSpecialKeyStatus(fk_Key.RIGHT, fk_Switch.PRESS))
            {
                argModel.GlTranslate(STEP, 0.0, 0.0);
            }
            if (argWindow.GetSpecialKeyStatus(fk_Key.LEFT, fk_Switch.PRESS))
            {
                argModel.GlTranslate(-STEP, 0.0, 0.0);
            }
        }

        static void RobotRotate(fk_AppWindow argwindow, fk_Model argModel)
        {
            var origin = new fk_Vector(0.0, 0.0, 0.0);

            if (argwindow.GetKeyStatus('z', fk_Switch.PRESS))
            {
                argModel.LoRotateWithVec(origin, fk_Axis.Y, Math.PI / 60.0);
            }
            if (argwindow.GetKeyStatus('x', fk_Switch.PRESS))
            {
                argModel.LoRotateWithVec(origin, fk_Axis.Y, -Math.PI / 60.0);
            }
        }

        static void ShadowVecChange(int argCount, fk_AppWindow argWindow)
        {
            var rotMat = new fk_Matrix();
            rotMat.MakeRot((double)argCount / 100.0, fk_Axis.Y);
            var vec = rotMat * (new fk_Vector(1.0, -1.0, 0.0));
            argWindow.ShadowVec = vec;
            argWindow.DefaultLightVec = vec;
        }

        static void ShadowChange(fk_AppWindow argWindow, fk_Model argModel, char argC1, char argC2)
        {
            if(argWindow.GetKeyStatus(argC1, fk_Switch.DOWN))
            {
                argModel.ShadowEffect = (argModel.ShadowEffect ? false : true);
            }
            if(argWindow.GetKeyStatus(argC2, fk_Switch.DOWN))
            {
                argModel.ShadowDraw = (argModel.ShadowDraw ? false : true);
            }
        }

        static void Main(string[] args)
        {
            var window = new fk_AppWindow();
            var bgColor = new fk_Color(0.5, 0.5, 0.5);

            window.Size = new fk_Dimension(800, 800);
            window.TrackBallMode = true;
            window.ShowGuide();
            window.CameraPos = new fk_Vector(0.0, 50.0, 200.0);
            window.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
            window.DefaultLightVec = new fk_Vector(1.0, -1.0, 1.0);
            window.DefaultLightMaterial = fk_Material.WhiteLight;
            window.BGColor = bgColor;
            window.FPS = 60;

            var ifsShape = new fk_IFSTexture();
            if (ifsShape.ReadBMP("00tex_master.BMP") == false)
            {
                Console.WriteLine("Image Read Error");
            }

            if (ifsShape.ReadMQOFile("meka.mqo", "body01") == false)
            {
                Console.WriteLine("ifs load err");
            }

            var sph = new fk_Sphere(8, 7.0);
            var floor = new fk_Block(200.0, 2.0, 200.0);
            var spModel = new fk_Model();
            var ifsModel = new fk_Model();
            var floorModel = new fk_Model();

            spModel.Shape = sph;
            ifsModel.Shape = ifsShape;
            floorModel.Shape = floor;

            // 各モデルをディスプレイリストに登録
            window.Entry(floorModel);
            window.Entry(spModel);
            window.Entry(ifsModel);

            //window.ShadowMode = fk_ShadowMode.OFF;
            //window.ShadowMode = fk_ShadowMode.HARD;
            //window.ShadowMode = fk_ShadowMode.SOFT_FAST;
            window.ShadowMode = fk_ShadowMode.SOFT_NICE;
            window.ShadowVec = new fk_Vector(1.0, -1.0, 1.0);
            window.ShadowAreaSize = 500.0;
            window.ShadowDistance = 300.0;
            window.ShadowResolution = 1024;
            window.ShadowVisibility = 0.9;
            window.ShadowBias = 0.01;

            ModelSetup(spModel, fk_Material.Yellow, new fk_Vector(-20.0, 20.0, 0.0));
            ModelSetup(ifsModel, fk_Material.White, new fk_Vector(20.0, 5.0, 0.0));
            ModelSetup(floorModel, fk_Material.White, new fk_Vector(0.0, -1.0, 0.0));

            window.Open();

            Console.WriteLine("1 : 球影効果 ON/OFF");
            Console.WriteLine("2 : 球影描画 ON/OFF");
            Console.WriteLine("3 : ロボット影効果 ON/OFF");
            Console.WriteLine("4 : ロボット影描画 ON/OFF");
            Console.WriteLine("z : ロボット 反時計回り回転");
            Console.WriteLine("x : ロボット 時計回り回転");
            Console.WriteLine("矢印 : 球移動");

            for (int count = 0;  window.Update(); count++)
            {
                BallMove(window, spModel);
                RobotRotate(window, ifsModel);
                ShadowVecChange(count, window);
                ShadowChange(window, spModel, '1', '2');
                ShadowChange(window, ifsModel, '3', '4');
            }
        }
    }
}
