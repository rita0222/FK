// Material_CLI.h

#pragma once

#include <FK/Material.h>
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

		static void	initDefault(void)
		{
			::fk_Material::initDefault();
		}
	};
}
