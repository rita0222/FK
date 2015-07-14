// IndexFace_CLI.h

#pragma once

#include <FK/Sphere.h>
#include "IndexFace_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	//! 球を生成、管理するクラス
	/*!
	 *	このクラスは、形状として球を制御する機能を提供しています。
	 *
	 *	実際には、球を近似する3角形面集合として表現されています。
	 *	3角形面の数は分割数を \f$ d \f$ とした場合 \f$ 8d(d-1) \f$ 枚となります。
	 *	分割数が高いほど球としての描画精度は高くなりますが、
	 *	面数も多くなるため描画速度が低下することになります。
	 *	特に多くのオブジェクトを同時に配置する場合は注意が必要です。
	 *
	 *	初期状態では、中心を原点とするように配置されます。
	 *	このクラスは fk_IndexFaceSet クラスの派生クラスであり、
	 *	生成後に fk_IndexFaceSet クラスの機能によって頂点を移動することが可能です。
	 *
	 *	\sa fk_IndexFaceSet, fk_Shape, fk_Model
	 */
	public ref class fk_Sphere : fk_IndexFaceSet {
	internal:
		::fk_Sphere * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Sphere(bool argNewFlg);
#endif

		//! コンストラクタ1
		/*!
		 *	分割数 2、半径 1 の球を生成します。
		 */
		fk_Sphere();

		//! コンストラクタ2
		/*!
		 *	引数として、分割数と半径を入力できます。分割数の最小値は 2 です。
		 *
		 *	\param[in]	div	分割数
		 *	\param[in]	rad	半径
		 */
		fk_Sphere(int div, double rad);

		//! デストラクタ
		~fk_Sphere();

		//! ファイナライザ
		!fk_Sphere();

		//! 分割数設定関数
		/*!
		 *	分割数を設定します。分割数の最小値は 2 です。
		 *
		 *	\param[in]	div	分割数
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
		 *	球全体を与えられた倍率で拡大縮小します。
		 *
		 *	\param[in]	scale	倍率
		 */
		void SetScale(double scale);
	};
}
