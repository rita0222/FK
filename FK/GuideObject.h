/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_GUIDE_OBJECT_HEADER__
#define __FK_GUIDE_OBJECT_HEADER__

#include <FK/Line.h>
#include <FK/Model.h>

typedef unsigned int fk_GuideMode;

const fk_GuideMode FK_NO_GUIDE = 0x0000;
const fk_GuideMode FK_AXIS_X   = 0x0001;
const fk_GuideMode FK_AXIS_Y   = 0x0002;
const fk_GuideMode FK_AXIS_Z   = 0x0004;
const fk_GuideMode FK_GRID_XZ  = 0x0008;
const fk_GuideMode FK_GRID_XY  = 0x0010;
const fk_GuideMode FK_GRID_YZ  = 0x0020;
const fk_GuideMode FK_ALL_GUIDE
	= FK_AXIS_X | FK_AXIS_Y | FK_AXIS_Z | FK_GRID_XZ | FK_GRID_XY | FK_GRID_YZ;

#define FKUT_NO_GUIDE	FK_NO_GUIDE
#define FKUT_AXIS_X		FK_AXIS_X
#define FKUT_AXIS_Y		FK_AXIS_Y
#define FKUT_AXIS_Z		FK_AXIS_Z
#define FKUT_GRID_XZ	FK_GRID_XZ
#define FKUT_GRID_XY	FK_GRID_XY
#define FKUT_GRID_YZ	FK_GRID_YZ
#define FKUT_ALL_GUIDE	FK_ALL_GUIDE

class fk_Scene;

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

class fk_GuideObject {
private:
	fk_Line			grid;
	fk_Model		gridModel[3];
	fk_Line			axis[3];
	fk_Model		axisModel[3];

	int	num;
	double scale;

public:
	//! コンストラクタ
	fk_GuideObject(void);
	//! デストラクタ
	~fk_GuideObject(void);

	//! 座標軸ライン幅設定関数
	/*!
	 *	座標軸を表す線分の太さを設定します。
	 *	デフォルトでは 4 になっています。
	 *
	 *	\param[in]	width	座標軸線の太さ。
	 *
	 *	\sa setGridWidth()
	 */
	void	setAxisWidth(double width);

	//! グリッド構成ライン幅設定関数
	/*!
	 *	グリッドを校正する線分の太さを設定します。
	 *	デフォルトでは 1 になっています。
	 *
	 *	\param[in]	width	グリッド線の太さ。
	 *
	 *	\sa setAxisWidth()
	 */
	void	setGridWidth(double width);

	//! グリッド間隔設定関数
	/*!
	 *	グリッドの線同士の間隔を設定します。
	 *	デフォルトでは 5 になっています。
	 *
	 *	\param[in]	scale	グリッド線同士の間隔。
	 *
	 *	\sa setNum()
	 */
	void	setScale(double scale);

	//! グリッド分割数設定関数
	/*!
	 *	グリッドの分割数を指定します。
	 *	ここでの分割数とは、グリッドの縦、横それぞれの領域の分割数を表します。
	 *	分割数を \f$ n \f$ としたとき、
	 *	グリッド領域全体の分割数は \f$ n^2 \f$ となり、
	 *	線分の本数は \f$ 2(n+1) \f$ となります。
	 *	デフォルトでは 20 になっています。
	 *
	 *	\param[in]	num		分割数。
	 *
	 *	\sa setScale()
	 */
	void	setNum(int num);

	//! 座標系ガイド適用モデル設定関数
	/*!
	 *	座標軸やグリッドを、この関数で指定したモデルの子モデルとします。
	 *	これにより、任意モデルのローカル座標系に追従した座標軸やグリッドを表示することができます。
	 *
	 *	\param[in]	model	座標系表示を追従させたいモデルインスタンスのポインタ。
	 *
	 *	\sa entryScene()
	 */
	void	setParent(fk_Model *model);

	//! シーン登録関数
	/*!
	 *	座標軸ならびにグリッドをシーンに登録します。
	 *	登録を制御できるのは x,y,z 軸ならびに xy, yz, xz 平面グリッドの6種類となります。
	 *	複数の要素を同時に登録するには、
	 *	対応する値をビット論理和演算子によって並べることで実現できます。
	 *	例えば x 軸, z 軸、xz 面グリッドを表示したい場合は以下の様になります。
	 *
	 *		fk_GuideObject	gobj;
	 *
	 *		gobj.entryScene(scene, FK_AXIS_X | FK_AXIS_Z | FK_GRID_XZ);
	 *
	 *	\param[in]	scene		登録するシーンインスタンスのポインタ。
	 *	\param[in]	mode		登録する要素。
	 *
	 *	\sa removeScene()
	 */
	void	entryScene(fk_Scene *scene,
					   fk_GuideMode mode = FK_AXIS_X | FK_AXIS_Y | FK_AXIS_Z | FK_GRID_XZ);

	//! シーン登録解除関数
	/*!
	 *	entryScene() によって登録した要素を解除します。
	 *	要素の複数指定方法は entryScene() と同様です。
	 *
	 *	\param[in]	scene		登録解除するシーンインスタンスのポインタ。
	 *	\param[in]	mode		登録解除する要素。
	 *
	 *	\sa entryScene()
	 */
	void	removeScene(fk_Scene *scene, fk_GuideMode mode = FK_NO_GUIDE);
};

#endif //!__FK_GUIDE_OBJECT_HEADER__
