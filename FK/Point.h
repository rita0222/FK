/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_POINT_HEADER__
#define __FK_POINT_HEADER__

#include <FK/Vector.h>
#include <FK/Array.H>
#include <FK/Shape.h>

class fk_Window;

//! 点群を生成、管理するクラス
/*!
 *	このクラスは、形状として点群を制御する機能を提供します。
 *	1つのインスタンスで、複数の点を制御することが可能です。
 *
 *	このクラスの機能は大きく以下のようなものとなります。
 *	- 点の生成や消去
 *	- 点の移動
 *	- 各点の描画有無の設定
 *	- 各店の描画色の設定
 *	.
 *	このクラスと同様に点群を扱うクラスとして、
 *	fk_Particle と fk_ParticleSet があります。
 *	fk_Point が点の制御を直接的に行うのに対し、
 *	fk_Particle や fk_ParticleSet では
 *	法則を記述することが主であるという特徴があります。
 *
 *	\sa fk_Shape, fk_Particle, fk_ParticleSet
 */

class fk_Point: public fk_Shape {

	friend class			fk_PointDraw;

 private:
	fk_Palette				localPal;
	fk_Array<fk_FVector>	vec;
	std::vector<char>		drawMode;
	int						drawCount;
	std::vector<int>		colorID;
	int						colorCount;

	bool	MakePoint(std::vector<fk_Vector> *);
	bool	MakePoint(int, fk_Vector *);

 public:

	//! コンストラクタ
	/*!
	 *	引数として vector による fk_Vector 型の配列を与えることによって、
	 *	最初から点群を生成することができます。
	 *
	 *	\param[in]	array
	 *		点群位置ベクトル配列。NULL の場合は何も生成しません。
	 */
	fk_Point(std::vector<fk_Vector> *array = NULL);

	//! デストラクタ
	virtual ~fk_Point();

	//! 頂点追加関数
	/*!
	 * 	頂点を新たに追加します。
	 *
	 *	\param[in]	pos		追加する頂点の位置ベクトル
	 *
	 *	\return		新しい頂点の ID
	 */
	int				pushVertex(fk_Vector pos);

	//! 頂点位置設定関数
	/*!
	 *	点群中の任意の頂点に対し、位置を設定します。
	 *
	 *	\param[in]	ID		頂点ID
	 *	\param[in]	pos		移動先の位置ベクトル
	 *
	 *	\return		移動に成功すれば true を、失敗すれば false を返します。
	 */
	bool			setVertex(int ID, fk_Vector pos);

	//! 点群生成関数 1
	/*
	 *	配列データから点群全体を生成します。
	 *	関数を呼ぶ前に存在していた点は全て消去されます。
	 *
	 *	\param[in]	num		頂点数
	 *	\param[in]	array	頂点位置ベクトルの配列
	 *
	 *	\return		生成に成功すれば true を、失敗すれば false を返します。
	 */
	bool			setVertex(int num, fk_Vector *array);

	//! 点群生成関数 2
	/*
	 *	配列データから点群全体を生成します。
	 *	関数を呼ぶ前に存在していた点は全て消去されます。
	 *
	 *	\param[in]	array	頂点位置ベクトルの配列
	 *
	 *	\return		生成に成功すれば true を、失敗すれば false を返します。
	 */
	bool			setVertex(std::vector<fk_Vector> *array);

	//! 頂点削除関数
	/*
	 *	頂点を削除します。
	 *
	 *	\param[in]	ID		頂点ID
	 *
	 *	\return		削除に成功すれば true を、失敗すれば false を返します。
	 */
	bool			removeVertex(int ID);

	//! 頂点位置ベクトル取得関数
	/*!
	 *	指定した頂点の位置ベクトルのポインタを返します。
	 *	ベクトルの型は fk_Vector ではなく
	 *	fk_FVector であることに注意して下さい。
	 *
	 *	\param[in]	ID		頂点ID
	 *
	 *	\return
	 *		頂点の位置ベクトルインスタンスへのポインタ。
	 *		指定した頂点が存在しない場合は NULL を返します。
	 */
	fk_FVector *	getVertex(int ID);

	//! 頂点数取得関数
	/*!
	 *	点群の頂点数を返します。
	 *
	 *	\return		頂点数
	 */
	int				getSize(void);

	//! 頂点描画制御関数
	/*!
	 *	個別の頂点に対し、描画の有無を設定します。
	 *
	 *	\param[in]	ID		頂点ID
	 *	\param[in]	mode
	 *		true であれば描画を有効に、false であれば無効にします。
	 */
	void			setDrawMode(int ID, bool mode);

	//! 全頂点描画状態参照関数
	/*!
	 *	点群全体の描画状況を取得します。
	 *
	 *	\return
	 *		点群中、1つでも描画される状態であれば true を、
	 *		そうでない場合は false を返します。
	 *		false を返す場合は、頂点が存在するが全て描画状態が無効である場合と、
	 *		1個も頂点が存在していない場合の2通りがありえます。
	 */
	bool			getDrawMode(void);

	//! 個別頂点描画状態参照関数
	/*!
	 *	個別の頂点に対し、描画状況をを取得します。
	 *
	 *	\param[in]	ID		頂点ID
	 *
	 *	\return
	 *		描画が有効であれば true を、無効であれば false を返します。
	 *		指定した ID を持つ頂点が存在しなかった場合も false を返します。
	 */
	bool			getDrawMode(int ID);

	//! 描画色設定関数
	/*!
	 *	個別の頂点に対し、描画色の ID を設定します。
	 *	色そのものの設定は、 fk_Shape::setPalette() を参照して下さい。
	 *
	 *	\param[in]	vID		頂点ID
	 *	\param[in]	cID		色ID
	 */
	void			setColorID(int vID, int cID);

	//! 描画色設定有無参照関数
	/*!
	 *	点群の描画色設定の有無を取得します。
	 *
	 *	\return
	 *		1個以上の点に描画色が設定されている場合 true を、
	 *		1つも描画色が設定されていない場合に false を返します。
	 */
	bool			getColorCount(void);

	//! 描画色参照関数
	/*!
	 *	個別の頂点の描画色を取得します。
	 *
	 *	\param[in]	vID		頂点ID
	 *
	 *	\return
	 *		描画色が設定されている場合はその描画色 ID を返します。
	 *		描画色が設定されていない場合は -1 を返します。
	 *		頂点が存在しない場合は -2 を返します。
	 */
	int				getColorID(int vID);

	//! 点群全消去関数
	/*!
	 *	全ての頂点に関するデータを消去します。
	 *
	 *	\param[in]	matFlag
	 *		true の場合は、マテリアルパレットも初期化します。
	 *		false の場合は、マテリアルパレットに関しては消去しません。
	 */
	void			allClear(bool matFlag = true);
};

#endif // !__FK_POINT_HEADER__
