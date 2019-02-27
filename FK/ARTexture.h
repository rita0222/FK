#ifndef	__FK_AR_TEXTURE_HEADER__
#define	__FK_AR_TEXTURE_HEADER__

#include <FK/Texture.h>

namespace FK {

	//! AR用フォーマット型を表す列挙型
	enum fk_PixelFormatType {
		FK_DEFAULT_PIXEL_FORMAT = 0,	//!< RGBA
		FK_PIXEL_FORMAT_RGB		= 1,	//!< RGB
		FK_PIXEL_FORMAT_BGR		= 2,	//!< BGR
		FK_PIXEL_FORMAT_RGBA	= 3,	//!< RGBA
		FK_PIXEL_FORMAT_BGRA	= 4,	//!< GBRA
		FK_PIXEL_FORMAT_ABGR	= 5,	//!< ABGR
		FK_PIXEL_FORMAT_MONO	= 6,	//!< MONO
		FK_PIXEL_FORMAT_ARGB	= 7,	//!< ARGB
		FK_PIXEL_FORMAT_2vuy	= 8,	//!< 2vuy
		FK_PIXEL_FORMAT_yuvs	= 9		//!< yuvs
	};


	//! AR 投影映像用テクスチャクラス
	/*!
	 *	このクラスは、AR 利用時にカメラから得られた映像を、
	 *	FK 内でテクスチャデータとして利用できるようにするためのクラスです。
	 *
	 *	\sa fk_ARDevice
	 */
	class fk_ARTexture : public fk_Texture {
	private:

		unsigned char *		arVideoBuf;		// ARのバッファを保持
		fk_PixelFormatType	pixelFormatType;
		fk_Dimension		imageSize;
		fk_TexCoord			texSize;

		void				MakeFunction(void);

	public:
		//! コンストラクタ
		/*!
		 *	インスタンスを生成します。
		 *
		 *	\param[in]	image	fk_Image 型の内部データ格納用インスタンス。
		 *						引数を省略した場合は nullptr を代入した場合は、
		 *						内部で自動的に fk_Image 型のインスタンスが生成されます。
		 */
		fk_ARTexture(fk_Image *image = nullptr);

		//! デストラクタ
		~fk_ARTexture();

		//!	初期化関数
		void					init(void);

		//!	画像フォーマット設定関数
		/*!
		 *	内部画像データのフォーマットを設定します。
		 *
		 *	\param[in]	type	画像フォーマット
		 */
		void					setPixelFormatType(fk_PixelFormatType type);

		//!	画像フォーマット取得関数
		/*!
		 *	内部画像データのフォーマットを取得します。
		 *
		 *	\return フォーマットタイプ
		 */
		fk_PixelFormatType		getPixelFormatType(void) const;

		//!	テクスチャサイズ設定関数
		/*!
		 *	映像投影テクスチャのサイズを設定します。
		 *
		 *	\param[in]	x		x方向(横)幅
		 *	\param[in]	y		y方向(縦)幅
		 */
		void					setTextureSize(double x, double y);

		//!	テクスチャサイズ取得関数
		/*!
		 *	テクスチャサイズを取得します。
		 *
		 *	\return	テクスチャサイズ
		 */
		fk_TexCoord				getTextureSize(void) const;

		//!	映像更新関数
		/*!
		 *	テクスチャデータを現時点でカメラデバイスから取り込んでいるデータに更新します。
		 */
		void					update(void);


#ifndef FK_DOXYGEN_USER_PROCESS
		void					SetVideoBuf(unsigned char *, int, int);
#endif
	};
}

#endif	// !__FK_AR_TEXTURE_HEADER__


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
