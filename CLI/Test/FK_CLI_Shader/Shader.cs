using System;
using FK_CLI;

namespace FK_CLI_Shader
{
    class Program
    {
        static void Main(string[] args)
        {
            var window = new fk_AppWindow();
            var lightModel = new fk_Model();
            var light = new fk_Light();

            var ifsShape = new fk_IFSTexture();
            var sphere = new fk_Sphere(8, 7.0);

            var modelDef = new fk_Model();
            var ifsModelDef = new fk_Model();
            var shockModel = new fk_Model();

            fk_Material.InitDefault();

            window.Size = new fk_Dimension(800, 600);
            window.ClearModel();
            window.SetCameraDefault();
            window.ShowGuide();
            window.TrackBallMode = true;
            window.BGColor = new fk_Color(0.5, 0.5, 0.5);

            lightModel.Shape = light;
            lightModel.Material = fk_Material.TrueWhite;
            lightModel.GlMoveTo(0.0, 0.0, 0.0);
            lightModel.GlFocus(-1.0, -1.0, -1.0);
            window.Entry(lightModel);

            if(!ifsShape.ReadBMP("mqo/00tex_master.BMP"))
            {
                Console.WriteLine("Tex Load Error");
            }
            if(!ifsShape.ReadMQOFile("mqo/meka.mqo", "body01"))
            {
                Console.WriteLine("IFS Load Error");
            }

            window.Open();
            if (window.Update() == false) return;

            var spBinder = new fk_ShaderBinder();
            modelDef.Shape = sphere;
            modelDef.Material = fk_Material.Yellow;
            modelDef.SmoothMode = true;
            modelDef.GlMoveTo(-20.0, 0.0, 0.0);
            spBinder.Program.LoadVertexShader("shader/model_vp.glsl");
            spBinder.Program.LoadFragmentShader("shader/model_fp.glsl");
            if (spBinder.Program.Validate())
            {
                //spBinder.BindModel(modelDef);
            }
            else
            {
                Console.WriteLine("Shader Error 1");
            }
            window.Entry(modelDef);

            var ifsBinder = new fk_ShaderBinder();
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
                Console.WriteLine("Shader Error 1");
            }
            window.Entry(ifsModelDef);

            while(window.Update())
            {
                lightModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, 0.01);
            }
        }
    }
}
