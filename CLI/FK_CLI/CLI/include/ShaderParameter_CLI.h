#pragma once

#include <FK/ShaderParameter.h>
#include "Texture_CLI.h"
#include "Matrix_CLI.h"

//using namespace FK_CLI;
using namespace System;
using namespace System::Collections::Generic;

namespace FK_CLI
{
	//! シェーダーパラメーター管理クラス
	/*!
	 *	このクラスは、シェーダープログラムに対してパラメーターを渡すための機能を提供します。
	 *	本クラスは単独のインスタンスとしてはあまり利用用途はなく、
	 *	fk_ShaderBinder クラスの fk_ShaderBinder.Parameter
	 *	プロパティとして利用することがほとんどです。
	 *
	 *	\sa fk_ShaderBinder, fk_ShaderParameter, fk_Texture
	 */

	public ref class fk_ShaderParameter
	{

	internal:
		bool dFlg;
		::FK::fk_ShaderParameter *pParam;
		::FK::fk_ShaderParameter * GetP(void);

	public:

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_ShaderParameter(bool);
		fk_ShaderParameter(::FK::fk_ShaderParameter *);
#endif

		//! コンストラクタ
		fk_ShaderParameter();

		//! デストラクタ
		~fk_ShaderParameter();

		//! ファイナライザ
		!fk_ShaderParameter();

		//! エラーメッセージプロパティ
		/*!
		 *	シェーダーに関するエラーが生じた場合に、
		 *	エラーメッセージの文字列をこのプロパティから取得できます。
		 */
		property String^ LastError { String^ get(void); };

		//! float 型 uniform 変数設定メソッド
		/*!
		 *	このメソッドは、バーテックスシェーダーやフラグメントシェーダーに対し、
		 *	float 型の uniform 変数を渡す設定を行います。
		 *
		 *	\param[in]	name
		 *		GLSL コード内での変数名
		 *
		 *	\param[in]	value
		 *		uniform 変数に渡す値
		 */
		void Register(String^ name, float value);

		//! float 配列型 uniform 変数設定メソッド
		/*!
		 *	このメソッドは、バーテックスシェーダーやフラグメントシェーダーに対し、
		 *	float 配列型の uniform 変数を渡す設定を行います。 
		 *	配列のサイズは 1 から 4 までで、
		 *	GLSL 内での型は配列サイズが 1 から順に float, vec2, vec3, vec4 となります。
		 *
		 *	\param[in]	name
		 *		GLSL コード内での変数名
		 *
		 *	\param[in]	value
		 *		uniform 変数に渡す配列
		 */
		void Register(String^ name, cli::array<float>^ value);

		//! int 型 uniform 変数設定メソッド
		/*!
		 *	このメソッドは、バーテックスシェーダーやフラグメントシェーダーに対し、
		 *	int 型の uniform 変数を渡す設定を行います。
		 *
		 *	\param[in]	name
		 *		GLSL コード内での変数名
		 *
		 *	\param[in]	value
		 *		uniform 変数に渡す値
		 */
		void Register(String^ name, int value);

		//! int 配列型 uniform 変数設定メソッド
		/*!
		 *	このメソッドは、バーテックスシェーダーやフラグメントシェーダーに対し、
		 *	int 配列型の uniform 変数を渡す設定を行います。
		 *	配列のサイズは 1 から 4 までで、
		 *	GLSL 内での型は配列サイズが 1 から順に int, ivec2, ivec3, ivec4 となります。
		 *
		 *	\param[in]	name
		 *		GLSL コード内での変数名
		 *
		 *	\param[in]	value
		 *		uniform 変数に渡す配列
		 */
		void Register(String^ name, cli::array<int>^ value);
		
		//! 行列型 uniform 変数設定メソッド
		/*!
		 *	このメソッドは、バーテックスシェーダーやフラグメントシェーダーに対し、
		 *	行列型の uniform 変数を渡す設定を行います。
		 *	このメソッドの引数は fk_Matrix 型変数となり、
		 *	GLSL コード内での型は mat4 となります。
		 *
		 *	\param[in]	name
		 *		GLSL コード内での変数名
		 *
		 *	\param[in]	value
		 *		uniform 変数に渡す行列
		 */
		void Register(String^ name, fk_Matrix^ value);

		//! uniform 変数解除メソッド
		/*!
		 *	各種 Register() メソッドで設定した uniform 変数を解除します。
		 *
		 *	\param[in]	name
		 *		GLSL コード内での変数名
		 *
		 *	\return
		 *		uniform 変数が存在していた場合は解除し true を返します。
		 *		変数が存在していなかった場合は false を返します。
		 */
		bool Unregister(String^ name);

		//! Attribute 変数予約関数
		/*!
		 *	Attribute 変数用の名前を予約します。
		 *
		 *	\param[in]	name
		 *		GLSL コード内での変数名
		 */
		void ReserveAttribute(String^ name);

		//! 参照テクスチャ設定メソッド
		/*!
		 *	GLSLコード内の参照テクスチャを設定します。
		 *	ここで設定したテクスチャは、
		 *	GLSL内では sampler2D 型 uniform 変数として扱われます。
		 *	複数のテクスチャを設定した場合、
		 *	GLSLコード内で変数を宣言した順番に割り振られます。
		 *
		 *	\param[in]	unit
		 *		シェーダー内でのテクスチャ ID を指定します。
		 *		0 から 31 までを指定することができます。
		 *		既に使用している ID を用いた場合、
		 *		前にその ID を用いていたテクスチャの設定は破棄されます。
		 *		GLSLコード内では、複数の sampler2D 変数に対し ID の若い順に割り振られます。
		 *
		 *	\param[in]	texture
		 *		テクスチャオブジェクト。詳細は fk_TextureSampler を参照して下さい。
		 *
		 *	\return
		 *		設定に成功すれば true を、失敗すれば false を返します。
		 */
		bool AttachTexture(int unit, fk_Texture^ texture);

		//! 参照テクスチャ解除メソッド
		/*!
		 *	AttachTexture() メソッドにて設定した参照テクスチャを解除します。
		 *
		 *	\param[in]	unit
		 *		テクスチャ ID
		 *
		 *	\return
		 *		解除に成功すれば true を、失敗すれば false を返します。
		 */
		bool DetachTexture(int unit);

		//! 参照テクスチャ全解除関数
		/*!
		 *	AttachTexture() メソッドにて設定した参照テクスチャを全て解除します。
		 */
		void ClearTexture(void);
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
