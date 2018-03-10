#include <FK/ARTexture.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_ARTexture::fk_ARTexture(fk_Image *argImage)
	: fk_Texture(argImage)
{
	SetObjectType(FK_ARTEXTURE);
	arVideoBuf = nullptr;
	imageSize.set(0, 0);
	texSize.set(0.0, 0.0);
	pixelFormatType = FK_DEFAULT_PIXEL_FORMAT;
	SetLocalImage();
	MakeGenFunction();

	return;
}

fk_ARTexture::~fk_ARTexture()
{
	init();

	return;
}

void fk_ARTexture::MakeGenFunction(void)
{
	GenTextureObj = [this] {
		fk_Dimension			bufSize = getVideoSize();
		const unsigned char		*arImageBuf = getVideoBuf();
		fk_PixelFormatType		type = getPixelFormatType();

		switch (type) {
		  case FK_PIXEL_FORMAT_RGB:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
						 bufSize.w, bufSize.h,
						 0, GL_RGB,
						 GL_UNSIGNED_BYTE,
						 arImageBuf);
			break;
			
		  case FK_PIXEL_FORMAT_BGR:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
						 bufSize.w, bufSize.h,
						 0, GL_BGR,
						 GL_UNSIGNED_BYTE,
						 arImageBuf);
			break;
			
		  case FK_PIXEL_FORMAT_RGBA:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
						 bufSize.w, bufSize.h,
						 0, GL_RGBA,
						 GL_UNSIGNED_BYTE,
						 arImageBuf);
			break;
			
		  case FK_PIXEL_FORMAT_BGRA:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
						 bufSize.w, bufSize.h,
						 0, GL_BGRA,
						 GL_UNSIGNED_BYTE,
						 arImageBuf);
			break;
			
		  case FK_PIXEL_FORMAT_MONO:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
						 bufSize.w, bufSize.h,
						 0, GL_LUMINANCE,
						 GL_UNSIGNED_BYTE,
						 arImageBuf);
			break;
			
		  case FK_PIXEL_FORMAT_ARGB:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
						 bufSize.w, bufSize.h,
						 0, GL_BGRA,
						 GL_UNSIGNED_INT_8_8_8_8,
						 arImageBuf);
			break;
			
		  case FK_PIXEL_FORMAT_2vuy:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
						 bufSize.w, bufSize.h,
						 0, GL_YCBCR_422_APPLE,
						 GL_UNSIGNED_SHORT_8_8_APPLE,
						 arImageBuf);
			break;
			
		  case FK_PIXEL_FORMAT_yuvs:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
						 bufSize.w, bufSize.h,
						 0, GL_YCBCR_422_APPLE,
						 GL_UNSIGNED_SHORT_8_8_APPLE,
						 arImageBuf);
			break;
			
		  default:
			break;			
		}
	};

	ReplaceSubImage = GenTextureObj;
	// =====================================================================
	return;
}

void fk_ARTexture::init(void)
{
	BaseInit();

	return;
}

void fk_ARTexture::setVideoBuf(unsigned char *argVid, int argW, int argH)
{
	imageSize.set(argW, argH);
	
	setTextureMode(FK_TEX_REPLACE);
	
	if(argVid != nullptr) {
		arVideoBuf = argVid;
	}else{
		fk_PutError("VideoBUffer NULL!");
	}
	return;
}

unsigned char * fk_ARTexture::getVideoBuf(void) const
{
	return arVideoBuf;
}

fk_Dimension fk_ARTexture::getVideoSize(void) const
{
	return imageSize;
}

void fk_ARTexture::setPixelFormatType(fk_PixelFormatType argType)
{
	pixelFormatType = argType;
	return;
}

fk_PixelFormatType fk_ARTexture::getPixelFormatType(void) const
{
	return pixelFormatType;
}

void fk_ARTexture::setTextureSize(double argX, double argY)
{
	texSize.set(argX, argY);
	return;
}

fk_TexCoord fk_ARTexture::getTextureSize(void) const
{
	return texSize;
}

void fk_ARTexture::update(void)
{
	SetInitFlag(true);
	return;
}
