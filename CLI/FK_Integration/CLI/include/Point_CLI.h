// Point_CLI.h

#pragma once

#include <FK/Point.h>
#include "Vector_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	//! 点群を生成、管理するクラス
	/*!
	 *	このクラスは、形状として点群を制御する機能を提供します。
	 *	1つのインスタンスで、複数の点を制御することが可能です。
	 *
	 *	このクラスの機能は大きく以下のようなものとなります。
	 *	- 点の生成や消去
	 *	- 点の移動
	 *	- 各点の描画有無の設定
	 *	- 各店の描画色の設定
	 *	.
	 *	このクラスと同様に点群を扱うクラスとして、
	 *	fk_Particle と fk_ParticleSet があります。
	 *	fk_Point が点の制御を直接的に行うのに対し、
	 *	fk_Particle や fk_ParticleSet では
	 *	法則を記述することが主であるという特徴があります。
	 *
	 *	\sa fk_Shape, fk_Particle, fk_ParticleSet
	 */
	public ref class fk_Point : fk_Shape {
	internal:
		::fk_Point * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Point(bool argNewFlg);
#endif
		//! コンストラクタ1
		/*!
		 *	点が空の状態でインスタンスを生成します。
		 */
		fk_Point();

		//! コンストラクタ2
		/*!
		 *	引数として fk_Vector 型の配列を与えることによって、
		 *	最初から点群を生成することができます。
		 *
		 *	\param[in]	array
		 *		点群位置ベクトル配列。null の場合は何も生成しません。
		 */
		fk_Point(cli::array<fk_Vector^>^ array);

		//! デストラクタ
		~fk_Point();

		//! ファイナライザ
		!fk_Point();

		//! 頂点数プロパティ
		/*!
		 *	点群の頂点数を参照します。
		 */
		property int Num {
			int get();
		}

		//! 描画色設定有無プロパティ
		/*!
		 *	点群の描画色設定の有無を参照します。
		 *	1個以上の点に描画色が設定されている場合 true、
		 *	1つも描画色が設定されていない場合に false となります。
		 */
		property bool ColorCount {
			bool get();
		}
		
		//! 頂点追加関数
		/*!
		 * 	頂点を新たに追加します。
		 *
		 *	\param[in]	pos		追加する頂点の位置ベクトル
		 *
		 *	\return		新しい頂点の ID
		 */
		int			PushVertex(fk_Vector^ pos);

		//! 頂点位置設定関数
		/*!
		 *	点群中の任意の頂点に対し、位置を設定します。
		 *
		 *	\param[in]	ID		頂点ID
		 *	\param[in]	pos		移動先の位置ベクトル
		 *
		 *	\return		移動に成功すれば true を、失敗すれば false を返します。
		 */
		bool		SetVertex(int ID, fk_Vector^ pos);

		//! 点群生成関数
		/*
		 *	配列データから点群全体を生成します。
		 *	関数を呼ぶ前に存在していた点は全て消去されます。
		 *
		 *	\param[in]	array	頂点位置ベクトルの配列
		 *
		 *	\return		生成に成功すれば true を、失敗すれば false を返します。
		 */
		bool		SetVertex(cli::array<fk_Vector^>^ array);

		//! 頂点削除関数
		/*
		 *	頂点を削除します。
		 *
		 *	\param[in]	ID		頂点ID
		 *
		 *	\return		削除に成功すれば true を、失敗すれば false を返します。
		 */
		bool		RemoveVertex(int ID);

		//! 頂点位置ベクトル取得関数
		/*!
		 *	指定した頂点の位置ベクトルを返します。
		 *
		 *	\param[in]	ID		頂点ID
		 *
		 *	\return
		 *		頂点の位置ベクトル。
		 *		指定した頂点が存在しない場合は null を返します。
		 */
		fk_Vector^	GetVertex(int ID);

		//! 頂点描画制御関数
		/*!
		 *	個別の頂点に対し、描画の有無を設定します。
		 *
		 *	\param[in]	ID		頂点ID
		 *
		 *	\param[in]	mode
		 *		true であれば描画を有効に、false であれば無効にします。
		 */
		void		SetDrawMode(int ID, bool mode);

		//! 全頂点描画状態参照関数
		/*!
		 *	点群全体の描画状況を取得します。
		 *
		 *	\return
		 *		点群中、1つでも描画される状態であれば true を、
		 *		そうでない場合は false を返します。
		 *		false を返す場合は、頂点が存在するが全て描画状態が無効である場合と、
		 *		1個も頂点が存在していない場合の2通りがありえます。
		 */
		bool		GetDrawMode(void);

		//! 個別頂点描画状態参照関数
		/*!
		 *	個別の頂点に対し、描画状況をを取得します。
		 *
		 *	\param[in]	ID		頂点ID
		 *
		 *	\return
		 *		描画が有効であれば true を、無効であれば false を返します。
		 *		指定した ID を持つ頂点が存在しなかった場合も false を返します。
		 */
		bool		GetDrawMode(int ID);

		//! 描画色設定関数
		/*!
		 *	個別の頂点に対し、描画色の ID を設定します。
		 *	色そのものの設定は、 fk_Shape::setPalette() を参照して下さい。
		 *
		 *	\param[in]	vID		頂点ID
		 *	\param[in]	cID		色ID
		 */
		void		SetColorID(int vID, int cID);

		//! 描画色参照関数
		/*!
		 *	個別の頂点の描画色を取得します。
		 *
		 *	\param[in]	vID		頂点ID
		 *
		 *	\return
		 *		描画色が設定されている場合はその描画色 ID を返します。
		 *		描画色が設定されていない場合は -1 を返します。
		 *		頂点が存在しない場合は -2 を返します。
		 */
		int			GetColorID(int vID);

		//! 点群全消去関数1
		/*!
		 *	全ての頂点に関するデータを消去します。
		 *
		 *	\param[in]	matFlag
		 *		true の場合は、マテリアルパレットも初期化します。
		 *		false の場合は、マテリアルパレットに関しては消去しません。
		 */
		void		AllClear(bool matFlag);

		//! 点群全消去関数2
		/*!
		 *	全ての頂点に関するデータを消去します。
		 *	マテリアルパレットも初期化します。
		 */
		void		AllClear(void);
	};
}
