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
#ifndef __FK_HALF_HEADER__
#define __FK_HALF_HEADER__

#include <FK/Topology.h>

namespace FK {
	class fk_Edge;
	class fk_Loop;
	class fk_Vertex;

	//! ソリッドモデルの半稜線位相を管理するクラス
	/*!
	 *	このクラスは、 fk_Solid によるソリッドモデルにおいて、
	 *	半稜線位相に関する制御機能を提供します。
	 *	FK におけるソリッドモデルの構造については、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」の章を参照して下さい。
	 *
	 *	派生クラスのうち、ID 管理については fk_Topology,
	 *	個別マテリアル設定については fk_TopologyMaterial,
	 *	属性設定については fk_Attribute を参照して下さい。
	 *
	 *	\sa fk_Solid, fk_Vertex, fk_Edge, fk_Loop, fk_Topology, fk_TopologyMaterial, fk_Attribute
	 */

	class fk_Half : public fk_Topology {

		friend class		fk_Operation;
		friend class		fk_DataBase;
		friend class		fk_IFSetHandle;
		friend class		fk_SolidBase;

	public:
		//! コンストラクタ
		fk_Half(int);
		//! デストラクタ
		virtual ~fk_Half();

		// コピーコンストラクタ
		fk_Half(const fk_Half &);

		//! 初期化関数
		/*!
		 *	この関数は、半稜線位相の初期化を行います。
		 *	通常、ユーザがこの関数を利用することはありません。
		 */
		void		Init(int);

		//! 始点頂点位相取得関数
		/*!
		 *	この半稜線が始点としている頂点の ID を取得します。
		 *
		 *	\return 始点頂点位相 ID
		 */
		int		getVertex(void) const;

		//! 後半稜線位相取得関数
		/*!
		 *	半稜線の接続関係において、この半稜線の後にあたる半稜線 ID を取得します。
		 *
		 *	\return 後の半稜線位相を表す ID
		 */
		int		getNextHalf(void) const;

		//! 前半稜線位相取得関数
		/*!
		 *	半稜線の接続関係において、この半稜線の前にあたる半稜線 ID を取得します。
		 *
		 *	\return 前の半稜線位相を表す ID
		 */
		int		getPrevHalf(void) const;

		//! 稜線位相取得関数
		/*!
		 *	この半稜線が属している稜線位相 ID を取得します。
		 *
		 *	\return 稜線位相を表す ID
		 */
		int		getParentEdge(void) const;

		//! ループ位相取得関数
		/*!
		 *	この半稜線が属しているループ位相 ID を取得します。
		 *
		 *	\return
		 *		ループ位相を表す ID。
		 *		半稜線がループに属していない場合は FK_UNDEFINED を返します。
		 */
		int		getParentLoop(void) const;

		//! 左側判定関数
		/*!
		 *	この半稜線が、属している稜線の「左側」かどうかを判定する関数です。
		 *
		 *	\return 「左側」である場合 true を、「右側」である場合 false を返します。
		 */
		bool		isLeft(void) const;

		//! 右側判定関数
		/*!
		 *	この半稜線が、属している稜線の「右側」かどうかを判定する関数です。
		 *
		 *	\return 「右側」である場合 true を、「左側」である場合 false を返します。
		 */
		bool		isRight(void) const;

#ifndef FK_DOXYGEN_USER_PROCESS
		void		Print(void) const;
		bool		Check(void) const;
		bool		Compare(fk_Half *) const;
#endif

	private:
		int			vertex;
		int			nextHalf;
		int			prevHalf;
		int			parentEdge;
		int			parentLoop;

		int			SetVertex(fk_Vertex *);
		int			SetNextHalf(fk_Half *);
		int			SetPrevHalf(fk_Half *);
		int			SetParentEdge(fk_Edge *);
		int			SetParentLoop(fk_Loop *);
	};
}
#endif // !__FK_HALF_HEADER__


