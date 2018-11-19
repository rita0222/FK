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
#ifdef FK_D3D
#include "Engine_D3D.cxx"
#else

#define FK_DEF_SIZETYPE
#include <FK/Engine.H>
#include <FK/Scene.h>
#include <FK/Light.h>
#include <FK/Plane.h>
#include <FK/PickData.h>
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
	arrayState = false;
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
	arrayState = true;
	textureMode = false;

	pointDraw->SetArrayState(arrayState);
	lineDraw->SetArrayState(arrayState);
	faceDraw->SetArrayState(arrayState);
	textureDraw->SetArrayState(arrayState);

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
#ifndef OPENGL4
	glViewport(0, 0, wSize, hSize);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#endif

	if(curDLink == nullptr) {
		SetProjection(&defProj);
	} else {
		SetProjection(curDLink->getProjection());
	}

#ifndef OPENGL4
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
#endif

	return;
}

void fk_GraphicsEngine::SetPickViewPort(int argPixSize, int argX, int argY)
{
	FK_UNUSED(argPixSize);
	FK_UNUSED(argX);
	FK_UNUSED(argY);

#ifndef OPENGL4	
	GLint	ViewPort[4];
	
	glViewport(0, 0, wSize, hSize);

	glGetIntegerv(GL_VIEWPORT, &ViewPort[0]);
	glSelectBuffer(FK_PICKDATAMAX*5, selectBuf);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPickMatrix(GLdouble(argX),
				  GLdouble(hSize - argY),
				  GLdouble(argPixSize),
				  GLdouble(argPixSize),
				  ViewPort);
#endif
	
	if(curDLink == nullptr) {
		SetProjection(&defProj);
	} else {
		SetProjection(curDLink->getProjection());
	}

#ifndef OPENGL4
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
#endif

	return;
}

void fk_GraphicsEngine::SetProjection(fk_ProjectBase *argProj)
{
	FK_UNUSED(argProj);

#ifdef OPENGL4
	argProj->MakeMat();
	viewMat = argProj->GetMatrix();

#else	
	fk_ProjectBase	*proj;
	fk_Perspective	*pers;
	fk_Frustum		*frus;
	fk_Ortho		*orth;

	proj = const_cast<fk_ProjectBase *>(argProj);

	switch(argProj->getMode()) {
	  case FK_PERSPECTIVE_MODE:
		pers = static_cast<fk_Perspective *>(proj);
		gluPerspective((180.0 * pers->getFovy())/FK_PI,
					   static_cast<GLfloat>(wSize)/static_cast<GLfloat>(hSize),
					   pers->getNear(), pers->getFar());
		break;

	  case FK_FRUSTUM_MODE:
		frus = static_cast<fk_Frustum *>(proj);
		glFrustum(frus->getLeft(), frus->getRight(),
				  frus->getBottom(), frus->getTop(),
				  frus->getNear(), frus->getFar());
		break;

	  case FK_ORTHO_MODE:
		orth = static_cast<fk_Ortho *>(proj);
		glOrtho(orth->getLeft(), orth->getRight(),
				orth->getBottom(), orth->getTop(),
				orth->getNear(), orth->getFar());
		break;

	  default:
		break;
	}
#endif
	return;
}

void fk_GraphicsEngine::OpenGLInit(void)
{
#ifndef OPENGL4
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPolygonMode(GL_FRONT, GL_FILL);
	glDisable(GL_BLEND);
	glAlphaFunc(GL_GREATER, 0.01f);
#endif
	
#ifdef NO_GL_POINTER
	arrayState = false;
	pointDraw->setArrayState(arrayState);
	lineDraw->setArrayState(arrayState);
	faceDraw->setArrayState(arrayState);
	textureDraw->setArrayState(arrayState);
#endif

	return;
}

/*
void fk_GraphicsEngine::SetStereoViewPort(fk_StereoChannel argChannel)
{
#ifndef OPENGL4
	glViewport(0, 0, wSize, hSize);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#endif
	
	if(curDLink == nullptr) {
		SetProjection(&defProj);
	} else {
		SetProjection(curDLink->getStereoProjection(argChannel));
	}

#ifndef OPENGL4
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
#endif

	return;
}

void fk_GraphicsEngine::RecalcStereoModelView(fk_StereoChannel argChannel)
{
	if(curDLink != nullptr) {
		const fk_Model	*camera = curDLink->getStereoCamera(argChannel);
		if(camera == nullptr) {
			RecalcInhModelView(curDLink->getCamera());
		} else {
			RecalcInhModelView(camera);
		}
	}

	return;
}

void fk_GraphicsEngine::StereoDrawPrep(fk_StereoChannel argChannel)
{
	switch(argChannel) {
	case FK_STEREO_LEFT:
		glDrawBuffer(GL_BACK_LEFT);
		break;
	case FK_STEREO_RIGHT:
		glDrawBuffer(GL_BACK_RIGHT);
		break;
	default:
		glDrawBuffer(GL_BACK);
	}

	return;
}

void fk_GraphicsEngine::StereoDrawMain(fk_StereoChannel argChannel)
{
	// どうせ毎回ビューポートを設定するのでリサイズフラグは確実に潰す
	if(resizeFlag == true || generalID > 2) {
		resizeFlag = false;
	}

	ApplySceneParameter(false);

	// バッファクリア時にステートを戻しておかないといけない（マジかよ）
	SetDepthMode(FK_DEPTH_READ_AND_WRITE);
	glClear(static_cast<GLbitfield>(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	SetStereoViewPort(argChannel);
#ifndef OPENGL4
	glPushMatrix();
#endif

	RecalcStereoModelView(argChannel);
	DrawStereoObjs(false);
#ifndef OPENGL4
	glPopMatrix();
	glFlush();
#endif
	return;
}

void fk_GraphicsEngine::DrawStereoObjs(bool argPickFlg)
{
	list<fk_Model *>::iterator	modelP, modelPEnd;
	list<fk_Model *>			*overlayList;
	bool						lightFlag;

	if(curDLink == nullptr) return;
	
	lightFlag = DefineLight();

	if(argPickFlg == true) modelArray.clear();

	textureDraw->StartUp();

	modelPEnd = curDLink->GetModelList()->end();
	for(modelP = curDLink->GetModelList()->begin();
		modelP != modelPEnd; ++modelP) {
		DrawModel(*modelP, lightFlag, argPickFlg);
	}

	overlayList = curDLink->GetOverlayList();
	if(overlayList->empty() == true) return;

	if(curDLink->getStereoOverlayMode() == false) {
		SetViewPort();
		RecalcModelView();
	}

	glDisable(GL_DEPTH_TEST);
	modelPEnd = overlayList->end();
	for(modelP = overlayList->begin(); modelP != modelPEnd; ++modelP) {
		DrawModel(*modelP, lightFlag, argPickFlg);
	}
	glEnable(GL_DEPTH_TEST);

	return;
}
*/

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

void fk_GraphicsEngine::Draw(bool argPickFlg)
{
	// リサイズ時に加えて、マルチウィンドウ時もビューポートを再設定(by rita)
	if(resizeFlag == true || generalID > 2) {
		SetViewPort();
		resizeFlag = false;
	}

	ApplySceneParameter(true);

	// バッファクリア時にステートを戻しておかないといけない（マジかよ）
	SetDepthMode(FK_DEPTH_READ_AND_WRITE);
	glClear(static_cast<GLbitfield>(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

#ifndef OPENGL4
	glPushMatrix();
#endif

	RecalcModelView();
	DrawObjs(argPickFlg);

#ifndef OPENGL4
	glPopMatrix();
	glFlush();
#endif
	return;
}

void fk_GraphicsEngine::SetScene(fk_Scene *argScene)
{
	curDLink = argScene;
	return;
}

void fk_GraphicsEngine::RecalcModelView(void)
{
	if(curDLink != nullptr) {
		RecalcInhModelView(curDLink->getCamera());
	}

	return;
}

void fk_GraphicsEngine::RecalcInhModelView(const fk_Model *argModel)
{
	fk_Angle	MAngle(0.0, 0.0, 0.0);
	fk_Vector	MPos(0.0, 0.0, 0.0);

	if(argModel == nullptr) return;

	MAngle = argModel->getAngle();
	MPos = argModel->getPosition();

#ifndef OPENGL4
	glRotated(180.0*MAngle.b/FK_PI, 0.0, 0.0, 1.0);
	glRotated(-180.0*MAngle.p/FK_PI, 1.0, 0.0, 0.0);
	glRotated(180.0*MAngle.h/FK_PI, 0.0, 1.0, 0.0);
	glTranslated(-MPos.x, -MPos.y, -MPos.z);
#endif
	
	if(argModel->getParent() != nullptr) {
		RecalcInhModelView(argModel->getParent());
	}

	return;
}

void fk_GraphicsEngine::DrawObjs(bool argPickFlg)
{
	list<fk_Model *>::iterator	modelP, modelPEnd;
	list<fk_Model *>			*overlayList;
	bool						lightFlag;

	if(curDLink == nullptr) return;
	lightFlag = DefineLight();

	if(argPickFlg == true) modelArray.clear();

	textureDraw->StartUp();

	modelPEnd = curDLink->GetModelList()->end();
	for(modelP = curDLink->GetModelList()->begin();
		modelP != modelPEnd; ++modelP) {
		SetDepthMode((*modelP)->getDepthMode());
		DrawModel(*modelP, lightFlag, argPickFlg);
	}

	overlayList = curDLink->GetOverlayList();
	if(overlayList->empty() == true) return;

	SetDepthMode(FK_DEPTH_NO_USE);
	modelPEnd = overlayList->end();
	for(modelP = overlayList->begin(); modelP != modelPEnd; ++modelP) {
		DrawModel(*modelP, lightFlag, argPickFlg);
	}

	return;
}

void fk_GraphicsEngine::DrawModel(fk_Model *argModel,
								  bool argLightFlg,
								  bool argPickFlg)
{
	fk_Shape		*modelShape;

	if(argPickFlg == true) {
		if(argModel->getPickMode() == false) return;
#ifndef OPENGL4
		glLoadName(GLuint(modelArray.size()));
#endif
		modelArray.push_back(argModel);
	}

	modelShape = argModel->getShape();

#ifndef OPENGL4
	glPushMatrix();
#endif
		
	if(argModel->getBDrawToggle() == true) {
		if(argModel->getBMode() == FK_B_AABB) {
			LoadAABBMatrix(argModel);
			DrawBoundaryObj(argModel, argLightFlg);
#ifndef OPENGL4
			glPopMatrix();
			glPushMatrix();
#endif
			LoadModelMatrix(argModel);
		} else {
			LoadModelMatrix(argModel);
			DrawBoundaryObj(argModel, argLightFlg);
		}
	} else {
		LoadModelMatrix(argModel);
	}
	
	if(modelShape == nullptr) {
#ifndef OPENGL4
		glPopMatrix();
#endif
		return;
	}

	SetBlendMode(argModel);
	argModel->preShader();
	for(auto it = argModel->preShaderList.begin(); it != argModel->preShaderList.end(); ++it) {
		get<1>(*it)();
	}
	
	if(modelShape->getRealShapeType() == FK_SHAPE_TEXTURE) {
		if(textureMode == false) {
			glEnable(GL_TEXTURE_2D);
			textureMode = true;
		}
		textureDraw->DrawTextureObj(argModel, argLightFlg, argPickFlg);
	} else {
		DrawShapeObj(argModel, argLightFlg, argPickFlg);
	}

	argModel->postShader();
	for(auto it = argModel->postShaderList.begin(); it != argModel->postShaderList.end(); ++it) {
		get<1>(*it)();
	}

#ifndef OPENGL4
	glPopMatrix();
#endif

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
									 bool argLightFlag,
									 bool argPickFlg)
{
	fk_DrawMode		DrawMode;

	DrawMode = argObj->getDrawMode();

	if(DrawMode == FK_NONEMODE) return;

	if(textureMode == true) {
		glDisable(GL_TEXTURE_2D);
		textureMode = false;
	}

	if((DrawMode & FK_POLYMODE) != FK_NONEMODE) {
		faceDraw->DrawShapeFace(argObj, argLightFlag, DrawMode, argPickFlg);
	}

	if((DrawMode & FK_POINTMODE) != FK_NONEMODE) {
		pointDraw->DrawShapePoint(argObj, argPickFlg);
	}

	if((DrawMode & FK_LINEMODE) != FK_NONEMODE) {
		lineDraw->DrawShapeLine(argObj, argPickFlg);
	}

#ifndef OPENGL4

	if(argLightFlag == true) {
		glEnable(GL_LIGHTING);
	} else {
		glDisable(GL_LIGHTING);
	}
#endif
	
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
		LoadModelMatrix(argObj->GetCapsuleModel());
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

bool fk_GraphicsEngine::GetViewLinePos(double argX, double argY,
									   fk_Vector *retS, fk_Vector *retE)
{
	fk_HVector		inVec, outVec;
	fk_Matrix		mat;
	double			tmpY;
	double			diffX, diffY;

	ViewMatCalc(&mat);
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

	ViewMatCalc(&mat);
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

void fk_GraphicsEngine::SetOGLPointerMode(bool argFlg)
{
	arrayState = argFlg;
	pointDraw->SetArrayState(arrayState);
	lineDraw->SetArrayState(arrayState);
	faceDraw->SetArrayState(arrayState);
	textureDraw->SetArrayState(arrayState);
	return;
}

bool fk_GraphicsEngine::GetOGLPointerMode(void)
{
	return arrayState;
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

void fk_GraphicsEngine::GetPickData(fk_PickData *argPickData,
									int argPixSize, int argMouseX, int argMouseY)
{
	GLint			hits = 0;
	_st				ii;
	int				elemID;
	fk_ObjectType	elemType = FK_BASEOBJECT;
	double			farDepth, nearDepth;

	if(argPickData == nullptr) return;

	SetPickViewPort(argPixSize, argMouseX, argMouseY);
	RecalcModelView();
	DrawObjs(true);

#ifndef OPENGL4
	hits = glRenderMode(GL_RENDER);
#endif

	argPickData->ClearData();

	for(ii = 0; ii < static_cast<_st>(hits); ii++) {
		switch(selectBuf[ii*5 + 4] % 3) {
		  case 0:
			elemType = FK_LOOP;
			break;

		  case 1:
			elemType = FK_EDGE;
			break;

		  case 2:
			elemType = FK_VERTEX;
			break;

		  default:
			break;
		}

		elemID = static_cast<int>(selectBuf[ii*5 + 4]/3);
		farDepth = static_cast<double>(selectBuf[ii*5 + 1])/0xffffffff;
		nearDepth = static_cast<double>(selectBuf[ii*5 + 2])/0xffffffff;

		argPickData->PushData(modelArray[selectBuf[ii*5 + 3]],
							  elemID, elemType, farDepth, nearDepth);
	}
	
	SetViewPort();

	return;
}

#ifdef NO_GLU_LIBRARY

void fk_GraphicsEngine::gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez,
								  GLdouble cx, GLdouble cy, GLdouble cz,
								  GLdouble upx, GLdouble upy, GLdouble upz)
{
	GLdouble	m[16];
	GLdouble	tmpX[3], tmpY[3], tmpZ[3];
	GLdouble	mag;

	// Z vector
	tmpZ[0] = eyex - cx;
	tmpZ[1] = eyey - cy;
	tmpZ[2] = eyez - cz;
	mag = sqrt(tmpZ[0]*tmpZ[0] + tmpZ[1]*tmpZ[1] + tmpZ[2]*tmpZ[2]);
	if (mag > FK_EPS) {
		tmpZ[0] /= mag;
		tmpZ[1] /= mag;
		tmpZ[2] /= mag;
	}

	// Y vector
	tmpY[0] = upx;
	tmpY[1] = upy;
	tmpY[2] = upz;

	// X vector = Y cross Z
	tmpX[0] =  tmpY[1]*tmpZ[2] - tmpY[2]*tmpZ[1];
	tmpX[1] = -tmpY[0]*tmpZ[2] + tmpY[2]*tmpZ[0];
	tmpX[2] =  tmpY[0]*tmpZ[1] - tmpY[1]*tmpZ[0];

	// Recompute Y = Z cross X
	tmpY[0] =  tmpZ[1]*tmpX[2] - tmpZ[2]*tmpX[1];
	tmpY[1] = -tmpZ[0]*tmpX[2] + tmpZ[2]*tmpX[0];
	tmpY[2] =  tmpZ[0]*tmpX[1] - tmpZ[1]*tmpX[0];

	mag = sqrt(tmpX[0]*tmpX[0] + tmpX[1]*tmpX[1] + tmpX[2]*tmpX[2]);
	if (mag > FK_EPS) {
		tmpX[0] /= mag;
		tmpX[1] /= mag;
		tmpX[2] /= mag;
	}

	mag = sqrt(tmpY[0]*tmpY[0] + tmpY[1]*tmpY[1] + tmpY[2]*tmpY[2]);
	if (mag > FK_EPS) {
		tmpY[0] /= mag;
		tmpY[1] /= mag;
		tmpY[2] /= mag;
	}

	m[0] = tmpX[0];	m[4] = tmpX[1];	m[8] = tmpX[2];		m[12] = 0.0;
	m[1] = tmpY[0];	m[5] = tmpY[1];	m[9] = tmpY[2];		m[13] = 0.0;
	m[2] = tmpZ[0];	m[6] = tmpZ[1];	m[10] = tmpZ[2];	m[14] = 0.0;
	m[3] = 0.0;		m[7] = 0.0;		m[11] = 0.0;		m[15] = 1.0;

#ifndef OPENGL4
	glMultMatrixd(m);
#endif

	// Translate Eye to Origin
	glTranslated(-eyex, -eyey, -eyez);

	return;
}

void fk_GraphicsEngine::gluPerspective(GLdouble argFovy, GLdouble argAspect,
									   GLdouble argZNear, GLdouble argZFar)
{
	GLdouble	xmin, xmax, ymin, ymax;

	ymax = argZNear * tan(argFovy * FK_PI / 360.0);
	ymin = -ymax;

	xmin = ymin * argAspect;
	xmax = ymax * argAspect;

	glFrustum(xmin, xmax, ymin, ymax, argZNear, argZFar);

	return;
}

void fk_GraphicsEngine::gluPickMatrix(GLdouble argX, GLdouble argY,
									  GLdouble width, GLdouble height,
									  const GLint viewport[4])
{
	GLdouble	m[16];
	GLdouble	sx, sy;
	GLdouble	tx, ty;

	sx = static_cast<GLdouble>(viewport[2])/width;
	sy = static_cast<GLdouble>(viewport[3])/height;
	tx = (static_cast<GLdouble>(viewport[2]) +
		  2.0 * (static_cast<GLdouble>(viewport[0]) - argX))/width;
	ty = (static_cast<GLdouble>(viewport[3]) +
		  2.0 * (static_cast<GLdouble>(viewport[1]) - argY))/height;

	m[0] = sx;	m[4] = 0.0;	 m[8] = 0.0;   m[12] = tx;
	m[1] = 0.0;	m[5] = sy;	 m[9] = 0.0;   m[13] = ty;
	m[2] = 0.0;	m[6] = 0.0;	 m[10] = 1.0;  m[14] = 0.0;
	m[3] = 0.0;	m[7] = 0.0;	 m[11] = 0.0;  m[15] = 1.0;

	glMultMatrixd(m);

	return;
}

#endif // NO_GLU_LIBRARY

#endif
