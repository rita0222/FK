#pragma once

#include <FK/Scene.h>
#include "Fog_CLI.h"

namespace FK_CLI
{
	// 影表示モードを表す列挙型
	public enum class fk_ShadowMode {
		HARD = 0,	//!< ハードシャドウ
		SOFT_FAST,	//!< 速度重視ソフトシャドウ
		SOFT_NICE,	//!< 質重視ソフトシャドウ
		OFF			//!< 影無効
	};
		
	//! シーンを制御するクラス
	/*!
	 *	このクラスは、シーンを制御するための機能を提供します。
	 *
	 *	シーンは、複数のモデルとカメラからなる「場面」を意味します。
	 *	利用者は、シーンに描画を想定した複数のモデルとカメラを示すモデルを登録します。
	 *	このシーンを fk_AppWindow クラス等によるウィンドウに設定することによって、
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
	 *	fk_DisplayLink クラスのメソッドを利用することが可能です。
	 *	モデル登録についての機能は、 fk_DisplayLink クラスの説明を参照して下さい。
	 *
	 *	シーンは、通常のモデルとは別に霧に関する設定も可能です。
	 *	霧に関する機能は、 fk_Fog クラスに集約されており、
	 *	fk_Scene クラスは fk_Fog クラスの派生クラスとなっています。
	 *	霧についての機能は、 fk_Fog クラスの説明を参照して下さい。
	 *
	 *	本クラス固有のプロパティは、背景色設定に関する機能と、
	 *	透過処理に関するものとなっています
	 *
	 *	\sa fk_DisplayLink, fk_Fog, fk_AppWindow
	 */
	public ref class fk_Scene : fk_Fog {
	internal:

		::FK::fk_Scene * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Scene(bool argNewFlg);
#endif

		//! コンストラクタ
		fk_Scene();

		//! デストラクタ
		~fk_Scene();

		//! ファイナライザ
		!fk_Scene();

		//! 背景色プロパティ
		/*!
		 *	シーンの背景色を設定します。
		 */
		property fk_Color^ BGColor {
			void set(fk_Color^);
			fk_Color^ get();
		}

		//! 透過処理プロパティ
		/*!
		 *	シーンに対し、透過処理を有効とするかどうかの参照・設定を行います。
		 *	true であれば有効、false であれば無効とします。
		 *
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
		 *	\sa fk_Material::Alpha
		 */
		property bool BlendStatus {
			void set(bool);
			bool get();
		}

		//! 影表示設定プロパティ
		/*!
		 *	影表示の設定や参照を行います。
		 *	設定は，以下の中から選択できます。
		 *
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
		 *	\sa ShadowVec, ShadowResolution, ShadowAreaSize, ShadowDistance, ShadowVisibility
		 */
		property fk_ShadowMode ShadowMode {
			void set(fk_ShadowMode);
			fk_ShadowMode get();
		}

		//! 影光線方向設定プロパティ
		/*!
		 *	影を生成する際の光の方向の設定や参照を行います。
		 *
		 *	\sa ShadowMode, ShadowResolution, ShadowAreaSize, ShadowDistance, ShadowVisibility
		 */
		property fk_Vector^ ShadowVec {
			void set(fk_Vector^);
			fk_Vector^ get();
		}

		//!	シャドウマップ解像度プロパティ
		/*!
		 *	影生成に使用するシャドウマップテクスチャの解像度の設定や参照を行います。
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
		 *	処理範囲については fk_Scene::ShadowAreaSize, fk_Scene::ShadowDistance を参照して下さい。
		 *
		 *	\sa ShadowMode, ShadowVec, ShadowAreaSize, ShadowDistance, ShadowVisibility
		 */
		property int ShadowResolution {
			void set(int);
			int get(void);
		}

		//!	シャドウマップ領域設定プロパティ
		/*!
		 *	影は空間中の直方体領域の内部に生成されますが、
		 *	この直方体のうち影光線ベクトルに垂直な辺の長さの設定や参照を行います。
		 *	この値が大きいほど広い領域に対し影を生成しますが、
		 *	この値が大きくなるにつれて影の粒度も荒くなります。
		 *	シーンの状況に応じて適切な値を設定する必要があります。
		 *
		 *	\sa ShadowMode, ShadowVec, ShadowResolution, ShadowDistance, ShadowVisibility
		 */
		property double ShadowAreaSize {
			void set(double);
			double get(void);
		}

		//!	シャドウマップ領域奥行き幅設定プロパティ
		/*!
		 *	影は空間中の直方体領域の内部に生成されますが、
		 *	この直方体のうち影光線ベクトルに平行な辺の長さの設定や参照を行います。
		 *	この値が大きいほど広い領域に対し影を生成しますが、
		 *	一方で大きいほど計算精度が悪くなり、描画の不具合を生じやすくなります。
		 *	通常は fk_Scene::ShadowAreaSize の設定値と同程度にしておくことが無難です。
		 *
		 *	\sa ShadowMode, ShadowVec, ShadowResolution, ShadowAreaSize, ShadowVisibility
		 */
		property double ShadowDistance {
			void set(double);
			double get(void);
		}

		//!	影濃度設定プロパティ
		/*!
		 *	影の濃度の設定や参照を行います。
		 *	この値が大きいほど影となる部分の輝度は低くなる、つまり影自体は濃くなってきます。
		 *	最小値は 0, 最大値は 1 で、0 のときは影効果は無効となります。
		 *	1 の場合、影となる領域は一切光が当たってない状況の輝度(色)となります。
		 *
		 *	\sa ShadowMode, ShadowVec, ShadowResolution, ShadowAreaSize, ShadowDistance
		 */
		property double ShadowVisibility {
			void set(double);
			double get(void);
		}

		//! 影バイアス値設定関数
		/*!
		 *	影バイアス値の設定や参照を行います．
		 *	FK での影生成処理は「シャドウマップ」という手法を用いています。
		 *	シャドウマップによる影生成では「シャドウアクネ」というモアレ模様が生じることがあります。
		 *	シャドウアクネを防ぐ方法としては、バイアス値を用いて補正を行いますが、
		 *	本関数はこのバイアス値を設定するものです。
		 *	バイアス値は正の微小値であり、デフォルトでは 0.0005 となっています。
		 *	この値が小さいとシャドウアクネが生じやすくなります。
		 *	しかし、この値が大きい場合は正常な影が生成できなくなります。
		 *	適切な値は様々な要因が関わってくるため、
		 *	シャドウアクネが生じた場合は適正な値を試行錯誤する必要があります。
		 */
		property double ShadowBias {
			void set(double);
			double get(void);
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
