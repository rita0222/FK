#ifndef __FK_DISPLAYLIST_HEADER__
#define __FK_DISPLAYLIST_HEADER__

#include <FK/Projection.h>
#include <FK/Model.h>
#include <list>

//! 立体視出力を制御する際に用いる列挙型
enum fk_StereoChannel {
	FK_STEREO_LEFT,			//!< 左目側
	FK_STEREO_RIGHT			//!< 右目側
};

//!	ディスプレイリストを制御するクラス
/*!
 *	このクラスは、ディスプレイリストを制御する機能を提供します。
 *	ディスプレイリストとは、シーン中に表示するためのモデルを管理する仕組みです。
 *	実際の利用時には、インスタンスは本クラスのものではなく
 *	派生クラスの fk_Scene によるものを利用することになります。
 *
 *	ディスプレイリストに登録する要素は、以下のようなものがあります。
 *		- 通常モデル:
 *			3次元空間に表示するためのモデルです。
 *		- オーバーレイモデル:
 *			オーバーレイモデルとして登録したモデルは、
 *			カメラからの前後に関係なく常に全体が表示されます。
 *			オーバーレイモデルが複数登録されている場合は、
 *			後に登録されたものほど前面に表示されます。
 *		- カメラ:
 *			シーンのカメラに当たるモデルです。
 *			同時に登録できるモデルは1つだけですが、
 *			どの時点でもモデルを変更することができます。
 *		- 投影設定:
 *			シーンを表示する際の投影設定です。
 *			詳細は fk_Perspective, fk_Frustum, fk_Ortho の
 *			各マニュアルを参照して下さい。
 *
 *	\sa fk_Scene, fk_Fog, fk_Model, fk_Perspective, , fk_Frustum, fk_Ortho
 */

class fk_DisplayLink : public fk_BaseObject {

	friend class		fk_Window;
	friend class		fk_GraphicsEngine;

 private:
	std::list<fk_Model *>	modelList;
	std::list<fk_Model *>	lightList;
	std::list<fk_Model *>	overlayList;
	int						displayID;
	fk_Model				localCamera;
	fk_Model				*camera;
	fk_ProjectBase			*proj;
	fk_Perspective			perspective;
	fk_Frustum				frustum;
	fk_Ortho				ortho;
	int						projStatus;

	fk_Model				*stereoCamera[2];
	fk_ProjectBase			*stereoProj[2];
	fk_Perspective			stereoPers[2];
	fk_Frustum				stereoFrus[2];
	fk_Ortho				stereoOrtho[2];
	bool					stereoOverlayMode;

	std::list<fk_Model *> *	GetModelList(void);
	std::list<fk_Model *> *	GetLightList(void);
	std::list<fk_Model *> *	GetOverlayList(void);
	int						GetID(void) const;
	int						GetProjChangeStatus(void) const;

 public:

	//! コンストラクタ
	fk_DisplayLink(void);

	//! デストラクタ
	virtual ~fk_DisplayLink();

	//!	初期化関数
	/*!
	 *	ディスプレイリストに登録されていた全ての情報を解除します。
	 *	解除する対象は通常表示モデル、モデルオーバーレイモデル、
	 *	カメラ、投影設定です。
	 */
	void					clearDisplay(void);

	//! 通常モデル登録関数
	/*!
	 *	通常モデルをディスプレイリストに登録します。
	 *
	 *	\param[in] model	登録モデルのアドレス
	 */
	void					entryModel(fk_Model *model);

	//! 通常モデル解除関数
	/*!
	 *	ディスプレイリストに登録されている通常モデルに対し、
	 *	登録を解除します。
	 *
	 *	\param[in] model	解除モデルのアドレス
	 */
	void					removeModel(fk_Model *model);

	//! 通常モデル全解除関数
	/*!
	 *	ディスプレイリストに登録されている全ての通常モデルに対し、
	 *	登録を解除します。
	 */
	void					clearModel(void);

	//! オーバーレイモデル登録関数
	/*!
	 *	オーバーレイモデルをディスプレイリストに登録します。
	 *	オーバーレイモデルは、後に登録したものほど前面に表示されるようになります。
	 *	もし既に登録されているモデルを再度登録した場合は、
	 *	一度解除したのちに改めて登録しなおすことと同義となります。
	 *
	 *	\param[in] model	登録モデルのアドレス
	 */
	void					entryOverlayModel(fk_Model *model);

	//! オーバーレイモデル解除関数
	/*!
	 *	ディスプレイリストに登録されているオーバーレイモデルに対し、
	 *	登録を解除します。
	 *
	 *	\param[in] model	解除モデルのアドレス
	 */
	void					removeOverlayModel(fk_Model *model);

	//! オーバーレイモデル全解除関数
	/*!
	 *	ディスプレイリストに登録されている全てのオーバーレイモデルに対し、
	 *	登録を解除します。
	 */
	void					clearOverlayModel(void);

	//! カメラモデル登録関数
	/*!
	 * 	カメラモデルをディスプレイリストに登録します。
	 *
	 *	\param[in] model	カメラモデルのアドレス
	 */
	void					entryCamera(fk_Model *model);

	//! カメラモデル取得関数
	/*!
	 *	ディスプレイリストに登録されているカメラモデルの
	 *	アドレスを取得します。
	 *
	 *	\return	カメラモデルのアドレス
	 */
	const fk_Model *		getCamera(void) const;

	//! 投影設定関数
	/*!
	 *	シーンで表示する際の投影設定を設定します。
	 *
	 *	\param[in] proj		投影設定のアドレス
	 *
	 *	\sa fk_Perspective, fk_Ortho
	 */
	void					setProjection(fk_ProjectBase *proj);

	//! 投影設定取得関数
	/*!
	 *	シーンに登録されている投影設定のアドレスを取得します。
	 *
	 *	\return 投影設定のアドレス
	 */
	const fk_ProjectBase *	getProjection(void) const;

	//! \name 立体視モード制御関数
	//@{
	//! 立体視用カメラモデル登録関数
	/*!
	 *	立体視モードで使用するカメラモデルをディスプレイリストに登録します。
	 *	立体視モードは fk_Window::setOGLStereoMode()で設定します。
	 *
	 *	\param[in] channel
	 *		左右どちらの視点を登録するかを指定します。
	 *		設定値については fk_StereoChannel を参照してください。
	 *	\param[in] model	カメラモデルのアドレス
	 *
	 *	\sa fk_StereoChannel, fk_Window::setOGLStereoMode()
	 */
	void					entryStereoCamera(fk_StereoChannel channel, fk_Model *model);

	//! 立体視用射影設定関数
	/*!
	 *	立体視モードで使用する射影設定を設定します。
	 *	立体視モードは fk_Window::setOGLStereoMode()で設定します。
	 *
	 *	\param[in] channel
	 *		左右どちらの視点の設定を登録するかを指定します。
	 *		fk_StereoChannel を参照してください。
	 *	\param[in] proj		射影設定のアドレス
	 *
	 *	\sa fk_StereoChannel, fk_Window::setOGLStereoMode()
	 */
	void					setStereoProjection(fk_StereoChannel channel, fk_ProjectBase *proj);

	//! 立体視用カメラモデル取得関数
	/*!
	 *	立体視モードで使用するカメラモデルのアドレスを取得します。
	 *	立体視モードは fk_Window::setGLStereoMode()で設定します。
	 *
	 *	\param[in] channel
	 *		左右どちらの視点を取得するかを指定します。
	 *		fk_StereoChannel を参照してください。
	 *
	 *	\return
	 *		カメラモデルのアドレス。
	 *		立体視用の設定が未設定の場合、通常のカメラモデルのアドレスを返します。
	 *
	 *	\sa fk_StereoChannel, entryStereoCamera()
	 */
	const fk_Model *		getStereoCamera(fk_StereoChannel channel);

	//! 立体視用射影設定取得関数
	/*!
	 *	立体視モードで使用する射影設定を取得します。
	 *
	 *	\param[in] channel
	 *		左右どちらの視点の設定を取得するかを指定します。
	 *		fk_StereoChannel を参照してください。
	 *
	 *	\return
	 *		射影設定のアドレス。
	 *		立体視用の設定が未設定の場合、通常の射影設定のアドレスを返します。
	 *
	 *	\sa fk_StereoChannel, getStereoProjection()
	 */
	const fk_ProjectBase *	getStereoProjection(fk_StereoChannel channel);

	//! 立体視用設定情報初期化関数
	/*!
	 *	立体視モードで使用する設定情報を初期化します。
	 *
	 *	\sa entryStereoCamera(), setStereoProjection(), getStereoCamera(), getStereoProjection()
	 */
	void					clearStereo(void);

	//! 立体視モード時のオーバーレイ描画モード設定関数
	/*!
	 *	立体視モード時のオーバーレイ描画モデルに対する動作を設定します。
	 *	一般的なゲームアプリケーションでは、3DCG をレンダリングした画面上に
	 *	2D の画像や文字などを情報として表示(いわゆる HUD 表示)しますが、
	 *	立体視を有効にした場合はそれらの表示にも視差が適用されます。
	 *	この動作は状況によっては望ましくない場合もあります。
	 *	この関数によって、オーバーレイ描画を行うモデルに対して視差を適用するか、
	 *	しないかを選択することができます。
	 *	HUD 表示はオーバーレイ描画によって実現することが多いため、
	 *	多くの場合はこの関数による設定で十分制御が可能となるはずです。
	 *	デフォルトではオーバーレイ描画モデルにも視差を適用する設定(true)になっています。
	 *
	 *	\param[in]	mode
	 *		true だった場合、オーバーレイ描画モデルの視差を有効にします。
	 *		false だった場合、オーバーレイ描画モデルの視差を無効にします。
	 *
	 *	\sa fk_Window::setOGLStereoMode(), getStereoOverlayMode()
	 */
	void	setStereoOverlayMode(bool mode);

	//! 立体視モード時のオーバーレイ描画モード取得関数
	/*!
	 *	立体視モード時のオーバーレイ描画モデルに対する動作モードを取得します。
	 *
	 *	\return
	 *		true だった場合、オーバーレイ描画モデルの視差が有効になっています。
	 *		false だった場合、オーバーレイ描画モデルの視差が無効になっています。
	 *
	 *	\sa fk_DisplayLink, setOGLStereoOverlayMode()
	 */
	bool	getStereoOverlayMode(void);
	//@}

#ifndef FK_DOXYGEN_USER_PROCESS
	void	SetFinalizeMode(void);
#endif

};

#endif // !__FK_DISPLAYLIST_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
