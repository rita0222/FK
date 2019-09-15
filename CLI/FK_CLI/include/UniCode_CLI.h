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
// UniCode_CLI.h

#pragma once

#include <FK/UniCode.h>
#include "Base_CLI.h"

namespace FK_CLI
{
	//! 日本語文字コードを表す列挙型
	public enum class fk_StringCode {
		UTF16,	//!< Unicode (UTF-16)
		UTF8,	//!< Unicode (UTF-8)
		JIS,	//!< ISO-2022-JIS (JISコード)
		SJIS,	//!< Shift-JIS (SJISコード)
		EUC		//!< EUC
	};

	//! Unicode の文字を表すクラス
	/*!
	 *	このクラスは、Unicode による文字を制御するための機能を提供します。
	 *
	 *	FK では、日本語の内部コードとして UTF-16 を用いています。
	 *	本クラスは、UTF-16 による文字を格納することができます。
	 *	実質的には、 fk_UniStr による文字列クラスによってほとんどの用途は満たせるため、
	 *	ユーザがこのクラスを利用する機会はほとんどないと思われます。
	 *	fk_UniStr の内部実装において、本クラスが利用されています。
	 *
	 *	\sa fk_UniStr
	 */
	public ref class fk_UniChar : fk_BaseObject {
	internal:
		::FK::fk_UniChar * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_UniChar(bool argNewFlg);
#endif
		//! コンストラクタ1
		/*!
		 *	文字コードが 0 となる文字を生成します。
		 */
		fk_UniChar();

		//! コンストラクタ2
		/*!
		 *	初期化の際に、数値によって文字コードを指定できます。
		 *
		 *	\param[in]	code
		 *		UTF-16 による文字コード。
		 */
		fk_UniChar(int code);

		//! デストラクタ
		~fk_UniChar();

		//! ファイナライザ
		!fk_UniChar();

		//! 文字コードプロパティ
		/*!
		 *	文字コードの参照・設定を行います。
		 *	設定の際には、Unicode での文字を表す数値を用います。
		 */
		property int Code {
			int get();
			void set(int);
		}

		//! ASCII文字取得プロパティ
		/*!
		 *	現在設定されている文字コードに対し、
		 *	ASCII 文字であると仮定した上で、その ASCII 文字を char 型で参照します。
		 *	もし格納されている文字コードが ASCII 文字を表さない場合、
		 *	結果は保証されません。
		 */
		property char Ascii {
			char get();
		}
		
		//! 文字コード設定メソッド1
		/*!
		 *	c1 + c2 * 256 で算出される文字コードを設定します。
		 *
		 *	\param[in]	c1	Unicode 前半8bit部
		 *	\param[in]	c2	Unicode 後半8bit部
		 */
		void SetBuffer(unsigned char c1, unsigned char c2);

		//! ASCII文字判定メソッド
		/*!
		 *	現在設定されている文字コードが、
		 *	ASCII文字かどうかを判定します。
		 *
		 *	\return		ASCII文字であれば true を、そうでなければ false を返します。
		 */
		bool IsAscii(void);
	};

	//! 文字列板に表示する文字列を制御するクラス
	/*!
	 *	このクラスは、 fk_TextImage による文字列板を作成する際に、
	 *	文字列を制御するための機能を提供します。
	 *	本クラスでは、内部の日本語コードとして Unicode (UTF-16) を採用しています。
	 *
	 *	fk_TextImage には、ファイルから文字列を直接入力する機能
	 *	(fk_TextImage::LoadStrFile() メソッド) がありますが、
	 *	動的に文字列を生成したい場合(例えば、ゲームの得点表示など)や、
	 *	プログラムコード中に直接表示文字列を記述したい場合などは、
	 *	このクラスによって文字列を生成します。
	 *
	 *	\sa fk_TextImage, fk_UniChar
	 */
	public ref class fk_UniStr : fk_BaseObject {

	internal:
		::FK::fk_UniStr * GetP(void);
		static ::FK::fk_StringCode GetCode(fk_StringCode);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_UniStr(bool argNewFlg);
#endif

		//! コンストラクタ
		fk_UniStr();

		//! デストラクタ
		~fk_UniStr();

		//! ファイナライザ
		!fk_UniStr();

		//! 初期化メソッド
		/*!
		 *	文字列の初期化を行います。初期化後、文字列は空文字列となります。
		 */
		void	Clear(void);

		//! 文字列長参照メソッド
		/*!
		 *	現在格納されている文字列の長さを取得します。
		 *	全角文字、半角文字共に 1 文字として数えます。
		 *
		 *	\return		文字列長
		 */
		int		GetLength(void);

		//! 一行分取得メソッド
		/*!
		 *	他の fk_UniStr 型インスタンスに格納されている文字列から、
		 *	一行分の文字列を取得します。
		 *	このメソッドで文字列を取得した際、元文字列から何文字目までを取得したのかは保存され、
		 *	次にこのメソッドを利用する際には前回の終了文字より後から読み込み始めます。
		 *	(C言語標準関数「fgets()」と似たような挙動ということです。)
		 *	このメソッドを用いた際、元の文字列についてはなんらの消去を行いません。
		 *	元文字列の終端に至った場合は、そこまでの文字列を格納します。
		 *
		 *	元文字列の改行に関係なく、全体をコピーしたい場合は CopyStr() を利用して下さい。
		 *
		 *	\param[in]	str		元文字列
		 *
		 *	\return
		 *		読み込みに成功した場合は true を返します。
		 *		以下の条件のいずれかの場合、false を返します。
		 *		- 既に前回の読み込みで終端に至っており、読み込む文字がもうない場合。
		 *		- 読み込みに失敗した場合。
		 *
		 *	\sa CopyStr(), MarkClear()
		 */
		bool	GetLine(fk_UniStr^ str);

		//! マーク初期化メソッド
		/*!
		 *	GetLine() メソッドでは、元文字列から何文字目までを取得したのかは保存されます。
		 * 	本メソッドは、この情報を初期化するものです。
		 *	このメソッドを呼ぶと、
		 *	次に GetLine() を用いた場合は改めて文字列の先頭から格納を始めます。
		 *
		 *	\sa GetLine()
		 */
		void	MarkClear(void);

		//! ファイル全体取得メソッド1
		/*!
		 *	テキストファイル全体を格納します。
		 *	本メソッドは、行が複数ある場合も全てを格納します。
		 *
		 *	\param[in]	fileName	テキストファイルのファイル名
		 *	\param[in]	code
		 *		入力する文字列の想定日本語コード。
		 *		サポートしているのは JISコード、SJISコード、EUC、UTF-16 です。
		 *		具体的な指定値は fk_StringCode のリストを参照して下さい。
		 *
		 *	\return		読み込みに成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa CopyStr()
		 */
		bool	ReadFile(String^ fileName, fk_StringCode code);

		//! ファイル全体取得メソッド2
		/*!
		 *	テキストファイル全体を格納します。
		 *	本メソッドは、行が複数ある場合も全てを格納します。
		 *	文字コードは UTF-16 であることを前提としています。
		 *	他の文字コードを扱いたい場合は、
		 *	ReadFile(String^, fk_StringCode) を利用して下さい。
		 *
		 *	\param[in]	fileName	テキストファイルのファイル名
		 *
		 *	\return		読み込みに成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa CopyStr()
		 */
		bool	ReadFile(String^ fileName);

		//! 文字列コピーメソッド
		/*!
		 *	他の fk_UniStr 型インスタンスに格納されている文字列をコピーします。
		 *	一行分のみをコピーしたい場合は、 GetLine() を利用して下さい。
		 *
		 *	\param[in]	str		コピー元のインスタンス
		 *
		 *	\sa GetLine(), ReadFile()
		 */
		void	CopyStr(fk_UniStr^ str);

		//! 文字列生成メソッド1
		/*!
		 *	文字列を生成します。
		 *	文字列部分の引数型は String 型となっており、
		 *	もちろん String 型の変数を代入することができますが、
		 *	以下のように直接コードに記述することも可能です。
		 *
		 *		fk_UniStr	str;
		 *		str.Convert("サンプル", FK_STR_SJIS);
		 *
		 *	\param[in]	str		格納したい文字列
		 *
		 *	\param[in]	code
		 *		入力する文字列の想定日本語コード。
		 *		サポートしているのは JISコード、SJISコード、EUC、UTF-16 です。
		 *		具体的な指定値は fk_StringCode のリストを参照して下さい。
		 *
		 *	\sa printf()
		 */
		void	Convert(String^ str, fk_StringCode code);

		//! 文字列生成メソッド2
		/*!
		 *	文字列を生成します。
		 *	文字列部分の引数型は String 型となっており、
		 *	もちろん String 型の変数を代入することができますが、
		 *	以下のように直接コードに記述することも可能です。
		 *
		 *		fk_UniStr	str;
		 *		str.Convert("サンプル");
		 *
		 *	なお、入力文字列は SJIS を前提としています。
		 *	他の文字コードを利用したい場合は、
		 *	Convert(String^, fk_StringCode) を利用して下さい。
		 *
		 *	\param[in]	str		格納したい文字列
		 */
		void	Convert(String^ str);

		//! 文字コード参照メソッド
		/*!
		 *	先頭から指定した番目の文字の UTF-16 に基づく文字コードを取得します。
		 *
		 *	\param[in]	num		文字の番目
		 *
		 *	\return
		 *		文字列の長さよりも num が小さかった場合は、指定した文字のコードを返します。
		 *		num 文字列の長さよりも大きかった場合、-1 を返します。
		 */
		int		GetCode(int num);

		//! 文字検索メソッド1
		/*!
		 *	現在格納されている文字列に対し、
		 *	指定した場所から特定の文字を検索します。
		 *
		 *	\param[in]	start
		 *		検索開始場所。最初から検索する場合は 0 を指定してください。
		 *		ここで指定した文字そのものも検索対象に入ります。
		 *
		 *	\param[in]	code		検索対象文字の UTF-16 に基づくコード
		 *
		 *	\return
		 *		発見された場合はその文字の番目を返します。
		 *		発見されなかった場合は -1 を返します。
		 *
		 *	\sa Find(int, unsigned char, unsigned char)
		 */
		int		Find(int start, int code);

		//! 文字検索メソッド2
		/*!
		 *	現在格納されている文字列に対し、
		 *	指定した場所から特定の文字を検索します。
		 *
		 *	\param[in]	start
		 *		検索開始場所。最初から検索する場合は 0 を指定してください。
		 *		ここで指定した文字そのものも検索対象に入ります。
		 *
		 *	\param[in]	c1	検索対象文字の UTF-16 前半8bit部
		 *
		 *	\param[in]	c2	検索対象文字の UTF-16 後半8bit部
		 *
		 *	\return
		 *		発見された場合はその文字の番目を返します。
		 *		発見されなかった場合は -1 を返します。
		 *
		 *	\sa Find(int, int)
		 */
		int		Find(int start, unsigned char c1, unsigned char c2);

		//! 最後尾文字削除メソッド
		/*!
		 *	格納されている文字列の、最後尾の文字を削除します。
		 */
		void	PopBack(void);

		//! 後部文字追加メソッド1
		/*!
		 *	格納されている文字列に対し、最後尾に文字を追加します。
		 *
		 *	\param[in]	c		格納文字
		 *
		 *	\sa fk_UniChar
		 */
		void	PushBack(fk_UniChar^ c);

		//! 後部文字追加メソッド3
		/*!
		 *	格納されている文字列に対し、最後尾に文字を追加します。
		 *
		 *	\param[in]	code	文字の UTF-16 に基づくコード
		 */
		void	PushBack(int code);
	};
}


