// PickData_CLI.h

#pragma once

#include <FK/PickData.h>
#include "Model_CLI.h"

namespace FK_CLI
{
	//! 位相タイプを表す列挙型
	public enum class fk_PickedTopologyType {
		NONE,	//!< 位相要素に該当しない
		VERTEX,	//!< 頂点
		EDGE,	//!< 稜線
		LOOP	//!< 面
	};

	//! ピックによる取得データを管理するクラス
	/*!
	 *	このクラスは、ピックによって得られるデータを参照する機能を提供します。
	 *	「ピック」とは、マウスなどのポインティングデバイスによって画面上をクリックし、
	 *	形状要素を選択することです。具体的な利用方法については、
	 *	fk_Renderer::GetPickData(int, int, int)
	 *	の解説を参照して下さい。ここでは、得られたデータの参照方法を主に記述します。
	 *
	 *	ピックデータは、以下の5種類によって構成されています。
	 *	- モデル
	 *	- 位相要素タイプ
	 *	- 位相要素 ID
	 *	- 位相の最大深度
	 *	- 位相の最小深度
	 *
	 *	\sa fk_Renderer::GetPickData(int, int, int)
	 */
	public ref class fk_PickData {
	private:
		fk_Model^				_model;
		fk_PickedTopologyType^	_type;
		int						_id;
		double					_farDepth;
		double					_nearDepth;

	public:
		//! コンストラクタ
		fk_PickData::fk_PickData(fk_Model^, fk_PickedTopologyType^,
								 int, double, double);

		//! デストラクタ
		fk_PickData::~fk_PickData();

		//! モデル参照プロパティ
		/*!
		 *	ピックデータのモデルインスタンスを参照します。
		 */
		property fk_Model^ Model {
			fk_Model^ get();
		}

		//! 位相タイプ参照プロパティ
		/*!
		 *	ピックデータの位相タイプを参照します。
		 *	タイプは以下のいずれかとなります。
		 *	- fk_PickedTopologyType.VERTEX:		頂点
		 *	- fk_PickedTopologyType.EDGE:		稜線
		 *	- fk_PickedTopologyType.LOOP:		面
		 */
		property fk_PickedTopologyType^ Type {
			fk_PickedTopologyType^ get();
		}

		//! 位相 ID 参照プロパティ
		/*!
		 *	ピックデータの位相 ID を参照します。
		 */
		property int ID {
			int get();
		}

		//! 位相最大深度取得プロパティ
		/*!
		 *	ピックデータの位相の最大深度を参照します。
		 *	最大深度とは、その位相を描画した際に画面から最も遠い距離のことを指します。
		 *	値の範囲は 0～1 です。
		 */
		property double FarDepth {
			double get();
		}

		//! 位相最小深度取得プロパティ
		/*!
		 *	ピックデータの位相の最小深度を参照します。
		 *	最小深度とは、その位相を描画した際に画面に最も近い距離のことを指します。
		 *	ピックデータのなかで一番画面に近い要素を選択するときに有効ですが、
		 *	位相の姿勢や位置関係によっては最小深度だけでは判断できないケースがあります。
		 *	その場合は FarDepth で得られる値も考慮して処理してください。
		 *	値の範囲は 0～1 です。
		 */
		property double NearDepth {
			double get();
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
