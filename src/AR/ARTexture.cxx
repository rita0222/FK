#include <FK/ARTexture.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_ARTexture::fk_ARTexture(fk_Image *argImage)
	: fk_Texture(argImage)
{
	SetObjectType(FK_ARTEXTURE);
	texSize.set(0.0, 0.0);
	pixelFormatType = FK_DEFAULT_PIXEL_FORMAT;
	SetLocalImage();
	MakeFunction();

	return;
}

fk_ARTexture::~fk_ARTexture()
{
	init();

	return;
}

void fk_ARTexture::MakeFunction(void)
{
	GenTextureObj = [this] {
		fk_PixelFormatType	type = getPixelFormatType();

		switch (type) {
		  case FK_PIXEL_FORMAT_RGB:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
						 imageSize.w, imageSize.h,
						 0, GL_RGB,
						 GL_UNSIGNED_BYTE,
						 arVideoBuf);
			break;
			
		  case FK_PIXEL_FORMAT_BGR:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
						 imageSize.w, imageSize.h,
						 0, GL_BGR,
						 GL_UNSIGNED_BYTE,
						 arVideoBuf);
			break;
			
		  case FK_PIXEL_FORMAT_RGBA:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
						 imageSize.w, imageSize.h,
						 0, GL_RGBA,
						 GL_UNSIGNED_BYTE,
						 arVideoBuf);
			break;
			
		  case FK_PIXEL_FORMAT_BGRA:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
						 imageSize.w, imageSize.h,
						 0, GL_BGRA,
						 GL_UNSIGNED_BYTE,
						 arVideoBuf);
			break;
			
		  case FK_PIXEL_FORMAT_MONO:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
						 imageSize.w, imageSize.h,
						 0, GL_LUMINANCE,
						 GL_UNSIGNED_BYTE,
						 arVideoBuf);
			break;
			
		  case FK_PIXEL_FORMAT_ARGB:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
						 imageSize.w, imageSize.h,
						 0, GL_BGRA,
						 GL_UNSIGNED_INT_8_8_8_8,
						 arVideoBuf);
			break;
			
		  case FK_PIXEL_FORMAT_2vuy:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
						 imageSize.w, imageSize.h,
						 0, GL_YCBCR_422_APPLE,
						 GL_UNSIGNED_SHORT_8_8_APPLE,
						 arVideoBuf);
			break;
			
		  case FK_PIXEL_FORMAT_yuvs:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
						 imageSize.w, imageSize.h,
						 0, GL_YCBCR_422_APPLE,
						 GL_UNSIGNED_SHORT_8_8_APPLE,
						 arVideoBuf);
			break;
			
		  default:
			break;			
		}
	};

	ReplaceSubImage = GenTextureObj;

	DrawTexture = [this](bool) {
		double			tmpX, tmpY;

		tmpX = texSize.x/2.0;
		tmpY = texSize.y/2.0;
	
		glNormal3d(0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
	
		glTexCoord2d(0.0, 0.0);
		glVertex3d(-tmpX, -tmpY, 0.0);
	
		glTexCoord2d(1.0, 0.0);
		glVertex3d(tmpX, -tmpY, 0.0);
	
		glTexCoord2d(1.0, 1.0);
		glVertex3d(tmpX, tmpY, 0.0);
	
		glTexCoord2d(0.0, 1.0);
		glVertex3d(-tmpX, tmpY, 0.0);

		glEnd();
	};
	return;
}

void fk_ARTexture::init(void)
{
	BaseInit();

	return;
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

void fk_ARTexture::SetVideoBuf(unsigned char *argVid, int argW, int argH)
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

