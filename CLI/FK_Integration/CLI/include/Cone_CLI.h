// Cone_CLI.h

#pragma once

#include <FK/Cone.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	//! 正多角錐・円錐を生成、管理するクラス
	/*!
	 *	このクラスは、形状として正多角錐や円錐を制御する機能を提供します。
	 *	円錐は、分割数の多い正多角錐として生成します。
	 *	通常、分割数が 20 を超える程度でほとんど円錐と見分けがつかなくなります。
	 *	配置は、底面の中心が原点となり、
	 *	頂点が -z 方向、底面が +z 方向となります。
	 *
	 *	設定できる要素は角数、底面半径、高さの3要素です。
	 *	底面半径とは、面を構成する正多角形の外接円半径を指します。
	 *
	 *	このクラスは、実質的には fk_IndexFaceSet クラスの派生クラスであり、
	 *	生成後に fk_IndexFaceSet クラスの機能によって頂点を移動することが可能です。
	 *	\sa fk_IndexFaceSet, fk_Shape, fk_Model, fk_Prism
	 */
	public ref class fk_Cone : fk_IndexFaceSet {
	internal:
		::fk_Cone * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Cone(bool argNewFlg);
#endif
		//! コンストラクタ1
		fk_Cone();
		/*!
		 *	角数 3, 底面半径 1, 高さ 1 の角錐を生成します。
		 */
		//! コンストラクタ2
		/*!
		 *	引数として、角数、底面半径、高さを入力できます。
		 *
		 *	\param[in]	div		角数
		 *	\param[in]	rad		底面半径
		 *	\param[in]	height	高さ
		 */
		fk_Cone(int div, double rad, double height);

		//! デストラクタ
		~fk_Cone();

		//! ファイナライザ
		!fk_Cone();

		//! 角数設定関数
		/*!
		 *	角数を変更します。
		 *
		 *	\param[in]	div	角数
		 */		
		void SetDivide(int div);

		//! 底面半径設定関数
		/*!
		 *	底面半径を設定します。
		 *
		 *	\param[in]	rad	底面半径
		 */
		void SetRadius(double rad);

		//! 高さ設定関数
		/*!
		 *	高さを設定します。
		 *
		 *	\param[in]	height	高さ
		 */
		void SetHeight(double height);
	};
}
