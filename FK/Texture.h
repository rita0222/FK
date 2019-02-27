#ifndef	__FK_TEXTURE_HEADER__
#define	__FK_TEXTURE_HEADER__

#include <FK/Shape.h>
#include <FK/Image.h>
#include <FK/IndexFace.h>

namespace FK {

	//! テクスチャモードを表す列挙型
	enum fk_TexMode {
		FK_TEX_MODULATE,	//!< 積算モード
		FK_TEX_REPLACE,		//!< 画像モード
		FK_TEX_DECAL		//!< 線形補間モード
	};

	//! テクスチャ描画品質を表す列挙型
	enum fk_TexRendMode {
		FK_TEX_REND_NORMAL,	//!< 標準品質
		FK_TEX_REND_SMOOTH	//!< 高品質
	};

	//! テクスチャ外周部の描画モードを表す列挙型
	enum fk_TexWrapMode {
		FK_TEX_WRAP_REPEAT,		//!< 繰り返し式
		FK_TEX_WRAP_CLAMP,		//!< 縁部伸張式
	};

	// フレームバッファのサンプリングソースを表す列挙型
	enum fk_SamplerSource {
		FK_TEXTURE_IMAGE,	//!< テクスチャ画像情報参照
		FK_COLOR_BUFFER,	//!< 画面色情報参照
		FK_DEPTH_BUFFER,	//!< 画面深度情報参照
	};

	//! テクスチャ用基底クラス
	/*!
	 *	このクラスは、テクスチャを表すクラスの基底クラスです。
	 *	様々なテクスチャクラスの共通機能を提供します。
	 *	クラス自体の主な機能はテクスチャ画像の生成や入力です。
	 *
	 *	\sa fk_Image, fk_RectTexture, fk_TriTexture, fk_MeshTexture, fk_IFSTexture, fk_Dimension
	 */

	class fk_Texture: public fk_Shape {
		friend class		fk_TextureDraw;

	public:

#ifndef FK_DOXYGEN_USER_PROCESS

		fk_Texture(fk_Image * = nullptr);
		virtual ~fk_Texture();
		virtual void			init(void) = 0;

#endif

		//! 画像データ設定関数
		/*!
		 *	画像データを設定します。
		 *
		 *	\note
		 *		fk_Texture (およびその派生クラス) では、
		 *		最初から自前の画像データ領域を保持しています。
		 *		この関数はあくまで外部で用意した画像データを
		 *		テクスチャとして利用したい場合に使用するためのものであり、
		 *		必ず設定しなければならないというわけではありません。
		 *
		 *	\param[in]		image		画像データ
		 */
		void					setImage(fk_Image *image);

		//! 画像データ取得関数
		/*!
		 *	現在設定されている画像データを取得します。
		 *
		 *	\return		画像データ
		 */
		fk_Image *				getImage(void);

		//! BMP ファイル入力関数
		/*!
		 *	BMP (Windows Bitmap) 形式のファイルからデータを読み込み、
		 *	テクスチャ画像として設定します。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\return	入力に成功すれば true、失敗すれば false を返します。
		 */
		bool					readBMP(std::string fileName);

		//! BMP バッファ入力関数
		/*!
		 *	BMP (Windows Bitmap) 形式のバッファからデータを読み込み、
		 *	テクスチャ画像として設定します。
		 *	fk_ImType 型は、OpenGL をサポートしている環境においては GLubyte、
		 *	サポートしていない環境では unsigned char 型として定義されています。
		 *
		 *	\param[in]	buf		データバッファ
		 *
		 *	\return 入力に成功すれば true、失敗すれば false を返します。
		 */
		bool					readBMPData(fk_ImType *buf);

		//! PNG ファイル入力関数
		/*!
		 *	PNG 形式のファイルからデータを読み込み、
		 *	テクスチャ画像として設定します。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\return	入力に成功すれば true、失敗すれば false を返します。
		 */
		bool					readPNG(std::string fileName);

		//! PNG バッファ入力関数
		/*!
		 * 	PNG 形式のバッファからデータを読み込み、
		 *	テクスチャ画像として設定します。
		 *	fk_ImType 型は、OpenGL をサポートしている環境においては GLubyte、
		 *	サポートしていない環境では unsigned char 型として定義されています。
		 *
		 *	\param[in]	buf		データバッファ
		 *
		 *	\return 入力に成功すれば true、失敗すれば false を返します。
		 */
		bool					readPNGData(fk_ImType *buf);

		//! JPEG ファイル入力関数
		/*!
		 *	JPEG 形式のファイルからデータを読み込み、
		 *	テクスチャ画像として設定します。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\return	入力に成功すれば true、失敗すれば false を返します。
		 */
		bool					readJPG(std::string fileName);

		//! 画像サイズ取得関数
		/*!
		 *	画像サイズを fk_Dimension 型で取得します。
		 *
		 *	\return		画像サイズ
		 *
		 *	\sa getBufferSize()
		 */
		const fk_Dimension *	getImageSize(void);

		//! 画像バッファサイズ取得関数
		/*!
		 *	実際に画像用データバッファとして確保されているサイズを、
		 *	fk_Dimension 型で返します。
		 *
		 *	\note
		 *		実画像サイズとデータバッファサイズの違いについては、
		 *		fk_Image::getBufferSize() の覚え書きを参照して下さい。
		 *
		 *	\return		データサイズ
		 *
		 *	\sa getImageSize(), fk_Image::getBufferSize()
		 */
		const fk_Dimension *	getBufferSize(void);

		//! テクスチャモード設定関数
		/*!
		 *	テクスチャの描画時における描画色処理モードを設定します。
		 *	これは、ポリゴンに設定されているマテリアルによる発色と、
		 *	テクスチャ画像の色をどのように混成するかを制御するものです。
		 *	それぞれのモードの概要と厳密な計算式を以下に記載します。
		 *	なお、数式中の \f$ C_f \f$ はポリゴン色、
		 *	\f$ C_\alpha \f$ ポリゴンの透明度、
		 *	\f$ T_f \f$ はテクスチャピクセル色、
		 *	\f$ T_\alpha \f$ はテクスチャの透明度を表します。
		 *
		 *	- FK_TEX_MODULATE \n
		 *		この設定では、ポリゴンの色とテクスチャの色を積算します。
		 *		そのため、光源による陰影効果が生じます。
		 *		透明度に関しても積算となります。
		 *		数式として表すと、色と透明度はそれぞれ
		 *		\f[
		 *			(C_f T_f, \; C_\alpha T_\alpha)
		 *		\f]
		 *		となります。
		 *
		 *	- FK_TEX_REPLACE \n
		 *		この設定では、ポリゴンの色は完全に無視され、
		 *		テクスチャのピクセル色がそのまま表示されます。
		 *		そのため、光源による陰影効果が生じません。
		 *		また、テクスチャ画像の透明度はそのまま描画に反映されます。
		 *		数式として表すと、色と透明度はそれぞれ
		 *		\f[
		 *			(T_f, \; T_\alpha)
		 *		\f]
		 *		となります。
		 *
		 *	- FK_TEX_DECAL \n
		 *		この設定では、各ピクセルの透明度に応じて、
		 *		ポリゴン色とピクセル色の混合が行われます。
		 *		光源による陰影効果は、ピクセルの透明度が低い場合に強くなります。
		 *		透明度は、ポリゴンの透明度がそのまま適用されます。
		 *		これを数式として表すと、色と透明度はそれぞれ
		 *		\f[
		 *			(C_f (1-T_\alpha) + T_f T_\alpha, \; C_\alpha)
		 *		\f]
		 *		となります。
		 *	.
		 *	なお、デフォルトでは FK_TEX_MODULATE が設定されています。
		 *
		 *	\param[in]		mode	モード
		 */
		void					setTextureMode(fk_TexMode mode);

		//! テクスチャモード取得関数
		/*!
		 *	現在のテクスチャモードを取得します。
		 *
		 *	\return		テクスチャモード
		 *
		 *	\sa setTextureMode()
		 */
		fk_TexMode				getTextureMode(void);

		//! テクスチャ描画品質設定関数
		/*!
		 *	テクスチャの描画品質を設定します。
		 *	設定可能なモードは以下の通りです。
		 *	- FK_TEX_REND_NORMAL: 標準品質。描画速度を優先します。
		 *	- FK_TEX_REND_SMOOTH: 高品質。画質を優先します。
		 *	.
		 *	なお、デフォルトでは FK_TEX_REND_NORMAL が設定されています。
		 *
		 *	\param[in]	mode	品質モード
		 */
		void					setTexRendMode(fk_TexRendMode mode);

		//! テクスチャ描画品質取得関数
		/*!
		 *	現在設定されているテクスチャ描画品質モードを取得します。
		 *
		 *	\return		品質モード
		 *
		 *	\sa setTexRendMode()
		 */
		fk_TexRendMode			getTexRendMode(void);

		//! テクスチャ外周部モード設定関数
		/*!
		 *	テクスチャ描画の際、外周部についてどのように描画するかを設定します。
		 *	設定できる種類は以下のとおりです。
		 *
		 *	- FK_TEX_WRAP_REPEAT: 内部の画像を繰り返して描画していきます。
		 *	- FK_TEX_WRAP_CLAMP: 縁部の色値を伸張して描画します。
		 *	.
		 *	なお、デフォルトでは FK_TEX_WRAP_REPEAT に設定されています。
		 *
		 *	\param[in]	mode	外周部モード
		 */
		void					setTexWrapMode(fk_TexWrapMode mode);

		//! テクスチャ外周部モード取得関数
		/*!
		 *	現在設定されているテクスチャ外周部モードを取得します。
		 *
		 *	\return		外周部モード
		 */
		fk_TexWrapMode			getTexWrapMode(void);
	
		//! 一様色初期化関数1
		/*!
		 *	内部の画像ピクセルを、すべて同じ色で初期化します。
		 *
		 *	\param[in]	color		初期化色
		 *
		 *	\sa fk_Color
		 */
		void					fillColor(const fk_Color &color);

		//! 一様色初期化関数2
		/*!
		 *	内部の画像ピクセルを、すべて同じ色で初期化します。
		 *	色要素は、最小値が 0, 最大値が 255 として解釈します。
		 *
		 *	\param[in]	r		初期化色の赤要素
		 *	\param[in]	g		初期化色の緑要素
		 *	\param[in]	b		初期化色の青要素
		 *	\param[in]	a		初期化色の透明度要素
		 */
		void					fillColor(int r, int g, int b, int a = 0);

		//! 画像データ配列先頭アドレス取得関数	
		/*!
		 *	画像データを実際に格納しているデータ配列の先頭アドレスを参照します。
		 *
		 *	\warning
		 *		この関数は fk_Image の内部構造に強く依存します。
		 *		内部構造は今後の更新で変更される可能性があるため、
		 *		本関数を用いた場合は後方互換性が保証できません。
		 *		また、この関数を用いて得た内部データを更新した場合、
		 *		システム全体の整合性が維持できなくなる可能性があります。
		 *		上記の2点の理由から、この関数の利用は推奨しません。
		 *
		 *	\return
		 *		画像データ配列の先頭アドレス。
		 *		テクスチャ画像が生成、設定されていない場合は nullptr を返します。
		 *
		 *	\sa fk_Image::getBufPointer()
		 */
		const fk_ImType *		getImageBuf(void);

		//! テクスチャ参照情報設定関数
		/*!
		 *	参照テクスチャが参照する情報を設定します。
		 *	設定できる種類は以下のとおりです。
		 *
		 *	- FK_TEXTURE_IMAGE: 
		 *		コンストラクタで設定した
		 *		fk_Image 型インスタンスに入っているデータを参照先とします。
		 *	- FK_COLOR_BUFFER: 
		 *		描画シーン全体の色値情報を参照先とします。
		 *	- FK_DEPTH_BUFFER: 
		 *		描画シーン全体の深度情報を参照先とします。
		 *	.
		 *	デフォルトは FK_TEXTURE_IMAGE に設定されています。
		 *
		 *	\param[in]	mode
		 *		テクスチャ参照情報の参照先
		 *
		 *	\sa getSamplerSource()
		 */
		void setSamplerSource(fk_SamplerSource mode);

		//! テクスチャ参照情報参照関数
		/*!
		 *	参照テクスチャが参照する情報を参照します。
		 *
		 *	\return		テクスチャ参照情報
		 */
		fk_SamplerSource getSamplerSource(void);

#ifndef FK_DOXYGEN_USER_PROCESS
		bool BindTexture(bool forceLoad);
		std::function<int(void)> GetFaceSize;
		std::function<void(void)> StatusUpdate;


		static const std::string		texIDName;

#endif

	protected:

		void				BaseInit(void);
		bool				IsLocalImage(void);
		void				SetLocalImage(void);
		bool				GetInitFlag(void);
		void				SetInitFlag(bool);
		void				FaceIBOSetup(void);

//		std::function<void(void)>	GenTextureObj;
//		std::function<void(void)>	ReplaceSubImage;
//		std::function<void(bool)>	DrawTexture;
//		std::function<void(void)>	DrawPick;


		fk_FVecArray			vertexPosition;
		fk_FVecArray			vertexNormal;
		fk_FVecArray			texCoord;
		std::vector<GLuint>		faceIndex;		
		GLuint					faceIBO;
		bool					faceIndexFlg;

	private:
		fk_Image			*image;
		fk_Image			localImage;
		fk_TexMode			texMode;
		fk_TexRendMode		texRendMode;
		fk_TexWrapMode		texWrapMode;
		fk_Palette			localPal;
		fk_SamplerSource	samplerSource;

		fk_TexID			GetTexID(void);
		void				SetTexID(const fk_TexID);
		static void			ClearTexState(fk_Image *);
		//void				MakeObjFunction(void);
	};
}

#endif	// !__FK_TEXTURE_HEADER__

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
