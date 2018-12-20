﻿/****************************************************************************
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
#ifdef FK_D3D
#include "Engine_D3D.cxx"
#else

#define FK_DEF_SIZETYPE
#include <FK/Engine.H>
#include <FK/Scene.h>
#include <FK/Light.h>
#include <FK/Plane.h>
#include <FK/Projection.h>
#include <FK/PointDraw.H>
#include <FK/LineDraw.H>
#include <FK/FaceDraw.H>
#include <FK/TextureDraw.H>
#include <FK/Error.H>

using namespace std;
using namespace FK;

static unsigned int		generalID = 1;

fk_GraphicsEngine::fk_GraphicsEngine(void)
{
	pointDraw = new fk_PointDraw;
	lineDraw = new fk_LineDraw;
	faceDraw = new fk_FaceDraw;
	textureDraw = new fk_TextureDraw;

	winID = 0;
	curDLink = nullptr;
	dLinkStatus = 0;
	dLinkID = 0;
	wSize = 0;
	hSize = 0;
	resizeFlag = false;
	textureMode = false;

	srcFactor = FK_FACTOR_SRC_ALPHA;
	dstFactor = FK_FACTOR_ONE_MINUS_SRC_ALPHA;
	depthRead = depthWrite = true;

	return;
}

fk_GraphicsEngine::~fk_GraphicsEngine()
{
	delete pointDraw;
	delete lineDraw;
	delete faceDraw;
	delete textureDraw;

	snapBuffer.clear();

	return;
}

void fk_GraphicsEngine::Init(int argW, int argH)
{
	winID = generalID;
	generalID++;
	curDLink = nullptr;
	dLinkStatus = FK_UNDEFINED;
	dLinkID = FK_UNDEFINED;
	wSize = argW;
	hSize = argH;
	resizeFlag = false;
	textureMode = false;

	textureDraw->SetBindMode(true);

	defProj.setAll(40.0, 1.0, 6000.0);
	
	return;
}

void fk_GraphicsEngine::ResizeWindow(int argW, int argH)
{
	wSize = argW;
	hSize = argH;
	resizeFlag = true;

	return;
}

void fk_GraphicsEngine::ClearTextureMemory(void)
{
	textureDraw->ClearTextureMemory();
	generalID++;
	return;
}

unsigned long fk_GraphicsEngine::GetUsingTextureMemory(void)
{
	return textureDraw->GetUsingTextureMemory();
}

void fk_GraphicsEngine::SetViewPort(void)
{
	if(curDLink == nullptr) {
		SetProjection(&defProj);
	} else {
		SetProjection(curDLink->getProjection());
	}
	return;
}

void fk_GraphicsEngine::SetProjection(fk_ProjectBase *argProj)
{
	curProj = argProj;
	if(curProj->getMode() == FK_PERSPECTIVE_MODE) {
		fk_Perspective *pers = dynamic_cast<fk_Perspective *>(curProj);
		pers->setAspect(GLfloat(wSize)/GLfloat(hSize));
	}
	curProj->MakeMat();
	pointDraw->SetProjectMatrix(curProj->GetMatrix());
	lineDraw->SetProjectMatrix(curProj->GetMatrix());
	faceDraw->SetProjectMatrix(curProj->GetMatrix());
	return;
}

void fk_GraphicsEngine::OpenGLInit(void)
{
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPolygonMode(GL_FRONT, GL_FILL);
	//glDisable(GL_BLEND);

#ifndef OPENGL4
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glShadeModel(GL_FLAT);
	glAlphaFunc(GL_GREATER, 0.01f);
#endif
	return;
}

void fk_GraphicsEngine::ApplySceneParameter(bool argVPFlg)
{
	bool			fogStatus = false;
	fk_Scene		*scene;
	fk_Color		bgColor;

	scene = nullptr;

	if(curDLink != nullptr) {
		if(dLinkID != curDLink->GetID() ||
		   dLinkStatus != curDLink->GetProjChangeStatus()) {
			dLinkID = curDLink->GetID();
			dLinkStatus = curDLink->GetProjChangeStatus();
			if(argVPFlg == true) {
				SetViewPort();
			}
			if(curDLink->getObjectType() == FK_SCENE) {
				scene = static_cast<fk_Scene *>(curDLink);
				scene->GetFogChangeStatus();
				fogStatus = true;
			}
		} else {
			if(curDLink->getObjectType() == FK_SCENE) {
				scene = static_cast<fk_Scene *>(curDLink);
				fogStatus = scene->GetFogChangeStatus();
			}
		}
	}

	if(scene != nullptr) {

		if(scene->getBlendStatus() == true) {
			glEnable(GL_BLEND);
		} else {
			glDisable(GL_BLEND);
		}
		if(fogStatus == true) {
			InitFogStatus(scene);
		}
		bgColor = scene->getBGColor();
		glClearColor(bgColor.col[0], bgColor.col[1], bgColor.col[2], 1.0f);

	} else {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	return;
}

void fk_GraphicsEngine::Draw(void)
{
	// リサイズ時に加えて、マルチウィンドウ時もビューポートを再設定(by rita)
	if(resizeFlag == true || generalID > 2) {
		SetViewPort();
		resizeFlag = false;
	}

	ApplySceneParameter(true);

	SetDepthMode(FK_DEPTH_READ_AND_WRITE);
	glClear(static_cast<GLbitfield>(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	curProj->MakeMat();
	fk_Matrix cameraM = curDLink->getCamera()->getInhInvMatrix();
	pointDraw->SetCameraMatrix(&cameraM);
	lineDraw->SetCameraMatrix(&cameraM);
	faceDraw->SetCameraMatrix(&cameraM);
	DrawObjs();

	return;
}

void fk_GraphicsEngine::SetScene(fk_Scene *argScene)
{
	curDLink = argScene;
	return;
}

void fk_GraphicsEngine::DrawObjs(void)
{
	list<fk_Model *>::iterator	modelP, modelPEnd;
	list<fk_Model *>			*overlayList;
	bool						lightFlag;

	if(curDLink == nullptr) return;
	lightFlag = DefineLight();

	//if(argPickFlg == true) modelArray.clear();

	textureDraw->StartUp();

	modelPEnd = curDLink->GetModelList()->end();
	for(modelP = curDLink->GetModelList()->begin();
		modelP != modelPEnd; ++modelP) {
		SetDepthMode((*modelP)->getDepthMode());
		DrawModel(*modelP, lightFlag);
	}

	overlayList = curDLink->GetOverlayList();
	if(overlayList->empty() == true) return;

	SetDepthMode(FK_DEPTH_NO_USE);
	modelPEnd = overlayList->end();
	for(modelP = overlayList->begin(); modelP != modelPEnd; ++modelP) {
		DrawModel(*modelP, lightFlag);
	}

	return;
}

void fk_GraphicsEngine::DrawModel(fk_Model *argModel,
								  bool argLightFlg)
{
	fk_Shape		*modelShape = argModel->getShape();
		
	if(argModel->getBDrawToggle() == true) {
		if(argModel->getBMode() == FK_B_AABB) {
			//LoadAABBMatrix(argModel);
			DrawBoundaryObj(argModel, argLightFlg);
			//LoadModelMatrix(argModel);
		} else {
			//LoadModelMatrix(argModel);
			DrawBoundaryObj(argModel, argLightFlg);
		}
	} else {
		//LoadModelMatrix(argModel);
	}
	
	if(modelShape == nullptr) return;

	SetBlendMode(argModel);
	fk_DrawMode drawMode = argModel->getDrawMode();
	if((drawMode & FK_SHADERMODE) != FK_NONEMODE) argModel->preShader();
	
	if(modelShape->getRealShapeType() == FK_SHAPE_TEXTURE) {
		if(textureMode == false) {
			glEnable(GL_TEXTURE_2D);
			textureMode = true;
		}
		textureDraw->DrawTextureObj(argModel, argLightFlg);
	} else {
		DrawShapeObj(argModel, argLightFlg);
	}

	if((drawMode & FK_SHADERMODE) != FK_NONEMODE) argModel->postShader();
	/*
	for(auto it = argModel->postShaderList.begin(); it != argModel->postShaderList.end(); ++it) {
		get<1>(*it)();
	}
	*/

	return;
}

bool fk_GraphicsEngine::DefineLight(void)
{
#ifndef OPENGL4
	const GLenum		LArray[8] = {
		GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,
		GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7
	};

	const int					MaxLNum = 8;
	int							LightID;
	list<fk_Model *>::iterator	LightP, LightPEnd;
	bool						lightFlag;
	fk_Material					*LightMate;
	fk_Light					*LightShape;
	fk_Vector					LightPos, LightDirection;
	float						LPosArray[4];

	if(curDLink->GetLightList()->size() == 0) {
		lightFlag = false;
	} else {
		lightFlag = true;
	}

	for(LightID = 0; LightID < MaxLNum; LightID++) {
		glDisable(LArray[LightID]);
	}

	if(lightFlag == true) {
		LightP = curDLink->GetLightList()->begin();
		LightPEnd = curDLink->GetLightList()->end();

		for(LightID = 0;
			LightP != LightPEnd && LightID < MaxLNum;
			++LightP, ++LightID) {
			LightMate = (*LightP)->getInhMaterial();
			glLightfv(LArray[LightID], GL_AMBIENT,
					  &(LightMate->getAmbient()->col[0]));
			glLightfv(LArray[LightID], GL_DIFFUSE,
					  &(LightMate->getDiffuse()->col[0]));
			glLightfv(LArray[LightID], GL_SPECULAR,
					  &(LightMate->getSpecular()->col[0]));

			LightShape = static_cast<fk_Light *>((*LightP)->getShape());

			switch(LightShape->getLightType()) {
			  case FK_PARALLEL_LIGHT:
				LightPos = (*LightP)->getInhVec();
				LPosArray[0] = static_cast<float>(-LightPos.x);
				LPosArray[1] = static_cast<float>(-LightPos.y);
				LPosArray[2] = static_cast<float>(-LightPos.z);
				LPosArray[3] = 0.0;
				glLightfv(LArray[LightID], GL_POSITION, LPosArray);
				break;

			  case FK_POINT_LIGHT:
				LightPos = (*LightP)->getInhPosition();
				LPosArray[0] = static_cast<float>(LightPos.x);
				LPosArray[1] = static_cast<float>(LightPos.y);
				LPosArray[2] = static_cast<float>(LightPos.z);
				LPosArray[3] = 1.0;
				glLightfv(LArray[LightID], GL_POSITION, LPosArray);
				glLightf(LArray[LightID], GL_LINEAR_ATTENUATION,
						 static_cast<float>(LightShape->getAttenuation(0)));
				glLightf(LArray[LightID], GL_QUADRATIC_ATTENUATION,
						 static_cast<float>(LightShape->getAttenuation(1)));
				glLightf(LArray[LightID], GL_CONSTANT_ATTENUATION,
						 static_cast<float>(LightShape->getAttenuation(2)));

				glLightf(LArray[LightID], GL_SPOT_CUTOFF, 180.0);

				break;

			  case FK_SPOT_LIGHT:
				LightPos = (*LightP)->getInhPosition();
				LightDirection = (*LightP)->getInhVec();
				LPosArray[0] = static_cast<float>(LightPos.x);
				LPosArray[1] = static_cast<float>(LightPos.y);
				LPosArray[2] = static_cast<float>(LightPos.z);
				LPosArray[3] = 1.0;
				glLightfv(LArray[LightID], GL_POSITION, LPosArray);
				LPosArray[0] = static_cast<float>(LightDirection.x);
				LPosArray[1] = static_cast<float>(LightDirection.y);
				LPosArray[2] = static_cast<float>(LightDirection.z);
				LPosArray[3] = 0.0;
				glLightfv(LArray[LightID], GL_SPOT_DIRECTION, LPosArray);

				glLightf(LArray[LightID], GL_LINEAR_ATTENUATION,
						 static_cast<float>(LightShape->getAttenuation(0)));
				glLightf(LArray[LightID], GL_QUADRATIC_ATTENUATION,
						 static_cast<float>(LightShape->getAttenuation(1)));
				glLightf(LArray[LightID], GL_CONSTANT_ATTENUATION,
						 static_cast<float>(LightShape->getAttenuation(2)));
				glLightf(LArray[LightID], GL_SPOT_EXPONENT,
						 static_cast<float>(LightShape->getSpotExponent()));
				glLightf(LArray[LightID], GL_SPOT_CUTOFF,
						 static_cast<float>(LightShape->getSpotCutOff()*180.0/FK_PI));

			  default:
				break;
			}

			glEnable(LArray[LightID]);
		}
	}	
	return lightFlag;
#endif
	return true;
}

void fk_GraphicsEngine::DrawShapeObj(fk_Model *argObj,
									 bool argLightFlag)
{
	fk_DrawMode		DrawMode;

	FK_UNUSED(argLightFlag);
	DrawMode = argObj->getDrawMode();

	//fk_Window::printf("DrawMode = %d", DrawMode);
	if(DrawMode == FK_NONEMODE) return;

	if(textureMode == true) {
		glDisable(GL_TEXTURE_2D);
		textureMode = false;
	}

	if((DrawMode & FK_POLYMODE) != FK_NONEMODE) {
		//faceDraw->DrawShapeFace(argObj, DrawMode);
	}

	if((DrawMode & FK_POINTMODE) != FK_NONEMODE) {
		pointDraw->DrawShapePoint(argObj);
	}

	if((DrawMode & FK_LINEMODE) != FK_NONEMODE) {
		lineDraw->DrawShapeLine(argObj);
	}

	return;
}

void fk_GraphicsEngine::DrawBoundaryObj(fk_Model *argObj, bool argLightFlag)
{
	FK_UNUSED(argLightFlag);
	
	if(textureMode == true) {
		glDisable(GL_TEXTURE_2D);
		textureMode = false;
	}

	if(argObj->getBMode() == FK_B_CAPSULE) {
#ifndef OPENGL4
		glPushMatrix();
#endif
		//LoadModelMatrix(argObj->GetCapsuleModel());
	}

	lineDraw->DrawBoundaryLine(argObj);

#ifndef OPENGL4	
	if(argObj->getBMode() == FK_B_CAPSULE) {
		glPopMatrix();
	}

	if(argLightFlag == true) {
		glEnable(GL_LIGHTING);
	} else {
		glDisable(GL_LIGHTING);
	}
#endif
	
	return;
}

/*
void fk_GraphicsEngine::LoadModelMatrix(fk_Model *argModel)
{
	fk_Angle	MAngle;
	fk_Vector	MPos;

	MAngle = argModel->getAngle();
	MPos = argModel->getPosition();

	if(argModel->getParent() != nullptr) {
		LoadModelMatrix(argModel->getParent());
	}

#ifndef OPENGL4
	glTranslated(MPos.x, MPos.y, MPos.z);
	glRotated(-180.0*MAngle.h/FK_PI, 0.0, 1.0, 0.0);
	glRotated(180.0*MAngle.p/FK_PI, 1.0, 0.0, 0.0);
	glRotated(-180.0*MAngle.b/FK_PI, 0.0, 0.0, 1.0);

	if(argModel->getScaleMode() == true) {
		double Scale = argModel->getScale();
		glScaled(Scale * argModel->getScale(fk_X),
				 Scale * argModel->getScale(fk_Y),
				 Scale * argModel->getScale(fk_Z));
	}
#endif
	
	return;
}
*/
/*
void fk_GraphicsEngine::LoadAABBMatrix(fk_Model *argModel)
{
	FK_UNUSED(argModel);
#ifndef OPENGL4
	fk_Vector MPos = argModel->getInhPosition();
	double scale = argModel->getInhScale();
	glTranslated(MPos.x, MPos.y, MPos.z);
	glScaled(scale, scale, scale);
#endif
	return;
}
*/
void fk_GraphicsEngine::InitFogStatus(fk_Scene *argScene)
{
	FK_UNUSED(argScene);

#ifndef OPENGL4
	fk_FogMode		fogMode = argScene->getFogMode();

	if(fogMode == FK_NONE_FOG) {
		glDisable(GL_FOG);
		return;
	}

	glEnable(GL_FOG);

	switch(fogMode) {
	  case FK_EXP_FOG:
		glFogi(GL_FOG_MODE, GL_EXP);
		break;
	
	  case FK_EXP2_FOG:
		glFogi(GL_FOG_MODE, GL_EXP);
		break;

	  case FK_LINEAR_FOG:
		glFogi(GL_FOG_MODE, GL_LINEAR);
		break;

	  default:
		break;
	}

	switch(argScene->getFogOption()) {
	  case FK_FASTEST_FOG:
		glHint(GL_FOG_HINT, GL_FASTEST);
		break;

	  case FK_NICEST_FOG:
		glHint(GL_FOG_HINT, GL_NICEST);
		break;

	  case FK_NOOPTION_FOG:
		glHint(GL_FOG_HINT, GL_DONT_CARE);
		break;

	  default:
		break;
	}

	glFogf(GL_FOG_DENSITY, static_cast<float>(argScene->getFogDensity()));
	glFogf(GL_FOG_START, static_cast<float>(argScene->getFogLinearStart()));
	glFogf(GL_FOG_END, static_cast<float>(argScene->getFogLinearEnd()));

	glFogfv(GL_FOG_COLOR, argScene->getFogColor().col);
#endif
	
	return;
}
/*
void fk_GraphicsEngine::ViewMatCalc(fk_Matrix *argMat)
{
	GLdouble	tmp_modelArray[16], projArray[16];
	fk_Matrix	projMat, modelMat;
	int			ii, ij;

#ifndef OPENGL4
	glPushMatrix();
#endif
	RecalcModelView();

#ifndef OPENGL4
	glGetIntegerv(GL_VIEWPORT, viewArray);
	glGetDoublev(GL_PROJECTION_MATRIX, projArray);
	glGetDoublev(GL_MODELVIEW_MATRIX, tmp_modelArray);

	glPopMatrix();
#endif
	
	for(ii = 0; ii < 4; ii++) {
		for(ij = 0; ij < 4; ij++) {
			projMat[ii][ij] = projArray[ij*4+ii];
			modelMat[ii][ij] = tmp_modelArray[ij*4+ii];
		}
	}

	*argMat = projMat * modelMat;
	return;
}
*/

bool fk_GraphicsEngine::GetViewLinePos(double argX, double argY,
									   fk_Vector *retS, fk_Vector *retE)
{
	fk_HVector		inVec, outVec;
	fk_Matrix		mat;
	double			tmpY;
	double			diffX, diffY;

	//ViewMatCalc(&mat);
	mat.inverse();

	tmpY = static_cast<double>(hSize) - argY - 1.0;
	diffX = argX - static_cast<double>(viewArray[0]);
	diffY = tmpY - static_cast<double>(viewArray[1]);

	inVec.x = diffX*2.0/static_cast<double>(viewArray[2]) - 1.0;
	inVec.y = diffY*2.0/static_cast<double>(viewArray[3]) - 1.0;
	inVec.w = 1.0;

	inVec.z = -1.0;
	outVec = mat * inVec;
	if(fabs(outVec.w) < FK_EPS) return false;
	retS->set(outVec.x/outVec.w, outVec.y/outVec.w, outVec.z/outVec.w);

	inVec.z = 1.0;
	outVec = mat * inVec;
	if(fabs(outVec.w) < FK_EPS) return false;
	retE->set(outVec.x/outVec.w, outVec.y/outVec.w, outVec.z/outVec.w);

	return true;
}

bool fk_GraphicsEngine::GetProjectPosition(double argX, double argY,
										   fk_Plane *argPlane,
										   fk_Vector *retPos)
{
	fk_Vector		sVec, eVec;

	if(curDLink == nullptr) return false;

	if(generalID > 2) SetViewPort();

	GetViewLinePos(argX, argY, &sVec, &eVec);
	return argPlane->calcCrossPos(sVec, eVec, retPos);
}

bool fk_GraphicsEngine::GetProjectPosition(double argX, double argY,
										   double argDist, fk_Vector *retPos)
{
	fk_Vector		sVec, eVec, eyeVec, cameraPos;
	const fk_Model	*tmpCamera;

	if(curDLink == nullptr) return false;
	tmpCamera = curDLink->getCamera();
	if(generalID > 2) SetViewPort();

	GetViewLinePos(argX, argY, &sVec, &eVec);
	eyeVec = eVec - sVec;
	eyeVec.normalize();
	if(tmpCamera == nullptr) {
		cameraPos.set(0.0, 0.0, 0.0);
	} else {
		cameraPos = tmpCamera->getInhPosition();
	}

	*retPos = cameraPos + eyeVec * argDist;
	return true;
}

bool fk_GraphicsEngine::GetWindowPosition(fk_Vector argPos, fk_Vector *retPos)
{
	fk_HVector		inVec, outVec;
	fk_Matrix		mat;

	inVec = argPos;
	inVec.w = 1.0;

	if(generalID > 2) SetViewPort();

	//ViewMatCalc(&mat);
	outVec = mat * inVec;
	if(fabs(outVec.w) < FK_EPS) return false;
	outVec /= outVec.w;
	retPos->set(static_cast<double>(viewArray[0]) +
				static_cast<double>(viewArray[2])*(outVec.x + 1.0)/2.0,
				static_cast<double>(viewArray[1]) +
				static_cast<double>(hSize) - 1.0 -
				static_cast<double>(viewArray[3])*(outVec.y + 1.0)/2.0,
				(1.0 + outVec.z)/2.0);
	return true;
}

void fk_GraphicsEngine::SetOGLTextureBindMode(bool argFlg)
{
	textureDraw->SetBindMode(argFlg);
	return;
}

bool fk_GraphicsEngine::GetOGLTextureBindMode(void)
{
	return textureDraw->GetBindMode();
}

GLenum GetBlendFactor(fk_BlendFactor factor)
{
	switch (factor) {
	case FK_FACTOR_ZERO:
		return GL_ZERO;
	case FK_FACTOR_ONE:
		return GL_ONE;
	case FK_FACTOR_SRC_COLOR:
		return GL_SRC_COLOR;
	case FK_FACTOR_ONE_MINUS_SRC_COLOR:
		return GL_ONE_MINUS_SRC_ALPHA;
	case FK_FACTOR_DST_COLOR:
		return GL_DST_COLOR;
	case FK_FACTOR_ONE_MINUS_DST_COLOR:
		return GL_ONE_MINUS_DST_COLOR;
	case FK_FACTOR_SRC_ALPHA:
		return GL_SRC_ALPHA;
	case FK_FACTOR_ONE_MINUS_SRC_ALPHA:
		return GL_ONE_MINUS_SRC_ALPHA;
	case FK_FACTOR_DST_ALPHA:
		return GL_DST_ALPHA;
	case FK_FACTOR_ONE_MINUS_DST_ALPHA:
		return GL_ONE_MINUS_DST_ALPHA;
	default:
		return GL_ONE;
	}
}

void fk_GraphicsEngine::SetBlendMode(fk_Model *argModel)
{
	fk_BlendFactor src, dst;
	argModel->getBlendMode(&src, &dst);

	if(src != srcFactor || dst != dstFactor) {
		srcFactor = src;
		dstFactor = dst;
		glBlendFunc(GetBlendFactor(srcFactor), GetBlendFactor(dstFactor));
	}
	return;
}

void fk_GraphicsEngine::SetDepthMode(fk_DepthMode argMode)
{
	bool r = (argMode & FK_DEPTH_READ) != 0;
	bool w = (argMode & FK_DEPTH_WRITE) != 0;
	if (depthRead != r) {
		if (r) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);
		depthRead = r;
	}
	if (depthWrite != w) {
		glDepthMask(w ? GL_TRUE : GL_FALSE);
		depthWrite = w;
	}
}

bool fk_GraphicsEngine::SnapImage(fk_Image *argImage, fk_SnapProcMode argMode)
{
	int		wCount, hCount;
	_st		index;

	if(argImage == nullptr) return false;

	if(argImage->getWidth() != wSize || argImage->getHeight() != hSize) {
		argImage->newImage(wSize, hSize);
	}
	if(static_cast<int>(snapBuffer.size()) != 3*wSize*hSize) {
		snapBuffer.resize(static_cast<_st>(3*wSize*hSize));
	}
	if(argMode == FK_SNAP_GL_FRONT) {
		glReadBuffer(GL_FRONT);
	} else {
		glReadBuffer(GL_BACK);
	}
	glReadPixels(0, 0, wSize, hSize,
				 GL_RGB, GL_UNSIGNED_BYTE,
				 static_cast<GLvoid *>(&snapBuffer[0]));

	for(hCount = 0; hCount < hSize; hCount++) {
		for(wCount = 0; wCount < wSize; wCount++) {
			index = static_cast<_st>(3*(hCount*wSize + wCount));
			argImage->setRGB(wCount, hSize - hCount - 1,
							 snapBuffer[index],
							 snapBuffer[index+1],
							 snapBuffer[index+2]);
		}
	}

	return true;
}

#endif
