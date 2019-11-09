using System;
using System.Threading.Tasks;
using System.Threading;
using FK_CLI;

namespace FK_CLI
{
	// BGM用クラス
	public class fk_BGM : IDisposable
	{
        private fk_AudioStream bgm;
        private bool openStatus;
        private Task task;

        public bool StopStatus { get; set; }	// 終了指示用プロパティ

		// コンストラクタ 引数は音源ファイル名 (Ogg 形式)
		public fk_BGM(string argFileName)
		{
			StopStatus = false;
			bgm = new fk_AudioStream();
			openStatus = bgm.Open(argFileName);
			if(openStatus == false) {
				Console.WriteLine("Audio File Open Error.");
			}
            task = new Task(Start_);
		}

        private void Start_()
        {
			if(openStatus == false) return;
			bgm.LoopMode = true;
			bgm.Gain = 0.5;
			while(StopStatus == false) {
				bgm.Play();
				Thread.Sleep(100);
			}
        }

		// BGM再生処理
		public void Start()
		{
            task.Start();
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
            Task.WaitAll(new[] { task });
		}

    }

    // Sound Effect (SE) 用クラス
    public class fk_Sound : IDisposable
	{
        private fk_AudioWavBuffer[] se;
        private bool[] openStatus;
        private bool[] playStatus;
        private Task task;


        public bool StopStatus { get; set; }	// 終了指示用プロパティ

		// コンストラクタ 引数は音源の個数
		public fk_Sound(int argNum)
		{
			StopStatus = false;
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
            task = new Task(Start_);
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
		public void StartSound(int argID)
		{
			if(argID < 0 || argID >= se.Length) return;
			playStatus[argID] = true;
			se[argID].Seek(0.0);
		}

		// SE再生処理
		private void Start_()
		{
			int i;

			for(i = 0; i < se.Length; i++)
			{
				if(openStatus[i] == false) return;
			}

			while(StopStatus == false)
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

        public void Start()
        {
            task.Start();
        }

		// スレッド終了時処理
		public void Dispose()
		{
			for(int i = 0; i < se.Length; i++)
			{
				se[i].Dispose();
			}
            Task.WaitAll(new[] { task });
		}

		public void SetGain(int argID, double argGain)
		{
            if (argID < 0 || argID >= se.Length) return;
            se[argID].Gain = argGain;
        }

        public double GetGain(int argID)
        {
            if (argID < 0 || argID >= se.Length) return -1.0;
            return se[argID].Gain;
        }
    }
}
