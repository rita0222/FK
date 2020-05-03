#ifndef __FK_SCENE_HEADER__
#define __FK_SCENE_HEADER__

#include <FK/Fog.h>

namespace FK {

	// 影モードを表す列挙型
	enum class fk_ShadowMode {
		HARD = 0,	//!< ハードシャドウ
		SOFT_FAST,	//!< 速度重視ソフトシャドウ
		SOFT_NICE,	//!< 質重視ソフトシャドウ
		OFF,		//!< 影無効
		NUM			//!< 影モード種類数
	};
	
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

	class fk_Scene : public fk_Fog {

#ifndef FK_DOXYGEN_USER_PROCESS
		class fk_SceneData {
		public:
			fk_Color bgColor;
			bool blendStatus;
			fk_ShadowMode shadowMode;
			fk_Vector shadowVec;
			int shadowResolution;
			double shadowSize;
			double shadowDistance;
			double shadowVisibility;
			double shadowBias;

			fk_SceneData(void);
		};
#endif

	public:

		//! コンストラクタ
		fk_Scene(void);
		//! デストラクタ
		virtual ~fk_Scene();

		//! \name 背景色制御関数
		///@{

		//! 背景色設定関数1
		/*!
		 *	シーンの背景色を設定します。
		 *
		 *	\param[in]	col		背景色
		 *
		 *	\sa setBGColor(float, float, float), fk_Color, getBGColor()
		 */
		void setBGColor(fk_Color col);

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
		void setBGColor(float r, float g, float b);

		//! 背景色参照関数
		/*!
		 *	シーンの背景色を取得します。
		 *
		 *	\return		背景色
		 *
		 *	\sa fk_Color, setBGColor(fk_Color), setBGColor(float, float, float)
		 */
		fk_Color getBGColor(void);
		///@}

		//! \name 透過処理制御関数
		///@{

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
		 *		実行するハードウェアによっては、
		 *		シーンに登録した順番によって適切な透過処理がなされないことがあります。
		 *		カメラからみて手前側にある形状が透明(あるいは半透明)であり、
		 *		奥側にある形状が透けて見える状況を想定したとします。
		 *		このとき、手前側のモデルの方がシーンの登録順が先であった場合、
		 *		透けて見えるはずの奥側の形状が表示されないという現象が起こることがあります。
		 *		この場合、シーンの登録順を変更すれば奥側の形状が透けて見えるようになりますが、
		 *		カメラとの位置関係を常に監視し、
		 *		登録順を変動させなければならないという問題が生じます。
		 *
		 *	\param[in]	mode		true であれば有効、false であれば無効とします。
		 *
		 *	\sa fk_Material::setAlpha()
		 */
		void setBlendStatus(bool mode);

		//! 透過処理参照関数
		/*!
		 *	現在の透過処理状態を取得します。
		 *
		 *	\return		有効であれば true を、無効であれば false を返します。
		 *
		 *	\sa setBlendStatus()
		 */
		bool getBlendStatus(void);
		///@}

		//! \name 影制御関数
		///@{

		//! 影表示設定変更関数
		/*!
		 *	影表示の設定を行います。
		 *	以下の中から選択できます。
		 *	- fk_ShadowMode::HARD \n
		 *		ハードシャドウを描画します。
		 *		影表示を有効とする設定の中で描画は高速ですが、
		 *		影の内外部分の境界が明瞭なため、ディザーが目立ちます。
		 *		ディザーを改善するには、ソフトシャドウを利用するか、
		 *		シャドウマップ解像度を高く設定します。
		 *
		 *	- fk_ShadowMode::SOFT_FAST \n
		 *		速度重視設定のソフトシャドウを描画します。
		 *		ソフトシャドウは、影の内外部分の境界に対しエイリアシング処理を施したものであり、
		 *		多くの場合でハードシャドウよりも印象が良くなります。
		 *		ただし、ハードシャドウよりも実行速度は低下します。
		 *
		 *	- fk_ShadowMode::SOFT_NICE \n
		 *		質重視設定のソフトシャドウを描画します。
		 *		この設定は fk_ShadowMode::SOFT_FAST よりも高い質のソフトシャドウを生成しますが、
		 *		描画速度が低下する場合があります。
		 *
		 *	- fk_ShadowMode::OFF \n
		 *		影表示を無効とします。デフォルトはこの設定となります。
		 *		影表示が有効な場合よりもかなり描画速度が速くなります。
		 *
		 *	\param[in]	mode   	影表示モード
		 */
		void setShadowMode(fk_ShadowMode mode);

		//! 影表示設定参照関数
		/*!
		 *	影表示設定を参照します。
		 *
		 *	\return		影表示モード
		 */
		fk_ShadowMode getShadowMode(void);

		//! 影光線方向設定関数1
		/*!
		 *	影を生成する際の光の方向を設定します。
		 *
		 *	\param[in]	v	光の方向ベクトル
		 */
		void setShadowVec(const fk_Vector &v);

		//! 影光線方向設定関数2
		/*!
		 *	影を生成する際の光の方向を設定します。
		 *
		 *	\param[in]	x	光の方向ベクトル x 成分
		 *	\param[in]	y	光の方向ベクトル y 成分
		 *	\param[in]	z	光の方向ベクトル z 成分
		 */
		void setShadowVec(double x, double y, double z);

		//!	影光線方向取得関数
		/*!
		 *	影生成光線の方向を取得します。
		 *
		 *	\return		光の方向ベクトル
		 */
		fk_Vector getShadowVec(void);

		//!	シャドウマップ解像度設定関数
		/*!
		 *	影生成に使用するシャドウマップテクスチャの解像度を指定します。
		 *	この解像度は影表示の質と実行速度に大きく影響します。
		 *	解像度が高いと影のディザーは目立たなくなりますが、描画速度が低下し、
		 *	また実行環境によっては表示に異常をきたすことがあります。
		 *	解像度が低い場合は描画速度が向上しますが、
		 *	ディザーが発生しやすくなります。
		 *
		 *	この解像度は 16 以上の 2の累乗数であることが前提となっており、
		 *	その条件を満たさない場合は 15 以下の場合は 16、
		 *	それ以外の数値の場合はその数値未満の最大の2の累乗数が設定されます。
		 *
		 *	シャドウマップのディザーを目立たなくするには、
		 *	解像度だけでなく処理範囲も重要な要素です。
		 *	処理範囲については setShadowAreaSize(), setShadowDistance() を参照して下さい。
		 *
		 *	\param[in]	resolution	シャドウマップ解像度
		 *
		 *	\sa setShadowMode(), setShadowVec(), setShadowAreaSize(), setShadowDistance()
		 */
		void setShadowResolution(int resolution);

		//!	シャドウマップ解像度取得関数
		/*!
		 *	シャドウマップの解像度を取得します。
		 *
		 *	\return 解像度
		 *
		 *	\sa setShadowResolution()
		 */
		int getShadowResolution(void);

		//!	シャドウマップ領域設定関数
		/*!
		 *	影は空間中の直方体領域の内部に生成されますが、
		 *	この直方体のうち影光線ベクトルに垂直な辺の長さを設定します。
		 *	この値が大きいほど広い領域に対し影を生成しますが、
		 *	この値が大きくなるにつれて影の粒度も荒くなります。
		 *	シーンの状況に応じて適切な値を設定する必要があります。
		 *
		 *	\param[in]	size	影生成領域の大きさ
		 *
		 *	\sa setShadowVec(), setShadowResolution(), setshadowDistance()
		 */
		void setShadowAreaSize(double size);

		//!	シャドウマップ領域取得関数
		/*!
		 *	影生成直方体領域の大きさを取得します。
		 *
		 *	\return	影生成領域の大きさ
		 *
		 *	\sa setShadowAreaSize()
		 */
		double getShadowAreaSize(void);

		//!	シャドウマップ領域奥行き幅設定関数
		/*!
		 *	影は空間中の直方体領域の内部に生成されますが、
		 *	この直方体のうち影光線ベクトルに平行な辺の長さを設定します。
		 *	この値が大きいほど広い領域に対し影を生成しますが、
		 *	一方で大きいほど計算精度が悪くなり、描画の不具合を生じやすくなります。
		 *	通常は setShadowAreaSize() の設定値と同程度にしておくことが無難です。
		 *
		 *	\param[in]	distance	シャドウマップ領域奥行き幅
		 *
		 *	\sa setShadowVec(), setShadowResolution(), setShadowAreaSize()
		 */
		void setShadowDistance(double distance);

		//!	シャドウマップ領域奥行き幅取得関数
		/*!
		 *	影性生直方体領域の奥行き方向(影光線ベクトルに平行な方向)の幅を取得します。
		 *
		 *	\return 領域奥行き幅
		 *
		 *	\sa setShadowDistance()
		 */
		double getShadowDistance(void);

		//!	影濃度設定関数
		/*!
		 *	影の濃度を設定します。
		 *	この値が大きいほど影となる部分の輝度は低くなる、つまり影自体は濃くなってきます。
		 *	最小値は 0, 最大値は 1 で、0 のときは影効果は無効となります。
		 *	1 の場合、影となる領域は一切光が当たってない状況の輝度(色)となります。
		 *
		 *	\param[in]	value	影濃度。0 で最小、1 で最大で、大きいほど影が濃くなります。
		 */
		void setShadowVisibility(double value);

		//!	影濃度取得関数
		/*!
		 *	影の濃度を取得します。
		 *
		 *	\return	影濃度
		 */
		double getShadowVisibility(void);

		//! 影バイアス値設定関数
		/*!
		 *	影バイアス値を設定します。
		 *	FK での影生成処理は「シャドウマップ」という手法を用いています。
		 *	シャドウマップによる影生成では「シャドウアクネ」というモアレ模様が生じることがあります。
		 *	シャドウアクネを防ぐ方法としては、バイアス値を用いて補正を行いますが、
		 *	本関数はこのバイアス値を設定するものです。
		 *	バイアス値は正の微小値であり、デフォルトでは 0.0005 となっています。
		 *	この値が小さいとシャドウアクネが生じやすくなります。
		 *	しかし、この値が大きい場合は正常な影が生成できなくなります。
		 *	適切な値は様々な要因が関わってくるため、
		 *	シャドウアクネが生じた場合は適正な値を試行錯誤する必要があります。
		 *
		 *	\param[in]	bias		影バイアス値
		 */
		void setShadowBias(double bias);

		//!	影バイアス値取得関数
		/*!
		 *	影バイアス値を取得します。
		 *
		 *	\return	影バイアス値
		 */
		double getShadowBias(void);

		///@}

	private:
		std::unique_ptr<fk_SceneData> scene_data;
	};
}

#endif // !__FK_SCENE_HEADER__

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
