using System;
using FK_CLI;

namespace FK_CLI_FBO
{
    class FBO
    {
        static int MODE;
        const int WIN_W = 512;
        const int WIN_H = 512;
        const double SP_X = -((double)(WIN_W/2) - 10.0);
        const double SP_Y = (double)(WIN_H/2) - 10.0;

        static void ShaderSetup(fk_ShaderBinder argBinder, fk_Model argModel, fk_Material argMat,
            fk_Vector argPos, string argVP, string argFP)
        {
            argModel.Material = argMat;
            argModel.SmoothMode = true;
            argModel.GlMoveTo(argPos);
            argBinder.Program.LoadVertexShader(argVP);
            argBinder.Program.LoadFragmentShader(argFP);
            if(argBinder.Program.Validate())
            {
                argBinder.BindModel(argModel);
            } else {
                Console.WriteLine("Shader Error (Original Side)");
                Console.WriteLine(argBinder.Program.LastError);
            }
        }

        // FBOシェーダー設定
        static void FBOSetup(fk_ShaderBinder argBinder, fk_AppWindow argWindow,
            float argTH, string argFP)
        {
            var prog = argBinder.Program;

            argBinder.InitializeFrameBufferObject(WIN_W, WIN_H);
            prog.LoadFragmentShader(argFP);
            if (prog.Validate())
            {
                argBinder.Parameter.Register("Thresshold", argTH);
                argBinder.BindWindow(argWindow);
            }
            else
            {
                Console.WriteLine("Shader Error (FBO Side)");
                Console.WriteLine(prog.LastError);
            }
        }

        static void Main(string[] args)
        {
            // 1: カラーバッファからのエッジ抽出
            // 2: デプスマップ
            MODE = 2;

            var mat = new fk_Material();
            var normalWindow = new fk_AppWindow();
            var edgeWindow = new fk_AppWindow();
            var depthWindow = new fk_AppWindow();
            var lightModel = new fk_Model();
            var light = new fk_Light();

            var ifsShape = new fk_IFSTexture();
            var sphere = new fk_Sphere(8, 7.0);
            var sprite = new fk_SpriteModel();

            var modelDef = new fk_Model();
            var ifsModelDef = new fk_Model();

            var spBinder = new fk_ShaderBinder();
            var ifsBinder = new fk_ShaderBinder();
            var edgeBinder = new fk_ShaderBinder();
            var depthBinder = new fk_ShaderBinder();
            int thresshold = 80;

            fk_Material.InitDefault();

            // 照明の設定
            lightModel.Shape = light;
            lightModel.Material = fk_Material.TrueWhite;
            lightModel.GlMoveTo(0.0, 0.0, 0.0);
            lightModel.GlFocus(-1.0, -1.0, -1.0);

            // 球と読み込みデータの設定
            if (ifsShape.ReadBMP("mqo/00tex_master.BMP") == false)
            {
                Console.WriteLine("tex load err");
            }

            if (ifsShape.ReadMQOFile("mqo/meka.mqo", "body01") == false)
            {
                Console.WriteLine("ifs load err");
            }
            ifsShape.RendMode = fk_TexRendMode.SMOOTH;
            modelDef.Shape = sphere;
            ifsModelDef.Shape = ifsShape;

            // スプライト設定

            if (sprite.InitFont("rm1b.ttf") == false)
            {
                Console.WriteLine("Font Init Error");
            }
            sprite.SetPositionLT(SP_X, SP_Y);

            // 各モデルをディスプレイリストに登録
            normalWindow.BGColor = new fk_Color(0.5, 0.5, 0.5);
            normalWindow.Entry(lightModel);
            normalWindow.Entry(modelDef);
            normalWindow.Entry(ifsModelDef);

            // 視点の位置と姿勢を設定
            normalWindow.CameraPos = new fk_Vector(0.0, 0.0, 100.0);
            normalWindow.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
            normalWindow.Entry(sprite);

            // ウィンドウ生成 (シェーダー設定の前に行う必要がある。)
            normalWindow.Open();
            normalWindow.TrackBallMode = true;
            normalWindow.ShowGuide();

            edgeWindow.Scene = normalWindow.Scene;
            depthWindow.Scene = normalWindow.Scene;

            if(MODE == 1)
            {
                edgeWindow.Open();
            } else
            {
                depthWindow.Open();
            }

            // 各種シェーダー設定
            ShaderSetup(spBinder, modelDef, fk_Material.Yellow,
                new fk_Vector(-20.0, 0.0, 0.0), "shader/model_vp.glsl", "shader/model_fp.glsl");

            ShaderSetup(ifsBinder, ifsModelDef, fk_Material.White,
                new fk_Vector(20.0, 0.0, 0.0), "shader/model_vp.glsl", "shader/modelTex_fp.glsl");

            FBOSetup(edgeBinder, edgeWindow, (float)thresshold / 100.0f, "shader/fbo_edge.glsl");
            FBOSetup(depthBinder, depthWindow, 0.0f, "shader/fbo_depth.glsl");

            while(normalWindow.Update())
            {
                if (MODE == 1)
                {
                    if (edgeWindow.Update() == false) break;
                } else
                {
                    if (depthWindow.Update() == false) break;
                }
                // エッジ抽出用閾値の変更
                if (normalWindow.GetSpecialKeyStatus(fk_SpecialKey.UP, fk_Switch.PRESS))
                {
                    ++thresshold;
                }
                if (normalWindow.GetSpecialKeyStatus(fk_SpecialKey.DOWN, fk_Switch.PRESS))
                {
                    if (thresshold > 0) --thresshold;
                }

                // FBOシェーダーに閾値を送信
                edgeBinder.Parameter.Register("Thresshold", (float)thresshold / 100.0f);

                // 光源回転
                lightModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, 0.05);

                string outStr = string.Format("{0:0.00}", (double)thresshold / 100.0);
                sprite.DrawText(outStr, true);
                sprite.SetPositionLT(SP_X, SP_Y);
            }
        }
    }
}