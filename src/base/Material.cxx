/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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

fk_Color::fk_Color(float r, float g, float b)
	: fk_BaseObject(FK_COLOR)
{
	init(r, g, b, 1.0f);
}


fk_Color::fk_Color(double r, double g, double b)
	: fk_BaseObject(FK_COLOR)
{
	init(r, g, b, 1.0);
}

void fk_Color::init(void) { init(0.0f, 0.0f, 0.0f, 1.0f); }

void fk_Color::init(float r, float g, float b, float a)
{
	if(r < -FK_COLOR_EPS || r > 1.0f + FK_COLOR_EPS ||
	   g < -FK_COLOR_EPS || g > 1.0f + FK_COLOR_EPS ||
	   b < -FK_COLOR_EPS || b > 1.0f + FK_COLOR_EPS ||
	   a < -FK_COLOR_EPS || a > 1.0f + FK_COLOR_EPS) {
		fk_PutError("fk_Color", "init", 1, "Color Value Error,");
		return;
	}
	col[0] = r;
	col[1] = g;
	col[2] = b;
	col[3] = a;
	return;
}

void fk_Color::init(double r, double g, double b, double a)
{
	init(float(r), float(g), float(b), float(a));
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

void fk_Color::setR(float r) { init(r, col[1], col[2], col[3]);	}
void fk_Color::setG(float g) { init(col[0], g, col[2], col[3]);	}
void fk_Color::setB(float b) { init(col[0], col[1], b, col[3]);	}
void fk_Color::setA(float a) { init(col[0], col[1], col[2], a);	}

void fk_Color::setR(double r) { init(float(r), col[1], col[2], col[3]);	}
void fk_Color::setG(double g) { init(col[0], float(g), col[2], col[3]);	}
void fk_Color::setB(double b) { init(col[0], col[1], float(b), col[3]);	}
void fk_Color::setA(double a) { init(col[0], col[1], col[2], float(a));	}

float fk_Color::getR(void) const { return col[0]; }
float fk_Color::getG(void) const { return col[1]; }
float fk_Color::getB(void) const { return col[2]; }
float fk_Color::getA(void) const { return col[3]; }

bool operator ==(fk_Color A, fk_Color B)
{
	float r, g, b, a;

	r = A.col[0] - B.col[0];
	g = A.col[1] - B.col[1];
	b = A.col[2] - B.col[2];
	a = A.col[3] - B.col[3];

	return(fabs((float)r) < FK_COLOR_EPS &&
		   fabs((float)g) < FK_COLOR_EPS &&
		   fabs((float)b) < FK_COLOR_EPS &&
		   fabs((float)a) < FK_COLOR_EPS);
}

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

void fk_Material::setAlpha(float al)
{
	if(al < -FK_COLOR_EPS || al > 1.0f + FK_COLOR_EPS) {
		fk_PutError("fk_Material", "setAlpha", 1,
					"Alpha Value Error.");
		return;
	}
	alpha = al;

	ambient.setA(al);
	diffuse.setA(al);
	emission.setA(al);
	specular.setA(al);
}

void fk_Material::setAlpha(double al)
{
	setAlpha(float(al));
	return;
}

void fk_Material::setAmbient(fk_Color am)
{
	ambient = am;
	ambient.setA(alpha);
}

void fk_Material::setDiffuse(fk_Color di)
{
	diffuse = di;
	diffuse.setA(alpha);
}

void fk_Material::setEmission(fk_Color em)
{
	emission = em;
	emission.setA(alpha);
}

void fk_Material::setSpecular(fk_Color sp)
{
	specular = sp;
	specular.setA(alpha);
}

void fk_Material::setAmbDiff(fk_Color ad)
{
	diffuse = ad;
	diffuse.setA(alpha);
	ambient = ad;
	ambient.setA(alpha);
}

void fk_Material::setAmbient(float r, float g, float b)
{
	ambient.init(r, g, b, alpha);
}

void fk_Material::setDiffuse(float r, float g, float b)
{
	diffuse.init(r, g, b, alpha);
}

void fk_Material::setEmission(float r, float g, float b)
{
	emission.init(r, g, b, alpha);

}

void fk_Material::setSpecular(float r, float g, float b)
{
	specular.init(r, g, b, alpha);
}

void fk_Material::setAmbDiff(float r, float g, float b)
{
	ambient.init(r, g, b, alpha);  
	diffuse.init(r, g, b, alpha);
}

void fk_Material::setAmbient(double r, double g, double b)
{
	ambient.init(float(r), float(g), float(b), alpha);
}

void fk_Material::setDiffuse(double r, double g, double b)
{
	diffuse.init(float(r), float(g), float(b), alpha);
}

void fk_Material::setEmission(double r, double g, double b)
{
	emission.init(float(r), float(g), float(b), alpha);

}

void fk_Material::setSpecular(double r, double g, double b)
{
	specular.init(float(r), float(g), float(b), alpha);
}

void fk_Material::setAmbDiff(double r, double g, double b)
{
	ambient.init(float(r), float(g), float(b), alpha);	
	diffuse.init(float(r), float(g), float(b), alpha);
}

void fk_Material::setShininess(float sh)
{
	if(sh < -FK_COLOR_EPS || sh > 128.0f + FK_COLOR_EPS) {
		fk_PutError("fk_Material", "setShininess", 1,
					"Shininess Value Error.");
		return;
	}
	shininess = sh;
}

void fk_Material::setShininess(double sh)
{
	setShininess(float(sh));
	return;
}

float fk_Material::getAlpha(void) { return alpha; }
fk_Color * fk_Material::getAmbient(void) { return &ambient; }
fk_Color * fk_Material::getDiffuse(void) { return &diffuse; }
fk_Color * fk_Material::getEmission(void) { return &emission; }
fk_Color * fk_Material::getSpecular(void) { return &specular; }
float fk_Material::getShininess(void) { return shininess; }

int operator ==(fk_Material a, fk_Material b)
{
	float al, sh;

	al = a.alpha - b.alpha;
	sh = a.shininess - b.shininess;
	return(fabs((float)al) < FK_COLOR_EPS &&
		   fabs((float)sh) < FK_COLOR_EPS &&
		   a.ambient == b.ambient &&
		   a.diffuse == b.diffuse &&
		   a.emission == b.emission &&
		   a.specular == b.specular);
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
