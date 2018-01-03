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
	return;
}

fk_ARTexture::~fk_ARTexture()
{
	init();

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
	
	if(argVid != NULL){
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
