// Topology_CLI.h

#pragma once

#include <FK/Topology.h>
#include "Attribute_CLI.h"
#include "Palette_CLI.h"

namespace FK_CLI
{
	//! 位相タイプを表す列挙型
	public enum class fk_TopologyType {
		VERTEX,		//!< 頂点
		HALF,		//!< 半稜線
		EDGE,		//!< 稜線
		LOOP,		//!< ループ
		INDEXFACE,	//!< インデックスフェースセット
		UNDEFINED	//!< 未定義な位相要素
	};

	//! ソリッドモデル位相要素用基底クラス
	/*!
	 *	このクラスは、 fk_Solid における位相要素の共通部分に関する機能を提供します。
	 *	FK におけるソリッドモデルの構造については、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」の章を参照して下さい。
	 *
	 *	\sa fk_Solid, fk_Vertex, fk_Half, fk_Edge, fk_Loop, fk_TopologyMaterial
	 */
	public ref class fk_Topology : fk_Attribute {
	internal:
		::fk_Topology * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Topology(bool argNewFlg);
		~fk_Topology();
		!fk_Topology();
#endif
		
		//! IDプロパティ
		property int ID {
			int get();
		}

		//! 位相タイププロパティ
		/*!
		 *	位相タイプを参照します。以下のいずれかとなります。
		 *
		 *	\retval fk_TopologyType.VERTEX		頂点を表します。
		 *	\retval fk_TopologyType.HALF		半稜線を表します。
		 *	\retval fk_TopologyType.EDGE		稜線を表します。
		 *	\retval fk_TopologyType.LOOP		ループを表します。
		 *	\retval fk_TopologyType.INDEXFACE	インデックスフェースセットを表します。
		 *	\retval fk_TopologyType.UNDEFINED	未定義な位相要素を表します。
		 */
		property fk_TopologyType Type {
			fk_TopologyType get();
		}
	};

	//! 位相要素個別マテリアル管理クラス
	/*!
	 *	このクラスは、 fk_Solid における位相要素について、
	 *	個別にマテリアルを管理する機能を提供します。
	 *
	 *	fk_Solid による1つの形状内で、
	 *	各位相要素について別々にマテリアルを設定したい場合は、
	 *	このクラスのメンバ関数を用います。
	 *
	 *	\sa fk_Solid, fk_Vertex, fk_Edge, fk_Loop, fk_Topology, fk_Shape, fk_Model
	 */
	public ref class fk_TopologyMaterial : fk_Topology {
	internal:
		::fk_TopologyMaterial * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_TopologyMaterial(bool argNewFlg);
		~fk_TopologyMaterial();
		!fk_TopologyMaterial();
#endif
		
		//! マテリアルモードプロパティ
		/*!
		 *	各位相要素の描画の際に、
		 *	個別のマテリアルを利用に関する参照・設定を行います。
		 *	fk_Solid による形状では、
		 *	個別マテリアルを有効とするのには以下の条件を満たす必要があります。
		 *	- fk_Model にてマテリアルモードが fk_MaterialMode.PARENT になっている。
		 *		(fk_Model::MaterialMode を参照して下さい。)
		 *	- fk_Solid にてマテリアルモードが fk_MaterialMode.PARENT になっている。
		 *		(fk_Shape::MaterialMode を参照して下さい。)
		 *	.
		 *	上記の条件を満たさない場合、個別のマテリアル設定の有無に関わらず
		 *	全ての位相要素がモデルに設定されたマテリアルによって描画を行います。
		 *
		 *	前述の条件を前提として、位相要素のマテリアルを以下のように設定します。
		 *		- fk_MaterialMode.CHILD:	個別設定を利用します。
		 *		- fk_MaterialMode.PARENT:	モデル設定を利用します。
		 *		- fk_MaterialMode.NONE:		描画を行いません。
		 */
		property fk_MaterialMode MaterialMode {
			fk_MaterialMode get();
			void set(fk_MaterialMode);
		}

		//!	マテリアルIDプロパティ
		/*!
		 *	位相要素の個別マテリアルの設定である、パレットの ID の参照・設定を行います。
		 *	パレットに関する解説は
		 *	fk_Shape::SetPalette() や fk_Shape::PushPalette() を参照して下さい。
		 */
		property int MaterialID {
			int get();
			void set(int);
		}
	};		
}
