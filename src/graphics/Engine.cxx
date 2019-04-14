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
#include <FK/Error.H>
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

	srcFactor = FK_FACTOR_SRC_ALPHA;
	dstFactor = FK_FACTOR_ONE_MINUS_SRC_ALPHA;
	depthRead = depthWrite = true;

	boundaryModel.setDrawMode(FK_LINEMODE);
	boundaryModel.setBMode(FK_B_NONE);
	boundaryModel.setBDrawToggle(false);
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

void fk_GraphicsEngine::SetViewPort(void)
{
	glViewport(0, 0, wSize, hSize);
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
	fk_DrawBase::SetProjectionMatrix(curProj->GetMatrix());

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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPolygonMode(GL_FRONT, GL_FILL);
	glDisable(GL_BLEND);

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

	SetDepthMode(FK_DEPTH_READ_AND_WRITE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ApplySceneParameter(true);

	curProj->MakeMat();
	fk_DrawBase::SetCamera(curDLink->getCamera());
	fk_DrawBase::SetLight(curDLink->GetLightList(FK_PARALLEL_LIGHT), FK_PARALLEL_LIGHT);
	fk_DrawBase::SetLight(curDLink->GetLightList(FK_POINT_LIGHT), FK_POINT_LIGHT);
	fk_DrawBase::SetLight(curDLink->GetLightList(FK_SPOT_LIGHT), FK_SPOT_LIGHT);
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

	if(curDLink == nullptr) return;

	modelPEnd = curDLink->GetModelList()->end();
	for(modelP = curDLink->GetModelList()->begin();
		modelP != modelPEnd; ++modelP) {
		SetDepthMode((*modelP)->getDepthMode());
		DrawModel(*modelP);
	}

	overlayList = curDLink->GetOverlayList();
	if(overlayList->empty() == true) return;

	SetDepthMode(FK_DEPTH_NO_USE);
	modelPEnd = overlayList->end();
	for(modelP = overlayList->begin(); modelP != modelPEnd; ++modelP) {
		DrawModel(*modelP);
	}

	return;
}

void fk_GraphicsEngine::DrawModel(fk_Model *argModel)
{
	if(argModel->getBDrawToggle() == true) DrawBoundaryLine(argModel);

	fk_Shape * modelShape = argModel->getShape();
	if(modelShape == nullptr) return;
	modelShape->FlushAttr();
	fk_DrawBase::SetModel(argModel);
	SetBlendMode(argModel);
	DrawShapeObj(argModel);
	modelShape->FinishSetVBO();
	return;
}

void fk_GraphicsEngine::DrawBoundaryLine(fk_Model *argModel)
{
	fk_Vector posS, posE;
	fk_Matrix mat;

	switch(argModel->getBMode()) {
	  case FK_B_SPHERE:
	  case FK_B_AABB:
		  boundaryModel.glMoveTo(argModel->getInhPosition());
		  break;
		  
	  case FK_B_OBB:
		  boundaryModel.glMoveTo(argModel->getInhPosition());
		  boundaryModel.glAngle(argModel->getInhAngle());
		  break;

	  case FK_B_CAPSULE:
		  mat = argModel->getInhMatrix();
		  posS = mat * argModel->getCapsuleStartPos();
		  posE = mat * argModel->getCapsuleEndPos();
		  boundaryModel.glMoveTo((posS + posE)/2.0);
		  boundaryModel.glVec(posE - posS);
		  break;
		  
	  default:
		  return;
	}

	if(argModel->getInterMode() == true &&
	   argModel->getInterStatus() == true) {
		boundaryModel.setLineColor(argModel->getBIntLineColor());
	} else {
		boundaryModel.setLineColor(argModel->getBLineColor());
	}	
	boundaryModel.setShape(argModel->GetBShape());
	boundaryModel.setDrawMode(FK_LINEMODE);
	DrawModel(&boundaryModel);
	return;
}

void fk_GraphicsEngine::DrawShapeObj(fk_Model *argModel)
{
	fk_DrawMode		DrawMode;

	DrawMode = argModel->getDrawMode();

	if(DrawMode == FK_NONEMODE) return;

	argModel->getShape()->FlushAttr();

	if((DrawMode & FK_POLYMODE) != FK_NONEMODE) {
		faceDraw->DrawShapeFace(argModel);
	}

	if((DrawMode & FK_POINTMODE) != FK_NONEMODE) {
		pointDraw->DrawShapePoint(argModel);
	}

	if((DrawMode & FK_LINEMODE) != FK_NONEMODE) {
		lineDraw->DrawShapeLine(argModel);
	}

	if((DrawMode & FK_TEXTUREMODE) != FK_NONEMODE) {
		textureDraw->DrawShapeTexture(argModel);
	}

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

bool fk_GraphicsEngine::GetViewLinePos(double argX, double argY,
									   fk_Vector *retS, fk_Vector *retE)
{
	fk_HVector		inVec, outVec;
	fk_Matrix		mat;
	double			tmpY;
	double			diffX, diffY;

	mat = *(curProj->GetMatrix()) * curDLink->getCamera()->getInhInvMatrix();
	mat.inverse();

	glGetIntegerv(GL_VIEWPORT, viewArray);

	tmpY = double(hSize) - argY - 1.0;
	diffX = argX - double(viewArray[0]);
	diffY = tmpY - double(viewArray[1]);

	inVec.x = diffX*2.0/double(viewArray[2]) - 1.0;
	inVec.y = diffY*2.0/double(viewArray[3]) - 1.0;
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

	glGetIntegerv(GL_VIEWPORT, viewArray);
	mat = *(curProj->GetMatrix()) * curDLink->getCamera()->getInhInvMatrix();
	outVec = mat * inVec;
	if(fabs(outVec.w) < FK_EPS) return false;
	outVec /= outVec.w;
	retPos->set(double(viewArray[0]) + double(viewArray[2])*(outVec.x + 1.0)/2.0,
				double(viewArray[1] + hSize - 1) - double(viewArray[3])*(outVec.y + 1.0)/2.0,
				(1.0 + outVec.z)/2.0);
	return true;
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
	bool readMode = (argMode & FK_DEPTH_READ) != 0;
	bool writeMode = (argMode & FK_DEPTH_WRITE) != 0;

	if (depthRead != readMode) {
		if (readMode == true) {
			glEnable(GL_DEPTH_TEST);
		} else {
			glDisable(GL_DEPTH_TEST);
		}
		depthRead = readMode;
	}
	if (depthWrite != writeMode) {
		if(writeMode == true) {
			glDepthMask(GL_TRUE);
		} else {
			glDepthMask(GL_FALSE);
		}
		depthWrite = writeMode;
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
