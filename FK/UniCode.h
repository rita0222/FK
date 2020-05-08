#ifndef __FK_UNICODE_HEADER__
#define __FK_UNICODE_HEADER__

#include <vector>
#include <FK/Base.h>

namespace FK {
	
	class fk_StrConverterBase;

	//! 日本語文字コードを表す列挙型
	enum class fk_StringCode {
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

	class fk_UniChar : public fk_BaseObject {
	public:
		//! コンストラクタ
		/*!
		 *	初期化の際に、数値によって文字コードを指定できます。
		 *
		 *	\param[in]	code
		 *		UTF-16 による文字コード。
		 */
		fk_UniChar(int code = 0);

		//! コピーコンストラクタ
		fk_UniChar(const fk_UniChar &);

		//! 単純代入演算子
		fk_UniChar &	operator =(const fk_UniChar &);

		//! ファイル入力関数
		/*!
		 *	ファイルから1文字分のデータを入力し、
		 *	そのコードを格納します。
		 *
		 *	\param[in]	fp	open済みのFILE型ポインタ
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool		readFile(FILE *fp);

		//! 文字コード設定関数1
		/*!
		 *	c1 + c2 * 256 で算出される文字コードを設定します。
		 *
		 *	\param[in]	c1	Unicode 前半8bit部
		 *	\param[in]	c2	Unicode 後半8bit部
		 */
		void		setBuffer(unsigned char c1, unsigned char c2);

		//! 文字コード設定関数2
		/*!
		 *	文字コードを設定します。
		 *
		 *	\param[in]	code	Unicode での文字を表す数値
		 */
		void		setCode(int code);

		//! 文字コード参照関数
		/*!
		 *	設定されている文字コードを取得します。
		 *
		 *	\return		文字コード
		 */
		int			getCode(void);

		//! ASCII文字判定関数
		/*!
		 *	現在設定されている文字コードが、
		 *	ASCII文字かどうかを判定します。
		 *
		 *	\return		ASCII文字であれば true を、そうでなければ false を返します。
		 */
		bool		isAscii(void);

		//! ASCII文字取得関数
		/*!
		 *	現在設定されている文字コードに対し、
		 *	ASCII 文字であると仮定した上で、その ASCII 文字を char 型で返します。
		 *	もし格納されている文字コードが ASCII 文字を表さない場合、
		 *	結果は保証されません。
		 *
		 *	\return		char 型の ASCII 文字
		 */
		char		getAscii(void);

	private:
		int			code;
	};

	//! 文字列板に表示する文字列を制御するクラス
	/*!
	 *	このクラスは、 fk_TextImage による文字列板を作成する際に、
	 *	文字列を制御するための機能を提供します。
	 *	本クラスでは、内部の日本語コードとして Unicode (UTF-16) を採用しています。
	 *
	 *	fk_TextImage には、ファイルから文字列を直接入力する機能
	 *	(fk_TextImage::loadStrFile() 関数) がありますが、
	 *	動的に文字列を生成したい場合(例えば、ゲームの得点表示など)や、
	 *	プログラムコード中に直接表示文字列を記述したい場合などは、
	 *	このクラスによって文字列を生成します。
	 *
	 *	\sa fk_TextImage, fk_UniChar
	 */

	class fk_UniStr : public fk_BaseObject {
	public:
		//! コンストラクタ
		fk_UniStr(void);

		//! デストラクタ
		virtual ~fk_UniStr();

		//! コピーコンストラクタ
		fk_UniStr(const fk_UniStr &);

		//! 単純代入演算子
		fk_UniStr &	operator =(const fk_UniStr &);

		//! 初期化関数
		/*!
		 *	文字列の初期化を行います。初期化後、文字列は空文字列となります。
		 */
		void	clear(void);

		//! 文字列長参照関数
		/*!
		 *	現在格納されている文字列の長さを取得します。
		 *	全角文字、半角文字共に 1 文字として数えます。
		 *
		 *	\return		文字列長
		 */
		int		getLength(void) const;

		//! 一行分取得関数
		/*!
		 *	他の fk_UniStr 型インスタンスに格納されている文字列から、
		 *	一行分の文字列を取得します。
		 *	この関数で文字列を取得した際、元文字列から何文字目までを取得したのかは保存され、
		 *	次にこの関数を利用する際には前回の終了文字より後から読み込み始めます。
		 *	(C言語標準関数「fgets()」と似たような挙動ということです。)
		 *	この関数を用いた際、元の文字列についてはなんらの消去を行いません。
		 *	元文字列の終端に至った場合は、そこまでの文字列を格納します。
		 *
		 *	元文字列の改行に関係なく、全体をコピーしたい場合は copyStr() を利用して下さい。
		 *
		 *	\param[in]	str		元文字列
		 *
		 *	\return
		 *		読み込みに成功した場合は true を返します。
		 *		以下の条件のいずれかの場合、false を返します。
		 *		- 既に前回の読み込みで終端に至っており、読み込む文字がもうない場合。
		 *		- 読み込みに失敗した場合。
		 *
		 *	\sa fgetLine(), copyStr(), markClear()
		 */
		bool	getLine(fk_UniStr *str);

		//! マーク初期化関数
		/*!
		 *	getLine() 関数では、元文字列から何文字目までを取得したのかは保存されます。
		 * 	本関数は、この情報を初期化するものです。
		 *	この関数を呼ぶと、
		 *	次に getLine() を用いた場合は改めて文字列の先頭から格納を始めます。
		 *
		 *	\sa getLine()
		 */
		void	markClear(void);

		//! ファイル一行分取得関数1
		/*!
		 *	ファイルから一行分の文字列を格納します。
		 *	この関数で文字列を取得した際、
		 *	次にこの関数を利用する際には前回の終了文字より後から読み込み始めます。
		 *	(C言語標準関数「fgets()」と似たような挙動ということです。)
		 *
		 *	ファイル中の改行に関係なく、全体を読み込みたい場合は
		 *	readFile() を利用して下さい。
		 *
		 *	\param[in]	fp
		 *		FILE型ファイルポインタ。
		 *		事前に fopen() 関数を用いて自前でファイルを開いておく必要があります。
		 *
		 *	\param[in]	code
		 *		入力する文字列の想定日本語コード。
		 *		サポートしているのは JISコード、SJISコード、EUC、UTF-16 です。
		 *		具体的な指定値は fk_StringCode のリストを参照して下さい。
		 *
		 *	\return
		 *		読み込みに成功した場合は true を返します。
		 *		以下の条件のいずれかの場合、false を返します。
		 *		- 既に前回の読み込みで終端に至っており、読み込む文字がもうない場合。
		 *		- 読み込みに失敗した場合。
		 *
		 *	\sa getLine(), readFile()
		 */
		bool	fgetLine(FILE *fp, fk_StringCode code = fk_StringCode::UTF16);

		//! ファイル一行分取得関数2
		/*!
		 *	ファイルから一行分の文字列を格納します。
		 *	この関数で文字列を取得した際、
		 *	次にこの関数を利用する際には前回の終了文字より後から読み込み始めます。
		 *	(C言語標準関数「fgets()」と似たような挙動ということです。)
		 *
		 *	ファイル中の改行に関係なく、全体を読み込みたい場合は
		 *	readFile() を利用して下さい。
		 *
		 *	\param[in]	ifs
		 *		std::ifstream型ポインタ。
		 *		事前にファイルを開いておく必要があります。
		 *
		 *	\param[in]	code
		 *		入力する文字列の想定日本語コード。
		 *		サポートしているのは JISコード、SJISコード、EUC、UTF-16 です。
		 *		具体的な指定値は fk_StringCode のリストを参照して下さい。
		 *
		 *	\return
		 *		読み込みに成功した場合は true を返します。
		 *		以下の条件のいずれかの場合、false を返します。
		 *		- 既に前回の読み込みで終端に至っており、読み込む文字がもうない場合。
		 *		- 読み込みに失敗した場合。
		 *
		 *	\sa getLine(), readFile()
		 */

		bool	fgetLine(std::ifstream *ifs, fk_StringCode code = fk_StringCode::UTF16);
		//! ファイル全体取得関数
		/*!
		 *	テキストファイル全体を格納します。
		 *	本関数は、行が複数ある場合も全てを格納します。
		 *	一行ずつ読み込みたい場合は fgetLine() を利用して下さい。
		 *
		 *	\param[in]	fileName	テキストファイルのファイル名
		 *
		 *	\param[in]	code
		 *		入力する文字列の想定日本語コード。
		 *		サポートしているのは JISコード、SJISコード、EUC、UTF-16 です。
		 *		具体的な指定値は fk_StringCode のリストを参照して下さい。
		 *
		 *	\return		読み込みに成功した場合 true を、失敗した場合 false を返します。
		 *
		 *	\sa fgetLine(), copyStr()
		 */
		bool	readFile(const std::string fileName,
						 fk_StringCode code = fk_StringCode::UTF16);

		//! 文字列コピー関数
		/*!
		 *	他の fk_UniStr 型インスタンスに格納されている文字列をコピーします。
		 *	一行分のみをコピーしたい場合は、 getLine() を利用して下さい。
		 *
		 *	\param[in]	str		コピー元のインスタンス
		 *
		 *	\sa getLine(), readFile()
		 */
		void	copyStr(fk_UniStr *str);

		//! 文字列生成関数
		/*!
		 *	文字列を生成します。
		 *	文字列部分の引数型は std::string 型となっており、
		 *	もちろん std::string 型の変数を代入することができますが、
		 *	以下のように直接コードに記述することも可能です。
		 *
		 *		fk_UniStr	str;
		 *		str.convert("サンプル", fk_StringCode::SJIS);
		 *
		 *	printf 形式の書式付きで生成したい場合は、 printf() を利用して下さい。
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
		void	convert(const std::string &str, fk_StringCode code);

		//! printf 形式書式付き文字列生成関数
		/*!
		 *	文字列を printf 形式の書式に従って生成します。
		 *	本関数は、第1引数が文字コード指定であり、
		 *	第2引数が書式フォーマットであるという点以外は、
		 *	C言語標準関数である printf() と同様の利用が可能です。
		 *	例えば、以下のサンプルコードは
		 *	str[0]〜str[9]に「0です」〜「9です」という文字列を格納します。
		 *
		 *		fk_UniStr	str[10];
		 *
		 *		for(int i = 0; i < 10; i++) {
		 *			str[i].printf(fk_StringCode::SJIS, "%dです", i);
		 *		}
		 *
		 *	\param[in]	code
		 *		入力する文字列の想定日本語コード。
		 *		サポートしているのは JISコード、SJISコード、EUC、UTF-16 です。
		 *		具体的な指定値は fk_StringCode のリストを参照して下さい。
		 *
		 *	\param[in]	format		printf() 形式のフォーマット
		 *
		 *	\sa convert()
		 */
		void	printf(fk_StringCode code, const char *format, ...);

		//! 文字コード参照関数
		/*!
		 *	先頭から指定した番目の文字の UTF-16 に基づく文字コードを取得します。
		 *
		 *	\param[in]	num		文字の番目
		 *
		 *	\return
		 *		文字列の長さよりも num が小さかった場合は、指定した文字のコードを返します。
		 *		num 文字列の長さよりも大きかった場合、-1 を返します。
		 */
		int		getCode(int num) const;

		//! 文字検索関数1
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
		 *	\sa find(int, unsigned char, unsigned char)
		 */
		int		find(int start, int code);

		//! 文字検索関数2
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
		 *	\sa find(int, int)
		 */
		int		find(int start, unsigned char c1, unsigned char c2);

		//! 最後尾文字削除関数
		/*!
		 *	格納されている文字列の、最後尾の文字を削除します。
		 */
		void	pop_back(void);

		//! 後部文字追加関数1
		/*!
		 *	格納されている文字列に対し、最後尾に文字を追加します。
		 *
		 *	\param[in]	c		格納文字
		 *
		 *	\sa fk_UniChar
		 */
		void	push_back(fk_UniChar c);

		//! 後部文字追加関数2
		/*!
		 *	格納されている文字列に対し、最後尾に文字を追加します。
		 *	引数がポインタになっていますが、
		 *	追加されるのは指定アドレスにある最初の1文字のみです。
		 *
		 *	\param[in]	c		格納文字
		 *
		 *	\sa fk_UniChar
		 */
		void	push_back(fk_UniChar *c);

		//! 後部文字追加関数3
		/*!
		 *	格納されている文字列に対し、最後尾に文字を追加します。
		 *
		 *	\param[in]	code	文字の UTF-16 に基づくコード
		 */
		void	push_back(int code);

#ifndef FK_DOXYGEN_USER_PROCESS
		void	Print(std::string = "");
#endif

	private:
		std::vector<int>		uniStr;
		int						mark;

		bool					fgetLine_UTF16(FILE *);
		bool					fgetLine_UTF16(std::ifstream *);
	};

	//! 日本語文字コード変換クラス
	/*!
	 *	このクラスは、Shift-JISコード、EUCコード、
	 *	ISO-2022-JP (以下「JISコード」) で表現された日本語文字列を、
	 *	UTF-16 コードに変換するための機能を提供します。
	 *
	 *	FK システムでは、
	 *	fk_TextImage クラスでの内部文字コードとして UTF-16 を採用しています。
	 *	そのため、その他の文字コードで記述されている
	 *	ソースプログラムやデータファイルを入力する場合は、
	 *	文字コードを変換する必要があります。
	 *	本クラスでは、 std::string に格納されている文字列に対し、
	 *	fk_UniStr 型の文字列に変換する機能を提供します。
	 *
	 *	実質的には、 fk_UniStr::convert() があるため、
	 *	ユーザが本クラスを利用する機会はほとんどないと思われます。
	 *	fk_UniStr::convert() の内部実装においては、本クラスが利用されています。
	 *
	 *	なお、改行コードについては変換を行いません。
	 *
	 *	\sa fk_UniStr
	 */

	class fk_StrConverter {
	public:
		//! コンストラクタ
		fk_StrConverter(void);
		//! デストラクタ
		virtual ~fk_StrConverter();

		//! JISコード変換関数
		/*!
		 *	ISO-2022-JP コード (通称 JIS コード) から UTF-16 へ文字列を変換します。
		 *
		 *	\param[in]	str		JISコードの文字列データ
		 *	\param[out]	uniStr	変換文字列を格納する fk_UniStr 型インスタンス
		 */
		void		convertJIS(const std::string &str, fk_UniStr *uniStr);

		//! Shift-JISコード変換関数
		/*!
		 *	Shift-JIS コード (通称 SJIS コード) から UTF-16 へ文字列を変換します。
		 *
		 *	\param[in]	str		SJISコードの文字列データ
		 *	\param[out]	uniStr	変換文字列を格納する fk_UniStr 型インスタンス
		 */
		void		convertSJIS(const std::string &str, fk_UniStr *uniStr);

		//! EUCコード変換関数
		/*!
		 *	EUC コードから UTF-16 へ文字列を変換します。
		 *
		 *	\param[in]	str		EUCコードの文字列データ
		 *	\param[out]	uniStr	変換文字列を格納する fk_UniStr 型インスタンス
		 */
		void		convertEUC(const std::string &str, fk_UniStr *uniStr);

		//! UTF-8 コード変換関数
		/*!
		 *	UTF-8 コードから UTF-16 へ文字列を変換します。
		 *
		 *	\param[in]	str		UTF-8 コードの文字列データ
		 *	\param[out]	uniStr	変換文字列を格納する fk_UniStr 型インスタンス
		 */
		void		convertUTF8(const std::string &str, fk_UniStr *uniStr);



#ifndef FK_DOXYGEN_USER_PROCESS
		void		convert_SJIS(const std::string &,
								 std::string *,
								 fk_StringCode);

		void		convert_UTF8(const std::string &,
								 std::string *,
								 fk_StringCode);
#endif

	private:
		std::unique_ptr<fk_StrConverterBase> base;

		void	ConvertJIS_UTF8(const std::string &, std::string *);
		void	ConvertSJIS_UTF8(const std::string &, std::string *);
		void	ConvertEUC_UTF8(const std::string &, std::string *);
		void	ConvertUTF16_UTF8(const std::string &, std::string *);

		void	ConvertJIS_SJIS(const std::string &, std::string *);
		void	ConvertEUC_SJIS(const std::string &, std::string *);
		void	ConvertUTF8_SJIS(const std::string &, std::string *);
		void	ConvertUTF16_SJIS(const std::string &, std::string *);

	};

	//! 簡易文字コード変換用名前空間
	namespace fk_Code {

		//! 入力文字コード設定関数
		/*!
		 *	簡易的に文字コードを変換する機能を用いるときの、
		 *	入力用文字コードを事前に設定します。
		 *
		 *	\sa utf8(const std::string &), sjis(const std::string &)
		 */
		void	setInputCoding(fk_StringCode);

		//! UTF-8変換関数(入力文字コード省略)
		/*!
		 *	入力された文字列を UTF-8 に変換します。
		 *	入力文字列の文字コードは事前に
		 *	setInputCoding() で設定しておく必要があります。
		 *
		 *	\param[in]	str		入力文字列
		 *
		 *	\return
		 *		UTF-8 に変換した文字列の先頭アドレスを返します。
		 *
		 *	\sa	setInputCoding()
		 */
		char *	utf8(const std::string &str);

		//! UTF8変換関数
		/*!
		 *	入力された文字列を UTF-8 に変換します。
		 *
		 *	\param[in]	str		入力文字列
		 *	\param[in]	code	入力文字列の文字コード
		 *
		 *	\return
		 *		UTF-8 に変換した文字列の先頭アドレスを返します。
		 */
		char *	utf8(const std::string &str, fk_StringCode code);

		//! Shift-JIS変換関数(入力文字コード省略)
		/*!
		 *	入力された文字列を Shift-JIS に変換します。
		 *	入力文字列の文字コードは事前に
		 *	setInputCoding() で設定しておく必要があります。
		 *
		 *	\param[in]	str		入力文字列
		 *
		 *	\return
		 *		Shift-JIS に変換した文字列の先頭アドレスを返します。
		 *
		 *	\sa	setInputCoding()
		 */
		char *	sjis(const std::string &str);

		//! Shift-JIS変換関数
		/*!
		 *	入力された文字列を Shift-JIS に変換します。
		 *
		 *	\param[in]	str		入力文字列
		 *	\param[in]	code	入力文字列の文字コード
		 *
		 *	\return
		 *		Shift-JIS に変換した文字列の先頭アドレスを返します。
		 */
		char *	sjis(const std::string &str, fk_StringCode code);
	}
}

#endif // !__FK_UNICODE_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
