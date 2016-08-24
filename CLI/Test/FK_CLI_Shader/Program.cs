using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;
using FK_ShaderPlugin;

namespace FK_CLI_Box
{
    class Program
	{
		static void Main(string[] args)
		{
			int i;

			// ウィンドウ生成
			var win = new fk_AppWindow();
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

            fk_ShaderBinder binder;
            //fk_TextureSampler sampler = new fk_TextureSampler();
            //if(!sampler.ReadBMP("../../../../../../samples/samp.bmp")) System.Console.WriteLine("failed");
            fk_TextureSampler sampler = new fk_TextureSampler(new fk_Image(512, 512));
            sampler.SamplerSource = fk_SamplerSource.COLOR_BUFFER;
            sampler.WrapMode = fk_TexWrapMode.REPEAT;
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
                binder.Program.VertexShaderSource =
                    "uniform mat4 scale;" +
                    "varying vec4 pos;" +
                    "varying vec2 fUV;" +
                    "attribute vec2 vUV;" +
                    "void main(void)" +
                    "{" +
                    "    gl_Position = gl_ModelViewProjectionMatrix * scale * gl_Vertex;" +
                    "    pos = gl_ModelViewProjectionMatrix * gl_Vertex;" +
                    "    fUV = vUV;" +
                    "}";
                binder.Program.FragmentShaderSource =
                    "uniform sampler2D tex;" +
                    "varying vec4 pos;" +
                    "varying vec2 fUV;" +
                    "void main(void)" +
                    "{" +
                    "    gl_FragColor.rgb = texture2D(tex, fUV).rgb; " +
                    "    gl_FragColor.a = 1.0; " +
                    "}";
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
            }
            win.Scene.EntryModel(blockModel);
            for (i = 0; win.Update() == true; i++) {
				camera.GlTranslate(0.0, 0.0, -1.0);
				blockModel.GlRotateWithVec(origin, fk_Axis.Y, FK.PI/300.0);
				var cPos = camera.Position;
				if(cPos.z < -FK.EPS) camera.GlFocus(origin);
				if(i >= 1000) camera.LoRotateWithVec(origin, fk_Axis.Z, FK.PI/500.0);
			}
		}
	}
}
