// Half_CLI.h

#pragma once

#include <FK/Half.h>
#include "Topology_CLI.h"
//#include "Edge_CLI.h"
//#include "Loop_CLI.h"

namespace FK_CLI
{
	ref class fk_Vertex;
	ref class fk_Edge;
	ref class fk_Loop;

	//! ソリッドモデルの半稜線位相を管理するクラス
	/*!
	 *	このクラスは、 fk_Solid によるソリッドモデルにおいて、
	 *	半稜線位相に関する制御機能を提供します。
	 *	FK におけるソリッドモデルの構造については、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」の章を参照して下さい。
	 *
	 *	派生クラスのうち、ID 管理については fk_Topology,
	 *	個別マテリアル設定については fk_TopologyMaterial,
	 *	属性設定については fk_Attribute を参照して下さい。
	 *
	 *	\sa fk_Solid, fk_Vertex, fk_Edge, fk_Loop, fk_Topology, fk_TopologyMaterial, fk_Attribute
	 */
	public ref class fk_Half : fk_Topology {
	internal:
		::fk_Half * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Half(bool argNewFlg);
		~fk_Half();
		!fk_Half();
#endif

		//! 頂点プロパティ
		/*!
		 *	この半稜線が始点としている頂点位相を参照します。
		 */
		property fk_Vertex^ Vertex {
			fk_Vertex^ get();
		}

		//! 後半稜線位相プロパティ
		/*!
		 *	半稜線の接続関係において、この半稜線の後にあたる半稜線を参照します。
		 */
		property fk_Half^ NextHalf {
			fk_Half^ get();
		}
		
		//! 前半稜線位相プロパティ
		/*!
		 *	半稜線の接続関係において、この半稜線の前にあたる半稜線を参照します。
		 */
		property fk_Half^ PrevHalf {
			fk_Half^ get();
		}

		//! 稜線位相プロパティ
		/*!
		 *	この半稜線が属している稜線位相を参照します。
		 */
		property fk_Edge^ ParentEdge {
			fk_Edge^ get();
		}
		
		//! ループ位相プロパティ
		/*!
		 *	この半稜線が属しているループ位相を参照します。
		 *	半稜線がループに属していない場合は null となります。
		 */
		property fk_Loop^ ParentLoop {
			fk_Loop^ get();
		}

		//! 左側判定関数
		/*!
		 *	この半稜線が、属している稜線の「左側」かどうかを判定する関数です。
		 *
		 *	\return 「左側」である場合 true を、「右側」である場合 false を返します。
		 */
		bool IsLeft(void);

		//! 右側判定関数
		/*!
		 *	この半稜線が、属している稜線の「右側」かどうかを判定する関数です。
		 *
		 *	\return 「右側」である場合 true を、「左側」である場合 false を返します。
		 */
		bool IsRight(void);
	};
}
