// Vertex_CLI.h

#pragma once

#include <FK/Vertex.h>
#include "Topology_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI {

	ref class fk_Half;

	//! ソリッドモデルの頂点位相を管理するクラス
	/*!
	 *	このクラスは、 fk_Solid によるソリッドモデルにおいて、
	 *	頂点位相に関する制御機能を提供します。
	 *	FK におけるソリッドモデルの構造については、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」の章を参照して下さい。
	 *
	 *	派生クラスのうち、ID 管理については fk_Topology,
	 *	個別マテリアル設定については fk_TopologyMaterial,
	 *	属性設定については fk_Attribute を参照して下さい。
	 *
	 *	\sa fk_Solid, fk_Half, fk_Edge, fk_Loop, fk_Topology, fk_TopologyMaterial, fk_Attribute
	 */
	public ref class fk_Vertex : fk_TopologyMaterial {
	internal:
		::fk_Vertex * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Vertex(bool argNewFlg);
		~fk_Vertex();
		!fk_Vertex();
#endif

		//! 位置ベクトルぷろぱてぃい
		/*!
		 *	頂点位相の位置ベクトルを参照します。
		 *	このプロパティによる位置ベクトルは、
		 *	fk_Model での配置や姿勢制御がまったく反映されないことに注意して下さい。
		 */
		property fk_Vector^ Position {
			fk_Vector^ get();
		}

		//! 法線ベクトルプロパティ
		/*!
		 *	頂点が2次元多様体上にある条件下のもと、
		 *	適切な法線ベクトルを算出し、参照します。
		 *	算出できなかった場合は零ベクトルを返します。
		 */
		property fk_Vector^ Normal {
			fk_Vector^ get();
		}

		//! 接続半稜線プロパティ
		/*!
		 *	この頂点を始点とする半稜線のうちの1つを参照します。
		 *	条件を満たす全ての半稜線を得たい場合は、
		 *	fk_Reference::GetAllHOnV() 関数を用いて下さい。
		 *	対象となる半稜線が存在しない場合は null となります。
		 */
		property fk_Half^ OneHalf {
			fk_Half^ get();
		}
		
		//! 描画サイズプロパティ
		/*!
		 *	頂点を描画する際のサイズの参照・設定を行います。
		 *	ここでの単位は「ピクセル」となります。
		 *	カメラからの距離に関係なく、同一の大きさで描画されます。
		 *	また、設定したサイズで実際に描画されるかどうかは
		 *	グラフィックスハードウェアの機能に依存します。
		 */
		property double DrawSize {
			double get();
			void set(double);
		}
	};
}
