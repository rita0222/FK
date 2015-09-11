// ShapeViewer_CLI.h

#pragma once

#include <FK/ShapeViewer.h>
#include "Matrix_CLI.h"
#include "Image_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	//! 簡易形状表示システム用クラス
	/*!
	 *	このクラスは、簡易形状表示システムを制御する機能を提供します。
	 *
	 *	FK システムにおいて、形状を表示するためには形状用インスタンスの他にモデル、
	 *	シーン、ウィンドウを準備する必要があります。
	 *	また、様々な角度から形状を閲覧したい場合には、
	 *	さらにカメラ操作のプログラムを追加しなければなりません。
	 *	fk_ShapeViewer を用いると、モデル、シーン、ウィンドウを準備する必要はなく、
	 *	閲覧するための機能が最初から備わっています。
	 *
	 *	fk_ShapeViewer が備えている標準機能は、以下のようなものがあります。
	 *	- VRML、STL、DXF 各フォーマットファイル入力機能と、VRML ファイル出力機能。
	 *	- 表示されている画像をファイルに保存する機能。
	 *	- 面表示、稜線表示、頂点表示の各 ON/OFF および座標軸表示の ON/OFF。
	 *	- 光源回転有無の制御。
	 *	- 面のマテリアルおよび稜線、頂点の表示色設定。
	 *	- GUI による姿勢制御および表示倍率、座標軸サイズの制御。
	 *	- 左右矢印キーによるヘディング角制御。
	 *	- スペースキーによる表示倍率制御。スペースキー単体で拡大、
	 *		シフトキーとスペースキーを同時に押すことで縮小が行えます。
	 *	- マウスドラッグ操作による形状の平行移動。
	 *	.
	 *	上記の操作は全てメニューなどの GUI から操作が可能で、
	 *	プログラムとして記述する必要がありません。
	 *	また、以下に述べるような各種メンバ関数を利用することで、
	 *	プログラムから細かく制御することもできます。
	 *	例えば、複数の形状を別々に動作させるといった制御も可能となります。
	 *	特に ID を指定しなかった場合や、メニューから形状データを読み込んだ場合は、
	 *	形状 ID が 0 となります。
	 *
	 *	変形アニメーションの様子を表示することも可能です。
	 *	これは、 Draw() を変形する度に呼び出すことで実現できます。
	 *
	 *	\sa fk_AppWindow
	 */
	public ref class fk_ShapeViewer : fk_BaseObject {
	internal:
		::fk_ShapeViewer * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_ShapeViewer(bool argNewFlg);
#endif
		//! コンストラクタ1
		/*!
		 *	描画領域の大きさが横幅 300 ピクセル、
		 *	縦幅 360 ピクセルとしてインスタンスを生成します。
		 *	ウィンドウ全体の大きさではないことに注意して下さい。
		 */
		fk_ShapeViewer();

		//! コンストラクタ2
		/*!
		 *	描画領域の大きさを指定することができます。単位はピクセルとなります。
		 *	ウィンドウ全体の大きさではないことに注意して下さい。
		 *
		 *	\param[in]	w	描画領域横幅
		 *	\param[in]	h	描画領域縦幅
		 */
		fk_ShapeViewer(int w, int h);

		//! デストラクタ
		~fk_ShapeViewer();

		//! ファイナライザ
		!fk_ShapeViewer();

		//! 描画領域サイズプロパティ
		/*!
		 *	描画領域のサイズを変更します。単位はピクセルとなります。
		 */
		property fk_Dimension^ WindowSize {
			void set(fk_Dimension^);
		}

		//! 単独形状参照・設定プロパティ
		/*!
		 *	形状を描画対象として設定します。
		 *	fk_Shape の派生クラスであれば、
		 *	(テクスチャ系も含めて)全てのクラスを描画対象として設定できます。
		 *
		 *	なお、このプロパティへの設定は ID を 0 番として
		 *	SetShape(int, fk_Shape^) を用いた場合と同義になります。
		 *	また、参照は GetShape() において ID に 0 を指定した場合と同義となります。
		 *
		 *	\sa SetShape(), GetShape()
		 */
		property fk_Shape^ Shape {
			void set(fk_Shape^);
			fk_Shape^ get();
		}

		//! 形状設定数プロパティ
		/*!
		 *	現在設定されている形状の個数を参照します。
		 */
		property int ModelNum {
			int get();
		}

		//! 描画モードプロパティ
		/*!
		 *	登録されている全ての形状の描画モードを設定します。
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
		 *		fk_ShapeViewer	viewer;
		 *
		 *		viewer.DrawMode = fk_DrawMode.POINTMODE | fk_DrawMode.LINEMODE | fk_DrawMode.POLYMODE;
		 *
		 *	個別の形状に対して別々の描画モードを設定する場合は、
		 *	SetDrawMode(int, fk_DrawMode) を利用して下さい。
		 *
		 *	\sa SetDrawMode(int, fk_DrawMode), fk_Model::DrawMode
		 */
		property fk_DrawMode DrawMode {
			fk_DrawMode get();
			void set(fk_DrawMode);
		}

		//! 透過処理プロパティ
		/*!
		 *	描画の際、透過処理を有効とするかどうかの参照・設定を行います。
		 *	true であれば有効、false であれば無効とします。
		 *	機能的には fk_Scene::BlendStatus プロパティと同様です。
		 *	詳細は、 fk_Scene::BlendStatus のマニュアルを参照して下さい。
		 *
		 *	\sa fk_Scene::BlendStatus
		 */
		property bool BlendStatus {
			bool get();
			void set(bool);
		}

		//! 背景色プロパティ
		/*!
		 *	描画領域背景色の参照・設定を行います。
		 */
		property fk_Color^ BGColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		//! 座標軸描画設定関数
		/*!
		 *	座標軸の表示の有無の参照・設定を行います。
		 *	true であれば描画有効、false であれば無効とします。
		 *
		 *	\sa AxisScale
		 */
		property bool AxisMode {
			bool get();
			void set(bool);
		}

		//! 座標軸大きさ設定関数
		/*!
		 *	座標軸の大きさの参照・設定を行います。
		 *	ここでいう大きさとは、各軸の長さのことです。
		 *
		 *	\sa AxisMode
		 */
		property double AxisScale {
			double get();
			void set(double);
		}

		//! 描画領域中心座標プロパティ
		/*!
		 *	現在の描画領域で中心(注視点)となっている位置の位置ベクトルを参照します。
		 */
		property fk_Vector^ Center {
			fk_Vector^ get();
		}

		//! カメラヘッド角プロパティ
		/*!
		 *	カメラのヘッド角の参照・設定を行います。
		 *	ヘッド角についての詳細は、 fk_Angle の解説を参照して下さい。
		 *	引数の単位は弧度法(ラジアン)となります。
		 *
		 *	\sa Pitch, Bank, Scale, fk_Angle
		 */
		property double Head {
			double get();
			void set(double);
		}
		
		//! カメラピッチ角プロパティ
		/*!
		 *	カメラのピッチ角の参照・設定を行います。
		 *	ピッチ角についての詳細は、 fk_Angle の解説を参照して下さい。
		 *	引数の単位は弧度法(ラジアン)となります。
		 *
		 *	\sa Head, Bank, Scale, fk_Angle
		 */
		property double Pitch {
			double get();
			void set(double);
		}

		//! カメラバンク角プロパティ
		/*!
		 *	カメラのバンク角の参照・設定を行います。
		 *	バンク角についての詳細は、 fk_Angle の解説を参照して下さい。
		 *	引数の単位は弧度法(ラジアン)となります。
		 *
		 *	\sa Head, Pitch, Scale, fk_Angle
		 */
		property double Bank {
			double get();
			void set(double);
		}

		//! カメラ倍率プロパティ
		/*!
		 *	カメラの表示倍率を設定します。
		 *
		 *	\sa Head, Picth, Bank
		 */
		property double Scale {
			double get();
			void set(double);
		}
		
		//! \name 描画処理・描画領域制御関数
		//@{

		//! 描画更新関数
		/*!
		 *	形状の描画を行います。
		 *	GUI ならびにメンバ関数によって操作を行っても、
		 *	この関数を呼ばなければ画面は更新されません。
		 *
		 *	通常は、以下のようなコードを記述することになります。
		 *
		 *		fk_ShapeViewer	viewer;
		 *
		 *		while(viewer.Draw() == true) {
		 *			// (もし必要なら)形状の変形処理を記述
		 *		}
		 *
		 *	\return
		 *		描画が正常に行えた場合、true を返します。
		 *		そうでない場合に false を返します。
		 *		これは例えば、ウィンドウが閉じられた場合などがそれに当たります。
		 */
		bool		Draw(void);

		//! ID付き形状設定関数
		/*!
		 *	形状を描画対象として設定します。
		 *	複数の形状を同時に描画したい場合は、
		 *	異なる ID をそれぞれの形状に付けることで実現できます。
		 *
		 *	Shape プロパティによる設定は、
		 *	本関数で ID に 0 を入力した場合と同義となります。
		 *
		 *	\param[in]	ID		形状 ID
		 *	\param[in]	shape	形状インスタンス
		 */
		void		SetShape(int ID, fk_Shape^ shape);

		//! 形状参照関数
		/*!
		 *	指定した ID で設定されている形状インスタンスを返します。
		 *	Shape プロパティを参照することは、
		 *	本関数で ID に 0 を入力した場合と同義となります。
		 *
		 *	\param[in]	ID	形状 ID
		 *
		 *	\return
		 *		形状インスタンスを返します。
		 *		指定した ID の形状インスタンスが存在しない場合は、null を返します。
		 */
		fk_Shape^	GetShape(int ID);

		//! 形状設定初期化関数
		/*!
		 *	現在設定されている全ての形状情報を消去します。
		 */
		void		ClearModel(void);

		//@}
		
		//! \name 形状個別描画属性・マテリアル設定関数
		//@{

		//! 個別形状描画モード設定関数
		/*!
		 *	個別の形状に対して描画モードを設定します。
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
		 *		fk_ShapeViewer	viewer;
		 *
		 *		viewer.setDrawMode(1, fk_DrawMode.POINTMODE | fk_DrawMode.LINEMODE | fk_DrawMode.POLYMODE);
		 *
		 *	全ての形状に対しての描画モードを設定する場合は、
		 *	fk_ShapeViewer::DrawMode プロパティを利用して下さい。
		 *
		 *	\param[in]	ID		形状 ID
		 *	\param[in]	mode	描画モード
		 *
		 *	\sa DrawMode, fk_Model::DrawMode
		 */
		void		SetDrawMode(int ID, fk_DrawMode mode);
		
		//! 描画モード参照関数
		/*!
		 *	現在の描画モードを参照します。
		 *
		 *	\return		描画モード
		 *
		 *	\sa SetDrawMode(int, fk_DrawMode)
		 */
		fk_DrawMode	GetDrawMode(int ID);

		
		//! 形状稜線描画幅設定関数
		/*!
		 *	形状に対し、稜線の描画幅を設定します。
		 *	単位はピクセルです。整数以外も設定可能です。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	width	描画幅
		 */
		void		SetLineWidth(int ID, double width);

		//! 形状稜線描画幅参照関数
		/*!
		 *	形状の稜線描画幅を取得します。
		 *	単位はピクセルです。
		 *
		 *	\param[in]	ID		形状ID
		 *
		 *	\return		描画幅
		 *
		 *	\sa GetLineWidth()
		 */
		double		GetLineWidth(int ID);

		//! 形状頂点描画サイズ設定関数
		/*!
		 *	形状に対し、頂点描画サイズを設定します。
		 *	単位はピクセルです。整数以外も設定可能です。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	size	描画サイズ
		 */
		void		SetPointSize(int ID, double size);

		//! 形状頂点描画サイズ参照関数
		/*!
		 *	形状の頂点描画サイズを取得します。
		 *	単位はピクセルです。
		 *
		 *	\param[in]	ID		形状ID
		 *
		 *	\return		描画サイズ
		 *
		 *	\sa SetPointSize()
		 */
		double		GetPointSize(int ID);

		//! 形状マテリアル設定関数
		/*!
		 *	形状に対し、面のマテリアルを設定します。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	mat		マテリアル
		 *
		 *	\sa SetEdgeColor(), SetVertexColor(), fk_Material
		 */
		void		SetMaterial(int ID, fk_Material^ mat);

		//! 形状稜線描画色設定関数
		/*!
		 *	形状に対し、稜線の描画色を設定します。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	col		稜線色
		 *
		 *	\sa SetMaterial(), SetVertexColor(), fk_Color
		 */
		void		SetEdgeColor(int ID, fk_Color^ col);

		//! 形状頂点描画色設定関数
		/*!
		 *	形状に対し、頂点の描画色を設定します。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	col		頂点色
		 *
		 *	\sa SetMaterial(), SetEdgeColor(), fk_Color
		 */
		void		SetVertexColor(int ID, fk_Color^ col);

		//@}

		//! \name カメラ角度・倍率制御関数
		//@{

		//! 形状位置設定関数1
		/*!
		 *	形状の位置を設定します。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	pos		形状位置ベクトル
		 *
		 *	\sa	SetPosition(int, double, double, double),
		 *		SetAngle(int, fk_Angle^), SetVec(int, fk_Vector^),
		 *		SetUpvec(int, fk_Vector^)
		 */
		void		SetPosition(int ID, fk_Vector^ pos);

		//! 形状位置設定関数2
		/*!
		 *	形状の位置を設定します。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	x		形状位置ベクトルのx成分
		 *	\param[in]	y		形状位置ベクトルのy成分
		 *	\param[in]	z		形状位置ベクトルのz成分
		 *
		 *	\sa SetPosition(int, fk_Vector^),
		 *		SetAngle(int, fk_Angle^), SetVec(int, fk_Vector^),
		 *		SetUpvec(int, fk_Vector^)
		 */
		void		SetPosition(int ID, double x, double y, double z);

		//! 形状姿勢設定関数1
		/*!
		 *	形状の姿勢をオイラー角で設定します。
		 *	オイラー角については、 fk_Angle の解説を参照して下さい。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	angle	姿勢を表すオイラー角
		 *
		 *	\sa SetAngle(int, double, double, double),
		 *		SetPosition(int, fk_Vector^), SetVec(int, fk_Vector^),
		 *		SetUpvec(int, fk_Vector^)
		 */
		void		SetAngle(int ID, fk_Angle^ angle);

		//! 形状姿勢設定関数2
		/*!
		 *	形状の姿勢をオイラー角で設定します。
		 *	オイラー角については、 fk_Angle の解説を参照して下さい。
		 *	なお、角度の単位は弧度法(ラジアン)となります。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	h		姿勢を表すオイラー角のヘッド角度
		 *	\param[in]	p		姿勢を表すオイラー角のピッチ角度
		 *	\param[in]	b		姿勢を表すオイラー角のバンク角度
		 *
		 *	\sa SetAngle(int, fk_Angle^),
		 *		SetPosition(int, fk_Vector^), SetVec(int, fk_Vector^),
		 *		SetUpvec(int, fk_Vector^)
		 */
		void		SetAngle(int ID, double h, double p, double b);

		//! 形状方向ベクトル設定関数1
		/*!
		 *	形状の方向ベクトルを設定します。
		 *	方向ベクトルは正規化してある必要はありません。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	vec		方向ベクトル
		 *
		 *	\sa SetVec(int, double, double, double),
		 *		SetPosition(int, fk_Vector^), SetAngle(int, fk_Angle^),
		 *		SetUpvec(int, fk_Vector^)
		 */
		void		SetVec(int ID, fk_Vector^ vec);

		//! 形状方向ベクトル設定関数2
		/*!
		 *	形状の方向ベクトルを設定します。
		 *	方向ベクトルは正規化してある必要はありません。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	x		方向ベクトルのx成分
		 *	\param[in]	y		方向ベクトルのy成分
		 *	\param[in]	z		方向ベクトルのz成分
		 *
		 *	\sa SetVec(int, fk_Vector^),
		 *		SetPosition(int, fk_Vector^), SetAngle(int, fk_Angle^),
		 *		SetUpvec(int, fk_Vector^)
		 */
		void		SetVec(int ID, double x, double y, double z);

		//! 形状アップベクトル設定関数1
		/*!
		 *	形状のアップベクトルを設定します。
		 *	アップベクトルは正規化してある必要はありません。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	vec		アップベクトル
		 *
		 *	\sa SetUpvec(int, double, double, double),
		 *		SetPosition(int, fk_Vector^), SetAngle(int, fk_Angle^),
		 *		SetVec(int, fk_Vector^)
		 */
		void		SetUpvec(int ID, fk_Vector^ vec);

		//! 形状アップベクトル設定関数2
		/*!
		 *	形状のアップベクトルを設定します。
		 *	アップベクトルは正規化してある必要はありません。
		 *
		 *	\param[in]	ID		形状ID
		 *	\param[in]	x		アップベクトルのx成分
		 *	\param[in]	y		アップベクトルのy成分
		 *	\param[in]	z		アップベクトルのz成分
		 *
		 *	\sa SetUpvec(int, fk_Vector^),
		 *		SetPosition(int, fk_Vector^), SetAngle(int, fk_Angle^),
		 *		SetVec(int, fk_Vector^)
		 */
		void		SetUpvec(int ID, double x, double y, double z);

		//@}

		//! \name 描画画像取り込み関数
		//@{

		//! 描画画像ファイル出力関数
		/*!
		 *	この関数は、描画領域に表示されている画像を、画像ファイルとして出力します。
		 *
		 *	\param[in]	fileName	画像ファイル名
		 *
		 *	\param[in]	format
		 *		画像ファイルのフォーマット。
		 *		現在利用可能なフォーマットは、
		 *		fk_ImageType の解説を参照して下さい。
		 *
		 *	\return
		 *		出力に成功すれば true を、失敗すれば false を返します。
		 */
		bool		SnapImage(String^ fileName, fk_ImageType format);

		//! 描画画像データ出力関数
		/*!
		 *	この関数は、描画領域に表示されている画像を、
		 *	fk_Image 型のインスタンスに出力します。
		 *
		 *	\param[in]	image		画像データ出力先インスタンス
		 *
		 *	\return
		 *		出力に成功すれば true を、失敗すれば false を返します。
		 */
		bool		SnapImage(fk_Image^ image);
		//@}
	};
}
