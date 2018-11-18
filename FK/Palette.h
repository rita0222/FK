#ifndef __FK_PALETTE_HEADER__
#define __FK_PALETTE_HEADER__

#include <FK/Material.h>
#include <vector>

namespace FK {

	//! マテリアルモード型
	using fk_MaterialMode = unsigned char;

	const fk_MaterialMode	FK_NONE_MODE = 0;		//!< 不描画モード
	const fk_MaterialMode	FK_CHILD_MODE = 1;		//!< 個別設定モード
	const fk_MaterialMode	FK_PARENT_MODE = 2;		//!< モデル設定モード

	//! マテリアルパレットを管理するクラス
	/*!
	 *	このクラスは、マテリアルパレットを制御する機能を提供します。
	 *	「マテリアルパレット」とは、複数のマテリアルを管理するデータベースのことです。
	 *	水彩や油彩で使う「パレット」のような機能を保持しており、
	 *	複数のマテリアルを登録することができます。
	 *
	 *	\sa fk_Material, fk_Color, fk_Shape
	 */

	class fk_Palette : public fk_BaseObject {
	public:

		//! コンストラクタ
		fk_Palette(void);

		//! デストラクタ
		virtual ~fk_Palette();

		//! 初期化関数
		/*!
		 *	パレットを初期化します。
		 */
		void						clearMaterial(void);

		//! オブジェクトマテリアル ID 設定関数
		/*!
		 *	オブジェクトマテリアルの ID を設定します。
		 *
		 *	\param[in]	ID		オブジェクトマテリアルの ID。
		 *
		 *	\sa getObjMaterialID()
		 */
		void						setObjMaterialID(int ID);

		//! マテリアル追加関数
		/*!
		 *	パレットにマテリアルを新たに追加します。
		 *	追加するマテリアルの ID は、
		 *	この関数を呼ぶ前に getPaletteSize() 関数を呼ぶことで得られます。
		 *	以下のコードは、マテリアルを追加しその ID を引数に代入します。
		 *
		 *		fk_Palette		pal;
		 *		fk_Material		mat;
		 *		int				id;
		 *		
		 *		id = pal.getPaletteSize();
		 *		pal.pushPalette(&mat);
		 *
		 *	\param[in]	mat		追加するマテリアル変数のアドレス
		 *
		 *	\sa setPalette()
		 */
		void						pushPalette(fk_Material *mat);

		//! マテリアル設定関数
		/*!
		 *	パレットに対し、対応する ID でマテリアルを設定します。
		 *	ID の指定により、以下のように挙動が若干変わります。
		 *	- もし ID が負であった場合は、パレットは何も変化しません。
		 *	- もし ID で指定されているマテリアルが既にパレット中に存在する場合は、
		 *		旧マテリアルを破棄して新しいマテリアルで上書きします。
		 *	- もし ID が新規のものであった場合、
		 *		その ID で新たに登録します。
		 *	.
		 *
		 *	\param[in]	mat		設定するマテリアル
		 *	\param[in]	ID		マテリアルID
		 *
		 *	\sa pushPalette()
		 */
		void						setPalette(fk_Material *mat, int ID);

		//! オブジェクトマテリアル ID 取得関数
		/*!
		 *	現在設定されているオブジェクトマテリアルの ID を取得します。
		 *
		 *	\return オブジェクトマテリアルの ID
		 *
		 *	\sa setObjMaterialID()
		 */
		int							getObjMaterialID(void);

		//! パレット中のマテリアル格納数取得関数
		/*!
		 *	現在パレットに格納されているマテリアルの数を返します。
		 *
		 *	\return マテリアル数
		 *
		 *	\sa pushPalette(), setPalette(), getMaterial()
		 */
		int							getPaletteSize(void);

		//! マテリアル取得関数
		/*!
		 *	指定された ID に対応するマテリアルのポインタを返します。
		 *	
		 *	\param[in]	ID		マテリアルID
		 *
		 *	\return
		 *		対象マテリアルのポインタ。
		 *		ID に対応するマテリアルがパレット中にない場合は、
		 *		デフォルト状態のマテリアルインスタンスへのポインタを返します。
		 *
		 *	\sa pushPalette(), setPalette(), getPaletteSize()
		 */
		fk_Material *				getMaterial(int ID);

		//! マテリアル配列取得関数
		/*!
		 *	パレットに格納されているマテリアルを、
		 *	STL の vector 配列へのポインタとして返します。
		 *
		 *	\return マテリアル配列
		 *
		 *	\sa getMaterial()
		 */
		std::vector<fk_Material> *	getMaterialVector(void);

#ifndef FK_DOXYGEN_USER_PROCESS

		void						Print(int, std::string = "");
		void						Resize(int);

#endif

	private:
		int							thisColorID;
		std::vector<fk_Material>	paletteStack;
	};
}

#endif // __FK_PALETTE_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
