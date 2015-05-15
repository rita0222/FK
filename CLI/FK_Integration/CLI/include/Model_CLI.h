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
		
		::fk_Model * GetP(void);
		
	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Model::fk_Model(bool argNewFlg);
#endif

		//! コンストラクタ
		fk_Model::fk_Model();

		//! デストラクタ
		fk_Model::~fk_Model();

		//! ファイナライザ
		fk_Model::!fk_Model();

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

		//////////////////////////////////////////////////////////////
		void DeleteMaterial(void);
		void DeletePointColor(void);
		void DeleteLineColor(void);

		bool SetParent(fk_Model^ model, bool mode);
		bool SetParent(fk_Model^ model);
		void DeleteParent(bool mode);
		void DeleteParent(void);

		bool EntryChild(fk_Model^ model, bool mode);
		bool EntryChild(fk_Model^ model);
		bool DeleteChild(fk_Model^ model, bool mode);
		bool DeleteChild(fk_Model^ model);
		void DeleteChildren(bool mode);
		void DeleteChildren(void);

		void SnapShot(void);
		bool Restore(void);
		bool Restore(double time);

		void AdjustSphere(void);
		void AdjustAABB(void);
		void AdjustOBB(void);
		void AdjustCapsule(fk_Vector^ startPos, fk_Vector^ endPos);

		bool IsInter(fk_Model^ model);
		bool IsCollision(fk_Model^ model, double %time);
		void ResetInter(void);

		void EntryInterModel(fk_Model^ model);
		void DeleteInterModel(fk_Model^ model);
		void ClearInterModel(void);

		//////////////////////////////////////////////////////////////
		bool GlRotate(fk_Vector^ origin, fk_Axis axis, double theta);
		bool GlRotate(double x, double y, double z, fk_Axis axis, double theta);
		bool GlRotate(fk_Vector^ A, fk_Vector^ B, double theta);
		bool GlRotate(double Ax, double Ay, double Az,
					  double Bx, double By, double Bz, double theta);
		bool LoRotate(fk_Vector^ origin, fk_Axis axis, double theta);
		bool LoRotate(double x, double y, double z, fk_Axis axis, double theta);
		bool LoRotate(fk_Vector^ A, fk_Vector^ B, double theta);
		bool LoRotate(double Ax, double Ay, double Az,
					  double Bx, double By, double Bz, double theta);
		bool GlRotateWithVec(fk_Vector^ origin, fk_Axis axis, double theta);
		bool GlRotateWithVec(double x, double y, double z, fk_Axis axis, double theta);
		bool GlRotateWithVec(fk_Vector^ A, fk_Vector^ B, double theta);
		bool GlRotateWithVec(double Ax, double Ay, double Az,
							 double Bx, double By, double Bz, double theta);
		bool LoRotateWithVec(fk_Vector^ origin, fk_Axis axis, double theta);
		bool LoRotateWithVec(double x, double y, double z, fk_Axis axis, double theta);
		bool LoRotateWithVec(fk_Vector^ A, fk_Vector^ B, double theta);
		bool LoRotateWithVec(double Ax, double Ay, double Az,
							 double Bx, double By, double Bz, double theta);
		bool GlTranslate(fk_Vector^ V);
		bool GlTranslate(double x, double y, double z);
		bool LoTranslate(fk_Vector^ V);
		bool LoTranslate(double x, double y, double z);
		bool GlMoveTo(fk_Vector^ V);
		bool GlMoveTo(double x, double y, double z);
	};
}
