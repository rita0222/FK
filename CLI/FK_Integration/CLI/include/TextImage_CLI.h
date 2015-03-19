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
		::fk_TextImage * GetP(void);

	public:
		fk_TextImage();
		fk_TextImage(bool argNewFlg);
		~fk_TextImage();
		!fk_TextImage();

		property int DPI {
			int get();
			void set(int);
		}

		property int PTSize {
			int get();
			void set(int);
		}

		property int BoldStrength {
			int get();
			void set(int);
		}

		property bool ShadowMode {
			bool get();
			void set(bool);
		}

		property fk_Dimension^ ShadowOffset {
			fk_Dimension^ get();
			void set(fk_Dimension^);
		}

		property fk_Color^ ShadowColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		property fk_Color^ ForeColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		property fk_Color^ BackColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		property bool SmoothMode {
			bool get();
			void set(bool);
		}

		property bool MonospaceMode {
			bool get();
			void set(bool);
		}

		property int MonospaceSize {
			int get();
			void set(int);
		}

		property int CharSkip {
			int get();
			void set(int);
		}
		
		property int LineSkip {
			int get();
			void set(int);
		}

		property int SpaceLineSkip {
			int get();
			void set(int);
		}

		property fk_TextAlign Align {
			fk_TextAlign get();
			void set(fk_TextAlign);
		}

		property int MinLineWidth {
			int get();
			void set(int);
		}

		property int LineNum {
			int get();
		}
		
		property int AllCharNum {
			int get();
		}

		property int MaxLineWidth {
			int get();
		}

		property int MaxLineHeight {
			int get();
		}

		property fk_TextSendingMode SendingMode {
			fk_TextSendingMode get();
			void set(fk_TextSendingMode);
		}

		static property bool CacheMode {
			bool get();
			void set(bool);
		}
		
		bool	InitFont(String^ fontFileName);
		void	SetOffset(int up, int down, int left, int right);
		int		GetUpOffset(void);
		int		GetDownOffset(void);
		int		GetLeftOffset(void);
		int		GetRightOffset(void);
		bool	LoadUniStr(fk_UniStr^ str);
		bool	LoadStrFile(String^ fileName, fk_StringCode code);
		bool	LoadStrFile(String^ fileName);
		int		GetLineCharNum(int num);
		int		GetLineWidth(int num);
		int		GetLineHeight(int num);
		int		GetLineStartXPos(int num);
		int		GetLineStartYPos(int num);
		bool	Send(void);
		bool	Finish(void);
		bool	Clear(void);
		static void	ClearCache(void);
	};
}
