// Block_CLI.h

#pragma once

#include <FK/Capsule.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	//! カプセル型を生成、管理するクラス
	/*!
	 *	このクラスは、形状としてカプセル型を制御する機能を提供します。
	 *	カプセル型は半径の等しい円柱側面と半球面によって構成されています。
	 *	数学的には、カプセル型の内部は1本の線分より一定距離以下の部分の集合であり、
	 *	その一定距離は前述の半径と等しくなります。この線分を「中心軸」と呼びます。
	 *	初期状態は中心軸の中点が原点に配置され、z軸方向と中心軸が平行となります。
	 *
	 *	このクラスは、実質的には fk_IndexFaceSet クラスの派生クラスであり、
	 *	生成後に fk_IndexFaceSet クラスの機能によって頂点を移動することが可能です。
	 *
	 *	\sa fk_IndexFaceSet, fk_Shape, fk_Model
	 */
	public ref class fk_Capsule : fk_IndexFaceSet {
	internal:
		::fk_Capsule * GetP(void);

	public:
		//! コンストラクタ1
		/*!
		 *	分割数2, 中心軸張1, 半径1 のカプセル型を生成します。
		 */
		fk_Capsule();

		//! コンストラクタ2
		/*!
		 *	引数として、中心軸の長さと半径、分割数を入力できます。
		 *	分割数の最小値は 2 です。
		 *
		 *	\param[in]	div		分割数
		 *	\param[in]	len		中心軸長
		 *	\param[in]	rad		半径
		 */
		fk_Capsule(int div, double len, double rad);


#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Capsule(bool argNewFlg);
#endif

		//! デストラクタ
		~fk_Capsule();

		//! ファイナライザ
		!fk_Capsule();

		//! 分割数設定関数
		/*!
		 *	分割数を設定します。分割数の最小値は 2 です。
		 *
		 *	\param[in]	div	分割数
		 *
		 *	\note
		 *		分割数についての詳細は、 fk_Sphere の分割数の説明に準拠します。
		 *
		 *	\sa SetLength(), SetRadius()
		 */
		void SetDivide(int div);

		//! 中心軸長設定関数
		/*!
		 *	中心軸の長さを設定します。
		 *
		 *	\param[in]	length	中心軸長
		 *
		 *	\note
		 *		カプセル型の全長はこの中心軸の長さではなく、
		 *		中心軸長と半径の2倍を足したものとなります。
		 *
		 *	\sa SetDivide(), SetRadius()
		 */
		void SetLength(double length);

		//! 半径設定関数
		/*!
		 *	円柱面や半球面の半径を設定します。
		 *
		 *	\param[in]	radius	半径
		 *
		 *	\sa SetDivide(), SetLength()
		 */
		void SetRadius(double radius);

		//! 拡大縮小関数
		/*!
		 *	カプセル型全体を与えられた倍率で拡大縮小します。
		 *
		 *	\param[in]	scale	倍率
		 */
		void SetScale(double scale);
	};
}
