#ifndef __FK_SHADER_BINDER_HEADER__
#define __FK_SHADER_BINDER_HEADER__

//#define GLEW_STATIC
//#include <GL/glew.h>
#include <FK/AppWindow.h>
#include <FK/ShaderProgram.h>

namespace FK {
	//! シェーダープログラム統括クラス
	/*!
	 *	このクラスは、FK におけるシェーダー全体を統括する機能を提供します。
	 *	FK でシェーダーを扱う場合は、
	 *	基本的にはこの fk_ShaderBinder クラスによるインスタンスを用いて制御を行います。
	 *
	 *	このクラスの役割は大きく以下の3種類となります。
	 *		- シェーダープログラム管理: \n
	 *			getProgram() によって得られる fk_ShaderProgram 型インスタンスによって、
	 *			シェーダープログラムの設定を行います。
	 *		- シェーダーパラメーター管理: \n
	 *			getParamete() によって得られる fk_ShaderParameter 型インスタンスによって、
	 *			C++ 側からシェーダー側に渡すパラメーターを設定します。
	 *		- モデル管理: \n
	 *			シェーダーを適用するモデルを
	 *			bindModel() 関数
	 *			(FBO へ適用する場合は initializeFrameBufferObject() 関数)
	 *			を用いて設定します。
	 *
	 *	シェーダープログラムの設定については fk_ShaderProgram を、
	 *	シェーダーに渡すパラメータ設定については fk_ShaderParameter を参照して下さい。
	 *	また、入出力用テクスチャについては fk_TextureSampler を参照して下さい。
	 *
	 *	\sa fk_ShaderProgram, fk_ShaderParameter, fk_TextureSampler, fk_Model
	 */

	class fk_ShaderBinder
	{
	public:
		//! コンストラクタ1
		/*!
		 *	インスタンスを生成します。
		 *	シェーダープログラムおよびシェーダーパラメーターは何も設定されません。
		 */
		fk_ShaderBinder(void);

		//! コンストラクタ2
		/*!
		 *	インスタンスを生成する際に、
		 *	プログラムとパラメーターを初期設定するコンストラクタです。
		 *
		 *	\param[in]	prog
		 *		シェーダープログラム
		 *
		 *	\param[in]	param
		 *		シェーダーパラメーター
		 */
		fk_ShaderBinder(fk_ShaderProgram *prog, fk_ShaderParameter *param);

		//! デストラクタ
		~fk_ShaderBinder();

		//! シェーダープログラム参照関数
		/*!
		 *	シェーダープログラムを格納する、 fk_ShaderProgram 型インスタンスを参照します。
		 *	シェーダープログラムの設定はこのインスタンスを利用して行います。
		 *	詳細は fk_ShaderProgram のマニュアルを参照して下さい。
		 *
		 *	\return	  現在設定されている fk_ShaderProgram 型インスタンス
		 *
		 *	\sa fk_ShaderProgram, setProgram()
		 */
		fk_ShaderProgram *getProgram(void);

		//! シェーダープログラム設定関数
		/*!
		 *	シェーダープログラムを設定します。
		 *	fk_ShaderBinder はインスタンスを生成すると、
		 *	内部に fk_ShaderProgram インスタンスを確保しますので、
		 *	通常はこの関数を用いる必要はありません。
		 *	他の fk_ShaderBinder 型インスタンスのシェーダープログラムを流用したい場合や、
		 *	fk_ShaderProgram インスタンスを複数の
		 *	fk_ShaderBinder インスタンスで共有したい場合に用いて下さい。
		 *
		 *	\param[in]	program
		 *		新たに設定する fk_ShaderProgram 型インスタンス
		 *
		 *	\sa fk_ShaderProgram, getProgram()
		 */
		void setProgram(fk_ShaderProgram *program);

		//! シェーダーパラメーター参照関数
		/*!
		 *	シェーダーパラメーターを格納する、 fk_ShaderParameter 型インスタンスを参照します。
		 *	シェーダーへのパラメーターの設定はこのインスタンスを利用して行います。
		 *	詳細は fk_ShaderParametern のマニュアルを参照して下さい。
		 *
		 *	\return	  現在設定されている fk_ShaderParameter 型インスタンス
		 *
		 *	\sa fk_ShaderParameter, setParameter()
		 */
		fk_ShaderParameter *getParameter(void);

		//! シェーダーパラメーター設定関数
		/*!
		 *	シェーダープログラムを設定します。
		 *	詳細は fk_ShaderParameter のマニュアルを参照して下さい。
		 *
		 *	\param[in]	param
		 *		新たに設定する fk_ShaderParameter 型インスタンス
		 *
		 *	\sa fk_ShaderParameter, getParameter()
		 */
		void setParameter(fk_ShaderParameter *param);

	
		//! シェーダーモデル連携設定関数
		/*!
		 *	設定されているシェーダープログラムを適用するモデルを設定します。
		 *	1つの fk_ShaderBinder インスタンスによるプログラムを、
		 *	複数のモデルに対して適用することが可能です。
		 *	モデルへのシェーダー適用を外すには、 unbindModel() 関数を利用して下さい。
		 *
		 *	また、1つのモデルに対し、複数のシェーダーを適用することも可能です。
		 *	その場合は、 bindModel() によって適用した順番に処理がなされます。
		 *
		 *	\param[in]	model
		 *		シェーダー適用モデルインスタンス
		 */
		void bindModel(fk_Model *model);

		//! シェーダーモデル連携解除関数
		/*!
		 *	bindModel() 関数によってシェーダーを適用したモデルに対し、
		 *	適用を外します。
		 *
		 *	\param[in]	model
		 *		シェーダー適用済モデルインスタンス
		 */
		void unbindModel(fk_Model *model);

		//! フレームバッファーオブジェクト (FBO) 初期化関数1
		/*!
		 *	シェーダー内でフレームバッファーオブジェクト
		 *	(FBO) を利用する際の初期化を行います。
		 *	この関数を呼ぶことで、
		 *	FBO にアクセスするシェーダープログラムを利用することができます。
		 *
		 *	本関数を用いたあと、実際に画面に出力を行うには
		 *	bindWindow() メソッドで連携を行う必要があります。
		 *
		 *	\param[in]	width
		 *		FBO の横幅
		 *
		 *	\param[in]	height
		 *		FBO の縦幅
		 *
		 *	\sa bindWindow(), finalizeFrameBufferObject()
		 */
		void initializeFrameBufferObject(int width, int height);

		//! フレームバッファーオブジェクト (FBO) 初期化関数2
		/*!
		 *	シェーダー内でフレームバッファーオブジェクト
		 *	(FBO) を利用する際の初期化を行います。
		 *	この関数を呼ぶことで、
		 *	FBO にアクセスするシェーダープログラムを利用することができます。
		 *
		 *	\param[in]	dim
		 *		FBO の横幅と縦幅を表す fk_Dimension 型インスタンス
		 *
		 *	\sa bindWindow(), finalizeFrameBufferObject()
		 */
		void initializeFrameBufferObject(fk_Dimension dim);

		//! フレームバッファーオブジェクト (FBO) 利用終了関数
		/*!
		 *	フレームバッファーオブジェクト (FBO) の利用を終了します。
		 *
		 *	\sa initializeFrameBufferObject(int, int),
		 *			initializeFrameBufferObject(fk_Dimension)
		 */
		void finalizeFrameBufferObject();
	
		//! ウィンドウ連携設定関数1
		/*!
		 *	フレームバッファーオブジェクト
		 *	(FBO) を処理するシェーダーの出力を、
		 *	ウィンドウに表示するよう連携する設定を行います。
		 *
		 *	\param[in]	window
		 *		FBO用シェーダーの出力を表示するウィンドウの fk_Window 型インスタンス
		 *
		 *	\sa initializeFrameBufferObject(int, int),
		 *			initializeFrameBufferObject(fk_Dimension *),
		 *			unbindWindow(fk_Window *), bindWindow(fk_AppWindow *)
		 */
		void bindWindow(fk_Window *window);

		//! ウィンドウ連携設定関数2
		/*!
		 *	フレームバッファーオブジェクト
		 *	(FBO) を処理するシェーダーの出力を、
		 *	ウィンドウに表示するよう連携する設定を行います。
		 *
		 *	\param[in]	window
		 *		FBO用シェーダーの出力を表示するウィンドウの fk_AppWindow 型インスタンス
		 *
		 *	\sa initializeFrameBufferObject(int, int),
		 *			initializeFrameBufferObject(fk_Dimension *),
		 *			unbindWindow(fk_AppWindow *), bindWindow(fk_Window *)
		 */
		void bindWindow(fk_AppWindow *window);

		//! ウィンドウ連携解除メソッド1
		/*!
		 *	bindWindow() メソッドによって設定していた連携を解除します。
		 *
		 *	\param[in]	window
		 *		bindWindow() メソッドで連携設定を行っていたウィンドウの
		 *		fk_Window 型インスタンス
		 *
		 *	\sa bindWindow(fk_Window *), unbindWindow(fk_AppWindow *)
		 */
		void unbindWindow(fk_Window *window);

		//! ウィンドウ連携解除メソッド2
		/*!
		 *	bindWindow() メソッドによって設定していた連携を解除します。
		 *
		 *	\param[in]	window
		 *		bindWindow() メソッドで連携設定を行っていたウィンドウの
		 *		fk_AppWindow 型インスタンス
		 *
		 *	\sa bindWindow(fk_AppWindow *), unbindWindow(fk_Window *)
		 */
		void unbindWindow(fk_AppWindow *window);

#ifndef FK_DOXYGEN_USER_PROCESS
		static bool Initialize(void);
#endif
	
	private:
		void ProcPreShader(void);
		void ProcPostShader(void);

		fk_ShaderProgram innerProgram;
		fk_ShaderParameter innerParameter;

		fk_ShaderProgram *program;
		fk_ShaderParameter *parameter;

		static bool	isExtensionInitialized;
		bool usingProgram;

		void ProcPreDraw(void);
		void ProcPostDraw(void);
		GLuint	fboID;
		GLuint	texID;
		GLuint	depthTexID;
		GLint	bufW;
		GLint	bufH;
	};
}

#endif

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
