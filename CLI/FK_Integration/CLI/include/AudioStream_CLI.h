// AudioStream_CLI.h

#pragma once

#include <FK/Audio.h>
#include "AudioBase_CLI.h"

namespace FK_CLI
{
	//! オーディオストリームクラス
	/*!
	 *	このクラスは、
	 *	Ogg Vorbis 形式のファイルに格納された音声の、
	 *	ストリーミング再生機能を提供します。
	 *
	 *	このクラスでの再生は、再生時にファイルの一部分のみを読み込み、
	 *	再生が進む過程で逐次ファイルの読み込みを行います。
	 *	従って、巨大なファイルの入力であってもメモリの使用量を節約できます。
	 *	長尺でループするような、BGM などの音源に適しています。
	 *
	 *	一方、頻繁な停止と再生の繰り返し、
	 *	Seek() を頻繁に用いた再生位置の変更、
	 *	即応性のある再生には対応できません。
	 *	そのため効果音等には向いていません。
	 *	効果音を制御するような用途としては、
	 *	fk_AudioOggBuffer, fk_AudioWavBuffer が適しています。
	 *
	 *	なお、本クラスは fk_AudioBase クラスの派生クラスであり、
	 *	音量やループ再生の制御、サラウンド効果の使用といった機能の利用については
	 *	fk_AudioBase のメンバ関数を用いて行います。
	 *
	 *	\sa fk_AudioBase, fk_AudioOggBuffer, fk_AudioWavBuffer
	 */
	public ref class fk_AudioStream : fk_AudioBase {
	internal:
		::fk_AudioStream * GetP(void);

	public:
		//! コンストラクタ
		fk_AudioStream();

		//! デストラクタ
		~fk_AudioStream();

		//! ファイナライザ
		!fk_AudioStream();

		//! オーディオデータ読み込み関数
		/*!
		 *	Ogg Vorbis 形式のファイルを指定することで、
		 *	音声データを読み込みます。
		 *
		 *	\note
		 *		サラウンド効果を有効とするためには、
		 *		音源はモノラルでなければなりません。
		 *
		 *	\param[in]	filename	ファイル名。
		 *
		 *	\return
		 *		入力に成功すれば true を、
		 *		失敗すれば false を返します。
		 */
		virtual bool Open(String^ filename) override;

		//! 再生開始可能状態取得関数
		/*!
		 *	Open() によってファイルから音声を入力した後、
		 *	再生可能な状態になっているかどうかを取得します。
		 *
		 *	\note
		 *		本関数は、通常の利用においてはユーザが使用する必要はありません。
		 *
		 *	\return
		 *		再生可能状態であれば true を、
		 *		まだ再生の準備ができていない状態であれば false を返します。
		 */
		virtual bool Ready(void) override;

		//! 再生関数
		/*!
		 *	実際に音声の再生を行う関数です。
		 *	この関数は、再生を行いたい状況においては1秒に数回以上の割合で、
		 *	連続して実行する必要があります。
		 *	通常は、画面更新のためのメインループ中に一度ずつ実行します。
		 *
		 *	\return
		 *		音声再生が完了していない場合は true を、
		 *		完了している場合 false を返します。
		 */
		virtual bool Play(void) override;

		//! 再生位置取得関数
		/*!
		 *	現在の再生位置を返します。単位は秒です。
		 *	この関数が返す値は再生時間ではなく、
		 *	音源での始端からの時間となります。
		 *
		 *	\return
		 *		現時点での再生位置。
		 *
		 *	\sa Seek()
		 */
		virtual double Tell(void) override;

		//! 再生位置頭出し関数
		/*!
		 *	現在の再生位置を変更します。単位は秒です。
		 *
		 *	\param[in]	time	再生位置。
		 *
		 *	\sa Tell()
		 */
		virtual void Seek(double time) override;

		//! 停止関数
		/*!
		 *	音声の再生を停止し、再生位置も初期化します。
		 *	この後に Play() を実行した場合、
		 *	停止位置ではなく始端(または指定した箇所)から再生されます。
		 *	一時停止を行いたい場合は fk_AudioBase::Pause() を利用して下さい。
		 *
		 *	\sa fk_AudioBase::Pause()
		 */
		virtual void Stop(void) override;

		//! オーディオデータ解放関数
		/*!
		 *	Open() 等で確保したデータを解放します。
		 *
		 *	\sa Open(), Stop(), fk_AudioBase::Pause()
		 */
		virtual void End(void) override;
	};
}
