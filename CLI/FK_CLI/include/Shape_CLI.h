#pragma once

#include <FK/Shape.h>
#include "Attribute_CLI.h"
#include "Vector_CLI.h"
#include "TexCoord_CLI.h"

namespace FK_CLI
{
	using namespace System::Collections::Generic;

	//! 形状データの具体的なデータ構造を表す列挙型
	public enum class fk_RealShapeType {
		IFS,		//!<	fk_IndexFaceSetベース
		SOLID,		//!<	fk_Solidベース
		TEXTURE,	//!<	fk_Textureベース
		POINT,		//!<	fk_Pointベース
		LIGHT,		//!<	fk_Lightベース
		OTHER		//!<	その他
	};

	//! 形状用基底クラス
	/*!
	 *	このクラスは、形状を表すクラスの基底クラスです。
	 *	クラス自体の主な機能は、マテリアルやパレットの管理です。
	 *
	 *	\sa fk_Material, fk_Palette
	 */
	public ref class fk_Shape : fk_Attribute {
	internal:
		::FK::fk_Shape * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Shape(bool argNewFlg);
		~fk_Shape();
		!fk_Shape();
#endif
		
		//!	形状データ構造プロパティ
		/*!
		 *
		 *	格納されているインスタンスの具体的なデータ構造を参照します。
		 */
		property fk_RealShapeType^ RealShapeType {
			fk_RealShapeType^ get();
		}

		//! シェーダー内 attribute 変数設定メソッド1
		/*!
		 *	形状の各頂点に対応した attribute 変数値を整数型で登録します。
		 *	ここで登録する要素数は形状の頂点数、
		 *	厳密にはデータ要素数よりも多数である必要があります。
		 *
		 *	\param[in]	name
		 *		GLSL内での変数名
		 *
		 *	\param[in]	dim
		 *		変数の次元数で、1から4まで設定することができます。
		 *		GLSL内での型は、1から順に int, ivec2, ivec3, ivec4 となります。
		 *
		 *	\param[in]	array
		 *		attribute 変数として転送するデータ。
		 *		このコレクションのサイズは、形状の頂点数と次元数の積以上である必要があります。
		 *
		 *	\note
		 *	   	ここで設定した attribute 変数用データに変更があった場合は、
		 *		再度本メソッドを使用する必要があります。
		 */
		void SetShaderAttribute(String^ name, int dim, IEnumerable<int>^ array);

		//! シェーダー内 attribute 変数設定メソッド2
		/*!
		 *	形状の各頂点に対応した attribute 変数値を 32bit 浮動小数点型で登録します。
		 *	ここで登録する要素数は形状の頂点数、
		 *	厳密にはデータ要素数よりも多数である必要があります。
		 *
		 *	\param[in]	name
		 *		GLSL内での変数名
		 *
		 *	\param[in]	dim
		 *		変数の次元数で、1から4まで設定することができます。
		 *		GLSL内での型は、1から順に float, vec2, vec3, vec4 となります。
		 *
		 *	\param[in]	array
		 *		attribute 変数として転送するデータ。
		 *		このコレクションのサイズは、形状の頂点数と次元数の積以上である必要があります。
		 *
		 *	\note
		 *	   	ここで設定した attribute 変数用データに変更があった場合は、
		 *		再度本メソッドを使用する必要があります。
		 */
		void SetShaderAttribute(String^ name, int dim, IEnumerable<float>^ array);

		//! シェーダー内 attribute 変数設定メソッド3
		/*!
		 *	形状の各頂点に対応した attribute 変数値を 64bit 浮動小数点型で登録します。
		 *	ここで登録する要素数は形状の頂点数、
		 *	厳密にはデータ要素数よりも多数である必要があります。
		 *
		 *	\param[in]	name
		 *		GLSL内での変数名		 
		 *
		 *	\param[in]	dim
		 *		変数の次元数で、1から4まで設定することができます。
		 *		GLSL内での型は、1から順に float, vec2, vec3, vec4 となります。
		 *
		 *	\param[in]	array
		 *		attribute 変数として転送するデータ。
		 *		このコレクションのサイズは、形状の頂点数と次元数の積以上である必要があります。
		 *
		 *	\note
		 *	   	ここで設定した attribute 変数用データに変更があった場合は、
		 *		再度本メソッドを使用する必要があります。
		 */
		void SetShaderAttribute(String^ name, int dim, IEnumerable<double>^ array);

		//! シェーダー内 attribute 変数設定メソッド4
		/*!
		 *	形状の各頂点に対応した attribute 変数値を fk_Vector^ 型で登録します。
		 *	ここで登録する要素数は形状の頂点数、
		 *	厳密にはデータ要素数よりも多数である必要があります。
		 *
		 *	\param[in]	name
		 *		GLSL内での変数名
		 *
		 *	\param[in]	dim
		 *		変数の次元数で、1から4まで設定することができます。
		 *		GLSL内での型は、1から順に float, vec2, vec3, vec4 となります。
		 *		1 を指定した場合、y,z 成分は無視されます。
		 *		2 を指定した場合、z 成分は無視されます。
		 *		4 を指定した場合、第4成分 (w成分) は 0 となります。
		 *
		 *	\param[in]	array
		 *		attribute 変数として転送するデータ。
		 *		このコレクションのサイズは、形状の頂点数と次元数の積以上である必要があります。
		 *
		 *	\note
		 *	   	ここで設定した attribute 変数用データに変更があった場合は、
		 *		再度本メソッドを使用する必要があります。
		 */
		void SetShaderAttribute(String^ name, int dim, IEnumerable<fk_Vector^>^ array);

		//! シェーダー内 attribute 変数設定メソッド5
		/*!
		 *	形状の各頂点に対応した attribute 変数値を fk_TexCoord^ 型で登録します。
		 *	ここで登録する要素数は形状の頂点数、
		 *	厳密にはデータ要素数よりも多数である必要があります。
		 *
		 *	\param[in]	name
		 *		GLSL内での変数名
		 *
		 *	\param[in]	dim
		 *		変数の次元数で、1から4まで設定することができます。
		 *		GLSL内での型は、1から順に float, vec2, vec3, vec4 となります。
		 *		1 を指定した場合、y 成分は無視されます。
		 *		3,4 を指定した場合、第3,4成分 (z,w成分) は 0 となります。
		 *
		 *	\param[in]	array
		 *		attribute 変数として転送するデータ。
		 *		このコレクションのサイズは、形状の頂点数と次元数の積以上である必要があります。
		 *
		 *	\note
		 *	   	ここで設定した attribute 変数用データに変更があった場合は、
		 *		再度本メソッドを使用する必要があります。
		 */
		void SetShaderAttribute(String^ name, int dim, IEnumerable<fk_TexCoord^>^ array);

		//! シェーダー内 attribute 変数設定メソッド6
		/*!
		 *	形状の各頂点に対応した attribute 変数値を fk_Vector^ 型で登録します。
		 *	ここで登録する要素数は形状の頂点数、
		 *	厳密にはデータ要素数よりも多数である必要があります。
		 *
		 *	\param[in]	name
		 *		GLSL内での変数名
		 *
		 *	\param[in]	dim
		 *		変数の次元数で、1から4まで設定することができます。
		 *		GLSL内での型は、1から順に float, vec2, vec3, vec4 となります。
		 *		1 を指定した場合は y,z,w 成分は無視されます。
		 *		2 を指定した場合は z,w 成分は無視されます。
		 *		3 を指定した場合は、w 成分は無視されま。
		 *
		 *	\param[in]	array
		 *		attribute 変数として転送するデータ。
		 *		このコレクションのサイズは、形状の頂点数と次元数の積以上である必要があります。
		 *
		 *	\note
		 *	   	ここで設定した attribute 変数用データに変更があった場合は、
		 *		再度本メソッドを使用する必要があります。
		 */
		void SetShaderAttribute(String^ name, int dim, IEnumerable<fk_HVector^>^ array);
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
