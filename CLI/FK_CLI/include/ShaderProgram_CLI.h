﻿#pragma once

#include <FK/ShaderProgram.h>

using namespace System;

namespace FK_CLI
{
	//! シェーダープログラム格納クラス
	/*!
	 *	このクラスは、シェーダーのプログラムソースを格納するための機能を提供します。
	 *	インスタンス内部でバーテックス(頂点)シェーダーと
	 *	フラグメント(ピクセル)シェーダーのソースコードを管理します。
	 *	本クラスは単独のインスタンスとしてはあまり利用用途はなく、
	 *	fk_ShaderBinder の fk_ShaderBinder.Program
	 *	プロパティとして利用することがほとんどです。
	 *
	 *	\sa fk_ShaderBinder, fk_ShaderParameter, fk_TextureSampler
	 */
	public ref class fk_ShaderProgram
	{
	internal:
		bool dFlg;
		::FK::fk_ShaderProgram *pProg;
		::FK::fk_ShaderProgram * GetP(void);

	public:

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_ShaderProgram(::FK::fk_ShaderProgram *);
		fk_ShaderProgram(bool);
#endif

		//! コンストラクタ
		fk_ShaderProgram();

		//! デストラクタ
		~fk_ShaderProgram();

		//! ファイナライザ
		!fk_ShaderProgram();

		//! バーテックスシェーダーコードプロパティ
		/*!
		 *	バーテックス(頂点)シェーダーのコードの設定や取得を行います。
		 *	バーテックスシェーダーのコードを設定する際は、
		 *	本プロパティに直接コードを書き込むか、
		 *	LoadVertexShader() メソッドでコードが格納されているファイル名を指定して下さい。
		 */
		property String^ VertexShaderSource {
			String^ get(void);
			void set(String^);
		}

		//! フラグメントシェーダーコードプロパティ
		/*!
		 *	フラグメント(ピクセル)シェーダーのコードの設定や取得を行います。
		 *	フラグメントシェーダーのコードを設定する際は、
		 *	本プロパティに直接コードを書き込むか、
		 *	LoadVertexShader() メソッドでコードが格納されているファイル名を指定して下さい。
		 */
		property String^ FragmentShaderSource {
			String^ get(void);
			void set(String^);
		}

		//! ジオメトリシェーダーコードプロパティ
		/*!
		 *	ジオメトリシェーダーのコードの設定や取得を行います。
		 *	ジオメトリシェーダーのコードを設定する際は、
		 *	本プロパティに直接コードを書き込むか、
		 *	LoadGeometryShader() メソッドでコードが格納されているファイル名を指定して下さい。
		 */
		property String^ GeometryShaderSource {
			String^ get(void);
			void set(String^);
		}

		//! テッセレーション制御コードプロパティ
		/*!
		 *	テッセレーション制御シェーダーのコードの設定や取得を行います。
		 *	テッセレーション制御シェーダーのコードを設定する際は、
		 *	本プロパティに直接コードを書き込むか、
		 *	LoadTessCtrlShader() 関数でコードが格納されているファイル名を指定して下さい。
		 */
		property String ^TessCtrlShaderSource {
			String ^get(void);
			void set(String ^);
		}

		//! テッセレーション評価シェーダーコードプロパティ
		/*!
		 *	テッセレーション評価シェーダーのコードの設定や取得を行います。
		 *	テッセレーション評価シェーダーのコードを設定する際は、
		 *	本プロパティに直接コードを書き込むか、
		 *	LoadTessEvalShader() 関数でコードが格納されているファイル名を指定して下さい。
		 */
		property String ^TessEvalShaderSource {
			String ^get(void);
			void set(String ^);
		}

		//! IDプロパティ
		/*!
		 *	GPU からシェーダープログラムに割り振られた ID を取得します。
		 *
		 *	\note
		 *		この ID は、具体的には OpenGL の関数である
		 *		glCreateProgram() による返値のことです。
		 */
		property UInt32 ProgramID { UInt32 get(void); };

		//! エラーメッセージプロパティ
		/*!
		 *	シェーダーに関するエラーが生じた場合に、
		 *	エラーメッセージの文字列をこのプロパティから取得できます。
		 */
		property String^ LastError { String^ get(void); };

		//! バーテックスシェーダーコード入力メソッド
		/*!
		 *	バーテックス(頂点)シェーダーのコードが記述されているファイルから、
		 *	コードを読み込みます。
		 *	読み込みに成功した場合、
		 *	fk_ShaderProgram.VertexShaderSource プロパティにその内容が格納されます。
		 *	なお、コードに誤りがあった場合でも、この時点では false を返しません。
		 *	実際に利用するには、 Validate() メソッドを呼ぶ必要があります。
		 *
		 *	\param[in]	fileName
		 *		ファイル名
		 *
		 *	\return
		 *		入力に成功すれば true を、失敗すれば false を返します。
		 */
		bool LoadVertexShader(String^ fileName);

		//! フラグメントシェーダーコード入力メソッド
		/*!
		 *	フラグメント(ピクセル)シェーダーのコードが記述されているファイルから、
		 *	コードを読み込みます。
		 *	読み込みに成功した場合、
		 *	fk_ShaderProgram.FragmentShaderSource プロパティにその内容が格納されます。
		 *	なお、コードに誤りがあった場合でも、この時点では false を返しません。
		 *	実際に利用するには、 Validate() メソッドを呼ぶ必要があります。
		 *
		 *	\param[in]	fileName
		 *		ファイル名
		 *
		 *	\return
		 *		入力に成功すれば true を、失敗すれば false を返します。
		 */
		bool LoadFragmentShader(String^ fileName);

		//! ジオメトリシェーダーコード入力メソッド
		/*!
		 *	ジオメトリシェーダーのコードが記述されているファイルから、
		 *	コードを読み込みます。
		 *	読み込みに成功した場合、
		 *	fk_ShaderProgram.GeometryShaderSource プロパティにその内容が格納されます。
		 *	なお、コードに誤りがあった場合でも、この時点では false を返しません。
		 *	実際に利用するには、 Validate() メソッドを呼ぶ必要があります。
		 *
		 *	\param[in]	fileName
		 *		ファイル名
		 *
		 *	\return
		 *		入力に成功すれば true を、失敗すれば false を返します。
		 */
		bool LoadGeometryShader(String^ fileName);

		//! テッセレーション制御シェーダーコード入力メソッド
		/*!
		 *	テッセレーション評価シェーダーのコードが記述されているファイルから、
		 *	コードを読み込みます。
		 *	読み込みに成功した場合、
		 *	fk_ShaderProgram.TessCtrlShaderSource プロパティにその内容が格納されます。
		 *	なお、コードに誤りがあった場合でも、この時点では false を返しません。
		 *	実際に利用するには、 Validate() 関数を呼ぶ必要があります。
		 *
		 *	\param[in]	fileName
		 *		ファイル名
		 *
		 *	\return
		 *		入力に成功すれば true を、失敗すれば false を返します。
		 */
		bool LoadTessCtrlShader(String^ fileName);

		//! テッセレーション評価シェーダーコード入力メソッド
		/*!
		 *	テッセレーション評価シェーダーのコードが記述されているファイルから、
		 *	コードを読み込みます。
		 *	読み込みに成功した場合、
		 *	fk_ShaderProgram.TessEvalShaderSource プロパティにその内容が格納されます。
		 *	なお、コードに誤りがあった場合でも、この時点では false を返しません。
		 *	実際に利用するには、 Validate() 関数を呼ぶ必要があります。
		 *
		 *	\param[in]	fileName
		 *		ファイル名
		 *
		 *	\return
		 *		入力に成功すれば true を、失敗すれば false を返します。
		 */
		bool LoadTessEvalShader(String^ fileName);

		//! シェーダープログラムコンパイルメソッド
		/*!
		 *	格納されているシェーダーコードのコンパイルを行います。
		 *
		 *	\return
		 *		コンパイルに成功すれば true を、失敗すれば false を返します。
		 *		失敗した場合は、
		 *		fk_ShaderProgram.LastError プロパティでエラーメッセージを参照できます。
		 */
		bool Validate(void);

		//! シェーダープログラムリンクメソッド
		/*!
		 *	コンパイル後、プログラムのリンクを実行します。
		 *	Attribute 変数等の定義はこの前に行っておく必要があります。
		 *
		 *	\return
		 *		リンクに成功すれば true を、失敗すれば false を返します。
		 *		失敗した場合は、 fk_ShaderProgram.LastError でエラーメッセージを取得できます。
		 */
		bool Link(void);
	};
}

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
