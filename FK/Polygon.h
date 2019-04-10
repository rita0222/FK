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
#ifndef __FK_POLYGON_HEADER__
#define __FK_POLYGON_HEADER__

#include <FK/Solid.h>

namespace FK {
	//! 多角形を生成、管理するクラス
	/*!
	 *	このクラスは、形状として多角形を制御する機能を提供します。
	 *	このクラスによる形状は、多角形の内部も描画します。
	 *	もし辺のみを描画したい場合は fk_Closedline クラスを利用して下さい。
	 *
	 *	描画される面は、基本的には多角形の頂点順番が向かって
	 *	反時計回りになっている側になります。
	 *	両面を描画したい場合は fk_Model の setDrawMode() 関数を参照して下さい。
	 *	また、本クラスの多角形の角数は 3 以上であれば制限はありませんが、
	 *	平面でなかった場合に意図している形状と描画形状が異なる場合があります。
	 *	\sa fk_Solid, fk_Polyline, fk_Closedline
	 */

	class fk_Polygon: public fk_Solid {
	public:

		//! コンストラクタ
		/*!
		 *	引数はシステム内部制御のために利用されるものです。
		 *	ユーザは引数を省略して定義を行って下さい。
		 */
		fk_Polygon(std::vector<fk_Vector> *array = nullptr,
				   fk_ObjectType = FK_POLYGON);

		//! デストラクタ
		virtual ~fk_Polygon();

		//! 頂点追加関数
		/*!
		 *	頂点を追加します。
		 *	\param[in] pos 追加頂点の位置ベクトル
		 */
		void	pushVertex(fk_Vector pos);

		//! 頂点位置設定関数
		/*!
		 *	頂点の位置を設定します。
		 *	対象となる頂点がまだ存在していなかった場合、
		 *	角数を (id+1) まで増加させます。
		 *	\param[in] ID 頂点ID
		 *	\param[in] pos 頂点位置ベクトル
		 */
		void	setVertex(int ID, fk_Vector pos);

		//! 頂点位置設定関数
		/*!
		 *	頂点全部を、指定した配列に入れ替えます。
		 *	\param[in] size 角数
		 *	\param[in] array 頂点位置ベクトル配列の先頭アドレス
		 */
		void	setVertex(int size, fk_Vector *array);

		//! 頂点位置設定関数
		/*!
		 *	頂点全部を、指定した配列に入れ替えます。
		 *	\param[in] array vectorによる頂点位置ベクトル配列のアドレス
		 */
		void	setVertex(std::vector<fk_Vector> *array);
	};
}
#endif // !__FK_POLYGON_HEADER__


