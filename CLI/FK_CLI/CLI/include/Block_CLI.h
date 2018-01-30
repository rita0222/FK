// Block_CLI.h

#pragma once

#include <FK/Block.h>
#include "IndexFace_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	//! 直方体を生成、管理するクラス
	/*!
	 *	このクラスは、形状として直方体を制御する機能を提供します。
	 *	直方体は、物体の中心が原点に来るように配置されます。
	 *	従って、(x, y, z) という大きさで直方体を生成した場合、
	 *	各頂点の位置ベクトルは以下のようになります。
	 *	- (x/2, y/2, z/2)
	 *	- (-x/2, y/2, z/2)
	 *	- (-x/2, -y/2, z/2)
	 *	- (x/2, -y/2, z/2)
	 *	- (x/2, y/2, -z/2)
	 *	- (-x/2, y/2, -z/2)
	 *	- (-x/2, -y/2, -z/2)
	 *	- (x/2, -y/2, -z/2)
	 *
	 *	このクラスは、実質的には fk_IndexFaceSet クラスの派生クラスであり、
	 *	生成後に fk_IndexFaceSet クラスの機能によって頂点を移動することが可能です。
	 *
	 *	\sa fk_IndexFaceSet, fk_Shape, fk_Model
	 */
	public ref class fk_Block : fk_IndexFaceSet {
	internal:
		::fk_Block * GetP(void);

	public:
		//! コンストラクタ1
		/*!
		 *	全辺の長さが 1 である直方体(立方体)を生成します。
		 */
		fk_Block();

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Block(bool);
#endif

		//! コンストラクタ2
		/*!
		 *	引数として、各軸方向の幅を入力できます。
		 *
		 *	\param[in]	x	x方向の辺長
		 *	\param[in]	y	y方向の辺長
		 *	\param[in]	z	z方向の辺長
		 */
		fk_Block(double x, double y, double z);
		
		//! デストラクタ
		~fk_Block();

		//! ファイナライザ
		!fk_Block();

		//! 各辺長設定メソッド
		/*!
		 *	直方体の各軸方向の辺長を一括して設定します。
		 *
		 *	\param[in]	x	x方向の辺長
		 *	\param[in]	y	y方向の辺長
		 *	\param[in]	z	z方向の辺長
		 */
		void SetSize(double x, double y, double z);

		//! 個別辺長設定メソッド
		/*!
		 *	直方体の辺長を個別に設定します。
		 *
		 *	\param[in]	length	辺長
		 *	\param[in]	axis	軸方向。以下のいずれかを指定します。
		 *		- fk_Axis.X x方向
		 *		- fk_Axis.Y y方向
		 *		- fk_Axis.Z z方向
		 */
		void SetSize(double length, fk_Axis axis);

		//! 全体拡大縮小メソッド
		/*!
		 *	直方体全体を、指定された倍率で拡大・縮小します。
		 *
		 *	\param[in]	scale	倍率
		 */
		void SetScale(double scale);

		//! 軸方向拡大縮小メソッド
		/*!
		 *	直方体を、指定された軸方向についてのみ拡大・縮小します。
		 *
		 *	\param[in]	scale	倍率
		 *	\param[in]	axis	軸方向。以下のいずれかを指定します。
		 *		- fk_Axis.X x方向
		 *		- fk_Axis.Y y方向
		 *		- fk_Axis.Z z方向
		 */
		void SetScale(double scale, fk_Axis axis);

		//! 軸方向個別拡大縮小メソッド
		/*!
		 *	直方体を、各軸方向に対し個別の倍率で拡大・縮小します。
		 *
		 *	\param[in]	x	x方向の倍率
		 *	\param[in]	y	y方向の倍率
		 *	\param[in]	z	z方向の倍率
		 */
		void SetScale(double x, double y, double z);
	};
}

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
