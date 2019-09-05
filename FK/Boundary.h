/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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


#ifndef __FK_BOUNDARY_HEADER__
#define __FK_BOUNDARY_HEADER__

#include <FK/MatAdmin.h>
#include <FK/DrawMode.h>

namespace FK {

	class fk_Model;
	class fk_Color;
	class fk_IndexFaceSet;

	//! 境界ボリュームのタイプを表す列挙型
	enum fk_BoundaryMode {
		FK_B_SPHERE,		//!<	境界球
		FK_B_AABB,			//!<	軸平行境界ボックス (Axis Aligned Bounding Box)
		FK_B_OBB,			//!<	有向境界ボックス (Oriented Bounding Box)
		FK_B_CAPSULE,		//!<	カプセル型
		FK_B_NONE			//!<	未定義境界
	};
/*
	using fk_DrawMode = unsigned int;

	const fk_DrawMode	FK_NONEMODE 			= 0;
	const fk_DrawMode 	FK_POINTMODE 			= 1 << 1;
	const fk_DrawMode	FK_LINEMODE 			= 1 << 2;
	const fk_DrawMode	FK_POLYMODE 			= 1 << 3;
	const fk_DrawMode	FK_BACK_POLYMODE		= ((1 << 4) | FK_POLYMODE);
	const fk_DrawMode	FK_FRONTBACK_POLYMODE	= ((1 << 5) | FK_POLYMODE);
	const fk_DrawMode	FK_TEXTUREMODE			= 1 << 6;
	const fk_DrawMode	FK_CURVEMODE			= 1 << 7;
	const fk_DrawMode	FK_SURFACEMODE			= 1 << 8;
*/
	
	//! 境界ボリュームを管理するクラス
	/*!
	 *	このクラスは、モデルの干渉判定や衝突判定を行うための
	 *	「境界ボリューム」を制御する機能を提供します。
	 *
	 *	「境界ボリューム」とは、モデルが干渉判定や衝突判定を行う際に、
	 *	処理を高速に行うための簡易的な形状を指します。
	 *	モデル同士の干渉・衝突判定は、
	 *	実際にはこの境界ボリューム同士の干渉状態や衝突を検出することになります。
	 *	干渉判定と衝突判定に関する詳細は fk_Model の概要を参照して下さい。
	 *
	 *	境界ボリュームには、現在は以下の4種類が提供されています。
	 *
	 *	- 境界球 \n
	 *		球形状による境界ボリュームです。
	 *		処理は最も高速ですが、本来の形状との誤差が大きくなることがあります。
	 *		現状では、衝突判定を行いたい場合はこの境界球を用いる必要があります。
	 *	- 軸平行境界ボックス (Axis Aligned Bounding Box, AABB) \n
	 *		直方体による境界ボリュームですが、
	 *		常に各面が座標軸と垂直であるという特性を持ちます。
	 *		境界球と比較すると元形状にフィッティングしやすく、
	 *		判定処理も OBB やカプセル型と比較して高速であるという特性を持ちます。
	 *		その反面、モデルが回転した場合に新たに大きさを再設定する必要があることや、
	 *		回転によって大きさが変化することなどから、
	 *		モデルが回転する場合には扱いづらい面があります。
	 *		モデルが方向ベクトルを変化させずに移動するような場合に適しています。
	 *	- 有向境界ボックス (Oriented Bounding Box, OBB) \n
	 *		AABB と同じく直方体による境界ボリュームですが、
	 *		こちらはモデルの回転に伴ってボックスの向きも追従します。
	 *		境界ボリュームの挙動が想定しやすく扱いやすい特性を持ちますが、
	 *		判定処理は全ての境界ボリューム中もっとも重く、
	 *		多くのモデルがある状態で多用するとかなり全体の処理が重くなる可能性があります。
	 *	- カプセル型 \n
	 *		境界が円柱側面と半球によって構成されている境界ボリュームです。
	 *		数学的には、線分から一定距離以内にある点の集合となります。
	 *		この線分を本マニュアルでは「中心軸」と呼称します。
	 *		中心軸両端点を設定することがやや面倒ですが、
	 *		長細いモデルにもフィットしやすく、判定処理も OBB より高速なので、
	 *		使い勝手のよい境界ボリュームです。
	 *
	 *	\sa fk_Model
	 */

	class fk_Boundary : public fk_MatrixAdmin {
	public:

		//! コンストラクタ
		fk_Boundary(fk_Type);

		//! デストラクタ
		virtual ~fk_Boundary();

		//! \name 境界ボリューム選択制御関数
		//@{

		//! 境界ボリューム選択関数
		/*!
		 *	この関数は、
		 *	干渉判定にどの境界ボリュームを利用するかを選択します。
		 *	本関数の設定は各境界ボリュームの設定とは独立しており、
		 *	この関数によってモードを変更しても、
		 *	各境界ボリュームの大きさ等の設定は初期化されません。
		 *
		 *	\note
		 *		本関数で選択が有効となるのは、現バージョンでは干渉判定のみです。
		 *		衝突判定については、本関数での設定に関わらず境界球の設定が用いられます。
		 *
		 *	\param[in]	mode	モデルで干渉判定に利用する境界ボリュームの種類
		 *
		 *	\sa getBMode(), fk_Model::isInter()
		 */
		void		setBMode(fk_BoundaryMode mode);

		//! 境界ボリューム選択状態参照関数
		/*!
		 *	現在選択されている境界ボリュームの種類を取得します。
		 *
		 *	\return		境界ボリューム種類
		 *
		 *	\sa setBMode(), fk_Model::isInter()
		 */
		fk_BoundaryMode			getBMode(void);
		//@}

		//! \name 境界球制御関数
		//@{

		//! 境界球半径設定関数
		/*!
		 *	境界球半径を設定します。
		 *	現在モデルに設定されている形状から、
		 *	自動的に境界球半径を設定したい場合は fk_Model::adjustSphere() を用いて下さい。
		 *
		 *	\param[in]	r	境界球半径
		 *
		 *	\sa getSphere(), setBMode(), fk_Model::adjustSphere()
		 */
		void		setSphere(double r);

		//! 境界球半径参照関数
		/*!
		 *	現在設定されている境界球半径を取得します。
		 *
		 *	\return		境界球半径
		 *
		 *	\sa setSphere(), fk_Model::adjustSphere()
		 */
		double		getSphere(void);
		//@}

		//! \name 軸平行境界ボックス (AABB) 制御関数
		//@{

		//! 軸平行境界ボックス (AABB) サイズ設定関数1
		/*!
		 *	軸平行境界ボックス (AABB) のサイズを設定します。
		 *	サイズの各成分はグローバル座標系に対応します。
		 *	自動的に AABB のサイズを設定したい場合は fk_Model::adjustAABB() を用いて下さい。
		 *
		 *	\param[in]	x	AABBのx方向のサイズ
		 *	\param[in]	y	AABBのy方向のサイズ
		 *	\param[in]	z	AABBのz方向のサイズ
		 *
		 *	\sa setAABBSize(fk_Vector), getAABBSize(), setBMode(), fk_Model::adjustAABB()
		 */
		void		setAABBSize(double x, double y, double z);

		//! 軸平行境界ボックス (AABB) サイズ設定関数2
		/*!
		 *	軸平行境界ボックス (AABB) のサイズを設定します。
		 *	サイズの各成分はグローバル座標系に対応します。
		 *	自動的に AABB のサイズを設定したい場合は fk_Model::adjustAABB() を用いて下さい。
		 *
		 *	\param[in]	size	AABBのサイズ
		 *
		 *	\sa setAABBSize(double, double, double), getAABBSize(),
		 *		setBMode(), fk_Model::adjustAABB()
		 */
		void		setAABBSize(fk_Vector size);

		//! 軸平行境界ボックス (AABB) サイズ取得関数
		/*!
		 *	現在設定されている軸平行境界ボックス (AABB) のサイズを取得します。
		 *
		 *	\return		AABBの大きさ
		 *
		 *	\sa setAABBSize(double, double, double), setAABBSize(fk_Vector), fk_Model::adjustAABB()
		 */
		fk_Vector	getAABBSize(void);
		//@}

		//! \name 有向境界ボックス (OBB) 制御関数
		//@{

		//! 有向境界ボックス (OBB) サイズ設定関数1
		/*!
		 *	有向境界ボックス (OBB) のサイズを設定します。
		 *	サイズの各成分はモデルのローカル座標系に対応します。
		 *	自動的に OBB のサイズを設定したい場合は fk_Model::adjustOBB() を用いて下さい。
		 *
		 *	\param[in]	x	OBBのx方向のサイズ
		 *	\param[in]	y	OBBのy方向のサイズ
		 *	\param[in]	z	OBBのz方向のサイズ
		 *
		 *	\sa setOBBSize(fk_Vector), getOBBSize(), setBMode(), fk_Model::adjustOBB()
		 */
		void		setOBBSize(double x, double y, double z);

		//! 有向境界ボックス (OBB) サイズ設定関数2
		/*!
		 *	有向境界ボックス (OBB) のサイズを設定します。
		 *	サイズの各成分はモデルのローカル座標系に対応します。
		 *	自動的に OBB のサイズを設定したい場合は fk_Model::adjustOBB() を用いて下さい。
		 *
		 *	\param[in]	size	OBBのサイズ
		 *
		 *	\sa setOBBSize(double, double, double), getOBBSize(), setBMode(), fk_Model::adjustOBB()
		 */
		void		setOBBSize(fk_Vector size);

		//! 有向境界ボックス (OBB) サイズ取得関数
		/*!
		 *	現在設定されている有向境界ボックス (OBB) のサイズを取得します。
		 *
		 *	\return		IBBの大きさ
		 *
		 *	\sa setOBBSize(double, double, double), setOBBSize(fk_Vector), fk_Model::adjustOBB()
		 */
		fk_Vector	getOBBSize(void);
		//@}

		//! \name カプセル型制御関数
		//@{

		//! カプセル型設定関数
		/*!
		 *	カプセル型は、数学的には線分(中心軸)からある一定距離以内にある領域となります。
		 *	この関数は、中心軸の両端点と距離を設定することでカプセル型を規定するものです。
		 *	中心軸端点の位置ベクトルは、モデルのローカル座標系に対応します。
		 *	自動的にカプセル型のサイズを設定したい場合は fk_Model::adjustCapsule() を用いて下さい。
		 *
		 *	\param[in]	sPos	中心軸端点(始点側)の位置ベクトル
		 *	\param[in]	ePos	中心軸端点(終点側)の位置ベクトル
		 *	\param[in]	r		中心軸からの領域規定距離
		 *
		 *	\sa	getCapsuleRadius(), getCapsuleLength(), getCapsuleStartPos(), getCapsuleEndPos(),
		 *		setBMode(), fk_Model::adjustCapsule()
		 */
		void		setCapsule(fk_Vector sPos, fk_Vector ePos, double r);

		//! カプセル型領域規定距離取得関数
		/*!
		 *	現在設定されているカプセル型の領域規定距離を取得します。
		 *
		 *	\return		カプセル型の領域規定距離
		 *
		 *	\sa	setCapsule(), fk_Model::adjustCapsule()
		 */
		double		getCapsuleRadius(void);

		//! カプセル型中心軸長取得関数
		/*!
		 *	現在設定されているカプセル型の中心軸の長さを取得します。
		 *
		 *	\return		カプセル型の中心軸の長さ
		 *
		 *	\sa	setCapsule(), fk_Model::adjustCapsule()
		 */
		double		getCapsuleLength(void);

		//! カプセル型中心軸始点取得関数
		/*!
		 *	現在設定されているカプセル型の中心軸の始点位置ベクトルを取得します。
		 *
		 *	\return		カプセル型の中心軸の始点位置ベクトル
		 *
		 *	\sa	setCapsule(), fk_Model::adjustCapsule()
		 */
		fk_Vector	getCapsuleStartPos(void);

		//! カプセル型中心軸終点取得関数
		/*!
		 *	現在設定されているカプセル型の中心軸の終点位置ベクトルを取得します。
		 *
		 *	\return		カプセル型の中心軸の終点位置ベクトル
		 *
		 *	\sa	setCapsule(), fk_Model::adjustCapsule()
		 */
		fk_Vector	getCapsuleEndPos(void);
		//@}

		//! \name 境界ボリューム描画制御関数
		//@{

		//! 境界ボリューム描画有無設定関数
		/*!
		 *	境界ボリュームに対し、描画の有無を制御します。
		 *
		 *	\param[in]	mode
		 *		true である場合、描画が有効となります。false である場合は無効となります。
		 *
		 *	\sa getBDrawToggle(), setBLineColor(), setBIntLineColor(), setBLineWidth()
		 */
		void		setBDrawToggle(bool mode);

		//! 境界ボリューム描画有無取得関数
		/*!
		 *	現在の境界ボリューム描画状態を取得します。
		 *
		 *	\return
		 *		現在の境界ボリューム描画が有効の場合 true を、
		 *		無効の場合 false を返します。
		 *
		 *	\sa	setBDrawToggle()
		 */
		bool		getBDrawToggle(void);

		//! 境界ボリューム非干渉描画色設定関数
		/*!
		 *	境界ボリューム描画の際に、非干渉状態である場合の線色を設定します。
		 *
		 *	\param[in]	col		線色
		 *
		 *	\sa	getBLineColor(), setBIntLineColor(), setBDrawToggle(),
		 *		fk_Model::isInter(), fk_Model::setInterMode()
		 */
		void		setBLineColor(fk_Color col);

		//! 境界ボリューム非干渉描画色取得関数
		/*!
		 *	境界ボリューム描画の際に、非干渉状態である場合の線色を取得します。
		 *
		 *	\return		線色
		 *
		 *	\sa	setBLineColor(), getBIntLineColor()
		 */
		fk_Color *	getBLineColor(void);

		//! 境界ボリューム干渉状態描画色設定関数
		/*!
		 *	境界ボリューム描画の際に、干渉状態である場合の線色を設定します。
		 *
		 *	\note
		 *		この線色で描画される条件は、
		 *		fk_Model::setInterMode() による設定によって異なります。
		 *
		 *	\param[in]	col		線色
		 *
		 *	\sa	getBIntLineColor(), setBLineColor(), setBDrawToggle(),
		 *		fk_Model::isInter(), fk_Model::setInterMode()
		 */
		void		setBIntLineColor(fk_Color col);

		//! 境界ボリューム干渉状態描画色取得関数
		/*!
		 *	境界ボリューム描画の際に、干渉状態である場合の線色を取得します。
		 *
		 *	\return		線色
		 *
		 *	\sa	setBIntLineColor(), getBLineColor()
		 */
		fk_Color *	getBIntLineColor(void);

		//!	境界ボリューム描画線幅設定関数
		/*!
		 *	境界ボリューム描画の際の線幅を設定します。
		 *
		 *	\param[in]	width		線幅
		 *
		 *	\sa setBDrawToggle(), setBLineColor(), setBIntLineColor()
		 */
		void		setBLineWidth(double width);

		//!	境界ボリューム描画線幅取得関数
		/*!
		 *	境界ボリューム描画の際の線幅を取得します。
		 *
		 *	\return		線幅
		 *
		 *	\sa setBLineWidth()
		 */
		double		getBLineWidth(void);
		//@}

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_IndexFaceSet *		GetBShape(void);
#endif

	private:
		fk_BoundaryMode		bMode;
		bool				bDrawToggle;
		fk_Color			*bLineColor, *bIntLineColor;
		double				bLineWidth;

		double				bSphereRad;
		fk_Vector			*bAABBSize;
		fk_Vector			*bOBBSize;
		fk_Vector			*bCapSPos, *bCapEPos;
		double				bCapRad;

		fk_IndexFaceSet		*bSphere;
		fk_IndexFaceSet		*bAABB;
		fk_IndexFaceSet		*bOBB;
		fk_IndexFaceSet		*bCapsule;
	};
}

#endif // !__FK_BOUNDARY_HEADER__
