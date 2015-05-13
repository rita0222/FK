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
#ifndef __FK_FOG_HEADER__
#define __FK_FOG_HEADER__

#include <FK/Material.h>

//! 霧効果の減衰関数を表す列挙型
enum fk_FogMode {
	FK_LINEAR_FOG,		//!< 線形式
	FK_EXP_FOG,			//!< 指数式
	FK_EXP2_FOG,		//!< 指数(2乗)式
	FK_NONE_FOG			//!< 無効
};

//! 霧効果のオプションを表す列挙型
enum fk_FogOption {
	FK_FASTEST_FOG,		//!< 速度優先
	FK_NICEST_FOG,		//!< 質優先
	FK_NOOPTION_FOG		//!< 指定なし
};

//! シーン中の霧効果を制御するクラス
/*!
 *	このクラスは、シーン内の霧効果を制御する機能を提供します。
 *	実際の利用時には、インスタンスは本クラスのものではなく
 *	派生クラスの fk_Scene によるものを利用することになります。
 *
 *	\sa fk_Scene, fk_DisplayLink, fk_Color
 */

class fk_Fog {

	friend class	fk_Window;
	friend class	fk_GraphicsEngine;

 private:

	fk_FogMode		fogMode;
	fk_FogOption	fogOption;
	double			fogStart, fogEnd, fogDensity;
	bool			fogChangeStatus;
	fk_Color		fogColor;

	bool			GetFogChangeStatus(void);
 public:

	//! コンストラクタ
	fk_Fog(void);
	//! デストラクタ
	virtual ~fk_Fog();

	//! 減衰関数設定関数
	/*!
	 *	霧効果の減衰関数を設定します。設定できる関数の種類は以下のとおりです。
	 *	各数式中の \f$ z \f$ はカメラからの距離を意味します。
	 *
	 *	- FK_LINEAR_FOG \n
	 *		減衰関数として線形式を設定します。具体的には以下の数式を用います。
	 *		\f[
	 *			\frac{E-z}{E-S}
	 *		\f]
	 *		式中の \f$ E, S \f$ は setFogLinearMap() で設定します。
	 *	- FK_EXP_FOG \n
	 *		減衰関数として指数式を設定します。具体的には以下の数式を用います。
	 *		\f[
	 *			e^{-dz}
	 *		\f]
	 *		式中の \f$ d \f$ は setFogDensity() で設定します。
	 *	- FK_EXP2_FOG \n
	 *		減衰関数として指数(2乗)式を設定します。具体的には以下の数式を用います。
	 *		\f[
	 *			e^{-\left(dz\right)^2}
	 *		\f]
	 *		式中の \f$ d \f$ は setFogDensity() で設定します。
	 *	- FK_NONE_FOG \n
	 *		この値を設定した場合、霧効果を無効にします。
	 *	.
	 *	デフォルトでは FK_NONE_FOG が設定されています。
	 *
	 *	\param[in] mode		減衰関数を表す値
	 */
	void			setFogMode(const fk_FogMode mode);

	//! 霧効果処理オプション設定関数
	/*!
	 *	霧効果処理に対するオプションを設定します。
	 *	実際の効果の程度についてはハードウェアやOSに依存します。
	 *	設定できるオプションの種類は以下のとおりです。
	 *
	 *	- FK_FASTEST_FOG \n
	 *		処理の際に、実行速度を優先します。
	 *	- FK_NICEST_FOG \n
	 *		処理の際に、品質を優先します。
	 *	- FK_NOOPTION_FOG \n
	 *		特に優先度を設定しません。
	 *	.
	 *	デフォルトでは FK_NOOPTION_FOG が設定されています。
	 *
	 *	\param[in] opt	オプションを表す値
	 */
	void			setFogOption(const fk_FogOption opt);

	//! 指数式係数設定関数
	/*!
	 *	減衰関数として指数式か指数(2乗)式を選択した場合の、
	 *	指数部の係数 d を設定します。
	 *	数式の詳細は setFogMode() を参照して下さい。
	 *
	 *	\param[in] d	指数部係数
	 */
	void			setFogDensity(const double d);

	//! 線形式係数設定関数
	/*!
	 *	減衰関数として線形式を選択した場合の、
	 *	係数 S, E を設定します。
	 *	意味的には、霧効果が始まる最低距離が S、
	 *	霧によって完全に物体が見えなくなる距離を E とすることになります。
	 *	数式の詳細は setFogMode() を参照して下さい。
	 *
	 *	\param[in]	S	霧効果開始距離
	 *	\param[in]	E	霧効果完全距離
	 */
	void			setFogLinearMap(const double S, const double E);

	//! 霧色設定関数1
	/*!
	 *	霧の色を設定します。通常はシーンの背景色と同色とします。
	 *
	 *	\param[in] col	霧色
	 *
	 *	\sa fk_Scene::setBGColor()
	 */
	void			setFogColor(const fk_Color col);

	//! 霧色設定関数2
	/*!
	 *	霧の色を設定します。通常はシーンの背景色と同色とします。
	 *	色設定に関しての詳細は fk_Color を参照して下さい。
	 *
	 *	\param[in] r	霧色のR(赤)要素値
	 *	\param[in] g	霧色のG(緑)要素値
	 *	\param[in] b	霧色のB(青)要素値
	 *	\param[in] a	霧色のA(透過)要素値
	 *
	 *	\sa fk_Scene::setBGColor()
	 */
	void			setFogColor(const float r, const float g,
								const float b, const float a);

	//! 霧色設定関数3
	/*!
	 *	霧の色を設定します。通常はシーンの背景色と同色とします。
	 *	色設定に関しての詳細は fk_Color を参照して下さい。
	 *
	 *	\param[in] r	霧色のR(赤)要素値
	 *	\param[in] g	霧色のG(緑)要素値
	 *	\param[in] b	霧色のB(青)要素値
	 *	\param[in] a	霧色のA(透過)要素値
	 *
	 *	\sa fk_Scene::setBGColor()
	 */
	void			setFogColor(const double r, const double g,
								const double b, const double a);

	//! 減衰関数取得関数
	/*!
	 *	霧効果の減衰関数として何が選択されているのかを取得します。
	 *	関数の種類および詳細は setFogMode() を参照して下さい。
	 *
	 *	\return 減衰関数を表す値
	 */
	fk_FogMode		getFogMode(void) const;

	//! 霧効果処理オプション取得関数
	/*!
	 *	霧効果処理に対して現在設定されているオプションを取得します。
	 *	オプションの種類および詳細は setFogOption() を参照して下さい。
	 *
	 *	\return オプションを表す値
	 */
	fk_FogOption	getFogOption(void) const;

	//! 指数式係数取得関数
	/*!
	 *	減衰関数として指数式か指数(2乗)式を選択した場合の、
	 *	指数部の係数 d を参照します。
	 *	数式の詳細は setFogMode() を参照して下さい。
	 *
	 *	\return 指数部係数
	 */
	double			getFogDensity(void) const;

	//! 線形式係数取得関数1
	/*!
	 *	減衰関数として線形式を選択した場合の、
	 *	係数 S を参照します。
	 *	数式の詳細は setFogMode() を参照して下さい。
	 *
	 *	\return 霧効果開始距離
	 */
	double			getFogLinearStart(void) const;

	//! 線形式係数取得関数1
	/*!
	 *	減衰関数として線形式を選択した場合の、
	 *	係数 E を参照します。
	 *	数式の詳細は setFogMode() を参照して下さい。
	 *
	 *	\return 霧効果完全距離
	 */
	double			getFogLinearEnd(void) const;

	//! 霧色取得関数
	/*!
	 *	現在設定されている霧の色を参照します。
	 *
	 *	\return 霧色
	 */
	fk_Color		getFogColor(void) const;
};

#endif // !__FK_FOG_HEADER__
