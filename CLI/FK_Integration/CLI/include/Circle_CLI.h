// Circle_CLI.h

#pragma once

#include <FK/Circle.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	//! 円を生成、管理するクラス
	/*!
	 *	このクラスは、形状として円を制御する機能を提供します。
	 *	ここでの「円」は実際には正多角形を円に近似して扱っています。
	 *	多角形の角数は (分割数) * 4 となっています。
	 *	この多角形は、実質的には設定された半径の円に内接するものです。
	 *	円としての見栄えを良くするには分割数を大きめに設定すべきですが、
	 *	分割数の大きい円を大量に利用すると描画処理が遅くなるという問題が生じます。
	 *
	 *	初期状態では、中心を原点とし、
	 *	面の法線ベクトルが (0, 0, 1) となるように配置されます。
	 *	このクラスは fk_IndexFaceSet クラスの派生クラスであり、
	 *	生成後に fk_IndexFaceSet クラスの機能によって頂点を移動することが可能です。
	 *
	 *	\sa fk_IndexFaceSet, fk_Shape, fk_Model
	 */	
	public ref class fk_Circle : fk_IndexFaceSet {
	internal:
		::fk_Circle * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Circle(bool argNewFlg);
#endif

		//! コンストラクタ1
		/*!
		 *	分割数 3, 半径 1 の円を生成します。
		 */
		fk_Circle();

		//! コンストラクタ2
		/*!
		 *	引数として、分割数と半径を入力できます。
		 *
		 *	\param[in]	div	分割数。実際には円弧全体をこの数値の 4 倍で分割します。
		 *	\param[in]	rad	半径
		 */
		fk_Circle(int div, double rad);

		//! デストラクタ
		~fk_Circle();

		//! ファイナライザ
		!fk_Circle();

		//! 分割数設定関数
		/*!
		 *	分割数を設定します。
		 *
		 *	\param[in]	div	分割数。実際には円弧全体をこの数値の 4 倍で分割します。
		 */
		void SetDivide(int div);

		//! 半径設定関数
		/*!
		 *	半径を設定します。
		 *
		 *	\param[in]	rad	半径
		 */
		void SetRadius(double rad);

		//! 拡大縮小関数
		/*!
		 *	円全体を与えられた倍率で拡大縮小します。
		 *
		 *	\param[in]	scale	倍率
		 */
		void SetScale(double scale);
	};
}
