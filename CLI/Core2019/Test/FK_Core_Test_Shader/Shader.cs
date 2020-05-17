using System;
using FK_CLI;

namespace FK_Core_Test_Shader
{
    class Program
    {
        static fk_AppWindow SetupWindow()
        {
            var window = new fk_AppWindow();
            window.Size = new fk_Dimension(800, 600);
            window.ClearModel();
            window.SetCameraDefault();
            window.ShowGuide();
            window.TrackBallMode = true;
            window.BGColor = new fk_Color(0.5, 0.5, 0.5);

            return window;
        }

        static fk_Model SetupLight(fk_AppWindow argWin)
        {
            var lightModel = new fk_Model();
            var light = new fk_Light();
            lightModel.Shape = light;
            lightModel.Material = fk_Material.TrueWhite;
            lightModel.GlMoveTo(0.0, 0.0, 0.0);
            lightModel.GlFocus(-1.0, -1.0, -1.0);
            argWin.Entry(lightModel);
            return lightModel;
        }

        static fk_Model SphereSetup(fk_Sphere argSphere)
        {
            var spBinder = new fk_ShaderBinder();
            var model = new fk_Model();
            model.Shape = argSphere;
            model.Material = fk_Material.Yellow;
            model.SmoothMode = true;
            model.GlMoveTo(-20.0, 0.0, 0.0);
            spBinder.Program.LoadVertexShader("shader/model_vp.glsl");
            spBinder.Program.LoadFragmentShader("shader/model_fp.glsl");

            if (spBinder.Program.Validate())
            {
                spBinder.BindModel(model);
            }
            else
            {
                Console.WriteLine("Shader Error 1");
            }

            return model;
        }

        static fk_Model IFSSetup()
        {
            var ifsBinder = new fk_ShaderBinder();
            var ifsShape = new fk_IFSTexture();
            var model = new fk_Model();

            if (!ifsShape.ReadBMP("mqo/00tex_master.BMP"))
            {
                Console.WriteLine("Tex Load Error");
            }
            if (!ifsShape.ReadMQOFile("mqo/meka.mqo", "body01"))
            {
                Console.WriteLine("IFS Load Error");
            }

            model.Shape = ifsShape;
            model.Material = fk_Material.White;
            model.SmoothMode = true;
            model.GlMoveTo(20.0, 0.0, 0.0);
            ifsBinder.Program.LoadVertexShader("shader/model_vp.glsl");
            ifsBinder.Program.LoadFragmentShader("shader/modelTex_fp.glsl");
            if (ifsBinder.Program.Validate())
            {
                ifsBinder.BindModel(model);
            }
            else
            {
                Console.WriteLine("Shader Error 2");
            }

            return model;
        }

        static fk_Model ShockSetup(fk_Sphere argSphere)
        {
            var shockBinder = new fk_ShaderBinder();
            var model = new fk_Model();
            model.Shape = argSphere;
            model.Scale = 0.01;
            model.BlendMode = fk_BlendMode.ADDITION;
            shockBinder.Program.LoadVertexShader("shader/shockSph_vp.glsl");
            shockBinder.Program.LoadFragmentShader("shader/shockSph_fp.glsl");
            if (shockBinder.Program.Validate())
            {
                shockBinder.BindModel(model);
            }
            else
            {
                Console.WriteLine("Shader Error 3");
            }

            return model;
        }

        static void Main(string[] args)
        {
            var window = SetupWindow();
            var lightModel = SetupLight(window);

            window.Open();
            if (window.Update() == false) return;

            var sphere = new fk_Sphere(8, 7.0);

            window.Entry(SphereSetup(sphere));
            window.Entry(IFSSetup());

            var shockModel = ShockSetup(sphere);
            window.Entry(shockModel);

            while (window.Update())
            {
                lightModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, 0.01);
                if(window.GetKeyStatus(' ', fk_Switch.PRESS))
                {
                    shockModel.Scale = shockModel.Scale + 0.01;
                }

                if(window.GetSpecialKeyStatus(fk_Key.ENTER, fk_Switch.DOWN))
                {
                    shockModel.Scale = 0.01;
                }
            }
        }
    }
}
