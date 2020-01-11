/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
// Modify_CLI.h

#pragma once

#include <FK/Modify.h>
#include "Operation_CLI.h"

namespace FK_CLI
{
	using namespace System::Collections::Generic;

	//! ソリッドモデル変形操作用クラス
	/*!
	 *	このクラスは、 fk_Solid クラスのインスタンスにおいて、
	 *	様々な変形処理機能を提供します。
	 *	fk_Solid の位相についての詳細は、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」という章を参照して下さい。
	 *
	 *	同様の意味を持つクラスとして fk_Operation がありますが、
	 *	このクラスではより複雑な変形操作を提供しています。
	 *	内部的には、本クラスの変形処理は全て
	 *	fk_Operation の変形操作のみを用いて実現されています。
	 *	これにより、 fk_Operation の持つ履歴操作が、
	 *	本クラスの変形処理においても有効となっています。
	 *	fk_Solid を利用する際に、
	 *	メソッドが fk_Operation によるものか、
	 *	fk_Modify によるものかを利用者が意識する必要はありません。
	 *
	 *	このクラスの機能は、大きく分けて
	 *	- 高度な位相操作 (removeVertexInLoop(), contractEdge() など)
	 *	- 基本形状の生成 (makeBlock(), makeSphere() など)
	 *	- 頂点移動 (moveVPosition())
	 *	.
	 *	の3種類があります。基本形状の生成および頂点移動については、
	 *	fk_IndexFaceSet クラスにも全て同名のメソッドが提供されており、機能も同一です。
	 *	fk_Block や fk_Sphere といった基本形状を
	 *	fk_Solid によって生成したい場合に便利です。
	 *
	 *	\sa fk_Solid, fk_Operation, fk_DataAccess, fk_Reference, fk_IndexFaceSet
	 */

	public ref class fk_Modify : fk_Operation {
	internal:
		::FK::fk_Modify * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Modify(bool argNewFlg);
		~fk_Modify();
#endif
		//! \name 位相操作メソッド
		///@{

		//! 頂点削除メソッド
		/*!
		 *	形状中の頂点と、その頂点に接続していた稜線を全て削除します。
		 *	また、頂点に接続していたループを全て結合し、新たなループを生成します。
		 *
		 *	このメソッドを実行するには、削除する頂点に隣接している頂点が、
		 *	全て3本以上の稜線と接続しているという条件を満たしているという必要があります。
		 *	隣接するループについては、必ずしもループが生成されている必要はありません。
		 *	このメソッドで削除を実行してしまうと、
		 *	それに伴い接続している稜線やループも自動的に削除されます。
		 *	削除される稜線やループの情報が必要な場合は、
		 *	事前に fk_Reference::GetAllEOnV() メソッドや
		 *	fk_Reference::GetAllLOnV() メソッド等によって参照しておく必要があります。
		 *
		 *	\image html Euler07.png "RemoveVertexInLoop"
		 *	\image latex Euler07.eps "RemoveVertexInLoop" width=10cm
		 *
		 *	\param[in]	V	削除する頂点位相インスタンス
		 *
		 *	\return
		 *		削除に成功した場合は、
		 *		新たに生成されたループの位相インスタンスを返します。
		 *		失敗した場合は null を返します。
		 */
		fk_Loop^ RemoveVertexInLoop(fk_Vertex ^V);

		//! 稜線削除メソッド1-1
		/*!
		 *	形状中の稜線を削除し、その両端点を結合します。
		 *	結合後の頂点位置は、稜線の両端点の中点となります。
		 *	結合後の頂点位置を指定したい場合は、
		 *	ContractEdge(fk_Edge^, fk_Vector^, bool) を利用して下さい。
		 *
		 *	削除する稜線は、
		 *	fk_Operation の解説にある「定義稜線」の条件を満たしている必要があります。
		 *	その他にも、処理後に形状が矛盾を来さない多くの条件があります。
		 *	削除が可能かどうかを事前に調べるには、
		 *	CheckContract() メソッドを利用して下さい。
		 *
		 *	稜線の削除に成功した場合、以下の位相が同時に削除されます。
		 *	- 稜線に接続していたループ2つ。
		 *	- 稜線の端点のうち、どちらか一方の頂点。
		 *	- 削除されていた頂点に接続していた稜線全て。
		 *	.
		 *	削除される稜線やループの情報が必要な場合は、
		 *	事前に fk_Reference::GetRightLOnE()、
		 *	fk_Reference::GetLeftLOnE() メソッドや、
		 *	fk_Reference::GetAllEOnV() メソッド等によって参照しておく必要があります。
		 *
		 *	\param[in]	E	削除する稜線位相院寸タンス
		 *
		 *	\param[in]	R
		 *		true の場合、右側半稜線の始点側頂点が残ります。
		 *		false の場合はその反対が残ります。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa CheckContract(), ContractEdge(fk_Edge^, fk_Vector^, bool)
		 */
		bool ContractEdge(fk_Edge ^E, bool R);

		//! 稜線削除メソッド1-2
		/*!
		 *	形状中の稜線を削除し、その両端点を結合します。
		 *	結合後の頂点位置は、稜線の両端点の中点となります。
		 *	結合後の頂点位置を指定したい場合は、
		 *	ContractEdge(fk_Edge^, fk_Vector^, bool) を利用して下さい。
		 *
		 *	削除する稜線は、
		 *	fk_Operation の解説にある「定義稜線」の条件を満たしている必要があります。
		 *	その他にも、処理後に形状が矛盾を来さない多くの条件があります。
		 *	削除が可能かどうかを事前に調べるには、
		 *	CheckContract() メソッドを利用して下さい。
		 *
		 *	稜線の削除に成功した場合、以下の位相が同時に削除されます。
		 *	- 稜線に接続していたループ2つ。
		 *	- 稜線の端点のうち、どちらか一方の頂点。
		 *	- 削除されていた頂点に接続していた稜線全て。
		 *	.
		 *	削除される稜線やループの情報が必要な場合は、
		 *	事前に fk_Reference::GetRightLOnE()、
		 *	fk_Reference::GetLeftLOnE() メソッドや、
		 *	fk_Reference::GetAllEOnV() メソッド等によって参照しておく必要があります。
		 *
		 *	なお、本メソッドは ContractEdge(fk_Edge^, bool) において、
		 *	第2引数に true を入力した場合と同義となります。
		 *
		 *	\param[in]	E	削除する稜線位相院寸タンス
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa CheckContract(), ContractEdge(fk_Edge^, fk_Vector^, bool)
		 */
		bool ContractEdge(fk_Edge ^E);

		//! 稜線削除メソッド2-1
		/*!
		 *	形状中の稜線を削除し、その両端点を結合します。
		 *	結合後の頂点位置を指定できる以外は、
		 *	ContractEdge(fk_Edge^, bool) と同様です。
		 *
		 *	\param[in]	E	削除する稜線位相院寸タンス
		 *	\param[in]	P	結合した頂点の位置ベクトル
		 *
		 *	\param[in]	R
		 *		true の場合、右側半稜線の始点側頂点が残ります。
		 *		false の場合はその反対が残ります。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa CheckContract(), ContractEdge(fk_Edge^, bool)
		 */
		bool ContractEdge(fk_Edge ^E, fk_Vector ^P, bool R);

		//! 稜線削除メソッド2-2
		/*!
		 *	形状中の稜線を削除し、その両端点を結合します。
		 *	結合後の頂点位置を指定できる以外は、
		 *	ContractEdge(fk_Edge^, bool) と同様です。
		 *
		 *	なお、本メソッドは ContractEdge(fk_Edge^, fk_Vector^, bool) において、
		 *	第3引数に true を入力した場合と同義となります。

		 *	\param[in]	E	削除する稜線位相院寸タンス
		 *	\param[in]	P	結合した頂点の位置ベクトル
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa CheckContract(), ContractEdge(fk_Edge^, bool)
		 */
		bool ContractEdge(fk_Edge ^E, fk_Vector ^P);


		//! 稜線削除可能判定メソッド
		/*!
		 *	ContractEdge() メソッドによって、稜線が削除可能かどうかを判定するメソッドです。
		 *
		 *	\param[in]	E	判定する稜線の位相インスタンス
		 *
		 *	\return		削除可能であれば true を、不可能であれば false を返します。
		 */
		bool CheckContract(fk_Edge ^E);
		///@}

		//! \name 多角形生成メソッド
		///@{

		//! 多角形生成メソッド1
		/*!
		 *	新たに多角形を生成します。
		 *
		 *	\param[in]	array
		 *		頂点の位置ベクトル配列。
		 *		要素数が 3 以上である必要があります。
		 *		多角形頂点は、この配列の順番に繫がります。
		 *
		 *	\param[in]	openFlg
		 *		true の場合、開いた多角形を生成します。
		 *		この場合は、頂点の始点と終点の間に線分を生成しません。
		 *		false の場合は閉じた多角形を生成します。
		 *		つまり、始点と終点の間に稜線を生成します。
		 *
		 *	\param[in]	initFlg
		 *		true の場合、既にあった形状を全て消去します。false の場合は消去しません。
		 *		false の場合、実質的に PushPolygon() と機能的に同一となります。
		 *
		 *	\return
		 *		生成に成功すれば、生成されたループ位相インスタンスを返します。
		 *		失敗した場合は nullptr を返します。
		 *
		 *	\sa PushPolygon(IEnumerable<fk_Vector^>^, bool)
		 */
		fk_Loop^ MakePolygon(IEnumerable<fk_Vector^>^ array, bool openFlg, bool initFlg);

		//! 多角形生成メソッド2
		/*!
		 *	新たに多角形を生成します。
		 *	本メソッドは、 MakePolygon(IEnumerable<fk_Vector^>^, bool, bool) において、
		 *	第3引数に true を入力した場合と同義となります。
		 *
		 *	\param[in]	array
		 *		頂点の位置ベクトル配列。
		 *		要素数が 3 以上である必要があります。
		 *		多角形頂点は、この配列の順番に繫がります。
		 *
		 *	\param[in]	openFlg
		 *		true の場合、開いた多角形を生成します。
		 *		この場合は、頂点の始点と終点の間に線分を生成しません。
		 *		false の場合は閉じた多角形を生成します。
		 *		つまり、始点と終点の間に稜線を生成します。
		 *
		 *	\return
		 *		生成に成功すれば、生成されたループ位相インスタンスを返します。
		 *		失敗した場合は nullptr を返します。
		 *
		 *	\sa PushPolygon(IEnumerable<fk_Vector^>^, bool)
		 */
		fk_Loop^ MakePolygon(IEnumerable<fk_Vector^>^ array, bool openFlg);

		//! 多角形追加メソッド1
		/*!
		 *	多角形を追加します。
		 *	本メソッドは、実質的に MakePolygon(IEnumerable<fk_Vector^>^, bool, bool) メソッドで、
		 *	initFlg を false にした場合と機能的に同一となります。
		 *
		 *	\param[in]	array
		 *		頂点の位置ベクトル配列。
		 *		要素数が 3 以上である必要があります。
		 *		多角形頂点は、この配列の順番に繫がります。
		 *
		 *	\param[in]	openFlg
		 *		true の場合、開いた多角形を生成します。
		 *		この場合は、頂点の始点と終点の間に線分を生成しません。
		 *		false の場合は閉じた多角形を生成します。
		 *		つまり、始点と終点の間に稜線を生成します。
		 *
		 *	\return
		 *		生成に成功すれば、生成されたループ位相インスタンスを返します。
		 *		失敗した場合は nullptr を返します。
		 *
		 *	\sa MakePolygon(IEnumerable<fk_Vector^>^, bool, bool)
		 */
		fk_Loop^ PushPolygon(IEnumerable<fk_Vector^>^ array, bool openFlg);

		//! 多角形追加メソッド2
		/*!
		 *	多角形を追加します。
		 *	本メソッドは、 PushPolygon(IEnumerable<fk_Vector^>^, bool) において、
		 *	第2引数に false を入力した場合と同義となります。
		 *
		 *	\param[in]	array
		 *		頂点の位置ベクトル配列。
		 *		要素数が 3 以上である必要があります。
		 *		多角形頂点は、この配列の順番に繫がります。
		 *
		 *	\return
		 *		生成に成功すれば、生成されたループ位相インスタンスを返します。
		 *		失敗した場合は nullptr を返します。
		 *
		 *	\sa MakePolygon(IEnumerable<fk_Vector^>^, bool, bool)
		 */
		fk_Loop^ PushPolygon(IEnumerable<fk_Vector^>^ array);

		//! 多角形頂点追加メソッド
		/*!
		 *	このメソッドは、多角形に対して頂点を追加します。
		 *	本メソッドを用いる前提条件として、
		 *	MakePolygon() メソッドによって 1 つだけ多角形が生成された状況でなければなりません。
		 *	その条件が満たされていない場合の動作は保証されません。
		 *
		 *	\param[in]	pos		追加頂点の位置ベクトル
		 *
		 *	\param[in]	openFlg
		 *		true の場合、開いた多角形を生成します。
		 *		この場合は、多角形の始点と新規追加点の間に線分を生成しません。
		 *		false の場合は閉じた多角形を生成します。
		 *		つまり、多角形の始点と新規追加点の間に稜線を生成します。
		 */
		void PushPolygonVertex(fk_Vector ^pos, bool openFlg);
		///@}

		//! \name 頂点群生成メソッド
		///@{

		//! 頂点群生成メソッド
		/*!
		 *	与えられた位置ベクトル配列による頂点群を生成します。
		 *	このメソッドを呼ぶ前に存在していた形状データは全て消去されます。
		 *
		 *	\param[in]	array		頂点群の位置ベクトル配列
		 */
		void MakePoint(IEnumerable<fk_Vector^>^ array);

		//! 頂点追加メソッド
		/*!
		 *	形状に頂点1個を追加します。
		 *
		 *	\param[in]	pos		頂点の位置ベクトル
		 *
		 *	\return		新規に生成された頂点位相のインスタンスを返します。
		 */
		fk_Vertex^ PushPointVertex(fk_Vector ^pos);

		///@}

		//! \name 線分生成メソッド
		///@{

		//! 線分群生成メソッド
		/*!
		 *	与えられた位置ベクトル配列を元に、線分群を生成します。
		 *	位置ベクトルは、配列中で [始点1, 終点1, 始点2, 終点2, ...]
		 *	と扱われます。配列の長さが奇数であった場合、最後の要素は無視されます。
		 *	このメソッドを呼ぶ前に存在していた形状データは全て消去されます。
		 *
		 *	\param[in]	array		線分の両端点を表す頂点位置ベクトル配列
		 */
		void MakeLines(IEnumerable<fk_Vector^>^ array);

		//! 線分追加メソッド
		/*!
		 *	形状に線分1本を追加します。
		 *
		 *	\param[in]	pos1		稜線の始点位置ベクトル
		 *	\param[in]	pos2		稜線の終点位置ベクトル
		 *
		 *	\return		新規に生成された稜線位相のインスタンスを返します。
		 */
		fk_Edge^ PushLines(fk_Vector ^pos1, fk_Vector ^pos2);

		//! 線分頂点移動メソッド1
		/*!
		 *	線分の端点位置を移動します。
		 *	本メソッドを用いる前提条件として、
		 *	MakeLines() によって 1 本だけ線分が生成された状況でなければなりません。
		 *	その状況が満たされていない場合の動作は保証されません。
		 *
		 *	\param[in]	ID
		 *		0 であれば始点を、1 であれば終点を移動対象とします。
		 *		その他の ID が与えられた場合はエラーとなります。
		 *
		 *	\param[in]	pos		移動先の位置ベクトル
		 *
		 *	\return		移動に成功すれば true を、失敗すれば false を返します。
		 */
		bool SetLinePos(int ID, fk_Vector ^pos);

		//! 線分頂点移動メソッド2
		/*!
		 *	線分の端点位置を移動します。
		 *	本メソッドを用いる前提条件として、
		 *	MakeLines() と PushLines() のみによって、
		 *	複数の線分が生成された状況でなければなりません。
		 *	その条件が満たされていない場合の動作は保証されません。
		 *
		 *	\param[in]	edgeID
		 *		線分の ID。ID は生成した順に 0, 1, 2... となります。
		 *
		 *	\param[in]	vertexID
		 *		0 であれば始点を、1 であれば終点を移動対象とします。
		 *		その他の ID が与えられた場合はエラーとなります。
		 *
		 *	\param[in]	pos			移動先の位置ベクトル
		 *
		 *	\return		移動に成功すれば true を、失敗すれば false を返します。
		 */
		bool SetLinePos(int edgeID, int vertexID, fk_Vector^ pos);

		//! 線分両端点移動メソッド
		/*!
		 *	線分の、両端点の位置を同時に移動します。
		 *	本メソッドを用いる前提条件として、
		 *	MakeLines() と PushLines() のみによって、
		 *	複数の線分が生成された状況でなければなりません。
		 *	その条件が満たされていない場合の動作は保証されません。
		 *
		 *	\param[in]	edgeID		線分の ID。ID は生成した順に 0, 1, 2... となります。
		 *	\param[in]	pos1		始点の移動先位置ベクトル
		 *	\param[in]	pos2		終点の移動先位置ベクトル
		 *
		 *	\return		移動に成功すれば true を、失敗すれば false を返します。
		 */
		bool ChangeLine(int edgeID, fk_Vector^ pos1, fk_Vector^ pos2);
		///@}

		//! \name 直方体形状生成メソッド
		///@{

		//! 直方体生成メソッド
		/*!
		 *	直方体を生成します。
		 *
		 *	直方体は、原点の物体の中心が来るように配置されます。
		 *	従って、(x, y, z) という大きさで直方体を生成した場合、
		 *	各頂点の位置ベクトルは以下のようになります。
		 *	- (x/2, y/2, z/2)
		 *	- (-x/2, y/2, z/2)
		 *	- (-x/2, -y/2, z/2)
		 *	- (x/2, -y/2, z/2)
		 *	- (x/2, y/2, -z/2)
		 *	- (-x/2, y/2, -z/2)
		 *	- (-x/2, -y/2, -z/2)
		 *	- (x/2, -y/2, -z/2)
		 *
		 *	このメソッドを呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	x	x方向の辺長
		 *	\param[in]	y	y方向の辺長
		 *	\param[in]	z	z方向の辺長
		 *
		 *	\sa fk_Block
		 */
		void MakeBlock(double x, double y, double z);

		//! 直方体辺長変更メソッド
		/*!
		 *	MakeBlock() によって直方体を生成した後に、
		 *	直方体の辺長を一括して設定しなおします。
		 *	このメソッドは、 MakeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	x	x方向の辺長
		 *	\param[in]	y	y方向の辺長
		 *	\param[in]	z	z方向の辺長
		 *
		 *	\sa MakeBlock(), fk_Block
		 */
		void SetBlockSize(double x, double y, double z);

		//! 直方体個別辺長設定メソッド
		/*!
		 *	MakeBlock() によって直方体を生成した後に、
		 *	直方体の辺長を個別に設定します。
		 *	このメソッドは、 MakeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	length	辺長
		 *	\param[in]	axis	軸方向。以下のいずれかを指定します。
		 *		- fk_Axis.X x方向
		 *		- fk_Axis.Y y方向
		 *		- fk_Axis.Z z方向
		 *
		 *	\sa MakeBlock(), fk_Block
		 */
		void SetBlockSize(double length, fk_Axis axis);

		//! 直方体全体拡大縮小メソッド
		/*!
		 *	MakeBlock() によって直方体を生成した後に、
		 *	直方体全体を指定された倍率で拡大・縮小します。
		 *	このメソッドは、 MakeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *
		 *	\sa MakeBlock(), fk_Block
		 */
		void SetBlockScale(double scale);

		//! 直方体軸方向拡大縮小メソッド
		/*!
		 *	MakeBlock() によって直方体を生成した後に、
		 *	指定された軸方向についてのみ拡大・縮小します。
		 *	このメソッドは、 MakeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *	\param[in]	axis	軸方向。以下のいずれかを指定します。
		 *		- fk_Axis.X x方向
		 *		- fk_Axis.Y y方向
		 *		- fk_Axis.Z z方向
		 *
		 *	\sa MakeBlock(), fk_Block
		 */
		void SetBlockScale(double scale, fk_Axis axis);

		//! 直方体軸方向個別拡大縮小メソッド
		/*!
		 *	MakeBlock() によって直方体を生成した後に、
		 *	各軸方向に対し個別の倍率で拡大・縮小します。
		 *	このメソッドは、 MakeBlock() によって直方体を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	x	x方向の倍率
		 *	\param[in]	y	y方向の倍率
		 *	\param[in]	z	z方向の倍率
		 *
		 *	\sa MakeBlock(), fk_Block
		 */
		void SetBlockScale(double x, double y, double z);
		///@}

		//! \name 円形状生成メソッド
		///@{

		//! 円形状生成メソッド
		/*!
		 *	円形状を生成します。
		 *
		 *	ここでの「円」は実際には正多角形を円に近似して扱っています。
		 *	多角形の角数は (分割数) * 4 となっています。
		 *	この多角形は、実質的には設定された半径の円に内接するものです。
		 *	円としての見栄えを良くするには分割数を大きめに設定すべきですが、
		 *	分割数の大きい円を大量に利用すると描画処理が遅くなるという問題が生じます。
		 *
		 *	初期状態では、中心を原点とし、
		 *	面の法線ベクトルが (0, 0, 1) となるように配置されます。
		 *
		 *	このメソッドを呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	div	分割数。実際には円弧全体をこの数値の 4 倍で分割します。
		 *	\param[in]	rad	半径
		 *
		 *	\sa fk_Circle
		 */
		void MakeCircle(int div, double rad);

		//! 円形状半径設定メソッド
		/*!
		 *	MakeCircle() によって円形状を生成した後に、
		 *	半径を設定しなおします。
		 *	このメソッドは、 MakeCircle() によって円形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	rad	半径
		 *
		 *	\sa MakeCircle(), fk_Circle
		 */
		void SetCircleRadius(double rad);

		//! 円形状分割数設定メソッド
		/*!
		 *	MakeCircle() によって円形状を生成した後に、
		 *	分割数を設定しなおします。
		 *	このメソッドは、 MakeCircle() によって円形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div		分割数
		 *
		 *	\sa MakeCircle(), fk_Circle
		 */
		void SetCircleDivide(int div);

		//! 円形状拡大縮小メソッド
		/*!
		 *	MakeCircle() によって円形状を生成した後に、
		 *	形状全体を与えられた倍率で拡大・縮小します。
		 *	このメソッドは、 MakeCircle() によって円形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *
		 *	\sa MakeCircle(), fk_Circle
		 */
		void SetCircleScale(double scale);
		///@}

		//! \name 球形状制御メソッド
		///@{

		//! 球形状生成メソッド
		/*!
		 *	球形状を生成します。
		 *
		 *	実際には、球を近似する3角形面集合として表現されています。
		 *	3角形面の数は分割数を \f$ d \f$ とした場合 \f$ 8d(d-1) \f$ 枚となります。
		 *	分割数が高いほど球としての描画精度は高くなりますが、
		 *	面数も多くなるため描画速度が低下することになります。
		 *	特に多くのオブジェクトを同時に配置する場合は注意が必要です。
		 *
		 *	初期状態では、中心を原点とするように配置されます。
		 *
		 *	このメソッドを呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *	
		 *	\param[in]	div	分割数
		 *	\param[in]	rad	半径
		 *	\sa fk_Sphere
		 */
		void MakeSphere(int div, double rad);

		//! 球形状半径設定メソッド
		/*!
		 *	MakeSphere() によって球形状を生成した後に、
		 *	半径を設定しなおします。
		 *	このメソッドは、 MakeSphere() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	rad	半径
		 *
		 *	\sa MakeSphere(), fk_Sphere
		 */
		void SetSphereRadius(double rad);

		//! 球形状分割数設定メソッド
		/*!
		 *	MakeSphere() によって球形状を生成した後に、
		 *	分割数を設定しなおします。
		 *	このメソッドは、 MakeSphere() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div		分割数
		 *
		 *	\sa MakeSphere(), fk_Sphere
		 */
		void SetSphereDivide(int div);

		//! 球形状拡大縮小メソッド
		/*!
		 *	MakeSphere() によって球形状を生成した後に、
		 *	形状全体を与えられた倍率で拡大・縮小します。
		 *	このメソッドは、 MakeSphere() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	scale	倍率
		 *
		 *	\sa MakeSphere(), fk_Sphere
		 */
		void SetSphereScale(double scale);
		///@}

		//! \name 正多角柱(円柱)形状制御メソッド
		///@{

		//! 正多角柱(円柱)形状生成メソッド
		/*!
		 *	正多角柱(円柱)を生成します。
		 *
		 *	円柱は、分割数の多い正多角柱として生成します。
		 *	通常、分割数が 20 を超える程度でほとんど円柱と見分けがつかなくなります。
		 *	配置は、底面の中心が原点となり、
		 *	多角柱の上面が -z 方向、底面が +z 方向となります。
		 *
		 *	設定できる要素は角数、上面半径、底面半径、高さの4要素です。
		 *	上面と底面の半径とは、それぞれの面を構成する正多角形の外接円半径を指します。
		 *
		 *	このメソッドを呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	div		角数
		 *	\param[in]	top		上面半径
		 *	\param[in]	bottom	底面半径
		 *	\param[in]	height	高さ
		 *
		 *	\sa fk_Prism
		 */
		void MakePrism(int div, double top, double bottom, double height);

		//! 正多角柱(円柱)角数設定メソッド
		/*!
		 *	MakePrism() によって正多角柱(円柱)を生成した後に、
		 *	角数を設定しなおします。
		 *	このメソッドは、 MakePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div	角数
		 *
		 *	\sa MakePrism(), fk_Prism
		 */
		void SetPrismDivide(int div);

		//! 正多角柱(円柱)上面半径設定メソッド
		/*!
		 *	MakePrism() によって正多角柱(円柱)を生成した後に、
		 *	上面の外接円半径を設定しなおします。
		 *	このメソッドは、 MakePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	top	上面半径
		 *
		 *	\sa MakePrism(), fk_Prism
		 */
		void SetPrismTopRadius(double top);

		//! 正多角柱(円柱)角数設定メソッド
		/*!
		 *	MakePrism() によって正多角柱(円柱)を生成した後に、
		 *	底面の外接円半径を設定しなおします。
		 *	このメソッドは、 MakePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	bottom	底面半径
		 *
		 *	\sa MakePrism(), fk_Prism
		 */
		void SetPrismBottomRadius(double bottom);

		//! 正多角柱(円柱)高さ設定メソッド
		/*!
		 *	MakePrism() によって正多角柱(円柱)を生成した後に、
		 *	高さを設定しなおします。
		 *	このメソッドは、 MakePrism() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	height	高さ
		 *
		 *	\sa MakePrism(), fk_Prism
		 */
		void SetPrismHeight(double height);
		///@}

		//! \name 正多角錐(円錐)形状制御メソッド
		///@{

		//! 正多角錐(円錐)形状生成メソッド
		/*!
		 *	正多角錐(円錐)を生成します。
		 *
		 *	円錐は、分割数の多い正多角錐として生成します。
		 *	通常、分割数が 20 を超える程度でほとんど円錐と見分けがつかなくなります。
		 *	配置は、底面の中心が原点となり、
		 *	頂点 -z 方向、底面が +z 方向となります。
		 *
		 *	設定できる要素は角数、底面半径、高さの3要素です。
		 *	底面半径とは、面を構成する正多角形の外接円半径を指します。
		 *
		 *	このメソッドを呼ぶ前に生成されていた形状や各種属性は破棄されます。
		 *
		 *	\param[in]	div		角数
		 *	\param[in]	rad		底面半径
		 *	\param[in]	height	高さ
		 *
		 *	\sa fk_Cone
		 */
		void MakeCone(int div, double rad, double height);

		//! 正多角錐(円錐)角数設定メソッド
		/*!
		 *	MakeCone() によって正多角錐(円錐)を生成した後に、
		 *	角数を設定しなおします。
		 *	このメソッドは、 MakeCone() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	div	角数
		 *
		 *	\sa MakeCone(), fk_Cone
		 */
		void SetConeDivide(int div);

		//! 正多角錐(円錐)底面半径設定メソッド
		/*!
		 *	MakeCone() によって正多角錐(円錐)を生成した後に、
		 *	底面外接円半径を設定しなおします。
		 *	このメソッドは、 MakeCone() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	rad		底面半径
		 *
		 *	\sa MakeCone(), fk_Cone
		 */

		void SetConeRadius(double rad);
		//! 正多角錐(円錐)高さ設定メソッド
		/*!
		 *	MakeCone() によって正多角錐(円錐)を生成した後に、
		 *	高さを設定しなおします。
		 *	このメソッドは、 MakeCone() によって球形状を生成した場合のみ有効であり、
		 *	それ以外の形状状態に対してこのメソッドを呼んだときの挙動は保証されません。
		 *
		 *	\param[in]	height		高さ
		 *
		 *	\sa MakeCone(), fk_Cone
		 */
		void SetConeHeight(double height);
		///@}

		//! \name 頂点移動メソッド
		///@{

		//! 頂点移動メソッド1-1
		/*!
		 *	指定された頂点を移動します。
		 *
		 *	\param[in]	vertexID		頂点ID。
		 *	\param[in]	pos				移動先の位置ベクトル
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は 0 を入力して下さい。
		 *								
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool MoveVPosition(int vertexID, fk_Vector ^pos, int order);

		//! 頂点移動メソッド1-2
		/*!
		 *	指定された頂点を移動します。
		 *	本メソッドは、 MoveVPosition(int, fk_Vector^, int) において、
		 *	第3引数に 0 を入力した場合と同義となります。
		 *
		 *	\param[in]	vertexID		頂点ID。
		 *	\param[in]	pos				移動先の位置ベクトル
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool MoveVPosition(int vertexID, fk_Vector ^pos);

		//! 頂点移動メソッド2-1
		/*!
		 *	指定された頂点を移動します。
		 *
		 *	\param[in]	vertexID		頂点ID。
		 *	\param[in]	x				移動先位置ベクトルの x 成分
		 *	\param[in]	y				移動先位置ベクトルの y 成分
		 *	\param[in]	z				移動先位置ベクトルの z 成分
		 *
		 *	\param[in]	order
		 *		最初の頂点IDを補正するオーダー。通常は 0 を入力して下さい。
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool MoveVPosition(int vertexID, double x, double y, double z, int order);

		//! 頂点移動メソッド2-2
		/*!
		 *	指定された頂点を移動します。
		 *	本メソッドは、 MoveVPosition(int, double, double, double, int) において、
		 *	第5引数に 0 を入力した場合と同義となります。
		 *
		 *	\param[in]	vertexID		頂点ID。
		 *	\param[in]	x				移動先位置ベクトルの x 成分
		 *	\param[in]	y				移動先位置ベクトルの y 成分
		 *	\param[in]	z				移動先位置ベクトルの z 成分
		 *
		 *	\return		成功すれば true を、失敗すれば false を返します。
		 */
		bool MoveVPosition(int vertexID, double x, double y, double z);
		///@}

		//! \name 細分割曲面生成メソッド
		///@{

		//! 細分割曲面生成メソッド
		/*!
		 *	このメソッドは、細分割曲面 (Subdivision Surface) 手法に基づいた面分割を行います。
		 *	分割回数を増加するほど細分割曲面に形状は近くなりますが、
		 *	面数は大きく増加します。
		 *	現状では、曲面生成手法は「Catmull-Clark 手法」のみをサポートしています。
		 *
		 *	\param[in]	count		分割回数。
		 */
		void SubDivShape(int count);
		///@}
	};
}


