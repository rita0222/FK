using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using FK_CLI;

namespace FK_CLI_Audio
{
	class MyBGM : IDisposable
	{
		public bool endFlg { get; set; }
		private fk_AudioStream bgm;
		private bool openFlg;

		public MyBGM(string argFileName)
		{
			endFlg = false;
			bgm = new fk_AudioStream();
			openFlg = bgm.Open(argFileName);
			if(openFlg == false) {
				Console.WriteLine("Audio File Open Error.");
			}
		}

		public void Start()
		{
			if(openFlg == false) return;
			bgm.LoopMode = true;
			bgm.Gain = 0.5;
			while(endFlg == false) {
				bgm.Play();
				Thread.Sleep(100);
			}
		}

		public double Gain
		{
			set
			{
				bgm.Gain = value;
			}
		}

		public void Dispose()
		{
			bgm.Dispose();
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			var win = new fk_AppWindow();
			var block = new fk_Block(1.0, 1.0, 1.0);
			var blockModel = new fk_Model();
			var origin = new fk_Vector(0.0, 0.0, 0.0);
			var audio = new MyBGM("epoq.ogg");

			double volume = 0.5;

			fk_Material.InitDefault();			
			blockModel.Shape = block;
			blockModel.GlMoveTo(3.0, 3.0, 0.0);
			blockModel.Material = fk_Material.Yellow;
			win.Entry(blockModel);
			win.CameraPos = new fk_Vector(0.0, 1.0, 20.0);
			win.CameraFocus = new fk_Vector(0.0, 1.0, 0.0);
			win.Size = new fk_Dimension(800, 600);
			win.BGColor = new fk_Color(0.6, 0.7, 0.8);
			win.Open();
			win.ShowGuide(fk_GuideMode.GRID_XZ);

			var bgmTask = new Task(audio.Start);
			bgmTask.Start();

			while(win.Update()) {
				blockModel.GlRotateWithVec(origin, fk_Axis.Y, FK.PI/360.0);

				if(win.GetKeyStatus('Z', fk_SwitchStatus.DOWN) == true && volume < 1.0) {
					volume += 0.1;
				}
				if(win.GetKeyStatus('X', fk_SwitchStatus.DOWN) == true && volume > 0.0) {
					volume -= 0.1;
				}

				audio.Gain = volume;
			}
			audio.endFlg = true;
			Task.WaitAll(new[] { bgmTask });
		}
	}
}
