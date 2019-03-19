/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
#define FK_DEF_SIZETYPE

#include <FK/Material.h>
#include <FK/MatExample.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;
using namespace FK;

fk_Material::fk_Material()
	: fk_BaseObject(FK_MATERIAL)
{
	init();
}

void fk_Material::init(void)
{
	setAmbient(0.3, 0.3, 0.3);
	setDiffuse(0.0, 0.0, 0.0);
	setSpecular(1.0, 1.0, 1.0);
	setShininess(30.0);
}

fk_Material::fk_Material(const fk_Material &argMat)
	: fk_BaseObject(FK_MATERIAL)
{
	ambient = argMat.ambient;
	diffuse = argMat.diffuse;
	specular = argMat.specular;
	shininess = argMat.shininess;
}

fk_Material & fk_Material::operator =(const fk_Material &argMat)
{
	ambient = argMat.ambient;
	diffuse = argMat.diffuse;
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

	ambient.setA(argA);
	diffuse.setA(argA);
	specular.setA(argA);
	return;
}

void fk_Material::setAlpha(double argA)
{
	setAlpha(float(argA));
}

void fk_Material::setAmbient(fk_Color argC)
{
	ambient = argC;
}

void fk_Material::setDiffuse(fk_Color argC)
{
	diffuse = argC;
}

void fk_Material::setSpecular(fk_Color argC)
{
	specular = argC;
}

void fk_Material::setAmbDiff(fk_Color argC)
{
	setAmbient(argC);
	setDiffuse(argC);
}

void fk_Material::setAmbient(float argR, float argG, float argB, float argA)
{
	ambient.init(argR, argG, argB, argA);
}

void fk_Material::setDiffuse(float argR, float argG, float argB, float argA)
{
	diffuse.init(argR, argG, argB, argA);
}

void fk_Material::setSpecular(float argR, float argG, float argB, float argA)
{
	specular.init(argR, argG, argB, argA);
}

void fk_Material::setAmbDiff(float argR, float argG, float argB, float argA)
{
	ambient.init(argR, argG, argB, argA);  
	diffuse.init(argR, argG, argB, argA);
}

void fk_Material::setAmbient(double argR, double argG, double argB, double argA)
{
	ambient.init(float(argR), float(argG), float(argB), float(argA));
}

void fk_Material::setDiffuse(double argR, double argG, double argB, double argA)
{
	diffuse.init(float(argR), float(argG), float(argB), float(argA));
}

void fk_Material::setSpecular(double argR, double argG, double argB, double argA)
{
	specular.init(float(argR), float(argG), float(argB), float(argA));
}

void fk_Material::setAmbDiff(double argR, double argG, double argB, double argA)
{
	ambient.init(float(argR), float(argG), float(argB), float(argA));	
	diffuse.init(float(argR), float(argG), float(argB), float(argA));
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

float fk_Material::getAlpha(void) { return diffuse.getA(); }
fk_Color * fk_Material::getAmbient(void) { return &ambient; }
fk_Color * fk_Material::getDiffuse(void) { return &diffuse; }
fk_Color * fk_Material::getSpecular(void) { return &specular; }
float fk_Material::getShininess(void) { return shininess; }

namespace FK {
	bool operator ==(fk_Material argA, fk_Material argB)
	{
		float sh = argA.shininess - argB.shininess;
		return(fabs((float)sh) < FK_COLOR_EPS &&
			   argA.ambient == argB.ambient &&
			   argA.diffuse == argB.diffuse &&
			   argA.specular == argB.specular);
	}
}
	
void fk_Material::initDefault(void)
{
	fk_InitMaterial();
	return;
}

void fk_Material::setEmission(float, float, float) {}
void fk_Material::setEmission(double, double, double) {}
void fk_Material::setEmission(fk_Color) {}
fk_Color * fk_Material::getEmission(void) { return &ambient; }

void fk_Material::Print(int argTabSize, string argTag)
{
	string			tab;
	_st				i;
	stringstream	ss;
	
	tab.erase();
	for(i = 0; i < _st(argTabSize); i++) tab += '\t';

	if(argTag.size() == 0) {
		fk_PutError(tab + "Mat = {");
	} else {
		fk_PutError(tab + "Mat[" + argTag + "] = {");
	}

	ss << "\tamb = " << ambient.OutStr() << ";";
	fk_PutError(tab + ss.str());
	ss.clear();

	ss << "\tdiff = " << diffuse.OutStr() << ";";
	fk_PutError(tab + ss.str());
	ss.clear();

	ss << "\tspec = " << specular.OutStr() << ";";
	fk_PutError(tab + ss.str());
	ss.clear();

	ss << "\tshini = " << shininess << ";";
	fk_PutError(tab + ss.str());
	fk_PutError(tab + "}");
	
	return;
}
