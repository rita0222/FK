using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;
using FK_ShaderPlugin;

namespace Sample08_04
{
    class Program
    {
        static void Main(string[] args)
        {
            fk_Material.InitDefault();

			var camera = new fk_Model();
			camera.GlMoveTo(100.0, 100.0, 100.0);
			camera.GlFocus(0.0, 0.0, 0.0);
			camera.GlUpvec(0.0, 1.0, 0.0);

            var winSize = new fk_Dimension(800, 600);
            var window = new fk_AppWindow();
            window.ClearModel();
            window.CameraModel = camera;
            window.Size = winSize;
            window.BGColor = new fk_Color(0.5, 0.5, 0.5);
            window.ShowGuide();
            window.Open();

            var light = new fk_Light();
            var lightModel = new fk_Model();
            lightModel.Shape = light;
            lightModel.Material = fk_Material.TrueWhite;
            lightModel.GlMoveTo(0.0, 0.0, 0.0);
            lightModel.GlFocus(-1.0, -1.0, -1.0);
            window.Entry(lightModel);

            var ifsShape = new fk_IFSTexture();
            if (!ifsShape.ReadBMP("mqo/00tex_master.BMP"))
            {
                Console.WriteLine("MQO Texture Error.");
            }
            if (!ifsShape.ReadMQOFile("mqo/meka.mqo", "body01"))
            {
                Console.WriteLine("MQO Mesh Error.");
            }
            ifsShape.RendMode = fk_TexRendMode.SMOOTH;

            var ifsModel = new fk_Model();
            ifsModel.Shape = ifsShape;
            ifsModel.Material = fk_Material.White;
            ifsModel.GlMoveTo(20.0, 0.0, 0.0);
            window.Entry(ifsModel);

            var sph = new fk_Sphere(16, 7.0);
            var sphModel = new fk_Model();
            sphModel.Shape = sph;
            sphModel.Material = fk_Material.Yellow;
            sphModel.SmoothMode = true;
            sphModel.GlMoveTo(-20.0, 0.0, 0.0);
            window.Entry(sphModel);

            var origin = new fk_Vector();
#if false
			var proj = new fk_Perspective();
			var bgImage = new fk_Image(1024, 768);
            var bgTexture = new fk_MeshTexture(bgImage);
            double tan = Math.Tan(Math.PI / 9.0);// * 2.0;
			double aspect = (double)bgImage.Size.w / (double)bgImage.Size.h;
            bgTexture.TriNum = 1;
            bgTexture.SetVertexPos(0, 0, new fk_Vector(-tan * aspect, -tan, 0.0));
            bgTexture.SetVertexPos(0, 1, new fk_Vector( tan * aspect, tan, 0.0));
            bgTexture.SetVertexPos(0, 2, new fk_Vector(-tan * aspect, tan, 0.0));
            bgTexture.SetTextureCoord(0, 0, new fk_TexCoord(0.0, 0.0));
            bgTexture.SetTextureCoord(0, 1, new fk_TexCoord(1.0, 1.0));
            bgTexture.SetTextureCoord(0, 2, new fk_TexCoord(0.0, 1.0));

            var bgModel = new fk_Model();
			bgModel.Shape = bgTexture;
			bgModel.Parent = camera;
			bgModel.GlMoveTo(0.0, 0.0, -1.0);
			window.Scene.EntryOverlayModel(bgModel);

			var bgSampler = new fk_TextureSampler(bgImage);
			bgSampler.WrapMode = fk_TexWrapMode.CLAMP;
			bgSampler.RendMode = fk_TexRendMode.SMOOTH;
			bgSampler.SamplerSource = fk_SamplerSource.COLOR_BUFFER;
#endif  // ShaderBinder内の処理でこれらを吸収

            double thresshold = 0.2;

            if (window.Update() == false) return;
			var sphBinder = new fk_ShaderBinder();
			sphBinder.Program.LoadVertexShader("shader/model_vp.glsl");
			sphBinder.Program.LoadFragmentShader("shader/model_fp.glsl");

			if(sphBinder.Program.Validate())
			{
				sphBinder.BindModel(sphModel);
			}
			else
			{
				Console.WriteLine(sphBinder.Program.LastError);
			}

			var ifsBinder = new fk_ShaderBinder();
			ifsBinder.Program.LoadVertexShader("shader/model_vp.glsl");
			ifsBinder.Program.LoadFragmentShader("shader/modelTex_fp.glsl");
			if(ifsBinder.Program.Validate())
			{
				ifsBinder.BindModel(ifsModel);
			}
			else
			{
				Console.WriteLine(ifsBinder.Program.LastError);
			}

			var bgBinder = new fk_ShaderBinder();
			bgBinder.Program.LoadVertexShader("shader/fbo_vp.glsl");
			bgBinder.Program.LoadFragmentShader("shader/fbo_fp.glsl");
			if(bgBinder.Program.Validate())
			{
                // bgBinder.Parameter.AttachTexture(1, bgSampler);
                bgBinder.InitializeFrameBufferObject(winSize);    // ↑と置き換え
				bgBinder.Parameter.Register("tex0", 0); // 1->0
                bgBinder.Parameter.Register("Width", 1024.0f);
                bgBinder.Parameter.Register("Height", 768.0f);
                bgBinder.Parameter.Register("Thresshold", (float)thresshold);
                // bgBinder.BindModel(bgModel);
                bgBinder.BindWindow(window); // ↑と置き換え
			}
			else
			{
				Console.WriteLine(bgBinder.Program.LastError);
			}

            while (window.Update() == true)
			{
                lightModel.GlRotateWithVec(origin, fk_Axis.Y, 0.02);
                camera.GlRotateWithVec(origin, fk_Axis.Y, -0.003);

                if(window.GetSpecialKeyStatus(fk_SpecialKey.UP, fk_SwitchStatus.PRESS))
                {
                    thresshold += 0.01;
                    Console.WriteLine(thresshold);
                }
                if(window.GetSpecialKeyStatus(fk_SpecialKey.DOWN, fk_SwitchStatus.PRESS))
                {
                    thresshold -= 0.01;
                    if(thresshold < 0.0)
                    {
                        thresshold = 0.0;
                    }
                    Console.WriteLine(thresshold);
                }
                bgBinder.Parameter.Register("Thresshold", (float)thresshold);
            }
        }
    }
}
