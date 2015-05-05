// Polygon_CLI.h

#pragma once

#include <FK/Polygon.h>
#include "Solid_CLI.h"

namespace FK_CLI
{
	//! 多角形を生成、管理するクラス
	/*!
	 *	このクラスは、形状として多角形を制御する機能を提供します。
	 *	このクラスによる形状は、多角形の内部も描画します。
	 *	もし辺のみを描画したい場合は fk_Closedline クラスを利用して下さい。
	 *
	 *	描画される面は、基本的には多角形の頂点順番が向かって
	 *	反時計回りになっている側になります。
	 *	両面を描画したい場合は fk_Model::DrawMode プロパティを参照して下さい。
	 *	また、本クラスの多角形の角数は 3 以上であれば制限はありませんが、
	 *	平面でなかった場合に意図している形状と描画形状が異なる場合があります。
	 *
	 *	\sa fk_Solid, fk_Polyline, fk_Closedline
	 */
	public ref class fk_Polygon : fk_Solid {
	internal:
		::fk_Polygon * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Polygon(bool argNewFlg);
#endif
		//! コンストラクタ1
		/*!
		 *	空のポリゴンを生成します。
		 */
		fk_Polygon();

		//! コンストラクタ2
		/*!
		 *	与えられた引数を頂点とするポリゴンを生成します。
		 *
		 *	\param[in]	array		頂点配列。
		 */
		fk_Polygon(array<fk_Vector^>^ array);

		//! デストラクタ
		~fk_Polygon();

		//! ファイナライザ
		!fk_Polygon();

		//! 頂点追加関数
		/*!
		 *	頂点を追加します。
		 *
		 *	\param[in] pos 追加頂点の位置ベクトル
		 */
		void PushVertex(fk_Vector^ pos);

		//! 頂点位置設定関数
		/*!
		 *	頂点の位置を設定します。
		 *	対象となる頂点がまだ存在していなかった場合、
		 *	角数を (id+1) まで増加させます。
		 *
		 *	\param[in] ID 頂点ID
		 *	\param[in] pos 頂点位置ベクトル
		 */
		void SetVertex(int ID, fk_Vector^ pos);

		//! 頂点位置設定関数
		/*!
		 *	頂点全部を、指定した配列に入れ替えます。
		 *
		 *	\param[in] array	array型による頂点位置配列
		 */
		void SetVertex(array<fk_Vector^>^ array);
	};

	//! ポリラインを生成、管理するクラス
	/*!
	 *	このクラスは、形状としてポリラインを制御する機能を提供します。
	 *
	 *	\sa fk_Solid, fk_Polygon, fk_Closedline
	 */
	public ref class fk_Polyline : fk_Solid {
	internal:
		::fk_Polyline * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Polyline(bool argNewFlg);
#endif

		//! コンストラクタ1
		/*!
		 *	空のポリラインを生成します。
		 */
		fk_Polyline();

		//! コンストラクタ2
		/*!
		 *	与えられた引数を頂点とするポリラインを生成します。
		 *
		 *	\param[in]	array		頂点配列。
		 */
		fk_Polyline(array<fk_Vector^>^ array);

		//! デストラクタ
		~fk_Polyline();

		//! ファイナライザ
		!fk_Polyline();
	
		//! 頂点追加関数
		/*!
		 *	頂点を追加します。
		 *
		 *	\param[in] pos 追加頂点の位置ベクトル
		 */
		void PushVertex(fk_Vector^ pos);

		//! 頂点位置設定関数
		/*!
		 *	頂点の位置を設定します。
		 *	対象となる頂点がまだ存在していなかった場合、
		 *	角数を (id+1) まで増加させます。
		 *
		 *	\param[in] ID 頂点ID
		 *	\param[in] pos 頂点位置ベクトル
		 */
		void SetVertex(int ID, fk_Vector^ pos);

		//! 頂点位置設定関数
		/*!
		 *	頂点全部を、指定した配列に入れ替えます。
		 *
		 *	\param[in] array	array型による頂点位置配列
		 */
		void SetVertex(array<fk_Vector^>^ array);
	};

	//! 多角形(辺のみ)を生成、管理するクラス
	/*!
	 *	このクラスは閉じたポリライン、つまり多角形の辺のみを制御する機能を提供します。
	 *	このクラスの利用方法は実質的に fk_Polygon クラスと同一で、
	 *	描画が辺のみとなるという点だけが異なります。
	 *	利用方法については fk_Polygon クラスを参照して下さい。
	 *
	 *	\sa fk_Solid, fk_Polygon, fk_Polyline
	 */
	public ref class fk_Closedline : fk_Polygon {
	internal:
		::fk_Closedline * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Closedline(bool argNewFlg);
#endif
		//! コンストラクタ1
		/*!
		 *	空の閉じたポリラインを生成します。
		 */
		fk_Closedline();
		
		//! コンストラクタ2
		/*!
		 *	与えられた引数を頂点とする閉じたポリラインを生成します。
		 *
		 *	\param[in]	array		頂点配列。
		 */
		fk_Closedline(array<fk_Vector^>^ array);

		//! デストラクタ
		~fk_Closedline();

		//! ファイナライザ
		!fk_Closedline();
	};		
}
