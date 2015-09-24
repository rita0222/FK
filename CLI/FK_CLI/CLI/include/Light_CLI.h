// Light_CLI.h

#pragma once

#include <FK/Light.h>
#include "Shape_CLI.h"

namespace FK_CLI
{
	//! 光源タイプを表す列挙型
	public enum class fk_LightType {
		PARALLEL,	//!< 平行光源
		POINT,		//!< 点光源
		SPOT		//!< スポットライト
	};

	//! 光源を管理するクラス
	/*!
	 *	このクラスは、光源を制御する機能を提供します。
	 *	FK における光源の位置づけは、形状と同様に fk_Model に登録を行い、
	 *	位置や方向の制御は fk_Model の機能を用いるようになっています。
	 *	シーンへの登録についても、他の形状クラスと同様です。
	 *
	 *	表現できる光源は「平行光源」、「点光源」、「スポットライト」の3種類です。
	 *	一般的に、平行光源が最も処理が速く、
	 *	点光源、スポットライトの順で処理時間がかかるようになります。
	 *	また、シーン内の光源数は最高で 8 個までという制限があります。
	 *	一般的には、光源を多く設置すると各光源の光量自体は減少していくため、
	 *	シーン全体が明るくなるわけではありません。
	 *	光源の設置は最低限に留め、
	 *	マテリアル設定など別の方法で明るさを調整すべきです。
	 *
	 *	「平行光源」とは、空間中のあらゆる場所に対して同一方向から照らされる光源のことです。
	 *	最も扱いやすく、処理速度も速いため、
	 *	点光源やスポットライトを用いる積極的な理由がないのであれば平行光源を利用すべきです。
	 *
	 *	「点光源」は空間中のある1点から発光する光源のことです。
	 *	点光源は属性として減衰係数を保持しており、
	 *	距離によって光量が減衰していく効果が可能です。
	 *	詳細は SetAttenuation() を参照して下さい。
	 *	なお、この光源はあくまで面の発色輝度を計算するためのものであるため、
	 *	光源位置を注視するように設定しても光り輝く発色体た表示されるわけではありません。
	 *
	 *	「スポットライト」は特殊な点光源であり、光線方向に指向性があります。
	 *	特定のベクトルに近いほど光量が強く、方向がずれるほど光量が少なくなります。
	 *	詳しくは SpotExponent および SpotCutOff を参照して下さい。
	 *
	 *	\sa fk_Shape, fk_Model
	 */
	public ref class fk_Light : fk_Shape {
	internal:
		::fk_Light * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Light(bool argNewFlg);
#endif
		//! コンストラクタ
		fk_Light();

		//! デストラクタ
		~fk_Light();

		//! ファイナライザ
		!fk_Light();

		//! 光源タイププロパティ
		/*!
		 *	光源タイプの参照・設定を行います。
		 */
		property fk_LightType Type {
			void set(fk_LightType);
			fk_LightType get();
		}

		//! スポットライト効果範囲角度プロパティ
		/*!
		 *	スポットライト光源における、
		 *	光が放射される角度 \f$\theta\f$ の参照・設定を行います。
		 *	単位は弧度法(ラジアン)となります。
		 *
		 *	厳密には、光源位置を \f$ \mathbf{P} \f$、
		 *	光線方向を \f$\mathbf{L}\f$、
		 *	照射対象物体位置を \f$\mathbf{Q}\f$ としたとき、
		 *	以下の数式を満たすのであればスポットライトで照射されることになります。
		 *	\f[
		 *		\theta \geq \frac{(\mathbf{Q} - \mathbf{P})\cdot\mathbf{L}}
		 *		{|(\mathbf{Q} - \mathbf{P})\cdot\mathbf{L}|}
		 *	\f]
		 *	なお、デフォルトでは \f$\theta\f$は \f$\frac{\pi}{16}\f$ に設定されています。
		 *
		 *	\sa SpotExponent
		 */
		property double SpotCutOff {
			void set(double);
			double get();
		}
		
		//! スポットライト減衰指数設定関数
		/*!
		 *	スポットライト光源における、
		 *	光源方向からの減衰の度合いを指数 \f$\alpha\f$ として設定します。
		 *
		 *	具体的には、
		 *	光源位置を \f$ \mathbf{P} \f$、
		 *	光線方向を \f$\mathbf{L}\f$、
		 *	照射対象物体位置を \f$\mathbf{Q}\f$ としたとき、
		 *	減衰関数 \f$g(\alpha)\f$ は以下の数式によって表されます。
		 *	\f[
		 *		g(\alpha) = \max\left(
		 *		\frac{(\mathbf{Q} - \mathbf{P})\cdot\mathbf{L}}
		 *		{|(\mathbf{Q} - \mathbf{P})\cdot\mathbf{L}|}, \; 0\right)^\alpha
		 *	\f]
		 *	この関数は、光源から物体への方向ベクトル
		 *	\f$ (\mathbf{Q} - \mathbf{P}) \f$ が
		 *	光源の方向ベクトル \f$ \mathbf{L}\ \f$ と角度が大きいほど、
		 *	減衰関数 \f$ g(\alpha) \f$ の値は小さくなっていくことを意味します。
		 *	そして、\f$ \alpha \f$ は減衰の度合いを指数として指定することになり、
		 *	大きいほど減衰の度合いが強くなります。
		 *	\f$ \alpha \f$ が 0 であった場合、減衰は起こりません。
		 *	デフォルトでは \f$ \alpha \f$ は 0 に設定されています。
		 *
		 *	なお、もし \f$ g(\alpha) \f$ が 0 でなかったとしても、
		 *	SpotCutOff プロパティで設定した照射範囲から外れてしまっている場合は、
		 *	光源からの照射光量は 0 となります。つまり、本プロパティによる影響よりも
		 *	SpotCutOff プロパティによる照射範囲の方が優先されることになりますので、
		 *	設定には注意が必要です。
		 *	また、この減衰効果は SetAttenuation() 関数による減衰効果
		 *	\f$ f(d) \f$ と合わせて行われます。
		 *	つまり、実際の減衰量は \f$ f(d)\cdot g(\alpha) \f$ となります。
		 *
		 *	\sa SpotCutOff, SetAttenuation()
		 */
		property double SpotExponent {
			void set(double);
			double get();
		}

		//! 減衰係数設定関数1
		/*!
		 *	点光源やスポットライトにおける、
		 *	距離による減衰関数の係数を設定します。
		 * 	距離 \f$d\f$ による減衰関数 \f$ f(d) \f$ は以下の式で表されます。
		 *	\f[
		 *		f(d) = \frac{1}{k_l d + k_q d^2 + k_c}
		 *	\f]
		 *	ここで、\f$k_l\f$ は線形減衰係数、
		 *	\f$k_q\f$ は2次減衰係数、\f$k_c\f$ は一定減衰係数と呼ばれます。
		 *	デフォルトの状態は
		 *	\f$k_l, k_q\f$ が 0、\f$k_c\f$ が 1 に設定されています。
		 *	これは、距離による減衰が一切ない状態を意味します。
		 *
		 *	現実の物理特性は、点光源光量は距離の2乗に反比例するので、
		 *	2次減衰率係数が適していることになりますが、
		 *	実際の利用においては点光源の影響が著しく少なくなってしまい、
		 *	効果として望ましくない場合もあります。
		 *
		 *	\param[in]	k_l		線形減衰係数
		 *	\param[in]	k_q		2次減衰係数
		 *	\param[in]	k_c		一定減衰係数
		 *
		 *	\sa SpotExponent
		 */
		void SetAttenuation(double k_l, double k_q, double k_c);

		//! 減衰係数設定関数2
		/*!
		 *	点光源やスポットライトにおける、
		 *	距離による減衰関数の係数を設定します。
		 * 	距離 \f$d\f$ による減衰関数 \f$ f(d) \f$ は以下の式で表されます。
		 *	\f[
		 *		f(d) = \frac{1}{k_l d + k_q d^2 + 1}
		 *	\f]
		 *	ここで、\f$k_l\f$ は線形減衰係数、
		 *	\f$k_q\f$ は2次減衰係数と呼ばれます。
		 *	デフォルトの状態は
		 *	\f$k_l, k_q\f$ が 0 に設定されています。
		 *	これは、距離による減衰が一切ない状態を意味します。
		 *
		 *	現実の物理特性は、点光源光量は距離の2乗に反比例するので、
		 *	2次減衰率係数が適していることになりますが、
		 *	実際の利用においては点光源の影響が著しく少なくなってしまい、
		 *	効果として望ましくない場合もあります。
		 *
		 *	なお、本関数は SetAttenuation(double, double, double) において、
		 *	第3引数に 1.0 を入力した場合と同義となります。
		 *
		 *	\param[in]	k_l		線形減衰係数
		 *	\param[in]	k_q		2次減衰係数
		 *
		 *	\sa SpotExponent
		 */
		void SetAttenuation(double k_l, double k_q);

		//! 減衰係数参照関数
		/*!
		 *	距離による減衰関数の係数を参照します。
		 *
		 *	\param[in]	num
		 *		どの減衰係数を得るかを整数値で指定します。
		 *		-	0:			線形減衰係数を返します。
		 *		-	1:			2次減衰係数を返します。
		 *		-	2:			一定減衰係数を返します。
		 *		-	それ以外:	常に 0 を返します。
		 *
		 *	\return	指定された減衰係数の値
		 *
		 *	\sa SetAttenuation()
		 */
		double GetAttenuation(int num);
	};
}

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
