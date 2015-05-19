// Prism_CLI.h

#pragma once

#include <FK/Prism.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	//! 正多角柱・円柱を生成、管理するクラス
	/*!
	 *	このクラスは、形状として正多角柱や円柱を制御する機能を提供します。
	 *	円柱は、分割数の多い正多角柱として生成します。
	 *	通常、分割数が 20 を超える程度でほとんど円柱と見分けがつかなくなります。
	 *	配置は、底面の中心が原点となり、
	 *	多角柱の上面が -z 方向、底面が +z 方向となります。
	 *
	 *	設定できる要素は角数、上面半径、底面半径、高さの4要素です。
	 *	上面と底面の半径とは、それぞれの面を構成する正多角形の外接円半径を指します。
	 *
	 *	このクラスは、実質的には fk_IndexFaceSet クラスの派生クラスであり、
	 *	生成後に fk_IndexFaceSet クラスの機能によって頂点を移動することが可能です。
	 *
	 *	\sa fk_IndexFaceSet, fk_Shape, fk_Model, fk_Cone
	 */
	public ref class fk_Prism : fk_IndexFaceSet {
	internal:
		::fk_Prism * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Prism(bool argNewFlg);
#endif
		//! コンストラクタ1
		/*!
		 *	角数3, 上面半径1, 底面半径1, 高さ1 の角柱を作成します。
		 */
		fk_Prism();

		//! コンストラクタ2
		/*!
		 *	引数の寸法に従った角柱を作成します。
		 *
		 *	\param[in]	div		角数
		 *	\param[in]	top		上面半径
		 *	\param[in]	bottom	底面半径
		 *	\param[in]	height	高さ
		 */
		fk_Prism(int argDiv, double argTop, double argBottom, double argHeight);

		//! デストラクタ
		~fk_Prism();

		//! ファイナライザ
		!fk_Prism();

		//! 角数設定関数
		/*!
		 *	角数を変更します。
		 *
		 *	\param[in]	div	角数
		 */		
		void SetDivide(int div);

		//! 上面半径設定関数
		/*!
		 *	上面半径を設定します。
		 *
		 *	\param[in]	rad	上面半径
		 */
		void SetTopRadius(double rad);

		//! 底面半径設定関数
		/*!
		 *	底面半径を設定します。
		 *
		 *	\param[in]	rad	底面半径
		 */
		void SetBottomRadius(double rad);

		//! 高さ設定関数
		/*!
		 *	高さを設定します。
		 *
		 *	\param[in]	height	高さ
		 */
		void SetHeight(double height);
	};
}
