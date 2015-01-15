// TextImage_CLI.h

#pragma once

#include <FK/TextImage.h>
#include "Image_CLI.h"
#include "UniCode_CLI.h"

namespace FK_CLI {

	public enum class fk_TextAlign {
		LEFT,
		CENTER,
		RIGHT
	};

	public enum class fk_TextSendingMode {
		ALL,
		CHAR,
		LINE
	};

	public ref class fk_TextImage : fk_Image {
	internal:
		::fk_TextImage * GetP(void)
		{
			return (::fk_TextImage *)(pBase);
		}

	public:
		fk_TextImage::fk_TextImage() : fk_Image(false)
		{
			pBase = new ::fk_TextImage();
		}

		fk_TextImage::fk_TextImage(bool argNewFlg) : fk_Image(false)
		{
			if(argNewFlg == true) {
				pBase = new ::fk_TextImage();
			}
		}

		fk_TextImage::~fk_TextImage()
		{
			this->!fk_TextImage();
		}

		fk_TextImage::!fk_TextImage()
		{
			if(pBase == nullptr) return;
			if(dFlg == true) delete GetP();
			pBase = nullptr;
		}

		bool initFont(String^ fontFileName);
		void setDPI(int dpi);
		int getDPI(void);
		void setPTSize(int size);
		int getPTSize(void);
		void setBoldStrength(int str);
		int getBoldStrength(void);
		void setShadowMode(bool mode);
		bool getShadowMode(void);
		void setShadowOffset(int x, int y);
		fk_Dimension^ getShadowOffset(void);
		void setShadowColor(fk_Color^ col);
		void setShadowColor(float r, float g, float b, float a);
		void setShadowColor(double r, double g, double b, double a);
		fk_Color^ getShadowColor(void);
		void setForeColor(fk_Color^ col);
		void setForeColor(float r, float g, float b, float a);
		void setForeColor(double r, double g, double b, double a);
		fk_Color^ getForeColor(void);
		void setBackColor(fk_Color^ col);
		void setBackColor(float r, float g, float b, float a);
		void setBackColor(double r, double g, double b, double a);
		fk_Color^ getBackColor(void);
		void setSmoothMode(bool mode);
		bool getSmoothMode(void);
		void setCharSkip(int skip);
		int getCharSkip(void);
		void setLineSkip(int skip);
		int getLineSkip(void);
		void setSpaceLineSkip(int skip);
		int getSpaceLineSkip(void);
		void setOffset(int up, int down, int left, int right);
		int getUpOffset(void);
		int getDownOffset(void);
		int getLeftOffset(void);
		int getRightOffset(void);
		void setAlign(fk_TextAlign align);
		fk_TextAlign getAlign(void);
		void setMinLineWidth(int width);
		int getMinLineWidth(void);
		bool loadUniStr(fk_UniStr^ str);
		bool loadStrFile(String^ fileName, fk_StringCode code);
		bool loadStrFile(String^ fileName);
		int getLineNum(void);
		int getLineCharNum(int num);
		int getAllCharNum(void);
		int getMaxLineWidth(void);
		int getMaxLineHeight(void);
		int getLineWidth(int num);
		int getLineHeight(int num);
		int getLineStartXPos(int num);
		int getLineStartYPos(int num);
		void setSendingMode(fk_TextSendingMode mode);
		fk_TextSendingMode getSendingMode(void);
		bool send(void);
		bool finish(void);
		bool clear(void);
		static void setCacheMode(bool mode);
		static bool getCacheMode(void);
		static void clearCache(void);
	};
}
