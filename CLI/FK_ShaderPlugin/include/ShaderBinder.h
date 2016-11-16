#pragma once

#include "ShaderProgram.h"
#include "ShaderParameter.h"

using namespace System;
using namespace FK_CLI;

namespace FK_ShaderPlugin
{
	//! シェーダープログラム統括クラス
	/*!
	 *	このクラスは、FK におけるシェーダー全体を統括する機能を提供します。
	 *	FK でシェーダーを扱う場合は、
	 *	基本的にはこの fk_ShaderBinder クラスによるインスタンスを用いて制御を行います。
	 *
	 *	このクラスの役割は大きく以下の3種類となります。
	 *		- シェーダープログラム管理: \n
	 *			fk_ShaderBinder.Program プロパティを用いて、
	 *			シェーダープログラムの設定を行います。
	 *		- シェーダーパラメーター管理: \n
	 *			fk_ShaderBinder.Parameter プロパティを用いて、
	 *			C# 側からシェーダー側に渡すパラメーターを設定します。
	 *		- モデル管理: \n
	 *			シェーダーを適用するモデルを
	 *			BindModel() メソッド
	 *			(FBO へ適用する場合は InitializeFrameBufferObject() メソッド)
	 *			を用いて設定します。
	 *
	 *	fk_ShaderBinder.Program プロパティの扱い方については fk_ShaderProgram を、
	 *	fk_ShaderBinder.Parameter プロパティの扱い方については
	 *	fk_ShaderParameter を参照して下さい。
	 *	また、入出力用テクスチャについては fk_TextureSampler を参照して下さい。
	 *
	 *	\sa fk_ShaderProgram, fk_ShaderParameter, fk_TextureSampler, FK_CLI::fk_Model
	 */

   public ref class fk_ShaderBinder
	{
	public:
		//! コンストラクタ1
		/*!
		 *	インスタンスを生成します。
		 *	シェーダープログラムおよびシェーダーパラメーターは何も設定されません。
		 */
		fk_ShaderBinder();

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
		fk_ShaderBinder(fk_ShaderProgram^ prog, fk_ShaderParameter^ param);

		//! デストラクタ
		~fk_ShaderBinder();

		//! シェーダープログラムプロパティ
		/*!
		 *	シェーダープログラムを設定します。
		 *	詳細は fk_ShaderProgram のマニュアルを参照して下さい。
		 */
		property fk_ShaderProgram^ Program;

		//! シェーダーパラメータープロパティ
		/*!
		 *	シェーダープログラムに渡すパラメーターを設定します。
		 *	詳細は fk_ShaderParameter のマニュアルを参照して下さい。
		 */
		property fk_ShaderParameter^ Parameter;

		//! シェーダーモデル連携設定関数
		/*!
		 *	Program プロパティに設定されているシェーダープログラムを適用するモデルを設定します。
		 *	1つの fk_ShaderBinder インスタンスによるプログラムを、
		 *	複数のモデルに対して適用することが可能です。
		 *	モデルへのシェーダー適用を外すには、 UnbindModel() メソッドを利用して下さい。
		 *
		 *	また、1つのモデルに対し、複数のシェーダーを適用することも可能です。
		 *	その場合は、 BindModel() によって適用した順番に処理がなされます。
		 *
		 *	\param[in]	model
		 *		シェーダー適用モデルインスタンス
		 */
		void BindModel(fk_Model^ model);

		//! シェーダーモデル連携解除関数
		/*!
		 *	BindModel() メソッドによってシェーダーを適用したモデルに対し、
		 *	適用を外します。
		 *
		 *	\param[in]	model
		 *		シェーダー適用済モデルインスタンス
		 */
		void UnbindModel(fk_Model^ model);

		void InitializeFrameBufferObject(int width, int height);
		void FinalizeFrameBufferObject();
		void BindWindow(fk_IBindableDrawer^ window);
		void UnbindWindow(fk_IBindableDrawer^ window);

	internal:
		static bool Initialize(void);

	private:
		void ProcPreShader(void);
		void ProcPostShader(void);

		fk_ShaderProgram^ innerProgram = nullptr;
		fk_ShaderParameter^ innerParameter = nullptr;

		static bool	isExtensionInitialized = false;
		bool usingProgram = false;

		void ProcPreDraw(void);
		void ProcPostDraw(void);
		UInt32	fboID;
		UInt32	texID;
		UInt32	depthTexID;
		UInt32	rendID;
		Int32	bufW;
		Int32	bufH;
	};
}


/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
