﻿/****************************************************************************
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
#ifndef __FK_SHADER_PROGRAM_HEADER__
#define __FK_SHADER_PROGRAM_HEADER__

#include <FK/Engine.H>
#include <FK/ShaderParameter.h>

namespace FK {

	using fk_KeyPair = std::pair<std::string, std::string>;
	
	//! シェーダープログラム格納クラス
	/*!
	 *	このクラスは、シェーダーのプログラムソースを格納するための機能を提供します。
	 *	インスタンス内部でバーテックス(頂点)シェーダーと
	 *	フラグメント(ピクセル)シェーダーのソースコードを管理します。
	 *	本クラスは単独のインスタンスとしてはあまり利用用途はなく、
	 *	fk_ShaderBinder::getProgram() を介して利用することがほとんどです。
	 *
	 *	\sa fk_ShaderBinder, fk_ShaderParameter, fk_TextureSampler
	 */
	class fk_ShaderProgram {

	public:
		//! バーテックスシェーダーコードメンバー
		/*!
		 *	バーテックス(頂点)シェーダーのコードの設定や取得を行います。
		 *	バーテックスシェーダーのコードを設定する際は、
		 *	本メンバーに直接コードを書き込むか、
		 *	loadVertexShader() 関数でコードが格納されているファイル名を指定して下さい。
		 */
		std::string vertexShaderSource;

		//! フラグメントシェーダーコードメンバー
		/*!
		 *	フラグメント(ピクセル)シェーダーのコードの設定や取得を行います。
		 *	フラグメントシェーダーのコードを設定する際は、
		 *	本メンバーに直接コードを書き込むか、
		 *	loadVertexShader() 関数でコードが格納されているファイル名を指定して下さい。
		 */
		std::string fragmentShaderSource;

		//! ジオメトリシェーダーコードメンバー
		/*!
		 *	ジオメトリシェーダーのコードの設定や取得を行います。
		 *	ジオメトリシェーダーのコードを設定する際は、
		 *	本メンバーに直接コードを書き込むか、
		 *	loadGeometryShader() 関数でコードが格納されているファイル名を指定して下さい。
		 */
		std::string geometryShaderSource;

		std::string tessCtrlShaderSource;
		std::string tessEvalShaderSource;

		//! コンストラクタ
		fk_ShaderProgram(void);

		//! デストラクタ
		~fk_ShaderProgram();

		//! ID取得関数
		/*!
		 *	GPU からシェーダープログラムに割り振られた ID を取得します。
		 *
		 *	\note
		 *		この ID は、具体的には OpenGL の関数である
		 *		glCreateProgram() による返値のことです。
		 *
		 *	\return プログラムID
		 */
		GLuint getProgramID(void);

		//! エラーメッセージ取得関数
		/*!
		 *	シェーダーに関するエラーが生じた場合に、
		 *	エラーメッセージの文字列をこの関数で取得します。
		 *
		 *	\return エラーメッセージ文字列
		 */
		std::string getLastError(void);

		//! バーテックスシェーダーコード入力関数
		/*!
		 *	バーテックス(頂点)シェーダーのコードが記述されているファイルから、
		 *	コードを読み込みます。
		 *	読み込みに成功した場合、
		 *	fk_ShaderProgram::vertexShaderSource メンバーにその内容が格納されます。
		 *	なお、コードに誤りがあった場合でも、この時点では false を返しません。
		 *	実際に利用するには、 validate() 関数を呼ぶ必要があります。
		 *
		 *	\param[in]	fileName
		 *		ファイル名
		 *
		 *	\return
		 *		入力に成功すれば true を、失敗すれば false を返します。
		 */
		bool loadVertexShader(std::string fileName);

		//! フラグメントシェーダーコード入力関数
		/*!
		 *	フラグメント(ピクセル)シェーダーのコードが記述されているファイルから、
		 *	コードを読み込みます。
		 *	読み込みに成功した場合、
		 *	fk_ShaderProgram::fragmentShaderSource メンバーにその内容が格納されます。
		 *	なお、コードに誤りがあった場合でも、この時点では false を返しません。
		 *	実際に利用するには、 validate() 関数を呼ぶ必要があります。
		 *
		 *	\param[in]	fileName
		 *		ファイル名
		 *
		 *	\return
		 *		入力に成功すれば true を、失敗すれば false を返します。
		 */
		bool loadFragmentShader(std::string fileName);

		//! ジオメトリシェーダーコード入力関数
		/*!
		 *	ジオメトリシェーダーのコードが記述されているファイルから、
		 *	コードを読み込みます。
		 *	読み込みに成功した場合、
		 *	fk_ShaderProgram::geometryShaderSource メンバーにその内容が格納されます。
		 *	なお、コードに誤りがあった場合でも、この時点では false を返しません。
		 *	実際に利用するには、 validate() 関数を呼ぶ必要があります。
		 *
		 *	\param[in]	fileName
		 *		ファイル名
		 *
		 *	\return
		 *		入力に成功すれば true を、失敗すれば false を返します。
		 */
		bool loadGeometryShader(std::string fileName);


		bool loadTessCtrlShader(std::string fileName);
		bool loadTessEvalShader(std::string fileName);

		//! シェーダープログラムコンパイルメソッド
		/*!
		 *	fk_ShaderProgram::vertexShaderSource, fk_ShaderProgram::fragmentShaderSource,
		 *	fk_ShaderProgram::geometryShaderSource 
		 *	に格納されているコードのコンパイルを行います。
		 *
		 *	\return
		 *		コンパイルに成功すれば true を、失敗すれば false を返します。
		 *		失敗した場合は、 getLastError() でエラーメッセージを取得できます。
		 */
		bool validate(void);

		//! シェーダープログラムリンクメソッド
		/*!
		 *	コンパイル後、プログラムのリンクを実行します。
		 *	Attribute 変数等の定義はこの前に行っておく必要があります。
		 *
		 *	\return
		 *		リンクに成功すれば true を、失敗すれば false を返します。
		 *		失敗した場合は、 getLastError() でエラーメッセージを取得できます。
		 */
		bool link(void);

#ifndef FK_DOXYGEN_USER_PROCESS
		void SetParameter(fk_ShaderParameter *);
		void SetFBOMode(bool);

		void FindBuildIn(void);
#endif

	private:
		GLuint idProgram;
		GLuint idVertex;
		GLuint idFragment;
		GLuint idGeometry;
		GLuint idTessCtrl;
		GLuint idTessEval;
		
		std::string lastError;
		fk_ShaderParameter *parameter;
		bool fboMode;

		static std::string vertexBuildIn;
		static std::string fragmentBuildIn;
		static std::string geometryBuildIn;
		static std::string fboBuildIn;

		static std::vector<fk_KeyPair>	uniformStack;
		static std::vector<fk_KeyPair>	attributeStack;

		GLuint Compile(std::string *, GLuint);
		bool UpdateLastError(GLuint, std::string);
		void ReplaceBuildIn(std::string *, GLuint);
		void DeleteShader(GLuint);
		void DeleteProgram(GLuint);

		void MakeBuildInStack(std::string *, std::vector<fk_KeyPair> *, std::string);
	};
}
#endif


