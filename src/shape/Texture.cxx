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
#define FK_DEF_SIZETYPE
#include <FK/Texture.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_Texture::fk_Texture(fk_Image *argImage)
	: fk_Shape(FK_TEXTURE)
{
	SetPaletteData(&localPal);
	image = nullptr;
	BaseInit();
	setImage(argImage);

	return;
}

fk_Texture::~fk_Texture()
{
	BaseInit();

	return;
}

void fk_Texture::BaseInit(void)
{
	setImage(nullptr);
	clearMaterial();
	AttrInit();
	setTextureMode(FK_TEX_MODULATE);
	setMaterialMode(FK_PARENT_MODE);
	setTexRendMode(FK_TEX_REND_NORMAL);
	setTexWrapMode(FK_TEX_WRAP_REPEAT);
	MakeObjFunction();

	return;
}

void fk_Texture::MakeObjFunction(void)
{
	GenTextureObj = [this] {
		const fk_ImType		*imageBuf = image->getBufPointer();
		const fk_Dimension	*bufSize = image->getBufferSize();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufSize->w, bufSize->h,
					 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuf);
	};

	ReplaceSubImage = [this] {

		if(image == nullptr) return;

		static fk_Rect				tmpRect;	// 部分更新矩形情報
		static vector<fk_ImType>	subBuffer;	// 部分更新用バッファ
		const fk_Dimension			*imageSize = image->getImageSize();
		const fk_Dimension			*bufSize = image->getBufferSize();
		const fk_ImType				*imageBuf = image->getBufPointer();

		// 更新領域取得
		tmpRect = image->GetUpdateArea();
		if(tmpRect.w < 1 || tmpRect.h < 1) {	// 矩形が指定されていなかったら全体更新
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, bufSize->w, bufSize->h,
							GL_RGBA, GL_UNSIGNED_BYTE, imageBuf);
		} else {	// 指定されていたら部分更新
			subBuffer.resize(static_cast<_st>(tmpRect.w*tmpRect.h*4));
			for(int i = 0; i < tmpRect.h; ++i) {
				memcpy(&(subBuffer[static_cast<_st>((tmpRect.h-i-1)*tmpRect.w*4)]),
					   imageBuf+((imageSize->h - (tmpRect.y+i) - 1)*bufSize->w + tmpRect.x)*4,
					   static_cast<size_t>(tmpRect.w*4));
			}
			if(!subBuffer.empty()) {
				glTexSubImage2D(GL_TEXTURE_2D, 0, tmpRect.x,
								imageSize->h - tmpRect.h - tmpRect.y,
								tmpRect.w, tmpRect.h,
								GL_RGBA, GL_UNSIGNED_BYTE, &(subBuffer[0]));
			}
		}
	};
}

bool fk_Texture::IsLocalImage(void)
{
	return ((image == &localImage) ? true : false);
}

void fk_Texture::SetLocalImage(void)
{
	image = &localImage;
	return;
}

bool fk_Texture::readBMP(string argFileName)
{
	SetLocalImage();
	return image->readBMP(argFileName);
}

bool fk_Texture::readBMPData(fk_ImType *argBuffer)
{
	SetLocalImage();
	return image->readBMPData(argBuffer);
}

bool fk_Texture::readPNG(string argFileName)
{
	SetLocalImage();
	return image->readPNG(argFileName);
}

bool fk_Texture::readPNGData(fk_ImType *argBuffer)
{
	SetLocalImage();
	return image->readPNGData(argBuffer);
}

bool fk_Texture::readJPG(string argFileName)
{
	SetLocalImage();
	return image->readJPG(argFileName);
}

const fk_ImType * fk_Texture::getImageBuf(void)
{
	if(image != nullptr) {
		return image->getBufPointer();
	}
	return nullptr;
}

void fk_Texture::setImage(fk_Image *argImage)
{
	if(image == argImage) {
		return;
	}

	image = argImage;
	return;
}

fk_Image * fk_Texture::getImage(void)
{
	return image;
}

const fk_Dimension * fk_Texture::getImageSize(void)
{
	if(image != nullptr) {
		return image->getImageSize();
	}

	return nullptr;
}

const fk_Dimension * fk_Texture::getBufferSize(void)
{
	if(image != nullptr) {
		return image->getBufferSize();
	}

	return nullptr;
}

bool fk_Texture::GetInitFlag(void)
{
	if(image != nullptr) {
		return image->GetInitFlag();
	}

	return false;
}

void fk_Texture::SetInitFlag(bool argFlg)
{
	if(image != nullptr) {
		image->SetInitFlag(argFlg);
	}

	return;
}

fk_TexID fk_Texture::GetTexID(void)
{
	if(image != nullptr) {
		return image->GetTexID();
	}

	return 0;
}

void fk_Texture::SetTexID(fk_TexID argID)
{
	if(image != nullptr) {
		image->SetTexID(argID);
	}

	return;
}

void fk_Texture::ClearTexState(fk_Image *argImage)
{
	if(argImage == nullptr) return;

	argImage->SetInitFlag(false);
	argImage->SetTexID(0);

	return;
}

void fk_Texture::setTextureMode(fk_TexMode argMode)
{
	texMode = argMode;
	return;
}

fk_TexMode fk_Texture::getTextureMode(void)
{
	return texMode;
}

void fk_Texture::setTexRendMode(fk_TexRendMode argMode)
{
	texRendMode = argMode;
	return;
}

fk_TexRendMode fk_Texture::getTexRendMode(void)
{
	return texRendMode;
}

void fk_Texture::setTexWrapMode(fk_TexWrapMode argMode)
{
	texWrapMode = argMode;
	return;
}

fk_TexWrapMode fk_Texture::getTexWrapMode(void)
{
	return texWrapMode;
}

void fk_Texture::fillColor(const fk_Color &argCol)
{
	if(image == nullptr) return;

	image->fillColor(argCol);
	return;
}

void fk_Texture::fillColor(int argR, int argG, int argB, int argA)
{
	if(image == nullptr) return;

	image->fillColor(argR, argG, argB, argA);
	return;
}

fk_RectTexture::fk_RectTexture(fk_Image *argImage)
	: fk_Texture(argImage)
{
	SetObjectType(FK_RECTTEXTURE);
	texSize.set(2.0, 2.0);
	setRepeatMode(false);
	repeatParam.set(1.0, 1.0);
	texCoord[0].set(0.0, 0.0);
	texCoord[1].set(1.0, 1.0);

	return;
}

fk_RectTexture::~fk_RectTexture()
{
	init();

	return;
}

void fk_RectTexture::init(void)
{
	BaseInit();

	return;
}

bool fk_RectTexture::setTextureSize(double argX, double argY)
{
	if(argX < -FK_EPS || argY < -FK_EPS) {
		return false;
	}

	texSize.set(argX, argY);

	return true;
}

fk_TexCoord fk_RectTexture::getTextureSize(void)
{
	return texSize;
}

void fk_RectTexture::setRepeatMode(bool argFlag)
{
	repeatFlag = argFlag;
	return;
}

bool fk_RectTexture::getRepeatMode(void)
{
	return repeatFlag;
}

void fk_RectTexture::setRepeatParam(double argS, double argT)
{
	repeatParam.set(argS, argT);
	return;
}

fk_TexCoord fk_RectTexture::getRepeatParam(void)
{
	return repeatParam;
}

void fk_RectTexture::setTextureCoord(double argSU, double argSV,
									 double argEU, double argEV)
{
	if(argSU < -FK_EPS || argSU > 1.0 + FK_EPS ||
	   argSV < -FK_EPS || argSV > 1.0 + FK_EPS ||
	   argEU < -FK_EPS || argEU > 1.0 + FK_EPS ||
	   argEV < -FK_EPS || argEV > 1.0 + FK_EPS) {
		fk_PutError("fk_RectTexture", "setTextureCoord", 1,
					"Texture Coord Error.");
		return;
	}

	texCoord[0].set(argSU, argSV);
	texCoord[1].set(argEU, argEV);

	return;
}

void fk_RectTexture::setTextureCoord(const fk_TexCoord &argS,
									 const fk_TexCoord &argE)
{
	if(argS.x < -FK_EPS || argS.x > 1.0 + FK_EPS ||
	   argS.y < -FK_EPS || argS.y > 1.0 + FK_EPS ||
	   argE.x < -FK_EPS || argE.x > 1.0 + FK_EPS ||
	   argE.y < -FK_EPS || argE.y > 1.0 + FK_EPS) {
		fk_PutError("fk_RectTexture", "setTextureCoord", 2,
					"Texture Coord Error.");
		return;
	}

	texCoord[0].set(argS.x, argS.y);
	texCoord[1].set(argE.x, argE.y);
	return;
}

fk_TexCoord fk_RectTexture::getTextureCoord(int argID)
{
	if(argID < 0 || argID > 1) {
		fk_PutError("fk_RectTexture", "getTextureCoord", 1, "ID Error");
		return fk_TexCoord(0.0, 0.0);
	}
	return texCoord[argID];
}

fk_TriTexture::fk_TriTexture(fk_Image *argImage)
	: fk_Texture(argImage)
{
	SetObjectType(FK_TRITEXTURE);

	return;
}

fk_TriTexture::~fk_TriTexture()
{
	init();

	return;
}

void fk_TriTexture::init(void)
{
	BaseInit();

	return;
}

fk_Vector * fk_TriTexture::getPos(void)
{
	return &pos[0];
}

fk_TexCoord * fk_TriTexture::getCoord(void)
{
	return &texCoord[0];
}

bool fk_TriTexture::setVertexPos(int argID,
								 double argX, double argY, double argZ)
{
	if(argID < 0 || argID > 2) {
		fk_PutError("fk_TriTexture", "setVertexPos", 1, "ID Error.");
		return false;
	}

	pos[argID].set(argX, argY, argZ);
	return true;
}

bool fk_TriTexture::setVertexPos(int argID, fk_Vector argPos)
{
	if(argID < 0 || argID > 2) {
		fk_PutError("fk_TriTexture", "setVertexPos", 2, "ID Error.");
		return false;
	}

	pos[argID] = argPos;
	return true;
}

bool fk_TriTexture::setTextureCoord(int argID, double argS, double argT)
{
	if(argID < 0 || argID > 2) {
		fk_PutError("fk_TriTexture", "setTextureCoord", 1, "ID Error.");
		return false;
	}

	if(argS < -FK_EPS || argS > 1.0 + FK_EPS ||
	   argT < -FK_EPS || argT > 1.0 + FK_EPS) {
		fk_PutError("fk_TriTexture", "setTextureCoord", 2,
					"Texture Coord Error.");
		return false;
	}

	texCoord[argID].set(argS, argT);
	return true;
}


bool fk_TriTexture::setTextureCoord(int argID, fk_TexCoord argCoord)
{
	if(argID < 0 || argID > 2) {
		fk_PutError("fk_TriTexture", "setTextureCoord", 3, "ID Error.");
		return false;
	}

	if(argCoord.x < -FK_EPS || argCoord.x > 1.0 + FK_EPS ||
	   argCoord.y < -FK_EPS || argCoord.y > 1.0 + FK_EPS) {
		fk_PutError("fk_TriTexture", "setTextureCoord", 4,
					"Texture Coord Error.");
		return false;
	}

	texCoord[argID].set(argCoord.x, argCoord.y);
	return true;
}

fk_Vector fk_TriTexture::getVertexPos(int argID)
{
	fk_Vector		dummy(0.0, 0.0, 0.0);

	if(argID < 0 || argID > 2) {
		fk_PutError("fk_TriTexture", "getVertexPos", 1, "ID Error.");
		return dummy;
	}

	return pos[argID];
}

fk_TexCoord fk_TriTexture::getTextureCoord(int argID)
{
	fk_TexCoord		dummy(0.0, 0.0);

	if(argID < 0 || argID > 2) {
		fk_PutError("fk_TriTexture", "getTextureCoord", 1, "ID Error.");
		return dummy;
	}

	return texCoord[argID];
}
