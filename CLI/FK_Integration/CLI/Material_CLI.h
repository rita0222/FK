// Material_CLI.h

#pragma once

#include <FK/Material.h>
#include "Base_CLI.h"

using namespace std;
using namespace System;

namespace FK_CLI
{
	public ref class fk_Color : fk_BaseObject {
	public:
		fk_Color::fk_Color() : fk_BaseObject(false)
		{
			::fk_Color *p = new ::fk_Color();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Color::fk_Color(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) {
				::fk_Color *p = new ::fk_Color();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_Color::~fk_Color()
		{
			this->!fk_Color();
		}

		fk_Color::!fk_Color()
		{
			delete this->pBase;
			this->pBase = NULL;
		}

		property float col[int]
		{
			float get(int argI) {
				::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
				return p->col[argI];
			}
			void set(int argI, float argC)
			{
				::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
				p->col[argI] = argC;
			}
		}

		property float r
		{
			float get()
			{
				::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
				return p->col[0];
			}

			void set(float argF)
			{
				::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
				p->col[0] = argF;
			}
		}

		property float g
		{
			float get()
			{
				::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
				return p->col[1];
			}

			void set(float argF)
			{
				::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
				p->col[1] = argF;
			}
		}

		property float b
		{
			float get()
			{
				::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
				return p->col[2];
			}

			void set(float argF)
			{
				::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
				p->col[2] = argF;
			}
		}

		property float a
		{
			float get()
			{
				::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
				return p->col[3];
			}

			void set(float argF)
			{
				::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
				p->col[3] = argF;
			}
		}

		String^ fk_Color::ToString() override
		{
			::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
			std::string tmpBuf;

			tmpBuf = "C: ";
			for(int i = 0; i < 4; i++) {
				tmpBuf += to_string(p->col[i]);
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
			::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
			::fk_Color *p2 = reinterpret_cast<::fk_Color *>(argC->pBase);
			return (*p == *p2);
		}

		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_Color^ C = static_cast<fk_Color^>(argObj);
				::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
				::fk_Color *p2 = reinterpret_cast<::fk_Color *>(C->pBase);
				return (*p == *p2);
			}
			return false;
		}

		void init(void)
		{
			::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
			p->init();
		}


		void init(float argR, float argG, float argB)
		{
			::fk_Color *p = reinterpret_cast<::fk_Color *>(this->pBase);
			p->init(argR, argG, argB, 1.0f);
		}

		void init(float argR, float argG, float argB, float argA)
		{
			::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
			p->init(argR, argG, argB, argA);
		}

		void init(double argR, double argG, double argB)
		{
			::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
			p->init(argR, argG, argB, 1.0);
		}

		void init(double argR, double argG, double argB, double argA)
		{
			::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
			p->init(argR, argG, argB, argA);
		}

		void set(float argR, float argG, float argB)
		{
			::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
			p->set(argR, argG, argB, 1.0f);
		}

		void set(float argR, float argG, float argB, float argA)
		{
			::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
			p->set(argR, argG, argB, argA);
		}

		void set(double argR, double argG, double argB)
		{
			::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
			p->set(argR, argG, argB, 1.0);
		}

		void set(double argR, double argG, double argB, double argA)
		{
			::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
			p->set(argR, argG, argB, argA);
		}

		void setHSV(double argH, double argS, double argV)
		{
			::fk_Color *p = reinterpret_cast<::fk_Color *>(pBase);
			p->setHSV(argH, argS, argV);
		}
	};

	public ref class fk_Material : fk_BaseObject {
	public:
		fk_Material::fk_Material() : fk_BaseObject(false)
		{
			::fk_Material *p = new ::fk_Material();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Material::fk_Material(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) {
				::fk_Material *p = new ::fk_Material();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_Material::~fk_Material()
		{
			this->!fk_Material();
		}

		fk_Material::!fk_Material()
		{
			delete this->pBase;
			this->pBase = NULL;
		}

		bool Equals(fk_Material^ argM)
		{
			if(!argM) false;
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			::fk_Material *p2 = reinterpret_cast<::fk_Material *>(argM->pBase);
			return (*p == *p2);
		}

		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_Material^ M = static_cast<fk_Material^>(argObj);
				::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
				::fk_Material *p2 = reinterpret_cast<::fk_Material *>(M->pBase);
				return (*p == *p2);
			}
			return false;
		}

		property float alpha
		{
			float get()
			{
				::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
				return p->getAlpha();
			}

			void set(float argF)
			{
				::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
				p->setAlpha(argF);
			}
		}

		property fk_Color^ ambient
		{
			fk_Color^ get()
			{
				::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
				fk_Color^ C = gcnew fk_Color();
				::fk_Color *pC = reinterpret_cast<::fk_Color *>(C->pBase);
				*pC = *(p->getAmbient());
				return C;
			}

			void set(fk_Color^ argC)
			{
				if(!argC) return;
														 
				::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
				::fk_Color *pC = reinterpret_cast<::fk_Color *>(argC->pBase);
				p->setAmbient(*pC);
			}
		}

		property fk_Color^ diffuse
		{
			fk_Color^ get()
			{
				fk_Color^ C = gcnew fk_Color();
				::fk_Color *pC = reinterpret_cast<::fk_Color *>(C->pBase);
				::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
				*pC = *(p->getDiffuse());
				return C;
			}

			void set(fk_Color^ argC)
			{
				if(!argC) return;
				::fk_Color *pC = reinterpret_cast<::fk_Color *>(argC->pBase);
				::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
				p->setDiffuse(*pC);
			}
		}

		property fk_Color^ specular
		{
			fk_Color^ get()
			{
				fk_Color^ C = gcnew fk_Color();
				::fk_Color *pC = reinterpret_cast<::fk_Color *>(C->pBase);
				::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
				*pC = *(p->getSpecular());
				return C;
			}

			void set(fk_Color^ argC)
			{
				if(!argC) return;
				::fk_Color *pC = reinterpret_cast<::fk_Color *>(argC->pBase);
				::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
				p->setSpecular(*pC);
			}
		}

		property fk_Color^ emission
		{
			fk_Color^ get()
			{
				fk_Color^ C = gcnew fk_Color();
				::fk_Color *pC = reinterpret_cast<::fk_Color *>(C->pBase);
				::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
				*pC = *(p->getEmission());
				return C;
			}

			void set(fk_Color^ argC)
			{
				if(!argC) return;
				::fk_Color *pC = reinterpret_cast<::fk_Color *>(argC->pBase);
				::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
				p->setEmission(*pC);
			}
		}

		void init(void)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			p->init();
		}

		void setAmbient(float argR, float argG, float argB)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			p->setAmbient(argR, argG, argB);
		}

		void setAmbient(double argR, double argG, double argB)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			p->setAmbient(argR, argG, argB);
		}

		void setDiffuse(float argR, float argG, float argB)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			p->setDiffuse(argR, argG, argB);
		}

		void setDiffuse(double argR, double argG, double argB)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			p->setDiffuse(argR, argG, argB);
		}

		void setSpecular(float argR, float argG, float argB)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			p->setSpecular(argR, argG, argB);
		}

		void setSpecular(double argR, double argG, double argB)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			p->setSpecular(argR, argG, argB);
		}

		void setEmission(float argR, float argG, float argB)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			p->setEmission(argR, argG, argB);
		}

		void setEmission(double argR, double argG, double argB)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			p->setEmission(argR, argG, argB);
		}

		void setAmbDiff(float argR, float argG, float argB)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			p->setAmbDiff(argR, argG, argB);
		}

		void setAmbDiff(double argR, double argG, double argB)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			p->setAmbDiff(argR, argG, argB);
		}

		void setAmbDiff(fk_Color^ argC)
		{
			::fk_Material *p = reinterpret_cast<::fk_Material *>(pBase);
			::fk_Color *pC = reinterpret_cast<::fk_Color *>(argC->pBase);
			p->setAmbDiff(*pC);
		}

		static void	initDefault(void)
		{
			::fk_Material::initDefault();
		}
	};
}
