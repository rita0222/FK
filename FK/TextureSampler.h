#ifndef __FK_TEXTURE_SAMPLER_HEADER__
#define __FK_TEXTURE_SAMPLER_HEADER__

#include <FK/Texture.h>

// フレームバッファのサンプリングソースを表す列挙型
enum fk_SamplerSource {
	FK_TEXTURE_IMAGE,	//!< テクスチャ画像情報参照
	FK_COLOR_BUFFER,	//!< 画面色情報参照
	FK_DEPTH_BUFFER,	//!< 画面深度情報参照
};

//! シェーダー入出力テクスチャークラス
/*!
 *	このクラスは、シェーダープログラムでの参照テクスチャを管理する機能を提供します。
 *	GLSL プログラムにおいて、テクスチャデータは
 *	sampler2D という型の変数として扱います。
 *	このクラスを利用することで、
 *	フラグメントシェーダーの uniform 変数として参照テクスチャを
 *	C# プログラムとリンクすることができます。
 *
 *	最低限必要な手順は以下の通りとなります。
 *		-# 本クラスのインスタンスを生成する。
 *		-# fk_TextureSampler.SamplerSource プロパティを利用用途に応じて適切な値を設定する。
 *		-# fk_ShaderBinder 型変数の fk_ShaderBinder.Parameter プロパティに対し、
 *			fk_ShaderParameter::AttachTexture() メソッドによって連携設定を行う。
 *		-# フラグメントシェーダー内で uniform sampler2D 型変数を生成する。
 *
 *	\sa fk_ShaderBinder, fk_ShaderParameter, fk_MeshTexture
 */
class fk_TextureSampler : public fk_MeshTexture
{
public:

	//! コンストラクタ1
	/*!
	 *	参照テクスチャを生成します。
	 *	引数に何も入れなかった場合は、C++ 側で画像情報の設定や参照は行えません。
	 */
	fk_TextureSampler();

	//! コンストラクタ2
	/*!
	 *	参照テクスチャを生成します。
	 *	引数に fk_Image 型インスタンスを入力することにより、
	 *	その画像情報を GLSL 側に転送することや、
	 *	GLSL 側で生成した画像情報を C++ 側で参照することができます。
	 *
	 *	\param[in]	image
	 *		参照テクスチャ用画像データ
	 */
	fk_TextureSampler(fk_Image *image);

	//! デストラクタ
	~fk_TextureSampler();

	//! テクスチャ参照情報設定関数
	/*!
	 *	参照テクスチャが参照する情報を設定します。
	 *	設定できる種類は以下のとおりです。
	 *
	 *	- FK_TEXTURE_IMAGE: 
	 *		コンストラクタで設定した
	 *		fk_Image 型インスタンスに入っているデータを参照先とします。
	 *	- FK_COLOR_BUFFER: 
	 *		描画シーン全体の色値情報を参照先とします。
	 *	- FK_DEPTH_BUFFER: 
	 *		描画シーン全体の深度情報を参照先とします。
	 *	.
	 *	デフォルトは FK_TEXTURE_IMAGE に設定されています。
	 *
	 *	\param[in]	mode
	 *		テクスチャ参照情報の参照先
	 *
	 *	\sa getSamplerSource()
	 */
	void setSamplerSource(fk_SamplerSource mode);

	//! テクスチャ参照情報参照関数
	/*!
	 *	参照テクスチャが参照する情報を参照します。
	 *
	 *	\return		テクスチャ参照情報
	 */
	fk_SamplerSource getSamplerSource(void);
	
	//! 初期化メソッド
	/*!
	 *	現在設定されているテクスチャ情報を解除し、初期化を行います。
	 *
	 *	\sa setSamplerSource()
	 */
	void init(void);


#ifndef FK_DOXYGEN_USER_PROCESS
	bool BindTexture(bool forceLoad);
#endif

private:
	fk_SamplerSource	samplerSource;
	int					id;
	bool				loaded;
};


#endif

/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
