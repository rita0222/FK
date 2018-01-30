﻿// Shape_CLI.h

#pragma once

#include <FK/Shape.h>
#include "Attribute_CLI.h"
#include "Palette_CLI.h"

namespace FK_CLI
{
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
		::fk_Shape * GetP(void);

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

		//! パレットプロパティ
		/*!
		 *	パレットを参照します。
		 */
		property fk_Palette^ Palette {
			fk_Palette^ get();
		}

		//! マテリアルモード設定メソッド
		/*!
		 *	形状中の各要素を描画する際に、
		 *	どの要素のマテリアルを採用するかというモードの参照・設定を行います。
		 *	与えられる値は以下の3種類です。
		 *		\arg fk_MaterialMode.CHILD
		 *		\arg fk_MaterialMode.PARENT
		 *		\arg fk_MaterialMode.NONE
		 *
		 *	マテリアルの採用は、以下のような優先順で決定します。
		 *	-# fk_Model のマテリアルモードが fk_MaterialMode.CHILD の場合、
		 *		モデルのマテリアルが採用されます。
		 *		fk_MaterialMode.NONE の場合は描画されません。
		 *		fk_MaterialMode.PARENT の場合は以下の条件に従います。
		 *		(fk_Model::MaterialMode を参照して下さい。)
		 *	-# fk_Shape の派生クラスにてマテリアルモードが
		 *		fk_MaterialMode.CHILD になっている場合、形状のマテリアルが採用されます。
		 *		fk_MaterialMode.NONE の場合は描画されません。
		 *		fk_MaterialMode.PARENT の場合は以下の条件に従います。
		 *	-# 各位相要素でのマテリアルモードが、
		 *		fk_MaterialMode.CHILD になっている場合は個別のマテリアルが採用されます。
		 *		fk_MaterialMode.NONE の場合は描画されません。
		 *		fk_MaterialMode.PARENT の場合はモデルのマテリアルが採用されます。
		 *		(fk_TopologyMaterial::MaterialMode を参照して下さい。)
		 *
		 *	\sa fk_Model::MaterialMode, fk_TopologyMaterial::MaterialMode
		 */
		property fk_MaterialMode MaterialMode {
			fk_MaterialMode get();
			void set(fk_MaterialMode);
		}

		//! オブジェクトマテリアル ID プロパティ
		/*!
		 *	オブジェクトマテリアル ID の設定・参照を行います。
		 *
		 *	\sa fk_Palette::MaterialID
		 */
		property int MaterialID {
			int get();
			void set(int);
		}

		//! パレット中のマテリアル格納数プロパティ
		/*!
		 *	現在パレットに格納されているマテリアルの数を参照します。
		 *
		 *	\sa PushPalette(), SetPalette(), GetMaterial(), fk_Palette::Size
		 */
		property int PaletteSize {
			int get();
		}

		//! マテリアル配列取得メソッド
		/*!
		 *	パレットに格納されているマテリアル配列を参照します。
		 *
		 *	\return マテリアル配列
		 *
		 *	\sa GetMaterial()
		 */
		property cli::array<fk_Material^>^ MaterialVector {
			cli::array<fk_Material^>^ get();
		}
		
		//! パレット初期化メソッド
		/*!
		 *	現在設定されているパレットを初期化します。
		 *
		 *	\sa fk_Palette::ClearMaterial()
		 */
		void			ClearMaterial(void);

		//! マテリアル追加メソッド
		/*!
		 *	パレットにマテリアルを新たに追加します。
		 *
		 *	\param[in]	mat		追加するマテリアル変数のアドレス
		 *
		 *	\sa fk_Palette::PushPalette(), SetPalette()
		 */
		void			PushPalette(fk_Material^ mat);

		//! マテリアル設定メソッド
		/*!
		 *	パレットに対し、対応する ID でマテリアルを設定します。
		 *	詳細な仕様は fk_Palette::SetPalette() を参照して下さい。
		 *
		 *	\param[in]	mat		設定するマテリアル
		 *	\param[in]	ID		マテリアルID
		 *
		 *	\sa fk_Palette::SetPalette(), PushPalette()
		 */
		void			SetPalette(fk_Material^ mat, int ID);

		//! マテリアル取得メソッド
		/*!
		 *	指定された id に対応するマテリアルのポインタを返します。
		 *	id に対応するマテリアルがパレット中にない場合は、
		 * 	デフォルト状態のマテリアルインスタンスへのポインタを返します。
		 *
		 *	\return マテリアルのポインタ
		 *
		 *	\sa PushPalette(), SetPalette(), PaletteSize, fk_Palette::GetMaterial()
		 */
		fk_Material^	GetMaterial(int ID);
	};
}

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
