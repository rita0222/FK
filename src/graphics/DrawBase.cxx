/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
#include <FK/DrawBase.H>
#include <FK/Matrix.h>
#include <FK/Model.h>
#include <FK/Light.h>
#include <FK/ShaderParameter.h>

using namespace std;
using namespace FK;

const string fk_DrawBase::projectionMatrixName = "fk_ProjectionMatrix";
const string fk_DrawBase::viewMatrixName = "fk_ViewMatrix";
const string fk_DrawBase::modelMatrixName = "fk_ModelMatrix";
const string fk_DrawBase::modelViewMatrixName = "fk_ModelViewMatrix";
const string fk_DrawBase::modelViewProjectionMatrixName = "fk_ModelViewProjectionMatrix";
const string fk_DrawBase::normalMatrixName = "fk_NormalMatrix";

const string fk_DrawBase::modelMaterialName = "fk_Material";
const string fk_DrawBase::diffuseName = "diffuse";
const string fk_DrawBase::ambientName = "ambient";

const string fk_DrawBase::lightName = "fk_Light";
const string fk_DrawBase::lightTypeName = "type";
const string fk_DrawBase::lightPositionName = "position";
const string fk_DrawBase::lightVecName = "vec";
const string fk_DrawBase::lightDiffuseName = "diffuse";
const string fk_DrawBase::lightSpecularName = "specular";
const string fk_DrawBase::lightNumName = "fk_LightNum";

const string fk_DrawBase::fragmentName = "fragment";

fk_Matrix * fk_DrawBase::projectionMatrix;
fk_Matrix fk_DrawBase::viewMatrix;
fk_Matrix fk_DrawBase::modelMatrix;
fk_Matrix fk_DrawBase::modelViewMatrix;
fk_Matrix fk_DrawBase::modelViewProjectionMatrix;
fk_Matrix fk_DrawBase::normalMatrix;
fk_Material * fk_DrawBase::modelMaterial;

list<fk_Model *> * fk_DrawBase::lightList;

fk_DrawBase::fk_DrawBase(void)
{
	return;
}

fk_DrawBase::~fk_DrawBase()
{
	return;
}

void fk_DrawBase::SetProjectionMatrix(fk_Matrix *argM)
{
	projectionMatrix = argM;
	return;
}

void fk_DrawBase::SetViewMatrix(fk_Model *argModel)
{
	viewMatrix = argModel->getInhInvMatrix();
	return;
}

void fk_DrawBase::SetModel(fk_Model *argModel)
{
	modelMatrix = argModel->getInhMatrix();
	modelViewMatrix = viewMatrix * modelMatrix;
	modelViewProjectionMatrix = (*projectionMatrix) * modelViewMatrix;
	modelMaterial = argModel->getMaterial();
	normalMatrix = modelMatrix;
	normalMatrix.covariant();
}

void fk_DrawBase::SetLight(list<fk_Model *> *argList)
{
	lightList = argList;
}

void fk_DrawBase::SetParameter(fk_ShaderParameter *argParam)
{
	SetMatrixParam(argParam);
	SetMaterialParam(argParam);
	SetLightParam(argParam);
	return;
}

void fk_DrawBase::SetMatrixParam(fk_ShaderParameter *argParam)
{
	argParam->setRegister(projectionMatrixName, projectionMatrix);
	argParam->setRegister(viewMatrixName, &viewMatrix);
	argParam->setRegister(modelMatrixName, &modelMatrix);
	argParam->setRegister(modelViewMatrixName, &modelViewMatrix);
	argParam->setRegister(modelViewProjectionMatrixName, &modelViewProjectionMatrix);
	argParam->setRegister(normalMatrixName, &normalMatrix);
	return;
}

void fk_DrawBase::SetMaterialParam(fk_ShaderParameter *argParam)
{
	argParam->setRegister(modelMaterialName + "." + diffuseName,
						  &(modelMaterial->getDiffuse()->col));
	argParam->setRegister(modelMaterialName + "." + ambientName,
						  &(modelMaterial->getAmbient()->col));
	return;
}

void fk_DrawBase::SetLightParam(fk_ShaderParameter *argParam)
{
	FK_UNUSED(argParam);
	int lightID = 0;
	int lightType;
	fk_Vector tmp;

	for(auto p = lightList->begin(); p != lightList->end(); ++p) {
		fk_Model *model = *p;
		fk_Light *light = dynamic_cast<fk_Light *>(model->getShape());

		string nameBase = lightName + "[" + to_string(lightID) + "]";

		switch(light->getLightType()) {
		  case FK_PARALLEL_LIGHT:
			  lightType = 1;
			  break;

		  case FK_POINT_LIGHT:
			  lightType = 2;
			  break;

		  case FK_SPOT_LIGHT:
			  lightType = 3;
			  break;

		  default:
			  lightType = 0;
		}
		argParam->setRegister(nameBase + "." + lightTypeName, lightType);

		tmp = model->getInhPosition();
		argParam->setRegister(nameBase + "." + lightPositionName, &tmp);

		tmp = model->getInhVec();
		argParam->setRegister(nameBase + "." + lightVecName, &tmp);

		argParam->setRegister(nameBase + "." + lightDiffuseName,
							  &(model->getMaterial()->getDiffuse()->col));
		argParam->setRegister(nameBase + "." + lightSpecularName,
							  &(model->getMaterial()->getSpecular()->col));
		++lightID;
		if(lightID >= fk_Light::MAXLIGHTNUM) break;
	}

	argParam->setRegister(lightNumName, lightID);
}

