﻿#define FK_DEF_SIZETYPE
#include <FK/DrawBase.H>
#include <FK/Matrix.h>
#include <FK/Model.h>
#include <FK/Light.h>
#include <FK/ShaderBinder.h>

using namespace std;
using namespace FK;

const string fk_DrawBase::projectionMatrixName = "fk_ProjectionMatrix";
const string fk_DrawBase::viewMatrixName = "fk_ViewMatrix";
const string fk_DrawBase::modelMatrixName = "fk_ModelMatrix";
const string fk_DrawBase::modelViewMatrixName = "fk_ModelViewMatrix";
const string fk_DrawBase::modelViewProjectionMatrixName = "fk_ModelViewProjectionMatrix";
const string fk_DrawBase::normalModelMatrixName = "fk_NormalModelMatrix";
const string fk_DrawBase::normalModelViewMatrixName = "fk_NormalModelViewMatrix";
const string fk_DrawBase::cameraPositionName = "fk_CameraPosition";

const string fk_DrawBase::shadowMatrixName = "fk_ShadowMatrix";
const string fk_DrawBase::shadowVisibilityName = "fk_ShadowVisibility";
const string fk_DrawBase::shadowBiasName = "fk_ShadowBias";

const string fk_DrawBase::fogColorName = "fk_FogColor";
const string fk_DrawBase::fogParamName = "fk_FogParam";

const string fk_DrawBase::modelMaterialName = "fk_Material";
const string fk_DrawBase::diffuseName = "diffuse";
const string fk_DrawBase::ambientName = "ambient";
const string fk_DrawBase::specularName = "specular";
const string fk_DrawBase::shininessName = "shininess";

const string fk_DrawBase::parallelLightName = "fk_ParallelLight";
const string fk_DrawBase::pointLightName = "fk_PointLight";
const string fk_DrawBase::spotLightName = "fk_SpotLight";

const string fk_DrawBase::parallelLightNumName = "fk_ParallelLightNum";
const string fk_DrawBase::pointLightNumName = "fk_PointLightNum";
const string fk_DrawBase::spotLightNumName = "fk_SpotLightNum";

const string fk_DrawBase::lightPositionName = "position";
const string fk_DrawBase::lightVecName = "vec";
const string fk_DrawBase::lightDiffuseName = "diffuse";
const string fk_DrawBase::lightSpecularName = "specular";
const string fk_DrawBase::lightSpotCutOffName = "cut";
const string fk_DrawBase::lightSpotExponentName = "exp";
const string fk_DrawBase::lightAttenuationName = "attenuation";

const string fk_DrawBase::fragmentName = "fk_Fragment";

fk_Matrix * fk_DrawBase::projectionMatrix = nullptr;
unique_ptr<fk_Matrix> fk_DrawBase::viewMatrix = make_unique<fk_Matrix>();
unique_ptr<fk_Matrix> fk_DrawBase::modelMatrix = make_unique<fk_Matrix>();
unique_ptr<fk_Matrix> fk_DrawBase::modelViewMatrix = make_unique<fk_Matrix>();
unique_ptr<fk_Matrix> fk_DrawBase::modelViewProjectionMatrix = make_unique<fk_Matrix>();
unique_ptr<fk_Matrix> fk_DrawBase::normalModelMatrix = make_unique<fk_Matrix>();
unique_ptr<fk_Matrix> fk_DrawBase::normalModelViewMatrix = make_unique<fk_Matrix>();
unique_ptr<fk_Vector> fk_DrawBase::cameraPosition = make_unique<fk_Vector>();
fk_Material * fk_DrawBase::modelMaterial = nullptr;

fk_Matrix * fk_DrawBase::shadowProjMatrix = nullptr;
unique_ptr<fk_Matrix> fk_DrawBase::shadowViewMatrix = make_unique<fk_Matrix>();
unique_ptr<fk_Matrix> fk_DrawBase::shadowBiasMatrix = make_unique<fk_Matrix>();
unique_ptr<fk_Matrix> fk_DrawBase::shadowMatrix = make_unique<fk_Matrix>();
float fk_DrawBase::shadowVisibility = 1.0f;
float fk_DrawBase::shadowBias = 0.0005f;
fk_ShadowMode fk_DrawBase::shadowMode = fk_ShadowMode::OFF;

fk_FogMode fk_DrawBase::fogMode = fk_FogMode::OFF;
unique_ptr<fk_Vector> fk_DrawBase::fogParam = make_unique<fk_Vector>();
unique_ptr<fk_Color> fk_DrawBase::fogColor = make_unique<fk_Color>();

list<fk_Model *> * fk_DrawBase::parallelLightList;
list<fk_Model *> * fk_DrawBase::pointLightList;
list<fk_Model *> * fk_DrawBase::spotLightList;

fk_DrawBase::fk_DrawBase(void)
	: drawShader(nullptr),
	  shadowTexture(nullptr), defaultShaderFlag(true)
{
	InitBiasMatrix();
	return;
}

fk_DrawBase::~fk_DrawBase()
{
	return;
}

void fk_DrawBase::SetShadowMode(fk_ShadowMode argMode)
{
	shadowMode = argMode;
}

void fk_DrawBase::InitBiasMatrix(void)
{
	shadowBiasMatrix->init();
	shadowBiasMatrix->set(0, 0, 0.5);
	shadowBiasMatrix->set(1, 1, 0.5);
	shadowBiasMatrix->set(2, 2, 0.5);
	shadowBiasMatrix->set(0, 3, 0.5);
	shadowBiasMatrix->set(1, 3, 0.5);
	shadowBiasMatrix->set(2, 3, 0.5);
}

void fk_DrawBase::SetProjectionMatrix(fk_Matrix *argM)
{
	projectionMatrix = argM;
	return;
}

void fk_DrawBase::SetShadowProjMatrix(fk_Matrix *argM)
{
	shadowProjMatrix = argM;
	return;
}

void fk_DrawBase::SetCamera(fk_Model *argModel)
{
	*viewMatrix = argModel->getInhInvMatrix();
	*cameraPosition = argModel->getInhPosition();
	return;
}

void fk_DrawBase::SetShadowCamera(fk_Model *argModel)
{
	*shadowViewMatrix = argModel->getInhInvMatrix();
	return;
}

void fk_DrawBase::SetShadowParam(double argVis, double argBias)
{
	shadowVisibility = float(argVis);
	shadowBias = float(argBias);
}

void fk_DrawBase::SetFogStatus(fk_FogMode argFogMode,
							   double argFogStart, double argFogEnd,
							   double argFogDensity, fk_Color &argFogColor)
{
	if((fogMode = argFogMode) != fk_FogMode::OFF) {
		fogParam->set(argFogStart, argFogEnd, argFogDensity);
		*fogColor = argFogColor;
	}
}
	

void fk_DrawBase::SetModel(fk_Model *argModel)
{
	if(projectionMatrix == nullptr) return;

	*modelMatrix = argModel->getInhMatrix();
	*modelViewMatrix = (*viewMatrix) * (*modelMatrix);
	*modelViewProjectionMatrix = (*projectionMatrix) * (*modelViewMatrix);
	modelMaterial = argModel->getMaterial();
	*normalModelMatrix = (*modelMatrix);
	normalModelMatrix->covariant();
	*normalModelViewMatrix = (*modelViewMatrix);
	normalModelViewMatrix->covariant();

	if(shadowMode != fk_ShadowMode::OFF) {
		*shadowMatrix = (*shadowBiasMatrix) * (*shadowProjMatrix) *
			(*shadowViewMatrix) * (*modelMatrix);
	}
	return;
}

void fk_DrawBase::SetLight(list<fk_Model *> *argList, fk_LightType argType)
{
	switch(argType) {
	  case fk_LightType::PARALLEL:
		  parallelLightList = argList;
		  return;

	  case fk_LightType::POINT:
		  pointLightList = argList;
		  return;
		  
	  case fk_LightType::SPOT:
		  spotLightList = argList;
		  return;

	  default:
		  break;
	}

	return;
}

void fk_DrawBase::SetParameter(fk_ShaderParameter *argParam)
{
	if(projectionMatrix != nullptr) SetProjectionParam(argParam);
	if(shadowMode != fk_ShadowMode::OFF) SetShadowParam(argParam);
	if(fogMode != fk_FogMode::OFF) SetFogParam(argParam);
	SetMaterialParam(argParam);
	SetLightParam(argParam, fk_LightType::PARALLEL);
	SetLightParam(argParam, fk_LightType::POINT);
	SetLightParam(argParam, fk_LightType::SPOT);
	return;
}

void fk_DrawBase::SetProjectionParam(fk_ShaderParameter *argParam)
{
	argParam->setRegister(projectionMatrixName, projectionMatrix, projectionMatrixName);
	argParam->setRegister(viewMatrixName, viewMatrix.get(), viewMatrixName);
	argParam->setRegister(modelMatrixName, modelMatrix.get(), modelMatrixName);
	argParam->setRegister(modelViewMatrixName, modelViewMatrix.get(), modelViewMatrixName);
	argParam->setRegister(modelViewProjectionMatrixName, modelViewProjectionMatrix.get(),
						  modelViewProjectionMatrixName);
	argParam->setRegister(normalModelMatrixName, normalModelMatrix.get(),
						  normalModelMatrixName);
	argParam->setRegister(normalModelViewMatrixName, normalModelViewMatrix.get(),
						  normalModelViewMatrixName);
	argParam->setRegister(cameraPositionName, cameraPosition.get(), cameraPositionName);

	return;
}

void fk_DrawBase::SetShadowParam(fk_ShaderParameter *argParam)
{
	argParam->setRegister(shadowMatrixName, shadowMatrix.get(), shadowMatrixName);
	argParam->setRegister(shadowVisibilityName, shadowVisibility, shadowVisibilityName);
	argParam->setRegister(shadowBiasName, shadowBias, shadowBiasName);
}

void fk_DrawBase::SetFogParam(fk_ShaderParameter *argParam)
{
	argParam->setRegister(fogParamName, fogParam.get(), fogParamName);
	argParam->setRegister(fogColorName, &(fogColor->col), fogColorName);
}

void fk_DrawBase::SetMaterialParam(fk_ShaderParameter *argParam)
{
	argParam->setRegister(modelMaterialName + "." + diffuseName,
						  &(modelMaterial->getDiffuse()->col), modelMaterialName);
	argParam->setRegister(modelMaterialName + "." + ambientName,
						  &(modelMaterial->getAmbient()->col), modelMaterialName);
	argParam->setRegister(modelMaterialName + "." + specularName,
						  &(modelMaterial->getSpecular()->col), modelMaterialName);
	argParam->setRegister(modelMaterialName + "." + shininessName,
						  modelMaterial->getShininess(), modelMaterialName);
						  
	return;
}

void fk_DrawBase::SetLightParam(fk_ShaderParameter *argParam, fk_LightType argType)
{
	int lightID = 0;
	fk_Vector tmp;
	list<fk_Model *> *list;
	string lightName;
	string numName;
	vector<float>	attenuation(3);

	switch(argType) {
	  case fk_LightType::PARALLEL:
		  list = parallelLightList;
		  lightName = parallelLightName;
		  numName = parallelLightNumName;
		  break;

	  case fk_LightType::POINT:
		  list = pointLightList;
		  lightName = pointLightName;
		  numName = pointLightNumName;
		  break;

	  case fk_LightType::SPOT:
		  list = spotLightList;
		  lightName = spotLightName;
		  numName = spotLightNumName;
		  break;

	  default:
		  return;
	}

	if(list == nullptr) {
		argParam->setRegister(numName, 0, numName);
		return;
	}

	for(auto p = list->begin(); p != list->end(); ++p) {
		fk_Model *model = *p;
		fk_Light *light = dynamic_cast<fk_Light *>(model->getShape());

		string nameBase = lightName + "[" + to_string(lightID) + "]";

		if(argType != fk_LightType::PARALLEL) {
			tmp = model->getInhPosition();
			argParam->setRegister(nameBase + "." + lightPositionName, &tmp, lightName);
		}

		if(argType != fk_LightType::POINT) {
			tmp = model->getInhVec();
			argParam->setRegister(nameBase + "." + lightVecName, &tmp, lightName);
		}

		argParam->setRegister(nameBase + "." + lightDiffuseName,
							  &(model->getMaterial()->getDiffuse()->col), lightName);
		argParam->setRegister(nameBase + "." + lightSpecularName,
							  &(model->getMaterial()->getSpecular()->col), lightName);

		if(argType == fk_LightType::SPOT) {
			argParam->setRegister(nameBase + "." + lightSpotCutOffName,
								  float(light->getSpotCutOff()), lightName);
			argParam->setRegister(nameBase + "." + lightSpotExponentName,
								  float(light->getSpotExponent()), lightName);
		}

		if(argType != fk_LightType::PARALLEL) {
			attenuation[0] = float(light->getAttenuation(0));
			attenuation[1] = float(light->getAttenuation(1));
			attenuation[2] = float(light->getAttenuation(2));
			argParam->setRegister(nameBase + "." + lightAttenuationName, &attenuation, lightName);
		}

		++lightID;
		if(lightID >= fk_Light::MAXLIGHTNUM) break;
	}

	argParam->setRegister(numName, lightID, numName);
}

void fk_DrawBase::AttachShadowTexture(int argID, const string &strName, fk_Texture *argTexture)
{
	if(aliveShader.empty() == false) shadowTexture = argTexture;
	for(auto shader : aliveShader) {
		auto param = shader->getParameter();
		param->attachTexture(argID, argTexture);
		param->setRegister(strName, argID+1);
	}
}

void fk_DrawBase::FragmentFogInit(fk_ShaderProgram *argProg, fk_FogMode argFogMode)
{
	switch(argFogMode) {
	  case fk_FogMode::OFF:
		argProg->fragmentShaderSource +=
			#include "GLSL/Common/FS_Fog_Off.out"
			;
		break;
		
	  case fk_FogMode::LINEAR:
		argProg->fragmentShaderSource +=
			#include "GLSL/Common/FS_Fog_Linear.out"
			;
		break;

	  case fk_FogMode::EXP:
		argProg->fragmentShaderSource +=
			#include "GLSL/Common/FS_Fog_Exp1.out"
			;
		break;

	  case fk_FogMode::EXP2:
		argProg->fragmentShaderSource +=
			#include "GLSL/Common/FS_Fog_Exp2.out"
			;
		break;

	  default:
		argProg->fragmentShaderSource +=
			#include "GLSL/Common/FS_Fog_Off.out"
			;
		break;
	}
	return;
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
