#ifndef __FK_SPHERE_HEADER__
#define __FK_SPHERE_HEADER__

#include <FK/IndexFace.h>

namespace FK {
	//! 球を生成、管理するクラス
	/*!
	 *	このクラスは、形状として球を制御する機能を提供しています。
	 *
	 *	実際には、球を近似する3角形面集合として表現されています。
	 *	3角形面の数は分割数を \f$ d \f$ とした場合 \f$ 8d(d-1) \f$ 枚となります。
	 *	分割数が高いほど球としての描画精度は高くなりますが、
	 *	面数も多くなるため描画速度が低下することになります。
	 *	特に多くのオブジェクトを同時に配置する場合は注意が必要です。
	 *
	 *	初期状態では、中心を原点とするように配置されます。
	 *	このクラスは fk_IndexFaceSet クラスの派生クラスであり、
	 *	生成後に fk_IndexFaceSet クラスの機能によって頂点を移動することが可能です。
	 *
	 *	\sa fk_IndexFaceSet, fk_Shape, fk_Model
	 */

	class fk_Sphere: public fk_IndexFaceSet {
	public:

		//! コンストラクタ
		/*!
		 *	引数として、分割数と半径を入力できます。分割数の最小値は 2 です。
		 *
		 *	\param[in]	div	分割数
		 *	\param[in]	rad	半径
		 */
		fk_Sphere(int div = 2, double rad = 1.0);

		//! デストラクタ
		virtual ~fk_Sphere();

		//! 分割数設定関数
		/*!
		 *	分割数を設定します。分割数の最小値は 2 です。
		 *
		 *	\param[in]	div	分割数
		 */
		void	setDivide(int div);

		//! 半径設定関数
		/*!
		 *	半径を設定します。
		 *
		 *	\param[in]	rad	半径
		 */
		void	setRadius(double rad);

		//! 拡大縮小関数
		/*!
		 *	球全体を与えられた倍率で拡大縮小します。
		 *
		 *	\param[in]	scale	倍率
		 */
		void	setScale(double scale);
	};
}

#endif // !__FK_SPHERE_HEADER__

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
