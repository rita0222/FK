// Matrix_CLI.h

#pragma once

#include <FK/GuideObject.h>
#include "Base_CLI.h"
#include "Model_CLI.h"
#include "Scene_CLI.h"

namespace FK_CLI {

	//! fk_GuideObject での座標軸と座標平面を表す列挙型
	public enum class fk_GuideMode : int {
		NO_GUIDE = 0x0000,	//!< 表示なし
		AXIS_X   = 0x0001,	//!< x軸
		AXIS_Y   = 0x0002,	//!< y軸
		AXIS_Z   = 0x0004,	//!< z軸
		GRID_XZ  = 0x0008,	//!< xz平面
		GRID_XY  = 0x0010,	//!< xy平面
		GRID_YZ  = 0x0020,	//!< yz平面
		ALL_GUIDE = AXIS_X | AXIS_Y | AXIS_Z | GRID_XZ | GRID_XY | GRID_YZ	//!< 全要素
	};
		
	//! 座標系可視化支援クラス
	/*!
	 *	このクラスは、座標系を可視化を支援するためのクラスで、
	 *	座標軸やグリッド(方眼状の線の集合)を表示する機能を提供します。
	 *	fk_AppWindow では内部で利用しています。
	 *
	 *	座標軸については、x 軸が赤、y 軸が緑、z 軸が青となり、
	 *	すべて原点より正方向に伸びています。
	 *	グリッドの線色は黒となります。
	 *
	 *	\sa fk_Model, fk_Scene, fk_AppWindow
	 */
	public ref class fk_GuideObject {
	internal:
		bool dFlg;
		::fk_GuideObject *pGuide;
		::fk_GuideObject * GetP(void);
		
	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_GuideObject(bool argNewFlg);
#endif
		//! コンストラクタ
		fk_GuideObject();

		//! デストラクタ
		~fk_GuideObject();

		//! ファイナライザ
		!fk_GuideObject();

		//! 座業軸ライン幅プロパティ
		/*!
		 *	座標軸を表す線分の太さの設定を行います。
		 *	デフォルトでは 4 になっています。
		 *
		 *	\sa GridWidth
		 */
		property double AxisWidth {
			void set(double);
		}

		//! グリッド構成ライン幅プロパティ
		/*!
		 *	グリッドを校正する線分の太さの設定を行います。
		 *	デフォルトでは 1 になっています。
		 *
		 *	\sa AxisWidth, Scale, Num
		 */
		property double GridWidth {
			void set(double);
		}

		//! グリッド間隔プロパティ
		/*!
		 *	グリッドの線同士の間隔の設定を行います。
		 *	デフォルトでは 5 になっています。
		 *
		 *	\sa Num, GridWidth
		 */
		property double Scale {
			void set(double);
		}

		//! グリッド分割数プロパティ
		/*!
		 *	グリッドの分割数の設定を行います。
		 *	ここでの分割数とは、グリッドの縦、横それぞれの領域の分割数を表します。
		 *	分割数を \f$ n \f$ としたとき、
		 *	グリッド領域全体の分割数は \f$ n^2 \f$ となり、
		 *	線分の本数は \f$ 2(n+1) \f$ となります。
		 *	デフォルトでは 20 になっています。
		 *
		 *	\sa Scale, GridWidth
		 */
		property int Num {
			void set(int);
		}

		//! シーン登録関数
		/*!
		 *	座標軸ならびにグリッドをシーンに登録します。
		 *	登録を制御できるのは x,y,z 軸ならびに xy, yz, xz 平面グリッドの6種類となります。
		 *	複数の要素を同時に登録するには、
		 *	対応する値をビット論理和演算子によって並べることで実現できます。
		 *	例えば x 軸, z 軸、xz 面グリッドを表示したい場合は以下の様になります。
		 *
		 *		fk_GuideObject	gobj = new fk_GuideObject();
		 *
		 *		gobj.EntryScene(scene,
		 *						fk_GuideMode.AXIS_X |
		 *						fk_GuideMode.AXIS_Z |
		 *						fk_GuideMode.GRID_XZ);
		 *
		 *	\param[in]	scene		登録するシーンインスタンスのポインタ。
		 *	\param[in]	mode		登録する要素。
		 *
		 *	\sa RemoveScene()
		 */
		void EntryScene(fk_Scene^ scene, fk_GuideMode mode);

		//! シーン登録解除関数
		/*!
		 *	EntryScene() によって登録した要素を解除します。
		 *
		 *	\param[in]	scene		登録解除するシーンインスタンスのポインタ。
		 *
		 *	\sa EntryScene()
		 */
		void RemoveScene(fk_Scene^ scene);
	};
}
