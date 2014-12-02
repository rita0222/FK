/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#ifndef __EW_MATERIAL_EXAMPLE_HEADER__
#define __EW_MATERIAL_EXAMPLE_HEADER__

#include <FK/Material.h>

#ifdef FK_MATPALCODE
#define FK_EXTERN
#else
#define FK_EXTERN extern
#endif // FK_MATPALCODE

/*! @file MatExample.h
	デフォルトマテリアル
*/

/*! デフォルトマテリアル変数の初期化
	この関数は、最初から用意されているマテリアル用変数の初期化を行います。
	これを行わないと、各変数に適切な値が入力されません。
	この関数を呼んだあとに、各変数のマテリアル要素を設定しなおすことが可能です。
	その後改めて初期化するには、再度この関数を呼んで下さい。
	@return なし
*/
void fk_InitMaterial(void);

FK_EXTERN fk_Material LightCyan;
FK_EXTERN fk_Material AshGray;
FK_EXTERN fk_Material BurntTitan;
FK_EXTERN fk_Material IridescentGreen;
FK_EXTERN fk_Material UltraMarine;
FK_EXTERN fk_Material Ivory;
FK_EXTERN fk_Material BambooGreen;
FK_EXTERN fk_Material PearWhite;
FK_EXTERN fk_Material Lilac;
FK_EXTERN fk_Material HolidaySkyBlue;
FK_EXTERN fk_Material DimYellow;
FK_EXTERN fk_Material LavaRed;
FK_EXTERN fk_Material GrassGreen;
FK_EXTERN fk_Material Red;
FK_EXTERN fk_Material Pink;
FK_EXTERN fk_Material DarkRed;
FK_EXTERN fk_Material Orange;
FK_EXTERN fk_Material Flesh;
FK_EXTERN fk_Material Brown;
FK_EXTERN fk_Material Yellow;
FK_EXTERN fk_Material Cream;
FK_EXTERN fk_Material DarkYellow;
FK_EXTERN fk_Material Green;
FK_EXTERN fk_Material LightGreen;
FK_EXTERN fk_Material Cyan;
FK_EXTERN fk_Material PaleBlue;
FK_EXTERN fk_Material Blue;
FK_EXTERN fk_Material LightBlue;
FK_EXTERN fk_Material DarkGreen;
FK_EXTERN fk_Material DarkBlue;
FK_EXTERN fk_Material DarkPurple;
FK_EXTERN fk_Material Violet;
FK_EXTERN fk_Material Purple;
FK_EXTERN fk_Material LightViolet;
FK_EXTERN fk_Material Coral;
FK_EXTERN fk_Material White;
FK_EXTERN fk_Material Gray1;
FK_EXTERN fk_Material Gray2;
FK_EXTERN fk_Material GlossBlack;
FK_EXTERN fk_Material MatBlack;

#undef FK_EXTERN

#endif // !__EW_MATERIAL_EXAMPLE_HEADER__
