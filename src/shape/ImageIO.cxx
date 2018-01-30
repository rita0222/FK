/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
#include <FK/Image.h>
#include <FK/Error.H>

#if defined(_FREEBSD_) || defined(_LINUX_)
#include <png.h>
#else
#include <png/png.h>
#endif

#if defined(WIN32) && !defined(_MINGW_)
#pragma warning ( disable : 4793 )
#pragma warning ( disable : 4996 )
#endif

using namespace std;
using namespace FK;

extern "C" {
	#define XMD_H
	#ifdef WIN32
		#define HAVE_BOOLEAN
	#endif
	#if defined(_FREEBSD_) || defined(_LINUX_)
		#include <jpeglib.h>
	#else
		#include "jpeg/jpeglib.h"
	#endif
}

bool fk_Image::IsBmpFile(const string argFName) const
{
	ifstream	ifs(argFName, ios::binary);
	fk_ImType	buf[2];

	if(ifs.fail()) return false;

	ifs.read((char *)(buf), sizeof(fk_ImType)*2);
	if(ifs.bad()) {
		ifs.close();
		return false;
	}

	ifs.close();

	return IsBmpData(buf);
}

bool fk_Image::IsBmpData(fk_ImType *argData) const
{
	if(argData[0] == 'B' && argData[1] == 'M') return true;
	return false;
}


bool fk_Image::GetBmpFileHeader(ifstream &argIFS, fk_ImType *argHeader)
{
	size_t	imSize = sizeof(fk_ImType);

	argIFS.read((char *)(argHeader), static_cast<streamsize>(imSize * 14));
	if(argIFS.bad()) return false;

	return true;
}

bool fk_Image::GetBmpInfoHeader(ifstream &argIFS, fk_ImType *argHeader)
{
	size_t	imSize = sizeof(fk_ImType);

	argIFS.read((char *)(argHeader), static_cast<streamsize>(imSize * 40));
	if(argIFS.bad()) return false;

	return true;
}

fk_Dimension fk_Image::GetBmpSize(fk_ImType *argHeader)
{
	fk_Dimension	retDim;

	retDim.w = static_cast<int>(ChgUInt(argHeader, 4));
	retDim.h = static_cast<int>(ChgUInt(argHeader, 8));

	return retDim;
}

fk_ImageStatus fk_Image::LoadBmpFile(const string argFName)
{
	ifstream			ifs(argFName, ios::binary);
	int					tmpSize;
	unsigned int		bmpType;
	fk_ImType			bmpFileHeader[14];
	fk_ImType			bmpInfoHeader[40];
	fk_Dimension		bmpSize;
	vector<fk_ImType>	rgbQuad;
	vector<fk_ImType>	tmpBuffer;
	int					x, y;
	unsigned int		paletteSize;

	if(ifs.fail()) {
		return FK_IMAGE_OPENERROR;
	}

	if(GetBmpFileHeader(ifs, bmpFileHeader) == false) {
		ifs.close();
		return FK_IMAGE_DATAERROR;
	}

	if(GetBmpInfoHeader(ifs, bmpInfoHeader) == false) {
		ifs.close();
		return FK_IMAGE_DATAERROR;
	}

	paletteSize = ChgUInt(bmpFileHeader, 10) - 54;
	bmpSize = GetBmpSize(bmpInfoHeader);
	CreateBuffer(bmpSize);

	bmpType = ChgUShort(bmpInfoHeader, 14);

	if(bmpType <= 8) {
		rgbQuad.resize(paletteSize);
		ifs.read((char *)(&rgbQuad[0]),
				 static_cast<streamsize>(sizeof(fk_ImType) * paletteSize));
		if(ifs.bad()) {
			rgbQuad.clear();
			return FK_IMAGE_DATAERROR;
		}
	} else {
		rgbQuad.clear();
	}

	tmpSize = GetOneBufferSize(static_cast<int>(bmpType), bmpSize.w);
	if(tmpSize < 0) return FK_IMAGE_DATAERROR;

	tmpBuffer.resize(static_cast<_st>(tmpSize));

	for(y = bmpSize.h - 1; y >= 0; y--) {

		ifs.read((char *)(&tmpBuffer[0]),
				 static_cast<streamsize>(sizeof(fk_ImType) * static_cast<size_t>(tmpSize)));

		if(ifs.bad()) {
			ifs.close();
			rgbQuad.clear();
			tmpBuffer.clear();
			return FK_IMAGE_DATAERROR;
		}

		for(x = 0; x < bmpSize.w; x++) {
			SetRGBA4Bmp(x, y, &tmpBuffer[0],
						static_cast<int>(bmpType), rgbQuad);
		}
	}

	ifs.close();
	rgbQuad.clear();
	tmpBuffer.clear();

	return FK_IMAGE_OK;
}

fk_ImageStatus fk_Image::LoadBmpData(fk_ImType *argBuffer)
{
	int					tmpSize, count;
	fk_ImType			*bmpFileHeader;
	fk_ImType			*bmpInfoHeader;
	vector<fk_ImType>	rgbQuad;
	fk_ImType			*tmpImageBuf;
	unsigned int		bmpType;
	fk_Dimension		bmpSize;
	int					x, y;
	unsigned int		i;
	unsigned int		paletteSize;
	

	bmpFileHeader = argBuffer;
	bmpInfoHeader = argBuffer + 14;

	paletteSize = ChgUInt(bmpFileHeader, 10) - 54;
	bmpSize = GetBmpSize(bmpInfoHeader);
	CreateBuffer(bmpSize);

	bmpType = ChgUShort(bmpInfoHeader, 14);

	if(bmpType <= 8) {
		rgbQuad.resize(paletteSize);
		for(i = 0; i < paletteSize; i++) rgbQuad[i] = argBuffer[i+54];
		tmpImageBuf = argBuffer + paletteSize + 54;
	} else {
		rgbQuad.clear();
		tmpImageBuf = argBuffer + 54;
	}

	tmpSize = GetOneBufferSize(static_cast<int>(bmpType), bmpSize.w);
	if(tmpSize < 0) return FK_IMAGE_DATAERROR;

	for(y = bmpSize.h - 1, count = 0; y >= 0; y--, count++) {

		for(x = 0; x < bmpSize.w; x++) {
			SetRGBA4Bmp(x, y,
						tmpImageBuf + count * tmpSize,
						static_cast<int>(bmpType), rgbQuad);
		}
	}

	return FK_IMAGE_OK;
}

void fk_Image::SetRGBA4Bmp(int argX, int argY,
						   fk_ImType *argBuffer, int argType,
						   vector<fk_ImType> &argQuadBuffer)
{
	fk_ImType	tmp;
	_st			pb;

	switch(argType) {
	  case 1:
		if((argBuffer[argX/8] & (0x80 >> argX % 8)) != 0) {
			setRGB(argX, argY,
				   static_cast<int>(argQuadBuffer[4]),
				   static_cast<int>(argQuadBuffer[5]),
				   static_cast<int>(argQuadBuffer[6]));
		} else {
			setRGB(argX, argY,
				   static_cast<int>(argQuadBuffer[0]),
				   static_cast<int>(argQuadBuffer[1]),
				   static_cast<int>(argQuadBuffer[2]));
		}

		break;

	  case 4:
		if((argX % 2) == 0) {
			tmp = (fk_ImType)(static_cast<int>(argBuffer[argX/2]) >> 4);
			tmp &= 0x0f;
		} else {
			tmp = (fk_ImType)(static_cast<int>(argBuffer[argX/2]) & 0x0f);
		}

		setRGB(argX, argY,
			   argQuadBuffer[2+4*tmp],
			   argQuadBuffer[1+4*tmp],
			   argQuadBuffer[4*tmp]);

		break;

	  case 8:
		pb = static_cast<_st>(argBuffer[argX]);

		setRGB(argX, argY,
			   static_cast<int>(argQuadBuffer[2+4*pb]),
			   static_cast<int>(argQuadBuffer[1+4*pb]),
			   static_cast<int>(argQuadBuffer[4*pb]));
		break;

	  case 24:

		setRGB(argX, argY,
			   static_cast<int>(argBuffer[argX*3+2]),
			   static_cast<int>(argBuffer[argX*3+1]),
			   static_cast<int>(argBuffer[argX*3]));
		break;

	  case 32:

		setRGBA(argX, argY,
				static_cast<int>(argBuffer[argX*4+2]),
				static_cast<int>(argBuffer[argX*4+1]),
				static_cast<int>(argBuffer[argX*4]),
				255 - static_cast<int>(argBuffer[argX*4+3]));
		break;

	  default:
		break;
	}

	return;
}

fk_ImageStatus fk_Image::SaveBmpFile(string argFName, bool argTransFlg)
{
	ofstream			ofs(argFName, ios::binary);
	int					wSize, hSize;
	vector<fk_ImType>	bmpFileHeader;
	vector<fk_ImType>	bmpInfoHeader;
	vector<fk_ImType>	bmpBuffer;
	_st					x, bmpBufSize;
	int					y;
	int					bitSize;

	if(imageBuf.empty() == true) return FK_IMAGE_DATAERROR;

	if(ofs.fail()) {
		return FK_IMAGE_OPENERROR;
	}

	wSize = imageSize.w;
	hSize = imageSize.h;

	bitSize = (argTransFlg == true) ? 4 : 3;

	MakeBmpFileHeader(wSize, hSize, bitSize, bmpFileHeader);
	MakeBmpInfoHeader(wSize, hSize, bitSize*8, bmpInfoHeader);

	bmpBufSize = static_cast<_st>(wSize * bitSize);

	while(bmpBufSize % 4 != 0) {
		bmpBufSize++;
	}

	bmpBuffer.resize(bmpBufSize);
	for(x = 0; x < bmpBufSize; x++) bmpBuffer[x] = 0;

	ofs.write((char *)(&bmpFileHeader[0]),
			  static_cast<streamsize>(sizeof(fk_ImType) * bmpFileHeader.size()));

	ofs.write((char *)(&bmpInfoHeader[0]),
			  static_cast<streamsize>(sizeof(fk_ImType) * bmpInfoHeader.size()));

	for(y = hSize-1; y >= 0; y--) {
		MakeBmpBuffer(y, wSize, argTransFlg, &bmpBuffer[0]);
		ofs.write((char *)(&bmpBuffer[0]),
				  static_cast<streamsize>(sizeof(fk_ImType) * bmpBufSize));
	}

	ofs.close();

	bmpFileHeader.clear();
	bmpInfoHeader.clear();
	bmpBuffer.clear();

	return FK_IMAGE_OK;
}

void fk_Image::MakeBmpFileHeader(int argW, int argH, int argBitSize,
								 vector<fk_ImType> &argHeader)
{
	int			offset = 0;

	argHeader.resize(14);
	argHeader[0] = static_cast<fk_ImType>('B');
	argHeader[1] = static_cast<fk_ImType>('M');
	offset += 2;

	SetLong2Byte(14 + 40 +
				 static_cast<long>(argW) *
				 static_cast<long>(argH) *
				 static_cast<long>(argBitSize),
				 &argHeader[0], offset);
	offset += 4;

	SetInt2Byte(0, &argHeader[0], offset);
	offset += 2;

	SetInt2Byte(0, &argHeader[0], offset);
	offset += 2;

	SetLong2Byte(14 + 40, &argHeader[0], offset);

	return;
}

void fk_Image::MakeBmpInfoHeader(int argW, int argH, int argBitSize,
								 vector<fk_ImType> &argInfo)
{
	int			offset = 0;

	argInfo.resize(40);

	// .biSize
	SetLong2Byte(40, &argInfo[0], offset);
	offset += 4;

	// .biWidth
	SetLong2Byte(static_cast<long>(argW), &argInfo[0], offset);
	offset += 4;

	// .biHeight
	SetLong2Byte(static_cast<long>(argH), &argInfo[0], offset);
	offset += 4;

	// .biPlanes
	SetInt2Byte(1, &argInfo[0], offset);
	offset += 2;

	// .biBitCount
	SetInt2Byte(argBitSize, &argInfo[0], offset);
	offset += 2;

	// .biCompression
	SetLong2Byte(0, &argInfo[0], offset);
	offset += 4;

	// .biSizeImage
	SetLong2Byte(0, &argInfo[0], offset);
	offset += 4;

	// .biXPelsPerMeter
	SetLong2Byte(0, &argInfo[0], offset);
	offset += 4;

	// .biYPelsPerMeter
	SetLong2Byte(0, &argInfo[0], offset);
	offset += 4;

	// .biClrUsed
	SetLong2Byte(0, &argInfo[0], offset);
	offset += 4;

	// .biClrImportant
	SetLong2Byte(0, &argInfo[0], offset);

	return;
}

void fk_Image::MakeBmpBuffer(int argY, int argW,
							 bool argTransFlg, fk_ImType *argBuffer)
{
	int		x;
	int		offset;

	offset = (argTransFlg == true) ? 4 : 3;

	for(x = 0; x < argW; x++) {
		argBuffer[x * offset] = static_cast<fk_ImType>(getB(x, argY));
		argBuffer[x * offset + 1] = static_cast<fk_ImType>(getG(x, argY));
		argBuffer[x * offset + 2] = static_cast<fk_ImType>(getR(x, argY));
		if(argTransFlg == true) {
			argBuffer[x * offset + 3] = static_cast<fk_ImType>(255 - getA(x, argY));
		}
	}
}

bool fk_Image::readBMP(const string argFName)
{
	if(CreateImg(argFName) != FK_IMAGE_OK) {
		return false;
	}

	return true;
}

bool fk_Image::readBMPData(fk_ImType *argBuffer)
{
	if(CreateImg(argBuffer) != FK_IMAGE_OK) {
		return false;
	}

	return true;
}

bool fk_Image::writeBMP(const string argFName, const bool argTransFlg)
{
	if(SaveBmpFile(argFName, argTransFlg) != FK_IMAGE_OK) {
		return false;
	}

	return true;
}


bool fk_Image::IsPngFile(const string argFName) const
{
	ifstream		ifs(argFName, ios::binary);
	unsigned char	sig[4];

	if(ifs.fail()) return false;

	// ヘッダの読込(4バイト)
	ifs.read((char *)(sig), 4);

	if(ifs.bad()) {
		ifs.close();
		return false;
	}

	// PNGファイルであるかどうかをチェック
	if(png_sig_cmp(sig, 0, 4)) {
		ifs.close();
		return false;
	}

	ifs.close();
	return true;
}

void _fk_Image_PngReadFunc(png_struct *argPng, png_bytep argBuf,
						   png_size_t argSize)
{
	unsigned char **p = static_cast<unsigned char **>(png_get_io_ptr(argPng));
	memcpy(argBuf, *p, argSize);
	*p += static_cast<int>(argSize);
	return;
}


fk_ImageStatus fk_Image::LoadPngData(fk_ImType *argBuffer)
{
	png_structp		png_ptr;
	png_infop		info_ptr;
	_st				trueX, trueY;
	png_bytepp		tmpBuffer;

	if(png_sig_cmp(argBuffer, 0, 4)) return FK_IMAGE_DATAERROR;

	// PNG構造体の初期化
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

	if(png_ptr == nullptr) {
		return FK_IMAGE_DATAERROR;
	}

	// PNG情報構造体の初期化
	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr == nullptr) {
		png_destroy_read_struct(&png_ptr, nullptr, nullptr);
		return FK_IMAGE_DATAERROR;
	}

	if(setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		return FK_IMAGE_DATAERROR;
	}

	png_set_read_fn(png_ptr, &argBuffer,
					_fk_Image_PngReadFunc);

	// PNG情報構造体の取得
	png_read_info(png_ptr, info_ptr);

	// PNGデータの情報取得
	// PNG_COLOR_TYPE_GRAY (ビット深度 1, 2, 4, 8, 16)
	// PNG_COLOR_TYPE_GRAY_ALPHA (ビット深度 8, 16)
	// PNG_COLOR_TYPE_PALETTE (ビット深度 1, 2, 4, 8)
	// PNG_COLOR_TYPE_RGB (ビット深度 8, 16)
	// PNG_COLOR_TYPE_RGB_ALPHA (ビット深度 8, 16)

	int type    = png_get_color_type(png_ptr, info_ptr);	// 色タイプ
	int depth	= png_get_bit_depth(png_ptr, info_ptr);	// 色深度(1,2,4,8,16)

	// 16bit-depthのPNGは除外
	if(depth == 16){
		png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		return FK_IMAGE_DATAERROR;
	}

	// 画像サイズの取得
	trueX = png_get_image_width(png_ptr, info_ptr);
	trueY = png_get_image_height(png_ptr, info_ptr);

	// fk_Image 本体のバッファを作成
	CreateBuffer(static_cast<int>(trueX),
				 static_cast<int>(trueY));

	// テンポラリイメージデータのメモリを取得
	if((tmpBuffer = static_cast<png_bytepp>(malloc(trueY * sizeof(png_bytep)))) == nullptr) {
		png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		return FK_IMAGE_READERROR;
	}
	for(png_uint_32 i = 0; i < trueY; i++) {
		// 1 ラインのテンポラリメモリを取得
		tmpBuffer[i] = static_cast<png_bytep>(malloc(png_get_rowbytes(png_ptr, info_ptr)));
		if (tmpBuffer[i] == nullptr) {
			for (png_uint_32 j = 0; j < i; j++) {
				free(tmpBuffer[j]);
			}
			free(tmpBuffer);
			png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
			return FK_IMAGE_READERROR;
		}
	}
	// pngの内容を読み込み
	png_read_image(png_ptr, tmpBuffer);

	// pngの読込終了
	png_read_end(png_ptr, info_ptr);

	fk_ImageStatus result = FK_IMAGE_OK;

	// フルカラー(RGB)
	if(type == PNG_COLOR_TYPE_RGB) {
		// 内容の移し変え
		_st		offset;

		for(int j = 0; j < static_cast<int>(trueY); j++){
			for(int i = 0; i < static_cast<int>(trueX); i++){
				offset = static_cast<_st>(GetOffset(i, j));
				imageBuf[offset]   = tmpBuffer[j][i*3];
				imageBuf[offset+1] = tmpBuffer[j][i*3+1];
				imageBuf[offset+2] = tmpBuffer[j][i*3+2];
				imageBuf[offset+3] = 255;
			}
		}
	}
	// フルカラー+アルファチャンネル(RGBA)
	else if(type == PNG_COLOR_TYPE_RGB_ALPHA) {
		// 内容の移し変え
		int	lineSize = static_cast<int>(png_get_rowbytes(png_ptr, info_ptr));

		for(int j = 0; j < static_cast<int>(trueY); j++) {
			memcpy(&(imageBuf[static_cast<_st>(GetOffset(0, j))]),
				   tmpBuffer[j], static_cast<size_t>(lineSize));
		}
	}
	// グレースケール(8bit)
	else if(type == PNG_COLOR_TYPE_GRAY && depth == 8) {
		// 内容の移し変え
		_st 	offset;

		for(int j = 0; j < static_cast<int>(trueY); j++){
			for(int i = 0; i < static_cast<int>(trueX); i++){
				offset = static_cast<_st>(GetOffset(i, j));
				imageBuf[offset]   = tmpBuffer[j][i];
				imageBuf[offset+1] = tmpBuffer[j][i];
				imageBuf[offset+2] = tmpBuffer[j][i];
				imageBuf[offset+3] = 255;
			}
		}
	}
	// グレースケール(1bit)
	else if(type == PNG_COLOR_TYPE_GRAY && depth == 1){
		// 内容の移し変え
		unsigned char	color;
		_st				offset;
		int				x, y;

		for(int j = 0; j < static_cast<int>(trueY); j++){
			for(int i = 0; i < static_cast<int>(trueX/8+1); i++){
				color = tmpBuffer[j][i];

				for(int k = 0; k < 8; k++){
					x = i*8+k;
					y = j;
					offset = static_cast<_st>(GetOffset(x, y));
					
					if(x < static_cast<int>(trueX)){
						imageBuf[offset]   = static_cast<fk_ImType>(255 * ((color >> (7-k)) % 2));
						imageBuf[offset+1] = static_cast<fk_ImType>(255 * ((color >> (7-k)) % 2));
						imageBuf[offset+2] = static_cast<fk_ImType>(255 * ((color >> (7-k)) % 2));
						imageBuf[offset+3] = static_cast<fk_ImType>(255);
					}
				}
			}
		}
	}
	// パレット(8bit)
	else if(type == PNG_COLOR_TYPE_PALETTE && depth == 8){
		png_colorp		palette;		// パレットデータ
		int				num_palette;	// パレット数
		_st				offset;
		unsigned char	num;
		
		// パレットの取得
		png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);

		// 内容の移し変え
		for(int j = 0; j < static_cast<int>(trueY); j++){
			for(int i = 0; i < static_cast<int>(trueX); i++){
				offset = static_cast<_st>(GetOffset(i, j));
				// パレット番号の取得
				num = tmpBuffer[j][i];
				imageBuf[offset]   = palette[num].red;
				imageBuf[offset+1] = palette[num].green;
				imageBuf[offset+2] = palette[num].blue;
				imageBuf[offset+3] = 255;
			}
		}	
	}
	// 想定外フォーマット
	else {
		result = FK_IMAGE_DATAERROR;
	}

	// メモリの解放
	for(png_uint_32 i = 0; i < trueY; i++) free(tmpBuffer[i]);
	free(tmpBuffer);

	// PNGメモリの解放
	png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

	return result;
}

fk_ImageStatus fk_Image::LoadPngFile(const string argFName)
{
	FILE			*fp;
	unsigned char	sig[4];
	png_structp		png_ptr;
	png_infop		info_ptr;
	unsigned int	trueX, trueY;
	png_bytepp		tmpBuffer;

	// ファイルの読込
	if((fp = fopen(argFName.c_str(), "rb")) == nullptr) {
		return FK_IMAGE_OPENERROR;
	}

	// ヘッダの読込(4バイト)
	if(fread(sig, 1, 4, fp) != 4) {
		fclose(fp);
		return FK_IMAGE_DATAERROR;
	}

	// PNGファイルであるかどうかをチェック
	if(png_sig_cmp(sig, 0, 4)) {
		fclose(fp);
		return FK_IMAGE_DATAERROR;
	}

	// PNG構造体の初期化
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if(png_ptr == nullptr) {
		fclose(fp);
		return FK_IMAGE_DATAERROR;
	}

	// PNG情報構造体の初期化
	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr == nullptr) {
		png_destroy_read_struct(&png_ptr, nullptr, nullptr);
		fclose(fp);
		return FK_IMAGE_DATAERROR;
	}

	if(setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		fclose(fp);
		return FK_IMAGE_DATAERROR;
	}

	// ファイルポインタのセット
	png_init_io(png_ptr, fp);
	// 事前にシグネチャを読込確認済なら
	// ファイル先頭から読み飛ばしているバイト数を知らせる
	png_set_sig_bytes(png_ptr, 4);
	// PNG情報構造体の取得
	png_read_info(png_ptr, info_ptr);

	// PNGデータの情報取得
	// PNG_COLOR_TYPE_GRAY (ビット深度 1, 2, 4, 8, 16)
	// PNG_COLOR_TYPE_GRAY_ALPHA (ビット深度 8, 16)
	// PNG_COLOR_TYPE_PALETTE (ビット深度 1, 2, 4, 8)
	// PNG_COLOR_TYPE_RGB (ビット深度 8, 16)
	// PNG_COLOR_TYPE_RGB_ALPHA (ビット深度 8, 16)

	int type    = png_get_color_type(png_ptr, info_ptr);	// 色タイプ
	int depth	= png_get_bit_depth(png_ptr, info_ptr);	// 色深度(1,2,4,8,16)

	// 16bit-depthのPNGは除外
	if(depth == 16){
		png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		fclose(fp);
		return FK_IMAGE_DATAERROR;
	}

	// 画像サイズの取得
	trueX = png_get_image_width(png_ptr, info_ptr);
	trueY = png_get_image_height(png_ptr, info_ptr);

	// fk_Image 本体のバッファを作成
	CreateBuffer(static_cast<int>(trueX),
				 static_cast<int>(trueY));

	// テンポラリイメージデータのメモリを取得
	if((tmpBuffer = static_cast<png_bytepp>(malloc(trueY * sizeof(png_bytep)))) == nullptr) {
		png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		fclose(fp);
		return FK_IMAGE_READERROR;
	}
	for(png_uint_32 i = 0; i < trueY; i++) {
		// 1 ラインのテンポラリメモリを取得
		tmpBuffer[i] = static_cast<png_bytep>(malloc(png_get_rowbytes(png_ptr, info_ptr)));
		if (tmpBuffer[i] == nullptr) {
			for (png_uint_32 j = 0; j < i; j++) {
				free(tmpBuffer[j]);
			}
			free(tmpBuffer);
			png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
			fclose(fp);
			return FK_IMAGE_READERROR;
		}
	}
	// pngの内容を読み込み
	png_read_image(png_ptr, tmpBuffer);

	// pngの読込終了
	png_read_end(png_ptr, info_ptr);

	// ファイルを閉じる
	fclose(fp);

	fk_ImageStatus result = FK_IMAGE_OK;

	// フルカラー(RGB)
	if(type == PNG_COLOR_TYPE_RGB) {
		// 内容の移し変え
		_st 	offset;

		for(int j = 0; j < static_cast<int>(trueY); j++){
			for(int i = 0; i < static_cast<int>(trueX); i++){
				offset = static_cast<_st>(GetOffset(i, j));
				imageBuf[offset]   = tmpBuffer[j][i*3];
				imageBuf[offset+1] = tmpBuffer[j][i*3+1];
				imageBuf[offset+2] = tmpBuffer[j][i*3+2];
				imageBuf[offset+3] = 255;
			}
		}
	}
	// フルカラー+アルファチャンネル(RGBA)
	else if(type == PNG_COLOR_TYPE_RGB_ALPHA) {
		// 内容の移し変え
		int	lineSize = static_cast<int>(png_get_rowbytes(png_ptr, info_ptr));

		for(int j = 0; j < static_cast<int>(trueY); j++) {
			memcpy(&imageBuf[static_cast<_st>(GetOffset(0, j))],
				   tmpBuffer[j], static_cast<size_t>(lineSize));
		}
	}
	// グレースケール(8bit)
	else if(type == PNG_COLOR_TYPE_GRAY && depth == 8) {
		// 内容の移し変え
		_st		offset;

		for(int j = 0; j < static_cast<int>(trueY); j++){
			for(int i = 0; i < static_cast<int>(trueX); i++){
				offset = static_cast<_st>(GetOffset(i, j));
				imageBuf[offset]   = tmpBuffer[j][i];
				imageBuf[offset+1] = tmpBuffer[j][i];
				imageBuf[offset+2] = tmpBuffer[j][i];
				imageBuf[offset+3] = 255;
			}
		}
	}
	// グレースケール(1bit)
	else if(type == PNG_COLOR_TYPE_GRAY && depth == 1){
		// 内容の移し変え
		unsigned char	color;
		_st				offset;
		int				x, y;

		for(int j = 0; j < static_cast<int>(trueY); j++){
			for(int i = 0; i < static_cast<int>(trueX/8+1); i++){
				color = tmpBuffer[j][i];

				for(int k = 0; k < 8; k++){
					x = i*8+k;
					y = j;
					offset = static_cast<_st>(GetOffset(x, y));
					
					if(x < static_cast<int>(trueX)) {
						imageBuf[offset]   = static_cast<fk_ImType>(255 * ((color >> (7-k)) % 2));
						imageBuf[offset+1] = static_cast<fk_ImType>(255 * ((color >> (7-k)) % 2));
						imageBuf[offset+2] = static_cast<fk_ImType>(255 * ((color >> (7-k)) % 2));
						imageBuf[offset+3] = static_cast<fk_ImType>(255);
					}
				}
			}
		}
	}
	// パレット(8bit)
	else if(type == PNG_COLOR_TYPE_PALETTE && depth == 8){
		png_colorp		palette;		// パレットデータ
		int				num_palette;	// パレット数
		_st				offset;
		unsigned char	num;
		
		// パレットの取得
		png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);

		// 内容の移し変え
		for(int j = 0; j < static_cast<int>(trueY); j++){
			for(int i = 0; i < static_cast<int>(trueX); i++){
				offset = static_cast<_st>(GetOffset(i, j));
				// パレット番号の取得
				num = tmpBuffer[j][i];
				imageBuf[offset]   = palette[num].red;
				imageBuf[offset+1] = palette[num].green;
				imageBuf[offset+2] = palette[num].blue;
				imageBuf[offset+3] = 255;
			}
		}	
	}
	// 想定外フォーマット
	else {
		result = FK_IMAGE_DATAERROR;
	}

	// メモリの解放
	for(png_uint_32 i = 0; i < trueY; i++) free(tmpBuffer[i]);
	free(tmpBuffer);

	// PNGメモリの解放
	png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

	return result;
}

bool fk_Image::readPNG(const string argFName)
{
	if(LoadPngFile(argFName) != FK_IMAGE_OK) {
		return false;
	}

	return true;
}

bool fk_Image::readPNGData(fk_ImType *argBuffer)
{
	if(LoadPngData(argBuffer) != FK_IMAGE_OK) {
		return false;
	}

	return true;
}

bool fk_Image::writePNG(const string fileName, const bool argTransFlg)
{
	FILE			*fp;
	png_structp		png_ptr;
	png_infop		info_ptr;
	unsigned int	trueX, trueY, lineSize;
	png_bytepp		tmpBuffer;

	// バイナリ書き込みモードでファイルをオープン
	fp = fopen(fileName.c_str(), "wb");
	if(fp == nullptr) return false;

	// 書き込み用構造体を作成
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if(png_ptr == nullptr) {
		fclose(fp);
		return false;
	}

	// PNG 情報構造体を作成
	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr == nullptr) {
	   png_destroy_write_struct(&png_ptr, nullptr);
	   fclose(fp);
	   return false;
	}

	// ファイルポインタのセット
	png_init_io(png_ptr, fp);

	// ヘッダに情報を設定(幅、高さ、256(8bit)階調、RGB(A)、インタレースなし)
	if(argTransFlg == true) {
		png_set_IHDR(png_ptr, info_ptr,
					 static_cast<png_uint_32>(getWidth()),
					 static_cast<png_uint_32>(getHeight()), 8,
					 PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
					 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_BASE);
	} else {
		png_set_IHDR(png_ptr, info_ptr,
					 static_cast<png_uint_32>(getWidth()),
					 static_cast<png_uint_32>(getHeight()), 8,
					 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
					 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_BASE);
	}
	png_write_info(png_ptr, info_ptr);

	// 構造体にセットしてから幅と高さを取得し直す
	trueX = png_get_image_width(png_ptr, info_ptr);
	trueY = png_get_image_height(png_ptr, info_ptr);
	lineSize = static_cast<unsigned int>(png_get_rowbytes(png_ptr, info_ptr));

	// テンポラリイメージデータのメモリを取得
	if((tmpBuffer = static_cast<png_bytepp>(malloc(trueY * sizeof(png_bytep)))) == nullptr) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
	}
	for(png_uint_32 i = 0; i < trueY; i++) {
		// 1 ラインのテンポラリメモリを取得
		tmpBuffer[i] = static_cast<png_bytep>(malloc(lineSize));
		if(tmpBuffer[i] == nullptr) {
			for(png_uint_32 j = 0; j < i; j++) {
				free(tmpBuffer[j]);
			}
			free(tmpBuffer);
			png_destroy_write_struct(&png_ptr, &info_ptr);
			fclose(fp);
			return false;
		}
	}

	// 内容の移し変え
	if(argTransFlg == true) {
		for(int j = 0; j < static_cast<int>(trueY); j++) {
			memcpy(tmpBuffer[j],
				   &imageBuf[static_cast<_st>(GetOffset(0, j))],
				   lineSize);
		}
	} else {
		_st		offset;
		for(int j = 0; j < static_cast<int>(trueY); j++) {
			for(int i = 0; i < static_cast<int>(trueX); i++) {
				offset = static_cast<_st>(GetOffset(i, j));
				tmpBuffer[j][i * 3 + 0] = imageBuf[offset + 0];
				tmpBuffer[j][i * 3 + 1] = imageBuf[offset + 1];
				tmpBuffer[j][i * 3 + 2] = imageBuf[offset + 2];
			}
		}
	}

	// 画像の書き込み
	png_write_image(png_ptr, tmpBuffer);

	// 書き込み終了
	png_write_end(png_ptr, info_ptr);
	fclose(fp);

	// メモリの解放
	for(png_uint_32 i = 0; i < trueY; ++i) {
		free(tmpBuffer[i]);
	}
	free(tmpBuffer);
	// 構造体の解体
	png_destroy_write_struct(&png_ptr, &info_ptr);

	return true;
}

bool fk_Image::readJPG(const string fileName)
{
	struct jpeg_decompress_struct	cinfo;	// JPEG情報構造体
	struct jpeg_error_mgr			jerr;	// エラーハンドラ
	FILE							*infile;

	// ファイルを開く
	if((infile = fopen(fileName.c_str(), "rb")) == nullptr) {
		return false;
	}

	// JPEGオブジェクトの初期化
	cinfo.err = jpeg_std_error(&jerr);

	// 独自のエラーハンドラを設定
	cinfo.client_data   = const_cast<char *>("fk_Image JPEG Proc");
	jerr.error_exit     = nullptr;
	jerr.output_message = nullptr;

	jpeg_create_decompress(&cinfo);

	// 標準出力のソースがinfileであることを設定
	jpeg_stdio_src(&cinfo, infile);

	// ヘッダの読み込み
	jpeg_read_header(&cinfo, TRUE);

	// 展開の開始
	jpeg_start_decompress(&cinfo);

	// 幅と高さの取得
	unsigned int wid = cinfo.output_width;
	unsigned int hgt = cinfo.output_height;

	// イメージを保持するメモリ領域の確保と初期化
	JSAMPARRAY img = static_cast<JSAMPARRAY>(malloc(sizeof(JSAMPROW) * hgt));
	if(img == nullptr) {
		fclose(infile);
		return false;
	}

	for(int i = 0; i < int(hgt); i++) {
		img[i] = static_cast<JSAMPROW>(calloc(sizeof(JSAMPLE), 3 * wid));
		if(img[i] == nullptr) {
			for(int j = i-1; j >= 0; j--) free(img[j]);
			free(img);
			fclose(infile);
			return false;
		}
	}

	// 全イメージデータを取得	
	while(cinfo.output_scanline < cinfo.output_height) {
		jpeg_read_scanlines(&cinfo, img + cinfo.output_scanline,
							cinfo.output_height - cinfo.output_scanline);
	}

	// 展開の終了
	jpeg_finish_decompress(&cinfo);

	// JPEGオブジェクトの破棄
	jpeg_destroy_decompress(&cinfo);

	// ファイルを閉じる
	fclose(infile);

	// バッファの生成
	CreateBuffer(static_cast<int>(wid),
				 static_cast<int>(hgt));

	// 内容の移し変え
	_st	 offset;

	for(int j = 0; j < static_cast<int>(hgt); j++){
		for(int i = 0; i < static_cast<int>(wid); i++){
			offset = static_cast<_st>(GetOffset(i, j));
			imageBuf[offset + 0] = img[j][i * 3 + 0];
			imageBuf[offset + 1] = img[j][i * 3 + 1];
			imageBuf[offset + 2] = img[j][i * 3 + 2];
			imageBuf[offset + 3] = 255;
		}
	}

	// イメージデータを保持するメモリ領域を開放
	for(unsigned int i = 0; i < hgt; i++){
		free(img[i]);
	}
	free(img);

	return true;
}

bool fk_Image::writeJPG(const string fileName, int quality)
{
	if(imageBuf.empty()) {
		return false;
	}

	struct jpeg_compress_struct		cinfo;
	struct jpeg_error_mgr			jerr;
	FILE							*outfile;
	JSAMPARRAY						img;

	// クオリティ値の調整
	if(quality < 0) {
		quality = 0;
	} 
	if(quality > 100) {
		quality = 100;
	}

	// ファイルを開く
	if((outfile = fopen(fileName.c_str(), "wb")) == nullptr) {
		return false;
	}

	size_t		wid = static_cast<size_t>(getWidth());
	size_t		hgt = static_cast<size_t>(getHeight());
	_st 		offset;

	// イメージを保持するメモリ領域の確保と初期化
	img = static_cast<JSAMPARRAY>(malloc(sizeof(JSAMPROW) * hgt));
	if(img == nullptr) {
		fclose(outfile);	
		return false;
	}

	for(int j = 0; j < static_cast<int>(hgt); j++) {
		img[j] = (JSAMPROW)malloc(sizeof(JSAMPLE) * 3 * wid);
		if(img[j] == nullptr) {
			for(int k = j-1; k >= 0; k--) free(img[k]);
			free(img);
			fclose(outfile);
			return false;
		}
		
		for(int i = 0; i < static_cast<int>(wid); i++) {
			offset = static_cast<_st>(GetOffset(i, j));
			img[j][i * 3 + 0] = imageBuf[offset + 0];
			img[j][i * 3 + 1] = imageBuf[offset + 1];
			img[j][i * 3 + 2] = imageBuf[offset + 2];
		}
	}

	// JPEGオブジェクトの初期化
	cinfo.err = jpeg_std_error(&jerr);

	// 独自のエラーハンドラを設定
	cinfo.client_data   = const_cast<char *>("fk_Image JPEG Proc");
	jerr.error_exit     = nullptr;
	jerr.output_message = nullptr;
	
	jpeg_create_compress(&cinfo);

	// 標準出力をoutfile
	jpeg_stdio_dest(&cinfo, outfile);
	
	// 圧縮のクオリティを設定
	jpeg_set_quality(&cinfo, quality, TRUE);

	// パラメータの設定
	cinfo.image_width      = static_cast<JDIMENSION>(wid);
	cinfo.image_height     = static_cast<JDIMENSION>(hgt);
	cinfo.input_components = 3;
	cinfo.in_color_space   = JCS_RGB;

	// デフォルト値の設定
	jpeg_set_defaults(&cinfo);

	// 圧縮の開始
	jpeg_start_compress(&cinfo, TRUE);

	// 全イメージデータを出力
	jpeg_write_scanlines(&cinfo, img, static_cast<JDIMENSION>(hgt));

	// 圧縮の終了
	jpeg_finish_compress(&cinfo);

	// JPEGオブジェクトの破棄
	jpeg_destroy_compress(&cinfo);

	// ファイルを閉じる
	fclose(outfile);	

	// イメージデータを保持するメモリ領域を開放
	for(int i = 0; i < static_cast<int>(hgt); i++) {
		free(img[i]);
	}
	free(img);

	return true;
}
