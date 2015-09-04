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

		//! \name 二項演算子
		//@{

		//! 色要素和二項演算子
		/*!
		 *	色値 C1 と C2 の和を得るには、以下のように記述します。
		 *	C1, C2, C3 はいずれも fk_Color 型の変数です。
		 *
		 *		C3 = C1 + C2;
		 *
		 *	なお演算の結果、成分値が 1 を超える場合はその成分を 1 とします。
		 */
		static fk_Color^ operator+(fk_Color^, fk_Color^);

		//! 色要素差二項演算子
		/*!
		 *	色値 C1 と C2 の差を得るには、以下のように記述します。
		 *	C1, C2, C3 はいずれも fk_Color 型の変数です。
		 *
		 *		C3 = C1 - C2;
		 *
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 にします。
		 */
		static fk_Color^ operator-(fk_Color^, fk_Color^);

		//! 実数倍二項演算子1
		/*!
		 *	ベクトル C1 のスカラー倍色値を得るには、以下のように記述します。
		 *	C1, C2 は共に fk_Color 型の変数で、d は double 型の変数です。
		 *
		 *		C2 = C1 * d;
		 *
		 *	色値と実数の順番は逆でも構いません。
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 に、
		 *	1 を超える場合はその成分を 1 とします。
		 */
		static fk_Color^ operator*(fk_Color^, double);

		//! 実数倍二項演算子2
		/*!
		 *	ベクトル C1 のスカラー倍色値を得るには、以下のように記述します。
		 *	C1, C2 は共に fk_Color 型の変数で、d は double 型の変数です。
		 *
		 *		C2 = d * C1;
		 *
		 *	色値と実数の順番は逆でも構いません。
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 に、
		 *	1 を超える場合はその成分を 1 とします。
		 */
		static fk_Color^ operator*(double, fk_Color^);

		//! 実数商二項演算子
		/*!
		 *	ベクトル C1 のスカラー商色値を得るには、以下のように記述します。
		 *	C1, C2 は共に fk_Color 型の変数で、d は double 型の変数です。
		 *
		 *		C2 = C1/d;
		 *
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 に、
		 *	1 を超える場合はその成分を 1 とします。
		 */
		static fk_Color^ operator/(fk_Color^, double);

		//@}

		//! \name 代入演算子
		//@{
		
		//! 実数積代入演算子
		/*!
		 *	以下のコードは、C の各成分を d 倍します。
		 *	C は fk_Color 型の変数、d は double 型の変数です。
		 *
		 *		C *= d;
		 *
		 *	d は変数でなく数値でも構いません。
		 *
		 *		C *= 2.0;
		 *
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 に、
		 *	1 を超える場合はその成分を 1 とします。
		 */
		static void operator *= (fk_Color^, double);

		//! 実数商代入演算子
		/*!
		 *	以下のコードは、C の各成分を 1/d 倍します。
		 *	C は fk_Color 型の変数、d は double 型の変数です。
		 *
		 *		C /= d;
		 *
		 *	d は変数でなく数値でも構いません。
		 *
		 *		C /= 2.0;
		 *
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 に、
		 *	1 を超える場合はその成分を 1 とします。
		 *	また、d が 0 であった場合は C の値を変更しません。
		 */
		static void operator /= (fk_Color^, double);

		//! 単項和代入演算子
		/*!
		 *	以下のコードは、C1 に C2 を追加します。
		 *	C1、C2 はいずれも fk_Color 型の変数です。
		 *
		 *		C1 += C2;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		C1 = C1 + C2;
		 *
		 *	なお演算の結果、成分値が 1 を超える場合はその成分を 1 とします。
		 */
		static void operator += (fk_Color^, fk_Color^);

		//! 単項差代入演算子
		/*!
		 *	以下のコードは、C1 から C2 を引きます。
		 *	C1、C2 はいずれも fk_Color 型の変数です。
		 *
		 *		C1 -= C2;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		C1 = C1 - C2;
		 *
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 にします。
		 */
		static void operator -= (fk_Color^, fk_Color^);

		//@}
		
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
		  * (0.04, 0.11, 0.07), (0.09, 0.39, 0.18), (0.08, 0.67, 0.1), (14.0)
		  */
		 static fk_Material^ IridescentGreen;

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
		  * (0.0, 0.0, 0.0), (0.5, 0.7, 0.7), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ PaleBlue;

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
		  * (1.0, 1.0, 1.0), (1.0, 1.0, 1.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ TrueWhite;

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
