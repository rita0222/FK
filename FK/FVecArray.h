#ifndef __FK_FVECARRAY_HEADER__
#define __FK_FVECARRAY_HEADER__

#include <FK/Vector.h>

namespace FK {

	class fk_Color;

	//! シェーダー内 attribute 変数用ベクトル管理クラス
	/*!
	 *	このクラスは、シェーダー内の attribute 変数として使用することを念頭においた、
	 *	ベクトルデータ格納用のクラスです。
	 *	このクラスは fk_Vector のような各種ベクトル演算は利用できませんが、
	 *	FK 内で作成した様々なベクトルデータを効率的に格納し、
	 *	シェーダー側に転送する機能を提供します。
	 *	なお、内部では全て float 型浮動小数点数として保存されます。
	 *
	 *	シェーダー内で attribute 変数として使用するには、大きく4つの処理が必要です。
	 *
	 *	-# クラス内の各種設定やデータ格納を行っておく。
	 *	-# fk_Shape::setShaderAttribute(std::string, int, std::vector<float> *) を用いて
	 *		シェーダー内の変数名を設定しておく。その際、第3引数の getP() を利用する。
	 *	-# fk_ShaderParameter::reserveAttribute() により、シェーダー内での変数名を設定する。
	 *	-# 格納データの変更があったら fk_Shape::modifyAttribute() を呼び出す。
	 *	.
	 *
	 *	\ sa fk_Vector, fk_HVector, fk_TexCoord, fk_Color, fk_Shape, fk_ShaderParameter
	 */

	class fk_FVecArray {

	public:
		//! コンストラクタ
		fk_FVecArray(void);

		//! デストラクタ
		~fk_FVecArray();

		//! 次元設定関数
		/*!
		 *	格納するベクトルデータの次元数を設定します。
		 *	次元は 2 から 4 まで設定が可能で、
		 *	シェーダープログラム内での型はそれぞれ vec2, vec3, vec4 となります。
		 *	デフォルトでの次元数は 3 に設定されています。
		 *
		 *	\param[in]	dim		次元数
		 */
		void setDim(int dim);

		//! 次元参照関数
		/*!
		 *	現在設定されている次元数を参照します。
		 *
		 *	\return 次元数
		 */
		int getDim(void);

		//! 要素数設定関数
		/*!
		 *	要素数を設定します。
		 * 	格納される float 型実数の個数は、ここで指定した要素数と次元の積となります。
		 *
		 *	\param[in]	size	要素数
		 *
		 *	\sa getSize(), clear(), setDim()
		 */
		void resize(int size);

		//! 要素数参照関数
		/*!
		 *	現在設定されている要素数を返します。
		 * 	格納されている float 型実数の個数は、この要素数と次元の積となります。
		 *
		 *	\return		要素数
		 *
		 *	\sa resize(), clear(), setDim()
		 */
		int getSize(void);

		//! データ消去関数
		/*!
		 *	現在格納されている要素を全て破棄し、要素数を 0 にします。
		 *	この関数により次元は変更されません。
		 *
		 *	\sa resize(), getSize(), setDim()
		 */
		void clear(void);

		//! fk_Vector 型ベクトル追加関数
		/*!
		 *	fk_Vector 型変数からデータを追加します。
		 *	なお、次元数が 2 だった場合は z 成分を破棄します。
		 *	また、次元数が 4 だった場合は、第 4 成分には 0 が設定されます。
		 *
		 *	\param[in]	v	追加するベクトル
		 *
		 *	\sa set(int, const fk_Vector &)
		 */
		void push(const fk_Vector &v);

		//! fk_FVector 型ベクトル追加関数
		/*!
		 *	fk_FVector 型変数からデータを追加します。
		 *	なお、次元数が 2 だった場合は z 成分を破棄します。
		 *	また、次元数が 4 だった場合は、第 4 成分には 0 が設定されます。
		 *
		 *	\param[in]	v	追加するベクトル
		 *
		 *	\sa set(int, const fk_FVector &)
		 */
		void push(const fk_FVector &v);

		//! fk_HVector 型ベクトル追加関数
		/*!
		 *	fk_HVector 型変数からデータを追加します。
		 *	なお、次元数が 2 だった場合は z,w 成分を、
		 *	次元数が 3 だった場合は w 成分を破棄します。
		 *
		 *	\param[in]	v	追加するベクトル
		 *
		 *	\sa set(int, const fk_HVector &)
		 */
		void push(const fk_HVector &v);

		//! fk_TexCoord 型ベクトル追加関数
		/*!
		 *	fk_TexCoord 型変数からデータを追加します。
		 *	なお、次元数が 3,4 だった場合は、それぞれの成分に 0 が設定されます。
		 *
		 *	\param[in]	v	追加するベクトル
		 *
		 *	\sa set(int, const fk_TexCoord &)
		 */
		void push(const fk_TexCoord &v);

		//! fk_Color 型色値追加関数
		/*!
		 *	fk_Color 型変数からデータを追加します。
		 *	なお、次元数が 2 だった場合は b,a 成分を、
		 *	次元数が 3 だった場合は a 成分を破棄します。
		 *
		 *	\param[in]	c	追加する色値
		 *
		 *	\sa set(int, const fk_Color &)
		 */
		void push(const fk_Color &c);

		//! ベクトル追加関数1
		/*!
		 *	ベクトルを (x, y, z, w) の順番で追加します。
		 *	次元数が引数の個数より多かった場合は超過した成分を破棄します。
		 *	次元数が引数の個数より少なかった場合、指定されなかった成分には 0 が設定されます。
		 *	第3,4引数は省略可能です。
		 *
		 *	\param[in]	x	第1成分
		 *	\param[in]	y	第2成分
		 *	\param[in]	z	第3成分
		 *	\param[in]	w	第4成分
		 */
		void push(double x, double y, double z = 0.0, double w = 0.0);

		//! ベクトル追加関数2
		/*!
		 *	ベクトルを (x, y, z, w) の順番で追加します。
		 *	次元数が引数の個数より多かった場合は超過した成分を破棄します。
		 *	次元数が引数の個数より少なかった場合、指定されなかった成分には 0 が設定されます。
		 *	第3,4引数は省略可能です。
		 *
		 *	\param[in]	x	第1成分
		 *	\param[in]	y	第2成分
		 *	\param[in]	z	第3成分
		 *	\param[in]	w	第4成分
		 */
		void push(float x, float y, float z = 0.0f, float w = 0.0f);

		//! fk_Vector 型ベクトル設定関数
		/*!
		 *	fk_Vector 型変数のデータを設定します。
		 *	もし id が現在の要素数以上となっていた場合は、
		 *	内部で自動的に resize(id+1) が呼び出されます。
		 *
		 *	なお、次元数が 2 だった場合は z 成分を破棄します。
		 *	また、次元数が 4 だった場合は、第 4 成分には 0 が設定されます。
		 *
		 *	\param[in]	id	要素 ID
		 *	\param[in]	v	追加するベクトル
		 *
		 *	\sa push(const fk_Vector &)
		 */
		bool set(int id, const fk_Vector &v);

		//! fk_FVector 型ベクトル設定関数
		/*!
		 *	fk_FVector 型変数のデータを設定します。
		 *	もし id が現在の要素数以上となっていた場合は、
		 *	内部で自動的に resize(id+1) が呼び出されます。
		 *
		 *	なお、次元数が 2 だった場合は z 成分を破棄します。
		 *	また、次元数が 4 だった場合は、第 4 成分には 0 が設定されます。
		 *
		 *	\param[in]	id	要素 ID
		 *	\param[in]	v	追加するベクトル
		 *
		 *	\sa push(const fk_FVector &)
		 */
		bool set(int id, const fk_FVector &v);

		//! fk_HVector 型ベクトル設定関数
		/*!
		 *	fk_HVector 型変数のデータを設定します。
		 *	もし id が現在の要素数以上となっていた場合は、
		 *	内部で自動的に resize(id+1) が呼び出されます。
		 *
		 *	なお、次元数が 2 だった場合は z,w 成分を、
		 *	次元数が 3 だった場合は w 成分を破棄します。
		 *
		 *	\param[in]	id	要素 ID
		 *	\param[in]	v	追加するベクトル
		 *
		 *	\sa push(const fk_HVector &)
		 */
		bool set(int id, const fk_HVector &v);

		//! fk_TexCoord 型ベクトル設定関数
		/*!
		 *	fk_TexCoord 型変数のデータを設定します。
		 *	もし id が現在の要素数以上となっていた場合は、
		 *	内部で自動的に resize(id+1) が呼び出されます。
		 *
		 *	なお、次元数が 3,4 だった場合は、それぞれの成分に 0 が設定されます。
		 *
		 *	\param[in]	id	要素 ID
		 *	\param[in]	v	追加するベクトル
		 *
		 *	\sa push(const fk_TexCoord &)
		 */
		bool set(int id, const fk_TexCoord &v);

		//! fk_Color 型ベクトル設定関数
		/*!
		 *	fk_Color 型変数のデータを設定します。
		 *	もし id が現在の要素数以上となっていた場合は、
		 *	内部で自動的に resize(id+1) が呼び出されます。
		 *
		 *	なお、次元数が 2 だった場合は b,a 成分を、
		 *	次元数が 3 だった場合は a 成分を破棄します。
		 *
		 *	\param[in]	id	要素 ID
		 *	\param[in]	c	追加する色値
		 *
		 *	\sa push(const fk_Color &)
		 */
		bool set(int id, const fk_Color &c);

		//! ベクトル設定関数1
		/*!
		 *	ベクトルを (x, y, z, w) の順番で設定します。
		 *	もし id が現在の要素数以上となっていた場合は、
		 *	内部で自動的に resize(id+1) が呼び出されます。
		 *
		 *	次元数が引数の個数より多かった場合は超過した成分を破棄します。
		 *	次元数が引数の個数より少なかった場合、指定されなかった成分には 0 が設定されます。
		 *	第3,4引数は省略可能です。
		 *
		 *	\param[in]	id	要素 ID
		 *	\param[in]	x	第1成分
		 *	\param[in]	y	第2成分
		 *	\param[in]	z	第3成分
		 *	\param[in]	w	第4成分
		 *
		 *	\sa push(double, double, double, double)
		 */
		bool set(int id, double x, double y, double z = 0.0, double w = 0.0);

		//! ベクトル設定関数2
		/*!
		 *	ベクトルを (x, y, z, w) の順番で設定します。
		 *	もし id が現在の要素数以上となっていた場合は、
		 *	内部で自動的に resize(id+1) が呼び出されます。
		 *
		 *	次元数が引数の個数より多かった場合は超過した成分を破棄します。
		 *	次元数が引数の個数より少なかった場合、指定されなかった成分には 0 が設定されます。
		 *	第3,4引数は省略可能です。
		 *
		 *	\param[in]	id	要素 ID
		 *	\param[in]	x	第1成分
		 *	\param[in]	y	第2成分
		 *	\param[in]	z	第3成分
		 *	\param[in]	w	第4成分
		 *
		 *	\sa push(float, float, float, float)
		 */
		bool set(int id, float x, float y, float z = 0.0f, float w = 0.0f);

		//! fk_Vector 型取得関数
		/*!
		 *	fk_Vector 型で格納データを取得します。
		 *
		 *	\param[in]	id	要素 ID
		 *
		 *	\return		要素データ
		 *
		 *	\sa set(int, const fk_Vector &)
		 */
		fk_Vector getV(int id);

		//! fk_FVector 型取得関数
		/*!
		 *	fk_FVector 型で格納データを取得します。
		 *
		 *	\param[in]	id	要素 ID
		 *
		 *	\return		要素データ
		 *
		 *	\sa set(int, const fk_FVector &)
		 */
		fk_FVector getF(int id);

		//! fk_HVector 型取得関数
		/*!
		 *	fk_HVector 型で格納データを取得します。
		 *
		 *	\param[in]	id	要素 ID
		 *
		 *	\return		要素データ
		 *
		 *	\sa set(int, const fk_HVector &)
		 */
		fk_HVector getHV(int id);

		//! fk_TexCoord 型取得関数
		/*!
		 *	fk_TexCoord 型で格納データを取得します。
		 *
		 *	\param[in]	id	要素 ID
		 *
		 *	\return		要素データ
		 *
		 *	\sa set(int, const fk_TexCoord &)
		 */
		fk_TexCoord getT(int id);

		//! fk_Color 型取得関数
		/*!
		 *	fk_Color 型で格納データを取得します。
		 *
		 *	\param[in]	id	要素 ID
		 *
		 *	\return		要素データ
		 *
		 *	\sa set(int, const fk_Color &)
		 */
		fk_Color getC(int id);

		//! データアドレス取得関数
		/*!
		 *	データ格納データのアドレスを取得します。
		 *	本関数は、 fk_Shape::setShaderAttribute(std::string, int, std::vector<float> *)
		 *	の第3引数に入力することを想定しています。
		 *
		 *	\return		アドレス
		 */
		std::vector<float> * getP(void);

		//! 全体変更状態取得関数
		/*!
		 *	以前に reset() が呼ばれてからのデータ変更有無を取得します。
		 *
		 *	\return		変更があった場合 true を、なかった場合 false を返します。
		 *
		 *	\sa isModify(int)
		 */
		bool	isModify(void);

		//! 個別要素変更状態取得関数
		/*!
		 *	以前に reset() が呼ばれてから、個別要素データ変更の有無を取得します。
		 *
		 *	\param[in]	id	要素ID
		 *	
		 *	\return		変更があった場合 true を、なかった場合 false を返します。
		 *
		 *	\sa isModify()
		 */
		bool	isModify(int id);

		//! 変更状態初期化関数
		/*!
		 *	isModify(), isModify(int) による変更有無情報を初期化します。
		 *
		 *	\sa isModify(), isModify(int)
		 */
		void	reset(void);

	private:
		int					dim;
		int					size;
		bool				allFlg;
		std::vector<float>	array;
		std::vector<char>	elemFlg;
	};
}

#endif /* !__FK_FVECARRAY_HEADER__ */

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
