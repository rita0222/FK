// AudioBase_CLI.h

#pragma once

#include <FK/Audio.h>
#include "Model_CLI.h"

namespace FK_CLI
{
	//! オーディオ基底クラス
	/*!
	 *	このクラスは、FKが提供するオーディオクラスの基底クラスとなっています。
	 *	オーディオ全般で共通して利用するクラスメソッドを実装しています。
	 *	FKでは、オーディオシステムとして OpenAL を採用しています。
	 *	(OpenAL は FK のインストール時に自動的にインストールされます。)
	 *
	 *	このクラスの派生クラスによるインスタンスは、
	 *	音声再生を制御するための基本的な機能となる再生、
	 *	停止、繰り返し再生、音量調整を制御できます。
	 *
	 *	加えて、サラウンド(立体音響)を利用することもできます。
	 *	サラウンド機能においては、
	 *	各音源自体の3次元空間での位置を fk_Model と同期を取ることで実現します。
	 *	そのため、FK の 3D プログラムと高い親和性を持ちます。
	 *	また、3Dグラフィックスにおける「カメラ」に相当するような、
	 *	自分自身を指す言葉を「リスナー」と呼びます。
	 *	リスナーも fk_Model と同期を取ることができます。
	 *
	 *	\sa fk_AudioStream, fk_AudioOggBuffer, fk_AudioWavBuffer, fk_Model
	 */
	public ref class fk_AudioBase abstract {
	internal:
		::FK::fk_AudioBase *pAudio;
		bool dFlg;

		::FK::fk_AudioBase * GetP(void);

	public:
		//! コンストラクタ
		fk_AudioBase();

		//! デストラクタ
		~fk_AudioBase();

		//! ファイナライザ
		!fk_AudioBase();

		//! 音量プロパティ
		/*!
		 *	音量(減衰率)の参照や設定を行います。
		 *	0 で無音、1 で最大音量となります。
		 *	0 未満または 1 を超過する値が指定された場合は、
		 *	音量の変化を行いません。
		 */
		property double Gain {
			double get();
			void set(double);
		}

		//! キューバッファサイズプロパティ
		/*!
		 *	キューバッファサイズの参照や設定を行います。
		 *	デフォルトは 64 です。
		 */
		property int QueueSize {
			int get();
			void set(int);
		}

		//! ループモードプロパティ
		/*!
		 *	ループモードの参照や設定を行います。
		 *	ループモードとは、音源の最後まで再生が終了した際に、
		 *	最初から再び再生を開始するかどうかを設定するためのモードです。
		 *	具体的には、再生が音源の最後となった時点での
		 *	play() の挙動が異なってきます。
		 *	ループモードが ON (true) の場合、
		 *	再生位置が最初の時点に戻り音源の再生を行います。
		 *	OFF の場合 play() は再生を終了し、OFF (false) となります。
		 *
		 *	\sa Play(), SetLoopArea()
		 */
		property bool LoopMode {
			bool get();
			void set(bool);
		}

		//! サラウンド音源位置プロパティ
		/*!
		 *	音源インスタンス 3 次元位置の参照や設定を行います。
		 *	Model プロパティによる同期モデルの指定が行われた場合は、
		 *	同期モデル位置が優先されます。
		 *	デフォルトは原点です。
		 *
		 *	\sa Model
		 */
		property fk_Vector^ Position {
			fk_Vector^ get();
			void set(fk_Vector^);
		}
					
		//! サラウンド音源同期モデルプロパティ
		/*!
		 *	音源インスタンスの3次元空間中での位置と同期するモデルの参照や指定を行います。
		 *	ここで指定したモデルが移動することにより、
		 *	音源もサラウンド効果の中で移動します。
		 *	同期を解除したい場合は null を代入します。
		 *
		 *	\sa Position, Model, SetListenerModel(fk_Model^)
		 */
		property fk_Model^ Model {
			fk_Model^ get();
			void set(fk_Model^);
		}

		//! サラウンド音源有効距離プロパティ
		/*!
		 *	3次元空間中で音源が届く距離の参照や指定を行います。
		 *	サラウンド効果においては、
		 *	音源はリスナーから離れるほど出力音量が小さくなり、
		 *	ここで指定する距離より大きい場合に聞こえなくなります。
		 */
		property double Distance {
			double get();
			void set(double);
		}

		//! サラウンド効果状態プロパティ
		/*!
		 *	このインスタンスのサラウンド効果を制御します。
		 *	true の場合、サラウンド効果を有効とします。
		 *	false の場合は無効とします。
		 *
		 *	\note
		 *		音源のサラウンド効果を有効とするには、
		 *		音源自体は(ステレオではなく)モノラルである必要があります。
		 */
		property bool SurroundMode {
			bool get();
			void set(bool);
		}					

		//! \name 再生制御メソッド
		//@{

		//! オーディオデータ読み込みメソッド
		/*!
		 *	データを開くための仮想メソッドです。
		 *	具体的な仕様は各派生クラスの Open() を参照して下さい。
		 *
		 *	\param[in]	name	データ名称。
		 *
		 *	\return
		 *		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa	fk_AudioStream::Open(), fk_AudioOggBuffer::Open(),
		 *		fk_AudioWavBuffer::Open()
		 */
		virtual bool Open(String^ name) abstract;

		//! 再生開始可能状態取得メソッド
		/*!
		 *	データ入力やデバイスの初期化等の処理が終了し、
		 *	再生が可能な状態となっているかどうかを取得するメソッドです。
		 *
		 *	\note
		 *		本メソッドは、通常の利用においてはユーザが使用する必要はありません。
		 *
		 *	\return
		 *		再生可能状態であれば true を、
		 *		まだ再生の準備ができていない状態であれば false を返します。
		 */
		virtual bool Ready(void) abstract;

		//! 再生メソッド
		/*!
		 *	実際に音声の再生を行うメソッドです。
		 *	本メソッドは、再生を行いたい状況においては1秒に数回以上の割合で、
		 *	連続して実行する必要があります。
		 *
		 *	\note
		 *		本メソッドは、呼び出しタイミングが一定でないと環境によっては
		 *		動作が不安定となることがあります。
		 *		メインループとは別のスレッドにて、一定タイミングで呼び出すことを推奨します。
		 *
		 *	\return
		 *		音声再生が完了していない場合は true を、
		 *		完了している場合 false を返します。
		 */
		virtual bool Play(void) abstract;

		//! 再生位置取得メソッド
		/*!
		 *	現在の再生位置を返します。単位は秒です。
		 *	このメソッドが返す値は再生時間ではなく、
		 *	音源での始端からの時間となります。
		 *
		 *	\return
		 *		現時点での再生位置。
		 *
		 *	\sa Seek()
		 */

		virtual double Tell(void) abstract;

		//! 再生位置頭出しメソッド
		/*!
		 *	現在の再生位置を変更します。単位は秒です。
		 *
		 *	\param[in]	time	再生位置。
		 *
		 *	\sa Tell()
		 */
		virtual void Seek(double time) abstract;

		//! 停止メソッド
		/*!
		 *	音声の再生を停止し、再生位置も初期化します。
		 *	この後に Play() を実行した場合、
		 *	停止位置ではなく始端(または指定した箇所)から再生されます。
		 *	一時停止を行いたい場合は Pause() を利用して下さい。
		 *
		 *	\sa Pause()
		 */
		virtual void Stop(void) abstract;

		//! オーディオデータ解放メソッド
		/*!
		 *	Open() 等で確保したデータを解放します。
		 *
		 *	\sa Open(), Stop(), Pause()
		 */
		virtual void End(void) abstract;

		//! ポーズメソッド
		/*!
		 *	音声再生の一時停止を行います。
		 *	この後に Play() を実行した場合、
		 *	停止位置からの再生が始まります。
		 *	始端(または指定した箇所)からの再生を行いたい場合は
		 *	Stop() を利用して下さい。
		 *
		 *	\sa Play(), Stop(), End()
		 */
		void Pause(void);

		//@}
		
		//! \name ループ再生制御メソッド
		//@{

		//! ループエリア設定メソッド
		/*!
		 *	ループモードが ON である場合に、繰り返す音源の時間帯を指定します。
		 *	デフォルトでは、開始時間は 0、終了時間は -1 に設定されており、
		 *	終了時間が開始時間より前に設定されている場合、
		 *	ループモードでの終端は音源の終端となります。
		 *
		 *	\param[in]	start	ループモードでの再生開始時間
		 *	\param[in]	end		ループモードでの再生終了時間
		 *
		 *	\sa LoopMode, Play(), Seek(), Tell()
		 */
		void SetLoopArea(double start, double end);


		//! ループ開始点取得メソッド
		/*!
		 *	ループモードでの再生開始時間を取得します。
		 *
		 *	\return		再生開始時間
		 *
		 *	\sa LoopMode, SetLoopArea(), GetLoopEndTime()
		 */
		double GetLoopStartTime(void);

		//! ループ終了点取得メソッド
		/*!
		 *	ループモードでの再生終了時間を取得します。
		 *
		 *	\return		再生終了時間
		 *
		 *	\sa LoopMode, SetLoopArea(), GetLoopStartTime()
		 */
		double GetLoopEndTime(void);
		//@}

		//! \name システム全体初期化・制御メソッド
		//@{

		//! オーディオシステム初期化メソッド
		/*!
		 *	オーディオシステムを利用する際の初期化を行います。
		 *	本メソッドはオーディオシステムを利用する際には必ず実行する必要があります。
		 *	しかし、このメソッドの実行には一定の時間を要する場合もあります。
		 * 	GetInit() メソッドを併用することで、頻繁な実行は避けるべきです。
		 *
		 *	\sa GetInit()
		 */
		static bool Init(void);

		//! オーディオシステム初期化状態取得メソッド
		/*!
		 *	既に初期化を行っているかどうかを取得します。
		 *	初期化を行う Init() メソッドは、
		 *	環境によってはかなり長い実行時間となることもあるため、
		 *	事前に本メソッドによって既に初期化が行われているかどうか調査を行い、
		 *	初期化されていない場合にのみ初期化を行うように記述すべきです。
		 *
		 *	\sa Init()
		 */
		static bool GetInit(void);

		//! プロセススリープメソッド
		/*!
		 *	音声再生のため処理を、指定された時間だけ中断します。
		 *	単位は秒です。
		 *
		 *	このメソッドは、処理を短時間停止して
		 *	CPU の計算資源を別の処理に割くためのものであり、
		 *	再生を停止するためのものではありません。
		 *	再生を停止するには本メソッドではなく Stop() や
		 *	Pause() を用いて下さい。
		 *
		 *	なお、本メソッドは static メソッドとなっており、
		 *	処理の停止はインスタンス全体に対して行われます。
		 *
		 *	\note
		 *		本メソッドは、通常の利用においてユーザが用いることは想定していません。
		 *
		 *	\param[in]	time	処理を停止する時間。
		 *
		 *	\sa Stop(), End()
		 */
		static void Sleep(double time);
		//@}

		//! \name サラウンドリスナー制御メソッド
		//@{

		//! サラウンドリスナー同期モデル設定メソッド
		/*!
		 *	リスナーの位置を制御するための、
		 *	同期モデルインスタンスを指定します。
		 *	デフォルトでは、リスナー位置は原点です。
		 *
		 *	なお、本クラスのリスナーは
		 *	オーディオ系クラスの全インスタンスで共通となっています。
		 *	そのため static メソッドとなっており、
		 *	クラスインスタンスを生成せずに指定することが可能です。
		 *
		 *	リスナーではなく、音源自身の位置を変更するには
		 *	Position プロパティや Model プロパティを使用して下さい。
		 *
		 *	\param[in]	model	リスナーとなるモデルインスタンスへのポインタ。
		 *
		 *	\sa Position, Model
		 */
		static void SetListenerModel(fk_Model^ model);

		//! サラウンドリスナーモデル取得メソッド
		/*!
		 *	リスナーに指定したモデルインスタンスを取得します。
		 *
		 *	\return
		 *		リスナーモデルインスタンスのポインタ。
		 *
		 *	\sa SetListenerModel(fk_Model^)
		 */
		static fk_Model^ GetListenerModel(void);
		//@}
	};
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
