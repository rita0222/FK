#include "Image_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::fk_Dimension * fk_Dimension::GetP(void)
	{
		return pDim;
	}

	fk_Dimension::fk_Dimension()
	{
		pDim = new ::fk_Dimension();
	}

	fk_Dimension::fk_Dimension(int argW, int argH)
	{
		pDim = new ::fk_Dimension(argW, argH);
	}

	fk_Dimension::~fk_Dimension()
	{
		this->!fk_Dimension();
	}

	fk_Dimension::!fk_Dimension()
	{
		delete pDim;
	}
	
	int fk_Dimension::w::get()
	{
		return pDim->w;
	}

	void fk_Dimension::w::set(int value)
	{
		pDim->w = value;
	}

	int fk_Dimension::h::get()
	{
		return pDim->h;
	}

	void fk_Dimension::h::set(int value)
	{
		pDim->h = value;
	}

	int fk_Dimension::x::get()
	{
		return pDim->w;
	}

	void fk_Dimension::x::set(int value)
	{
		pDim->w = value;
	}

	int fk_Dimension::y::get()
	{
		return pDim->h;
	}

	void fk_Dimension::y::set(int value)
	{
		pDim->h = value;
	}

	String^	fk_Dimension::ToString()
	{
		string	tmpBuf;
		tmpBuf = "DIM: " + to_string(pDim->w) + ", ";
		tmpBuf += to_string(pDim->h);
		return gcnew String(tmpBuf.c_str());
	}
	
	void fk_Dimension::Set(int argW, int argH)
	{
		GetP()->set(argW, argH);
	}
	
	//////////////////////////////////////////////////////////////



	::fk_Rect * fk_Rect::GetP(void)
	{
		return pRect;
	}

	fk_Rect::fk_Rect()
	{
		pRect = new ::fk_Rect();
	}

	fk_Rect::fk_Rect(int argX, int argY, int argW, int argH)
	{
		pRect = new ::fk_Rect(argX, argY, argW, argH);
	}

	fk_Rect::~fk_Rect()
	{
		this->!fk_Rect();
	}

	fk_Rect::!fk_Rect()
	{
		delete pRect;
	}

	int fk_Rect::x::get()
	{
		return pRect->x;
	}

	void fk_Rect::x::set(int value)
	{
		pRect->x = value;
	}

	int fk_Rect::y::get()
	{
		return pRect->y;
	}

	void fk_Rect::y::set(int value)
	{
		pRect->y = value;
	}

	int fk_Rect::w::get()
	{
		return pRect->w;
	}

	void fk_Rect::w::set(int value)
	{
		pRect->w = value;
	}

	int fk_Rect::h::get()
	{
		return pRect->h;
	}

	void fk_Rect::h::set(int value)
	{
		pRect->h = value;
	}
	
	String^	fk_Rect::ToString()
	{
		string	tmpBuf;
		tmpBuf = "RECT: ";
		tmpBuf += to_string(pRect->x) + ", ";
		tmpBuf += to_string(pRect->y) + ", ";
		tmpBuf += to_string(pRect->w) + ", ";
		tmpBuf += to_string(pRect->h);
		return gcnew String(tmpBuf.c_str());
	}

	void fk_Rect::Set(int argX, int argY, int argW, int argH)
	{
		GetP()->set(argX, argY, argW, argH);
	}

	void fk_Rect::SetPos(int argX, int argY)
	{
		GetP()->setPos(argX, argY);
	}

	void fk_Rect::SetSize(int argW, int argH)
	{
		GetP()->setSize(argW, argH);
	}

	fk_Dimension^ fk_Rect::GetSize(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = GetP()->getSize();
		return D;
	}

	/////////////////////////////////////////////////////////////////////

	::fk_Image * fk_Image::GetP(void)
	{
		return (::fk_Image *)(pBase);
	}
	
	fk_Image::fk_Image() : fk_BaseObject(false)
	{
		pBase = new ::fk_Image();
	}

	fk_Image::fk_Image(bool argNewFlg) : fk_BaseObject(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_Image();
		}
	}

	fk_Image::fk_Image(int argW, int argH) : fk_BaseObject(false)
	{
		pBase = new ::fk_Image(argW, argH);
	}

	fk_Image::~fk_Image()
	{
		this->!fk_Image();
	}

	fk_Image::!fk_Image()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	fk_Color^ fk_Image::default::get(int argX, int argY)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getColor(argX, argY);
		return C;
	}

	void fk_Image::default::set(int argX, int argY, fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setColor(argX, argY, *(argC->pCol));
	}

	fk_Dimension^ fk_Image::Size::get(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = *(GetP()->getImageSize());
		return D;
	}

	fk_Dimension^ fk_Image::BufferSize::get(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = *(GetP()->getBufferSize());
		return D;
	}

#ifndef FK_DOXYGEN_USER_PROCESS
	void* fk_Image::Buffer::get(void)
	{
		return (void*)(GetP()->getBufPointer());
	}
#endif

	void fk_Image::Init(void)
	{
		GetP()->init();
	}

	void fk_Image::NewImage(int argW, int argH, bool argInitFlg)
	{
		GetP()->newImage(argW, argH, argInitFlg);
	}

	void fk_Image::NewImage(int argW, int argH)
	{
		GetP()->newImage(argW, argH, true);
	}

	void fk_Image::CopyImage(fk_Image^ argImage)
	{
		if(!argImage) return;
		GetP()->copyImage(argImage->GetP());
	}

	void fk_Image::CopyImage(fk_Image^ argImage, int argX, int argY)
	{
		if(!argImage) return;
		GetP()->copyImage(argImage->GetP(), argX, argY);
	}

	bool fk_Image::SubImage(fk_Image^ argImage, int argX, int argY, int argW, int argH)
	{
		if(!argImage) return false;
		return GetP()->subImage(argImage->GetP(), argX, argY, argW, argH);
	}

	int	fk_Image::GetR(int argX, int argY)
	{
		return GetP()->getR(argX, argY);
	}

	int fk_Image::GetG(int argX, int argY)
	{
		return GetP()->getG(argX, argY);
	}

	int fk_Image::GetB(int argX, int argY)
	{
		return GetP()->getB(argX, argY);
	}
	int fk_Image::GetA(int argX, int argY)
	{
		return GetP()->getA(argX, argY);
	}

	bool fk_Image::SetRGBA(int argX, int argY, int argR, int argG, int argB, int argA)
	{
		return GetP()->setRGBA(argX, argY, argR, argG, argB, argA);
	}

	bool fk_Image::SetRGB(int argX, int argY, int argR, int argG, int argB)
	{
		return GetP()->setRGB(argX, argY, argR, argG, argB);
	}

	bool fk_Image::SetR(int argX, int argY, int argR)
	{
		return GetP()->setR(argX, argY, argR);
	}

	bool fk_Image::SetG(int argX, int argY, int argG)
	{
		return GetP()->setG(argX, argY, argG);
	}

	bool fk_Image::SetB(int argX, int argY, int argB)
	{
		return GetP()->setB(argX, argY, argB);
	}

	bool fk_Image::SetA(int argX, int argY, int argA)
	{
		return GetP()->setA(argX, argY, argA);
	}

	bool fk_Image::ReadBMP(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readBMP(marshal_as<string>(argFileName));
	}

	bool fk_Image::ReadPNG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readPNG(marshal_as<string>(argFileName));
	}

	bool fk_Image::ReadJPG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readJPG(marshal_as<string>(argFileName));
	}

	bool fk_Image::WriteBMP(String^ argFileName, bool argTransFlg)
	{
		if(!argFileName) return false;
		return GetP()->writeBMP(marshal_as<string>(argFileName), argTransFlg);
	}

	bool fk_Image::WriteBMP(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->writeBMP(marshal_as<string>(argFileName), false);
	}

	bool fk_Image::WritePNG(String^ argFileName, bool argTransFlg)
	{
		if(!argFileName) return false;
		return GetP()->writePNG(marshal_as<string>(argFileName), argTransFlg);
	}

	bool fk_Image::WritePNG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->writePNG(marshal_as<string>(argFileName), true);
	}

	bool fk_Image::WriteJPG(String^ argFileName, int argQuality)
	{
		if(!argFileName) return false;
		return GetP()->writeJPG(marshal_as<string>(argFileName), argQuality);
	}

	bool fk_Image::WriteJPG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->writeJPG(marshal_as<string>(argFileName), 80);
	}

	void fk_Image::FillColor(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->fillColor(*argC->pCol);
	}

	void fk_Image::FillColor(int argR, int argG, int argB, int argA)
	{
		GetP()->fillColor(argR, argG, argB, argA);
	}
		
	void fk_Image::FillColor(int argR, int argG, int argB)
	{
		GetP()->fillColor(argR, argG, argB);
	}
}
/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
