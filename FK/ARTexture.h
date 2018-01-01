#ifndef	__FK_AR_TEXTURE_HEADER__
#define	__FK_AR_TEXTURE_HEADER__

#include <FK/Texture.h>

namespace FK {

	// ピクセルフォーマットタイプ for AR
	enum fk_PixelFormatType {
		FK_DEFAULT_PIXEL_FORMAT = 0,	// RGBA(FK Default)
		FK_PIXEL_FORMAT_RGB		= 1,	// RGB
		FK_PIXEL_FORMAT_BGR		= 2,	// BGR
		FK_PIXEL_FORMAT_RGBA	= 3,	// RGBA
		FK_PIXEL_FORMAT_BGRA	= 4,	// GBRA
		FK_PIXEL_FORMAT_ABGR	= 5,	// ABGR
		FK_PIXEL_FORMAT_MONO	= 6,	// MONO
		FK_PIXEL_FORMAT_ARGB	= 7,	// ARGB
		FK_PIXEL_FORMAT_2vuy	= 8,	// 2vuy
		FK_PIXEL_FORMAT_yuvs	= 9		// yuvs
	};

	class fk_ARTexture : public fk_Texture {
	private:

		unsigned char *		arVideoBuf;		// ARのバッファを保持
		fk_PixelFormatType	pixelFormatType;
		fk_Dimension		imageSize;
		fk_TexCoord			texSize;

	public:
		fk_ARTexture(fk_Image * = NULL);
		~fk_ARTexture();

		void					init(void);
		void					setVideoBuf(unsigned char *, int, int);
		unsigned char *			getVideoBuf(void) const;
		fk_Dimension			getVideoSize(void) const;
		void					setPixelFormatType(fk_PixelFormatType);
		fk_PixelFormatType		getPixelFormatType(void) const;
		void					setTextureSize(double, double);
		fk_TexCoord				getTextureSize(void) const;
		void					update(void);
	};
}

#endif	// !__FK_AR_TEXTURE_HEADER__
