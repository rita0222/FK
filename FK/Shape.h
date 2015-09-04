#ifndef __FK_SHAPEBASE_HEADER__
#define __FK_SHAPEBASE_HEADER__

#include <FK/Base.h>
#include <FK/Palette.h>
#include <FK/Attribute.h>

//! 形状データの具体的なデータ構造を表す列挙型
enum fk_RealShapeType {
	FK_SHAPE_IFS,		//!<	fk_IndexFaceSetベース
	FK_SHAPE_SOLID,		//!<	fk_Solidベース
	FK_SHAPE_TEXTURE,	//!<	fk_Textureベース
	FK_SHAPE_POINT,		//!<	fk_Pointベース
	FK_SHAPE_LIGHT,		//!<	fk_Lightベース
	FK_SHAPE_OTHER		//!<	その他
};

//! 形状用基底クラス
/*!
 *	このクラスは、形状を表すクラスの基底クラスです。
 *	クラス自体の主な機能は、マテリアルやパレットの管理です。
 *
 *	\sa fk_Material, fk_Palette
 */

class fk_Shape: public fk_Attribute {

 private:
	fk_Palette			*palette;
	fk_MaterialMode		materialMode;

 public:
	//! コンストラクタ
	fk_Shape(fk_ObjectType = FK_SHAPE);
	//! デストラクタ
	virtual ~fk_Shape();

	//!	形状データ構造取得関数
	/*!
	 *
	 *	格納されているインスタンスの具体的なデータ構造を取得します。
	 *
	 *	\return		格納データ構造
	 */
	fk_RealShapeType				getRealShapeType(void);

	//! パレット取得関数
	/*!
	 *	パレットのアドレスを取得します。
	 *
	 *	\return	パレット
	 */
	fk_Palette *					getPaletteData(void);

	//! パレット初期化関数
	/*!
	 *	現在設定されているパレットを初期化します。
	 *
	 *	\sa fk_Palette::clearMaterial()
	 */
	void							clearMaterial(void);

	//! オブジェクトマテリアル ID 設定関数
	/*!
	 *	オブジェクトマテリアルの ID を設定します。
	 *
	 *	\param[in]	ID		オブジェクトマテリアルの ID。
	 *
	 *	\sa getObjMaterialID()
	 *	\sa fk_Palette::setObjMaterialID()
	 */
	void							setObjMaterialID(int ID);

	//! マテリアル追加関数
	/*!
	 *	パレットにマテリアルを新たに追加します。
	 *
	 *	\param[in]	mat		追加するマテリアル変数のアドレス
	 *
	 *	\sa fk_Palette::pushPalette(), setPalette()
	 */
	void							pushPalette(fk_Material &mat);

	//! マテリアル設定関数
	/*!
	 *	パレットに対し、対応する ID でマテリアルを設定します。
	 *	詳細な仕様は fk_Palette::setPalette() を参照して下さい。
	 *
	 *	\param[in]	mat		設定するマテリアル
	 *	\param[in]	ID		マテリアルID
	 *
	 *	\sa fk_Palette::setPalette(), pushPalette()
	 */
	void							setPalette(fk_Material &mat, int ID);

	//! マテリアルモード設定関数
	/*!
	 *	形状中の各要素を描画する際に、どの要素のマテリアルを採用するかを設定します。
	 *	マテリアルの採用は、以下のような優先順で決定します。
	 *	-# fk_Model のマテリアルモードが FK_CHILD_MODE の場合、
	 *		モデルのマテリアルが採用されます。
	 *		FK_NONE_MODE の場合は描画されません。
	 *		FK_PARENT_MODE の場合は以下の条件に従います。
	 *		(fk_Model::setMaterialMode() を参照して下さい。)
	 *	-# fk_Shape の派生クラスにてマテリアルモードが
	 *		FK_CHILD_MODE になっている場合、形状のマテリアルが採用されます。
	 *		FK_NONE_MODE の場合は描画されません。
	 *		FK_PARENT_MODE の場合は以下の条件に従います。
	 *	-# 各位相要素でのマテリアルモードが、
	 *		FK_CHILD_MODE になっている場合は個別のマテリアルが採用されます。
	 *		FK_NONE_MODE の場合は描画されません。
	 *		FK_PARENT_MODE の場合はモデルのマテリアルが採用されます。
	 *		(fk_TopologyMaterial::setElemMaterialMode() を参照して下さい。)
	 *
	 *	\param[in]	mode
	 *		マテリアルモードを設定します。与えられる値は以下の3種類です。
	 *		\arg FK_CHILD_MODE
	 *		\arg FK_PARENT_MODE
	 *		\arg FK_NONE_MODE
	 *
	 *	\sa getMaterialMode(), fk_Model::setMaterialMode(), fk_TopologyMaterial::setElemMaterialMode()
	 */
	void							setMaterialMode(fk_MaterialMode mode);


	//! マテリアルモード取得関数
	/*!
	 *	マテリアルモードを取得します。
	 *
	 *	\return マテリアルモード
	 *
	 *	\sa setMaterialMode()
	 */
	fk_MaterialMode					getMaterialMode(void);

	//! オブジェクトマテリアル ID 取得関数
	/*!
	 *	現在設定されているオブジェクトマテリアルの ID を取得します。
	 *
	 *	\return オブジェクトマテリアルの ID
	 *
	 *	\sa setObjMaterialID(), fk_Palette::getObjMaterialID()
	 */
	int								getObjMaterialID(void);

	//! パレット中のマテリアル格納数取得関数
	/*!
	 *	現在パレットに格納されているマテリアルの数を返します。
	 *
	 *	\return マテリアル数
	 *
	 *	\sa pushPalette(), setPalette(), getMaterial(), fk_Palette::getPaletteSize()
	 */
	int								getPaletteSize(void);

	//! マテリアル取得関数
	/*!
	 *	指定された id に対応するマテリアルのポインタを返します。
	 *	id に対応するマテリアルがパレット中にない場合は、
	 * 	デフォルト状態のマテリアルインスタンスへのポインタを返します。
	 *
	 *	\return マテリアルのポインタ
	 *
	 *	\sa pushPalette(), setPalette(), getPaletteSize(), fk_Palette::getMaterial()
	 */
	fk_Material *					getMaterial(int id);

	//! マテリアル配列取得関数
	/*!
	 *	パレットに格納されているマテリアルを、
	 *	STL の vector 配列へのポインタとして返します。
	 *
	 *	\return マテリアル配列
	 *
	 *	\sa getMaterial(), fk_Palette::getMaterialVector()
	 */
	std::vector<fk_Material> *		getMaterialVector(void);

#ifndef FK_DOXYGEN_USER_PROCESS

	void							SetPaletteData(fk_Palette *pal);
	void							setPaletteData(fk_Palette *pal);

#endif
};

#endif // !__FK_SHAPEBASE_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
