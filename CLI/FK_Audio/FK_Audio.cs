/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/
// FK_Audio.cs

using System;
using System.Threading.Tasks;
using System.Threading;

namespace FK_CLI
{
	//! BGM 再生クラス
    /*!
	 *	このクラスは、BGM (Back Ground Music) を再生する機能を提供します。
	 *	同様の目的を持つクラスとして fk_AudioStream がありますが、
	 *	この fk_BGM の方がより容易に用いることができます。
	 *
	 *	本クラスは、内部で fk_AudioStream を用いており、
	 *	音楽再生専用のスレッドを生成してストリーミング再生を行います。
	 *	そのため、再生の即応性が求められる効果音には向いていません。
	 *	効果音再生には fk_Sound を用いて下さい。
	 *
	 *	\sa fk_Sound, fk_AudioStream, fk_AudioBase
     */
	public class fk_BGM : IDisposable
	{
        private fk_AudioStream bgm;
        private bool openStatus;
        private Task task;

		//! コンストラクタ
		/*!
		 *	\param[in] argFileName
		 *		音源ファイル名。Ogg 形式の音源データである必要があります。
		 *		入力に失敗した場合、コンソールに「Audio File Open Error.」
		 *		というエラーメッセージが出力されます。
		 *
		 *		なお、インスタンス生成時はまだ再生は開始しません。
		 *		再生を開始するのは Start() メソッドを実行する必要があります。
		 */
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

		//! BGM 再生開始メソッド
		/*!
		 *	BGM の再生を開始します。
		 */
		public void Start()
		{
            task.Start();
        }

		//! 終了指示用プロパティ
		/*!
		 *	BGM 再生を終了したいタイミングで、このプロパティに true を代入します。
		 *	false を代入しても、即財には終了せずわずかなタイムラグがあることに注意して下さい。
		 */
        public bool StopStatus { get; set; }	// 終了指示用プロパティ


        //! 音量プロパティ
		/*!
		 *	音量設定を行うプロパティです。
		 *	1.0 が最大で、0.0 で無音状態となります。
		 *	なお、初期値は 0.5 となっています。
		 */
        public double Gain
		{
			set
			{
				bgm.Gain = value;
			}
		}

#if (!FK_DOXYGEN_USER_PROCESS)		

		public void Dispose()
		{
			bgm.Dispose();
            Task.WaitAll(new[] { task });
		}

#endif
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
    }

	//! 効果音再生クラス
    /*!
	 *	このクラスは、効果音 (Sound Effect, SE) を再生する機能を提供します。
	 *	同様の目的を持つクラスとして fk_AudioOggBuffer や fk_AudioWavBuffer がありますが、
	 *	この fk_Sound の方がより容易に用いることができます。
	 *
	 *	本クラスは、内部で fk_WavBuffer を用いており、
	 *	効果音再生専用のスレッドを生成して音源データを全てメモリ上に保存します。
	 *	そのため、長時間の再生を行う BGM には向いていません。
	 *	BGM 再生には fk_BGM を用いて下さい。
	 *
	 *	\sa fk_BGM, fk_AudioWavBuffer, fk_AudioOggBuffer, fk_AudioBase
     */
    public class fk_Sound : IDisposable
	{
        private fk_AudioWavBuffer[] se;
        private bool[] openStatus;
        private bool[] playStatus;
        private Task task;


		//! コンストラクタ
		/*!
		 *	\param[in] argNum
		 *		効果音の個数を設定します。
		 */
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

		//! 効果音源読み込みメソッド
		/*!
		 *	効果音の音源データファイルを設定し、読み込みを行います。
		 *	音源データは WAV 形式である必要があります。
		 *
		 *	\param[in]	argID
		 *		音源に割り当てる ID。
		 *		0 から(コンストラクタで設定した個数 - 1) のいずれかである必要があります。
		 *
		 *	\param[in]	argFileName		音源ファイル名。WAV 形式である必要があります。
		 *
		 *	\return		入力に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa StartSound(), Start()
		 */
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
				return false;
			}
			se[argID].LoopMode = false;
			se[argID].Gain = 0.5;
			return true;
		}

		//!	再生準備メソッド
		/*!
		 *	効果音再生の準備を行います。
		 *	このメソッドを実行しないと、 StartSound() を実行しても再生されません。
		 *
		 *	\sa StartSound()
		 */
        public void Start()
        {
            task.Start();
        }

		//! 再生開始メソッド
		/*!
		 *	効果音の再生を開始します。
		 *	現在再生中の効果音についても、
		 *	本メソッドを実行することにより「頭出し再生」を行います。
		 *
		 *	\param[in]	argID	効果音の ID
		 */
		public void StartSound(int argID)
		{
			if(argID < 0 || argID >= se.Length) return;
			playStatus[argID] = true;
			se[argID].Seek(0.0);
		}

		//!	音量設定メソッド
		/*!
		 *	各効果音ごとに音量を設定します。
		 *	最大が 1.0 で、0.0 で無音となります。
		 *	なお、初期値は 0.5 となっています。
		 *
		 *	\param[in]	argID	効果音ID
		 *	\param[in]	argGain	音量
		 */
		public void SetGain(int argID, double argGain)
		{
            if (argID < 0 || argID >= se.Length) return;
            se[argID].Gain = argGain;
        }

		//!	音量参照メソッド
		/*!
		 *	各効果音ごとに音量を参照します。
		 *	最大が 1.0 で、0.0 で無音となります。
		 *
		 *	\param[in]	argID	効果音ID
		 *
		 *	\return		音量値
		 */
        public double GetGain(int argID)
        {
            if (argID < 0 || argID >= se.Length) return -1.0;
            return se[argID].Gain;
        }

		//! 終了指示用プロパティ
		/*!
		 *	効果音再生を終了したいタイミングで、このプロパティに true を代入します。
		 *	false を代入しても、即財には終了せずわずかなタイムラグがあることに注意して下さい。
		 */
        public bool StopStatus { get; set; }


#if (!FK_DOXYGEN_USER_PROCESS)

		public void Dispose()
		{
			for(int i = 0; i < se.Length; i++)
			{
				se[i].Dispose();
			}
            Task.WaitAll(new[] { task });
		}

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
#endif

    }
}
