﻿#pragma once

#include <FK/FrameBuffer.h>
#include "Image_CLI.h"

namespace FK_CLI
{
	// フレームバッファーのサンプリングソースを表す列挙型
	public enum class fk_SamplerSource {
		COLOR,	//!< 画面色情報参照
		DEPTH	//!< 画面深度情報参照
	};

	//! フレームバッファー制御クラス
	/*!
	 *	このクラスは、フレームバッファーを制御する機能を提供します。
	 *	フレームバッファーとはシーン描画時の色情報と深度情報のことであり、
	 *	それぞれを「カラーバッファー」、「深度バッファー」と呼称します。
	 *	シーン描画は通常は fk_AppWindow によってモニター上に描画されますが、
	 *	fk_Scene インスタンスを fk_Renderer に設定することにより、
	 *	描画情報をモニター上ではなくフレームバッファーに格納することができます。
	 *	そのフレームバッファー情報を示すのが本クラスです。
	 *	この情報を fk_Texture::FrameBuffer に渡すことで、
	 *	フレームバッファーをアニメーションテクスチャとして利用できます。
	 *
	 *	\sa fk_Scene, fk_Renderer, fk_Texture
	 */

	public ref class fk_FrameBuffer {
    internal:
        ::FK::fk_FrameBuffer* pFrame;
        ::FK::fk_FrameBuffer* GetP(void);

	public:

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_FrameBuffer(::FK::fk_FrameBuffer *);
		~fk_FrameBuffer();
        !fk_FrameBuffer();
#endif
		//! バッファー種類プロパティ
		/*!
		 *	フレームバッファーの種類を参照します。
		 *	種類は以下のとおりです。
		 *
		 *	- fk_SamplerSource::COLOR:
		 *		描画シーン全体の色値情報を参照先とします。
		 *	- fk_SamplerSource::DEPTH:
		 *		描画シーン全体の深度情報を参照先とします。
		 */

        property fk_SamplerSource Source {
            fk_SamplerSource get();
        }

		//! バッファーサイズプロパティ
		/*!
		 *	現在設定されているバッファーのサイズを取得します。
		 */
        property fk_Dimension^ BufferSize {
            fk_Dimension^ get();
        }
	};
}

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
