// Material_CLI.h

#pragma once

#include <FK/Material.h>
#include <FK/MatExample.h>
#include "Base_CLI.h"

namespace FK_CLI
{
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

		property float col[int] {
			float get(int argI)
			{
				return GetP()->col[argI];
			}
			void set(int argI, float argC)
			{
				GetP()->col[argI] = argC;
			}
		}

		property float r {
			float get()
			{
				return GetP()->col[0];
			}

			void set(float argF)
			{
				GetP()->col[0] = argF;
			}
		}

		property float g {
			float get()
			{
				return GetP()->col[1];
			}

			void set(float argF)
			{
				GetP()->col[1] = argF;
			}
		}

		property float b {
			float get()
			{
				return GetP()->col[2];
			}

			void set(float argF)
			{
				GetP()->col[2] = argF;
			}
		}

		property float a {
			float get()
			{
				return GetP()->col[3];
			}

			void set(float argF)
			{
				GetP()->col[3] = argF;
			}
		}

		bool fk_Color::Equals(fk_Color^ argC)
		{
			if(!argC) false;
			return (*GetP() == *argC->GetP());
		}

		virtual bool fk_Color::Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_Color^ C = static_cast<fk_Color^>(argObj);
				return (*GetP() == *C->GetP());
			}
			return false;
		}

		String^ fk_Color::ToString() override;

		void init(void);
		void init(float argR, float argG, float argB);
		void init(float argR, float argG, float argB, float argA);
		void init(double argR, double argG, double argB);
		void init(double argR, double argG, double argB, double argA);
		void set(float argR, float argG, float argB);
		void set(float argR, float argG, float argB, float argA);
		void set(double argR, double argG, double argB);
		void set(double argR, double argG, double argB, double argA);
		void setHSV(double argH, double argS, double argV);
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

		property float alpha {
			float get()
			{
				return GetP()->getAlpha();
			}

			void set(float argF)
			{
				GetP()->setAlpha(argF);
			}
		}

		property fk_Color^ ambient {
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

		property fk_Color^ diffuse {
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

		property fk_Color^ specular {
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

		property fk_Color^ emission {
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

		void init(void);
		void setAmbient(float r, float g, float b);
		void setAmbient(double r, double g, double b);
		void setDiffuse(float r, float g, float b);
		void setDiffuse(double r, double g, double b);
		void setSpecular(float r, float g, float b);
		void setSpecular(double r, double g, double b);
		void setEmission(float r, float g, float b);
		void setEmission(double r, double g, double b);
		void setAmbDiff(float r, float g, float b);
		void setAmbDiff(double r, double g, double b);
		void setAmbDiff(fk_Color^ col);
		static void initDefault(void);

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
		static fk_Material^ TrueWhite;

	};
}
