// Block_CLI.h

#pragma once

#include <FK/Block.h>
#include "IndexFace_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	//! 直方体を生成、管理するクラス
	/*!
	 *	このクラスは、形状として直方体を制御する機能を提供します。
	 *	直方体は、物体の中心が原点に来るように配置されます。
	 *	従って、(x, y, z) という大きさで直方体を生成した場合、
	 *	各頂点の位置ベクトルは以下のようになります。
	 *	- (x/2, y/2, z/2)
	 *	- (-x/2, y/2, z/2)
	 *	- (-x/2, -y/2, z/2)
	 *	- (x/2, -y/2, z/2)
	 *	- (x/2, y/2, -z/2)
	 *	- (-x/2, y/2, -z/2)
	 *	- (-x/2, -y/2, -z/2)
	 *	- (x/2, -y/2, -z/2)
	 *
	 *	このクラスは、実質的には fk_IndexFaceSet クラスの派生クラスであり、
	 *	生成後に fk_IndexFaceSet クラスの機能によって頂点を移動することが可能です。
	 *
	 *	\sa fk_IndexFaceSet, fk_Shape, fk_Model
	 */
	public ref class fk_Block : fk_IndexFaceSet {
	internal:
		::fk_Block * GetP(void);

	public:
		//! コンストラクタ1
		/*!
		 *	全辺の長さが 1 である直方体(立方体)を生成します。
		 */
		fk_Block();

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Block(bool);
#endif

		//! コンストラクタ2
		/*!
		 *	引数として、各軸方向の幅を入力できます。
		 *
		 *	\param[in]	x	x方向の辺長
		 *	\param[in]	y	y方向の辺長
		 *	\param[in]	z	z方向の辺長
		 */
		fk_Block(double x, double y, double z);
		
		//! デストラクタ
		~fk_Block();

		//! ファイナライザ
		!fk_Block();

		//! 各辺長設定関数
		/*!
		 *	直方体の各軸方向の辺長を一括して設定します。
		 *
		 *	\param[in]	x	x方向の辺長
		 *	\param[in]	y	y方向の辺長
		 *	\param[in]	z	z方向の辺長
		 */
		void SetSize(double x, double y, double z);

		//! 個別辺長設定関数
		/*!
		 *	直方体の辺長を個別に設定します。
		 *
		 *	\param[in]	length	辺長
		 *	\param[in]	axis	軸方向。以下のいずれかを指定します。
		 *		- fk_Axis.X x方向
		 *		- fk_Axis.Y y方向
		 *		- fk_Axis.Z z方向
		 */
		void SetSize(double length, fk_Axis axis);

		//! 全体拡大縮小関数
		/*!
		 *	直方体全体を、指定された倍率で拡大・縮小します。
		 *
		 *	\param[in]	scale	倍率
		 */
		void SetScale(double scale);

		//! 軸方向拡大縮小関数
		/*!
		 *	直方体を、指定された軸方向についてのみ拡大・縮小します。
		 *
		 *	\param[in]	scale	倍率
		 *	\param[in]	axis	軸方向。以下のいずれかを指定します。
		 *		- fk_Axis.X x方向
		 *		- fk_Axis.Y y方向
		 *		- fk_Axis.Z z方向
		 */
		void SetScale(double scale, fk_Axis axis);

		//! 軸方向個別拡大縮小関数
		/*!
		 *	直方体を、各軸方向に対し個別の倍率で拡大・縮小します。
		 *
		 *	\param[in]	x	x方向の倍率
		 *	\param[in]	y	y方向の倍率
		 *	\param[in]	z	z方向の倍率
		 */
		void SetScale(double x, double y, double z);
	};
}
