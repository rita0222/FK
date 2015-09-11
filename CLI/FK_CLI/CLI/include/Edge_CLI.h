// Half_CLI.h

#pragma once

#include <FK/Edge.h>
#include "Topology_CLI.h"

namespace FK_CLI
{
	ref class fk_Half;
	
	//! 稜線状態を表す列挙型
	public enum class fk_EdgeStatus {
		NONE_EDGE,		//!< 位相の不整合
		UNDEF_EDGE,		//!< 未定義稜線
		HALFDEF_EDGE,	//!< 半定義稜線
		BOTHDEF_EDGE	//!< 両定義稜線
	};

	//! ソリッドモデルの稜線位相を管理するクラス
	/*!
	 *	このクラスは、 fk_Solid によるソリッドモデルにおいて、
	 *	稜線位相に関する制御機能を提供します。
	 *	FK におけるソリッドモデルの構造については、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」の章を参照して下さい。
	 *
	 *	派生クラスのうち、ID 管理については fk_Topology,
	 *	個別マテリアル設定については fk_TopologyMaterial,
	 *	属性設定については fk_Attribute を参照して下さい。
	 *
	 *	\sa fk_Solid, fk_Vertex, fk_Half, fk_Loop, fk_Topology, fk_TopologyMaterial, fk_Attribute
	 */
	public ref class fk_Edge : fk_TopologyMaterial {
	internal:
		::fk_Edge * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Edge(bool argNewFlg);
		~fk_Edge();
		!fk_Edge();
#endif
		
		//! 左側半稜線プロパティ
		/*!
		 *	この稜線に属する「左側」にあたる半稜線を取得します。
		 */
		property fk_Half^ LeftHalf {
			fk_Half^ get();
		}

		//! 右側半稜線プロパティ
		/*!
		 *	この稜線に属する「右側」にあたる半稜線を取得します。
		 */
		property fk_Half^ RightHalf {
			fk_Half^ get();
		}

		//! 描画線幅プロパティ
		/*!
		 *	稜線を描画する際の線幅の設定や参照を行います。
		 *	ここでの単位は「ピクセル」となります。
		 *	カメラからの距離に関係なく、同一の幅で描画されます。
		 *	また、設定した幅で実際に描画されるかどうかは
		 *	グラフィックスハードウェアの機能に依存します。
		 */
		property double DrawWidth {
			double get();
			void set(double argW);
		}
	};
}
