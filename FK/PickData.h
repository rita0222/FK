#ifndef __FK_PICKDATA_HEADER__
#define __FK_PICKDATA_HEADER__

#include <vector>
#include <FK/Base.h>

namespace FK {
	class fk_Model;

	const int FK_PICKDATAMAX	= 512;

	//! ピックによる取得データを管理するクラス
	/*!
	 *	このクラスは、ピックによって得られるデータを参照する機能を提供します。
	 *	「ピック」とは、マウスなどのポインティングデバイスによって画面上をクリックし、
	 *	形状要素を選択することです。具体的な利用方法については、
	 *	fk_Window::getPickModel(fk_PickData *, int),
	 *	fk_Window::getPickModel(fk_PickData *, int, int, int)
	 *	の解説を参照して下さい。ここでは、得られたデータの参照方法を主に記述します。
	 *
	 *	ピックデータは、以下の5種類によって構成されています。
	 *	- モデル
	 *	- 位相要素タイプ
	 *	- 位相要素 ID
	 *	- 位相の最大深度
	 *	- 位相の最小深度
	 *
	 *	\sa fk_Window::getPickModel(fk_PickData *, int),
	 *	fk_Window::getPickModel(fk_PickData *, int, int, int),
	 *	fk_Model::setPickMode()
	 */

	class fk_PickData : public fk_BaseObject {
	public:
		//! コンストラクタ
		fk_PickData(void);

		//! デストラクタ
		virtual ~fk_PickData();

		//! コピーコンストラクタ
		fk_PickData(const fk_PickData &);

		//! 単純代入演算子
		fk_PickData & operator =(const fk_PickData &);

		//! 取得サイズ参照関数
		/*!
		 *	fk_Window::getPickModel() によって得られたデータの個数を返します。
		 *
		 *	\return		取得データ数
		 */
		int						getSize(void);

		//! モデル参照関数
		/*!
		 *	得られたピックデータのモデルインスタンスのポインタを返します。
		 *	
		 *	\param[in]		index
		 *		データのインデックス。
		 *		最初の要素は 0 で、最後の要素は getSize() から 1 を引いた数となります。
		 *
		 *	\return		モデルインスタンスのポインタ
		 */
		fk_Model *				getModel(int index);

		//! 位相タイプ参照関数
		/*!
		 *	得られたピックデータの位相タイプを返します。
		 *	タイプは以下のいずれかとなります。
		 *	- FK_VERTEX (頂点)
		 *	- FK_EDGE	(稜線)
		 *	- FK_LOOP	(面)
		 *
		 *	\param[in]		index
		 *		データのインデックス。
		 *		最初の要素は 0 で、最後の要素は getSize() から 1 を引いた数となります。
		 *
		 *	\return		位相タイプ
		 */
		fk_ObjectType			getType(int index);

		//! 位相 ID 参照関数
		/*!
		 *	得られたピックデータの位相 ID を返します。
		 *
		 *	\param[in]		index
		 *		データのインデックス。
		 *		最初の要素は 0 で、最後の要素は getSize() から 1 を引いた数となります。
		 *
		 *	\return		位相ID
		 */
		int						getID(int index);

		//! 位相最大深度取得関数
		/*!
		 *	得られたピックデータの位相の最大深度を返します。
		 *	最大深度とは、その位相を描画した際に画面から最も遠い距離のことを指します。
		 *	値の範囲は 0～1 です。
		 *
		 *	\param[in]		index
		 *		データのインデックス。
		 *		最初の要素は 0 で、最後の要素は getSize() から 1 を引いた数となります。
		 *
		 *	\return		位相noの最大深度
		 */
		double					getFarDepth(int index);

		//! 位相最小深度取得関数
		/*!
		 *	得られたピックデータの位相の最小深度を返します。
		 *	最小深度とは、その位相を描画した際に画面に最も近い距離のことを指します。
		 *	ピックデータのなかで一番画面に近い要素を選択するときに有効ですが、
		 *	位相の姿勢や位置関係によっては最小深度だけでは判断できないケースがあります。
		 *	その場合は getFarDepth()で得られる値も考慮して処理してください。
		 *	値の範囲は 0～1 です。
		 *
		 *	\param[in]		index
		 *		データのインデックス。
		 *		最初の要素は 0 で、最後の要素は getSize() から 1 を引いた数となります。
		 *
		 *	\return		位相の最小深度
		 */
		double					getNearDepth(int index);

#ifndef FK_DOXYGEN_USER_PROCESS

		void					ClearData(void);
		void					PushData(fk_Model *, int, fk_ObjectType, double, double);

#endif

	private:
		std::vector<fk_Model *>		ModelArray;
		std::vector<int>			IDArray;
		std::vector<fk_ObjectType>	typeArray;
		std::vector<double>			farDepthArray, nearDepthArray;
	};
}
#endif // !__FK_PICKDATA_HEADER__


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
