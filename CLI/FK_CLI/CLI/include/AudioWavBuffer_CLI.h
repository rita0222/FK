// AudioWavBuffer_CLI.h

#pragma once

#include <FK/Audio.h>
#include "AudioOggBuffer_CLI.h"

namespace FK_CLI
{
	//! Wave オーディオバッファクラス
	/*!
	 *	このクラスは、Wave 形式のファイルに格納された音声を、
	 *	オンメモリで再生する機能を提供します。
	 *	このクラスは、ファイルを読み込む時点で全ての音声データをメモリ上に展開します。
	 *	これにより、頻繁な再生と停止を繰り返したり、
	 *	seek() を頻繁に用いて再生位置を変更するといった、
	 *	即応性の高い再生を可能としています。
	 *	短くて頻繁に再生と停止を繰り返すような、効果音などの音源に適しています。
	 *	また、サラウンドにも対応しています。
	 *
	 *	しかしながら、全てのデータをメモリ上に展開するという仕様上、
	 *	巨大な音声データを入力した場合にはかなりのメモリを使用してしまいます。
	 *	長尺で単調に再生するような BGM 再生などの用途には向いていません。
	 *	そのような用途を想定する場合は、 fk_AudioStream クラスを利用して下さい。
	 *
	 *	また、Ogg Vorbis 形式のファイルを再生したい場合は
	 *	fk_AudioOggBuffer クラスを利用してください。
	 *	本クラスとほぼ同一の機能を持ちます。
	 *
	 *	なお、本クラスは fk_AudioBase クラスの派生クラスであり、
	 *	音量やループ再生の制御、サラウンド効果の使用といった機能の利用については
	 *	fk_AudioBase のメンバ関数を用いて行います。
	 *
	 *	\sa fk_AudioBase, fk_AudioOggBuffer, fk_AudioStream
	 */
	public ref class fk_AudioWavBuffer : fk_AudioOggBuffer {
	internal:
		::fk_AudioWavBuffer * GetP(void);

	public:
		//! コンストラクタ
		fk_AudioWavBuffer();

		//! デストラクタ
		~fk_AudioWavBuffer();

		//! ファイナライザ
		!fk_AudioWavBuffer();

		//! オーディオデータ読み込み関数
		/*!
		 *	Wave 形式のファイルを指定することで、
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
	};
}
