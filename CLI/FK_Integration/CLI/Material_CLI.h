// Material_CLI.h

#pragma once

#include <FK/Material.h>
#include <FK/MatExample.h>
#include "Base_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;

	public ref class fk_Color {
	internal:
		bool dFlg;
		::fk_Color *pCol;

		::fk_Color * GetP(void)
		{
			return pCol;
		}

	public:
		fk_Color::fk_Color() : dFlg(true)
		{
			pCol = new ::fk_Color();
		}

		fk_Color::fk_Color(bool argNewFlg) : dFlg(argNewFlg)
		{
			if(argNewFlg == true) pCol = new ::fk_Color();
		}

		fk_Color::~fk_Color()
		{
			this->!fk_Color();
		}

		fk_Color::!fk_Color()
		{
			if(dFlg == true) delete pCol;
			pCol = NULL;
		}

		property float col[int]
		{
			float get(int argI) {
				return GetP()->col[argI];
			}
			void set(int argI, float argC)
			{
				GetP()->col[argI] = argC;
			}
		}

		property float r
		{
			float get()
			{
				return GetP()->col[0];
			}

			void set(float argF)
			{
				GetP()->col[0] = argF;
			}
		}

		property float g
		{
			float get()
			{
				return GetP()->col[1];
			}

			void set(float argF)
			{
				GetP()->col[1] = argF;
			}
		}

		property float b
		{
			float get()
			{
				return GetP()->col[2];
			}

			void set(float argF)
			{
				GetP()->col[2] = argF;
			}
		}

		property float a
		{
			float get()
			{
				return GetP()->col[3];
			}

			void set(float argF)
			{
				GetP()->col[3] = argF;
			}
		}

		String^ fk_Color::ToString() override
		{
			std::string tmpBuf;

			tmpBuf = "C: ";
			for(int i = 0; i < 4; i++) {
				tmpBuf += to_string(GetP()->col[i]);
				if(i != 3) {
					tmpBuf += ", ";
				} else {
					tmpBuf += "\n";
				}
			}
			return gcnew String(tmpBuf.c_str());
		}

		bool Equals(fk_Color^ argC)
		{
			if(!argC) false;
			return (*GetP() == *argC->GetP());
		}

		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_Color^ C = static_cast<fk_Color^>(argObj);
				return (*GetP() == *C->GetP());
			}
			return false;
		}

		void init(void)
		{
			GetP()->init();
		}


		void init(float argR, float argG, float argB)
		{
			GetP()->init(argR, argG, argB, 1.0f);
		}

		void init(float argR, float argG, float argB, float argA)
		{
			GetP()->init(argR, argG, argB, argA);
		}

		void init(double argR, double argG, double argB)
		{
			GetP()->init(argR, argG, argB, 1.0);
		}

		void init(double argR, double argG, double argB, double argA)
		{
			GetP()->init(argR, argG, argB, argA);
		}

		void set(float argR, float argG, float argB)
		{
			GetP()->set(argR, argG, argB, 1.0f);
		}

		void set(float argR, float argG, float argB, float argA)
		{
			GetP()->set(argR, argG, argB, argA);
		}

		void set(double argR, double argG, double argB)
		{
			GetP()->set(argR, argG, argB, 1.0);
		}

		void set(double argR, double argG, double argB, double argA)
		{
			GetP()->set(argR, argG, argB, argA);
		}

		void setHSV(double argH, double argS, double argV)
		{
			GetP()->setHSV(argH, argS, argV);
		}
	};

	public ref class fk_Material {
	internal:
		bool dFlg;
		::fk_Material *pMat;

		::fk_Material * GetP(void)
		{
			return pMat;
		}

	public:
		fk_Material::fk_Material() : dFlg(true)
		{
			pMat = new ::fk_Material();
		}

		fk_Material::fk_Material(bool argNewFlg) : dFlg(argNewFlg)
		{
			if(argNewFlg == true) pMat = new ::fk_Material();
		}

		fk_Material::~fk_Material()
		{
			this->!fk_Material();
		}

		fk_Material::!fk_Material()
		{
			if(dFlg == true) delete pMat;
			pMat = NULL;
		}

		bool Equals(fk_Material^ argM)
		{
			if(!argM) false;
			return (*GetP() == *argM->GetP());
		}

		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_Material^ M = static_cast<fk_Material^>(argObj);
				return (*GetP() == *M->GetP());
			}
			return false;
		}

		property float alpha
		{
			float get()
			{
				return GetP()->getAlpha();
			}

			void set(float argF)
			{
				GetP()->setAlpha(argF);
			}
		}

		property fk_Color^ ambient
		{
			fk_Color^ get()
			{
				fk_Color^ C = gcnew fk_Color();
				*C->pCol = *(GetP()->getAmbient());
				return C;
			}

			void set(fk_Color^ argC)
			{
				if(!argC) return;
				GetP()->setAmbient(*argC->pCol);
			}
		}

		property fk_Color^ diffuse
		{
			fk_Color^ get()
			{
				fk_Color^ C = gcnew fk_Color();
				*C->pCol = *(GetP()->getDiffuse());
				return C;
			}

			void set(fk_Color^ argC)
			{
				if(!argC) return;
				GetP()->setDiffuse(*argC->pCol);
			}
		}

		property fk_Color^ specular
		{
			fk_Color^ get()
			{
				fk_Color^ C = gcnew fk_Color();
				*C->pCol = *(GetP()->getSpecular());				
				return C;
			}

			void set(fk_Color^ argC)
			{
				if(!argC) return;
				GetP()->setSpecular(*argC->pCol);
			}
		}

		property fk_Color^ emission
		{
			fk_Color^ get()
			{
				fk_Color^ C = gcnew fk_Color();
				*C->pCol = *(GetP()->getEmission());
				return C;
			}

			void set(fk_Color^ argC)
			{
				if(!argC) return;
				GetP()->setEmission(*argC->pCol);
			}
		}

		void init(void)
		{
			GetP()->init();
		}

		void setAmbient(float argR, float argG, float argB)
		{
			GetP()->setAmbient(argR, argG, argB);
		}

		void setAmbient(double argR, double argG, double argB)
		{
			GetP()->setAmbient(argR, argG, argB);
		}

		void setDiffuse(float argR, float argG, float argB)
		{
			GetP()->setDiffuse(argR, argG, argB);
		}

		void setDiffuse(double argR, double argG, double argB)
		{
			GetP()->setDiffuse(argR, argG, argB);
		}

		void setSpecular(float argR, float argG, float argB)
		{
			GetP()->setSpecular(argR, argG, argB);
		}

		void setSpecular(double argR, double argG, double argB)
		{
			GetP()->setSpecular(argR, argG, argB);
		}

		void setEmission(float argR, float argG, float argB)
		{
			GetP()->setEmission(argR, argG, argB);
		}

		void setEmission(double argR, double argG, double argB)
		{
			GetP()->setEmission(argR, argG, argB);
		}

		void setAmbDiff(float argR, float argG, float argB)
		{
			GetP()->setAmbDiff(argR, argG, argB);
		}

		void setAmbDiff(double argR, double argG, double argB)
		{
			GetP()->setAmbDiff(argR, argG, argB);
		}

		void setAmbDiff(fk_Color^ argC)
		{
			if(!argC) return;
			GetP()->setAmbDiff(*argC->pCol);
		}

		static fk_Material^ LightCyan;
		static fk_Material^ AshGray;
		static fk_Material^ BurntTitan;
		static fk_Material^ IridescentGreen;
		static fk_Material^ UltraMarine;
		static fk_Material^ Ivory;
		static fk_Material^ BambooGreen;
		static fk_Material^ PearWhite;
		static fk_Material^ Lilac;
		static fk_Material^ HolidaySkyBlue;
		static fk_Material^ DimYellow;
		static fk_Material^ LavaRed;
		static fk_Material^ GrassGreen;
		static fk_Material^ Red;
		static fk_Material^ Pink;
		static fk_Material^ DarkRed;
		static fk_Material^ Orange;
		static fk_Material^ Flesh;
		static fk_Material^ Brown;
		static fk_Material^ Yellow;
		static fk_Material^ Cream;
		static fk_Material^ DarkYellow;
		static fk_Material^ Green;
		static fk_Material^ LightGreen;
		static fk_Material^ Cyan;
		static fk_Material^ PaleBlue;
		static fk_Material^ Blue;
		static fk_Material^ LightBlue;
		static fk_Material^ DarkGreen;
		static fk_Material^ DarkBlue;
		static fk_Material^ DarkPurple;
		static fk_Material^ Violet;
		static fk_Material^ Purple;
		static fk_Material^ LightViolet;
		static fk_Material^ Coral;
		static fk_Material^ White;
		static fk_Material^ Gray1;
		static fk_Material^ Gray2;
		static fk_Material^ GlossBlack;
		static fk_Material^ MatBlack;

		static void initDefault(void)
		{
			::fk_Material::initDefault();

			LightCyan = gcnew fk_Material();
			*LightCyan->pMat = ::LightCyan;

			AshGray = gcnew fk_Material();
			*AshGray->pMat = ::AshGray;

			BurntTitan = gcnew fk_Material();
			*BurntTitan->pMat = ::BurntTitan;

			IridescentGreen = gcnew fk_Material();
			*IridescentGreen->pMat = ::IridescentGreen;

			UltraMarine = gcnew fk_Material();
			*UltraMarine->pMat = ::UltraMarine;

			Ivory = gcnew fk_Material();
			*Ivory->pMat = ::Ivory;

			BambooGreen = gcnew fk_Material();
			*BambooGreen->pMat = ::BambooGreen;

			PearWhite = gcnew fk_Material();
			*PearWhite->pMat = ::PearWhite;

			Lilac = gcnew fk_Material();
			*Lilac->pMat = ::Lilac;

			HolidaySkyBlue = gcnew fk_Material();
			*HolidaySkyBlue->pMat = ::HolidaySkyBlue;

			DimYellow = gcnew fk_Material();
			*DimYellow->pMat = ::DimYellow;

			LavaRed = gcnew fk_Material();
			*LavaRed->pMat = ::LavaRed;

			GrassGreen = gcnew fk_Material();
			*GrassGreen->pMat = ::GrassGreen;

			Red = gcnew fk_Material();
			*Red->pMat = ::Red;

			Pink = gcnew fk_Material();
			*Pink->pMat = ::Pink;

			DarkRed = gcnew fk_Material();
			*DarkRed->pMat = ::DarkRed;

			Orange = gcnew fk_Material();
			*Orange->pMat = ::Orange;

			Flesh = gcnew fk_Material();
			*Flesh->pMat = ::Flesh;

			Brown = gcnew fk_Material();
			*Brown->pMat = ::Brown;

			Yellow = gcnew fk_Material();
			*Yellow->pMat = ::Yellow;

			Cream = gcnew fk_Material();
			*Cream->pMat = ::Cream;

			DarkYellow = gcnew fk_Material();
			*DarkYellow->pMat = ::DarkYellow;

			Green = gcnew fk_Material();
			*Green->pMat = ::Green;

			LightGreen = gcnew fk_Material();
			*LightGreen->pMat = ::LightGreen;

			Cyan = gcnew fk_Material();
			*Cyan->pMat = ::Cyan;

			PaleBlue = gcnew fk_Material();
			*PaleBlue->pMat = ::PaleBlue;

			Blue = gcnew fk_Material();
			*Blue->pMat = ::Blue;

			LightBlue = gcnew fk_Material();
			*LightBlue->pMat = ::LightBlue;

			DarkGreen = gcnew fk_Material();
			*DarkGreen->pMat = ::DarkGreen;

			DarkBlue = gcnew fk_Material();
			*DarkBlue->pMat = ::DarkBlue;

			DarkPurple = gcnew fk_Material();
			*DarkPurple->pMat = ::DarkPurple;

			Violet = gcnew fk_Material();
			*Violet->pMat = ::Violet;

			Purple = gcnew fk_Material();
			*Purple->pMat = ::Purple;

			LightViolet = gcnew fk_Material();
			*LightViolet->pMat = ::LightViolet;

			Coral = gcnew fk_Material();
			*Coral->pMat = ::Coral;

			White = gcnew fk_Material();
			*White->pMat = ::White;

			Gray1 = gcnew fk_Material();
			*Gray1->pMat = ::Gray1;

			Gray2 = gcnew fk_Material();
			*Gray2->pMat = ::Gray2;

			GlossBlack = gcnew fk_Material();
			*GlossBlack->pMat = ::GlossBlack;

			MatBlack = gcnew fk_Material();
			*MatBlack->pMat = ::MatBlack;
		}
	};
}
