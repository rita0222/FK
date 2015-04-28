// Fog_CLI.h

#pragma once

#include <FK/Fog.h>
#include "DList_CLI.h"

namespace FK_CLI
{
	//! 霧効果の減衰関数を表す列挙型
	public enum class fk_FogMode {
		LINEAR_FOG,		//!< 線形式
		EXP_FOG,		//!< 指数式
		EXP2_FOG,		//!< 指数(2乗)式
		NONE_FOG		//!< 無効
	};

	//! 霧効果のオプションを表す列挙型
	public enum class fk_FogOption {
		FASTEST_FOG,	//!< 速度優先
		NICEST_FOG,		//!< 質優先
		NOOPTION_FOG	//!< 指定なし
	};

	//! シーン中の霧効果を制御するクラス
	/*!
	 *	このクラスは、シーン内の霧効果を制御する機能を提供します。
	 *	実際の利用時には、インスタンスは本クラスのものではなく
	 *	派生クラスの fk_Scene によるものを利用することになります。
	 *
	 *	\sa fk_Scene, fk_DisplayLink, fk_Color
 */
	public ref class fk_Fog : fk_DisplayLink {
	internal:
		::fk_Fog * GetP(void);

	public:

#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Fog(bool argNewFlg);
		~fk_Fog();
		!fk_Fog();
#endif
		
		//! 減衰関数プロパティ
		/*!
		 *	霧効果の減衰関数の設定や参照を行います。設定できる関数の種類は以下のとおりです。
		 *	各数式中の \f$ z \f$ はカメラからの距離を意味します。
		 *
		 *	- fk_FogMode.LINEAR_FOG \n
		 *		減衰関数として線形式を設定します。具体的には以下の数式を用います。
		 *		\f[
		 *			\frac{E-z}{E-S}
		 *		\f]
		 *		式中の \f$ E, S \f$ は
		 *		fk_Fog::FogLinearEnd, fk_Fog::FogLinearStart プロパティで設定します。
		 *
		 *	- fk_FogMode.EXP_FOG \n
		 *		減衰関数として指数式を設定します。具体的には以下の数式を用います。
		 *		\f[
		 *			e^{-dz}
		 *		\f]
		 *		式中の \f$ d \f$ は fk_Fog::FogDensity プロパティで設定します。
		 *
		 *	- fk_FogMode.EXP2_FOG \n
		 *		減衰関数として指数(2乗)式を設定します。具体的には以下の数式を用います。
		 *		\f[
		 *			e^{-\left(dz\right)^2}
		 *		\f]
		 *		式中の \f$ d \f$ は fk_Fog::FogDensity プロパティで設定します。
		 *
		 *	- fk_FogMode.NONE_FOG \n
		 *		この値を設定した場合、霧効果を無効にします。
		 *	.
		 *	デフォルトでは fk_FogMode.NONE_FOG が設定されています。
		 */
		property fk_FogMode FogMode {
			void set(fk_FogMode);
			fk_FogMode get();
		}

		//! 霧効果処理オプションプロパティ
		/*!
		 *	霧効果処理に対するオプションの設定や参照を行います。
		 *	実際の効果の程度についてはハードウェアやOSに依存します。
		 *	設定できるオプションの種類は以下のとおりです。
		 *
		 *	- fk_FogOption.FASTEST_FOG \n
		 *		処理の際に、実行速度を優先します。
		 *	- fk_FogOption.FK_NICEST_FOG \n
		 *		処理の際に、品質を優先します。
		 *	- fk_FogOption.NOOPTION_FOG \n
		 *		特に優先度を設定しません。
		 *	.
		 *	デフォルトでは fk_FogOption.NOOPTION_FOG が設定されています。
		 */
		property fk_FogOption FogOption {
			void set(fk_FogOption);
			fk_FogOption get();
		}

		//! 指数式係数プロパティ
		/*!
		 *	減衰関数として指数式か指数(2乗)式を選択した場合の、
		 *	指数部の係数 d の設定や参照を行います。
		 *	数式の詳細は fk_Fog::FogMode を参照して下さい。
		 */
		property double FogDensity {
			void set(double);
			double get(void);
		}

		//! 線形式係数開始距離プロパティ
		/*!
		 *	減衰関数として線形式を選択した場合の、
		 *	開始距離の設定や参照を行います。
		 *	意味的には、霧効果が始まる最低距離になります。
		 *	数式の詳細は fk_Fog::FogMode を参照して下さい。
		 */
		property double FogLinearStart {
			void set(double);
			double get(void);
		}

		//! 線形式係数完全距離プロパティ
		/*!
		 *	減衰関数として線形式を選択した場合の、
		 *	完全距離の設定や参照を行います。
		 *	意味的には、霧によって物体が完全見えなくなる距離になります。
		 *	数式の詳細は fk_Fog::FogMode を参照して下さい。
		 */
		property double FogLinearEnd {
			void set(double);
			double get(void);
		}

		//! 霧色プロパティ
		/*!
		 *	霧の色の設定や参照を行います。通常はシーンの背景色と同色とします。
		 *
		 *	\sa fk_Scene::BGColor
		 */
		property fk_Color^ FogColor {
			void set(fk_Color^);
			fk_Color^ get();
		}
	};
}
