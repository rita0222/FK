﻿#define FK_DEF_SIZETYPE
#include <FK/Texture.h>
#include <FK/Error.H>
#include <FK/Window.h>

using namespace std;
using namespace FK;

const string fk_Texture::texIDName = "fk_TexID";

fk_Texture::Member::Member(void) :
	image(nullptr),
	texMode(fk_TexMode::MODULATE),
	texRendMode(fk_TexRendMode::NORMAL),
	texWrapMode(fk_TexWrapMode::REPEAT),
	frameBuffer(nullptr)
{
	return;
}

fk_Texture::fk_Texture(fk_Image *argImage) :
	fk_Shape(fk_Type::TEXTURE),
	_m_texCoord(make_unique<fk_FVecArray>()),
	_m(make_unique<Member>())
{
	GetFaceSize = []() { return 0; };
	StatusUpdate = []() {};
	FaceIBOSetup = []() {};
	realType = fk_RealShapeType::TEXTURE;
	BaseInit();
	setImage(argImage);

	return;
}

fk_Texture::~fk_Texture()
{
	return;
}

void fk_Texture::BaseInit(void)
{
	setImage(nullptr);
	_m->frameBuffer = nullptr;
	clearMaterial();
	AttrInit();
	setTextureMode(fk_TexMode::MODULATE);
	setMaterialMode(fk_MaterialMode::PARENT);
	setTexRendMode(fk_TexRendMode::NORMAL);
	setTexWrapMode(fk_TexWrapMode::REPEAT);
	  
	return;
}

bool fk_Texture::IsLocalImage(void)
{
	return ((_m->image == &_m->localImage) ? true : false);
}

void fk_Texture::SetLocalImage(void)
{
	_m->image = &_m->localImage;
	StatusUpdate();
	return;
}

bool fk_Texture::readBMP(string argFileName)
{
	SetLocalImage();
	if(_m->image->readBMP(argFileName) == false) return false;
	StatusUpdate();
	return true;
}

bool fk_Texture::readBMPData(fk_ImType *argBuffer)
{
	SetLocalImage();
	if(_m->image->readBMPData(argBuffer) == false) return false;
	StatusUpdate();
	return true;
}

bool fk_Texture::readPNG(string argFileName)
{
	SetLocalImage();
	if(_m->image->readPNG(argFileName) == false) return false;
	StatusUpdate();
	return true;
}

bool fk_Texture::readPNGData(fk_ImType *argBuffer)
{
	SetLocalImage();
	if(_m->image->readPNGData(argBuffer) == false) return false;
	StatusUpdate();
	return true;
}

bool fk_Texture::readJPG(string argFileName)
{
	SetLocalImage();
	if(_m->image->readJPG(argFileName) == false) return false;
	StatusUpdate();
	return true;
}

const fk_ImType * fk_Texture::getImageBuf(void)
{
	if(_m->image != nullptr) {
		return _m->image->getBufPointer();
	}
	return nullptr;
}

void fk_Texture::setImage(fk_Image *argImage)
{
	if(_m->image == argImage) {
		return;
	}

	_m->image = argImage;
	StatusUpdate();
	return;
}

fk_Image * fk_Texture::getImage(void)
{
	return _m->image;
}

const fk_Dimension * fk_Texture::getImageSize(void)
{
	if(_m->frameBuffer != nullptr) {
		return _m->frameBuffer->getBufferSize();
	} else if(_m->image != nullptr) {
		return _m->image->getImageSize();
	}

	return nullptr;
}

const fk_Dimension * fk_Texture::getBufferSize(void)
{
	if(_m->frameBuffer != nullptr) {
		return _m->frameBuffer->getBufferSize();
	} else if(_m->image != nullptr) {
		return _m->image->getBufferSize();
	}

	return nullptr;
}

fk_TexID fk_Texture::GetTexID(void)
{
	if(_m->frameBuffer != nullptr) {
		return _m->frameBuffer->GetTexID();
	} else if(_m->image != nullptr) {
		return _m->image->GetTexID();
	}

	return 0;
}

void fk_Texture::SetTexID(fk_TexID argID)
{
	if(_m->image != nullptr) {
		_m->image->SetTexID(argID);
	}

	return;
}

void fk_Texture::ClearTexState(fk_Image *argImage)
{
	if(argImage == nullptr) return;

	argImage->SetUpdate(false);
	argImage->SetTexID(0);

	return;
}

void fk_Texture::setTextureMode(fk_TexMode argMode)
{
	_m->texMode = argMode;
	return;
}

fk_TexMode fk_Texture::getTextureMode(void)
{
	return _m->texMode;
}

void fk_Texture::setTexRendMode(fk_TexRendMode argMode)
{
	_m->texRendMode = argMode;
	return;
}

fk_TexRendMode fk_Texture::getTexRendMode(void)
{
	return _m->texRendMode;
}

void fk_Texture::setTexWrapMode(fk_TexWrapMode argMode)
{
	_m->texWrapMode = argMode;
	return;
}

fk_TexWrapMode fk_Texture::getTexWrapMode(void)
{
	return _m->texWrapMode;
}

void fk_Texture::fillColor(const fk_Color &argCol)
{
	if(_m->image == nullptr) return;

	_m->image->fillColor(argCol);
	return;
}

void fk_Texture::fillColor(int argR, int argG, int argB, int argA)
{
	if(_m->image == nullptr) return;

	_m->image->fillColor(argR, argG, argB, argA);
	return;
}

bool fk_Texture::BindTexture(bool forceLoad)
{
	bool loaded = true;

	if (_m->frameBuffer == nullptr && _m->image == nullptr) return false;

	const fk_Dimension	*bufSize = getBufferSize();
	if(bufSize == nullptr) return false;

	GLuint			id = GetTexID();

	if(id == 0) {
		glGenTextures(1, &id);
		_m->image->SetTexID(id);
		loaded = false;
	}

	glBindTexture(GL_TEXTURE_2D, id);

	GLint tmpWrapModeGl = (getTexWrapMode() == fk_TexWrapMode::REPEAT)
		? GL_REPEAT : GL_CLAMP_TO_EDGE;

	GLint tmpRendMode = (getTexRendMode() == fk_TexRendMode::NORMAL)
		? GL_NEAREST : GL_LINEAR;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tmpWrapModeGl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tmpWrapModeGl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tmpRendMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tmpRendMode);

	if (_m->frameBuffer == nullptr && (loaded == false || forceLoad == true)) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufSize->w, bufSize->h,
					 0, GL_RGBA, GL_UNSIGNED_BYTE, _m->image->getBufPointer());
	}

	return true;
}

void fk_Texture::Replace(void)
{
	if(_m->frameBuffer == nullptr && _m->image == nullptr) return;
	if(_m->frameBuffer != nullptr) {
		StatusUpdate();
		BindTexture(true);
	} else if(_m->image->GetUpdate() == true) {
		StatusUpdate();
		BindTexture(true);
		_m->image->SetUpdate(false);
	}
}

void fk_Texture::setFrameBuffer(fk_FrameBuffer *argFB)
{
	_m->frameBuffer = argFB;
}

fk_FrameBuffer * fk_Texture::getFrameBuffer(void)
{
	return _m->frameBuffer;
}

void fk_Texture::initFrameBuffer(void)
{
	_m->frameBuffer = nullptr;
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
