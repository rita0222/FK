/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#include <map>
#include <algorithm>
#include <FK/TextImage.h>
#include <FK/Error.H>
#include <ft2build.h>

using namespace std;

#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H

// rita: UTF-16 における空白コード
const unsigned int SP_1BYTE = 0x0020;
const unsigned int SP_2BYTE = 0x3000;

class fk_GlyphStatus {
private:
	FT_Face		face;
	FT_UInt		index, code;
	int			ptsize, dpi, strength;

public:
	fk_GlyphStatus(void);
	fk_GlyphStatus(const fk_GlyphStatus &);
	~fk_GlyphStatus();

	bool				operator ==(const fk_GlyphStatus &) const;
	bool				operator >(const fk_GlyphStatus &) const;
	bool				operator <(const fk_GlyphStatus &) const;
	fk_GlyphStatus &	operator =(const fk_GlyphStatus &);

	void		Init(void);
	void		Set(FT_Face, FT_UInt, int, int, int);
	FT_UInt		GetIndex(void) const;
	FT_UInt		GetCode(void) const;
};

class fk_FTGlyph {
 public:
	fk_GlyphStatus			status;
	FT_Pos					xOffset;
	FT_BBox					bbox;

	fk_FTGlyph(void);
	~fk_FTGlyph();

	void		Init(void);
};

class fk_FontServer {
 private:
	FT_Library				library;
	map<string, FT_Face>	faceArray;

 public:
	fk_FontServer(void);
	~fk_FontServer();

	FT_Face					GetFace(string);
};

class fk_GlyphCache {
public:
	FT_BBox					bbox;
	fk_GlyphBuffer			*buffer;
};

class fk_GlyphServer {
private:
	map<fk_GlyphStatus, fk_GlyphCache *>	glyphArray;

public:
	fk_GlyphServer(void);
	~fk_GlyphServer();

	void				Clear(void);
	void				MakeCache(const fk_GlyphStatus &, const FT_BBox &);
	fk_GlyphBuffer *	GetBuffer(const fk_GlyphStatus &);
	FT_BBox *			GetBBox(const fk_GlyphStatus &);
	bool				IsArive(const fk_GlyphStatus &) const;
};

class fk_FTFace {
public:
	FT_Face		face;

	fk_FTFace(void);
	~fk_FTFace();
};

fk_GlyphStatus::fk_GlyphStatus(void)
{
	Init();
	return;
}

fk_GlyphStatus::fk_GlyphStatus(const fk_GlyphStatus &argStatus)
{
	face = argStatus.face;
	index = argStatus.index;
	code = argStatus.code;
	strength = argStatus.strength;
	ptsize = argStatus.ptsize;
	dpi = argStatus.dpi;
}

fk_GlyphStatus::~fk_GlyphStatus()
{
	return;
}

bool fk_GlyphStatus::operator ==(const fk_GlyphStatus &argStatus) const
{
	if(face == argStatus.face &&
	   index == argStatus.index &&
	   code == argStatus.code &&
	   strength == argStatus.strength &&
	   ptsize == argStatus.ptsize &&
	   dpi == argStatus.dpi) {
		return true;
	}

	return false;
}

bool fk_GlyphStatus::operator >(const fk_GlyphStatus &argStatus) const
{
	if(index > argStatus.index) return true;
	if(index < argStatus.index) return false;
	if(code > argStatus.code) return true;
	if(code < argStatus.code) return false;
	if(face > argStatus.face) return true;
	if(face < argStatus.face) return false;
	if(strength > argStatus.strength) return true;
	if(strength < argStatus.strength) return false;
	if(ptsize > argStatus.ptsize) return true;
	if(ptsize < argStatus.ptsize) return false;
	if(dpi > argStatus.dpi) return true;

	return false;
}

bool fk_GlyphStatus::operator <(const fk_GlyphStatus &argStatus) const
{
	if(index < argStatus.index) return true;
	if(index > argStatus.index) return false;
	if(code < argStatus.code) return true;
	if(code > argStatus.code) return false;
	if(face < argStatus.face) return true;
	if(face > argStatus.face) return false;
	if(strength < argStatus.strength) return true;
	if(strength > argStatus.strength) return false;
	if(ptsize < argStatus.ptsize) return true;
	if(ptsize > argStatus.ptsize) return false;
	if(dpi < argStatus.dpi) return true;

	return false;
}

fk_GlyphStatus & fk_GlyphStatus::operator =(const fk_GlyphStatus &argStatus)
{
	face = argStatus.face;
	index = argStatus.index;
	code = argStatus.code;
	strength = argStatus.strength;
	ptsize = argStatus.ptsize;
	dpi = argStatus.dpi;

	return *this;
}

void fk_GlyphStatus::Init(void)
{
	Set(nullptr, 0, 0, 0, 1);
	return;
}

void fk_GlyphStatus::Set(FT_Face argFace, FT_UInt argCode,
						 int argPTSize, int argDPI, int argStrength)
{
	face = argFace;
	code = argCode;
	strength = argStrength;
	ptsize = argPTSize;
	dpi = argDPI;

	if(argCode != 0) {
		index = FT_Get_Char_Index(face, code);
	} else {
		index = 0;
	}

	return;
}

FT_UInt fk_GlyphStatus::GetIndex(void) const
{
	return index;
}

FT_UInt fk_GlyphStatus::GetCode(void) const
{
	return code;
}

fk_FTGlyph::fk_FTGlyph(void)
{
	Init();
}

fk_FTGlyph::~fk_FTGlyph()
{
	Init();
}

void fk_FTGlyph::Init(void)
{
	status.Init();

	return;
}

fk_FontServer::fk_FontServer(void)
{
	FT_Init_FreeType(&library);
	return;
}

fk_FontServer::~fk_FontServer()
{
	for(auto p = faceArray.begin(); p != faceArray.end(); ++p) {
		FT_Done_Face(p->second);
	}
	FT_Done_FreeType(library);
	return;
}

FT_Face fk_FontServer::GetFace(string argName)
{
	FT_Face		face;
	FT_Error	error;

	auto p = faceArray.find(argName);
	if(p == faceArray.end()) {
		error = FT_New_Face(library, argName.c_str(), 0, &face);

		if(error) {
			return nullptr;
		}

		faceArray[argName] = face;
		return face;
	}

	return faceArray[argName];
}

fk_FTFace::fk_FTFace(void)
{
	face = nullptr;
	return;
}

fk_FTFace::~fk_FTFace()
{
	return;
}

fk_GlyphServer::fk_GlyphServer(void)
{
	return;
}

fk_GlyphServer::~fk_GlyphServer()
{
	Clear();
	return;
}

void fk_GlyphServer::Clear(void)
{
	fk_GlyphCache	*tmpCache;

	for(auto p = glyphArray.begin(); p != glyphArray.end(); ++p) {
		tmpCache = p->second;
		delete tmpCache->buffer;
		delete tmpCache;
	}

	glyphArray.clear();
	return;
}

void fk_GlyphServer::MakeCache(const fk_GlyphStatus &argStatus,
							   const FT_BBox &argBBox)
{
	fk_GlyphCache		*cache;

	if(IsArive(argStatus) == true) return;
	cache = new fk_GlyphCache;
	cache->bbox = argBBox;
	cache->buffer = new fk_GlyphBuffer;
	glyphArray[argStatus] = cache;
	return;
}

fk_GlyphBuffer * fk_GlyphServer::GetBuffer(const fk_GlyphStatus &argStatus)
{
	if(IsArive(argStatus) == false) return nullptr;
	return glyphArray[argStatus]->buffer;
}

FT_BBox * fk_GlyphServer::GetBBox(const fk_GlyphStatus &argStatus)
{
	if(IsArive(argStatus) == false) return nullptr;
	return &(glyphArray[argStatus]->bbox);
}

bool fk_GlyphServer::IsArive(const fk_GlyphStatus &argStatus) const
{
	if(glyphArray.find(argStatus) == glyphArray.end()) return false;
	return true;
}

static fk_FontServer * getFTServer(void)
{
	static fk_FontServer	ft;
	return &ft;
}

static fk_GlyphServer *	getGlyphServer(void)
{
	static fk_GlyphServer	gs;
	return &gs;
}

static bool				cacheMode = false;

fk_TextImage::fk_TextImage(void)
{
	SetObjectType(FK_TEXTIMAGE);
	setDPI(48);
	setPTSize(48);
	setCharSkip(0);
	setLineSkip(0);
	setSpaceLineSkip(0);
	setSmoothMode(true);
	setMonospaceMode(false);
	setMonospaceSize(0);
	setOffset(0, 0, 0, 0);
	maxHeight = maxWidth = 0;
	setMinLineWidth(0);
	setShadowMode(false);
	setShadowOffset(0, 0);
	setBoldStrength(1);

	lineArray.clear();
	lineMap.clear();
	charArray.clear();

	charImages.clear();

	fgColor.init(1.0, 1.0, 1.0, 1.0);
	bgColor.init(0.0, 0.0, 0.0, 1.0);
	shadowColor.init(0.0, 0.0, 0.0, 1.0);

	alignMode = FK_ALIGN_LEFT;
	sendingMode = FK_SENDING_ALL;

	face = new fk_FTFace;

	return;
}

fk_TextImage::~fk_TextImage()
{
	delete face;
	ClearCharImages();

	return;
}

void fk_TextImage::setDPI(int argDPI)
{
	dpi = argDPI;
	return;
}

void fk_TextImage::setPTSize(int argPTSize)
{
	ptsize = argPTSize;
	return;
}

int fk_TextImage::getDPI(void) const
{
	return dpi;
}

int fk_TextImage::getPTSize(void) const
{
	return ptsize;
}

void fk_TextImage::setBoldStrength(int argStrength)
{
	if(argStrength <= 0) return;
	boldStrength = argStrength;
	return;
}

int fk_TextImage::getBoldStrength(void) const
{
	return boldStrength;
}

void fk_TextImage::setLineSkip(int argSkip)
{
	if(argSkip >= 0) {
		lineSkip = argSkip;
	}
	return;
}

int fk_TextImage::getLineSkip(void) const
{
	return lineSkip;
}

void fk_TextImage::setCharSkip(int argSkip)
{
	if(argSkip >= 0) {
		charSkip = argSkip;
	}
	return;
}

int fk_TextImage::getCharSkip(void) const
{
	return charSkip;
}

void fk_TextImage::setSpaceLineSkip(int argSkip)
{
	if(argSkip >= 0) {
		spaceLineSkip = argSkip;
	}
	return;
}

int fk_TextImage::getSpaceLineSkip(void) const
{
	return spaceLineSkip;
}

void fk_TextImage::setAlign(fk_TextAlign argAlign)
{
	alignMode = argAlign;
	return;
}

fk_TextAlign fk_TextImage::getAlign(void) const
{
	return alignMode;
}

void fk_TextImage::setOffset(int argUp, int argDown, int argLeft, int argRight)
{
	upOffset = argUp;
	downOffset = argDown;
	leftOffset = argLeft;
	rightOffset = argRight;
	return;
}

int fk_TextImage::getUpOffset(void) const
{
	return upOffset;
}

int fk_TextImage::getDownOffset(void) const
{
	return downOffset;
}

int fk_TextImage::getLeftOffset(void) const
{
	return leftOffset;
}

int fk_TextImage::getRightOffset(void) const
{
	return rightOffset;
}

void fk_TextImage::setMinLineWidth(int argWidth)
{
	minWidth = argWidth;
	return;
}

int fk_TextImage::getMinLineWidth(void) const
{
	return minWidth;
}

int fk_TextImage::getMaxLineWidth(void) const
{
	return maxWidth;
}

int fk_TextImage::getMaxLineHeight(void) const
{
	return maxHeight;
}

bool fk_TextImage::initFont(const string fontName)
{
	face->face = getFTServer()->GetFace(fontName);
	if(face->face == nullptr) {
		return false;
	}
	return true;
}

void fk_TextImage::FreeGlyph(vector<fk_FTGlyph *> *argGlyphArray)
{
	_st				i;
	fk_FTGlyph		*glyph;

	for(i = 0; i < argGlyphArray->size(); i++) {
		glyph = (*argGlyphArray)[i];
		glyph->Init();
		delete glyph;
	}

	argGlyphArray->clear();
	return;
}

bool fk_TextImage::send(void)
{
	_st		i, endPos, sp;

	sp = static_cast<_st>(sendPos);
	if(sp == charArray.size()) return false;

	switch(sendingMode) {
	  case FK_SENDING_ALL:
		endPos = charArray.size();
		break;

	  case FK_SENDING_CHAR:
		endPos = sp + 1;
		break;

	  case FK_SENDING_LINE:

		for(i = sp + 1; i < charArray.size(); i++) {
			if(lineMap[sp] != lineMap[i]) break;
		}
		endPos = i;
		break;

	  default:
		return false;
	}

	for(i = sp; i < endPos; i++) {
		CopyCharImage(static_cast<int>(i));
	}
	sendPos = static_cast<int>(endPos);

	return true;
}

bool fk_TextImage::finish(void)
{
	int		i, endPos;

	endPos = static_cast<int>(charArray.size());
	if(sendPos == endPos) return false;

	for(i = sendPos; i < endPos; i++) {
		CopyCharImage(i);
	}

	sendPos = endPos;

	return true;
}

bool fk_TextImage::clear(void)
{
	if(sendPos == 0) return false;
	InitTextImage();
	sendPos = 0;
	if(charImages.empty() == true) loadUniStr(nullptr);
	return true;
}

void fk_TextImage::setSendingMode(fk_TextSendingMode argMode)
{
	sendingMode = argMode;
	return;
}

fk_TextSendingMode fk_TextImage::getSendingMode(void) const
{
	return sendingMode;
}

bool fk_TextImage::loadUniStr(fk_UniStr *argStr)
{
	fk_FTGlyph				*glyph;
	vector<fk_FTGlyph *>	glyphArray;
	int						i;
	int						upper, lineNum;
	fk_UniStr				tmpStr, line;
	int						fbScale[1024], sbScale[1024];

	if(face->face == nullptr) {
		fk_PutError("fk_TextImage", "loadUniStr", 1);
		return false;
	}

	if(argStr != nullptr) strData.copyStr(argStr);
	tmpStr.copyStr(&strData);

	FreeGlyph(&glyphArray);
	FT_Set_Char_Size(face->face, ptsize << 6, ptsize << 6,
					 static_cast<FT_UInt>(dpi),
					 static_cast<FT_UInt>(dpi));

	lineArray.clear();
	lineMap.clear();
	charArray.clear();
	ClearCharImages();

	MakeColorScale(fgColor, bgColor, fbScale);
	if(shadowMode == true) MakeColorScale(shadowColor, bgColor, sbScale);

	for(lineNum = 0; tmpStr.getLine(&line); lineNum++) {
		for(i = 0; i < line.getLength(); i++) {
			glyph = new fk_FTGlyph;
			glyph->status.Set(face->face, static_cast<FT_UInt>(line.getCode(i)),
							  ptsize, dpi, boldStrength);
			glyphArray.push_back(glyph);
			lineMap.push_back(lineNum);
		}

		upper = LayoutGlyphs(&glyphArray);
		DumpRasterMap(upper, fbScale, sbScale, &glyphArray);
		FreeGlyph(&glyphArray);
	}

	CalcTextOffset();
	ReCalcCharOffset();
	InitTextImage();
	if(sendingMode == FK_SENDING_ALL) {
		for(i = 0; i < static_cast<int>(charArray.size()); i++) CopyCharImage(i);
		ClearCharImages();
		sendPos = static_cast<int>(charArray.size());
	} else {
		sendPos = 0;
	}
	if(cacheMode == false) clearCache();

	return true;
}

void fk_TextImage::ClearCharImages(void)
{
	for(_st i = 0; i < charImages.size(); i++) {
		delete charImages[i];
	}

	charImages.clear();
	return;
}

void fk_TextImage::MakeColorScale(const fk_Color &argC1,
								  const fk_Color &argC2,
								  int *argScale)
{
	int		index, i, j;
	float	val1, val2;

	for(i = 0; i < 256; i++) {
		for(j = 0; j < 4; j++) {
			index = i*4 + j;
			val1 = argC1.col[j] * static_cast<float>(i)/255.0f;
			val2 = argC2.col[j] * (1.0f - (static_cast<float>(i)/255.0f));
			argScale[index] = static_cast<int>(256.0f*(val1 + val2));
			if(argScale[index] >= 256) argScale[index] = 255;
			if(argScale[index] < 0) argScale[index] = 0;
		}
	}
	return;
}

int fk_TextImage::LayoutGlyphs(vector<fk_FTGlyph *> *argGlyphArray)
{
	FT_Pos			image_w, image_h, oneImage_w, oneImage_h, upper, under;
	//FT_UInt			load_flags;
	_st				i, j;
	FT_BBox			*pBBox;
	FT_Glyph		glyph;
	fk_FTGlyph		*fkGlyph;
	fk_Rect			lineRect;
	FT_GlyphSlot	slot;
	fk_GlyphBuffer	*buffer;


	int				pixelSp = int((double)dpi/96.0*(double)ptsize);

	//load_flags = FT_LOAD_DEFAULT;

	image_w = 0;
	image_h = 0;
	upper = 0;
	under = 0;

	for(i = 0; i < argGlyphArray->size(); i++) {
		fkGlyph = (*argGlyphArray)[i];

		if(getGlyphServer()->IsArive(fkGlyph->status) == false) {
			if(FT_Load_Glyph(face->face, fkGlyph->status.GetIndex(),
							 FT_LOAD_DEFAULT | FT_LOAD_NO_BITMAP)) {
				fk_PutError("fk_TextImage", "LayoutGlyphs", 1);
				continue;
			}

			slot = face->face->glyph;

			if(slot->format != FT_GLYPH_FORMAT_OUTLINE) {
				fk_PutError("fk_TextImage", "LayoutGlyohs", 2);
				continue;
			}

			if(boldStrength != 1) {
				if(FT_Outline_Embolden(&(slot->outline), boldStrength)) {
					fk_PutError("fk_TextImage", "LayoutGlyohs", 3);
					continue;
				}
			}

			if(FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL)) {
				fk_PutError("fk_TextImage", "LayoutGlyohs", 4);
				continue;
			}

			FT_Get_Glyph(slot, &glyph);

			FT_Glyph_Get_CBox(glyph, ft_glyph_bbox_pixels, &(fkGlyph->bbox));

			getGlyphServer()->MakeCache(fkGlyph->status, fkGlyph->bbox);

			pBBox = &(fkGlyph->bbox);
			oneImage_w = pBBox->xMax - pBBox->xMin;
			oneImage_h = pBBox->yMax - pBBox->yMin;

			buffer = getGlyphServer()->GetBuffer(fkGlyph->status);
			buffer->resize(static_cast<_st>(oneImage_w * oneImage_h));

			for(j = 0; j < static_cast<_st>(oneImage_w * oneImage_h); j++) {
				(*buffer)[j] = slot->bitmap.buffer[j];
			}
			FT_Done_Glyph(glyph);
		} else {
			pBBox = getGlyphServer()->GetBBox(fkGlyph->status);
			fkGlyph->bbox = *pBBox;
		}

		fkGlyph->xOffset = image_w;

		if(monospaceMode == true) {
			image_w += monospaceSize + charSkip;
		} else {
			// rita: 空白挿入処理＆通常のシフト処理
			switch(fkGlyph->status.GetCode()) {
			  case SP_1BYTE:
				image_w += pixelSp/2 + charSkip;
				break;
			  case SP_2BYTE:
				image_w += pixelSp + charSkip;
				break;
			  default:
				image_w += pBBox->xMax - pBBox->xMin + charSkip;
				break;
			}
		}

		if(shadowMode == true && image_w != 0) image_w += abs(shadowOffset.w);
		if(upper < pBBox->yMax) upper = pBBox->yMax;
		if(under > pBBox->yMin) under = pBBox->yMin;
	}

	image_h = upper - under;
	if(shadowMode == true && image_h != 0) image_h += abs(shadowOffset.h);

	lineRect.set(0, 0, static_cast<int>(image_w - charSkip), static_cast<int>(image_h));
	lineArray.push_back(lineRect);

	return static_cast<int>(upper);
}

void fk_TextImage::DumpRasterMap(int argUpper,
								 int *argFBScale,
								 int *argSBScale,
								 vector<fk_FTGlyph *> *argGlyphArray)
{
	_st				i;
	int				j, k;
	fk_GlyphBuffer	*localImageBuf;
	FT_BBox			*pBBox;
	_st				pixel, setVal;
	fk_FTGlyph		*glyph;
	fk_Rect			charRect, imageRect;
	fk_Image		*charImage;
	fk_Dimension	orgImageSize;
	fk_Dimension	posOffset;

	for(i = 0; i < argGlyphArray->size(); i++) {
		glyph = (*argGlyphArray)[i];
		pBBox = &(glyph->bbox);
		localImageBuf = getGlyphServer()->GetBuffer(glyph->status);

		charRect.x = static_cast<int>(glyph->xOffset);
		charRect.y = static_cast<int>(argUpper - pBBox->yMax);
		orgImageSize.w = static_cast<int>(pBBox->xMax - pBBox->xMin);
		orgImageSize.h = static_cast<int>(pBBox->yMax - pBBox->yMin);

		if(monospaceMode == true) {
			charRect.w = monospaceSize;
		} else {
			charRect.w = orgImageSize.w;
		}
		charRect.h = orgImageSize.h;

		imageRect = charRect;

		if(shadowMode == true) {
			imageRect.w += abs(shadowOffset.w);
			imageRect.h += abs(shadowOffset.h);
		}
		
		charImage = new fk_Image(imageRect.w, imageRect.h);
		charImage->fillColor(argFBScale[0], argFBScale[1],
							 argFBScale[2], argFBScale[3]);

		if(shadowMode == true) {
			posOffset.w = (shadowOffset.w < 0) ? 0 : shadowOffset.w;
			posOffset.h = (shadowOffset.h < 0) ? 0 : shadowOffset.h;

			for(j = 0; j < charRect.h; j++) {
				for(k = 0; k < charRect.w; k++) {
					pixel = static_cast<_st>(GetPixel(localImageBuf, charRect.w,
													  orgImageSize.w, j, k));
					if(smoothFlg == true) {
						setVal = (pixel > 255) ? 255 : pixel;
					} else {
						setVal = (pixel > 128) ? 255 : 0;
					}
					if(setVal != 0) {
						charImage->setRGBA(static_cast<int>(k) + posOffset.w,
										   static_cast<int>(j) + posOffset.h,
										   argSBScale[setVal*4],
										   argSBScale[setVal*4 + 1],
										   argSBScale[setVal*4 + 2],
										   argSBScale[setVal*4 + 3]);
					}
				}
			}

			posOffset.w = (shadowOffset.w > 0) ? 0 : -shadowOffset.w;
			posOffset.h = (shadowOffset.h > 0) ? 0 : -shadowOffset.h;
		} else {
			posOffset.set(0, 0);
		}

		for(j = 0; j < charRect.h; j++) {
			for(k = 0; k < charRect.w; k++) {
				/*
				_st tmpW = static_cast<_st>(orgImageSize.w);
				if(monospaceMode == true) {
					_st w = (k * tmpW)/static_cast<_st>(charRect.w);
					_st index = j * tmpW + w;
					if(tmpW >= w) {
						pixel = localImageBuf->at(index);
					} else {
						_st pixel1 = localImageBuf->at(index);
						_st pixel2 = localImageBuf->at(index+1);
						double t = (double(tmpW)/double(charRect.w)) * double(k) - double(w);
						pixel = (_st)((1.0 - t)*double(pixel1) + t * double(pixel2));
					}
				} else {
					_st index = j * tmpW + k;
					pixel = localImageBuf->at(index);
				}
				*/

				pixel = static_cast<_st>(GetPixel(localImageBuf, charRect.w,
												  orgImageSize.w, j, k));

				if(smoothFlg == true) {
					setVal = (pixel > 255) ? 255 : pixel;
				} else {
					setVal = (pixel > 128) ? 255 : 0;
				}
				if(setVal != 0) {
					charImage->setRGBA(static_cast<int>(k) + posOffset.w,
									   static_cast<int>(j) + posOffset.h,
									   argFBScale[setVal*4],
									   argFBScale[setVal*4 + 1],
									   argFBScale[setVal*4 + 2],
									   argFBScale[setVal*4 + 3]);
				}
			}
		}

		charArray.push_back(charRect);
		charImages.push_back(charImage);
	}

	return;
}

int fk_TextImage::GetPixel(fk_GlyphBuffer *argBuffer, int argCW, int argIW, int argJ, int argK)
{
	_st pixel, index;

	if(monospaceMode == true) {
		int w = (argK * argIW)/argCW;
		index = static_cast<_st>(argJ * argIW + w);
		if(argIW >= w) {
			pixel = argBuffer->at(index);
		} else {
			_st pixel1 = argBuffer->at(index);
			_st pixel2 = argBuffer->at(index+1);
			double t = (double(argIW)/double(argCW)) * double(argK) - double(w);
			pixel = static_cast<_st>((1.0 - t)*double(pixel1) + t * double(pixel2));
		}
	} else {
		index = static_cast<_st>(argJ * argIW + argK);
		pixel = argBuffer->at(index);
	}
	return static_cast<int>(pixel);
}
	

void fk_TextImage::setSmoothFlg(bool argFlg)
{
	setSmoothMode(argFlg);
	return;
}

void fk_TextImage::setSmoothMode(bool argFlg)
{
	smoothFlg = argFlg;
	return;
}

bool fk_TextImage::getSmoothFlg(void) const
{
	return getSmoothMode();
}

bool fk_TextImage::getSmoothMode(void) const
{
	return smoothFlg;
}

void fk_TextImage::setMonospaceMode(bool argMode)
{
	monospaceMode = argMode;
	return;
}

bool fk_TextImage::getMonospaceMode(void) const
{
	return monospaceMode;
}

void fk_TextImage::setMonospaceSize(int argSize)
{
	if(argSize >= 0) monospaceSize = argSize;
	return;
}

int fk_TextImage::getMonospaceSize(void) const
{
	return monospaceSize;
}

void fk_TextImage::setForeColor(fk_Color argColor)
{
	fgColor = argColor;
	return;
}

void fk_TextImage::setForeColor(float argR, float argG, float argB, float argA)
{
	fgColor.set(argR, argG, argB, argA);
	return;
}

void fk_TextImage::setForeColor(double argR, double argG,
								double argB, double argA)
{
	fgColor.set(argR, argG, argB, argA);
	return;
}

void fk_TextImage::setBackColor(fk_Color argColor)
{
	bgColor = argColor;
	return;
}

void fk_TextImage::setBackColor(float argR, float argG, float argB, float argA)
{
	bgColor.set(argR, argG, argB, argA);
	return;
}

void fk_TextImage::setBackColor(double argR, double argG,
								double argB, double argA)
{
	bgColor.set(argR, argG, argB, argA);
	return;
}

void fk_TextImage::setShadowColor(fk_Color argColor)
{
	shadowColor = argColor;
	return;
}

void fk_TextImage::setShadowColor(float argR, float argG,
								  float argB, float argA)
{
	shadowColor.set(argR, argG, argB, argA);
	return;
}

void fk_TextImage::setShadowColor(double argR, double argG,
								  double argB, double argA)
{
	shadowColor.set(argR, argG, argB, argA);
	return;
}

fk_Color fk_TextImage::getForeColor(void) const
{
	return fgColor;
}

fk_Color fk_TextImage::getBackColor(void) const
{
	return bgColor;
}

fk_Color fk_TextImage::getShadowColor(void) const
{
	return shadowColor;
}

void fk_TextImage::CalcTextOffset(void)
{
	_st		lineID;
	int		yOffset, xOffset;
	int		curW, curH, trueWidth;

	yOffset = upOffset;

	maxWidth = -1;
	maxHeight = -1;

	for(lineID = 0; lineID < lineArray.size(); lineID++) {
		curW = lineArray[lineID].w;
		curH = lineArray[lineID].h;

		if(curW > maxWidth) maxWidth = curW;
		if(curH > maxHeight) maxHeight = curH;
	}

	trueWidth = (maxWidth > minWidth) ? maxWidth : minWidth;

	for(lineID = 0; lineID < lineArray.size(); lineID++) {
		curW = lineArray[lineID].w;
		curH = lineArray[lineID].h;

		switch(alignMode) {
		  case FK_ALIGN_LEFT:
			xOffset = leftOffset;
			break;

		  case FK_ALIGN_CENTER:
			xOffset = (trueWidth - curW)/2 + leftOffset;
			break;

		  case FK_ALIGN_RIGHT:
			xOffset = trueWidth - curW + leftOffset;
			break;

		  default:
			xOffset = leftOffset;
			break;
		}

		lineArray[lineID].x = xOffset;
		lineArray[lineID].y = yOffset;

		if(curH == 0) {
			yOffset += spaceLineSkip + lineSkip;
		} else {
			yOffset += curH + lineSkip;
		}
	}

	newImage(trueWidth + leftOffset + rightOffset,
			 yOffset + downOffset - lineSkip, false);

	return;
}

void fk_TextImage::ReCalcCharOffset(void)
{
	_st		i, index;

	if(charArray.empty() == true) return;

	for(i = 0; i < charArray.size(); i++) {
		index = static_cast<_st>(lineMap[i]);
		charArray[i].x += lineArray[index].x;
		charArray[i].y += lineArray[index].y;
	}
	return;
}


void fk_TextImage::InitTextImage(void)
{
	unsigned int	i;
	int				bgCol[4];

	for(i = 0; i < 4; i++) {
		bgCol[i] = static_cast<int>(bgColor.col[i] * 256);
		if(bgCol[i] >= 256) bgCol[i] = 255;
		if(bgCol[i] < 0) bgCol[i] = 0;
	}

	fillColor(bgCol[0], bgCol[1], bgCol[2], bgCol[3]);

	return;
}

void fk_TextImage::CopyCharImage(int argID)
{
	_st		id = static_cast<_st>(argID);

	copyImage(charImages[id], charArray[id].x, charArray[id].y);

	return;
}

bool fk_TextImage::loadStrFile(const string argFileName, fk_StringCode argCode)
{
	fk_UniStr		uniStr;

	if(uniStr.readFile(argFileName, argCode) == false) {
		fk_PutError("fk_TextImage", "loadStrFile", 1);
		return false;
	}

	loadUniStr(&uniStr);
	return true;
}

int fk_TextImage::getLineNum(void) const
{
	return static_cast<int>(lineArray.size());
}

int fk_TextImage::getLineCharNum(int argLineID) const
{
	_st			i, count;

	if(argLineID < 0 || argLineID >= int(lineArray.size())) return 0;

	for(count = 0, i = 0; i < lineMap.size(); i++) {
		if(argLineID == lineMap[i]) count++;
		if(argLineID < lineMap[i]) break;
	}
	return static_cast<int>(count);
}

int fk_TextImage::getAllCharNum(void) const
{
	return static_cast<int>(charArray.size());
}

int fk_TextImage::getLineWidth(int argID) const
{
	_st		id = static_cast<_st>(argID);

	if(argID < 0 || id >= lineArray.size()) return -1;

	return lineArray[id].w;
}

int fk_TextImage::getLineHeight(int argID) const
{
	_st		id = static_cast<_st>(argID);

	if(argID < 0 || id >= lineArray.size()) return -1;

	return lineArray[id].h;
}

int fk_TextImage::getLineStartXPos(int argID) const
{
	_st		id = static_cast<_st>(argID);

	if(argID < 0 || id >= lineArray.size()) return -1;

	return lineArray[id].x;
}

int fk_TextImage::getLineStartYPos(int argID) const
{
	_st		id = static_cast<_st>(argID);

	if(argID < 0 || id >= lineArray.size()) return -1;

	return lineArray[id].y;
}

void fk_TextImage::setShadowMode(bool argMode)
{
	shadowMode = argMode;
	return;
}

void fk_TextImage::setShadowOffset(int argX, int argY)
{
	shadowOffset.set(argX, argY);
	return;
}

bool fk_TextImage::getShadowMode(void) const
{
	return shadowMode;
}

fk_Dimension fk_TextImage::getShadowOffset(void) const
{
	return shadowOffset;
}

void fk_TextImage::clearCache(void)
{
	getGlyphServer()->Clear();
	return;
}

void fk_TextImage::setCacheMode(bool argMode)
{
	cacheMode = argMode;
	return;
}

bool fk_TextImage::getCacheMode(void)
{
	return cacheMode;
}
