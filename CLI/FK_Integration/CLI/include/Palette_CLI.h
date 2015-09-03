// Palette_CLI.h

#pragma once

#include <FK/Palette.h>
#include "Material_CLI.h"

namespace FK_CLI
{
	//! マテリアルモードを表す列挙型
	public enum class fk_MaterialMode : int {
		NONE = 0,		//!<	不描画モード
		CHILD = 1,		//!<	個別設定モード
		PARENT = 2		//!<	モデル設定モード
	};

	//! マテリアルパレットを管理するクラス
	/*!
	 *	このクラスは、マテリアルパレットを制御する機能を提供します。
	 *	「マテリアルパレット」とは、複数のマテリアルを管理するデータベースのことです。
	 *	水彩や油彩で使う「パレット」のような機能を保持しており、
	 *	複数のマテリアルを登録することができます。
	 *
	 *	\sa fk_Material, fk_Color, fk_Shape
	 */
	public ref class fk_Palette {
	internal:
		::fk_Palette *pPalette;
		bool dFlg;
		
		::fk_Palette * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Palette(bool argNewFlg);
#endif

		//! コンストラクタ
		fk_Palette();

		//! デストラクタ
		~fk_Palette();

		//! ファイナライザ
		!fk_Palette();

		//! オブジェクトマテリアル ID プロパティ
		/*!
		 *	オブジェクトマテリアル ID の参照・設定を行います。
		 */
		property int MaterialID {
			void set(int);
			int get();
		}

		//! パレット中のマテリアル格納数プロパティ
		/*!
		 *	現在パレットに格納されているマテリアルの数を参照します。
		 *
		 *	\return マテリアル数
		 *
		 *	\sa PushPalette(), SetPalette(), GetMaterial()
		 */
		property int Size {
			int get();
		}

		//! マテリアル配列プロパティ
		/*!
		 *	パレットに格納されているマテリアルを、配列として参照します。
		 *
		 *	\sa GetMaterial()
		 */
		property cli::array<fk_Material^>^ MaterialVector {
			cli::array<fk_Material^>^ get();

		}

		//! 初期化関数
		/*!
		 *	パレットを初期化します。
		 */
		void ClearMaterial(void);

		//! マテリアル追加関数
		/*!
		 *	パレットにマテリアルを新たに追加します。
		 *	追加するマテリアルの ID は、
		 *	この関数を呼ぶ前に PaletteSize プロパティを参照することで得られます。
		 *	以下のコードは、マテリアルを追加しその ID を引数に代入します。
		 *
		 *		fk_Palette		pal = new fk_Palette();
		 *		fk_Material		mat = new fk_Material();
		 *		int				id;
		 *		
		 *		id = pal.Size;
		 *		pal.PushPalette(mat);
		 *
		 *	\param[in]	material		追加するマテリアル
		 *
		 *	\sa SetPalette()
		 */
		void PushPalette(fk_Material^ material);

		//! マテリアル設定関数
		/*!
		 *	パレットに対し、対応する ID でマテリアルを設定します。
		 *	ID の指定により、以下のように挙動が若干変わります。
		 *	- もし ID が負であった場合は、パレットは何も変化しません。
		 *	- もし ID で指定されているマテリアルが既にパレット中に存在する場合は、
		 *		旧マテリアルを破棄して新しいマテリアルで上書きします。
		 *	- もし ID が新規のものであった場合、
		 *		その ID で新たに登録します。
		 *	.
		 *
		 *	\param[in]	material	設定するマテリアル
		 *	\param[in]	ID			マテリアルID
		 *
		 *	\sa PushPalette()
		 */
		void SetPalette(fk_Material^ material, int ID);

		//! マテリアル取得関数
		/*!
		 *	指定された ID に対応するマテリアルのポインタを返します。
		 *	
		 *	\param[in]	ID		マテリアルID
		 *
		 *	\return
		 *		対象マテリアルのポインタ。
		 *		ID に対応するマテリアルがパレット中にない場合は、
		 *		デフォルト状態のマテリアルインスタンスへのポインタを返します。
		 *
		 *	\sa PushPalette(), SetPalette(), Size
		 */
		fk_Material^ GetMaterial(int ID);
	};
}
