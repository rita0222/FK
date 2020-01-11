/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_VERTEX_HEADER__
#define __FK_VERTEX_HEADER__

#include <FK/Base.h>
#include <FK/Vector.h>
#include <FK/Topology.h>

namespace FK {
	
	class fk_Half;
	class fk_Loop;

	//! ソリッドモデルの頂点位相を管理するクラス
	/*!
	 *	このクラスは、 fk_Solid によるソリッドモデルにおいて、
	 *	頂点位相に関する制御機能を提供します。
	 *	FK におけるソリッドモデルの構造については、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」の章を参照して下さい。
	 *
	 *	派生クラスのうち、ID 管理については fk_Topology,
	 *	属性設定については fk_Attribute を参照して下さい。
	 *
	 *	\sa fk_Solid, fk_Half, fk_Edge, fk_Loop, fk_Topology, fk_TopologyMaterial, fk_Attribute
	 */

	class fk_Vertex : public fk_Topology {

		friend class		fk_Operation;
		friend class		fk_DataBase;
		friend class		fk_IFSetHandle;

	public:
		//! コンストラクタ
		fk_Vertex(int = FK_UNDEFINED);
		//! デストラクタ
		virtual ~fk_Vertex();

		//! 位置ベクトル取得関数
		/*!
		 *	頂点位相の位置ベクトルを取得します。
		 *	この関数による位置ベクトルは、
		 *	fk_Model での配置や姿勢制御がまったく反映されないことに注意して下さい。
		 *
		 *	\return 位置ベクトル
		 */
		fk_Vector	getPosition(void) const;

		//! 接続半稜線取得関数
		/*!
		 *	この頂点を始点とする半稜線のうちの1つを取得します。
		 *	条件を満たす全ての半稜線を得たい場合は、
		 *	fk_ReferenceL2::getAllHOnV() 関数を用いて下さい。
		 *
		 *	\return
		 *		この頂点を始点とする半稜線を表すインスタンス。
		 *		対象となる半稜線が存在しない場合は nullptr を返します。
		 */
		fk_Half *	getOneHalf(void) const;

		//! 法線ベクトル取得関数
		/*!
		 *	頂点が2次元多様体上にある条件下のもと、適切な法線ベクトルを取得します。
		 *
		 *	\return 法線ベクトル。算出できなかった場合は零ベクトルを返します。
		 */
		fk_Vector	getNormal(void);

		//! 描画サイズ取得関数
		/*!
		 *	頂点が描画される際のサイズを返します。
		 *
		 *	\return 描画サイズ
		 */
		double		getDrawSize(void) const;

		//! 描画サイズ設定関数
		/*!
		 *	頂点を描画する際のサイズを設定します。
		 *	ここでの単位は「ピクセル」となります。
		 *	カメラからの距離に関係なく、同一の大きさで描画されます。
		 *	また、設定したサイズで実際に描画されるかどうかは
		 *	グラフィックスハードウェアの機能に依存します。
		 *
		 *	\param[in] size	描画サイズ
		 */
		void		setDrawSize(double size);

#ifndef FK_DOXYGEN_USER_PROCESS

		void		Init(fk_DataBase *, int);

		fk_Vector *	GetPositionP(void);
		fk_Vector *	GetNormalP(void);
		void		Print(void) const;
		bool		Check(void) const;
		bool		Compare(fk_Vertex *) const;
		void		PutFile_Text(FILE *);
		void		PutFile_Binary(FILE *);

#endif

	private:
		fk_Vector	position;
		fk_Vector	normal;
		bool		normCalcFlag;
		bool		normFailFlag;
		int 		oneHalf;
		double		size;

		void		CalcNormal(void);
		void		SetOneHalf(int);
		void		UndefNormal(void);
		void		SetPosition(fk_Vector);
		void		SetNormal(const fk_Vector &);
	};
}

#endif // !__FK_VERTEX_HEADER__


