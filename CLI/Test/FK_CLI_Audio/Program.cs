using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using FK_CLI;

namespace FK_CLI_Audio
{
	class MyBGM
	{
		public bool endFlg;
		private fk_AudioStream bgm;

		public MyBGM()
		{
			endFlg = false;
			bgm = new fk_AudioStream();
			if(bgm.open("epoq.ogg") == false) {
				Console.WriteLine("Audio File Open Error.");
			}
		}

		public void start()
		{
			bgm.setLoopMode(true);
			bgm.setGain(0.5);
			while(endFlg == false) {
				bgm.play();
				Thread.Sleep(100);
			}
		}

		public void setGain(double argVolume)
		{
			bgm.setGain(argVolume);
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
			var audio = new MyBGM();

			double volume = 0.5;

			fk_Material.initDefault();			
			blockModel.setShape(block);
			blockModel.glMoveTo(3.0, 3.0, 0.0);
			blockModel.setMaterial(fk_Material.Yellow);
			win.entry(blockModel);
			win.setCameraPos(0.0, 1.0, 20.0);
			win.setCameraFocus(0.0, 1.0, 0.0);
			win.setSize(800, 600);
			win.setBGColor(0.6, 0.7, 0.8);
			win.open();
			win.showGuide(fk_GuideMode.GRID_XZ);

			var bgmTask = new Task(audio.start);
			bgmTask.Start();

			while(win.update()) {
				blockModel.glRotateWithVec(origin, fk_Axis.Y, FK.PI/360.0);

				if(win.getKeyStatus('Z', fk_SwitchStatus.DOWN) == true && volume < 1.0) {
					volume += 0.1;
				}
				if(win.getKeyStatus('X', fk_SwitchStatus.DOWN) == true && volume > 0.0) {
					volume -= 0.1;
				}

				audio.setGain(volume);
			}
			audio.endFlg = true;
			Task.WaitAll(new[] { bgmTask });
		}
	}
}
