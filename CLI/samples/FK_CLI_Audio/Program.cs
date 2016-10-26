using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using FK_CLI;

namespace FK_CLI_Audio
{
	// BGM用クラス
	class MyBGM : IDisposable
	{
		public bool EndStatus { get; set; }	// 終了指示用プロパティ
		private fk_AudioStream bgm;
		private bool openStatus;

		// コンストラクタ 引数は音源ファイル名 (Ogg 形式)
		public MyBGM(string argFileName)
		{
			EndStatus = false;
			bgm = new fk_AudioStream();
			openStatus = bgm.Open(argFileName);
			if(openStatus == false)
			{
				Console.WriteLine("Audio File Open Error.");
			}
		}

		// BGM再生処理
		public void Start()
		{
			if(openStatus == false) return;
			bgm.LoopMode = true;
			bgm.Gain = 0.5;
			while(EndStatus == false)
			{
				bgm.Play();
				Thread.Sleep(50);
			}
		}

		// 音量用プロパティ
		public double Gain
		{
			set
			{
				bgm.Gain = value;
			}
		}

		// スレッド終了時処理
		public void Dispose()
		{
			bgm.Dispose();
		}
	}

	// Sound Effect (SE) 用クラス
	class MySE : IDisposable
	{
		public bool EndStatus { get; set; }	// 終了指示用プロパティ
		private fk_AudioWavBuffer [] se;
		private bool [] openStatus;
		private bool [] playStatus;

		// コンストラクタ 引数は音源の個数
		public MySE(int argNum)
		{
			EndStatus = false;
			if(argNum < 1) return;
			se = new fk_AudioWavBuffer [argNum];
			openStatus = new bool [argNum];
			playStatus = new bool [argNum];

			for(int i = 0; i < argNum; i++)
			{
				se[i] = new fk_AudioWavBuffer();
				openStatus[i] = false;
				playStatus[i] = false;
			}
		}

		// SE音源読み込みメソッド (WAV 形式)
		public bool LoadData(int argID, string argFileName)
		{
			if(argID < 0 || argID >= se.Length)
			{
				return false;
			}

			openStatus[argID] = se[argID].Open(argFileName);
			if(openStatus[argID] == false)
			{
				Console.WriteLine("Audio File ({0}) Open Error.", argFileName);
			}
			se[argID].LoopMode = false;
			se[argID].Gain = 0.5;
			return true;
		}

		// SE開始メソッド
		public void StartSE(int argID)
		{
			if(argID < 0 || argID >= se.Length) return;
			playStatus[argID] = true;
			se[argID].Seek(0.0);
		}

		// SE再生処理
		public void Start()
		{
			int i;

			for(i = 0; i < se.Length; i++)
			{
				if(openStatus[i] == false) return;
			}

			while(EndStatus == false)
			{
				for(i = 0; i < se.Length; i++)
				{
					if(playStatus[i] == true)
					{
						playStatus[i] = se[i].Play();
					}
				}
				Thread.Sleep(10);
			}
		}

		// スレッド終了時処理
		public void Dispose()
		{
			for(int i = 0; i < se.Length; i++)
			{
				se[i].Dispose();
			}
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			// 組込マテリアル初期化
			fk_Material.InitDefault();			

			// ウィンドウの各種設定
			var win = new fk_AppWindow();
			win.CameraPos = new fk_Vector(0.0, 1.0, 20.0);
			win.CameraFocus = new fk_Vector(0.0, 1.0, 0.0);
			win.Size = new fk_Dimension(600, 600);
			win.BGColor = new fk_Color(0.6, 0.7, 0.8);
			win.ShowGuide(fk_GuideMode.GRID_XZ);

			// 立方体の各種設定
			var block = new fk_Block(1.0, 1.0, 1.0);
			var blockModel = new fk_Model();
			blockModel.Shape = block;
			blockModel.GlMoveTo(3.0, 3.0, 0.0);
			blockModel.Material = fk_Material.Yellow;
			win.Entry(blockModel);

			// BGMの各種設定
			var bgm = new MyBGM("epoq.ogg");
			var bgmTask = new Task(bgm.Start);
            double volume = 0.5;
            bgm.Gain = volume;
			
			// SEの各種設定
			var se = new MySE(2);
			var seTask = new Task(se.Start);
			se.LoadData(0, "MIDTOM2.wav");
			se.LoadData(1, "SDCRKRM.wav");

			win.Open();
			bgmTask.Start(); // BGM スレッド開始
			seTask.Start();  // SE スレッド開始

			var origin = new fk_Vector(0.0, 0.0, 0.0);

			while(win.Update())
			{
				blockModel.GlRotateWithVec(origin, fk_Axis.Y, FK.PI/360.0);

				// 上矢印キーで BGM 音量アップ
				if(win.GetSpecialKeyStatus(fk_SpecialKey.UP, fk_SwitchStatus.DOWN) == true)
				{
					if(volume < 1.0) volume += 0.1;
				}

				// 下矢印キーで BGM 音量ダウン
				if(win.GetSpecialKeyStatus(fk_SpecialKey.DOWN, fk_SwitchStatus.DOWN) == true)
				{
					if(volume > 0.0) volume -= 0.1;
				}

				// Z キーで 0 番の SE を再生開始
				if(win.GetKeyStatus('Z', fk_SwitchStatus.DOWN) == true)
				{
					se.StartSE(0);
				}

				// X キーで 1 番の SE を再生開始
				if(win.GetKeyStatus('X', fk_SwitchStatus.DOWN) == true)
				{
					se.StartSE(1);
				}

				bgm.Gain = volume;
			}

			// BGM 変数と SE 変数に終了を指示
			bgm.EndStatus = true;
			se.EndStatus = true;

			// BGM, SE 両スレッドが終了するまで待機
			Task.WaitAll(new[] { bgmTask, seTask });
		}
	}
}
