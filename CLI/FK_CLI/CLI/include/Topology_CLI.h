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

/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
