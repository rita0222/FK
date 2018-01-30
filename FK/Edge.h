#ifndef __FK_EDGE_HEADER__
#define __FK_EDGE_HEADER__

#include <FK/Topology.h>

namespace FK {

	class fk_Half;
	class fk_Curve;

	//! 稜線状態を表す列挙型
	enum fk_EdgeStatus {
		FK_NONE_EDGE,		//!< 位相の不整合
		FK_UNDEF_EDGE,		//!< 未定義稜線
		FK_HALFDEF_EDGE,	//!< 半定義稜線
		FK_BOTHDEF_EDGE		//!< 両定義稜線
	};

	//! 幾何曲線の種類を表す列挙型
	enum fk_CurveType {
		FK_BEZ_CURVE,		//!< Bezier 曲線
		FK_BSPL_CURVE		//!< B-Spline 曲線
	};

	//! ソリッドモデルの稜線位相を管理するクラス
	/*!
	 *	このクラスは、 fk_Solid によるソリッドモデルにおいて、
	 *	稜線位相に関する制御機能を提供します。
	 *	FK におけるソリッドモデルの構造については、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」の章を参照して下さい。
	 *
	 *	派生クラスのうち、ID 管理については fk_Topology,
	 *	個別マテリアル設定については fk_TopologyMaterial,
	 *	属性設定については fk_Attribute を参照して下さい。
	 *
	 *	稜線に対して、幾何形状として曲線データを設定することができます。
	 *	詳細は fk_Curve, fk_BezCurve, fk_BSplCurve を参照して下さい。
	 *	\sa fk_Solid, fk_Vertex, fk_Half, fk_Loop, fk_Topology,
	 *		fk_TopologyMaterial, fk_Attribute, fk_Curve, fk_BezCurve, fk_BSplCurve
	 */

	class fk_Edge : public fk_TopologyMaterial {

		friend class		fk_Operation;
		friend class		fk_DataBase;
		friend class		fk_FileInput;
		friend class		fk_FileOutput;
		friend class		fk_IFSetHandle;

	public:
		//! コンストラクタ
		fk_Edge(int);
		//! デストラクタ
		virtual ~fk_Edge();

		//! 初期化関数
		/*!
		 *	この関数は、稜線位相の初期化を行います。
		 *	通常、ユーザがこの関数を利用することはありません。
		 */
		void		Init(int);

		//! 左側半稜線取得関数
		/*!
		 *	この稜線に属する「左側」にあたる半稜線を取得します。
		 *
		 *	\return 「左側」にあたる半稜線を表す fk_Half 型インスタンスのアドレス。
		 */
		fk_Half *	getLeftHalf(void) const;

		//! 右側半稜線取得関数
		/*!
		 *	この稜線に属する「右側」にあたる半稜線を取得します。
		 *
		 *	\return 「右側」にあたる半稜線を表す fk_Half 型インスタンスのアドレス。
		 */
		fk_Half *	getRightHalf(void) const;

		//! 描画線幅取得関数
		/*!
		 *	稜線が描画される際の線幅を返します。
		 *
		 *	\return 描画線幅
		 */
		double		getDrawWidth(void) const;

		//! 描画線幅設定関数
		/*!
		 *	稜線を描画する際の線幅を設定します。
		 *	ここでの単位は「ピクセル」となります。
		 *	カメラからの距離に関係なく、同一の幅で描画されます。
		 *	また、設定した幅で実際に描画されるかどうかは
		 *	グラフィックスハードウェアの機能に依存します。
		 *
		 *	\param[in] width	描画線幅
		 */
		void		setDrawWidth(double width);

		//! 幾何曲線形状設定関数
		/*!
		 *	任意の自由曲線を幾何曲線として稜線に設定します。
		 * 	FK には既に Bezier 曲線 (fk_BezCurve) と
		 * 	B-Spline 曲線 (fk_BSplCurve) が標準で実装されていますが、
		 *	fk_Curve の条件を満たせばユーザによる自作クラスも設定することができます。
		 *	条件については fk_Curve を参照して下さい。
		 *
		 *	\param[in] curve	幾何曲線インスタンスのアドレス
		 */
		void		setCurveGeometry(fk_Curve *curve);

		//! 幾何曲線形状取得関数
		/*!
		 * 	稜線に設定されている自由曲線を取得します。
		 *
		 *	\return
		 *		自由曲線インスタンスのアドレス。
		 *		設定されていなかった場合は nullptr を返します。
		 */
		fk_Curve *	getCurveGeometry(void);

#ifndef FK_DOXYGEN_USER_PROCESS

		void		Print(void) const;
		bool		Check(void) const;
		bool		Compare(fk_Edge *) const;

#endif

	private:
		fk_Half		*leftHalf;
		fk_Half		*rightHalf;
		fk_Curve	*curv;

		double		width;

		fk_Half *  	SetLeftHalf(fk_Half *);
		fk_Half *	SetRightHalf(fk_Half *);

		void		SwapHalf(void);
	};
}
#endif // !__FK_EDGE_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
