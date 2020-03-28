#pragma once

#include <FK/GuideObject.h>
#include "Base_CLI.h"
#include "Model_CLI.h"
#include "Scene_CLI.h"

namespace FK_CLI {

	//! fk_GuideObject での座標軸と座標平面を表す列挙型
	public enum class fk_Guide : unsigned int {
		NO_GUIDE = 0,	//!< 表示なし
		AXIS_X   = 1 << 1,	//!< x軸
		AXIS_Y   = 1 << 2,	//!< y軸
		AXIS_Z   = 1 << 3,	//!< z軸
		GRID_XZ  = 1 << 4,	//!< xz平面
		GRID_XY  = 1 << 5,	//!< xy平面
		GRID_YZ  = 1 << 6	//!< yz平面
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
		::FK::fk_GuideObject *pGuide;
		::FK::fk_GuideObject * GetP(void);
		
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

		//! シーン登録メソッド
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
		 *						fk_Guide.AXIS_X |
		 *						fk_Guide.AXIS_Z |
		 *						fk_Guide.GRID_XZ);
		 *
		 *	\param[in]	scene		登録するシーンインスタンスのポインタ。
		 *	\param[in]	mode		登録する要素。
		 *
		 *	\sa RemoveScene()
		 */
		void EntryScene(fk_Scene^ scene, fk_Guide mode);

		//! シーン登録解除メソッド
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

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/
