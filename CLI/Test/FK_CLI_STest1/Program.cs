using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;
//using FK_ShaderPlugin;

namespace FK_CLI_Box
{
	class Program
	{
		static void Main(string[] args)
		{
			int i;

			// ウィンドウ生成
			var win = new fk_AppWindow();
			win.Size = new fk_Dimension(1024, 768);
			fk_Material.InitDefault();
			win.BGColor = new fk_Color(0.5, 0.5, 0.5);

			// 光源生成
			var light = new fk_Light();
			var lightModel = new fk_Model();
			lightModel.Material = fk_Material.TrueWhite;
			lightModel.GlMoveTo(0.0, 0.0, 0.0);
			lightModel.GlFocus(-1.0, -1.0, -1.0);
			win.Entry(lightModel);

			// 直方体モデル生成
			var blockModel = new fk_Model();
			var block = new fk_Block(50.0, 70.0, 40.0);
			blockModel.Shape = block;
			blockModel.Material = fk_Material.Yellow;
			blockModel.SmoothMode = true;
			win.Entry(blockModel);

			// 線分モデル生成
			fk_Vector[] pos = new fk_Vector[4];
			pos[0] = new fk_Vector(0.0, 100.0, 0.0);
			pos[1] = new fk_Vector(100.0, 0.0, 0.0);
			pos[2] = -pos[0];
			pos[3] = -pos[1];
			fk_Line[] line = new fk_Line[2];
			fk_Model[] lineModel = new fk_Model[2];
			for(i = 0; i < 2; i++) {
				line[i] = new fk_Line();
				line[i].PushLine(pos[2*i], pos[2*i + 1]);
				lineModel[i] = new fk_Model();
				lineModel[i].Shape = line[i];
				lineModel[i].Parent = blockModel;
				win.Entry(lineModel[i]);
			}

			lineModel[0].LineColor = new fk_Color(1.0, 0.0, 0.0);
			lineModel[1].LineColor = new fk_Color(0.0, 1.0, 0.0);

			// カメラモデル生成
			var camera = new fk_Model();
			camera.GlMoveTo(0.0, 0.0, 2000.0);
			camera.GlFocus(0.0, 0.0, 0.0);
			camera.GlUpvec(0.0, 1.0, 0.0);
			win.CameraModel = camera;
			win.Open();

			var origin = new fk_Vector(0.0, 0.0, 0.0);

			var proj = new fk_Perspective();

			var bgImg = new fk_Image(1024, 768);
			var bg = new fk_RectTexture(bgImg);
			var tan = Math.Tan(Math.PI / 9.0) * 2.0;
			var asp = (float)bgImg.Size.w / (float)bgImg.Size.h;
			bg.TextureSize = new fk_TexCoord(tan * asp, tan);
			var bgModel = new fk_Model();
			bgModel.Shape = bg;
			bgModel.Parent = camera;
			bgModel.GlMoveTo(0.0, 0.0, -1.0);
			win.Entry(bgModel);
			fk_ShaderBinder bgBinder;
			var bgSampler = new fk_TextureSampler(bgImg);
			bgSampler.WrapMode = fk_TexWrapMode.CLAMP;
			bgSampler.RendMode = fk_TexRendMode.SMOOTH;
			bgSampler.SamplerSource = fk_SamplerSource.COLOR_BUFFER;

			fk_ShaderBinder binder;
			var sampler = new fk_TextureSampler();
			if (!sampler.ReadBMP("samp.bmp")) System.Console.WriteLine("failed");
			sampler.WrapMode = fk_TexWrapMode.CLAMP;
			fk_Matrix scaleMatrix = new fk_Matrix();
			scaleMatrix.MakeScale(1.0, 1.0, 1.0);
			var uvArray = new[]
				{
					1.0f, 0.0f,
					0.9f, 0.8f,
					0.0f, 0.7f,
					0.0f, 0.0f,
					1.0f, 0.0f,
					0.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 0.0f,
				};
			if (win.Update())
			{
				binder = new fk_ShaderBinder();
				binder.Program.LoadVertexShader("vs1.glsl");
				binder.Program.LoadFragmentShader("fs1.glsl");
				if (binder.Program.Validate())
				{
					binder.Parameter.AttachTexture(1, sampler);
					binder.Parameter.Register("scale", scaleMatrix);
					binder.Parameter.AddAttribute("vUV", 2, uvArray);
					binder.Parameter.Register("tex", 1);
					binder.BindModel(blockModel);
				}
				else
				{
					System.Console.WriteLine(binder.Program.LastError);
				}

				bgBinder = new fk_ShaderBinder();
				bgBinder.Program.LoadVertexShader("vs2.glsl");
				bgBinder.Program.LoadFragmentShader("fs2.glsl");
				if (bgBinder.Program.Validate())
				{
					bgBinder.Parameter.AttachTexture(1, bgSampler);
					bgBinder.Parameter.Register("tex", 1);
					bgBinder.BindModel(bgModel);
				}
				else
				{
					System.Console.WriteLine(bgBinder.Program.LastError);
				}
			}

			for (i = 0; win.Update() == true; i++) {
				camera.GlTranslate(0.0, 0.0, -1.0);
				blockModel.GlRotateWithVec(origin, fk_Axis.Y, Math.PI/300.0);
				var cPos = camera.Position;
				if(cPos.z < -0.00001) camera.GlFocus(origin);
				if(i >= 1000) camera.LoRotateWithVec(origin, fk_Axis.Z, Math.PI/500.0);

				if(win.GetKeyStatus(' ', fk_SwitchStatus.PRESS))
				{
					win.Remove(bgModel);
				}
				else
				{
					win.Entry(bgModel);
				}
			}
		}
	}
}
