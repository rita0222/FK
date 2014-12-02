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
#ifndef __FK_SCENE_HEADER__
#define __FK_SCENE_HEADER__

#include <FK/DList.h>
#include <FK/Fog.h>

//! シーンを制御するクラス
/*!
 *	このクラスは、シーンを制御するための機能を提供します。
 *
 *	シーンは、複数のモデルとカメラからなる「場面」を意味します。
 *	利用者は、シーンに描画を想定した複数のモデルとカメラを示すモデルを登録します。
 *	このシーンを fk_Window クラスによるウィンドウに設定することによって、
 *	そのシーンに登録されたモデル群が実際に描画される仕組みになっています。
 *
 *	シーンは、別々のインスタンスとして複数存在することが可能です。
 *	異なるシーンを同時に生成しておき、
 *	実際にウィンドウに描画するシーンを動的に切り替えることができます。
 *	任意のモデルは、複数のシーンに同時に登録することができます。
 *
 *	シーンにモデルを登録するための機能は、
 *	実質的には fk_DisplayLink クラスに集約されています。
 *	fk_Scene クラスは fk_DisplayLink クラスの派生クラスとなっており、
 *	fk_DisplayLink クラスのメンバ関数を利用することが可能です。
 *	モデル登録についての機能は、 fk_DisplayLink クラスの説明を参照して下さい。
 *
 *	シーンは、通常のモデルとは別に霧に関する設定も可能です。
 *	霧に関する機能は、 fk_Fog クラスに集約されており、
 *	fk_Scene クラスは fk_Fog クラスの派生クラスとなっています。
 *	霧についての機能は、 fk_Fog クラスの説明を参照して下さい。
 *
 *	本クラス固有のメンバ関数は、背景色設定に関する機能と、
 *	透過処理に関するものとなっています
 *
 *	\sa fk_DisplayLink, fk_Fog, fk_Window
 */

class fk_Scene : public fk_DisplayLink, public fk_Fog {

 private:

	fk_Color		bgColor;
	bool			blendStatus;

 public:

	//! コンストラクタ
	fk_Scene(void);
	//! デストラクタ
	virtual ~fk_Scene();

	//! \name 背景色制御関数
	//@{

	//! 背景色設定関数1
	/*!
	 *	シーンの背景色を設定します。
	 *
	 *	\param[in]	col		背景色
	 *
	 *	\sa setBGColor(float, float, float), fk_Color, getBGColor()
	 */
	void			setBGColor(fk_Color col);

	//! 背景色設定関数2
	/*!
	 *	シーンの背景色を設定します。
	 *	各色要素は 0 から 1 までの値を取ります。
	 *	それ以外の値が与えられた場合、0 以下なら 0 に、1 以上なら 1 に丸められます。
	 *
	 *	\param[in]	r		背景色の赤要素
	 *	\param[in]	g		背景色の緑要素
	 *	\param[in]	b		背景色の青要素
	 *
	 *	\sa setBGColor(fk_Color), getBGColor()
	 */
	void			setBGColor(float r, float g, float b);

	//! 背景色参照関数
	/*!
	 *	シーンの背景色を取得します。
	 *
	 *	\return		背景色
	 *
	 *	\sa fk_Color, setBGColor(fk_Color), setBGColor(float, float, float)
	 */
	fk_Color		getBGColor(void);
	//@}

	//! \name 透過処理制御関数
	//@{

	//! 透過処理設定関数
	/*!
	 *	シーンに対し、透過処理を有効とするかどうかを設定します。
	 *	有効にした場合、シーン全体で透過処理がなされますが、
	 *	無効な場合と比較して描画速度が遅くなります。
	 *	これは、実際に透過する物体があるかどうかに関わらず、
	 *	速度が遅くなるということに注意して下さい。
	 *	デフォルトでは透過処理設定は無効となっています。
	 *
	 *	\note
	 *	実行するハードウェアによっては、
	 *	シーンに登録した順番によって適切な透過処理がなされないことがあります。
	 *	カメラからみて手前側にある形状が透明(あるいは半透明)であり、
	 *	奥側にある形状が透けて見える状況を想定したとします。
	 *	このとき、手前側のモデルの方がシーンの登録順が先であった場合、
	 *	透けて見えるはずの奥側の形状が表示されないという現象が起こることがあります。
	 *	この場合、シーンの登録順を変更すれば奥側の形状が透けて見えるようになりますが、
	 *	カメラとの位置関係を常に監視し、
	 *	登録順を変動させなければならないという問題が生じます。
	 *
	 *	\param[in]	mode		true であれば有効、false であれば無効とします。
	 *
	 *	\sa fk_Material::setAlpha()
	 */
	void			setBlendStatus(bool mode);

	//! 透過処理参照関数
	/*!
	 *	現在の透過処理状態を取得します。
	 *
	 *	\return		有効であれば true を、無効であれば false を返します。
	 *
	 *	\sa setBlendStatus()
	 */
	bool			getBlendStatus(void);
	//@}
};

#endif // !__FK_SCENE_HEADER__
