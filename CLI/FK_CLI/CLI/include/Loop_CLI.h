// Half_CLI.h

#pragma once

#include <FK/Loop.h>
#include "Topology_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	ref class fk_Half;
	
	//! ソリッドモデルのループ位相を管理するクラス
	/*!
	 *	このクラスは、 fk_Solid によるソリッドモデルにおいて、
	 *	ループ位相に関する制御機能を提供します。
	 *	FK におけるソリッドモデルの構造については、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」の章を参照して下さい。
	 *
	 *	派生クラスのうち、ID 管理については fk_Topology,
	 *	個別マテリアル設定については fk_TopologyMaterial,
	 *	属性設定については fk_Attribute を参照して下さい。
	 *
	 *	ループに対して、幾何形状として曲面データを設定することができます。
	 *	詳細は fk_Surface を参照して下さい。
	 *	\sa fk_Solid, fk_Vertex, fk_Half, fk_Edge, fk_Topology,
	 *		fk_TopologyMaterial, fk_Attribute, fk_Surface
	 */

	public ref class fk_Loop : fk_TopologyMaterial {
	internal:
		::fk_Loop * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Loop(bool argNewFlg);
		~fk_Loop();
		!fk_Loop();
#endif

		//! 接続半稜線プロパティ
		/*!
		 *	このループを構成する半稜線のうちの1つを参照します。
		 *	条件を満たす全ての半稜線を得たい場合は、
		 *	fk_Reference::GetAllHOnL() 関数を用いて下さい。
		 *
		 *	\return このループを構成する半稜線を表す fk_Half 型インスタンスのアドレス。
		 */
		property fk_Half^ OneHalf {
			fk_Half^ get();
		}

		//! 法線ベクトルプロパティ
		/*!
		 *	適切な法線ベクトルを参照します。
		 *	ループが曲面である場合は、面全体の平均法線ベクトルとなります。
		 *	null となるケースがありえることに注意して下さい。
		 *
		 *	\return 法線ベクトルのアドレス。算出できなかった場合は null を返します。
		 */
		property fk_Vector^ Normal {
			fk_Vector^ get();
		}

		//! 頂点数プロパティ
		/*!
		 *	このループを構成する頂点数を参照します。
		 *
		 *	\return	ループを構成する頂点数。もしエラーが生じた場合は -1 となります。
		 *
		 *	\sa fk_Reference::GetVNumOnL()
		 */
		property int VertexNum {
			int get();
		}

		//! テセレーション設定プロパティ
		/*!
		 *	true の場合、4角以上のループに対してテセレーション処理を施すようになります。
		 *	false の場合はテセレーション処理を行いません。
		 *
		 *	「テセレーション」とは、4角以上の多角形に対し、
		 *	内部を複数の3角形に分割する処理のことです。
		 *	一般的に、非凸多角形や非平面多角形である場合、
		 *	描画処理が適切に行えないことがあります。
		 *	そのようなループに対しては、
		 *	テセレーションを施すことによって正常に描画されることが期待できます。
		 *
		 *	形状中の全てのループに対して、テセレーションの有無効を設定するには、
		 *	fk_Operation::TesselateMode を利用して下さい。
		 *
		 *	\sa fk_Operation::TesselateMode
		 */
		property bool TesselateMode {
			bool get();
			void set(bool);
		}

		//! テセレーション状態参照関数
		/*!
		 *	テセレーションが有効になっていても、ループが 3 角形であった場合など、
		 *	内部ではテセレーション処理を行っていない可能性があります。
		 *	実際にテセレーション処理を行ったかどうかを知るには、
		 *	この関数を用いる必要があります。
		 *
		 *	\return
		 *		true であれば、ループに対しテセレーション処理が行われています。
		 *		false であれば行われていません。
		 *
		 *	\sa TesselateMode
		 */
		bool IsTesselated(void);
	};
}
