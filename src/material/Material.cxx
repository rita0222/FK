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
#include <FK/Material.h>
#include <FK/MatExample.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;

fk_Color::fk_Color(float argR, float argG, float argB, float argA)
	: fk_BaseObject(FK_COLOR)
{
	init(argR, argG, argB, argA);
}


fk_Color::fk_Color(double argR, double argG, double argB, double argA)
	: fk_BaseObject(FK_COLOR)
{
	init(argR, argG, argB, argA);
}

void fk_Color::init(void) { init(0.0f, 0.0f, 0.0f, 1.0f); }

void fk_Color::init(float argR, float argG, float argB, float argA)
{
	col[0] = clamp(argR);
	col[1] = clamp(argG);
	col[2] = clamp(argB);
	col[3] = clamp(argA);
	return;
}

void fk_Color::init(double argR, double argG, double argB, double argA)
{
	init(float(argR), float(argG), float(argB), float(argA));
	return;
}

void fk_Color::set(float argR, float argG, float argB, float argA)
{
	init(argR, argG, argB, argA);
}

void fk_Color::set(double argR, double argG, double argB, double argA)
{
	init(argR, argG, argB, argA);
}

float fk_Color::clamp(float argX)
{
	if(argX > 0.0f) {
		return (argX < 1.0f) ? argX : 1.0f;
	}
	return 0.0f;
}

double fk_Color::clamp(double argX)
{
	if(argX > 0.0) {
		return (argX < 1.0) ? argX : 1.0;
	}
	return 0.0;
}

fk_Color::fk_Color(const fk_Color &argColor)
	: fk_BaseObject(FK_COLOR)
{
	init(argColor.col[0], argColor.col[1], argColor.col[2], argColor.col[3]);
}

fk_Color & fk_Color::operator =(const fk_Color &argColor)
{
	init(argColor.col[0], argColor.col[1], argColor.col[2], argColor.col[3]);

	return *this;
}

namespace FK {
	bool operator ==(fk_Color argA, fk_Color argB)
	{
		float r, g, b, a;

		r = argA.col[0] - argB.col[0];
		g = argA.col[1] - argB.col[1];
		b = argA.col[2] - argB.col[2];
		a = argA.col[3] - argB.col[3];

		return(fabs((float)r) < FK_COLOR_EPS &&
			   fabs((float)g) < FK_COLOR_EPS &&
			   fabs((float)b) < FK_COLOR_EPS &&
			   fabs((float)a) < FK_COLOR_EPS);
	}
}

fk_Color & fk_Color::operator *=(double argD)
{
	for(int i = 0; i < 3; i++) {
		col[i] = clamp(col[i] * float(argD));
	}

	return *this;
}

fk_Color & fk_Color::operator /=(double argD)
{
	if(fabs(argD) < FK_COLOR_EPS) return *this;

	for(int i = 0; i < 3; i++) {
		col[i] = clamp(col[i] / float(argD));
	}

	return *this;
}

fk_Color & fk_Color::operator +=(const fk_Color &argC)
{
	for(int i = 0; i < 3; i++) {
		col[i] = clamp(col[i] + argC.col[i]);
	}

	return *this;
}

fk_Color & fk_Color::operator -=(const fk_Color &argC)
{
	for(int i = 0; i < 3; i++) {
		col[i] = clamp(col[i] - argC.col[i]);
	}

	return *this;
}

void fk_Color::setR(float argR) { col[0] = clamp(argR); }
void fk_Color::setG(float argG) { col[1] = clamp(argG); }
void fk_Color::setB(float argB) { col[2] = clamp(argB); }
void fk_Color::setA(float argA) { col[3] = clamp(argA); }

void fk_Color::setR(double argR) { col[0] = clamp(float(argR)); }
void fk_Color::setG(double argG) { col[1] = clamp(float(argG)); }
void fk_Color::setB(double argB) { col[2] = clamp(float(argB)); }
void fk_Color::setA(double argA) { col[3] = clamp(float(argA)); }

float fk_Color::getR(void) const { return col[0]; }
float fk_Color::getG(void) const { return col[1]; }
float fk_Color::getB(void) const { return col[2]; }
float fk_Color::getA(void) const { return col[3]; }


void fk_Color::setHSV(double argH, double argS, double argV)
{
	double	f, p, q, t, H_r;
	int		H, H_n;

	H_n = int(floor(argH/(2.0*FK_PI)));
	H_r = argH - (double(H_n) * 2.0 * FK_PI);
	H = int(floor(H_r * 3.0 / FK_PI));

	f = 3.0*H_r/FK_PI - H;
	p = argV*(1.0 - argS);
	q = argV*(1.0 - f*argS);
	t = argV*(1.0 - (1.0 - f)*argS);

	switch(H) {
	  case 0:
		col[0] = float(argV); col[1] = float(t); col[2] = float(p);
		break;

	  case 1:
		col[0] = float(q); col[1] = float(argV); col[2] = float(p);
		break;

	  case 2:
		col[0] = float(p); col[1] = float(argV); col[2] = float(t);
		break;

	  case 3:
		col[0] = float(p); col[1] = float(q); col[2] = float(argV);
		break;

	  case 4:
		col[0] = float(t); col[1] = float(p); col[2] = float(argV);
		break;

	  case 5:
		col[0] = float(argV); col[1] = float(p); col[2] = float(q);
		break;

	  default:
		break;
	}

	return;
}

// friend 宣言による外部関数化した二項演算子

fk_Color operator +(const fk_Color &argA, const fk_Color &argB)
{
	fk_Color	tmp(fk_Color::clamp(argA.col[0] + argB.col[0]),
					fk_Color::clamp(argA.col[1] + argB.col[1]),
					fk_Color::clamp(argA.col[2] + argB.col[2]),
					fk_Color::clamp(argA.col[3] + argB.col[3]));

	return tmp;
}
					
fk_Color operator -(const fk_Color &argA, const fk_Color &argB)
{
	fk_Color	tmp(fk_Color::clamp(argA.col[0] - argB.col[0]),
					fk_Color::clamp(argA.col[1] - argB.col[1]),
					fk_Color::clamp(argA.col[2] - argB.col[2]),
					fk_Color::clamp(argA.col[3] - argB.col[3]));

	return tmp;
}

fk_Color operator *(const fk_Color &argC, double argD)
{
	fk_Color	tmp(fk_Color::clamp(argC.col[0] * float(argD)),
					fk_Color::clamp(argC.col[1] * float(argD)),
					fk_Color::clamp(argC.col[2] * float(argD)),
					fk_Color::clamp(argC.col[3] * float(argD)));

	return tmp;
}
					
fk_Color operator *(double argD, const fk_Color &argC)
{
	fk_Color	tmp(fk_Color::clamp(argC.col[0] * float(argD)),
					fk_Color::clamp(argC.col[1] * float(argD)),
					fk_Color::clamp(argC.col[2] * float(argD)),
					fk_Color::clamp(argC.col[3] * float(argD)));

	return tmp;
}
					
fk_Color	operator /(const fk_Color &argC, double argD)
{
	if(fabs(argD) < FK_COLOR_EPS) return argC;

	fk_Color	tmp(fk_Color::clamp(argC.col[0] / float(argD)),
					fk_Color::clamp(argC.col[1] / float(argD)),
					fk_Color::clamp(argC.col[2] / float(argD)),
					fk_Color::clamp(argC.col[3] / float(argD)));

	return tmp;
}

fk_Material::fk_Material()
	: fk_BaseObject(FK_MATERIAL)
{
	init();
}

void fk_Material::init(void)
{
	setAlpha(1.0f);
	setAmbient(0.3f, 0.3f, 0.3f);
	setDiffuse(0.0f, 0.0f, 0.0f);
	setEmission(0.0f, 0.0f, 0.0f);
	setSpecular(0.2f, 0.2f, 0.2f);
	setShininess(17.0f);
}

fk_Material::fk_Material(const fk_Material &argMat)
	: fk_BaseObject(FK_MATERIAL)
{
	alpha = argMat.alpha;
	ambient = argMat.ambient;
	diffuse = argMat.diffuse;
	emission = argMat.emission;
	specular = argMat.specular;
	shininess = argMat.shininess;
}

fk_Material & fk_Material::operator =(const fk_Material &argMat)
{
	alpha = argMat.alpha;
	ambient = argMat.ambient;
	diffuse = argMat.diffuse;
	emission = argMat.emission;
	specular = argMat.specular;
	shininess = argMat.shininess;

	return *this;
}

void fk_Material::setAlpha(float argA)
{
	if(argA < -FK_COLOR_EPS || argA > 1.0f + FK_COLOR_EPS) {
		fk_PutError("fk_Material", "setAlpha", 1,
					"Alpha Value Error.");
		return;
	}
	alpha = argA;

	ambient.setA(argA);
	diffuse.setA(argA);
	emission.setA(argA);
	specular.setA(argA);
}

void fk_Material::setAlpha(double argA)
{
	setAlpha(float(argA));
	return;
}

void fk_Material::setAmbient(fk_Color argC)
{
	ambient = argC;
	ambient.setA(alpha);
}

void fk_Material::setDiffuse(fk_Color argC)
{
	diffuse = argC;
	diffuse.setA(alpha);
}

void fk_Material::setEmission(fk_Color argC)
{
	emission = argC;
	emission.setA(alpha);
}

void fk_Material::setSpecular(fk_Color argC)
{
	specular = argC;
	specular.setA(alpha);
}

void fk_Material::setAmbDiff(fk_Color argC)
{
	setAmbient(argC);
	setDiffuse(argC);
}

void fk_Material::setAmbient(float argR, float argG, float argB)
{
	ambient.init(argR, argG, argB, alpha);
}

void fk_Material::setDiffuse(float argR, float argG, float argB)
{
	diffuse.init(argR, argG, argB, alpha);
}

void fk_Material::setEmission(float argR, float argG, float argB)
{
	emission.init(argR, argG, argB, alpha);

}

void fk_Material::setSpecular(float argR, float argG, float argB)
{
	specular.init(argR, argG, argB, alpha);
}

void fk_Material::setAmbDiff(float argR, float argG, float argB)
{
	ambient.init(argR, argG, argB, alpha);  
	diffuse.init(argR, argG, argB, alpha);
}

void fk_Material::setAmbient(double argR, double argG, double argB)
{
	ambient.init(float(argR), float(argG), float(argB), alpha);
}

void fk_Material::setDiffuse(double argR, double argG, double argB)
{
	diffuse.init(float(argR), float(argG), float(argB), alpha);
}

void fk_Material::setEmission(double argR, double argG, double argB)
{
	emission.init(float(argR), float(argG), float(argB), alpha);

}

void fk_Material::setSpecular(double argR, double argG, double argB)
{
	specular.init(float(argR), float(argG), float(argB), alpha);
}

void fk_Material::setAmbDiff(double argR, double argG, double argB)
{
	ambient.init(float(argR), float(argG), float(argB), alpha);	
	diffuse.init(float(argR), float(argG), float(argB), alpha);
}

void fk_Material::setShininess(float argS)
{
	if(argS < -FK_COLOR_EPS || argS > 128.0f + FK_COLOR_EPS) {
		fk_PutError("fk_Material", "setShininess", 1,
					"Shininess Value Error.");
		return;
	}
	shininess = argS;
}

void fk_Material::setShininess(double argS)
{
	setShininess(float(argS));
	return;
}

float fk_Material::getAlpha(void) { return alpha; }
fk_Color * fk_Material::getAmbient(void) { return &ambient; }
fk_Color * fk_Material::getDiffuse(void) { return &diffuse; }
fk_Color * fk_Material::getEmission(void) { return &emission; }
fk_Color * fk_Material::getSpecular(void) { return &specular; }
float fk_Material::getShininess(void) { return shininess; }

namespace FK {
	bool operator ==(fk_Material argA, fk_Material argB)
	{
		float al, sh;

		al = argA.alpha - argB.alpha;
		sh = argA.shininess - argB.shininess;
		return(fabs((float)al) < FK_COLOR_EPS &&
			   fabs((float)sh) < FK_COLOR_EPS &&
			   argA.ambient == argB.ambient &&
			   argA.diffuse == argB.diffuse &&
			   argA.emission == argB.emission &&
			   argA.specular == argB.specular);
	}
}
	
void fk_Material::initDefault(void)
{
	fk_InitMaterial();
	return;
}

void fk_Material::Print(int argTabSize, string argTag)
{
	string			tab;
	int				i;
	stringstream	ss;
	
	tab.erase();
	for(i = 0; i < argTabSize; i++) tab += '\t';

	if(argTag.size() == 0) {
		fk_PutError(tab + "Mat = {");
	} else {
		fk_PutError(tab + "Mat[" + argTag + "] = {");
	}

	ss << "\talpha = " << alpha << ";";
	fk_PutError(tab + ss.str());
	ss.clear();

	ss << "\tamb = (";
	for(i = 0; i < 4; i++) {
		ss << ambient.col[i];
		if(i != 3) ss << ", ";
	}
	ss << ");";
	fk_PutError(tab + ss.str());
	ss.clear();

	ss << "\tdiff = (";
	for(i = 0; i < 4; i++) {
		ss << diffuse.col[i];
		if(i != 3) ss << ", ";
	}
	ss << ");";
	fk_PutError(tab + ss.str());
	ss.clear();

	ss << "\tspec = (";
	for(i = 0; i < 4; i++) {
		ss << specular.col[i];
		if(i != 3) ss << ", ";
	}
	ss << ");";
	fk_PutError(tab + ss.str());
	ss.clear();

	ss << "\temis = (";
	for(i = 0; i < 4; i++) {
		ss << emission.col[i];
		if(i != 3) ss << ", ";
	}
	ss << ");";
	fk_PutError(tab + ss.str());
	ss.clear();

	ss << "\tshini = " << shininess << ";";
	fk_PutError(tab + ss.str());

	fk_PutError(tab + "}");
	
	return;
}
