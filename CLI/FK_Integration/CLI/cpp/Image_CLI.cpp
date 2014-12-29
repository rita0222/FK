#include "Image_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;
	
	String^	fk_Dimension::ToString()
	{
		string	tmpBuf;
		tmpBuf = "DIM: " + to_string(pDim->w) + ", ";
		tmpBuf += to_string(pDim->h);
		return gcnew String(tmpBuf.c_str());
	}
	
	void fk_Dimension::set(int argW, int argH)
	{
		GetP()->set(argW, argH);
	}
	
	//////////////////////////////////////////////////////////////

	
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

	void fk_Rect::set(int argX, int argY, int argW, int argH)
	{
		GetP()->set(argX, argY, argW, argH);
	}

	void fk_Rect::setPos(int argX, int argY)
	{
		GetP()->setPos(argX, argY);
	}

	void fk_Rect::setSize(int argW, int argH)
	{
		GetP()->setSize(argW, argH);
	}

	fk_Dimension^ fk_Rect::getSize(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = GetP()->getSize();
		return D;
	}

	/////////////////////////////////////////////////////////////////////

	
	void fk_Image::init(void)
	{
		GetP()->init();
	}

	bool fk_Image::readBMP(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readBMP(marshal_as<string>(argFileName));
	}

	bool fk_Image::readPNG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readPNG(marshal_as<string>(argFileName));
	}

	bool fk_Image::readJPG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readJPG(marshal_as<string>(argFileName));
	}

	bool fk_Image::writeBMP(String^ argFileName, bool argTransFlg)
	{
		if(!argFileName) return false;
		return GetP()->writeBMP(marshal_as<string>(argFileName), argTransFlg);
	}

	bool fk_Image::writeBMP(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->writeBMP(marshal_as<string>(argFileName), false);
	}

	bool fk_Image::writePNG(String^ argFileName, bool argTransFlg)
	{
		if(!argFileName) return false;
		return GetP()->writePNG(marshal_as<string>(argFileName), argTransFlg);
	}

	bool fk_Image::writePNG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->writePNG(marshal_as<string>(argFileName), true);
	}

	bool fk_Image::writeJPG(String^ argFileName, int argQuality)
	{
		if(!argFileName) return false;
		return GetP()->writeJPG(marshal_as<string>(argFileName), argQuality);
	}

	bool fk_Image::writeJPG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->writeJPG(marshal_as<string>(argFileName), 80);
	}

	void fk_Image::newImage(int argW, int argH, bool argInitFlg)
	{
		GetP()->newImage(argW, argH, argInitFlg);
	}

	void fk_Image::newImage(int argW, int argH)
	{
		GetP()->newImage(argW, argH, true);
	}

	void fk_Image::copyImage(fk_Image^ argImage)
	{
		if(!argImage) return;
		GetP()->copyImage(argImage->GetP());
	}

	void fk_Image::copyImage(fk_Image^ argImage, int argX, int argY)
	{
		if(!argImage) return;
		GetP()->copyImage(argImage->GetP(), argX, argY);
	}

	bool fk_Image::subImage(fk_Image^ argImage, int argX, int argY, int argW, int argH)
	{
		if(!argImage) return false;
		return GetP()->subImage(argImage->GetP(), argX, argY, argW, argH);
	}
		
	int	fk_Image::getWidth(void)
	{
		return GetP()->getWidth();
	}

	int fk_Image::getHeight(void)
	{
		return GetP()->getHeight();
	}
		
	fk_Dimension^ fk_Image::getImageSize(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = *(GetP()->getImageSize());
		return D;
	}
				
	fk_Dimension^ fk_Image::getBufferSize(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = *(GetP()->getBufferSize());
		return D;
	}
				
	int	fk_Image::getR(int argX, int argY)
	{
		return GetP()->getR(argX, argY);
	}

	int fk_Image::getG(int argX, int argY)
	{
		return GetP()->getG(argX, argY);
	}

	int fk_Image::getB(int argX, int argY)
	{
		return GetP()->getB(argX, argY);
	}
	int fk_Image::getA(int argX, int argY)
	{
		return GetP()->getA(argX, argY);
	}

	fk_Color^ fk_Image::getColor(int argX, int argY)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getColor(argX, argY);
		return C;
	}

	bool fk_Image::setRGBA(int argX, int argY, int argR, int argG, int argB, int argA)
	{
		return GetP()->setRGBA(argX, argY, argR, argG, argB, argA);
	}

	bool fk_Image::setRGB(int argX, int argY, int argR, int argG, int argB)
	{
		return GetP()->setRGB(argX, argY, argR, argG, argB);
	}

	bool fk_Image::setR(int argX, int argY, int argR)
	{
		return GetP()->setR(argX, argY, argR);
	}

	bool fk_Image::setG(int argX, int argY, int argG)
	{
		return GetP()->setG(argX, argY, argG);
	}

	bool fk_Image::setB(int argX, int argY, int argB)
	{
		return GetP()->setB(argX, argY, argB);
	}

	bool fk_Image::setA(int argX, int argY, int argA)
	{
		return GetP()->setA(argX, argY, argA);
	}

	bool fk_Image::setColor(int argX, int argY, fk_Color^ argC)
	{
		if(!argC) return false;
		return GetP()->setColor(argX, argY, *(argC->pCol));
	}

	void fk_Image::fillColor(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->fillColor(*argC->pCol);
	}

	void fk_Image::fillColor(int argR, int argG, int argB, int argA)
	{
		GetP()->fillColor(argR, argG, argB, argA);
	}
		
	void fk_Image::fillColor(int argR, int argG, int argB)
	{
		GetP()->fillColor(argR, argG, argB);
	}
}
