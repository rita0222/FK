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


#ifndef __FK_DRAWMODE_HEADER__
#define __FK_DRAWMODE_HEADER__

namespace FK {

	//! 描画モードを表す列挙型
	enum class fk_Draw : unsigned int {
		NONE			= 0,					//!< 何も表示しない
		POINT 			= 1 << 1,				//!< 点描画
		LINE 			= 1 << 2,				//!< 線描画
		FACE 			= 1 << 3,				//!< 面描画 (表面のみ)
		BACK_FACE		= ((1 << 4) | FACE),	//!< 裏面描画
		FRONTBACK_FACE	= ((1 << 5) | FACE),	//!< 表裏面描画
		TEXTURE			= 1 << 6,				//!< テクスチャー描画
		GEOM_LINE		= 1 << 7,				//!< 曲線・曲面グリッド描画
		GEOM_POINT		= 1 << 8,				//!< 曲線・曲面点描画
		GEOM_FACE		= 1 << 9,				//!< 曲面描画
	};

	fk_Draw operator | (fk_Draw argL, fk_Draw argR);
	fk_Draw operator & (fk_Draw argL, fk_Draw argR);
	fk_Draw operator ^ (fk_Draw argL, fk_Draw argR);
/*
	const fk_DrawMode FK_NONEMODE = fk_DrawMode::NONE;
	const fk_DrawMode FK_POINTMODE = fk_DrawMode::POINT;
	const fk_DrawMode FK_LINEMODE = fk_DrawMode::LINE;
	const fk_DrawMode FK_POLYMODE = fk_DrawMode::FACE;
	const fk_DrawMode FK_BACK_POLYMODE = fk_DrawMode::BACK_FACE;
	const fk_DrawMode FK_FRONTBACK_POLYMODE = fk_DrawMode::FRONTBACK_FACE;
	const fk_DrawMode FK_TEXTUREMODE = fk_DrawMode::TEXTURE;
*/
}

#endif // !__FK_BOUNDARY_HEADER__
