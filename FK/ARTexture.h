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
	};
}

#endif	// !__FK_AR_TEXTURE_HEADER__
