// Model_CLI.h

#pragma once

#include <FK/Model.h>
#include "Boundary_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	using namespace System::Collections::Generic;

	// モデルの描画モードを表す列挙型												
	public enum class fk_DrawMode : unsigned int {
		NONEMODE			= 0x0000,					//!< 表示要素なし
		POINTMODE			= 0x0001,					//!< 頂点描画
		LINEMODE			= 0x0002,					//!< 稜線描画
		POLYMODE			= 0x0004,					//!< 面(表側)描画
		BACK_POLYMODE		= (0x0008 | FK_POLYMODE),	//!< 面(裏側)描画
		FRONTBACK_POLYMODE	= (0x0010 | FK_POLYMODE),	//!< 面(両面)描画
		TEXTUREMODE			= 0x0020					//!< テクスチャ描画
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
	 *		- Shape プロパティにて形状を設定した後に自動的に境界ボリュームのサイズを設定する機能。
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
	public ref class fk_Model : fk_Boundary {
	internal:

		static List<fk_Model^>^ modelList = gcnew List<fk_Model^>();
		fk_Shape^ shape;
		
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Model::fk_Model(bool argNewFlg);
#endif

	public:

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Model::fk_Model(::fk_Model *argUnmanagedPtr);
		::fk_Model * GetP(void);
#endif
		
	public:
		//! コンストラクタ
		fk_Model::fk_Model();

		//! デストラクタ
		fk_Model::~fk_Model();

		//! ファイナライザ
		fk_Model::!fk_Model();

		//! \name 基本情報プロパティ
		//@{

		//! ID プロパティ
		/*!
		 *	モデルの固有IDを参照します。
		 *	IDの最小値は 1 で、
		 *	同一プロセス中では同じ ID が別のモデルに割り振られることはありません。
		 */
		property unsigned int ID {
			unsigned int get();
		}

		//! 形状プロパティ
		/*!
		 *	モデル形状の参照・設定を行います。
		 *	形状は、 fk_Shape クラスの派生クラスであれば設定可能です。
		 *	なお、呼ぶ前に形状が設定されていた場合、前の設定は破棄されます。
		 *	初期状態は null となっており、
		 *	このプロパティが null の場合は「形状を持たないモデル」として扱われます。
		 */
		property fk_Shape^ Shape {
			fk_Shape^ get();
			void set(fk_Shape^);
		}

		//! ピックモードプロパティ
		/*!
		 *	モデルのピックモードの参照・設定を行います。
		 *	true の場合有効、false の場合無効となります。
		 *	ピックモードとは、
		 *	モデルをピックによる取得操作の対象とするかどうかを制御するものです。
		 *	ピックモードが有効である場合、モデルはピック取得の候補となります。
		 *	デフォルトでは無効となっています。
		 *
		 *	\sa fk_AppWindow::IsModelPicked()
		 */
		property bool PickMode {
			void set(bool);
			bool get(void);
		}

		//! 親モデルプロパティ
		/*!
		 *	親モデルの参照・設定を行います。
		 *	親モデルは 1 個しか設定できません。
		 *	設定の際に既に親モデルが設定されていた場合は、前のモデル設定は破棄されます。
		 *	親モデルが設定されていない場合は null となります。
		 *
		 *	なお、このプロパティの設定は、 SetParent(fk_Model^, bool) において、
		 *	第2引数に false を入力した場合と同義となります。
		 *
		 *	\sa SetParent(fk_Model^, bool), DeleteParent(), EntryChild()
		 */
		property fk_Model^ Parent {
			void set(fk_Model^);
			fk_Model^ get();
		}

		//@}

		//! \name 色・マテリアル関連プロパティ
		//@{
		
		//! マテリアルプロパティ
		/*!
		 *	モデルの基本マテリアルの参照・設定を行います。
		 *	マテリアルに関しての詳細は、
		 *	fk_Material の説明およびユーザーズマニュアルを参照して下さい。
		 *
		 *	\note
		 *		稜線の色は fk_Model::LineColor プロパティ、
		 *		頂点の色は fk_Model::PointColor プロパティを利用して設定して下さい。
		 *		個別位相要素のマテリアルとの制御については、
		 *		MaterialMode プロパティの説明を参照して下さい。
		 *		テクスチャを描画する際には、テクスチャモードによって混合の仕方が異なりますので、
		 *		fk_Texture::TextureMode の説明を参照して下さい。
		 *
		 *	\sa fk_Material, InhMaterial, LineColor, PointColor, fk_Texture::TextureMode
		 */
		property fk_Material^ Material {
			void set(fk_Material^);
			fk_Material^ get();
		}

		//! 継承マテリアルプロパティ
		/*!
		 *	親子関係を踏まえた基本マテリアルを参照します。
		 *	当モデルにマテリアルが設定されている場合、そのマテリアルを参照します。
		 *	当モデルにマテリアルが設定されていない場合は、親モデルのマテリアルを参照します。
		 *
		 *	\sa fk_Material, Material
		 */
		property fk_Material^ InhMaterial {
			fk_Material^ get();
		}

		//! 頂点色プロパティ
		/*!
		 *	現在モデルに設定されている頂点色の参照・設定を行います。
		 *	モデルに頂点色が設定されていない場合は null となります。
		 *
		 *	\sa fk_Color, PointColor, InhPointColor
		 */
		property fk_Color^ PointColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		//! 継承頂点色プロパティ
		/*!
		 *	親子関係を踏まえた頂点色を参照します。
		 *	当モデルに頂点色が設定されている場合、その頂点色を参照します。
		 *	当モデルに頂点色が設定されていない場合は、親モデルの頂点色を参照します。
		 *
		 *	\sa fk_Color, PointColor
		 */
		property fk_Color^ InhPointColor {
			fk_Color^ get();
		}

		//! 稜線色プロパティ
		/*!
		 *	現在モデルに設定されている稜線色の参照・設定を行います。
		 *	モデルに稜線色が設定されていない場合は null となります。
		 *
		 *	\sa fk_Color, InhLineColor
		 */
		property fk_Color^ LineColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		//! 継承稜線色プロパティ
		/*!
		 *	親子関係を踏まえた稜線色を参照します。
		 *	当モデルに稜線色が設定されている場合、その稜線色を参照します。
		 *	当モデルに稜線色が設定されていない場合は、親モデルの稜線色を参照します。
		 *
		 *	\sa fk_Color, LineColor
		 */
		property fk_Color^ InhLineColor {
			fk_Color^ get();
		}

		//! 頂点描画サイズプロパティ
		/*!
		 *	頂点描画サイズの参照・設定を行います。
		 *	単位はピクセルです。整数以外も設定可能です。
		 *
		 *	\sa	LineWidth
		 */
		property double PointSize {
			void set(double);
			double get();
		}
		
		//! 稜線描画幅プロパティ
		/*!
		 *	稜線描画幅の参照・設定を行います。
		 *	単位はピクセルです。整数以外も設定可能です。
		 *
		 *	\sa PointSize
		 */
		property double LineWidth {
			void set(double);
			double get();
		}


		//@}

		//! \name 描画制御関連プロパティ
		//@{

		//! 描画モードプロパティ
		/*!
		 *	モデルの描画モードを設定します。
		 *	描画モードとは、
		 *	面、稜線、頂点のそれぞれを描画するかどうかを制御するものです。
		 *	描画モードには以下のようなものがあります。
		 *	- fk_DrawMode.NONEMODE:				何も描画しません。
		 *	- fk_DrawMode.POINTMODE:			頂点を描画します。
		 *	- fk_DrawMode.LINEMODE:				稜線を描画します。
		 *	- fk_DrawMode.POLYMODE:				面の表を描画します。
		 *	- fk_DrawMode.BACK_POLYMODE:		面の裏を描画します。
		 *	- fk_DrawMode.FRONTBACK_POLYMODE:	面の表と裏を描画します。
		 *	- fk_DrawMode.TEXTUREMODE:			テクスチャを描画します。
		 *	.
		 *	これらの描画モードは、
		 *	ビット論理和を用いて複数のものを同時に指定することが可能です。
		 *	以下のコードは、頂点、稜線、面の表をすべて描画するように設定します。
		 *
		 *		fk_Model		model;
		 *		
		 *		model.DrawMode = fk_DrawMode.POINTMODE | fk_DrawMode.LINEMODE | fk_DrawMode.POLYMODE;
		 */
		property fk_DrawMode DrawMode {
			void set(fk_DrawMode);
			fk_DrawMode get();
		}

		//! マテリアルモードプロパティ
		/*!
		 *	形状中の各要素を描画する際に、
		 *	どの要素のマテリアルを採用するかというモードの参照・設定を行います。
		 *	与えられる値は以下の3種類です。
		 *		\arg fk_MaterialMode.CHILD
		 *		\arg fk_MaterialMode.PARENT
		 *		\arg fk_MaterialMode.NONE
		 *
		 *	マテリアルの採用は、以下のような優先順で決定します。
		 *	-# fk_Model のマテリアルモードが fk_MaterialMode.CHILD の場合、
		 *		モデルのマテリアルが採用されます。
		 *		fk_MaterialMode.NONE の場合は描画されません。
		 *		fk_MaterialMode.PARENT の場合は以下の条件に従います。
		 *	-# fk_Shape の派生クラスにてマテリアルモードが
		 *		fk_MaterialMode.CHILD になっている場合、形状のマテリアルが採用されます。
		 *		fk_MaterialMode.NONE の場合は描画されません。
		 *		fk_MaterialMode.PARENT の場合は以下の条件に従います。
		 *		(fk_Shape::MaterialMode を参照して下さい。)
		 *	-# 各位相要素でのマテリアルモードが、
		 *		fk_MaterialMode.CHILD になっている場合は個別のマテリアルが採用されます。
		 *		fk_MaterialMode.NONE の場合は描画されません。
		 *		fk_MaterialMode.PARENT の場合はモデルのマテリアルが採用されます。
		 *		(fk_TopologyMaterial::MaterialMode を参照して下さい。)
		 *
		 *
		 *	\sa fk_Shape::MaterialMode, fk_TopologyMaterial::MaterialMode
		 */
		property fk_MaterialMode MaterialMode {
			void set(fk_MaterialMode);
			fk_MaterialMode get();
		}

		//! スムースモードプロパティ
		/*!
		 *	モデルのスムースモードの参照・設定を行います。
		 *	true の場合有効、false の場合無効となります。
		 *	スムースモードを有効にすると、
		 *	形状の隣り合う面同士の法線ベクトルが補間され、
		 *	擬似的に滑らかな曲面として表示を行うようになります。
		 */
		property bool SmoothMode {
			void set(bool);
			bool get(void);
		}
			
		//! 描画順序制御プロパティ
		/*!
		 *	このプロパティでは、モデルの持つ位相要素の描画順序を制御します。
		 *	true の場合、モデル内の描画が通常と逆順になります。
		 *	false の場合、順序を通常の状態に戻します。
		 *	モデルの各位相要素が同一平面上にあり、描画順序を逆にしたい場合に用います。
		 */
		property bool ReverseDrawMode {
			void set(bool);
			bool get(void);
		}

		//@}

		//! \name 位置・姿勢・行列関連プロパティ

		//! 継承位置ベクトルプロパティ
		/*!
		 *	モデルの位置ベクトルを参照します。
		 *	本関数は、親モデルの有無にかかわらず、グローバル座標系での実際の位置ベクトルを返します。
		 *
		 *	\sa InhVec, InhUpvec, InhAngle, fk_MatrixAdmin::Position
		 */
		property fk_Vector^ InhPosition {
			fk_Vector^ get();
		}

		//! 継承方向ベクトルプロパティ
		/*!
		 *	モデルの方向ベクトルを取得します。
		 *	本関数は、親モデルの有無にかかわらず、グローバル座標系での実際の方向ベクトルを返します。
		 *
		 *	\sa InhPosition, InhUpvec, InhAngle, fk_MatrixAdmin::Vec
		 */
		property fk_Vector^ InhVec {
			fk_Vector^ get();
		}

		//! 継承アップベクトルプロパティ
		/*!
		 *	モデルのアップベクトルを取得します。
		 *	本関数は、親モデルの有無にかかわらず、グローバル座標系での実際のアップベクトルを返します。
		 *
		 *	\sa InhPosition, InhVec, InhAngle, fk_MatrixAdmin::Upvec
		 */
		property fk_Vector^ InhUpvec {
			fk_Vector^ get();
		}

		//! 継承オイラー角参照関数
		/*!
		 *	モデルのオイラー角を取得します。
		 *	本関数は、親モデルの有無にかかわらず、グローバル座標系での実際のオイラー角を返します。
		 *	オイラー角の詳細については、 fk_Angle の説明を参照して下さい。
		 *
		 *	\return		
		 *
		 *	\sa InhPosition, InhVec, InhUpvec, fk_MatrixAdmin::Angle, fk_Angle
		 */
		property fk_Angle^ InhAngle {
			fk_Angle^ get();
		}

		//! 継承全体倍率プロパティ
		/*!
		 *	モデルの全体拡大・縮小倍率を参照します。
		 *	親子関係の小モデルの場合、親モデルでの倍率も反映されます。
		 *
		 *	\sa InhPosition, InhVec, InhUpvec, InhAngle, fk_MatrixAdmin::Scale
		 */
		property double InhScale {
			double get();
		}

		//! 継承変換行列プロパティ
		/*!
		 *	モデルの位置と姿勢を表す変換行列を参照します。
		 *	当モデルに親モデルがあった場合、
		 *	その親モデルの変換行列と当モデルの変換行列の積となります。
		 *	結果として、この関数を用いることでグローバル座標系における
		 *	当モデルの変換行列を得ることができます。
		 *	親モデルが設定されていない場合は、
		 *	fk_MatrixAdmin::Matrix と結果が同じとなります。
		 *
		 *	\sa fk_MatrixAdmin::Matrix(), InhInvMatrix
		 */
		property fk_Matrix^ InhMatrix {
			fk_Matrix^ get();
		}

		//! 継承逆変換行列プロパティ
		/*!
		 *	モデルの位置と姿勢を表す変換行列の、逆行列を参照します。
		 *	これは、 fk_Model::InhMatrix プロパティで得られる行列の逆行列となります。
		 *	当モデルに親モデルがあった場合、
		 *	その親モデルの逆変換行列と当モデルの逆変換行列の積が返されます。
		 *	結果として、この関数を用いることでグローバル座標系における
		 *	当モデルの逆変換行列を得ることができます。
		 *	親モデルが設定されていない場合は、
		 *	fk_MatrixAdmin::InvMatrix と結果が同じとなります。
		 *
		 *	\sa fk_MatrixAdmin::InvMatrix, InhMatrix
		 */
		property fk_Matrix^ InhInvMatrix {
			fk_Matrix^ get();
		}

		//! 継承移動・回転要素変換行列プロパティ
		/*!
		 *	モデルの持つ変換要素のうち、
		 *	位置と姿勢のみを反映した、
		 *	すなわち拡大縮小の要素を省いた変換行列を参照します。
		 *	当モデルに親モデルがあった場合、
		 *	その親モデルの変換行列と当モデルの変換行列の積となります。
		 *	その結果として、この関数を用いることでグローバル座標系における
		 *	当モデルの変換行列を得ることができます。
		 *	親モデルが設定されていない場合は、
		 *	fk_MatrixAdmin::BaseMatrix と結果が同じとなります。
		 *
		 *	\sa fk_MatrixAdmin::BaseMatrix, InhMatrix, InhInvBaseMatrix
		 */
		property fk_Matrix^ InhBaseMatrix {
			fk_Matrix^ get();
		}

		//! 継承移動・回転要素逆変換行列プロパティ
		/*!
		 *	モデルの持つ変換要素のうち、
		 *	位置と姿勢のみを反映した、
		 *	すなわち拡大縮小の要素を省いた変換行列の逆行列を参照します。
		 *	当モデルに親モデルがあった場合、
		 *	その親モデルの逆変換行列と当モデルの逆変換行列の積となります。
		 *	その結果として、この関数を用いることでグローバル座標系における
		 *	当モデルの逆変換行列を得ることができます。
		 *	親モデルが設定されていない場合は、
		 *	fk_MatrixAdmin::InvBaseMatrix と結果が同じとなります。
		 *
		 *	\sa fk_MatrixAdmin::InvBaseMatrix, InhInvMatrix, InhBaseMatrix
		 */
		property fk_Matrix^ InhInvBaseMatrix {
			fk_Matrix^ get();
		}

		//@}

		//! \name 干渉・衝突判定関連プロパティ
		//@{

		//! 干渉継続モード設定関数
		/*!
		 *	干渉継続モードの参照・設定を行います。
		 *	true で有効、false で無効となります。
		 *	干渉継続モードを有効にしておくと、
		 *	本モデルが IsInter() 関数で他のモデルと干渉状態が検出された場合、
		 *	ResetInter() が呼ばれるまでは true を返すようになります。
		 *
		 *	\sa IsInter(), InterStatus, ResetInter(), InterStopMode, EntryInterModel()
		 */
		property bool InterMode {
			void set(bool);
			bool get();
		}
		
		//! 干渉継続状態プロパティ
		/*!
		 *	本プロパティは、干渉継続モードが有効である場合で、
		 *	前に ResetInter() が呼ばれた以降で、
		 *	IsInter() によって干渉が検出されたことがあるかを検出することができます。
		 *	干渉検出があった場合 true、なかった場合 false となっています。
		 *
		 *	\sa	IsInter(), InterMode, ResetInterStatus()
		 */
		property bool InterStatus {
			bool get();
		}

		//! 干渉自動停止モードプロパティ
		/*!
		 *	干渉自動停止モードの参照・設定を行います。
		 *	true で有効、false で無効となります。
		 *
		 *	「干渉自動停止モード」とは、以下のような処理を行う機能のことです。
		 *		-# 干渉チェック対象となるモデルを事前に登録しておく。
		 *		-# モデル移動の前に SnapShot() をしておく。
		 *		-# モデルの移動を行った際に、
		 *			もし干渉チェック対象モデルのいずれかと干渉していた場合は、
		 *			Restore() を実行し移動前の状態に戻る。
		 *
		 *	この機能を用いることで、移動後で干渉が起きてしまう移動が無効となります。
		 *	壁などにモデルが入らないように処理するような場面で有効となります。
		 *
		 *	このモードの対象となる移動関数は以下のとおりです。
		 *		- GlRotate()
		 *		- LoRotate()
		 *		- GlRotateWithVec()
		 *		- LoRotateWithVec()
		 *		- GlTranslate()
		 *		- LoTranslate()
		 *		- GlMoveTo()
		 *
		 *	これらの関数は、モデルの位置ベクトルが変化する可能性があるからです。
		 *	その他の姿勢制御関数については停止の対象とはなりません。
		 *
		 *	なお、このモードを利用する場合、 Restore() した後にも干渉状態となっている場合、
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
		 *		SnapShot() の情報が破棄されてしまうという問題がありますので、
		 *		SnapShot() や Restore() を利用する場合はこのモードは用いないようにして下さい。
		 *
		 *	\sa InterStopMode, EntryInterModel(), DeleteInterModel(), ClearInterModel(),
		 *		IsInter(), SnapShot(), Restore()
		 */
		property bool InterStopMode {
			void set(bool);
			bool get();
		}

		//@}

#ifndef FK_DOXYGEN_USER_PROCESS
		delegate void CallPreShader();
		delegate void CallPostShader();

		virtual void PreShader() {};
		virtual void PostShader() {};

		bool Equals(fk_Model^ argModel);
#endif

		//////////////////////////////////////////////////////////////
		//! \name マテリアル属性除去関数
		//@{

		//! 基本マテリアル削除関数
		/*!
		 *	基本マテリアル設定を削除します。
		 *	これにより、親モデルが存在する場合は親モデルの基本マテリアルを継承します。
		 *	親モデルが存在しない場合は、システムのデフォルトマテリアルが採用されます。
		 *
		 *	\sa Material, InhMaterial
		 */
		void DeleteMaterial(void);

		//! 頂点色削除関数
		/*!
		 *	頂点色設定を削除します。
		 *	これにより、親モデルが存在する場合は親モデルの頂点色を継承します。
		 *	親モデルが存在しない場合は、システムのデフォルト頂点色が採用されます。
		 *
		 *	\sa PointColor, InhPointColor
		 */
		void DeletePointColor(void);

		//! 稜線色削除関数
		/*!
		 *	稜線色設定を削除します。
		 *	これにより、親モデルが存在する場合は親モデルの稜線色を継承します。
		 *	親モデルが存在しない場合は、システムのデフォルト稜線色が採用されます。
		 *
		 *	\sa LineColor, InhLineColor
		 */
		void DeleteLineColor(void);

		//! \name 親子関係制御関数
		//@{

		//! 親モデル設定関数1
		/*!
		 *	親モデルを設定します。
		 *	親モデルは 1 個しか設定できません。
		 *	前に設定されていた場合は、前のモデル設定は破棄されます。
		 *
		 *	\param[in]		model		親モデルインスタンスのポインタ
		 *
		 *	\param[in]		mode
		 *		true の場合、現在のグローバル座標系の位置と姿勢を、
		 *		親モデル設定後も保持します。
		 *		false の場合は、当モデルでの位置と姿勢を親モデルからの
		 *		相対的な位置、姿勢として扱います。
		 *		そのため、設定後にグローバル座標系での位置や姿勢は変化することになります。
		 *		この引数を省略した場合は false と同様の挙動となります。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa Parent, DeleteParent(), EntryChild()
		 */
		bool SetParent(fk_Model^ model, bool mode);

		//! 親モデル設定関数2
		/*!
		 *	親モデルを設定します。
		 *	親モデルは 1 個しか設定できません。
		 *	前に設定されていた場合は、前のモデル設定は破棄されます。
		 *
		 *	なお本関数は、 SetParent(fk_Model^, bool) において、
		 *	第2引数に false を入力した場合と同義となります。
		 *	また、 Parent プロパティに model を代入することとも同義です。
		 *
		 *	\param[in]		model		親モデルインスタンスのポインタ
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa Parent, DeleteParent(), EntryChild()
		 */
		bool SetParent(fk_Model^ model);

		//! 親モデル解除関数1
		/*!
		 *	親モデルの設定を解除します。
		 *
		 *	\param[in]		mode
		 *		true の場合、現在のグローバル座標系の位置と姿勢を、
		 *		親モデル解除後も保持します。
		 *		false の場合は、親モデルからの相対的な位置と姿勢を、
		 *		解除後のグローバル座標系に設定します。
		 *
		 *	\sa SetParent(fk_Model^, bool), Parent, DeleteChild()
		 */
		void DeleteParent(bool mode);

		//! 親モデル解除関数2
		/*!
		 *	親モデルの設定を解除します。
		 *	本関数は、 DeleteParent(bool) において、
		 *	引数に false を入力した場合と同義となります。
		 *
		 *	\sa SetParent(fk_Model^, bool), DeleteParent(bool), Parent, DeleteChild()
		 */
		void DeleteParent(void);

		//! 子モデル設定関数1
		/*!
		 *	子モデルを設定します。
		 *	子モデルは複数持つことが可能なので、
		 *	既に子モデルが登録されている場合でも、その設定は破棄されません。
		 *
		 *	\param[in]		model		子モデルインスタンスのポインタ
		 *
		 *	\param[in]		mode
		 *		true の場合、子モデルの現在のグローバル座標系の位置と姿勢を、
		 *		設定後も保持します。
		 *		false の場合は、子モデルでの位置と姿勢を当モデルからの
		 *		相対的な位置、姿勢として扱います。
		 *		そのため、設定後にグローバル座標系での位置や姿勢は変化することになります。
		 *		この引数を省略した場合は false と同様の挙動となります。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa Parent, SetParent(), DeleteChild(), DeleteChildren()
		 */
		bool EntryChild(fk_Model^ model, bool mode);

		//! 子モデル設定関数2
		/*!
		 *	子モデルを設定します。
		 *	子モデルは複数持つことが可能なので、
		 *	既に子モデルが登録されている場合でも、その設定は破棄されません。
		 *
		 *	なお、本関数は EntryChild(fk_Model^, bool) において、
		 *	第2引数に false を入力した場合と同義となります。
		 *
		 *	\param[in]		model		子モデルインスタンスのポインタ
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa Parent, SetParent(), DeleteChild(), DeleteChildren()
		 */
		bool EntryChild(fk_Model^ model);
		
		//! 子モデル解除関数1
		/*!
		 *	子モデルの設定を解除します。
		 *
		 *	\param[in]		model
		 *		子モデルインスタンスのポインタ。
		 *		もし model が子モデルの中に存在しない場合は、false を返します。
		 *
		 *	\param[in]		mode
		 *		true の場合、子モデルのグローバル座標系の位置と姿勢を、
		 *		解除後も保持します。
		 *		false の場合は、親モデルからの相対的な位置と姿勢を、
		 *		解除後のグローバル座標系に設定します。
		 *		この引数を省略した場合は false と同様の挙動となります。
		 *
		 *	\return		解除に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa EntryChild(), DeleteChildren()
		 */
		bool DeleteChild(fk_Model^ model, bool mode);

		//! 子モデル解除関数2
		/*!
		 *	子モデルの設定を解除します。
		 *
		 *	なお、本関数は DeleteChild(fk_Model^, bool) において、
		 *	第2引数に false を入力した場合と同義となります。
		 *
		 *	\param[in]		model
		 *		子モデルインスタンスのポインタ。
		 *		もし model が子モデルの中に存在しない場合は、false を返します。
		 *
		 *	\return		解除に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa EntryChild(), DeleteChildren()
		 */
		bool DeleteChild(fk_Model^ model);

		//! 全子モデル解除関数1
		/*!
		 *	当モデルの全ての子モデルの設定を解除します。
		 *
		 *	\param[in]		mode
		 *		true の場合、子モデルのグローバル座標系の位置と姿勢を、
		 *		解除後も保持します。
		 *		false の場合は、親モデルからの相対的な位置と姿勢を、
		 *		解除後のグローバル座標系に設定します。
		 *		この引数を省略した場合は false と同様の挙動となります。
		 *
		 *	\sa EntryChild(), DeleteChild()
		 */
		void DeleteChildren(bool mode);

		//! 全子モデル解除関数2
		/*!
		 *	当モデルの全ての子モデルの設定を解除します。
		 *	本関数は、 DeleteChildren(bool) において、
		 *	引数に false を入力した場合と同義となります。
		 *
		 *	\sa EntryChild(), DeleteChild()
		 */
		void DeleteChildren(void);
		//@}

		//! \name 状態保存制御関数
		//@{

		//! 位置・姿勢保存関数
		/*!
		 *	現時点でのモデルの位置と姿勢を保存します。
		 *	Restore() 関数を用いることで復元します。
		 *
		 *	\sa Restore(void), Restore(double), InterStopMode
		 */
		void SnapShot(void);

		//! 位置・姿勢復元関数
		/*!
		 *	SnapShot() 関数によって保存した位置・姿勢を復元します。
		 *
		 *	\return		復元に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa	Restore(double), SnapShot(), InterStopMode
		 */
		bool Restore(void);

		//! 位置・姿勢途中復元関数
		/*!
		 *	SnapShot() 関数によって保存した位置・姿勢に対し、
		 *	現在の位置・姿勢と線形補間した状態にします。
		 *
		 *	\param[in]	t
		 *		線形補間パラメータ。
		 *		0 を SnapShot() 関数による保存時、
		 *		1 を現時点とし、
		 *		与えられた実数によって線形補間した位置と姿勢に設定します。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa	SnapShot(), Restore(void), IsCollision()
		 */
		bool Restore(double t);
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
		 *		fk_Model::Shape プロパティに別形状を設定した場合や、設定した形状を
		 *		fk_IndexFaceSet::MoveVPosition() などの関数によって変形した場合でも、
		 *		境界球半径は自動的に変化しません。
		 *		形状の全ての部分が境界球内部に入ることを保証するためには、
		 *		形状変化後に本関数を呼ぶ必要があります。
		 *
		 *	\sa AdjustAABB(), AdjustOBB(), AdjustCapsule(), IsInter(), IsCollision(),
		 *		fk_Boundary::BMode, fk_Boundary::SphereRadius
		 *
		 */
		void AdjustSphere(void);

		//! AABB 自動設定関数
		/*!
		 *	この関数は、
		 *	境界ボリュームである AABB (軸平行境界ボックス) の大きさを自動的に設定するものです。
		 *	すべての頂点が AABB の内部と入る条件を満たす最小の大きさが設定されます。
		 *	AABB に関する詳細は fk_Boundary クラスを参照して下さい。
		 *
		 *	\note
		 *		fk_Model::Shape プロパティに別形状を設定した場合や、設定した形状を
		 *		fk_IndexFaceSet::MoveVPosition() などの関数によって変形した場合でも、
		 *		AABB の大きさは自動的に変化しません。
		 *		形状の全ての部分が AABB 内部に入ることを保証するためには、
		 *		形状変化後に本関数を呼ぶ必要があります。
		 *		また、AABB はその性質上、
		 *		モデルが回転した場合には形状が AABB の外側にはみ出る可能性がありますので、
		 *		モデルが回転した後も形状が AABB 内部にあることを保証するには、
		 *		回転した後に本関数を呼ぶ必要があります。
		 *
		 *	\sa AdjustSphere(), AdjustOBB(), AdjustCapsule(), IsInter(), IsCollision(),
		 *		fk_Boundary::BMode, fk_Boundary:AABB
		 */
		void AdjustAABB(void);

		//! OBB 自動設定関数
		/*!
		 *	この関数は、
		 *	境界ボリュームである OBB (有向境界ボックス) の大きさを自動的に設定するものです。
		 *	すべての頂点が OBB の内部と入る条件を満たす最小の大きさが設定されます。
		 *	OBB に関する詳細は fk_Boundary クラスを参照して下さい。
		 *
		 *	\note
		 *		fk_Model::Shape プロパティに別形状を設定した場合や、設定した形状を
		 *		fk_IndexFaceSet::MoveVPosition() などの関数によって変形した場合でも、
		 *		OBB の大きさは自動的に変化しません。
		 *		形状の全ての部分が OBB 内部に入ることを保証するためには、
		 *		形状変化後に本関数を呼ぶ必要があります。
		 *
		 *	\sa AdjustSphere(), AdjustAABB(), AdjustCapsule(), IsInter(), IsCollision(),
		 *		fk_Boundary::BMode, fk_Boundary::OBB
		 */
		void AdjustOBB(void);

		//! 境界カプセル自動設定関数
		/*!
		 *	この関数は、
		 *	境界ボリュームである境界カプセルの大きさを自動的に設定するものです。
		 *	すべての頂点が境界カプセルの内部と入る条件を満たす最小の大きさが設定されます。
		 *	境界カプセルに関する詳細は fk_Boundary クラスを参照して下さい。
		 *
		 * \note
		 *		fk_Model::Shape プロパティに別形状を設定した場合や、設定した形状を
		 *		fk_IndexFaceSet::MoveVPosition() などの関数によって変形した場合でも、
		 *		境界カプセルの大きさは自動的に変化しません。
		 *		形状の全ての部分が境界カプセル内部に入ることを保証するためには、
		 *		形状変化後に本関数を呼ぶ必要があります。
		 *
		 * \param[in]	S	中心軸始点位置ベクトル
		 * \param[in]	E	中心軸終点位置ベクトル
		 *
		 * \sa AdjustSphere(), AdjustAABB(), AdjustOBB(), IsInter(), IsCollision(),
		 *		fk_Boundary::BMode,
		 *		fk_Boundary::SetCapsule(), fk_Boundary::GetCapsuleRadius(),
		 *		fk_Boundary::GetCapsuleLength(), fk_Boundary::GetCapsuleStartPos(),
		 *		fk_Boundary::GetCapsuleEndPos()
		 */
		void AdjustCapsule(fk_Vector^ S, fk_Vector^ E);
		//@}

		//! \name 干渉判定・衝突判定関数
		//@{

		//! モデル間干渉判定関数
		/*!
		 *	この関数は、別モデルとの干渉判定を行います。
		 *	干渉判定に用いられる境界ボリュームの種類は、
		 *	fk_Boundary::BMode に設定されているものが用いられます。
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
		 * \sa AdjustSphere(), AdjustAABB(), AdjustOBB(), AdjustCapsule(), IsCollision(),
		 *		SnapShot(), Restore(void), InterStopMode, EntryInterModel(),
		 *		fk_Boundary::BMode,
		 *		fk_Boundary::SetCapsule(), fk_Boundary::GetCapsuleRadius(),
		 *		fk_Boundary::GetCapsuleLength(), fk_Boundary::GetCapsuleStartPos(),
		 *		fk_Boundary::GetCapsuleEndPos()
		 */
		bool IsInter(fk_Model^ model);

		//! モデル間衝突判定関数
		/*!
		 *	この関数は、別モデルとの衝突判定を行います。
		 *	衝突判定を行うには、まずそれぞれのモデルにおいて
		 *	SnapShot() 関数によって衝突判定を行う初期状態を設定しておく必要があります。
		 *	その状態から現在の位置まで、両モデルが等速度直線運動していると想定し、
		 *	その間に衝突が発生したかどうかを検出します。
		 *
		 *	なお、本関数を利用する際には事前に境界球の半径を適切に設定しておく必要があります。
		 *	現在この関数は境界球による判定のみが有効となります。
		 *	fk_Boundary::BMode によって境界ボリュームが別の種類に設定されていた場合でも、
		 *	境界球の情報のみが用いられます。
		 *
		 *	なお、衝突判定は SnapShot() を呼ぶ以前や現時点以降を含めての検出となるので、
		 *	SnapShot() を呼んだ時点から現時点までの間に衝突が起こったかどうかを判定するには、
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
		 *		SnapShot() が呼ばれた時刻を 0、
		 *		現時点の時刻を 1 とした場合の、衝突時間を検出します。
		 *		本関数の返値が true であった場合でも、
		 *		この値が 0 から 1 の間にないときは、
		 *		衝突が起こっていないことになりますので、注意して下さい。
		 *
		 * \return
		 *		両モデルが等速度直線運動をすると想定した場合に、
		 *		いずれかの時刻で衝突が起きる場合 true を、衝突しない場合は false を返します。
		 *		ただし、第二引数の値が 0 から 1 の間にない場合は、
		 *		SnapShot() を呼んだ時点から現時点までの間においては衝突が起こっていないことになります。
		 *
		 * \sa AdjustSphere(), AdjustAABB(), AdjustOBB(), AdjustCapsule(), IsInter(),
		 *		SnapShot(), Restore(double),
		 *		fk_Boundary::BMode,
		 *		fk_Boundary::SetCapsule(), fk_Boundary::GetCapsuleRadius(),
		 *		fk_Boundary::GetCapsuleLength(), fk_Boundary::GetCapsuleStartPos(),
		 *		fk_Boundary::GetCapsuleEndPos()
		 */
		bool IsCollision(fk_Model^ model, double %time);

		//! 干渉継続状態初期化関数
		/*!
		 *	干渉継続モードによる干渉検出状態を初期化します。
		 *	干渉継続モードについては
		 *	fk_Model::InterMode プロパティの解説を参照して下さい。
		 *	この関数が呼ばれた以降、再び IsInter() による干渉が検出されるまでは、
		 *	InterStatus プロパティは false のままとなります。
		 *	
		 * \sa IsInter(), InterMode, InterStatus
		 */
		void ResetInter(void);
		//@}

		//! \name 干渉自動停止制御関数
		//@{

		//! 干渉自動停止モデル登録関数
		/*!
		 *	干渉自動停止モードの対象となるモデルを登録します。
		 *	干渉自動停止モードについては、
		 *	fk_Model::InterStopMode の解説を参照して下さい。
		 *
		 *	\note
		 *		本関数で登録したモデルのインスタンスを、
		 *		DeleteInterModel() や ClearInterModel() で解除する前に消去した場合、
		 *		動作は保証されません。
		 *
		 *	\param[in]	model		登録モデルインスタンス
		 *
		 *	\sa InterStopMode, DeleteInterModel(), ClearInterModel()
		 */
		void EntryInterModel(fk_Model^ model);

		//! 干渉自動停止モデル解除関数
		/*!
		 *	干渉自動停止モードの対象となっていたモデルの解除を行います。
		 *	干渉自動停止モードについては、
		 *	fk_Model::InterStopMode の解説を参照して下さい。
		 *	もし入力モデルが登録されていなかった場合は、なにも起こりません。
		 *
		 *	\param[in]	model		解除モデルインスタンス
		 *
		 *	\sa	InterStopMode, EntryInterModel(), ClearInterModel()
		 */
		void DeleteInterModel(fk_Model^ model);

		//! 干渉自動停止モデル初期化関数
		/*!
		 *	干渉自動停止モード用に登録されていた全てのモデルを解除します。
		 *
		 *	\sa	InterStopMode, EntryInterModel(), DeleteInterModel()
		 */
		void ClearInterModel(void);
		//@}

		//////////////////////////////////////////////////////////////
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
		 *	姿勢の回転も伴いたい場合は GlRotateWithVec() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は LoRotate() を利用して下さい。
		 *
		 *	\param[in]		origin
		 *		グローバル座標系での回転軸上の点
		 *
		 *	\param[in]		axis
		 *		回転軸に平行な軸。 fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 *
		 *	\param[in]		theta
		 *		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa GlRotateWithVec(fk_Vector^, fk_Axis, double),
		 *		LoRotate(fk_Vector^, fk_Axis, double)
		 */
		bool GlRotate(fk_Vector^ origin, fk_Axis axis, double theta);

		//! グローバル座標系座標軸回転関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(x, y, z) を通り、
		 *	axis で指定した座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は GlRotateWithVec() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は LoRotate() を利用して下さい。
		 *
		 *	\param[in]		x		グローバル座標系での回転軸上の点のx成分
		 *	\param[in]		y		グローバル座標系での回転軸上の点のy成分
		 *	\param[in]		z		グローバル座標系での回転軸上の点のz成分
		 *
		 *	\param[in]		axis
		 *		回転軸に平行な軸。 fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa GlRotateWithVec(double, double, double, fk_Axis, double),
		 *		LoRotate(double, double, double, fk_Axis, double)
		 */
		bool GlRotate(double x, double y, double z, fk_Axis axis, double theta);

		//! グローバル座標系任意軸回転関数1
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は GlRotateWithVec() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は LoRotate() を利用して下さい。
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
		 *	\sa GlRotateWithVec(fk_Vector^, fk_Vector^, double),
		 *		LoRotate(fk_Vector^, fk_Vector^, double)
		 */
		bool GlRotate(fk_Vector^ A, fk_Vector^ B, double theta);

		//! グローバル座標系任意軸回転関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は GlRotateWithVec() を利用して下さい。
		 *	ローカル座標系で回転移動を行いたい場合は LoRotate() を利用して下さい。
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
		 *	\sa GlRotateWithVec(double, double, double, double, double, double, double),
		 *		LoRotate(double, double, double, double, double, double, double)
		 */
		bool GlRotate(double Ax, double Ay, double Az,
					  double Bx, double By, double Bz, double theta);

		//! ローカル座標系座標軸回転関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) origin を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は LoRotateWithVec() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は GlRotate() を利用して下さい。
		 *
		 *	\param[in]		origin
		 *		ローカル座標系での回転軸上の点
		 *
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 *
		 *	\param[in]		theta
		 *		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa GlRotate(fk_Vector^, fk_Axis, double),
		 *		LoRotateWithVec(fk_Vector^, fk_Axis, double)
		 */
		bool LoRotate(fk_Vector^ origin, fk_Axis axis, double theta);

		//! ローカル座標系座標軸回転関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) (x, y, z) を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は LoRotateWithVec() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は GlRotate() を利用して下さい。
		 *
		 *	\param[in]		x		ローカル座標系での回転軸上の点のx成分
		 *	\param[in]		y		ローカル座標系での回転軸上の点のy成分
		 *	\param[in]		z		ローカル座標系での回転軸上の点のz成分
		 *
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa GlRotate(double, double, double, fk_Axis, double),
		 *		LoRotateWithVec(double, double, double, fk_Axis, double)
		 */
		bool LoRotate(double x, double y, double z, fk_Axis axis, double theta);

		//! ローカル座標系任意軸回転関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における) A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は LoRotateWithVec() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は GlRotate() を利用して下さい。
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
		 *	\sa GlRotateWithVec(fk_Vector^, fk_Vector^, double),
		 *		LoRotate(fk_Vector^, fk_Vector^, double)
		 */
		bool LoRotate(fk_Vector^ A, fk_Vector^ B, double theta);

		//! ローカル座標系任意軸回転関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における)
		 *	(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は位置のみを回転させるもので、姿勢は回転しません。
		 *	姿勢の回転も伴いたい場合は LoRotateWithVec() を利用して下さい。
		 *	グローバル座標系で回転移動を行いたい場合は GlRotate() を利用して下さい。
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
		 *	\sa GlRotateWithVec(double, double, double, double, double, double, double),
		 *		LoRotate(double, double, double, double, double, double, double)
		 */
		bool LoRotate(double Ax, double Ay, double Az,
					  double Bx, double By, double Bz, double theta);

		//! グローバル座標系座標軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、origin を通り、
		 *	axis で指定した座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は GlRotate() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	LoRotateWithVec() を利用して下さい。
		 *
		 *	\param[in]		origin		グローバル座標系での回転軸上の点
		 *
		 *	\param[in]		axis
		 *		回転軸に平行な軸。 fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa GlRotate(fk_Vector^, fk_Axis, double),
		 *		LoRotateWithVec(fk_Vector^, fk_Axis, double)
		 */
		bool GlRotateWithVec(fk_Vector^ origin, fk_Axis axis, double theta);

		//! グローバル座標系座標軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(x, y, z) を通り、
		 *	axis で指定した座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は GlRotate() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	LoRotateWithVec() を利用して下さい。
		 *
		 *	\param[in]		x		グローバル座標系での回転軸上の点のx成分
		 *	\param[in]		y		グローバル座標系での回転軸上の点のy成分
		 *	\param[in]		z		グローバル座標系での回転軸上の点のz成分
		 *
		 *	\param[in]		axis
		 *		回転軸に平行な軸。 fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa GlRotate(double, double, double, fk_Axis, double),
		 *		LoRotateWithVec(double, double, double, fk_Axis, double)
		 */
		bool GlRotateWithVec(double x, double y, double z, fk_Axis axis, double theta);

		//! グローバル座標系任意軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は GlRotate() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	LoRotateWithVec() を利用して下さい。
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
		 *	\sa GlRotate(fk_Vector^, fk_Vector^, double),
		 *		LoRotateWithVec(fk_Vector^, fk_Vector^, double)
		 */
		bool GlRotateWithVec(fk_Vector^ A, fk_Vector^ B, double theta);

		//! グローバル座標系任意軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、グローバル座標系によって回転した場所に移動します。
		 *	回転軸は、(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は GlRotate() を利用して下さい。
		 *	ローカル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	LoRotateWithVec() を利用して下さい。
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
		 *	\sa GlRotate(double, double, double, double, double, double, double),
		 *		LoRotateWithVec(double, double, double, double, double, double, double)
		 */
		bool GlRotateWithVec(double Ax, double Ay, double Az,
							 double Bx, double By, double Bz, double theta);

		//! ローカル座標系座標軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) origin を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は LoRotate() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	GlRotateWithVec() を利用して下さい。
		 *
		 *	\param[in]		origin		ローカル座標系での回転軸上の点
		 *
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa LoRotate(fk_Vector^, fk_Axis, double),
		 *		GlRotateWithVec(fk_Vector^, fk_Axis, double)
		 */
		bool LoRotateWithVec(fk_Vector^ origin, fk_Axis axis, double theta);

		//! ローカル座標系座標軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は(ローカル座標系における) (x, y, z) を通り、
		 *	axis で指定した (ローカル座標系における) 座標軸に平行な直線となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は LoRotate() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	GlRotateWithVec() を利用して下さい。
		 *
		 *	\param[in]		x		ローカル座標系での回転軸上の点のx成分
		 *	\param[in]		y		ローカル座標系での回転軸上の点のy成分
		 *	\param[in]		z		ローカル座標系での回転軸上の点のz成分
		 *
		 *	\param[in]		axis
		 *		回転軸に平行なローカル座標系上の軸。
		 *		fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 *
		 *	\param[in]		theta		回転角度(ラジアン)
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa LoRotate(double, double, double, fk_Axis, double),
		 *		GlRotateWithVec(double, double, double, fk_Axis, double)
		 */
		bool LoRotateWithVec(double x, double y, double z, fk_Axis axis, double theta);

		//! ローカル座標系任意軸回転(姿勢付き)関数1
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における) A と B を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は LoRotate() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	GlRotateWithVec() を利用して下さい。
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
		 *	\sa GlRotateWithVec(fk_Vector^, fk_Vector^, double)
		 *		LoRotate(fk_Vector^, fk_Vector^, double)
		 */
		bool LoRotateWithVec(fk_Vector^ A, fk_Vector^ B, double theta);

		//! ローカル座標系任意軸回転(姿勢付き)関数2
		/*!
		 *	モデルの位置を、ローカル座標系によって回転した場所に移動します。
		 *	回転軸は、(ローカル座標系における)
		 *	(Ax, Ay, Az) と (Bx, By, Bz) を通る軸となります。
		 *	回転角度は theta となります。単位は弧度法(ラジアン)です。
		 *
		 *	この関数は、回転の際に姿勢も回転していきます。
		 *	位置のみの回転を行いたい場合は LoRotate() を利用して下さい。
		 *	グローバル座標系で回転移動(姿勢付き)を行いたい場合は、
		 *	GlRotateWithVec() を利用して下さい。
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
		 *	\sa GlRotateWithVec(double, double, double, double, double, double, double),
		 *		LoRotate(double, double, double, double, double, double, double)
		 */
		bool LoRotateWithVec(double Ax, double Ay, double Az,
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
		 *	LoTranslate() を利用して下さい。
		 *
		 *	\param[in]		v		平行移動量ベクトル
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa LoTranslate(fk_Vector^)
		 */
		bool GlTranslate(fk_Vector^ v);

		//! グローバル座標系平行移動関数2
		/*!
		 *	モデルを、クローバル座標系によって平行移動した位置に移動します。
		 *	平行移動量はベクトルの成分を意味する3個の実数で指定します。
		 *
		 *	ローカル座標系による平行移動量の指定を行いたい場合は、
		 *	LoTranslate() を利用して下さい。
		 *
		 *	\param[in]		x		平行移動量ベクトルのx成分
		 *	\param[in]		y		平行移動量ベクトルのy成分
		 *	\param[in]		z		平行移動量ベクトルのz成分
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa LoTranslate(double, double, double)
		 */
		bool GlTranslate(double x, double y, double z);

		//! ローカル座標系平行移動関数1
		/*!
		 *	モデルを、ローカル座標系によって平行移動した位置に移動します。
		 *	平行移動量はベクトルで指定します。
		 *
		 *	グローバル座標系による平行移動量の指定を行いたい場合は、
		 *	GlTranslate() を利用して下さい。
		 *
		 *	\param[in]		v		平行移動量ベクトル
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa GlTranslate(fk_Vector^), GlMoveTo(fk_Vector^)
		 */
		bool LoTranslate(fk_Vector^ v);

		//! ローカル座標系平行移動関数2
		/*!
		 *	モデルを、ローカル座標系によって平行移動した位置に移動します。
		 *	平行移動量はベクトルの成分を意味する3個の実数で指定します。
		 *
		 *	グローバル座標系による平行移動量の指定を行いたい場合は、
		 *	GlTranslate() を利用して下さい。
		 *
		 *	\param[in]		x		平行移動量ベクトルのx成分
		 *	\param[in]		y		平行移動量ベクトルのy成分
		 *	\param[in]		z		平行移動量ベクトルのz成分
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa GlTranslate(double, double, double), GlMoveTo(double, double, double)
		 */
		bool LoTranslate(double x, double y, double z);

		//! グローバル座標系位置指定関数1
		/*!
		 *	モデルの位置を、指定した位置ベクトルに移動します。
		 *	位置はベクトルで指定します。
		 *
		 *	GlMoveTo() 関数に対応するローカル座標系関数
		 *	「LoMoveTo()」関数は存在しません。
		 *	これは、LoMoveTo() 関数はその意味的に
		 *	LoTranslate() とまったく同一の挙動となるためです。
		 *
		 *	\param[in]		p		移動先位置ベクトル
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa GlTranslate(fk_Vector^), LoTranslate(fk_Vector^)
		 */
		bool GlMoveTo(fk_Vector^ p);

		//! グローバル座標系位置指定関数2
		/*!
		 *	モデルの位置を、指定した位置ベクトルに移動します。
		 *	位置はベクトルの成分を意味する3個の実数で指定します。
		 *
		 *	GlMoveTo() 関数に対応するローカル座標系関数
		 *	「LoMoveTo()」関数は存在しません。
		 *	これは、LoMoveTo() 関数はその意味的に
		 *	LoTranslate() とまったく同一の挙動となるためです。
		 *
		 *	\param[in]		x		移動先位置ベクトルのx成分
		 *	\param[in]		y		移動先位置ベクトルのy成分
		 *	\param[in]		z		移動先位置ベクトルのz成分
		 *
		 *	\return			この関数は常に true を返します。
		 *
		 *	\sa GlTranslate(double, double, double), LoTranslate(double, double, double)
		 */
		bool GlMoveTo(double x, double y, double z);
		//@}
	};
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
