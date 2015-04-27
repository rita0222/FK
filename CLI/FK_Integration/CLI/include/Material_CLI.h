// Material_CLI.h

#pragma once

#include <FK/Material.h>
#include <FK/MatExample.h>
#include "Base_CLI.h"

namespace FK_CLI
{
	//! RGB色を管理するクラス
	/*!
	 *	このクラスは、RGBA法による色を管理、制御する機能を提供します。
	 *	「RGBA」のRが赤、Gが緑、Bが青、Aが透過度を意味します。
	 *	各要素は float 型によって表現し、値域は 0 から 1 までです。
	 *	透過色要素は 0 が完全な透明、1 が完全な不透明となります。
	 *
	 *	なお、透過色を設定した場合でも、
	 *	シーンで透過処理設定を有効としなければ、透過処理が行われません。
	 *	詳細は fk_Scene::BlendStatus の説明を参照して下さい。
	 *
	 *	\sa fk_Material, fk_Scene
	 */
	public ref class fk_Color {
	internal:
		bool dFlg;
		::fk_Color *pCol;

		::fk_Color * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Color(bool argNewFlg);
#endif		

		//! コンストラクタ1
		/*!
		 *	RGB値がすべて 0.2, 透過色 1 (完全不透明) であるデフォルト値で色を生成します。
		 */
		fk_Color();

		//! コンストラクタ2
		/*!
		 *	R,G,Bの各色を引数で指定します。透過色要素は初期値では 1 になります。
		 *
		 *	\param[in] R R要素の値
		 *	\param[in] G G要素の値
		 *	\param[in] B B要素の値
		 */
		fk_Color(double R, double G, double B);
		
		//! コンストラクタ3
		/*!
		 *	R,G,B,A(透過色)の各色を引数で指定します。
		 *
		 *	\param[in] R R要素の値
		 *	\param[in] G G要素の値
		 *	\param[in] B B要素の値
		 *	\param[in] A A要素の値
		 */
		fk_Color(double R, double G, double B, double A);

		//! コンストラクタ4
		/*!
		 *	R,G,Bの各色を引数で指定します。透過色要素は初期値では 1 になります。
		 *
		 *	\param[in] R R要素の値
		 *	\param[in] G G要素の値
		 *	\param[in] B B要素の値
		 */
		fk_Color(float R, float G, float B);

		//! コンストラクタ5
		/*!
		 *	R,G,B,A(透過色)の各色を引数で指定します。
		 *
		 *	\param[in] R R要素の値
		 *	\param[in] G G要素の値
		 *	\param[in] B B要素の値
		 *	\param[in] A A要素の値
		 */
		fk_Color(float R, float G, float B, float A);

		//! デストラクタ
		~fk_Color();

		//! ファイナライザ
		!fk_Color();

		//! 色要素配列プロパティ
		/*!
		 *	各色要素を float の配列によってアクセスできるプロパティです。
		 *	メンバ関数を介さずに直接参照、操作しても問題ありません。
		 */
		property float col[int] {
			float get(int argI);
			void set(int argI, float argC);
		}

		//! R(赤)要素プロパティ
		/*!
		 *	R(赤)要素の参照・設定を行います。0から1の値となります。
		 */
		property float r {
			float get();
			void set(float argF);
		}

		//! G(緑)要素プロパティ
		/*!
		 *	G(緑)要素の参照・設定を行います。0から1の値となります。
		 */
		property float g {
			float get();
			void set(float argF);
		}

		//! B(青)要素プロパティ
		/*!
		 *	B(青)要素の参照・設定を行います。0から1の値となります。
		 */
		property float b {
			float get();
			void set(float argF);
		}

		//! A(透過色)要素プロパティ
		/*!
		 *	A(透過色)要素の参照・設定を行います。
		 *	0から1の値となり、0 が完全な透明、1 が完全な不透明となります。
		 */
		property float a {
			float get();
			void set(float argF);
		}

		//! 同値比較関数1
		/*!
		 *	二つの色値が同値かどうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	C	同値かどうかを判定する色値
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		bool fk_Color::Equals(fk_Color^ C);

		//! 同値比較関数2
		/*!
		 *	二つの色値の値が同値かどうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	C	同値かどうかを判定する色値
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		virtual bool fk_Color::Equals(Object^ C) override;

		//! 文字列出力関数
		/*!
		 *	現在の色成分値を文字列として出力します。
		 *
		 *	\return		成分値の文字列
		 */
		String^ fk_Color::ToString() override;

		//! 初期化関数1
		/*!
		 *	(R, G, B, A) = (0, 0, 0, 1) で初期化を行います。
		 */
		void Init(void);

		//! 初期化関数2
		/*!
		 *	色要素の設定を行います。
		 *	Set(float, float, float) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 */
		void Init(float R, float G, float B);

		//! 初期化関数3
		/*!
		 *	色要素の設定を行います。
		 *	同一引数型を持つ Set(float, float, float, float) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 *	\param[in] A A要素値
		 */
		void Init(float R, float G, float B, float A);

		//! 初期化関数4
		/*!
		 *	色要素の設定を行います。
		 *	Set(double, double, double) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 */
		void Init(double R, double G, double B);

		//! 初期化関数5
		/*!
		 *	色要素の設定を行います。
		 *	同一引数型を持つ Set(double, double, double, double) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 *	\param[in] A A要素値
		 */
		void Init(double R, double G, double B, double A);

		//! 設定関数1
		/*!
		 *	色要素の設定を行います。
		 *	Init(float, float, float) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 */
		void Set(float R, float G, float B);

		//! 設定関数2
		/*!
		 *	色要素の設定を行います。
		 *	Init(float, float, float, float) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 *	\param[in] A A要素値
		 */
		void Set(float R, float G, float B, float A);

		//! 設定関数3
		/*!
		 *	色要素の設定を行います。
		 *	Init(double, double, double) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 */
		void Set(double R, double G, double B);

		//! 設定関数4
		/*!
		 *	色要素の設定を行います。
		 *	Init(double, double, double, double) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 *	\param[in] A A要素値
		 */
		void Set(double R, double G, double B, double A);

		//! HSV変換関数
		/*!
		 *	HSV色からの変換を行い、その結果を格納します。
		 *	透明度は 1.0 (完全な不透明) となります。
		 *	
		 *
		 *	\param[in] H 色相要素値。単位は弧度法(ラジアン)です。
		 *	\param[in] S 彩度要素値。最小値は0、最大値は1です。
		 *	\param[in] V 明度要素値。最小値は0、最大値は1です。
		 */
		void SetHSV(double H, double S, double V);
	};

	//! マテリアル(質感)を管理するクラス
	/*!
	 *	このクラスは、マテリアル(質感)を管理、制御する機能を提供します。
	 *	FKにおけるマテリアルは、以下の要素によって成り立っています。
	 *
	 *	- 環境反射係数 (Ambient)
	 *	- 拡散反射係数 (Diffuse)
	 *	- 鏡面反射係数 (Specular)
	 *	- 放射光係数 (Emission)
	 *	- 鏡面反射ハイライト (Shininess)
	 *	- 透明度 (alpha)
	 *	.
	 *	これらのうち、前者4つは fk_Color による RGBA 色表現であり、
	 *	後者2つは float 型によるスカラー値となっています。
	 *	各要素についての詳細はユーザーズマニュアルやCGの解説文献を参照して下さい。
	 *
	 *	マテリアルには、最初から定義されているグローバル変数があります。
	 *	これらのリストはユーザーズマニュアルの付録Aに記されています。
	 *	利用するには、 InitDefault() 関数を呼ぶ必要があります。
	 *
	 *	インスタンス生成時の初期状態は以下のような値となります。
	 *
	 *	- 環境反射係数: (0.3, 0.3, 0.3)
	 *	- 拡散反射係数: (0.0, 0.0, 0.0)
	 *	- 鏡面反射係数: (0.2, 0.2, 0.2)
	 *	- 放射光係数: (0.0, 0.0, 0.0)
	 *	- 鏡面反射ハイライト: 17.0
	 *	- 透明度: 1.0
	 *	.
	 *	なお、透過色を設定した場合でも、
	 *	シーンで透過処理設定を有効としなければ、透過処理が行われません。
	 *	詳細は fk_Scene::BlendStatus の説明を参照して下さい。
	 *
	 *	\sa fk_Color, fk_Palette, fk_Scene
	 */
	 public ref class fk_Material {
	 internal:
		 bool dFlg;
		 ::fk_Material *pMat;

		 ::fk_Material * GetP(void);

	 public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		 fk_Material(bool argNewFlg);
#endif
		 //! コンストラクタ
		 fk_Material();

		 //! デストラクタ
		 ~fk_Material();

		 //! ファイナライザ
		 !fk_Material();

		 //! 同値比較関数1
		 /*!
		  *	二つのマテリアル値が同値かどうかを判定します。
		  *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		  *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		  *
		  *	\param[in]	M	同値かどうかを判定するマテリアル値
		  *
		  *	\return		同値であれば true を、そうでなければ false を返します。
		  */
		 bool Equals(fk_Material^ M);

		 //! 同値比較関数2
		 /*!
		  *	二つのマテリアル値が同値かどうかを判定します。
		  *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		  *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		  *
		  *	\param[in]	M	同値かどうかを判定するマテリアル値
		  *
		  *	\return		同値であれば true を、そうでなければ false を返します。
		  */
		 virtual bool Equals(Object^ M) override;

		 //! 透明度プロパティ
		 /*!
		  *	透明度の設定・参照を行います。引数は float 型です。
		  *	設定できる値は 0 から 1 までで、
		  *	範囲外の数値については上下限に丸められます。
		  *
		  *	\note
		  *		透過色を設定した場合でも、
		  *		シーンで透過処理設定を有効としなければ、透過処理が行われません。
		  *		詳細は fk_Scene::BlendStatus の説明を参照して下さい。
		  *
		  *	\sa fk_Scene::BlendStatus
		  */
		 property float Alpha {
			 float get();
			 void set(float argF);
		 }

		 //! 環境反射係数プロパティ
		 /*!
		  *	環境反射係数の設定・参照を行います。
		  *	プロパティは fk_Color 型です。
		  */
		 property fk_Color^ Ambient {
			 fk_Color^ get();
			 void set(fk_Color^ argC);
		 }

		 //! 拡散反射係数プロパティ
		 /*!
		  *	拡散反射係数の設定・参照を行います。
		  *	プロパティは fk_Color 型です。
		  */
		 property fk_Color^ Diffuse {
			 fk_Color^ get();
			 void set(fk_Color^ argC);
		 }

		 //! 鏡面反射係数プロパティ
		 /*!
		  *	鏡面反射係数の設定・参照を行います。
		  *	プロパティは fk_Color 型です。
		  */
		 property fk_Color^ Specular {
			 fk_Color^ get();
			 void set(fk_Color^ argC);
		 }

		 //! 放射光反射係数プロパティ
		 /*!
		  *	放射光反射係数の設定・参照を行います。
		  *	プロパティは fk_Color 型です。
		  */
		 property fk_Color^ Emission {
			 fk_Color^ get();
			 void set(fk_Color^ argC);
		 }

		 //! 初期化関数
		 /*!
		  *	変数を初期状態に戻します。
		  */
		 void Init(void);

		 //! デフォルトマテリアル初期化関数
		 /*!
		  *	この関数を呼ぶと、
		  *	ユーザーズマニュアルに掲載しているマテリアル変数の値を、
		  *	マニュアルに記載してある値に初期化します。
		  *	この関数を呼んだ後、該当マテリアル変数を
		  *	別のマテリアル値に設定することが可能です。
		  *
		  *	この関数は static 宣言されているため、
		  *	クラスのインスタンスを生成しなくても呼ぶことができます。
		  */
		 static void InitDefault(void);

		 /*!
		  * (0.2, 0.2, 0.2), (0.4, 0.4, 0.4), (0.01, 0.01, 0.01), (10.0)
		  */
		 static fk_Material^ AshGray;

		 /*!
		  * (0.15, 0.28, 0.23), (0.23, 0.47, 0.19), (0.37, 0.68, 0.28), (20.0)
		  */
		 static fk_Material^ BambooGreen;

		 /*!
		  * (0.0, 0.0, 0.0), (0.0, 0.0, 0.7), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Blue;

		 /*!
		  * (0.2, 0.1, 0.0), (0.35, 0.15, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Brown;

		 /*!
		  * (0.1, 0.07, 0.07), (0.44, 0.17, 0.1), (0.6, 0.39, 0.1), (16.0)
		  */
		 static fk_Material^ BurntTitan;

		 /*!
		  * (0.5, 0.3, 0.4), (0.9, 0.5, 0.7), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Coral;

		 /*!
		  * (0.0, 0.0, 0.0), (0.8, 0.7, 0.6), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Cream;

		 /*!
		  * (0.0, 0.0, 0.0), (0.0, 0.6, 0.6), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Cyan;

		 /*!
		  * (0.1, 0.1, 0.4), (0.0, 0.0, 0.25), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ DarkBlue;

		 /*!
		  * (0.1, 0.4, 0.1), (0.0, 0.2, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ DarkGreen;

		 /*!
		  * (0.3, 0.1, 0.3), (0.3, 0.0, 0.3), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ DarkPurple;

		 /*!
		  * (0.2, 0.0, 0.0), (0.4, 0.0, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ DarkRed;

		 /*!
		  * (0.0, 0.0, 0.0), (0.4, 0.3, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ DarkYellow;

		 /*!
		  * (0.18, 0.14, 0.0), (0.84, 0.86, 0.07), (0.92, 0.82, 0.49), (0.0)
		  */
		 static fk_Material^ DimYellow;

		 /*!
		  * (0.0, 0.0, 0.0), (0.8, 0.6, 0.4), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Flesh;

		 /*!
		  * (0.0, 0.0, 0.0), (0.04, 0.04, 0.04), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ GlossBlack;

		 /*!
		  * (0.0, 0.1, 0.0), (0.0, 0.7, 0.0), (0.47, 0.98, 0.49), (0.0)
		  */
		 static fk_Material^ GrassGreen;

		 /*!
		  * (0.0, 0.0, 0.0), (0.6, 0.6, 0.6), (0.1, 0.1, 0.1), (0.0)
		  */
		 static fk_Material^ Gray1;

		 /*!
		  * (0.0, 0.0, 0.0), (0.2, 0.2, 0.2), (0.1, 0.1, 0.1), (0.0)
		  */
		 static fk_Material^ Gray2;

		 /*!
		  * (0.0, 0.0, 0.0), (0.0, 0.5, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Green;

		 /*!
		  * (0.01, 0.22, 0.4), (0.2, 0.66, 0.92), (0.47, 0.74, 0.74), (0.0)
		  */
		 static fk_Material^ HolidaySkyBlue;

		 /*!
		  *Ir, (0.04, 0.11, 0.07), (0.09, 0.39, 0.18), (0.08, 0.67, 0.1), (14.0)
		  */
		 static fk_Material^ idescentGreen;

		 /*!
		  * (0.36, 0.28, 0.18), (0.56, 0.52, 0.29), (0.72, 0.45, 0.4), (33.0)
		  */
		 static fk_Material^ Ivory;

		 /*!
		  * (0.14, 0.0, 0.0), (0.62, 0.0, 0.0), (1.0, 0.46, 0.46), (18.0)
		  */
		 static fk_Material^ LavaRed;

		 /*!
		  * (0.0, 0.0, 0.0), (0.4, 0.4, 0.9), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ LightBlue;

		 /*!
		  * (0.1, 0.2, 0.2), (0.0, 0.5, 0.5), (0.2, 0.2, 0.2), (60.0)
		  */
		 static fk_Material^ LightCyan;

		 /*!
		  * (0.0, 0.0, 0.0), (0.5, 0.7, 0.3), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ LightGreen;

		 /*!
		  * (0.0, 0.0, 0.0), (0.5, 0.4, 0.9), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ LightViolet;

		 /*!
		  * (0.21, 0.09, 0.23), (0.64, 0.54, 0.6), (0.4, 0.26, 0.37), (15.0)
		  */
		 static fk_Material^ Lilac;

		 /*!
		  * (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ MatBlack;

		 /*!
		  * (0.0, 0.0, 0.0), (0.8, 0.3, 0.0), (0.2, 0.2, 0.2), (0.0)
		  */
		 static fk_Material^ Orange;

		 /*!
		  *Pa, (0.0, 0.0, 0.0), (0.5, 0.7, 0.7), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ leBlue;

		 /*!
		  * (0.32, 0.29, 0.18), (0.64, 0.61, 0.5), (0.4, 0.29, 0.17), (15.0)
		  */
		 static fk_Material^ PearWhite;

		 /*!
		  * (0.6, 0.2, 0.3), (0.9, 0.55, 0.55), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Pink;

		 /*!
		  * (0.0, 0.0, 0.0), (0.7, 0.0, 0.7), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Purple;

		 /*!
		  * (0.0, 0.0, 0.0), (0.7, 0.0, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Red;

		 /*!
		  * (0.01, 0.03, 0.21), (0.07, 0.12, 0.49), (0.53, 0.52, 0.91), (11.0)
		  */
		 static fk_Material^ UltraMarine;

		 /*!
		  * (0.0, 0.0, 0.0), (0.4, 0.0, 0.8), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Violet;

		 /*!
		  * (0.0, 0.0, 0.0), (0.8, 0.8, 0.8), (0.1, 0.1, 0.1), (0.0)
		  */
		 static fk_Material^ White;

		 /*!
		  * (0.0, 0.0, 0.0), (0.8, 0.6, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Yellow;

	 };
}
