#ifndef __FK_MODEL_HEADER__
#define __FK_MODEL_HEADER__

#include <FK/Boundary.h>
#include <FK/Palette.h>
#include <FK/RenderState.h>
#include <FK/Angle.h>
#include <FK/IndexFace.h>
#include <FK/Texture.h>
#include <FK/Tree.h>
#include <memory>
#include <functional>

namespace FK {
	class fk_Material;
	class fk_Shape;
	class fk_TreeData;
	class fk_Color;
	class fk_ShaderBinder;

	using fk_funcSet = std::tuple<unsigned int, std::function<void(void)> >;

	//! 描画優先モードを表す列挙型
	enum fk_ElementMode {
		FK_ELEM_NONE,		//!<	描画しない
		FK_ELEM_MODEL,		//!<	モデル設定優先
		FK_ELEM_ELEMENT		//!<	形状個別要素設定優先
	};

	//! モデルを生成、管理するクラス
	/*!
	 *	このクラスは、「モデル」を制御する機能を提供します。
	 *	FK における「モデル」とは、位置や方向を持ったオブジェクトのことを指します。
	 *	利用者は、
	 *	このクラスを通じてカメラを含むオブジェクトの位置や姿勢を制御していきます。
	 *	従って、このクラスは FK システムにおいて最も中心的な存在であると言えます。
	 *	位置や姿勢を制御するための関数の多くは、
	 *	fk_MatrixAdmin クラスから継承しています。
	 *	(ただし、後述する「親子関係」に関連する機能は本クラス自体が持っています。)
	 *	fk_MatrixAdmin クラスの説明も合わせて参照して下さい。
	 *
	 *	FK において、モデルと形状は別の存在として扱います。
	 *	形状は別のクラスで作成しておき、
	 *	モデルに対して形状をリンクするという考え方です。
	 *	このような設計になっている利点は、
	 *	まず第1に1つのモデルが複数の形状を使い分けられるということがあります。
	 *	第2に、1つの形状を複数のモデルで共有することでメモリ利用量を削減できます。
	 *	形状については fk_Shape クラスおよびその派生クラスを参照して下さい。
	 *
	 *	位置や姿勢の制御と共に、このクラスの重要な機能の1つが「親子関係」です。
	 *	あるモデルを別のモデルに「子モデル」として登録したとします。
	 *	親モデルの位置や姿勢を制御すると、
	 *	子モデルの形状は親モデル内の形状と同じように追従するようになります。
	 *	例えば、車を車体モデルとタイヤモデルで別々に作成し、
	 *	タイヤモデルを車体モデルの子モデルとして登録しておけば、
	 *	車体モデルの位置移動にあわせてタイヤモデルも位置関係を維持しながら
	 *	一緒に移動します。
	 *	マテリアルや頂点色、稜線色については、
	 *	何も設定しない場合は親モデルの設定が用いられます。
	 *	それぞれのモデルにマテリアルや色属性を設定した場合、
	 *	そのモデルについては個々の設定が利用されるようになります。
	 *
	 *	また、モデル同士の干渉判定や衝突判定を検出することができます。
	 *	干渉・衝突判定を行うには、
	 *	まず「境界ボリューム」と呼ばれるモデルを覆う領域を設定します。
	 *	その後、その境界ボリューム同士が干渉部分や衝突時間の検出を行うことで実現します。
	 *	本マニュアルにおいて、「干渉判定」と「衝突判定」は以下のような意味を持ちます。
	 *	- 干渉判定: \n
	 *		ある時点において、モデル同士に干渉部分があるかどうかを判定すること。
	 *	- 衝突判定: \n
	 *		2つのモデルが時刻 t0 から t1 まで等速度直線運動をしていたと仮定した場合に、
	 *		途中で衝突が起こったかどうかを判定すること。
	 *
	 *	本クラスのメンバ関数では、以下のような機能を提供します。
	 *		- setShape() にて形状を設定した後に自動的に境界ボリュームのサイズを設定する機能。
	 *		- 干渉判定や衝突判定を行う機能。
	 *		- 登録しておいたモデルと干渉した場合に自動的に停止する機能。
	 *
	 *	干渉判定は現在すべての種類の境界ボリュームで対応していますが、
	 *	同じ種類同士である必要があります。
	 *	衝突判定については、現在は境界球のみで対応しています。
	 *	境界ボリュームの種類に関する解説や、適用する境界ボリュームの選択については
	 *	fk_Boundary クラスのリファレンスを参照して下さい。
	 *
	 *	\sa fk_MatrixAdmin, fk_Boundary, fk_Shape, fk_Scene, fk_DisplayLink
	 */

	class fk_Model : public fk_Boundary {

	public:

		//! コンストラクタ
		/*!
		 *	\param[in]	shape
		 *		形状インスタンスのポインタ。
		 *		nullptr を代入した場合や引数を省略した場合は、
		 *		初期形状が無い状態になります。
		 */
		fk_Model(fk_Shape *shape = nullptr);

		//! デストラクタ
		virtual ~fk_Model();


		//! ID参照関数
		/*!
		 *	モデルの固有IDを取得します。
		 *	IDの最小値は 1 で、
		 *	同一プロセス中では同じ ID が別のモデルに割り振られることはありません。
		 *
		 *	\return		固有モデルID
		 */
		unsigned int	getID(void) const;

		//! \name 回転制御関数
		//@{

		//! グローバル座標系座標軸回転関数1
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、origin を通り、
		 *	axis で指定した座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は glRotateWithVec() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は loRotate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ fk_MatrixAdmin::glRotate_(fk_Vector &, fk_Axis, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		origin
		 *		グローバル座標系での回転軸上の点
		 *
		 *	\param[in]		axis
		 *		回転軸に平行な軸。fk_X, fk_Y, fk_Z のいずれかになります。
		 *
		 *	\param[in]		theta
		 *		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotateWithVec(fk_Vector, fk_Axis, double),
		 *		loRotate(fk_Vector, fk_Axis, double),
		 *		fk_MatrixAdmin::glRotate_(fk_Vector &, fk_Axis, double)
		 */
		bool	glRotate(fk_Vector origin, fk_Axis axis, double theta);

		//! グローバル座標系座標軸回転関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(orgX, orgY, orgZ) を通り、
		 *	axis で指定した座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は glRotateWithVec() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は loRotate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::glRotate_(double, double, double, fk_Axis, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		orgX		グローバル座標系での回転軸上の点のx成分
		 *	\param[in]		orgY		グローバル座標系での回転軸上の点のy成分
		 *	\param[in]		orgZ		グローバル座標系での回転軸上の点のz成分
		 *
		 *	\param[in]		axis
		 *		回転軸に平行な軸。fk_X, fk_Y, fk_Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotateWithVec(double, double, double, fk_Axis, double),
		 *		loRotate(double, double, double, fk_Axis, double),
		 *		fk_MatrixAdmin::glRotate_(double, double, double, fk_Axis, double)
		 */
		bool 	glRotate(double orgX, double orgY, double orgZ, fk_Axis axis, double theta);

		//! グローバル座標系任意軸回転関数1
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は glRotateWithVec() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は loRotate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::glRotate_(fk_Vector &, fk_Vector &, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		A		回転軸上の1点。B と一致してはいけません。
		 *	\param[in]		B		回転軸上の1点。A と一致してはいけません。
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec(fk_Vector, fk_Vector, double),
		 *		loRotate(fk_Vector, fk_Vector, double),
		 *		fk_MatrixAdmin::glRotate_(fk_Vector &, fk_Vector &, double)
		 */
		bool 	glRotate(fk_Vector A, fk_Vector B, double theta);

		//! グローバル座標系任意軸回転関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は glRotateWithVec() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は loRotate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::glRotate_(double, double, double, double, double, double, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		Ax		回転軸上の1点 A の x 成分
		 *	\param[in]		Ay		回転軸上の1点 A の y 成分
		 *	\param[in]		Az		回転軸上の1点 A の z 成分
		 *	\param[in]		Bx		回転軸上の1点 B の x 成分
		 *	\param[in]		By		回転軸上の1点 B の y 成分
		 *	\param[in]		Bz		回転軸上の1点 B の z 成分
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec(double, double, double, double, double, double, double),
		 *		loRotate(double, double, double, double, double, double, double),
		 *		fk_MatrixAdmin::glRotate_(double, double, double, double, double, double, double)
		 */
		bool	glRotate(double Ax, double Ay, double Az,
						 double Bx, double By, double Bz, double theta);

		//! ローカル座標系座標軸回転関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) origin を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は loRotateWithVec() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は glRotate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::loRotate_(fk_Vector &, fk_Axis, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		origin
		 *		ローカル座標系での回転軸上の点
		 *
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_X, fk_Y, fk_Z のいずれかになります。
		 *
		 *	\param[in]		theta
		 *		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotate(fk_Vector, fk_Axis, double),
		 *		loRotateWithVec(fk_Vector, fk_Axis, double),
		 *		fk_MatrixAdmin::loRotate_(fk_Vector &, fk_Axis, double)
		 */
		bool	loRotate(fk_Vector origin, fk_Axis axis, double theta);

		//! ローカル座標系座標軸回転関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) (orgX, orgY, orgZ) を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は loRotateWithVec() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は glRotate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::loRotate_(double, double, double, fk_Axis, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		orgX		ローカル座標系での回転軸上の点のx成分
		 *	\param[in]		orgY		ローカル座標系での回転軸上の点のy成分
		 *	\param[in]		orgZ		ローカル座標系での回転軸上の点のz成分
		 *
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_X, fk_Y, fk_Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotate(double, double, double, fk_Axis, double),
		 *		loRotateWithVec(double, double, double, fk_Axis, double),
		 *		fk_MatrixAdmin::loRotate_(double, double, double, fk_Axis, double)
		 */
		bool	loRotate(double orgX, double orgY, double orgZ, fk_Axis axis, double theta);

		//! ローカル座標系任意軸回転関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における) A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は loRotateWithVec() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は glRotate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::loRotate_(fk_Vector &, fk_Vector &, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		A
		 *		ローカル座標系における回転軸上の1点。B と一致してはいけません。
		 *
		 *	\param[in]		B
		 *		ローカル座標系における回転軸上の1点。A と一致してはいけません。
		 *
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec(fk_Vector, fk_Vector, double),
		 *		loRotate(fk_Vector, fk_Vector, double),
		 *		fk_MatrixAdmin::loRotate_(fk_Vector &, fk_Vector &, double)
		 */
		bool	loRotate(fk_Vector A, fk_Vector B, double theta);

		//! ローカル座標系任意軸回転関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における)
		 *	(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は loRotateWithVec() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は glRotate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::loRotate_(double, double, double, double, double, double, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		Ax
		 *		ローカル座標系における回転軸上の1点 A の x 成分
		 *
		 *	\param[in]		Ay
		 *		ローカル座標系における回転軸上の1点 A の y 成分
		 *
		 *	\param[in]		Az
		 *		ローカル座標系における回転軸上の1点 A の z 成分
		 *
		 *	\param[in]		Bx
		 *		ローカル座標系における回転軸上の1点 B の x 成分
		 *
		 *	\param[in]		By
		 *		ローカル座標系における回転軸上の1点 B の y 成分
		 *
		 *	\param[in]		Bz
		 *		ローカル座標系における回転軸上の1点 B の z 成分
		 *
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec(double, double, double, double, double, double, double),
		 *		loRotate(double, double, double, double, double, double, double),
		 *		fk_MatrixAdmin::loRotate_(double, double, double, double, double, double, double)
		 */
		bool	loRotate(double Ax, double Ay, double Az,
						 double Bx, double By, double Bz, double theta);

		//! グローバル座標系座標軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、origin を通り、
		 *	axis で指定した座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は glRotate() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	loRotateWithVec() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::glRotateWithVec_(fk_Vector &, fk_Axis, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		origin		グローバル座標系での回転軸上の点
		 *
		 *	\param[in]		axis
		 *		回転軸に平行な軸。fk_X, fk_Y, fk_Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotate(fk_Vector, fk_Axis, double),
		 *		loRotateWithVec(fk_Vector, fk_Axis, double),
		 *		fk_MatrixAdmin::glRotateWithVec_(fk_Vector &, fk_Axis, double)
		 */
		bool	glRotateWithVec(fk_Vector origin, fk_Axis axis, double theta);


		//! グローバル座標系座標軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(orgX, orgY, orgZ) を通り、
		 *	axis で指定した座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は glRotate() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	loRotateWithVec() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::glRotateWithVec_(double, double, double, fk_Axis, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		orgX		グローバル座標系での回転軸上の点のx成分
		 *	\param[in]		orgY		グローバル座標系での回転軸上の点のy成分
		 *	\param[in]		orgZ		グローバル座標系での回転軸上の点のz成分
		 *
		 *	\param[in]		axis
		 *		回転軸に平行な軸。fk_X, fk_Y, fk_Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glRotate(double, double, double, fk_Axis, double),
		 *		loRotateWithVec(double, double, double, fk_Axis, double),
		 *		fk_MatrixAdmin::glRotateWithVec_(double, double, double, fk_Axis, double)
		 */
		bool	glRotateWithVec(double orgX, double orgY, double orgZ,
								fk_Axis axis, double theta);

		//! グローバル座標系任意軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は glRotate() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	loRotateWithVec() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::glRotateWithVec_(fk_Vector &, fk_Vector &, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		A		回転軸上の1点。B と一致してはいけません。
		 *	\param[in]		B		回転軸上の1点。A と一致してはいけません。
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotate(fk_Vector, fk_Vector, double),
		 *		loRotateWithVec(fk_Vector, fk_Vector, double),
		 *		fk_MatrixAdmin::glRotateWithVec_(fk_Vector &, fk_Vector &, double)
		 */
		bool	glRotateWithVec(fk_Vector A, fk_Vector B, double theta);

		//! グローバル座標系任意軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は glRotate() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	loRotateWithVec() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、同機能を持つ
		 *		fk_MatrixAdmin::glRotateWithVec_(double, double, double, double, double, double, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		Ax		回転軸上の1点 A の x 成分
		 *	\param[in]		Ay		回転軸上の1点 A の y 成分
		 *	\param[in]		Az		回転軸上の1点 A の z 成分
		 *	\param[in]		Bx		回転軸上の1点 B の x 成分
		 *	\param[in]		By		回転軸上の1点 B の y 成分
		 *	\param[in]		Bz		回転軸上の1点 B の z 成分
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotate(double, double, double, double, double, double, double),
		 *		loRotateWithVec(double, double, double, double, double, double, double),
		 *		fk_MatrixAdmin::glRotateWithVec_(double, double, double, double, double, double, double)
		 */
		bool	glRotateWithVec(double Ax, double Ay, double Az,
								double Bx, double By, double Bz, double theta);

		//! ローカル座標系座標軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) origin を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は loRotate() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	glRotateWithVec() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::loRotateWithVec_(fk_Vector &, fk_Axis, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		origin		ローカル座標系での回転軸上の点
		 *
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_X, fk_Y, fk_Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa loRotate(fk_Vector, fk_Axis, double),
		 *		glRotateWithVec(fk_Vector, fk_Axis, double),
		 *		fk_MatrixAdmin::loRotateWithVec_(fk_Vector &, fk_Axis, double)
		 */
		bool	loRotateWithVec(fk_Vector origin, fk_Axis axis, double theta);

		//! ローカル座標系座標軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) (orgX, orgY, orgZ) を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は loRotate() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	glRotateWithVec() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::loRotateWithVec_(double, double, double, fk_Axis, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		orgX		ローカル座標系での回転軸上の点のx成分
		 *	\param[in]		orgY		ローカル座標系での回転軸上の点のy成分
		 *	\param[in]		orgZ		ローカル座標系での回転軸上の点のz成分
		 *
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_X, fk_Y, fk_Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa loRotate(double, double, double, fk_Axis, double),
		 *		glRotateWithVec(double, double, double, fk_Axis, double),
		 *		fk_MatrixAdmin::loRotateWithVec_(double, double, double, fk_Axis, double)
		 */
		bool	loRotateWithVec(double orgX, double orgY, double orgZ,
								fk_Axis axis, double theta);

		//! ローカル座標系任意軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における) A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は loRotate() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	glRotateWithVec() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::loRotateWithVec_(fk_Vector &, fk_Vector &, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		A
		 *		ローカル座標系における回転軸上の1点。B と一致してはいけません。
		 *
		 *	\param[in]		B
		 *		ローカル座標系における回転軸上の1点。A と一致してはいけません。
		 *
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec(fk_Vector, fk_Vector, double)
		 *		loRotate(fk_Vector, fk_Vector, double),
		 *		fk_MatrixAdmin::loRotateWithVec_(fk_Vector &, fk_Vector &, double)
		 */
		bool	loRotateWithVec(fk_Vector A, fk_Vector B, double theta);

		//! ローカル座標系任意軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における)
		 *	(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は loRotate() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	glRotateWithVec() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、同機能を持つ
		 *		fk_MatrixAdmin::loRotateWithVec_(double, double, double, double, double, double, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		Ax
		 *		ローカル座標系における回転軸上の1点 A の x 成分
		 *
		 *	\param[in]		Ay
		 *		ローカル座標系における回転軸上の1点 A の y 成分
		 *
		 *	\param[in]		Az
		 *		ローカル座標系における回転軸上の1点 A の z 成分
		 *
		 *	\param[in]		Bx
		 *		ローカル座標系における回転軸上の1点 B の x 成分
		 *
		 *	\param[in]		By
		 *		ローカル座標系における回転軸上の1点 B の y 成分
		 *
		 *	\param[in]		Bz
		 *		ローカル座標系における回転軸上の1点 B の z 成分
		 *
		 *	\param[in]		theta	回転角度(ラジアン)
		 *
		 *	\return
		 *		回転が成功した場合 true を返します。
		 *		A と B が同一位置ベクトルであった場合、
		 *		回転せずに false を返します。
		 *
		 *	\sa glRotateWithVec(double, double, double, double, double, double, double),
		 *		loRotate(double, double, double, double, double, double, double),
		 *		fk_MatrixAdmin::loRotateWithVec_(double, double, double, double, double, double, double)
		 */
		bool	loRotateWithVec(double Ax, double Ay, double Az,
								double Bx, double By, double Bz, double theta);
		//@}

		//! \name 位置制御関数
		//@{

		//! グローバル座標系平行移動関数1
		/*!
		 *	モデルを、クローバル座標系によって平行移動した位置に移動します。
		 *	平行移動量はベクトルで指定します。
		 *
		 *	ローカル座標系による平行移動量の指定を行いたい場合は、
		 *	loTranslate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::glTranslate_(fk_Vector &)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		v		平行移動量ベクトル
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa loTranslate(fk_Vector), fk_MatrixAdmin::glTranslate_(fk_Vector &)
		 */
		bool	glTranslate(fk_Vector v);

		//! グローバル座標系平行移動関数2
		/*!
		 *	モデルを、クローバル座標系によって平行移動した位置に移動します。
		 *	平行移動量はベクトルの成分を意味する3個の実数で指定します。
		 *
		 *	ローカル座標系による平行移動量の指定を行いたい場合は、
		 *	loTranslate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::glTranslate_(double, double, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		x		平行移動量ベクトルのx成分
		 *	\param[in]		y		平行移動量ベクトルのy成分
		 *	\param[in]		z		平行移動量ベクトルのz成分
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa loTranslate(double, double, double),
		 *		fk_MatrixAdmin::glTranslate_(double, double, double)
		 */
		bool	glTranslate(double x, double y, double z);

		//! ローカル座標系平行移動関数1
		/*!
		 *	モデルを、ローカル座標系によって平行移動した位置に移動します。
		 *	平行移動量はベクトルで指定します。
		 *
		 *	グローバル座標系による平行移動量の指定を行いたい場合は、
		 *	glTranslate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::loTranslate_(fk_Vector &)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		v		平行移動量ベクトル
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glTranslate(fk_Vector), glMoveTo(fk_Vector),
		 *		fk_MatrixAdmin::loTranslate_(fk_Vector &)
		 */
		bool	loTranslate(fk_Vector v);

		//! ローカル座標系平行移動関数2
		/*!
		 *	モデルを、ローカル座標系によって平行移動した位置に移動します。
		 *	平行移動量はベクトルの成分を意味する3個の実数で指定します。
		 *
		 *	グローバル座標系による平行移動量の指定を行いたい場合は、
		 *	glTranslate() を利用して下さい。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::loTranslate_(double, double, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		x		平行移動量ベクトルのx成分
		 *	\param[in]		y		平行移動量ベクトルのy成分
		 *	\param[in]		z		平行移動量ベクトルのz成分
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glTranslate(double, double, double), glMoveTo(double, double, double),
		 *		fk_MatrixAdmin::loTranslate_(double, double, double)
		 */
		bool	loTranslate(double x, double y, double z);

		//! グローバル座標系位置指定関数1
		/*!
		 *	モデルの位置を、指定した位置ベクトルに移動します。
		 *	位置はベクトルで指定します。
		 *
		 *	glMoveTo() 関数に対応するローカル座標系関数
		 *	「loMoveTo()」関数は存在しません。
		 *	これは、loMoveTo() 関数はその意味的に
		 *	loTranslate() とまったく同一の挙動となるためです。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::glMoveTo_(fk_Vector &)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		p		移動先位置ベクトル
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glTranslate(fk_Vector), loTranslate(fk_Vector),
		 *		fk_MatrixAdmin::glMoveTo_(fk_Vector &)
		 */
		bool	glMoveTo(fk_Vector p);

		//! グローバル座標系位置指定関数2
		/*!
		 *	モデルの位置を、指定した位置ベクトルに移動します。
		 *	位置はベクトルの成分を意味する3個の実数で指定します。
		 *
		 *	glMoveTo() 関数に対応するローカル座標系関数
		 *	「loMoveTo()」関数は存在しません。
		 *	これは、loMoveTo() 関数はその意味的に
		 *	loTranslate() とまったく同一の挙動となるためです。
		 *
		 *	\note
		 *		「干渉自動停止モード」を利用しない場合は、
		 *		同機能を持つ
		 *		fk_MatrixAdmin::glMoveTo_(double, double, double)
		 *		を用いた方が、処理がわずかに速くなります。
		 *
		 *	\param[in]		x		移動先位置ベクトルのx成分
		 *	\param[in]		y		移動先位置ベクトルのy成分
		 *	\param[in]		z		移動先位置ベクトルのz成分
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa glTranslate(double, double, double), loTranslate(double, double, double),
		 *		fk_MatrixAdmin::glMoveTo_(double, double, double)
		 */
		bool	glMoveTo(double x, double y, double z);
		//@}

		//! \name 形状データ制御関数
		//@{

		//! 形状設定関数
		/*!
		 *	モデルの形状を設定します。
		 *	形状は、 fk_Shape クラスの派生クラスであれば設定可能です。
		 *	なお、呼ぶ前に形状が設定されていた場合、前の設定は破棄されます。
		 *
		 *	設定した形状インスタンスは、モデルに設定した状態で解放しないようにしてください。
		 *	もし解放された場合、プログラムが誤動作を起こします。
		 *
		 *	\param[in]	shape		形状インスタンスのポインタ
		 */
		void	setShape(fk_Shape *shape);

		//! 形状参照関数
		/*!
		 *	現在設定されている形状を取得します。
		 *	形状が設定されていない場合は nullptr を返します。
		 *
		 *	\return		形状インスタンスのポインタ
		 */
		fk_Shape *	getShape(void) const;

		//@}

		//! \name マテリアル属性設定関数
		//@{
		//! マテリアル設定関数
		/*!
		 *	モデルの基本マテリアルを設定します。
		 *	マテリアルに関しての詳細は、
		 *	fk_Material の説明およびユーザーズマニュアルを参照して下さい。
		 *
		 *	\note
		 *		稜線の色は setLineColor(), 
		 *		頂点の色は setPointColor() を利用して設定して下さい。
		 *		個別位相要素のマテリアルとの制御については、
		 *		setMaterialMode() を参照して下さい。
		 *		テクスチャを描画する際には、テクスチャモードによって混合の仕方が異なりますので、
		 *		fk_Texture::setTextureMode() を参照して下さい。
		 *
		 *	\param[in]	mat		マテリアル
		 *
		 *	\sa fk_Material, setLineColor(), setPointColor(), fk_Texture::setTextureMode()
		 */
		void	setMaterial(const fk_Material &mat);

		//! 頂点色設定関数1
		/*!
		 *	モデルの頂点色を設定します。
		 *	頂点は、光源による陰影の影響はなく、常に設定色で表示されます。
		 *
		 *	\param[in]	col		頂点色のポインタ
		 *
		 *	\sa fk_Color
		 */
		void	setPointColor(fk_Color *col);

		//! 頂点色設定関数2
		/*!
		 *	モデルの頂点色を設定します。
		 *	頂点は、光源による陰影の影響はなく、常に設定色で表示されます。
		 *	各色要素は 0 から 1 までの値を取ります。
		 *	それ以外の値が与えられた場合、0 以下なら 0 に、1 以上なら 1 に丸められます。
		 *
		 *	\param[in]	r		頂点色の赤要素
		 *	\param[in]	g		頂点色の緑要素
		 *	\param[in]	b		頂点色の青要素
		 */
		void	setPointColor(float r, float g, float b);

		//! 稜線色設定関数1
		/*!
		 *	モデルの稜線色を設定します。
		 *	稜線は、光源による陰影の影響はなく、常に設定色で表示されます。
		 *
		 *	\param[in]	col		稜線色のポインタ
		 *
		 *	\sa fk_Color
		 */
		void	setLineColor(fk_Color *col);

		//! 稜線色設定関数2
		/*!
		 *	モデルの稜線色を設定します。
		 *	稜線は、光源による陰影の影響はなく、常に設定色で表示されます。
		 *	各色要素は 0 から 1 までの値を取ります。
		 *	それ以外の値が与えられた場合、0 以下なら 0 に、1 以上なら 1 に丸められます。
		 *
		 *	\param[in]	r		稜線色の赤要素
		 *	\param[in]	g		稜線色の緑要素
		 *	\param[in]	b		稜線色の青要素
		 */
		void	setLineColor(float r, float g, float b);

		//@}

		//! \name マテリアル属性参照関数
		//@{
		//! マテリアル参照関数
		/*!
		 *	現在モデルに設定されている基本マテリアルを参照します。
		 *
		 *	\return		基本マテリアルのポインタ
		 *
		 *	\sa fk_Material, setMaterial()
		 */
		fk_Material *	getMaterial(void);

		//! 頂点色参照関数
		/*!
		 *	現在モデルに設定されている頂点色を参照します。
		 *
		 *	\return		頂点色のポインタ
		 *
		 *	\sa fk_Color, setPointColor()
		 */
		fk_Color *	getPointColor(void);

		//! 稜線色参照関数
		/*!
		 *	現在モデルに設定されている稜線色を参照します。
		 *	モデルに稜線色が設定されていない場合は nullptr を返します。
		 *
		 *	\return		稜線色のポインタ
		 *
		 *	\sa fk_Color, setLineColor()
		 */
		fk_Color *	getLineColor(void);

		//@}

		//! \name 描画属性制御関数
		//@{

		//! 頂点描画サイズ設定関数
		/*!
		 *	頂点の描画サイズを設定します。
		 *	単位はピクセルです。整数以外も設定可能です。
		 *
		 *	\param[in]	size	頂点描画サイズ
		 *
		 *	\sa	getPointSize(), setLineWidth()
		 */
		void	setPointSize(const double size);


		//! 頂点描画サイズ参照関数
		/*!
		 *	頂点の描画サイズを取得します。
		 *
		 *	\return		頂点描画サイズ
		 *
		 *	\sa	setPointSize()
		 */
		double	getPointSize(void) const;

		//@}

		//! \name 描画モード制御関数
		//@{

		//! 描画モード設定関数
		/*!
		 *	モデルの描画モードを設定します。
		 *	描画モードとは、
		 *	面、稜線、頂点のそれぞれを描画するかどうかを制御するものです。
		 *	描画モード種類は以下のとおりです。
		 *	- FK_NONEMODE:				何も描画しません。
		 *	- FK_POINTMODE:				頂点を描画します。
		 *	- FK_LINEMODE:				稜線を描画します。
		 *	- FK_POLYMODE:				面の表を描画します。
		 *	- FK_BACK_POLYMODE:			面の裏を描画します。
		 *	- FK_FRONTBACK_POLYMODE:	面の表と裏を描画します。
		 *	- FK_TEXTUREMODE:			テクスチャを描画します。
		 *	.
		 *	これらの描画モードは、
		 *	ビット論理和を用いて複数のものを同時に指定することが可能です。
		 *	以下のコードは、頂点、稜線、面の表をすべて描画するように設定します。
		 *
		 *		fk_Model		model;
		 *		
		 *		model.setDrawMode(FK_POINTMODE | FK_LINEMODE | FK_POLYMODE);
		 *
		 *	\param[in]	mode	描画モード
		 */
		void	setDrawMode(const fk_DrawMode mode);

		//! 描画モード参照関数
		/*!
		 *	現在の描画モードを参照します。
		 *
		 *	\return		描画モード
		 *
		 *	\sa setDrawMode()
		 */
		fk_DrawMode		getDrawMode(void) const;

		//! 要素モード設定関数
		/*!
		 *	形状表示の際、モデル設定と形状個別要素設定のどちらを採用するかを設定します。
		 *	モードには以下のものがあります。
		 *	- FK_ELEM_NONE:		何も描画しません。
		 *	- FK_ELEM_MODEL:	モデル設定を優先します。
		 *	- FK_ELEM_ELEMENT:	形状内の個別要素設定を優先します。
		 *	.
		 *
		 *	\param[in]	mode	設定モード
		 */
		void			setElementMode(const fk_ElementMode mode);

		//! 要素モード設定関数
		/*!
		 *	表示の際の優先モードを取得します。
		 *
		 *	\return	設定モード
		 *
		 *	\sa setElementMode()
		 */
		fk_ElementMode	getElementMode(void) const;
		
		//! ブレンドモード設定関数
		/*!
		 *	テクスチャ画像を伴うモデルを表示する場合、
		 *	表示色はテクスチャ画像の各画素色と、
		 *	モデルに設定されているマテリアルの両方が関与します。
		 *	この関数は、テクスチャ画像の画素色とモデルのマテリアル色に対し、
		 *	どのような計算式で双方を混合(ブレンド)するかを設定します。
		 *	ここでブレンドモードを設定しても、fk_Scene:setBlendStatus() で
		 *	ブレンドを有効にしていないと実際の描画で有効になりません。
		 *	ブレンドモードの設定は、一般的な設定をプリセットの中から選択するか、
		 *	カスタムモードを選択した上で、入力ピクセルと出力ピクセルに対する係数を
		 *	個別に指定するかのどちらかによって行います。
		 *
		 *	\param[in]	mode
		 *		ブレンドモードを設定します。与えられる値は以下の8種類です。
		 *		- FK_BLEND_ALPHA_MODE:		通常のアルファブレンドです。初期値です。
		 *		- FK_BLEND_NEGATIVE_MODE:	反転ブレンドです。
		 *		- FK_BLEND_ADDITION_MODE:	加算ブレンドです。
		 *		- FK_BLEND_SCREEN_MODE:		アルファ付き加算ブレンドです。
		 *		- FK_BLEND_LIGHTEN_MODE:	入出力ピクセルのうち明るい方を採用するブレンドです。
		 *		- FK_BLEND_MULTIPLY_MODE:	乗算ブレンドです。
		 *		- FK_BLEND_NONE_MODE:		ブレンドを行いません。
		 *									fk_Scene 側の設定によらずブレンドを無効にします。
		 *		- FK_BLEND_CUSTOM_MODE:		カスタムモードです。第 2,3 引数にて指定した
		 *									係数を用いた計算式でブレンドします。
		 *
		 *	\param[in]	srcFactor
		 *		入力ピクセルに対する係数を設定します。
		 *		mode に FK_BLEND_CUSTOM_MODE を指定した場合のみ有効です。
		 *		それ以外のモードでは省略可能です。
		 *		本関数の仕様は OpenGL 関数の glBlendFunc() に準拠します。
		 *		詳細は glBlendFunc() の情報を参照して下さい。
		 *		与えられる値は以下の10種類で、
		 *		それぞれの「FK_FACTOR」を「GL」に置き換えた GLenum 型の値に対応します。
		 *		- FK_FACTOR_ZERO
		 *		- FK_FACTOR_ONE
		 *		- FK_FACTOR_SRC_COLOR
		 *		- FK_FACTOR_ONE_MINUS_SRC_COLOR
		 *		- FK_FACTOR_DST_COLOR
		 *		- FK_FACTOR_ONE_MINUS_DST_COLOR
		 *		- FK_FACTOR_SRC_ALPHA
		 *		- FK_FACTOR_ONE_MINUS_SRC_ALPHA
		 *		- FK_FACTOR_DST_ALPHA
		 *		- FK_FACTOR_ONE_MINUS_DST_ALPHA
		 *
		 *	\param[in]	dstFactor
		 *		出力ピクセルに対する係数を設定します。
		 *		mode に FK_CUSTOM_BLEND_MODE を指定した場合のみ有効です。
		 *		それ以外のモードでは省略可能です。与えられる値は srcFactor と同様です。
		 *
		 *	\sa getBlendMode(), fk_Scene::setBlendStatus(), fk_Scene::getBlendStatus()
		 */
		void	setBlendMode(const fk_BlendMode mode,
							 const fk_BlendFactor srcFactor = FK_FACTOR_SRC_ALPHA,
							 const fk_BlendFactor dstFactor = FK_FACTOR_ONE_MINUS_SRC_ALPHA);

		//! ブレンドモード参照関数
		/*!
		 *	モデルのブレンドモードを取得します。
		 *
		 *	\param[out]	outSrc
		 *		入力ピクセルにかかる係数の種類を取得します。省略可能です。
		 *	\param[out]	outDst
		 *		出力ピクセルにかかる係数の種類を取得します。省略可能です。
		 *	\return		ブレンドモード
		 *
		 *	\sa setBlendMode()
		 */
		fk_BlendMode		getBlendMode(fk_BlendFactor *outSrc = nullptr,
										 fk_BlendFactor *outDst = nullptr) const;

		//! スムースモード設定関数
		/*!
		 *	モデルのスムースモードを設定します。
		 *	スムースモードを有効にすると、
		 *	形状の隣り合う面同士の法線ベクトルが補間され、
		 *	擬似的に滑らかな曲面として表示を行うようになります。
		 *
		 *	\param[in]	mode	true である場合、スムースモードを有効とします。
		 *		false である場合無効とします。
		 */
		void	setSmoothMode(const bool mode);

		//! スムースモード参照関数
		/*!
		 *	現在のモデルのスムースモードを取得します。
		 *
		 *	\return		有効である場合 true を、無効である場合 false を返します。
		 *
		 *	\sa setSmoothMode()
		 */
		bool	getSmoothMode(void) const;

		//! 描画順序制御関数
		/*!
		 *	この関数では、モデルの持つ位相要素の描画順序を制御します。
		 *	モデルの各位相要素が同一平面上にあり、描画順序を逆にしたい場合に用います。
		 *
		 *	\param[in]	mode
		 *		true の場合、モデル内の描画が通常と逆順になります。
		 *		false の場合、順序を通常の状態に戻します。
		 */
		void	setReverseDrawMode(const bool mode);

		//! 描画順序参照関数
		/*!
		 *	setReverseDrawMode() で設定した描画順序を取得します。
		 *
		 *	\return		逆順である場合 true を、正順である場合 false を返します。
		 *
		 *	\sa setReverseDrawMode()
		 */
		bool	getReverseDrawMode(void) const;

		//! 前後関係制御関数
		/*!
		 *	この関数では、モデルを描画する際の前後関係に関する設定を制御します。
		 *	fk_Scene::entryOverlayModel()でも前後関係を無視した描画はできますが、
		 *	通常の描画中に前後関係を無視したり、
		 *	半透明物体が後続の描画の前後関係に作用しないようにするなど、
		 *	細かな調整を行いたい場合に用います。
		 *
		 *	\param[in]	mode
		 *		前後関係の処理モードを設定します。与えられる値は以下の4種類です。
		 *		- FK_DEPTH_NO_USE:			前後関係の参照も更新も行わず、常に上書きします。
		 *		- FK_DEPTH_READ:			前後関係を参照してチェックします。
		 *		- FK_DEPTH_WRITE:			前後関係を更新して後続の描画に影響するようにします。
		 *		- FK_DEPTH_READ_AND_WRITE:	前後関係を参照しつつ更新します。
		 *									FK_DEPTH_READ | FK_DEPTH_WRITE と等価です。初期値です。
		 */
		void	setDepthMode(const fk_DepthMode mode);

		//! 前後関係参照関数
		/*!
		 *	setDepthMode() で設定した前後関係の設定を取得します。
		 *
		 *	\return		前後関係処理モード
		 *
		 *	\sa setDepthMode()
		 */
		fk_DepthMode	getDepthMode(void) const;

		//! テクスチャモード設定関数
		/*!
		 *	テクスチャの描画時における描画色処理モードを設定します。
		 *	これは、ポリゴンに設定されているマテリアルによる発色と、
		 *	テクスチャ画像の色をどのように混成するかを制御するものです。
		 *	それぞれのモードの概要と厳密な計算式を以下に記載します。
		 *	なお、数式中の \f$ C_f \f$ はポリゴン色、
		 *	\f$ C_\alpha \f$ ポリゴンの透明度、
		 *	\f$ T_f \f$ はテクスチャピクセル色、
		 *	\f$ T_\alpha \f$ はテクスチャの透明度を表します。
		 *
		 *	- FK_TEX_MODULATE \n
		 *		この設定では、ポリゴンの色とテクスチャの色を積算します。
		 *		そのため、光源による陰影効果が生じます。
		 *		透明度に関しても積算となります。
		 *		数式として表すと、色と透明度はそれぞれ
		 *		\f[
		 *			(C_f T_f, \; C_\alpha T_\alpha)
		 *		\f]
		 *		となります。
		 *
		 *	- FK_TEX_REPLACE \n
		 *		この設定では、ポリゴンの色は完全に無視され、
		 *		テクスチャのピクセル色がそのまま表示されます。
		 *		そのため、光源による陰影効果が生じません。
		 *		また、テクスチャ画像の透明度はそのまま描画に反映されます。
		 *		数式として表すと、色と透明度はそれぞれ
		 *		\f[
		 *			(T_f, \; T_\alpha)
		 *		\f]
		 *		となります。
		 *
		 *	- FK_TEX_DECAL \n
		 *		この設定では、各ピクセルの透明度に応じて、
		 *		ポリゴン色とピクセル色の混合が行われます。
		 *		光源による陰影効果は、ピクセルの透明度が低い場合に強くなります。
		 *		透明度は、ポリゴンの透明度がそのまま適用されます。
		 *		これを数式として表すと、色と透明度はそれぞれ
		 *		\f[
		 *			(C_f (1-T_\alpha) + T_f T_\alpha, \; C_\alpha)
		 *		\f]
		 *		となります。
		 *
		 *	- FK_TEX_NONE \n
		 *		この設定では、 fk_Model での設定は無視し、
		 *		fk_Texture::setTextureMode() での設定に従います。
		 *	.
		 *	デフォルトでは FK_TEX_NONE が設定されています。
		 *	なお、同様の設定は fk_Texture::setTextureMode() でも行うことが可能で、
		 *	fk_Model 側で FK_TEX_NONE 以外が設定されている場合は fk_Model 側の設定が優先されます。
		 *	fk_Model 側で FK_TEX_NONE が設定されている場合のみ、
		 *	fk_Texture 側での設定が有効となります。
		 *
		 *	\param[in]		mode	モード
		 *
		 *	\sa getTextureMode(), fk_Texture::setTextureMode()
		 */
		void	setTextureMode(fk_TexMode mode);
		
		//! テクスチャモード取得関数
		/*!
		 *	現在のテクスチャモードを取得します。
		 *
		 *	\return		テクスチャモード
		 *
		 *	\sa setTextureMode()
		 */
		fk_TexMode		getTextureMode(void);
		//@}

		//! \name 座標系情報参照関数
		//@{

		//! 継承変換行列取得関数
		/*!
		 *	モデルの位置と姿勢を表す変換行列を取得します。
		 *	当モデルに親モデルがあった場合、
		 *	その親モデルの変換行列と当モデルの変換行列の積が返されます。
		 *	結果として、この関数を用いることでグローバル座標系における
		 *	当モデルの変換行列を得ることができます。
		 *	親モデルが設定されていない場合は、
		 *	fk_MatrixAdmin::getMatrix() と結果が同じとなります。
		 *
		 *	\return		モデルの継承変換行列
		 *
		 *	\sa fk_MatrixAdmin::getMatrix(), getInhInvMatrix()
		 */
		fk_Matrix	getInhMatrix(void) const;

		//! 継承逆変換行列取得関数
		/*!
		 *	モデルの位置と姿勢を表す変換行列の、逆行列を取得します。
		 *	これは、 getInhMatrix() で得られる行列の逆行列となります。
		 *	当モデルに親モデルがあった場合、
		 *	その親モデルの逆変換行列と当モデルの逆変換行列の積が返されます。
		 *	結果として、この関数を用いることでグローバル座標系における
		 *	当モデルの逆変換行列を得ることができます。
		 *	親モデルが設定されていない場合は、
		 *	fk_MatrixAdmin::getInvMatrix() と結果が同じとなります。
		 *
		 *	\return		モデルの継承逆変換行列
		 *
		 *	\sa fk_MatrixAdmin::getInvMatrix(), getInhMatrix()
		 */
		fk_Matrix	getInhInvMatrix(void) const;

		//! 継承移動・回転要素変換行列取得関数
		/*!
		 *	モデルの持つ変換要素のうち、
		 *	位置と姿勢のみを反映した、
		 *	すなわち拡大縮小の要素を省いた変換行列を取得します。
		 *	当モデルに親モデルがあった場合、
		 *	その親モデルの変換行列と当モデルの変換行列の積が返されます。
		 *	その結果として、この関数を用いることでグローバル座標系における
		 *	当モデルの変換行列を得ることができます。
		 *	親モデルが設定されていない場合は、
		 *	fk_MatrixAdmin::getBaseMatrix() と結果が同じとなります。
		 *
		 *	\return		モデルの継承移動・回転要素変換行列
		 *
		 *	\sa fk_MatrixAdmin::getBaseMatrix(), getInhMatrix(), getInhInvBaseMatrix()
		 */
		fk_OrthoMatrix	getInhBaseMatrix(void) const;

		//! 継承移動・回転要素逆変換行列取得関数
		/*!
		 *	モデルの持つ変換要素のうち、
		 *	位置と姿勢のみを反映した、
		 *	すなわち拡大縮小の要素を省いた変換行列の逆行列を取得します。
		 *	当モデルに親モデルがあった場合、
		 *	その親モデルの逆変換行列と当モデルの逆変換行列の積が返されます。
		 *	その結果として、この関数を用いることでグローバル座標系における
		 *	当モデルの逆変換行列を得ることができます。
		 *	親モデルが設定されていない場合は、
		 *	fk_MatrixAdmin::getInvBaseMatrix() と結果が同じとなります。
		 *
		 *	\return		モデルの継承移動・回転要素逆変換行列
		 *
		 *	\sa fk_MatrixAdmin::getInvBaseMatrix(), getInhInvMatrix(), getInhBaseMatrix()
		 */
		fk_OrthoMatrix	getInhInvBaseMatrix(void) const;

		//! 継承位置ベクトル参照関数
		/*!
		 *	モデルの位置ベクトルを取得します。
		 *	本関数は、親モデルの有無にかかわらず、グローバル座標系での実際の位置ベクトルを返します。
		 *
		 *	\return		グローバル座標系での位置ベクトル
		 *
		 *	\sa getInhVec(), getInhUpvec(), getInhAngle(), fk_MatrixAdmin::getPosition()
		 */
		fk_Vector	getInhPosition(void) const;

		//! 継承方向ベクトル参照関数
		/*!
		 *	モデルの方向ベクトルを取得します。
		 *	本関数は、親モデルの有無にかかわらず、グローバル座標系での実際の方向ベクトルを返します。
		 *
		 *	\return		グローバル座標系での方向ベクトル
		 *
		 *	\sa getInhPosition(), getInhUpvec(), getInhAngle(), fk_MatrixAdmin::getVec()
		 */
		fk_Vector	getInhVec(void) const;

		//! 継承アップベクトル参照関数
		/*!
		 *	モデルのアップベクトルを取得します。
		 *	本関数は、親モデルの有無にかかわらず、
		 *	グローバル座標系での実際のアップベクトルを返します。
		 *
		 *	\return		グローバル座標系でのアップベクトル
		 *
		 *	\sa getInhPosition(), getInhVec(), getInhAngle(), fk_MatrixAdmin::getUpvec()
		 */
		fk_Vector	getInhUpvec(void) const;

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Vector	getInhUpVec(void) const;
		void		setPickMode(const bool);
		bool		getPickMode(void) const;
		void		setMaterialMode(const fk_MaterialMode mode);
		fk_MaterialMode		getMaterialMode(void) const;
#endif

		//! 継承オイラー角参照関数
		/*!
		 *	モデルのオイラー角を取得します。
		 *	本関数は、親モデルの有無にかかわらず、グローバル座標系での実際のオイラー角を返します。
		 *	オイラー角の詳細については、 fk_Angle の説明を参照して下さい。
		 *
		 *	\return		
		 *
		 *	\sa getInhPosition(), getInhVec(), getInhUpvec(), fk_MatrixAdmin::getAngle(), fk_Angle
		 */
		fk_Angle	getInhAngle(void) const;

		//! 継承全体倍率取得関数
		/*!
		 *	モデルの全体拡大・縮小倍率を取得します。
		 *	親子関係の小モデルの場合、親モデルでの倍率も反映されます。
		 *
		 *	\return		継承全体拡大・縮小倍率
		 *
		 *	\sa getInhPosition(), getInhVec(), getInhUpvec(),
		 *		getInhAngle(), fk_MatrixAdmin::getScale()
		 */
		double	getInhScale(void) const;
		//@}

		//! \name 親子関係制御関数
		//@{

		//! 親モデル設定関数
		/*!
		 *	親モデルを設定します。
		 *	親モデルは 1 個しか設定できません。
		 *	前に設定されていた場合は、前のモデル設定は破棄されます。
		 *
		 *	\param[in]		model		親モデルインスタンスのポインタ
		 *
		 *	\param[in]		setMode
		 *		true の場合、現在のグローバル座標系の位置と姿勢を、
		 *		親モデル設定後も保持します。
		 *		false の場合は、当モデルでの位置と姿勢を親モデルからの
		 *		相対的な位置、姿勢として扱います。
		 *		そのため、設定後にグローバル座標系での位置や姿勢は変化することになります。
		 *		この引数を省略した場合は false と同様の挙動となります。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa deleteParent(), getParent(), entryChild()
		 */
		bool	setParent(fk_Model *model, bool setMode = false);

		//! 親モデル解除関数
		/*!
		 *	親モデルの設定を解除します。
		 *
		 *	\param[in]		setMode
		 *		true の場合、現在のグローバル座標系の位置と姿勢を、
		 *		親モデル解除後も保持します。
		 *		false の場合は、親モデルからの相対的な位置と姿勢を、
		 *		解除後のグローバル座標系に設定します。
		 *		この引数を省略した場合は false と同様の挙動となります。
		 *
		 *	\sa setParent(), getParent(), deleteChild()
		 */
		void	deleteParent(bool setMode = false);

		//! 親モデル参照関数
		/*!
		 *	親モデルを取得します。
		 *
		 *	\return		親モデルインスタンスのポインタ。
		 *		親モデルが設定されていない場合は nullptr を返します。
		 *
		 *	\sa setParent(), deleteParent()
		 */
		fk_Model *	getParent(void) const;

		//! 子モデル設定関数
		/*!
		 *	子モデルを設定します。
		 *	子モデルは複数持つことが可能なので、
		 *	既に子モデルが登録されている場合でも、その設定は破棄されません。
		 *
		 *	\param[in]		model		子モデルインスタンスのポインタ
		 *
		 *	\param[in]		setMode
		 *		true の場合、子モデルの現在のグローバル座標系の位置と姿勢を、
		 *		設定後も保持します。
		 *		false の場合は、子モデルでの位置と姿勢を当モデルからの
		 *		相対的な位置、姿勢として扱います。
		 *		そのため、設定後にグローバル座標系での位置や姿勢は変化することになります。
		 *		この引数を省略した場合は false と同様の挙動となります。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa setParent(), deleteChild(), deleteChildren(), foreachChild()
		 */
		bool	entryChild(fk_Model *model, bool setMode = false);

		//! 子モデル解除関数
		/*!
		 *	子モデルの設定を解除します。
		 *
		 *	\param[in]		model
		 *		子モデルインスタンスのポインタ。
		 *		もし model が子モデルの中に存在しない場合は、false を返します。
		 *
		 *	\param[in]		setMode
		 *		true の場合、子モデルのグローバル座標系の位置と姿勢を、
		 *		解除後も保持します。
		 *		false の場合は、親モデルからの相対的な位置と姿勢を、
		 *		解除後のグローバル座標系に設定します。
		 *		この引数を省略した場合は false と同様の挙動となります。
		 *
		 *	\return		解除に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa entryChild(), deleteChildren(), foreachChild()
		 */
		bool	deleteChild(fk_Model *model, bool setMode = false);

		//! 全子モデル解除関数
		/*!
		 *	当モデルの全ての子モデルの設定を解除します。
		 *
		 *	\param[in]		setMode
		 *		true の場合、子モデルのグローバル座標系の位置と姿勢を、
		 *		解除後も保持します。
		 *		false の場合は、親モデルからの相対的な位置と姿勢を、
		 *		解除後のグローバル座標系に設定します。
		 *		この引数を省略した場合は false と同様の挙動となります。
		 *
		 *	\sa entryChild(), deleteChild(), foreachChild()
		 */
		void	deleteChildren(bool setMode = false);

		//! 子モデル逐次参照関数
		/*!
		 *	当モデルに設定されている子モデルを順番に帰します。
		 *	まず、引数に nullptr を渡したとき、1番目の子モデルを返します。
		 *	子モデルが存在しない場合は、その時点で nullptr を返します。
		 *	次に、1番目に帰ってきたモデルを引数として渡したとき、
		 *	2番目の子モデルを返します。
		 *	このように、設定されている子モデルを順番に参照することができます。
		 *	最後の子モデルが引数として渡されたとき、nullptr を返します。
		 *
		 *	以下のコードは、「parent」の全ての子モデルに対し、
		 *	描画モードを FK_LINEMODE に設定する例です。
		 *
		 *		fk_Model	parentModel, *childModel;
		 *		
		 *		for(childModel = parentModel.foreachChild(nullptr);
		 *			childModel != nullptr;
		 *			childModel = parentModel.foreachChild(childModel)) {
		 *		
		 *			childModel->setDrawMode(FK_LINEMODE);
		 *		}
		 *
		 *	\param[in]		model		順番に渡す子モデルインスタンスのポインタ
		 *
		 *	\return		次にあたる子モデルインスタンスのポインタ。
		 *		引数に最後の子モデルが渡された場合、nullptr を返します。
		 *
		 *	\sa entryChild(), deleteChild(), deleteChildren()
		 */
		fk_Model *	foreachChild(fk_Model *model);

		//@}

		//! \name 状態保存制御関数
		//@{

		//! 位置・姿勢保存関数
		/*!
		 *	現時点でのモデルの位置と姿勢を保存します。
		 *	restore() 関数を用いることで復元します。
		 *
		 *	\sa restore(void), restore(double), setInterStopMode()
		 */
		void	snapShot(void);

		//! 位置・姿勢復元関数
		/*!
		 *	snapShot() 関数によって保存した位置・姿勢を復元します。
		 *
		 *	\return		復元に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa	restore(double), snapShot(), setInterStopMode()
		 */
		bool	restore(void);

		//! 位置・姿勢途中復元関数
		/*!
		 *	snapShot() 関数によって保存した位置・姿勢に対し、
		 *	現在の位置・姿勢と線形補間した状態にします。
		 *
		 *	\param[in]	t
		 *		線形補間パラメータ。
		 *		0 を snapShot() 関数による保存時、
		 *		1 を現時点とし、
		 *		与えられた実数によって線形補間した位置と姿勢に設定します。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa	snapShot(), restore(void), isCollision()
		 */
		bool	restore(double t);

		//@}

		//! \name 描画制御用関数
		//@{

		//! シェーダー設定関数
		/*!
		 *	この関数は、モデル描画の際のシェーダーを設定するものです。
		 *	fk_ShaderBinder::bindModel() による設定とまったく同じ挙動となります。
		 *
		 *	\param[in]	shader		シェーダープログラム
		 *
		 *	\note
		 *		シェーダーを未設定にし、デフォルトのシェーダーで描画したい場合は、
		 *		引数に nullptr を入力して下さい。
		 */
		void				setShader(fk_ShaderBinder *shader);

		//! シェーダー取得関数
		/*!
		 *	setShader() (または fk_ShaderBinder::bindModel())
		 *	によって設定されたシェーダーを返します。
		 *
		 *	\return		シェーダーを返します。
		 *				シェーダーが設定されていない場合は nullptr を返します。
		 */
		fk_ShaderBinder		*getShader(void);

#ifndef FK_DOXYGEN_USER_PROCESS
		//! 描画処理事前関数
		/*!
		 *	この関数は、
		 *	描画エンジン内部でモデルが実際に描画される前に自動的に呼び出されます。
		 *	デフォルトの状態では中身は空ですが、
		 *	関数オブジェクトまたはラムダ式で上書きすることにより、
		 *	描画処理前の時点の処理を記述することが可能です。
		 *	主な利用用途はシェーダプログラミングやデバッグ、
		 *	あるいは独自形状描画などが考えられます。
		 *
		 *	本関数を利用するには、FK の描画エンジン内部に精通している必要があります。
		 *	ソースコードを解析し、内部処理を理解した上で利用することを推奨します。
		 */
		//std::function<void(void)>	preShader;
		
		//! 描画処理事後関数
		/*!
		 *	この関数は、
		 *	描画エンジン内部でモデルが実際に描画された後に自動的に呼び出されます。
		 *	デフォルトの状態では中身は空ですが、
		 *	関数オブジェクトまたはラムダ式で上書きすることにより、
		 *	描画処理後の時点の処理を記述することが可能です。
		 *	主な利用用途はシェーダプログラミングやデバッグ、
		 *	あるいは独自形状描画などが考えられます。
		 *
		 *	本関数を利用するには、FK の描画エンジン内部に精通している必要があります。
		 *	ソースコードを解析し、内部処理を理解した上で利用することを推奨します。
		 */
		//std::function<void(void)>	postShader;
#endif
		//@}

		//! \name 境界ボリューム自動設定関数
		//@{

		//! 境界球自動設定関数
		/*!
		 *	この関数は、
		 *	境界ボリュームである境界球の半径を自動的に設定するものです。
		 *	具体的には、モデルの中心から形状の最遠点となる点と中心との距離を半径とします。
		 *	その結果、すべての形状上の点は境界球の内側に入ることになります。
		 *	境界球に関する詳細は fk_Boundary クラスを参照して下さい。
		 *
		 *	\note
		 *		setShape() で別形状を設定した場合や、設定した形状を
		 *		fk_IndexFaceSet::moveVPosition() などの関数によって変形した場合でも、
		 *		境界球半径は自動的に変化しません。
		 *		形状の全ての部分が境界球内部に入ることを保証するためには、
		 *		形状変化後に本関数を呼ぶ必要があります。
		 *
		 *	\sa adjustAABB(), adjustOBB(), adjustCapsule(), isInter(), isCollision(),
		 *		fk_Boundary::setBMode(),
		 *		fk_Boundary::setSphere(), fk_Boundary::getSphere()
		 */
		void	adjustSphere(void);

		//! AABB 自動設定関数
		/*!
		 *	この関数は、
		 *	境界ボリュームである AABB (軸平行境界ボックス) の大きさを自動的に設定するものです。
		 *	すべての頂点が AABB の内部と入る条件を満たす最小の大きさが設定されます。
		 *	AABB に関する詳細は fk_Boundary クラスを参照して下さい。
		 *
		 *	\note
		 *		setShape() で別形状を設定した場合や、設定した形状を
		 *		fk_IndexFaceSet::moveVPosition() などの関数によって変形した場合でも、
		 *		AABB の大きさは自動的に変化しません。
		 *		形状の全ての部分が AABB 内部に入ることを保証するためには、
		 *		形状変化後に本関数を呼ぶ必要があります。
		 *		また、AABB はその性質上、
		 *		モデルが回転した場合には形状が AABB の外側にはみ出る可能性がありますので、
		 *		モデルが回転した後も形状が AABB 内部にあることを保証するには、
		 *		回転した後に本関数を呼ぶ必要があります。
		 *
		 *	\sa adjustSphere(), adjustOBB(), adjustCapsule(), isInter(), isCollision(),
		 *		fk_Boundary::setBMode(),
		 *		fk_Boundary::setAABBSize(double, double, double),
		 *		fk_Boundary::setAABBSize(fk_Vector), fk_Boundary::getAABBSize()
		 */
		void	adjustAABB(void);

		//! OBB 自動設定関数
		/*!
		 *	この関数は、
		 *	境界ボリュームである OBB (有向境界ボックス) の大きさを自動的に設定するものです。
		 *	すべての頂点が OBB の内部と入る条件を満たす最小の大きさが設定されます。
		 *	OBB に関する詳細は fk_Boundary クラスを参照して下さい。
		 *
		 *	\note
		 *		setShape() で別形状を設定した場合や、設定した形状を
		 *		fk_IndexFaceSet::moveVPosition() などの関数によって変形した場合でも、
		 *		OBB の大きさは自動的に変化しません。
		 *		形状の全ての部分が OBB 内部に入ることを保証するためには、
		 *		形状変化後に本関数を呼ぶ必要があります。
		 *
		 *	\sa adjustSphere(), adjustAABB(), adjustCapsule(), isInter(), isCollision(),
		 *		fk_Boundary::setBMode(),
		 *		fk_Boundary::setOBBSize(double, double, double),
		 *		fk_Boundary::setOBBSize(fk_Vector), fk_Boundary::getOBBSize()
		 */
		void	adjustOBB(void);

		//! 境界カプセル自動設定関数
		/*!
		 *	この関数は、
		 *	境界ボリュームである境界カプセルの大きさを自動的に設定するものです。
		 *	すべての頂点が境界カプセルの内部と入る条件を満たす最小の大きさが設定されます。
		 *	境界カプセルに関する詳細は fk_Boundary クラスを参照して下さい。
		 *
		 * \note
		 *		setShape() で別形状を設定した場合や、設定した形状を
		 *		fk_IndexFaceSet::moveVPosition() などの関数によって変形した場合でも、
		 *		境界カプセルの大きさは自動的に変化しません。
		 *		形状の全ての部分が境界カプセル内部に入ることを保証するためには、
		 *		形状変化後に本関数を呼ぶ必要があります。
		 *
		 * \param[in]	S	中心軸始点位置ベクトル
		 * \param[in]	E	中心軸終点位置ベクトル
		 *
		 * \sa adjustSphere(), adjustAABB(), adjustOBB(), isInter(), isCollision(),
		 *		fk_Boundary::setBMode(),
		 *		fk_Boundary::setCapsule(), fk_Boundary::getCapsuleRadius(),
		 *		fk_Boundary::getCapsuleLength(), fk_Boundary::getCapsuleStartPos(),
		 *		fk_Boundary::getCapsuleEndPos()
		 */
		void	adjustCapsule(fk_Vector S, fk_Vector E);
		//@}

		//! \name 干渉判定・衝突判定関数
		//@{

		//! モデル間干渉判定関数
		/*!
		 *	この関数は、別モデルとの干渉判定を行います。
		 *	干渉判定に用いられる境界ボリュームの種類は、
		 *	fk_Boundary::setBMode() で設定されたものが用いられます。
		 *	相手モデル側で別の種類が設定されていた場合でも、
		 *	この関数を呼び出しているインスタンス側の設定が優先されます。
		 *	従って、相手モデル側の境界ボリュームも適切に設定しておく必要があります。
		 *
		 * \note
		 *		「干渉判定」と「衝突判定」の違いに関しては、
		 *		本クラスの概要を参照して下さい。
		 *
		 * \param[in]	model
		 *		干渉判定を行うモデル
		 *
		 * \return		干渉している場合 true を、していない場合 false を返します。
		 *
		 * \sa adjustSphere(), adjustAABB(), adjustOBB(), adjustCapsule(), isCollision(),
		 *		snapShot(), restore(void), setInterStopMode(), entryInterModel(),
		 *		fk_Boundary::setBMode(),
		 *		fk_Boundary::setCapsule(), fk_Boundary::getCapsuleRadius(),
		 *		fk_Boundary::getCapsuleLength(), fk_Boundary::getCapsuleStartPos(),
		 *		fk_Boundary::getCapsuleEndPos()
		 */
		bool	isInter(fk_Model *model);

		//! モデル間衝突判定関数
		/*!
		 *	この関数は、別モデルとの衝突判定を行います。
		 *	衝突判定を行うには、まずそれぞれのモデルにおいて
		 *	snapShot() 関数によって衝突判定を行う初期状態を設定しておく必要があります。
		 *	その状態から現在の位置まで、両モデルが等速度直線運動していると想定し、
		 *	その間に衝突が発生したかどうかを検出します。
		 *
		 *	なお、本関数を利用する際には事前に境界球の半径を適切に設定しておく必要があります。
		 *	現在この関数は境界球による判定のみが有効となります。
		 *	fk_Boundary::setBMode() によって境界ボリュームが別の種類に設定されていた場合でも、
		 *	境界球の情報のみが用いられます。
		 *
		 *	なお、衝突判定は snapShot() を呼ぶ以前や現時点以降を含めての検出となるので、
		 *	snapShot() を呼んだ時点から現時点までの間に衝突が起こったかどうかを判定するには、
		 * 	第二引数の衝突時間を考慮する必要があります。
		 *
		 * \note
		 *		「干渉判定」と「衝突判定」の違いに関しては、
		 *		本クラスの概要を参照して下さい。
		 *
		 * \param[in]	model
		 *		衝突判定を行うモデル
		 *
		 * \param[out]	time
		 *		snapShot() が呼ばれた時刻を 0、
		 *		現時点の時刻を 1 とした場合の、衝突時間を検出します。
		 *		本関数の返値が true であった場合でも、
		 *		この値が 0 から 1 の間にないときは、
		 *		衝突が起こっていないことになりますので、注意して下さい。
		 *
		 * \return
		 *		両モデルが等速度直線運動をすると想定した場合に、
		 *		いずれかの時刻で衝突が起きる場合 true を、衝突しない場合は false を返します。
		 *		ただし、第二引数の値が 0 から 1 の間にない場合は、
		 *		snapShot() を呼んだ時点から現時点までの間においては、
		 *		衝突が起こっていないことになります。
		 *
		 * \sa adjustSphere(), adjustAABB(), adjustOBB(), adjustCapsule(), isInter(),
		 *		snapShot(), restore(double),
		 *		fk_Boundary::setBMode(),
		 *		fk_Boundary::setCapsule(), fk_Boundary::getCapsuleRadius(),
		 *		fk_Boundary::getCapsuleLength(), fk_Boundary::getCapsuleStartPos(),
		 *		fk_Boundary::getCapsuleEndPos()
		 */
		bool	isCollision(fk_Model *model, double *time);

		//! 干渉継続モード設定関数
		/*!
		 *	干渉継続モードを有効にしておくと、
		 *	本モデルが isInter() 関数で他のモデルと干渉状態が検出された場合、
		 *	resetInter() が呼ばれるまでは true を返すようになります。
		 *
		 *	\param[in]	mode
		 *		true である場合、干渉継続モードが有効となります。
		 *		false の場合無効にします。
		 *
		 *	\sa isInter(), getInterMode(), getInterStatus(), resetInter(),
		 *		setInterStopMode(), entryInterModel()
		 */
		void	setInterMode(bool mode);

		//! 干渉継続モード取得関数
		/*!
		 *	現在の干渉継続モード状態を取得します。
		 *
		 *	\return
		 *		干渉継続モードが有効である場合 true を、無効である場合 false を返します。
		 *
		 *	\sa setInterMode()
		 */
		bool	getInterMode(void);

		//! 干渉継続状態取得関数
		/*!
		 *	本関数は、干渉継続モードが有効である場合で、
		 *	前に resetInter() が呼ばれた以降で、
		 *	isInter() によって干渉が検出されたことがあるかを検出します。
		 *
		 *	\return
		 *		干渉検出があった場合 true を、なかった場合 false を返します。
		 *
		 *	\sa	isInter(), setInterMode(), resetInterStatus()
		 */
		bool	getInterStatus(void);

		//! 干渉継続状態初期化関数
		/*!
		 *	干渉継続モードによる干渉検出状態を初期化します。
		 *	この関数が呼ばれた以降、再び isInter() による干渉が検出されるまでは、
		 *	getInterStatus() 関数は false を返します。
		 *	
		 * \sa isInter(), setInterMode(), getInterStatus()
		 */
		void	resetInter(void);
		//@}

		//! \name 干渉自動停止制御関数
		//@{
		//! 干渉自動停止モード設定関数
		/*!
		 *	この関数は、干渉自動停止モードの有無効を設定します。
		 *	「干渉自動停止モード」とは、以下のような処理を行う機能のことです。
		 *		-# 干渉チェック対象となるモデルを事前に登録しておく。
		 *		-# モデル移動の前に snapShot() をしておく。
		 *		-# モデルの移動を行った際に、
		 *			もし干渉チェック対象モデルのいずれかと干渉していた場合は、
		 *			restore() を実行し移動前の状態に戻る。
		 *
		 *	この機能を用いることで、移動後で干渉が起きてしまう移動が無効となります。
		 *	壁などにモデルが入らないように処理するような場面で有効となります。
		 *
		 *	このモードの対象となる移動関数は以下のとおりです。
		 *		- glRotate()
		 *		- loRotate()
		 *		- glRotateWithVec()
		 *		- loRotateWithVec()
		 *		- glTranslate()
		 *		- loTranslate()
		 *		- glMoveTo()
		 *
		 *	これらの関数は、モデルの位置ベクトルが変化する可能性があるからです。
		 *	その他の姿勢制御関数については停止の対象とはなりません。
		 *
		 *	なお、このモードを利用する場合、 restore() した後にも干渉状態となっている場合、
		 *	適用モデルがまったく動かなくなるという問題が生じます。
		 *	そのため本機能を用いたい場合は、
		 *	干渉チェック対象となるモデルは全て静止した状態であることを推奨します。
		 *	また、位置のかわらない姿勢制御関数は干渉状態であっても動作しますが、
		 *	その際に物体の回転によって非干渉状態から干渉状態となることがありえますので、
		 *	これも注意が必要です。
		 *
		 *	\note
		 *		干渉判定を行う際の境界ボリュームに関する設定は、
		 *		事前に行っておく必要があります。
		 *
		 *	\note
		 *		このモードを利用する場合、副作用として自前で管理していた
		 *		snapShot() の情報が破棄されてしまうという問題がありますので、
		 *		snapShot() や restore() を利用する場合はこのモードは用いないようにして下さい。
		 *
		 *	\param[in]	mode		true の場合有効とし、 false の場合無効とします。
		 *
		 *	\sa getInterStopMode(), entryInterModel(), deleteInterModel(), clearInterModel(),
		 *		isInter(), snapShot(), restore()
		 */
		void	setInterStopMode(bool mode);

		//! 干渉自動停止モード取得関数
		/*!
		 *	干渉自動停止モードの有無効を取得します。
		 *
		 *	\return		有効である場合 true を、無効である場合 false を返します。
		 *
		 *	\sa setInterStopMode()
		 */
		bool	getInterStopMode(void);

		//! 干渉自動停止モデル登録関数
		/*!
		 *	干渉自動停止モードの対象となるモデルを登録します。
		 *
		 *	\note
		 *		本関数で登録したモデルのインスタンスを、
		 *		deleteInterModel() や clearInterModel() で解除する前に消去した場合、
		 *		動作は保証されません。
		 *
		 *	\param[in]	model		登録モデルインスタンス
		 *
		 *	\sa setInterStopMode(), deleteInterModel(), clearInterModel()
		 */
		void	entryInterModel(fk_Model *model);

		//! 干渉自動停止モデル解除関数
		/*!
		 *	干渉自動停止モードの対象となっていたモデルの解除を行います。
		 *	もし入力モデルが登録されていなかった場合は、なにも起こりません。
		 *
		 *	\param[in]	model		解除モデルインスタンス
		 *
		 *	\sa	setInterStopMode(), entryInterModel(), clearInterModel()
		 */
		void	deleteInterModel(fk_Model *model);

		//! 干渉自動停止モデル初期化関数
		/*!
		 *	干渉自動停止モード用に登録されていた全てのモデルを解除します。
		 *
		 *	\sa	setInterStopMode(), entryInterModel(), deleteInterModel()
		 */
		void	clearInterModel(void);

		//@}


#ifndef FK_DOXYGEN_USER_PROCESS
		// カスタムテクスチャ描画用エントリポイント
		virtual void	connectShader(unsigned int) {};

		void	SetTreeDelMode(bool);
		void	TreePrint(void);

		void	setSize(double);
		double	getSize(void) const;
		void	setWidth(double);
		double	getWidth(void) const;

#endif

	private:
		fk_Material			material;
		fk_Color			pointColor;
		fk_Color			lineColor;
		fk_Shape			*shape;
		fk_Model			*parentModel;
		fk_TreeData			*treeData;
		fk_DrawMode			drawMode;
		fk_ElementMode		elemMode;
		fk_BlendMode		blendMode;
		fk_BlendFactor		srcFactor;
		fk_BlendFactor		dstFactor;
		fk_DepthMode		depthMode;
		double				pointSize;
		bool				smoothFlag;
		bool				reverseFlag;
		bool				treeFlag;
		unsigned int		_modelID;
		bool				treeDelMode;
		fk_TexMode			texMode;

		fk_HVector			*snapPos;
		fk_HVector			*snapInhPos;
		fk_Angle			*snapAngle;
		bool				snapFlag;

		bool				interMode;
		bool				interStatus;
		bool				interStopMode;

		std::list<fk_Model *>	interList;

		fk_ShaderBinder		*shader;

		void				EntryTree(void);
		void				DeleteTree(void);
		fk_TreeData *		GetTreeData(fk_Model *);

		bool				IsBSInter(fk_Model *);
		bool				IsAABBInter(fk_Model *);
		bool				IsOBBInter(fk_Model *);
		bool				IsCapsuleInter(fk_Model *);

		void				PreMove(void);
		void				PostMove(void);

		static fk_Tree		_modelTree;
	};
}

#endif // !__FK_MODEL_HEADER__

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
