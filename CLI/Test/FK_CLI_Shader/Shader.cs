using System;
using FK_CLI;

namespace FK_CLI_Shader
{
    class Program
    {
        static void Main(string[] args)
        {
            fk_Material.InitDefault();

            var window = new fk_AppWindow();
            window.Size = new fk_Dimension(800, 600);
            window.ClearModel();
            window.SetCameraDefault();
            window.ShowGuide();
            window.TrackBallMode = true;
            window.BGColor = new fk_Color(0.5, 0.5, 0.5);

            var lightModel = new fk_Model();
            var light = new fk_Light();
            lightModel.Shape = light;
            lightModel.Material = fk_Material.TrueWhite;
            lightModel.GlMoveTo(0.0, 0.0, 0.0);
            lightModel.GlFocus(-1.0, -1.0, -1.0);
            window.Entry(lightModel);

            window.Open();
            if (window.Update() == false) return;

            var spBinder = new fk_ShaderBinder();
            var modelDef = new fk_Model();
            var sphere = new fk_Sphere(8, 7.0);
            modelDef.Shape = sphere;
            modelDef.Material = fk_Material.Yellow;
            modelDef.SmoothMode = true;
            modelDef.GlMoveTo(-20.0, 0.0, 0.0);
            spBinder.Program.LoadVertexShader("shader/model_vp.glsl");
            spBinder.Program.LoadFragmentShader("shader/model_fp.glsl");

            if (spBinder.Program.Validate())
            {
                spBinder.BindModel(modelDef);
            }
            else
            {
                Console.WriteLine("Shader Error 1");
            }

            window.Entry(modelDef);

            var ifsBinder = new fk_ShaderBinder();
            var ifsShape = new fk_IFSTexture();
            if (!ifsShape.ReadBMP("mqo/00tex_master.BMP"))
            {
                Console.WriteLine("Tex Load Error");
            }
            if (!ifsShape.ReadMQOFile("mqo/meka.mqo", "body01"))
            {
                Console.WriteLine("IFS Load Error");
            }

            var ifsModelDef = new fk_Model();
            ifsModelDef.Shape = ifsShape;
            ifsModelDef.Material = fk_Material.White;
            ifsModelDef.SmoothMode = true;
            ifsModelDef.GlMoveTo(20.0, 0.0, 0.0);
            ifsBinder.Program.LoadVertexShader("shader/model_vp.glsl");
            ifsBinder.Program.LoadFragmentShader("shader/modelTex_fp.glsl");
            if (ifsBinder.Program.Validate())
            {
                ifsBinder.BindModel(ifsModelDef);
            }
            else
            {
                Console.WriteLine("Shader Error 2");
            }
            window.Entry(ifsModelDef);

            var shockBinder = new fk_ShaderBinder();
            var shockModel = new fk_Model();
            shockModel.Shape = sphere;
            shockModel.Scale = 0.01;
            shockModel.BlendMode = fk_BlendMode.ADDITION_MODE;
            shockBinder.Program.LoadVertexShader("shader/shockSph_vp.glsl");
            shockBinder.Program.LoadFragmentShader("shader/shockSph_fp.glsl");
            if(shockBinder.Program.Validate())
            {
                shockBinder.BindModel(shockModel);
            }
            else
            {
                Console.WriteLine("Shader Error 3");
            }
            window.Entry(shockModel);

            while (window.Update())
            {
                lightModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, 0.01);
                if(window.GetKeyStatus(' ', fk_SwitchStatus.PRESS))
                {
                    shockModel.Scale = shockModel.Scale + 0.01;
                }

                if(window.GetSpecialKeyStatus(fk_SpecialKey.ENTER, fk_SwitchStatus.DOWN))
                {
                    shockModel.Scale = 0.01;
                }
            }
        }
    }
}
