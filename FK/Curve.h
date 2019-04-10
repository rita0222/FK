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


#ifndef __FK_CURVE_HEADER__
#define __FK_CURVE_HEADER__

#include <FK/Vector.h>
#include <FK/Shape.h>

namespace FK {

	class fk_Window;

	//! 曲線用純粋仮想クラス
	/*!
	 *	このクラスは、自由曲線用の純粋仮想クラスです。
	 *	このクラスを継承することによって、
	 *	ユーザは任意の自由曲線形式を fk_Edge に追加することができます。
	 *	fk_BezCurve と fk_BSplCurve はこのクラスを継承しています。
	 *	自由曲線は、以下の条件を満たす必要があります。
	 *	- パラメータ空間が [0, 1] である。
	 *	- パラメータ空間中のあらゆるパラメータで曲線上の点を算出できる。
	 *	- パラメータ空間中のあらゆるパラメータで曲線上の微分ベクトルを算出できる。
	 *	- 曲線の始点と終点の位置ベクトルが、稜線 (fk_Edge) の始点、終点と一致している。
	 *
	 *	\sa fk_Edge, fk_BezCurve, fk_BSplCurve, fk_Surface
	 */
	class fk_Curve : public fk_Shape {

	protected:

		//! 修正告知用フラグ
		/*!
		 *	この変数は、派生クラスにおいて曲線形状を変更した状況となったとき、
		 *	値を true に変更して下さい。
		 *	描画データキャッシュが生成された時点で再び false に戻されます。
		 */
		bool				changeFlg;

	public:

		//! コンストラクタ
		fk_Curve(void);

		//! デストラクタ
		virtual ~fk_Curve();
 
		//! 曲線点位置ベクトル算出関数
		/*!
		 *	曲線上の点の位置ベクトルを算出する純粋仮想関数です。
		 *	派生クラスにおいて実際に実装する必要があります。
		 *
		 *	\param[in]	t	曲線パラメータ
		 *
		 *	\return		曲線点の位置ベクトル
		 */
		virtual fk_Vector	pos(double t) = 0;

		//! 曲線微分ベクトル算出関数
		/*!
		 *	曲線上の点の微分ベクトルを算出する純粋仮想関数です。
		 *	派生クラスにおいて実際に実装する必要があります。
		 *
		 *	\param[in]	t	曲線パラメータ
		 *
		 *	\return		曲線点の微分ベクトル
		 */
		virtual fk_Vector	diff(double t) = 0;

		//! 曲線キャッシュ分割数設定関数
		/*!
		 *	描画する際の曲線の分割数を設定します。
		 *	本関数は、派生クラスにおいて再定義する必要はありません。
		 *
		 *	\param[in]	div		分割数。
		 */
		void	setDiv(int div);
	
		//! 曲線キャッシュ分割数参照関数
		/*!
		 *	描画する際の曲線の分割数を参照します。
		 *	本関数は、派生クラスにおいて再定義する必要はありません。
		 *
		 *	\return		分割数
		 */
		int		getDiv(void);

#ifndef FK_DOXYGEN_USER_PROCESS
		void	makeCache(void);
#endif

	private:
		int							div;
		std::vector<fk_Vector>		posCache;
		std::vector<fk_Vector>		diffCache;

		std::vector<fk_Vector> *	getPosCache(void);
		std::vector<fk_Vector> * 	getDiffCache(void);
	};
}

#endif	// __FK_CURVE_HEADER__
