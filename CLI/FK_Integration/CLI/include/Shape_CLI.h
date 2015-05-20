// Shape_CLI.h

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

		//! マテリアルモード設定関数
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

		//! マテリアル配列取得関数
		/*!
		 *	パレットに格納されているマテリアル配列を参照します。
		 *
		 *	\return マテリアル配列
		 *
		 *	\sa GetMaterial()
		 */
		property array<fk_Material^>^ MaterialVector {
			array<fk_Material^>^ get();
		}
		
		//! パレット初期化関数
		/*!
		 *	現在設定されているパレットを初期化します。
		 *
		 *	\sa fk_Palette::ClearMaterial()
		 */
		void			ClearMaterial(void);

		//! マテリアル追加関数
		/*!
		 *	パレットにマテリアルを新たに追加します。
		 *
		 *	\param[in]	mat		追加するマテリアル変数のアドレス
		 *
		 *	\sa fk_Palette::PushPalette(), SetPalette()
		 */
		void			PushPalette(fk_Material^ mat);

		//! マテリアル設定関数
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

		//! マテリアル取得関数
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
