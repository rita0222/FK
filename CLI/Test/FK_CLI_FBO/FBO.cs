using System;
using FK_CLI;

namespace FK_CLI_FBO
{
    class FBO
    {
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
            var mat = new fk_Material();
            var window = new fk_AppWindow();
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
            window.BGColor = new fk_Color(0.5, 0.5, 0.5);
            window.Entry(lightModel);
            window.Entry(modelDef);
            window.Entry(ifsModelDef);

            // 視点の位置と姿勢を設定
            window.CameraPos = new fk_Vector(0.0, 0.0, 100.0);
            window.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
            window.Entry(sprite);

            // ウィンドウ生成 (シェーダー設定の前に行う必要がある。)
            window.Open();
            window.TrackBallMode = true;

            // 各種シェーダー設定
            ShaderSetup(spBinder, modelDef, fk_Material.Yellow,
                new fk_Vector(-20.0, 0.0, 0.0), "shader/model_vp.glsl", "shader/model_fp.glsl");

            ShaderSetup(ifsBinder, ifsModelDef, fk_Material.White,
                new fk_Vector(20.0, 0.0, 0.0), "shader/model_vp.glsl", "shader/modelTex_fp.glsl");

            FBOSetup(edgeBinder, window, (float)thresshold / 100.0f, "shader/fbo_edge.glsl");

            //FBOSetup(depthBinder, window, 0.0f, "shader/fbo_depth.glsl");

            while(window.Update())
            {
                // エッジ抽出用閾値の変更
                if (window.GetSpecialKeyStatus(fk_SpecialKey.UP, fk_SwitchStatus.PRESS))
                {
                    ++thresshold;
                }
                if (window.GetSpecialKeyStatus(fk_SpecialKey.DOWN, fk_SwitchStatus.PRESS))
                {
                    if (thresshold > 0) --thresshold;
                }

                // FBOシェーダーに閾値を送信
                edgeBinder.Parameter.Register("Thresshold", (float)thresshold / 100.0f);

                // 光源回転
                lightModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, 0.05);

                sprite.DrawText(((double)thresshold / 100.0).ToString(), true);
                sprite.SetPositionLT(SP_X, SP_Y);
            }
        }
    }
}