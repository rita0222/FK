﻿#ifndef __EW_MATERIAL_EXAMPLE_HEADER__
#define __EW_MATERIAL_EXAMPLE_HEADER__

#include <FK/Material.h>

namespace FK {
	/*! @file MatExample.h
	 *	デフォルトマテリアル
	 */

	/*!	デフォルトマテリアル変数の初期化
	 *
	 *	この関数は、最初から用意されているマテリアル用変数の初期化を行います。
	 *	これを行わないと、各変数に適切な値が入力されません。
	 *	この関数を呼んだあとに、各変数のマテリアル要素を設定しなおすことが可能です。
	 *	その後改めて初期化するには、再度この関数を呼んで下さい。
	 */
	void fk_InitMaterial(void);

	//! デフォルトマテリアル用名前空間
#ifndef FK_MATPALCODE
	namespace Material {
		extern fk_Material LightCyan;
		extern fk_Material AshGray;
		extern fk_Material BurntTitan;
		extern fk_Material IridescentGreen;
		extern fk_Material UltraMarine;
		extern fk_Material Ivory;
		extern fk_Material BambooGreen;
		extern fk_Material PearWhite;
		extern fk_Material Lilac;
		extern fk_Material HolidaySkyBlue;
		extern fk_Material DimYellow;
		extern fk_Material LavaRed;
		extern fk_Material GrassGreen;
		extern fk_Material Red;
		extern fk_Material Pink;
		extern fk_Material DarkRed;
		extern fk_Material Orange;
		extern fk_Material Flesh;
		extern fk_Material Brown;
		extern fk_Material Yellow;
		extern fk_Material Cream;
		extern fk_Material DarkYellow;
		extern fk_Material Green;
		extern fk_Material LightGreen;
		extern fk_Material Cyan;
		extern fk_Material PaleBlue;
		extern fk_Material Blue;
		extern fk_Material LightBlue;
		extern fk_Material DarkGreen;
		extern fk_Material DarkBlue;
		extern fk_Material DarkPurple;
		extern fk_Material Violet;
		extern fk_Material Purple;
		extern fk_Material LightViolet;
		extern fk_Material Coral;
		extern fk_Material White;
		extern fk_Material Gray1;
		extern fk_Material Gray2;
		extern fk_Material GlossBlack;
		extern fk_Material MatBlack;
		extern fk_Material TrueWhite;
		extern fk_Material WhiteLight;
		extern fk_Material Raw;
	}
#endif
}

#endif // !__EW_MATERIAL_EXAMPLE_HEADER__

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
