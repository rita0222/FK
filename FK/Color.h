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


#ifndef __FK_COLOR_HEADER__
#define __FK_COLOR_HEADER__

#include <FK/Base.h>

namespace FK {

	const float FK_COLOR_EPS = 0.0001f;

	//! RGB色を管理するクラス
	/*!
	 *	このクラスは、RGBA法による色を管理、制御する機能を提供します。
	 *	「RGBA」のRが赤、Gが緑、Bが青、Aが透過度を意味します。
	 *	各要素は float 型によって表現し、値域は 0 から 1 までです。
	 *	透過色要素は 0 が完全な透明、1 が完全な不透明となります。
	 *
	 *	なお、透過色を設定した場合でも、
	 *	シーンで透過処理設定を有効としなければ、透過処理が行われません。
	 *	詳細は fk_Scene::setBlendStatus() の説明を参照して下さい。
	 *
	 *	\sa fk_Material, fk_Scene
	 */
	class fk_Color : public fk_BaseObject {
	public:

		//! 色要素配列
		/*!
		 *	各色要素を float の配列によって格納しています。
		 *	メンバ関数を介さずに直接参照、操作しても問題ありません。
		 */
		std::vector<float> col;

		//! コンストラクタ1
		/*!
		 *	\param[in] r R要素の値
		 *	\param[in] g G要素の値
		 *	\param[in] b B要素の値
		 *	\param[in] a 透過要素の値
		 */
		fk_Color(float r = 0.2f, float g = 0.2f, float b = 0.2f, float a = 1.0f);

		//! コンストラクタ2
		/*!
		 *	引数の型が double 型である以外は、「コンストラクタ1」と同じです。
		 *
		 *	\param[in] r R要素の値
		 *	\param[in] g G要素の値
		 *	\param[in] b B要素の値
		 *	\param[in] a 透過要素の値
		 */
		fk_Color(double r, double g, double b, double a = 1.0);

		//! デストラクタ
		virtual ~fk_Color() {}

		//! 比較等号演算子
		/*!
		 *	この等号演算子では、各色要素の差が
		 *	FK_COLOR_EPS(現バージョンでは 0.0001) 内の誤差内であれば
		 *	等しいと判断します。
		 */
		friend bool operator ==(fk_Color left, fk_Color right);

		//! コピーコンストラクタ
		fk_Color(const fk_Color &col);

		//! 単純代入演算子
		fk_Color & operator =(const fk_Color &col);

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
		fk_Color &			operator *=(double);

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
		fk_Color &			operator /=(double);

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
		fk_Color &			operator +=(const fk_Color &);

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
		fk_Color &			operator -=(const fk_Color &);

		//! 初期化関数1
		/*!
		 *	(R, G, B, A) = (0, 0, 0, 1) で初期化を行います。
		 */
		void		init(void);

		//! 初期化関数2
		/*!
		 *	色要素の設定を行います。同一引数型を持つ set() と同様に動作します。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A要素値
		 */
		void		init(float r, float g, float b, float a = 1.0f);

		//! 初期化関数3
		/*!
		 *	色要素の設定を行います。同一引数型を持つ set() と同様に動作します。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A要素値
		 */
		void		init(double r, double g, double b, double a = 1.0);

		//! 設定関数1
		/*!
		 *	色要素の設定を行います。同一引数型を持つ init() と同様に動作します。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A要素値
		 */
		void		set(float r, float g, float b, float a = 1.0f);

		//! 設定関数2
		/*!
		 *	色要素の設定を行います。同一引数型を持つ init() と同様に動作します。
		 *
		 *	\param[in] r R要素値
		 *	\param[in] g G要素値
		 *	\param[in] b B要素値
		 *	\param[in] a A要素値
		 */
		void		set(double r, double g, double b, double a = 1.0);

		//! HSV変換関数
		/*!
		 *	HSV色からの変換を行い、その結果を格納します。
		 *	透明度は 1.0 (完全な不透明) となります。
		 *
		 *	\param[in] h 色相要素値。単位は弧度法(ラジアン)です。
		 *	\param[in] s 彩度要素値。最小値は0、最大値は1です。
		 *	\param[in] v 明度要素値。最小値は0、最大値は1です。
		 */
		void		setHSV(double h, double s, double v);

		//! R要素設定関数
		/*!
		 *	\param[in] r R要素値
		 */
		void		setR(float r);

		//! G要素設定関数
		/*!
		 *	\param[in] g G要素値
		 */
		void		setG(float g);

		//! B要素設定関数
		/*!
		 *	\param[in] b B要素値
		 */
		void		setB(float b);

		//! A要素設定関数
		/*!
		 *	\param[in] a A要素値
		 */
		void		setA(float a);

		//! R要素設定関数
		/*!
		 *	\param[in] r R要素値
		 */
		void		setR(double r);

		//! G要素設定関数
		/*!
		 *	\param[in] g G要素値
		 */
		void		setG(double g);

		//! B要素設定関数
		/*!
		 *	\param[in] b B要素値
		 */
		void		setB(double b);

		//! A要素設定関数
		/*!
		 *	\param[in] a A要素値
		 */
		void		setA(double a);

		//! R要素参照関数
		/*!
		 *	\return R要素値
		 */
		float		getR(void) const;

		//! G要素参照関数
		/*!
		 *	\return G要素値
		 */
		float		getG(void) const;

		//! B要素参照関数
		/*!
		 *	\return B要素値
		 */
		float		getB(void) const;

		//! A要素参照関数
		/*!
		 *	\return A要素値
		 */
		float		getA(void) const;

		//! 

		//! 色成分範囲補正関数1
		/*!
		 *	入力した成分値に対し、0 未満である場合 0 を、
		 *	1 以上である場合 1 を、それ以外の場合は入力値自身を返します。
		 *
		 *	\param[in]	x	入力値
		 *
		 *	\return		補正値
		 */
		static double	clamp(double x);

		//! 色成分範囲補正関数2
		/*!
		 *	入力した成分値に対し、0 未満である場合 0 を、
		 *	1 以上である場合 1 を、それ以外の場合は入力値自身を返します。
		 *
		 *	\param[in]	x	入力値
		 *
		 *	\return		補正値
		 */
		static float	clamp(float x);

		//! \name 二項演算子
		//@{
		friend fk_Color	operator +(const fk_Color &, const fk_Color &);
		friend fk_Color	operator -(const fk_Color &, const fk_Color &);
		friend fk_Color	operator *(const fk_Color &, double);
		friend fk_Color	operator *(double, const fk_Color &);
		friend fk_Color	operator /(const fk_Color &, double);
		//@}
#ifndef FK_DOXYGEN_USER_PROCESS
		std::string		OutStr(void);
#endif
	};

	//! 色要素和二項演算子
	/*!
	 *	色値 C1 と C2 の和を得るには、以下のように記述します。
	 *	C1, C2, C3 はいずれも fk_Color 型の変数です。
	 *
	 *		C3 = C1 + C2;
	 *
	 *	なお演算の結果、成分値が 1 を超える場合はその成分を 1 とします。
	 */
	fk_Color	operator +(const fk_Color &, const fk_Color &);

	//! 色要素差二項演算子
	/*!
	 *	色値 C1 と C2 の差を得るには、以下のように記述します。
	 *	C1, C2, C3 はいずれも fk_Color 型の変数です。
	 *
	 *		C3 = C1 - C2;
	 *
	 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 にします。
	 */
	fk_Color	operator -(const fk_Color &, const fk_Color &);

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
	fk_Color	operator *(const fk_Color &, double);

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
	fk_Color	operator *(double, const fk_Color &);

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
	fk_Color	operator /(const fk_Color &, double);
}

#endif // __FK_COLOR_HEADER__
