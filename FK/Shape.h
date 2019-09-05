/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_SHAPE_BASE_HEADER__
#define __FK_SHAPE_BASE_HEADER__

#include <FK/Base.h>
#include <FK/Palette.h>
#include <FK/Attribute.h>
#include <FK/Vector.h>
#include <FK/OpenGL.H>
#include <map>
#include <functional>

namespace FK {

	const int FK_SHAPE_ALIVE = 1;
	const int FK_SHAPE_DEAD = 2;

	using shapeAttrI = std::tuple<int, int, std::vector<int> *>;
	using shapeAttrF = std::tuple<int, int, std::vector<float> *>;

	using shapeMapI = std::map<std::string, shapeAttrI>;
	using shapeMapF = std::map<std::string, shapeAttrF>;

	//! 形状データの具体的なデータ構造を表す列挙型
	enum fk_RealShapeType {
		FK_SHAPE_IFS,		//!<	fk_IndexFaceSetベース
		FK_SHAPE_SOLID,		//!<	fk_Solidベース
		FK_SHAPE_TEXTURE,	//!<	fk_Textureベース
		FK_SHAPE_POINT,		//!<	fk_Pointベース
		FK_SHAPE_LINE,		//!<	fk_Lineベース
		FK_SHAPE_CURVE,		//!<	fk_Curveベース
		FK_SHAPE_SURFACE,	//!<	fk_Surface ベース
		FK_SHAPE_LIGHT,		//!<	fk_Lightベース
		FK_SHAPE_OTHER		//!<	その他
	};

	//! 形状用基底クラス
	/*!
	 *	このクラスは、形状を表すクラスの基底クラスです。
	 *	クラス自体の主な機能は、マテリアルの管理です。
	 *
	 *	\sa fk_Material
	 */

	class fk_Shape: public fk_Attribute {

	public:
		//! コンストラクタ
		fk_Shape(fk_Type = fk_Type::SHAPE);
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

		//! シェーダー内 attribute 変数設定関数1
		/*!
		 *	形状の各頂点に対応した attribute 変数値を整数型で登録します。
		 *
		 *	ここで登録する要素数は形状の頂点数、
		 *	厳密にはデータ要素数よりも多数である必要があります。
		 *
		 *	\param[in]	name
		 *		GLSL内での変数名
		 *
		 *	\param[in]	dim
		 *		変数の次元数で、1から4まで設定することができます。
		 *		GLSL内での型は、1から順に int, ivec2, ivec3, ivec4 となります。
		 *
		 *	\param[in]	array
		 *		attribute 変数として転送するデータのポインタ。
		 *		このコンテナのサイズは、形状の頂点数と次元数の積以上である必要があります。
		 *
		 *	\param[in]	self
		 *		この引数が true の場合、
		 *		GPUに転送するデータ領域はインスタンスの内部に新たに確保されます。
		 *		その場合は本関数を使用後、array で指定した領域は解放しても問題ありません。
		 *		ただし、領域確保とデータコピーのため動作は遅くなります。
		 *		この引数が false の場合は、
		 *		GPUに転送するデータ領域として array をそのまま利用するため、
		 *		本関数利用後に array を解放するとプログラムが異常終了する恐れがあります。
		 *		本引数を省略した場合は false を指定したことと同義となります。
		 *
		 *	\note
		 *	   	ここで設定した attribute 変数用データに変更があった場合で、
		 *		self が false だった場合は、
		 *		再度本関数を呼ぶよりも modifyAttribute() を呼ぶ方が高速に処理が行えます。
		 *		self が true だった場合は、 modifyAttribute() を呼んでも
		 *		変更は反映されませんので、再度本関数を呼び出す必要があります。
		 */
		void setShaderAttribute(std::string name, int dim,
								std::vector<int> *array, bool self = false);

		//! シェーダー内 attribute 変数設定関数2
		/*!
		 *	形状の各頂点に対応した attribute 変数値を浮動小数点型で登録します。
		 *
		 *	ここで登録する要素数は形状の頂点数、
		 *	厳密にはデータ要素数よりも多数である必要があります。
		 *
		 *	\param[in]	name
		 *		GLSL内での変数名
		 *
		 *	\param[in]	dim
		 *		変数の次元数で、1から4まで設定することができます。
		 *		GLSL内での型は、1から順に float, vec2, vec3, vec4 となります。
		 *
		 *	\param[in]	array
		 *		attribute 変数として転送するデータのポインタ。
		 *		このコンテナのサイズは、形状の頂点数と次元数の積以上である必要があります。
		 *
		 *	\param[in]	self
		 *		この引数が true の場合、
		 *		GPUに転送するデータ領域はインスタンスの内部に新たに確保されます。
		 *		その場合は本関数を使用後、array で指定した領域は解放しても問題ありません。
		 *		ただし、領域確保とデータコピーのため動作は遅くなります。
		 *		この引数が false の場合は、
		 *		GPUに転送するデータ領域として array をそのまま利用するため、
		 *		本関数利用後に array を解放するとプログラムが異常終了する恐れがあります。
		 *		本引数を省略した場合は false を指定したことと同義となります。
		 *
		 *	\note
		 *	   	ここで設定した attribute 変数用データに変更があった場合で、
		 *		self が false だった場合は、
		 *		再度本関数を呼ぶよりも modifyAttribute() を呼ぶ方が高速に処理が行えます。
		 *		self が true だった場合は、 modifyAttribute() を呼んでも
		 *		変更は反映されませんので、再度本関数を呼び出す必要があります。
		 */
		void setShaderAttribute(std::string name, int dim,
								std::vector<float> *array, bool self = false);

		//! シェーダー内 attribute 変数設定関数3
		/*!
		 *	形状の各頂点に対応した attribute 変数値を fk_Vector 型で登録します。
		 *
		 *	ここで登録する要素数は形状の頂点数、
		 *	厳密にはデータ要素数よりも多数である必要があります。
		 *
		 *	\param[in]	name
		 *		GLSL内での変数名
		 *
		 *	\param[in]	dim
		 *		変数の次元数で、1から4まで設定することができます。
		 *		GLSL内での型は、1から順に float, vec2, vec3, vec4 となります。
		 *		1 を指定した場合、y,z 成分は無視されます。
		 *		2 を指定した場合、z 成分は無視されます。
		 *		4 を指定した場合、第4成分 (w成分) は 0 となります。
		 *
		 *	\param[in]	array
		 *		attribute 変数として転送するデータのポインタ。
		 *		このコンテナのサイズは、形状の頂点数と次元数の積以上である必要があります。
		 *
		 *	\note
		 *	   	ここで設定した attribute 変数用データに変更があった場合は、
		 *		再度本関数を呼び出す必要があります。
		 *		modifyAttribute() を呼び出しても変更は反映されないので、注意して下さい。
		 */
		void setShaderAttribute(std::string name, int dim, std::vector<fk_Vector> *array);

		//! シェーダー内 attribute 変数設定関数4
		/*!
		 *	形状の各頂点に対応した attribute 変数値を fk_TexCoord 型で登録します。
		 *
		 *	ここで登録する要素数は形状の頂点数、
		 *	厳密にはデータ要素数よりも多数である必要があります。
		 *
		 *	\param[in]	name
		 *		GLSL内での変数名
		 *
		 *	\param[in]	dim
		 *		変数の次元数で、1から4まで設定することができます。
		 *		GLSL内での型は、1から順に float, vec2, vec3, vec4 となります。
		 *		1 を指定した場合、y 成分は無視されます。
		 *		3,4 を指定した場合、第3,4成分 (z,w成分) は 0 となります。
		 *
		 *	\param[in]	array
		 *		attribute 変数として転送するデータのポインタ。
		 *		このコンテナのサイズは、形状の頂点数と次元数の積以上である必要があります。
		 *
		 *	\note
		 *	   	ここで設定した attribute 変数用データに変更があった場合は、
		 *		再度本関数を呼び出す必要があります。
		 *		modifyAttribute() を呼び出しても変更は反映されないので、注意して下さい。
		 */
		void setShaderAttribute(std::string name, int dim, std::vector<fk_TexCoord> *array);

		//! シェーダー内 attribute 変数設定関数5
		/*!
		 *	形状の各頂点に対応した attribute 変数値を fk_HVector 型で登録します。
		 *
		 *	ここで登録する要素数は形状の頂点数、
		 *	厳密にはデータ要素数よりも多数である必要があります。
		 *
		 *	\param[in]	name
		 *		GLSL内での変数名
		 *
		 *	\param[in]	dim
		 *		変数の次元数で、1から4まで設定することができます。
		 *		GLSL内での型は、1から順に float, vec2, vec3, vec4 となります。
		 *		1 を指定した場合は y,z,w 成分は無視されます。
		 *		2 を指定した場合は z,w 成分は無視されます。
		 *		3 を指定した場合は、w 成分は無視されま。
		 *
		 *	\param[in]	array
		 *		attribute 変数として転送するデータのポインタ。
		 *		このコンテナのサイズは、形状の頂点数と次元数の積以上である必要があります。
		 *
		 *	\note
		 *	   	ここで設定した attribute 変数用データに変更があった場合は、
		 *		再度本関数を呼び出す必要があります。
		 *		modifyAttribute() を呼び出しても変更は反映されないので、注意して下さい。
		 */
		void setShaderAttribute(std::string name, int dim, std::vector<fk_HVector> *array);

		//! attribute 変数更新関数
		/*!
		 *	attribute 変数用データに変更があった場合、
		 *	この関数を呼ぶ必要があります。この関数が呼ばれると、
		 *	対象となる attribute 変数用のデータは描画時に CPU から GPU へデータの転送が行われます。
		 * 	もしこの関数が呼ばれないと、内部データが変更されても描画には反映されません。
		 *
		 *	\param[in]	name		対象となる attribute 変数の GLSL 内での変数名
		 *
		 *	\note
		 *		本関数は、 setShaderAttribute(std::string, int, std::vector<int> *, bool) または
		 *		setShaderAttribute(std::string, int, std::vector<float> *, bool) で
		 *		第4引数に false を用いた場合のみに有効です。
		 *		第4引数に true を用いた場合や、その他の形式の attribute 変数設定に対しては、
		 *		本関数によって変更反映を行うことはできません。
		 */
		void modifyAttribute(std::string name);

#ifndef FK_DOXYGEN_USER_PROCESS

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

		void FinishSetVBO(void);
		virtual void ForceUpdateAttr(void);
		std::function<void(void)> FlushAttr;

		void	SetPaletteData(fk_Palette *pal);
		void	setPaletteData(fk_Palette *pal);

		void			SetPointVAO(GLuint);
		void			SetLineVAO(GLuint);
		void			SetFaceVAO(GLuint);
		GLuint			GetPointVAO(void);
		GLuint			GetLineVAO(void);
		GLuint			GetFaceVAO(void);

		void			DefineVBO(void);
		void			BindShaderBuffer(std::map<std::string, int> *);

		static GLuint	GenBuffer(void);
		static void		DeleteBuffer(GLuint);

		// シェーダー変数名: 頂点座標
		static const std::string	vertexName;
		static const std::string	normalName;

		// シェーダー変数名: 頂点モデル色
		static const std::string	pointModelColorName;
		static const std::string	pointElementColorName;
		static const std::string	pointElementAliveName;

		static const std::string	lineModelColorName;
		static const std::string	lineElementColorName;

		static const std::string	curveModelColorName;

		// シェーダー変数名: テクスチャ座標
		static const std::string	texCoordName;

		// シェーダー変数名: 曲線曲面
		static const std::string	ctrlPosName;
		static const std::string	degreeName;		

#endif

	private:
		fk_Palette			*palette;
		fk_Palette			defaultPalette;
		fk_MaterialMode		materialMode;
		GLuint				pointVAO, lineVAO, faceVAO;

		shapeMapI 			attrMapI;
		shapeMapF 			attrMapF;

		bool				vboInitFlg;

		std::map<std::string, bool>		attrModify;

		std::map<std::string, std::vector<int> *>	intSelf;
		std::map<std::string, std::vector<float> *> floatSelf;

		void			DeleteMapI(std::string);
		void			DeleteMapF(std::string);

	protected:
		fk_RealShapeType	realType;
	};
}

#endif // !__FK_SHAPE_BASE_HEADER__


