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

		::fk_Color * GetP(void);

	public:
		fk_Color();
		fk_Color(bool argNewFlg);
		fk_Color(double, double, double);
		fk_Color(double, double, double, double);
		fk_Color(float, float, float);
		fk_Color(float, float, float, float);
		~fk_Color();
		!fk_Color();

		property float col[int] {
			float get(int argI);
			void set(int argI, float argC);
		}

		property float r {
			float get();
			void set(float argF);
		}

		property float g {
			float get();
			void set(float argF);
		}

		property float b {
			float get();
			void set(float argF);
		}

		property float a {
			float get();
			void set(float argF);
		}

		bool fk_Color::Equals(fk_Color^ argC);
		virtual bool fk_Color::Equals(Object^ argObj) override;
		String^ fk_Color::ToString() override;

		void Init(void);
		void Init(float argR, float argG, float argB);
		void Init(float argR, float argG, float argB, float argA);
		void Init(double argR, double argG, double argB);
		void Init(double argR, double argG, double argB, double argA);
		void Set(float argR, float argG, float argB);
		void Set(float argR, float argG, float argB, float argA);
		void Set(double argR, double argG, double argB);
		void Set(double argR, double argG, double argB, double argA);
		void SetHSV(double argH, double argS, double argV);
	};

	public ref class fk_Material {
	internal:
		bool dFlg;
		::fk_Material *pMat;

		::fk_Material * GetP(void);

	public:
		fk_Material();
		fk_Material(bool argNewFlg);
		~fk_Material();
		!fk_Material();

		bool Equals(fk_Material^ argM);
		virtual bool Equals(Object^ argObj) override;

		property float Alpha {
			float get();
			void set(float argF);
		}

		property fk_Color^ Ambient {
			fk_Color^ get();
			void set(fk_Color^ argC);
		}

		property fk_Color^ Diffuse {
			fk_Color^ get();
			void set(fk_Color^ argC);
		}

		property fk_Color^ Specular {
			fk_Color^ get();
			void set(fk_Color^ argC);
		}

		property fk_Color^ Emission {
			fk_Color^ get();
			void set(fk_Color^ argC);
		}

		void Init(void);
		static void InitDefault(void);

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
