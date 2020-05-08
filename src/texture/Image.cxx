#define FK_DEF_SIZETYPE
#include <FK/Image.h>
#include <FK/TextureDraw.H>

using namespace std;
using namespace FK;

fk_Dimension::fk_Dimension(int argW, int argH)
{
	set(argW, argH);
}

fk_Dimension::fk_Dimension(const fk_Dimension &argDim)
{
	w = argDim.w;
	h = argDim.h;
}

void fk_Dimension::set(int argW, int argH)
{
	w = argW;
	h = argH;
	return;
}

fk_Rect::fk_Rect(int argX, int argY, int argW, int argH)
{
	set(argX, argY, argW, argH);
}

fk_Rect::fk_Rect(const fk_Rect &argRect)
{
	set(argRect.x, argRect.y, argRect.w, argRect.h);
}

void fk_Rect::set(int argX, int argY, int argW, int argH)
{
	x = argX;
	y = argY;
	w = argW;
	h = argH;
	return;
}

void fk_Rect::setPos(int argX, int argY)
{
	x = argX;
	y = argY;
	return;
}

void fk_Rect::setSize(int argW, int argH)
{
	w = argW;
	h = argH;
	return;
}

fk_Dimension fk_Rect::getSize(void)
{
	fk_Dimension retDim(w, h);

	return retDim;
}

fk_Image::Member::Member(void) :
	bufPointer(nullptr), texID(0), updateFlg(true)
{
	return;
}
		
fk_Image::fk_Image(int argW, int argH) : _m(make_unique<Member>())
{
	SetObjectType(fk_Type::IMAGE);
	CreateBuffer(argW, argH, true);
	
	return;
}

fk_Image::~fk_Image()
{
	ReleaseTexture();
	return;
}

fk_Image::fk_Image(const fk_Image &argImg)
	: fk_BaseObject()
{
	copyImage(&argImg);
}

void fk_Image::init(void)
{
	_m->imageSize.w = 0;
	_m->imageSize.h = 0;
	_m->bufSize.w = 0;
	_m->bufSize.h = 0;
	_m->imageBuf.clear();
	_m->bufPointer = nullptr;
	SetUpdate(true);
	ReleaseTexture();

	return;
}

void fk_Image::ReleaseTexture(void)
{
	if(_m->texID != 0) {
#ifndef FK_CLI_CODE		
		glDeleteTextures(1, &_m->texID);
#endif		
		_m->texID = 0;
	}
}	

unsigned int fk_Image::ChgUInt(unsigned char *argBuf, int argOffset) const
{
	unsigned int retVal = (unsigned int)(argBuf[argOffset+3]) * 256 * 256 * 256;
	retVal += (unsigned int)(argBuf[argOffset+2]) * 256 * 256;
	retVal += (unsigned int)(argBuf[argOffset+1]) * 256;
	retVal += (unsigned int)(argBuf[argOffset]);

	return retVal;
}

unsigned int fk_Image::ChgUShort(fk_ImType *argBuf, int argOffset) const
{
	unsigned int retVal = (unsigned int)(argBuf[argOffset+1]) * 256;
	retVal += (unsigned int)(argBuf[argOffset]);

	return retVal;
}

int fk_Image::GetOffset(int argX, int argY) const
{
	return (((_m->imageSize.h - argY - 1)*_m->bufSize.w + argX)*4);
}

fk_ImType fk_Image::RoundVal(int argVal) const
{
	if(argVal > 255) return 255;
	if(argVal < 0) return 0;
	return (fk_ImType)argVal;
}

fk_ImageStatus fk_Image::CreateImg(const string argFile)
{
	init();

	if(argFile == "") {
		_m->imageSize.w = _m->imageSize.h = 0;
		return fk_ImageStatus::OK;
	}

	if(IsBmpFile(argFile) == true) {

		// Windows Bitmap

		SetUpdate(true);
		fk_ImageStatus status = LoadBmpFile(argFile);
		switch(status) {
		  case fk_ImageStatus::OPENERROR:
		  case fk_ImageStatus::DATAERROR:
		  case fk_ImageStatus::READERROR:
			return status;
		  default:
			break;
		}
		return fk_ImageStatus::OK;
	}

	return fk_ImageStatus::DATAERROR;
}

void fk_Image::CreateBuffer(bool argInitFlg)
{
	CreateBuffer(0, 0, argInitFlg);
	return;
}

fk_ImageStatus fk_Image::CreateImg(fk_ImType *argBuffer)
{
	init();

	if(argBuffer == nullptr) {
		_m->imageSize.w = _m->imageSize.h = 0;
		return fk_ImageStatus::OK;
	}

	if(IsBmpData(argBuffer) == true) {

		// Windows Bitmap

		fk_ImageStatus status = LoadBmpData(argBuffer);
		switch(status) {
		  case fk_ImageStatus::OPENERROR:
		  case fk_ImageStatus::DATAERROR:
		  case fk_ImageStatus::READERROR:
			return status;
		  default:
			break;
		}
		return fk_ImageStatus::OK;
	}

	return fk_ImageStatus::DATAERROR;
}

void fk_Image::CreateBuffer(const fk_Dimension argDim, bool argInitFlg)
{
	CreateBuffer(argDim.w, argDim.h, argInitFlg);
	return;
}

void fk_Image::CreateBuffer(int argW, int argH, bool argInitFlg)
{
	if(argW <= 0 || argH <= 0) {
		init();
		return;
	}

	int tmpBufSizeW = GetFixVal(fk_ImageFix::FIX_LARGE, argW);
	int tmpBufSizeH = GetFixVal(fk_ImageFix::FIX_LARGE, argH);

	if(tmpBufSizeW != _m->bufSize.w || tmpBufSizeH != _m->bufSize.h) {
		init();
	} else {
		SetUpdate(true);
	}

	_m->imageSize.set(argW, argH);
	_m->bufSize.set(tmpBufSizeW, tmpBufSizeH);

	if(_m->bufPointer == nullptr) {
		_st bSize = _st(_m->bufSize.w) * _st(_m->bufSize.h) * 4;
		_m->imageBuf.resize(bSize);
		_m->bufPointer = &_m->imageBuf[0];
	}

	if(argInitFlg == true) fillColor(0, 0, 0, 0);

	return;
}

bool fk_Image::IsPixelStatus(int argX, int argY) const
{
	if(_m->imageBuf.empty() == true ||
	   argX < 0 || argY < 0 ||
	   argX >= _m->imageSize.w || argY >= _m->imageSize.h) {
		return false;
	}

	return true;
}

int fk_Image::GetOneBufferSize(int argType, int argXRes)
{
	int tmpSize = 0;

	switch(argType) {
	  case 1:
	  case 4:
	  case 8:

		tmpSize = (argXRes*argType)/8;
		while((tmpSize % 4) != 0) {
			tmpSize++;
		}
		break;

	  case 24:
	  case 32:

		tmpSize = (argXRes*argType)/8;
		while((tmpSize % 4) != 0) {
			tmpSize++;
		}
		break;

	  default:
		return -1;
	}

	return tmpSize;
}

void fk_Image::SetLong2Byte(long argNum, fk_ImType *argBuffer, int argOffset)
{
	long tmp = argNum;
	int v1 = int(tmp / (256 * 256 * 256));
	tmp %= (256 * 256 * 256);
	int v2 = int(tmp / (256 * 256));
	tmp %= (256 * 256);
	int v3 = int(tmp / 256);
	int v4 = int(tmp % 256);

	argBuffer[argOffset + 3] = fk_ImType(v1);
	argBuffer[argOffset + 2] = fk_ImType(v2);
	argBuffer[argOffset + 1] = fk_ImType(v3);
	argBuffer[argOffset] = fk_ImType(v4);

	return;
}

void fk_Image::SetInt2Byte(int argNum, fk_ImType *argBuffer, int argOffset)
{
	int v1 = argNum / 256;
	int v2 = argNum % 256;

	argBuffer[argOffset + 1] = fk_ImType(v1);
	argBuffer[argOffset] = fk_ImType(v2);

	return;
}

void fk_Image::newImage(int argW, int argH, bool argInitFlg)
{
	CreateBuffer(argW, argH, argInitFlg);
	return;
}

void fk_Image::copyImage(const fk_Image *argImage)
{
	if(argImage == this || argImage == nullptr) return;

	init();

	if(argImage->_m->bufSize.w > 0 && argImage->_m->bufSize.h > 0) {
		CreateBuffer(argImage->_m->imageSize, true);
		memcpy(&_m->imageBuf[0], &argImage->_m->imageBuf[0],
			   _st(_m->bufSize.w) * _st(_m->bufSize.h) * 4);
	}
	SetUpdate(true);

	return;
}

void fk_Image::copyImage(const fk_Image *argImage, int argX, int argY)
{
	if(argX < 0 || argY < 0) return;

	if(argX + argImage->_m->imageSize.w > _m->imageSize.w ||
	   argY + argImage->_m->imageSize.h > _m->imageSize.h) {
		return;
	}

	for(int i = 0; i < argImage->_m->imageSize.h; i++) {
		_st		off1, off2;
		off1 = _st(GetOffset(argX, argY + i));
		off2 = _st(argImage->GetOffset(0, i));
		memmove(&_m->imageBuf[off1],
				&argImage->_m->imageBuf[off2],
				_st(argImage->_m->imageSize.w) * 4);
	}

	SetUpdate(true);

	return;
}


bool fk_Image::subImage(const fk_Image *argImage,
						int argX, int argY, int argW, int argH)
{
	if(argImage == nullptr) return false;
	if(argImage == this) return false;

	if(argX < 0 || argY < 0 || argW <= 0 || argH <= 0) return false;

	int orgW = argImage->getWidth();
	int orgH = argImage->getHeight();

	if(orgW < argX + argW || orgH < argY + argH) return false;

	CreateBuffer(argW, argH, true);

	for(int i = 0; i < argH; i++) {
		_st index1 = _st(GetOffset(0, i));
		_st index2 = _st(argImage->GetOffset(argX, argY + i));
		memcpy(&_m->imageBuf[index1],
			   &argImage->_m->imageBuf[index2],
			   _st(argW) * 4);
	}

	SetUpdate(true);

	return true;
}

int fk_Image::getWidth(void) const
{
	return _m->imageSize.w;
}

int fk_Image::getHeight(void) const
{
	return _m->imageSize.h;
}

const fk_Dimension * fk_Image::getImageSize(void)
{
	return &_m->imageSize;
}

const fk_Dimension * fk_Image::getBufferSize(void)
{
	return &_m->bufSize;
}

int fk_Image::getR(int argX, int argY) const
{
	if(!IsPixelStatus(argX, argY)) {
		return -1;
	}

	return _m->imageBuf[_st(GetOffset(argX, argY))];
}

int fk_Image::getG(int argX, int argY) const
{
	if(!IsPixelStatus(argX, argY)) {
		return -1;
	}

	return _m->imageBuf[_st(GetOffset(argX, argY)) + 1];
}

int fk_Image::getB(int argX, int argY) const
{
	if(!IsPixelStatus(argX, argY)) {
		return -1;
	}

	return _m->imageBuf[_st(GetOffset(argX, argY)) + 2];
}

int fk_Image::getA(int argX, int argY) const
{
	if(!IsPixelStatus(argX, argY)) {
		return -1;
	}

	return (_m->imageBuf[_st(GetOffset(argX, argY)) + 3]);
}

fk_Color fk_Image::getColor(int argX, int argY) const
{
	fk_Color col(0.0, 0.0, 0.0);

	if(!IsPixelStatus(argX, argY)) {
		return col;
	}

	_st offset = _st(GetOffset(argX, argY));
	col.setR(float(_m->imageBuf[offset])/255.0f);
	col.setG(float(_m->imageBuf[offset+1])/255.0f);
	col.setB(float(_m->imageBuf[offset+2])/255.0f);
	col.setA(float(_m->imageBuf[offset+3])/255.0f);

	return col;
}

bool fk_Image::setRGBA(int argX, int argY,
					   int argR, int argG, int argB, int argA)
{
	if(!IsPixelStatus(argX, argY)) {
		return false;
	}

	_st offset = _st(GetOffset(argX, argY));
	_m->imageBuf[offset] = RoundVal(argR);
	_m->imageBuf[offset+1] = RoundVal(argG);
	_m->imageBuf[offset+2] = RoundVal(argB);
	_m->imageBuf[offset+3] = RoundVal(argA);

	SetUpdate(true);

	return true;
}

bool fk_Image::setRGB(int argX, int argY,
					  int argR, int argG, int argB)
{
	return setRGBA(argX, argY, argR, argG, argB, 255);
}

bool fk_Image::setR(int argX, int argY, int argR)
{
	if(!IsPixelStatus(argX, argY)) {
		return false;
	}

	_m->imageBuf[_st(GetOffset(argX, argY))] = RoundVal(argR);

	SetUpdate(true);

	return true;
}

bool fk_Image::setG(int argX, int argY, int argG)
{
	if(!IsPixelStatus(argX, argY)) {
		return false;
	}

	_m->imageBuf[_st(GetOffset(argX, argY))+1] = RoundVal(argG);

	SetUpdate(true);

	return true;
}

bool fk_Image::setB(int argX, int argY, int argB)
{
	if(!IsPixelStatus(argX, argY)) {
		return false;
	}

	_m->imageBuf[_st(GetOffset(argX, argY))+2] = RoundVal(argB);

	SetUpdate(true);

	return true;
}

bool fk_Image::setA(int argX, int argY, int argA)
{
	if(!IsPixelStatus(argX, argY)) {
		return false;
	}

	_m->imageBuf[_st(GetOffset(argX, argY))+3] = RoundVal(argA);

	SetUpdate(true);

	return true;
}

bool fk_Image::setColor(int argX, int argY, const fk_Color &argCol)
{
	if(!IsPixelStatus(argX, argY)) {
		return false;
	}

	_st offset = _st(GetOffset(argX, argY));
	_m->imageBuf[offset] = fk_ImType((double(argCol.getR()) + fk_Math::EPS)*255.0);
	_m->imageBuf[offset+1] = fk_ImType((double(argCol.getG()) + fk_Math::EPS)*255.0);
	_m->imageBuf[offset+2] = fk_ImType((double(argCol.getB()) + fk_Math::EPS)*255.0);
	_m->imageBuf[offset+3] = fk_ImType((double(argCol.getA()) + fk_Math::EPS)*255.0);

	SetUpdate(true);

	return true;
}

const fk_ImType * fk_Image::getBufPointer(void) const
{
	return _m->bufPointer;
}

int fk_Image::GetFixVal(fk_ImageFix argFix, int argSize) const
{
	int trueVal = 0;

	switch(argFix) {
	  case fk_ImageFix::FIX_SMALL:
		for(trueVal = 64; trueVal <= 65536; trueVal *= 2) {
			if(trueVal*2 > argSize) break;
		}

		break;

	  case fk_ImageFix::FIX_LARGE:
		for(trueVal = 64; trueVal <= 65536; trueVal *= 2) {
			if(trueVal >= argSize) break;
		}

		break;

	  case fk_ImageFix::FIX_64:
		trueVal = 64;
		break;

	  case fk_ImageFix::FIX_128:
		trueVal = 128;
		break;

	  case fk_ImageFix::FIX_256:
		trueVal = 256;
		break;

	  case fk_ImageFix::FIX_512:
		trueVal = 512;
		break;

	  case fk_ImageFix::FIX_1024:
		trueVal = 1024;
		break;

	  case fk_ImageFix::FIX_2048:
		trueVal = 2048;
		break;

	  case fk_ImageFix::FIX_4096:
		trueVal = 4096;
		break;

	  case fk_ImageFix::FIX_8192:
		trueVal = 8192;
		break;

	  case fk_ImageFix::FIX_16384:
		trueVal = 16384;
		break;

	  case fk_ImageFix::FIX_32768:
		trueVal = 32768;
		break;

	  case fk_ImageFix::FIX_65536:
		trueVal = 65536;
		break;

	  default:
		break;
	}

	return trueVal;
}

bool fk_Image::GetUpdate(void)
{
	return _m->updateFlg;
}

void fk_Image::SetUpdate(bool argFlg)
{
	_m->updateFlg = argFlg;
	return;
}

fk_TexID fk_Image::GetTexID(void)
{
	return _m->texID;
}

void fk_Image::SetTexID(const fk_TexID argID)
{
	_m->texID = argID;
	return;
}

void fk_Image::fillColor(const fk_Color &argCol)
{
	fillColor(int((double(argCol.getR()) + fk_Math::EPS)*255.0),
			  int((double(argCol.getG()) + fk_Math::EPS)*255.0),
			  int((double(argCol.getB()) + fk_Math::EPS)*255.0),
			  int((double(argCol.getA()) + fk_Math::EPS)*255.0));
	return;
}

void fk_Image::fillColor(int argR, int argG, int argB, int argA)
{
	if(argR < 0 || argR > 255 ||
	   argG < 0 || argG > 255 ||
	   argB < 0 || argB > 255 ||
	   argA < 0 || argA > 255) {

		return;
	}

	for(_st i = 0; i < _st(_m->bufSize.w) * _st(_m->bufSize.h); i++) {
		_m->imageBuf[4*i] = fk_ImType(argR);
		_m->imageBuf[4*i+1] = fk_ImType(argG);
		_m->imageBuf[4*i+2] = fk_ImType(argB);
		_m->imageBuf[4*i+3] = fk_ImType(argA);
	}

	SetUpdate(true);

	return;
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
