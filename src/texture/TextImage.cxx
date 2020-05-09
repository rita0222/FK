#define FK_DEF_SIZETYPE
#include <map>
#include <algorithm>
#include <FK/TextImage.h>
#include <FK/Error.H>

#if defined(_FREEBSD_) || defined(_LINUX_)
#include <ft2build.h>
#elif defined(_MSC_VER) || defined(_MACOSX_)
#include <ft2build.h>
#else
#include <freetype/ft2build.h>
#endif

using namespace std;

#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H

namespace FK {
	// rita: UTF-16 における空白コード
	const unsigned int SP_1BYTE = 0x0020;
	const unsigned int SP_2BYTE = 0x3000;


	class fk_GlyphStatus {
		class Member {
		public:
			FT_Face face;
			FT_UInt index, code;
			int ptsize, dpi, strength;

			Member(void);
		};
			
	private:
		unique_ptr<Member> _m;

	public:
		fk_GlyphStatus(void);
		fk_GlyphStatus(const fk_GlyphStatus &);
		~fk_GlyphStatus();

		bool operator ==(const fk_GlyphStatus &) const;
		bool operator >(const fk_GlyphStatus &) const;
		bool operator <(const fk_GlyphStatus &) const;
		fk_GlyphStatus & operator =(const fk_GlyphStatus &);

		void Init(void);
		void Set(FT_Face, FT_UInt, int, int, int);
		FT_UInt GetIndex(void) const;
		FT_UInt GetCode(void) const;
	};

	class fk_FTGlyph {
	public:
		fk_GlyphStatus status;
		FT_Pos xOffset;
		FT_BBox bbox;

		fk_FTGlyph(void);
		~fk_FTGlyph();

		void Init(void);
	};

	class fk_FontServer {
		class Member {
		public:
			FT_Library library;
			map<string, FT_Face> faceArray;

			Member(void);
		};
			
	private:
		unique_ptr<Member> _m;

	public:
		fk_FontServer(void);
		~fk_FontServer();

		FT_Face GetFace(string);
	};

	class fk_GlyphCache {
	public:
		FT_BBox bbox;
		fk_GlyphBuffer buffer;
	};

	class fk_GlyphServer {
	private:
		map<fk_GlyphStatus, unique_ptr<fk_GlyphCache>> glyphArray;

	public:
		fk_GlyphServer(void);
		~fk_GlyphServer();

		void Clear(void);
		void MakeCache(const fk_GlyphStatus &, const FT_BBox &);
		fk_GlyphBuffer * GetBuffer(const fk_GlyphStatus &);
		FT_BBox * GetBBox(const fk_GlyphStatus &);
		bool IsArive(const fk_GlyphStatus &) const;
	};

	class fk_FTFace {
	public:
		FT_Face face;

		fk_FTFace(void);
		~fk_FTFace();
	};
}

using namespace FK;

fk_GlyphStatus::Member::Member(void) :
	face(nullptr), index(0), code(0), ptsize(0), dpi(0), strength(1)
{
	return;
}

fk_GlyphStatus::fk_GlyphStatus(void) : _m(make_unique<Member>())
{
	Init();
	return;
}

fk_GlyphStatus::fk_GlyphStatus(const fk_GlyphStatus &argStatus) : _m(make_unique<Member>())
{
	_m->face = argStatus._m->face;
	_m->index = argStatus._m->index;
	_m->code = argStatus._m->code;
	_m->strength = argStatus._m->strength;
	_m->ptsize = argStatus._m->ptsize;
	_m->dpi = argStatus._m->dpi;
}

fk_GlyphStatus::~fk_GlyphStatus()
{
	return;
}

bool fk_GlyphStatus::operator ==(const fk_GlyphStatus &argStatus) const
{
	if(_m->face == argStatus._m->face &&
	   _m->index == argStatus._m->index &&
	   _m->code == argStatus._m->code &&
	   _m->strength == argStatus._m->strength &&
	   _m->ptsize == argStatus._m->ptsize &&
	   _m->dpi == argStatus._m->dpi) {
		return true;
	}

	return false;
}

bool fk_GlyphStatus::operator >(const fk_GlyphStatus &argStatus) const
{
	if(_m->index > argStatus._m->index) return true;
	if(_m->index < argStatus._m->index) return false;
	if(_m->code > argStatus._m->code) return true;
	if(_m->code < argStatus._m->code) return false;
	if(_m->face > argStatus._m->face) return true;
	if(_m->face < argStatus._m->face) return false;
	if(_m->strength > argStatus._m->strength) return true;
	if(_m->strength < argStatus._m->strength) return false;
	if(_m->ptsize > argStatus._m->ptsize) return true;
	if(_m->ptsize < argStatus._m->ptsize) return false;
	if(_m->dpi > argStatus._m->dpi) return true;

	return false;
}

bool fk_GlyphStatus::operator <(const fk_GlyphStatus &argStatus) const
{
	if(_m->index < argStatus._m->index) return true;
	if(_m->index > argStatus._m->index) return false;
	if(_m->code < argStatus._m->code) return true;
	if(_m->code > argStatus._m->code) return false;
	if(_m->face < argStatus._m->face) return true;
	if(_m->face > argStatus._m->face) return false;
	if(_m->strength < argStatus._m->strength) return true;
	if(_m->strength > argStatus._m->strength) return false;
	if(_m->ptsize < argStatus._m->ptsize) return true;
	if(_m->ptsize > argStatus._m->ptsize) return false;
	if(_m->dpi < argStatus._m->dpi) return true;

	return false;
}

fk_GlyphStatus & fk_GlyphStatus::operator =(const fk_GlyphStatus &argStatus)
{
	_m->face = argStatus._m->face;
	_m->index = argStatus._m->index;
	_m->code = argStatus._m->code;
	_m->strength = argStatus._m->strength;
	_m->ptsize = argStatus._m->ptsize;
	_m->dpi = argStatus._m->dpi;

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
	_m->face = argFace;
	_m->code = argCode;
	_m->strength = argStrength;
	_m->ptsize = argPTSize;
	_m->dpi = argDPI;

	if(argCode != 0) {
		_m->index = FT_Get_Char_Index(_m->face, _m->code);
	} else {
		_m->index = 0;
	}

	return;
}

FT_UInt fk_GlyphStatus::GetIndex(void) const
{
	return _m->index;
}

FT_UInt fk_GlyphStatus::GetCode(void) const
{
	return _m->code;
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

fk_FontServer::Member::Member(void)
{
	return;
}

fk_FontServer::fk_FontServer(void) : _m(make_unique<Member>())
{
	FT_Init_FreeType(&_m->library);
	return;
}

fk_FontServer::~fk_FontServer()
{
	for(auto p = _m->faceArray.begin(); p != _m->faceArray.end(); ++p) {
		FT_Done_Face(p->second);
	}
	FT_Done_FreeType(_m->library);
	return;
}

FT_Face fk_FontServer::GetFace(string argName)
{
	FT_Face face;
	FT_Error error;

	auto p = _m->faceArray.find(argName);
	if(p == _m->faceArray.end()) {
		error = FT_New_Face(_m->library, argName.c_str(), 0, &face);

		if(error) {
			return nullptr;
		}

		_m->faceArray[argName] = face;
		return face;
	}

	return _m->faceArray[argName];
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
	glyphArray.clear();
	return;
}

void fk_GlyphServer::MakeCache(const fk_GlyphStatus &argStatus,
							   const FT_BBox &argBBox)
{
	unique_ptr<fk_GlyphCache> cache;

	if(IsArive(argStatus) == true) return;
	cache = make_unique<fk_GlyphCache>();
	cache->bbox = argBBox;
	glyphArray[argStatus] = move(cache);
	return;
}

fk_GlyphBuffer * fk_GlyphServer::GetBuffer(const fk_GlyphStatus &argStatus)
{
	if(IsArive(argStatus) == false) return nullptr;
	return &(glyphArray[argStatus]->buffer);
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

fk_TextImage::Member::Member(void) :
	face(make_unique<fk_FTFace>()),
	dpi(96), ptsize(06),
	boldStrength(1),
	lineSkip(0), charSkip(0), spaceLineSkip(0),
	maxHeight(0), maxWidth(0),
	minWidth(0),
	upOffset(0), downOffset(0), leftOffset(0), rightOffset(0),
	smoothFlg(true),
	fgColor(1.0, 1.0, 1.0, 1.0),
	bgColor(0.0, 0.0, 0.0, 1.0),
	shadowColor(0.0, 0.0, 0.0, 1.0),
	alignMode(fk_TextAlign::LEFT),
	sendingMode(fk_TextSendingMode::ALL),
	sendPos(0), shadowMode(false),
	monospaceMode(true), monospaceSize(10)
{
	return;
}

fk_TextImage::fk_TextImage(void) : _m(make_unique<Member>())
{
	SetObjectType(fk_Type::TEXTIMAGE);
	return;
}

fk_TextImage::~fk_TextImage()
{
	ClearCharImages();

	return;
}

void fk_TextImage::setDPI(int argDPI)
{
	_m->dpi = argDPI;
	return;
}

void fk_TextImage::setPTSize(int argPTSize)
{
	_m->ptsize = argPTSize;
	return;
}

int fk_TextImage::getDPI(void) const
{
	return _m->dpi;
}

int fk_TextImage::getPTSize(void) const
{
	return _m->ptsize;
}

void fk_TextImage::setBoldStrength(int argStrength)
{
	if(argStrength <= 0) return;
	_m->boldStrength = argStrength;
	return;
}

int fk_TextImage::getBoldStrength(void) const
{
	return _m->boldStrength;
}

void fk_TextImage::setLineSkip(int argSkip)
{
	if(argSkip >= 0) {
		_m->lineSkip = argSkip;
	}
	return;
}

int fk_TextImage::getLineSkip(void) const
{
	return _m->lineSkip;
}

void fk_TextImage::setCharSkip(int argSkip)
{
	if(argSkip >= 0) {
		_m->charSkip = argSkip;
	}
	return;
}

int fk_TextImage::getCharSkip(void) const
{
	return _m->charSkip;
}

void fk_TextImage::setSpaceLineSkip(int argSkip)
{
	if(argSkip >= 0) {
		_m->spaceLineSkip = argSkip;
	}
	return;
}

int fk_TextImage::getSpaceLineSkip(void) const
{
	return _m->spaceLineSkip;
}

void fk_TextImage::setAlign(fk_TextAlign argAlign)
{
	_m->alignMode = argAlign;
	return;
}

fk_TextAlign fk_TextImage::getAlign(void) const
{
	return _m->alignMode;
}

void fk_TextImage::setOffset(int argUp, int argDown, int argLeft, int argRight)
{
	_m->upOffset = argUp;
	_m->downOffset = argDown;
	_m->leftOffset = argLeft;
	_m->rightOffset = argRight;
	return;
}

int fk_TextImage::getUpOffset(void) const
{
	return _m->upOffset;
}

int fk_TextImage::getDownOffset(void) const
{
	return _m->downOffset;
}

int fk_TextImage::getLeftOffset(void) const
{
	return _m->leftOffset;
}

int fk_TextImage::getRightOffset(void) const
{
	return _m->rightOffset;
}

void fk_TextImage::setMinLineWidth(int argWidth)
{
	_m->minWidth = argWidth;
	return;
}

int fk_TextImage::getMinLineWidth(void) const
{
	return _m->minWidth;
}

int fk_TextImage::getMaxLineWidth(void) const
{
	return _m->maxWidth;
}

int fk_TextImage::getMaxLineHeight(void) const
{
	return _m->maxHeight;
}

bool fk_TextImage::initFont(const string fontName)
{
	_m->face->face = getFTServer()->GetFace(fontName);
	if(_m->face->face == nullptr) {
		return false;
	}
	return true;
}

void fk_TextImage::FreeGlyph(vector<unique_ptr<fk_FTGlyph>> *argGlyphArray)
{
	for(auto &g : *argGlyphArray) {
		g->Init();
	}

	argGlyphArray->clear();
	return;
}

bool fk_TextImage::send(void)
{
	//_st		i, endPos, sp;

	_st sp = _st(_m->sendPos);
	if(sp == _m->charArray.size()) return false;

	_st endPos = 0, i;
	switch(_m->sendingMode) {
	  case fk_TextSendingMode::ALL:
		endPos = _m->charArray.size();
		break;

	  case fk_TextSendingMode::CHAR:
		endPos = sp + 1;
		break;

	  case fk_TextSendingMode::LINE:

		for(i = sp + 1; i < _m->charArray.size(); i++) {
			if(_m->lineMap[sp] != _m->lineMap[i]) break;
		}
		endPos = i;
		break;

	  default:
		return false;
	}

	for(i = sp; i < endPos; i++) {
		CopyCharImage(int(i));
	}
	_m->sendPos = int(endPos);

	return true;
}

bool fk_TextImage::finish(void)
{
	int endPos = int(_m->charArray.size());
	if(_m->sendPos == endPos) return false;

	for(int i = _m->sendPos; i < endPos; i++) {
		CopyCharImage(i);
	}

	_m->sendPos = endPos;

	return true;
}

bool fk_TextImage::clear(void)
{
	if(_m->sendPos == 0) return false;
	InitTextImage();
	_m->sendPos = 0;
	if(_m->charImages.empty() == true) loadUniStr(nullptr);
	return true;
}

void fk_TextImage::setSendingMode(fk_TextSendingMode argMode)
{
	_m->sendingMode = argMode;
	return;
}

fk_TextSendingMode fk_TextImage::getSendingMode(void) const
{
	return _m->sendingMode;
}

bool fk_TextImage::loadUniStr(fk_UniStr *argStr)
{
	/*
	fk_FTGlyph *glyph;
	vector<fk_FTGlyph *> glyphArray;
	int i, upper, lineNum;

	fk_UniStr tmpStr, line;
	int fbScale[1024], sbScale[1024];
	*/

	if(_m->face->face == nullptr) {
		Error::Put("fk_TextImage", "loadUniStr", 1);
		return false;
	}

	if(argStr != nullptr) _m->strData.copyStr(argStr);
	fk_UniStr tmpStr;
	tmpStr.copyStr(&_m->strData);

	//FreeGlyph(&glyphArray);

	FT_F26Dot6 ptsize_ = _m->ptsize << 6;
	FT_Set_Char_Size(_m->face->face, ptsize_, ptsize_, FT_UInt(_m->dpi), FT_UInt(_m->dpi));

	_m->lineArray.clear();
	_m->lineMap.clear();
	_m->charArray.clear();
	ClearCharImages();

	int fbScale[1024], sbScale[1024];
	MakeColorScale(_m->fgColor, _m->bgColor, fbScale);
	if(_m->shadowMode == true) MakeColorScale(_m->shadowColor, _m->bgColor, sbScale);

	fk_UniStr line;
	int i;
	vector<unique_ptr<fk_FTGlyph>> glyphArray;

	for(int lineNum = 0; tmpStr.getLine(&line); lineNum++) {
		for(i = 0; i < line.getLength(); i++) {
			unique_ptr<fk_FTGlyph> glyph(new fk_FTGlyph);
			glyph->status.Set(_m->face->face, FT_UInt(line.getCode(i)),
							  _m->ptsize, _m->dpi, _m->boldStrength);
			glyphArray.push_back(move(glyph));
			_m->lineMap.push_back(lineNum);
		}

		int upper = LayoutGlyphs(&glyphArray);
		DumpRasterMap(upper, fbScale, sbScale, &glyphArray);
		FreeGlyph(&glyphArray);
	}

	CalcTextOffset();
	ReCalcCharOffset();
	InitTextImage();
	if(_m->sendingMode == fk_TextSendingMode::ALL) {
		for(i = 0; i < int(_m->charArray.size()); i++) CopyCharImage(i);
		ClearCharImages();
		_m->sendPos = int(_m->charArray.size());
	} else {
		_m->sendPos = 0;
	}
	if(cacheMode == false) clearCache();

	return true;
}

void fk_TextImage::ClearCharImages(void)
{
	_m->charImages.clear();
	return;
}

void fk_TextImage::MakeColorScale(const fk_Color &argC1,
								  const fk_Color &argC2,
								  int *argScale)
{
	for(_st i = 0; i < 256; i++) {
		for(_st j = 0; j < 4; j++) {
			_st index = i*4 + j;
			float val1 = argC1.col[j] * float(i)/255.0f;
			float val2 = argC2.col[j] * (1.0f - (float(i)/255.0f));
			argScale[index] = int(256.0f*(val1 + val2));
			if(argScale[index] >= 256) argScale[index] = 255;
			if(argScale[index] < 0) argScale[index] = 0;
		}
	}
	return;
}

int fk_TextImage::LayoutGlyphs(vector<unique_ptr<fk_FTGlyph>> *argGlyphArray)
{
	int pixelSp = int((double)_m->dpi/96.0*(double)_m->ptsize);

	FT_Pos image_w = 0;
	FT_Pos image_h = 0;
	FT_Pos upper = 0;
	FT_Pos under = 0;

	FT_BBox *pBBox;
	for(auto &g : *argGlyphArray) {
		fk_FTGlyph *fkGlyph = g.get();

		if(getGlyphServer()->IsArive(fkGlyph->status) == false) {
			if(FT_Load_Glyph(_m->face->face, fkGlyph->status.GetIndex(),
							 FT_LOAD_DEFAULT | FT_LOAD_NO_BITMAP)) {
				Error::Put("fk_TextImage", "LayoutGlyphs", 1);
				continue;
			}

			FT_GlyphSlot slot = _m->face->face->glyph;

			if(slot->format != FT_GLYPH_FORMAT_OUTLINE) {
				Error::Put("fk_TextImage", "LayoutGlyohs", 2);
				continue;
			}

			if(_m->boldStrength != 1) {
				if(FT_Outline_Embolden(&(slot->outline), _m->boldStrength)) {
					Error::Put("fk_TextImage", "LayoutGlyohs", 3);
					continue;
				}
			}

			if(FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL)) {
				Error::Put("fk_TextImage", "LayoutGlyohs", 4);
				continue;
			}

			FT_Glyph glyph;
			FT_Get_Glyph(slot, &glyph);

			FT_Glyph_Get_CBox(glyph, ft_glyph_bbox_pixels, &(fkGlyph->bbox));

			getGlyphServer()->MakeCache(fkGlyph->status, fkGlyph->bbox);

			pBBox = &(fkGlyph->bbox);
			FT_Pos oneImage_w = pBBox->xMax - pBBox->xMin;
			FT_Pos oneImage_h = pBBox->yMax - pBBox->yMin;

			fk_GlyphBuffer *buffer = getGlyphServer()->GetBuffer(fkGlyph->status);
			buffer->resize(_st(oneImage_w) * _st(oneImage_h));

			for(_st j = 0; j < _st(oneImage_w) * _st(oneImage_h); j++) {
				(*buffer)[j] = slot->bitmap.buffer[j];
			}
			FT_Done_Glyph(glyph);
		} else {
			pBBox = getGlyphServer()->GetBBox(fkGlyph->status);
			fkGlyph->bbox = *pBBox;
		}

		fkGlyph->xOffset = image_w;

		if(_m->monospaceMode == true) {
			image_w += _m->monospaceSize + _m->charSkip;
		} else {
			// rita: 空白挿入処理＆通常のシフト処理
			switch(fkGlyph->status.GetCode()) {
			  case SP_1BYTE:
				image_w += pixelSp/2 + _m->charSkip;
				break;
			  case SP_2BYTE:
				image_w += pixelSp + _m->charSkip;
				break;
			  default:
				image_w += (pBBox->xMax - pBBox->xMin + _m->charSkip);
				break;
			}
		}

		if(_m->shadowMode == true && image_w != 0) image_w += abs(_m->shadowOffset.w);
		if(upper < pBBox->yMax) upper = pBBox->yMax;
		if(under > pBBox->yMin) under = pBBox->yMin;
	}

	image_h = upper - under;
	if(_m->shadowMode == true && image_h != 0) image_h += abs(_m->shadowOffset.h);

	fk_Rect lineRect(0, 0, int(image_w - _m->charSkip), int(image_h));
	_m->lineArray.push_back(lineRect);

	return int(upper);
}

void fk_TextImage::DumpRasterMap(int argUpper,
								 int *argFBScale,
								 int *argSBScale,
								 vector<unique_ptr<fk_FTGlyph>> *argGlyphArray)
{
	fk_Rect charRect;
	fk_Dimension orgImageSize, posOffset;
	_st setVal = 0;

	for(auto &g : *argGlyphArray) {
		fk_FTGlyph *glyph = g.get();
		FT_BBox *pBBox = &(glyph->bbox);
		fk_GlyphBuffer *localImageBuf = getGlyphServer()->GetBuffer(glyph->status);
		
		charRect.x = int(glyph->xOffset);
		charRect.y = int(argUpper - pBBox->yMax);
		orgImageSize.w = int(pBBox->xMax - pBBox->xMin);
		orgImageSize.h = int(pBBox->yMax - pBBox->yMin);

		if(_m->monospaceMode == true) {
			charRect.w = _m->monospaceSize;
		} else {
			charRect.w = orgImageSize.w;
		}
		charRect.h = orgImageSize.h;

		fk_Rect imageRect = charRect;

		if(_m->shadowMode == true) {
			imageRect.w += abs(_m->shadowOffset.w);
			imageRect.h += abs(_m->shadowOffset.h);
		}
		
		unique_ptr<fk_Image> charImage = make_unique<fk_Image>(imageRect.w, imageRect.h);
		charImage->fillColor(argFBScale[0], argFBScale[1],
							 argFBScale[2], argFBScale[3]);

		if(_m->shadowMode == true) {
			posOffset.w = (_m->shadowOffset.w < 0) ? 0 : _m->shadowOffset.w;
			posOffset.h = (_m->shadowOffset.h < 0) ? 0 : _m->shadowOffset.h;

			for(int j = 0; j < charRect.h; j++) {
				for(int k = 0; k < charRect.w; k++) {
					_st pixel = _st(GetPixel(localImageBuf, charRect.w, orgImageSize.w, j, k));
					if(_m->smoothFlg == true) {
						setVal = (pixel > 255) ? 255 : pixel;
					} else {
						setVal = (pixel > 128) ? 255 : 0;
					}
					if(setVal != 0) {
						charImage->setRGBA(int(k) + posOffset.w,
										   int(j) + posOffset.h,
										   argSBScale[setVal*4],
										   argSBScale[setVal*4 + 1],
										   argSBScale[setVal*4 + 2],
										   argSBScale[setVal*4 + 3]);
					}
				}
			}

			posOffset.w = (_m->shadowOffset.w > 0) ? 0 : -_m->shadowOffset.w;
			posOffset.h = (_m->shadowOffset.h > 0) ? 0 : -_m->shadowOffset.h;
		} else {
			posOffset.set(0, 0);
		}

		for(int j = 0; j < charRect.h; j++) {
			for(int k = 0; k < charRect.w; k++) {
				_st pixel = _st(GetPixel(localImageBuf, charRect.w, orgImageSize.w, j, k));
				if(_m->smoothFlg == true) {
					setVal = (pixel > 255) ? 255 : pixel;
				} else {
					setVal = (pixel > 128) ? 255 : 0;
				}
				if(setVal != 0) {
					charImage->setRGBA(int(k) + posOffset.w,
									   int(j) + posOffset.h,
									   argFBScale[setVal*4],
									   argFBScale[setVal*4 + 1],
									   argFBScale[setVal*4 + 2],
									   argFBScale[setVal*4 + 3]);
				}
			}
		}

		_m->charArray.push_back(charRect);
		_m->charImages.push_back(move(charImage));
	}

	return;
}

int fk_TextImage::GetPixel(fk_GlyphBuffer *argBuffer, int argCW, int argIW, int argJ, int argK)
{
	_st pixel, index;

	if(_m->monospaceMode == true) {
		int w = (argK * argIW)/argCW;
		index = _st(argJ) * _st(argIW) + _st(w);
		if(argIW >= w) {
			pixel = argBuffer->at(index);
		} else {
			_st pixel1 = argBuffer->at(index);
			_st pixel2 = argBuffer->at(index+1);
			double t = (double(argIW)/double(argCW)) * double(argK) - double(w);
			pixel = _st((1.0 - t)*double(pixel1) + t * double(pixel2));
		}
	} else {
		index = _st(argJ) * _st(argIW) + _st(argK);
		pixel = argBuffer->at(index);
	}
	return int(pixel);
}
	

void fk_TextImage::setSmoothFlg(bool argFlg)
{
	setSmoothMode(argFlg);
	return;
}

void fk_TextImage::setSmoothMode(bool argFlg)
{
	_m->smoothFlg = argFlg;
	return;
}

bool fk_TextImage::getSmoothFlg(void) const
{
	return getSmoothMode();
}

bool fk_TextImage::getSmoothMode(void) const
{
	return _m->smoothFlg;
}

void fk_TextImage::setMonospaceMode(bool argMode)
{
	_m->monospaceMode = argMode;
	return;
}

bool fk_TextImage::getMonospaceMode(void) const
{
	return _m->monospaceMode;
}

void fk_TextImage::setMonospaceSize(int argSize)
{
	if(argSize >= 0) _m->monospaceSize = argSize;
	return;
}

int fk_TextImage::getMonospaceSize(void) const
{
	return _m->monospaceSize;
}

void fk_TextImage::setForeColor(fk_Color argColor)
{
	_m->fgColor = argColor;
	return;
}

void fk_TextImage::setForeColor(float argR, float argG, float argB, float argA)
{
	_m->fgColor.set(argR, argG, argB, argA);
	return;
}

void fk_TextImage::setForeColor(double argR, double argG,
								double argB, double argA)
{
	_m->fgColor.set(argR, argG, argB, argA);
	return;
}

void fk_TextImage::setBackColor(fk_Color argColor)
{
	_m->bgColor = argColor;
	return;
}

void fk_TextImage::setBackColor(float argR, float argG, float argB, float argA)
{
	_m->bgColor.set(argR, argG, argB, argA);
	return;
}

void fk_TextImage::setBackColor(double argR, double argG,
								double argB, double argA)
{
	_m->bgColor.set(argR, argG, argB, argA);
	return;
}

void fk_TextImage::setShadowColor(fk_Color argColor)
{
	_m->shadowColor = argColor;
	return;
}

void fk_TextImage::setShadowColor(float argR, float argG,
								  float argB, float argA)
{
	_m->shadowColor.set(argR, argG, argB, argA);
	return;
}

void fk_TextImage::setShadowColor(double argR, double argG,
								  double argB, double argA)
{
	_m->shadowColor.set(argR, argG, argB, argA);
	return;
}

fk_Color fk_TextImage::getForeColor(void) const
{
	return _m->fgColor;
}

fk_Color fk_TextImage::getBackColor(void) const
{
	return _m->bgColor;
}

fk_Color fk_TextImage::getShadowColor(void) const
{
	return _m->shadowColor;
}

void fk_TextImage::CalcTextOffset(void)
{
	int yOffset, xOffset;
	_st lineID;
	int curW, curH;

	yOffset = _m->upOffset;
	_m->maxWidth = -1;
	_m->maxHeight = -1;

	for(lineID = 0; lineID < _m->lineArray.size(); lineID++) {
		curW = _m->lineArray[lineID].w;
		curH = _m->lineArray[lineID].h;

		if(curW > _m->maxWidth) _m->maxWidth = curW;
		if(curH > _m->maxHeight) _m->maxHeight = curH;
	}

	int trueWidth = (_m->maxWidth > _m->minWidth) ? _m->maxWidth : _m->minWidth;

	for(lineID = 0; lineID < _m->lineArray.size(); lineID++) {
		curW = _m->lineArray[lineID].w;
		curH = _m->lineArray[lineID].h;

		switch(_m->alignMode) {
		  case fk_TextAlign::LEFT:
			xOffset = _m->leftOffset;
			break;

		  case fk_TextAlign::CENTER:
			xOffset = (trueWidth - curW)/2 + _m->leftOffset;
			break;

		  case fk_TextAlign::RIGHT:
			xOffset = trueWidth - curW + _m->leftOffset;
			break;

		  default:
			xOffset = _m->leftOffset;
			break;
		}

		_m->lineArray[lineID].x = xOffset;
		_m->lineArray[lineID].y = yOffset;

		if(curH == 0) {
			yOffset += _m->spaceLineSkip + _m->lineSkip;
		} else {
			yOffset += curH + _m->lineSkip;
		}
	}

	newImage(trueWidth + _m->leftOffset + _m->rightOffset,
			 yOffset + _m->downOffset - _m->lineSkip, false);

	return;
}

void fk_TextImage::ReCalcCharOffset(void)
{
	if(_m->charArray.empty() == true) return;

	for(_st i = 0; i < _m->charArray.size(); i++) {
		_st index = _st(_m->lineMap[i]);
		_m->charArray[i].x += _m->lineArray[index].x;
		_m->charArray[i].y += _m->lineArray[index].y;
	}
	return;
}


void fk_TextImage::InitTextImage(void)
{
	int bgCol[4];

	for(_st i = 0; i < 4; i++) {
		bgCol[i] = int(_m->bgColor.col[i] * 256);
		if(bgCol[i] >= 256) bgCol[i] = 255;
		if(bgCol[i] < 0) bgCol[i] = 0;
	}

	fillColor(bgCol[0], bgCol[1], bgCol[2], bgCol[3]);

	return;
}

void fk_TextImage::CopyCharImage(int argID)
{
	_st		id = _st(argID);

	copyImage(_m->charImages[id].get(), _m->charArray[id].x, _m->charArray[id].y);
	return;
}

bool fk_TextImage::loadStrFile(const string argFileName, fk_StringCode argCode)
{
	fk_UniStr		uniStr;

	if(uniStr.readFile(argFileName, argCode) == false) {
		Error::Put("fk_TextImage", "loadStrFile", 1);
		return false;
	}

	loadUniStr(&uniStr);
	return true;
}

int fk_TextImage::getLineNum(void) const
{
	return int(_m->lineArray.size());
}

int fk_TextImage::getLineCharNum(int argLineID) const
{
	if(argLineID < 0 || argLineID >= int(_m->lineArray.size())) return 0;

	int count = 0;
	for(_st i = 0; i < _m->lineMap.size(); ++i) {
		if(argLineID == _m->lineMap[i]) ++count;
		if(argLineID < _m->lineMap[i]) break;
	}
	return count;
}

int fk_TextImage::getAllCharNum(void) const
{
	return int(_m->charArray.size());
}

int fk_TextImage::getLineWidth(int argID) const
{
	_st id = _st(argID);

	if(argID < 0 || id >= _m->lineArray.size()) return -1;

	return _m->lineArray[id].w;
}

int fk_TextImage::getLineHeight(int argID) const
{
	_st id = _st(argID);

	if(argID < 0 || id >= _m->lineArray.size()) return -1;

	return _m->lineArray[id].h;
}

int fk_TextImage::getLineStartXPos(int argID) const
{
	_st id = _st(argID);

	if(argID < 0 || id >= _m->lineArray.size()) return -1;

	return _m->lineArray[id].x;
}

int fk_TextImage::getLineStartYPos(int argID) const
{
	_st id = _st(argID);

	if(argID < 0 || id >= _m->lineArray.size()) return -1;

	return _m->lineArray[id].y;
}

void fk_TextImage::setShadowMode(bool argMode)
{
	_m->shadowMode = argMode;
	return;
}

void fk_TextImage::setShadowOffset(int argX, int argY)
{
	_m->shadowOffset.set(argX, argY);
	return;
}

bool fk_TextImage::getShadowMode(void) const
{
	return _m->shadowMode;
}

fk_Dimension fk_TextImage::getShadowOffset(void) const
{
	return _m->shadowOffset;
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
