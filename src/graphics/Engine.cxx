﻿/****************************************************************************
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
#define FK_DEF_SIZETYPE
#include <FK/Error.H>
#include <FK/Engine.H>
#include <FK/Scene.h>
#include <FK/Light.h>
#include <FK/Plane.h>
#include <FK/Curve.h>
#include <FK/Surface.h>
#include <FK/Graph.h>
#include <FK/Projection.h>
#include <FK/PointDraw.H>
#include <FK/LineDraw.H>
#include <FK/FaceDraw.H>
#include <FK/TextureDraw.H>
#include <FK/BezCurveDraw.H>
#include <FK/SurfaceDraw.H>
#include <FK/Error.H>

using namespace std;
using namespace FK;

static unsigned int		generalID = 1;
static unsigned int		engineNum = 0;

fk_PointDraw * fk_GraphicsEngine::pointDraw = nullptr;
fk_LineDraw * fk_GraphicsEngine::lineDraw = nullptr;
fk_FaceDraw * fk_GraphicsEngine::faceDraw = nullptr;
fk_TextureDraw * fk_GraphicsEngine::textureDraw = nullptr;
fk_BezCurveDraw * fk_GraphicsEngine::bezCurveLineDraw = nullptr;
fk_BezCurveDraw * fk_GraphicsEngine::bezCurvePointDraw = nullptr;
fk_SurfaceDraw * fk_GraphicsEngine::surfaceDraw = nullptr;
fk_SurfaceDraw * fk_GraphicsEngine::surfacePointDraw = nullptr;
fk_SurfaceDraw * fk_GraphicsEngine::surfaceLineDraw = nullptr;

static const GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};

fk_GraphicsEngine::fk_GraphicsEngine(void)
{
	if(engineNum == 0) {
		pointDraw = new fk_PointDraw;
		lineDraw = new fk_LineDraw;
		faceDraw = new fk_FaceDraw;
		textureDraw = new fk_TextureDraw;
		bezCurveLineDraw = new fk_BezCurveDraw(1);
		bezCurvePointDraw = new fk_BezCurveDraw(2);
		surfaceDraw = new fk_SurfaceDraw(1);
		surfaceLineDraw = new fk_SurfaceDraw(2);
		surfacePointDraw = new fk_SurfaceDraw(3);
	}

	engineNum++;

	winID = 0;
	curDLink = nullptr;
	dLinkStatus = 0;
	dLinkID = 0;
	wSize = 0;
	hSize = 0;
	resizeFlag = false;

	srcFactor = fk_BlendFactor::SRC_ALPHA;
	dstFactor = fk_BlendFactor::ONE_MINUS_SRC_ALPHA;
	depthRead = depthWrite = true;

	boundaryModel.setDrawMode(fk_Draw::LINE);
	boundaryModel.setBMode(fk_BoundaryMode::NONE);
	boundaryModel.setBDrawToggle(false);

	FBOMode = false;
	FBOWindowMode = false;
	colorTex = nullptr;
	depthTex = nullptr;
	rectVAO = 0;
	fboHandle = 0;
	FBOShader = nullptr;
	
	return;
}

fk_GraphicsEngine::~fk_GraphicsEngine()
{
	engineNum--;

	if(engineNum == 0) {
		delete pointDraw; pointDraw = nullptr;
		delete lineDraw; lineDraw = nullptr;
		delete faceDraw; faceDraw = nullptr;
		delete textureDraw; textureDraw = nullptr;
		delete bezCurveLineDraw; bezCurveLineDraw = nullptr;
		delete bezCurvePointDraw; bezCurvePointDraw = nullptr;
		delete surfaceDraw; surfaceDraw = nullptr;
		delete surfaceLineDraw; surfaceLineDraw = nullptr;
		delete surfacePointDraw; surfacePointDraw = nullptr;
	}

	snapBuffer.clear();

	delete colorTex;
	delete depthTex;

	if(FBOMode == true) {
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		if(fboHandle != 0) glDeleteFramebuffers(1, &fboHandle);
	}
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

	FBOMode = false;
	FBOWindowMode = false;
	delete colorTex;
	delete depthTex;
	colorTex = nullptr;
	depthTex = nullptr;
	FBOShader = nullptr;
	
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
	if(curProj->getMode() == fk_ProjectMode::PERSPECTIVE) {
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
	glEnable(GL_MULTISAMPLE);
	glClearDepth(1.0);
	//glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);

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
			if(curDLink->getObjectType() == fk_Type::SCENE) {
				scene = static_cast<fk_Scene *>(curDLink);
				scene->GetFogChangeStatus();
				fogStatus = true;
			}
		} else {
			if(curDLink->getObjectType() == fk_Type::SCENE) {
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
	if(FBOMode == true) PreFBODraw();
	// リサイズ時に加えて、マルチウィンドウ時もビューポートを再設定(by rita)
	if(resizeFlag == true || generalID > 2) {
		SetViewPort();
		resizeFlag = false;
	}

	SetDepthMode(fk_DepthMode::READ_AND_WRITE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	ApplySceneParameter(true);

	curProj->MakeMat();

	fk_DrawBase::SetCamera(curDLink->getCamera());

	fk_DrawBase::SetLight(curDLink->GetLightList(fk_LightType::PARALLEL),
						  fk_LightType::PARALLEL);

	fk_DrawBase::SetLight(curDLink->GetLightList(fk_LightType::POINT),
						  fk_LightType::POINT);

	fk_DrawBase::SetLight(curDLink->GetLightList(fk_LightType::SPOT),
						  fk_LightType::SPOT);

	DrawObjs();

	if(FBOMode == true) PostFBODraw();
	if(FBOWindowMode == true) FBOWindowDraw();
	
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

	SetDepthMode(fk_DepthMode::NO_USE);
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
	  case fk_BoundaryMode::SPHERE:
	  case fk_BoundaryMode::AABB:
		  boundaryModel.glMoveTo(argModel->getInhPosition());
		  break;
		  
	  case fk_BoundaryMode::OBB:
		  boundaryModel.glMoveTo(argModel->getInhPosition());
		  boundaryModel.glAngle(argModel->getInhAngle());
		  break;

	  case fk_BoundaryMode::CAPSULE:
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
	boundaryModel.setDrawMode(fk_Draw::LINE);
	DrawModel(&boundaryModel);
	return;
}

void fk_GraphicsEngine::DrawShapeObj(fk_Model *argModel)
{
	if(argModel == nullptr) return;

	auto drawMode = argModel->getDrawMode();
	if(drawMode == fk_Draw::NONE) return;

	auto realType = argModel->getShape()->getRealShapeType();

	fk_Curve *curve = nullptr;
	fk_Surface *surface = nullptr;
	fk_Graph *graph = nullptr;

	switch(realType) {
	  case fk_RealShapeType::CURVE:
		curve = dynamic_cast<fk_Curve *>(argModel->getShape());
		break;

	  case fk_RealShapeType::SURFACE:
		surface = dynamic_cast<fk_Surface *>(argModel->getShape());
		break;

	  case fk_RealShapeType::GRAPH:
		graph = dynamic_cast<fk_Graph *>(argModel->getShape());
		break;

	  default:
		break;
	}

	argModel->getShape()->FlushAttr();

	if((drawMode & fk_Draw::FACE) != fk_Draw::NONE) {
		faceDraw->DrawShapeFace(argModel);
	}

	if((drawMode & fk_Draw::POINT) != fk_Draw::NONE) {
		if(curve != nullptr) {
			pointDraw->DrawShapePoint(argModel, curve->GetPoint());
		} else if(surface != nullptr) {
			pointDraw->DrawShapePoint(argModel, surface->GetPoint());
		} else if(graph != nullptr) {
			pointDraw->DrawShapePoint(argModel, graph->GetVertexShape());
		} else {
			pointDraw->DrawShapePoint(argModel);
		}
	}

	if((drawMode & fk_Draw::LINE) != fk_Draw::NONE) {
		if(curve != nullptr) {
			lineDraw->DrawShapeLine(argModel, curve->GetLine());
		} else if(surface != nullptr) {
			lineDraw->DrawShapeLine(argModel, surface->GetLine());
		} else if(graph != nullptr) {
			lineDraw->DrawShapeLine(argModel, graph->GetEdgeShape());
		} else {
			lineDraw->DrawShapeLine(argModel);
		}
	}

	if((drawMode & fk_Draw::TEXTURE) != fk_Draw::NONE) {
		textureDraw->DrawShapeTexture(argModel);
	}

	if((drawMode & fk_Draw::GEOM_LINE) != fk_Draw::NONE) {
		if(curve != nullptr) {
			bezCurveLineDraw->DrawShapeCurve(argModel);
		} else if(surface != nullptr) {
			surfaceLineDraw->DrawShapeSurface(argModel);
		}
	}

	if((drawMode & fk_Draw::GEOM_POINT) != fk_Draw::NONE) {
		if(curve != nullptr) {
			bezCurvePointDraw->DrawShapeCurve(argModel);
		} else if(surface != nullptr) {
			surfacePointDraw->DrawShapeSurface(argModel);
		}
	}

	if((drawMode & fk_Draw::GEOM_FACE) != fk_Draw::NONE) {
		if(surface != nullptr) {
			surfaceDraw->DrawShapeSurface(argModel);
		}
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

tuple<fk_Vector, fk_Vector> fk_GraphicsEngine::GetViewLinePos(double argX, double argY)
{
	fk_HVector		inVec, outS, outE;
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
	outS = mat * inVec;
	inVec.z = 1.0;
	outE = mat * inVec;

	if(fabs(outS.w) < fk_Math::EPS || fabs(outE.w) < fk_Math::EPS) return {outS, outE};
	return {fk_Vector(outS)/outS.w, fk_Vector(outE)/outE.w};
}

tuple<bool, fk_Vector> fk_GraphicsEngine::GetProjectPosition(double argX, double argY,
															 fk_Plane &argPlane)
{
	if(curDLink == nullptr) return {false, fk_Vector()};
	if(generalID > 2) SetViewPort();

	auto [sVec, eVec] = GetViewLinePos(argX, argY);
	return argPlane.calcCrossPos(sVec, eVec);
}

tuple<bool, fk_Vector> fk_GraphicsEngine::GetProjectPosition(double argX, double argY,
															 double argDist)
{
	fk_Vector		eyeVec, cameraPos;
	const fk_Model	*tmpCamera;

	if(curDLink == nullptr) return {false, fk_Vector()};
	tmpCamera = curDLink->getCamera();
	if(generalID > 2) SetViewPort();

	auto [sVec, eVec] = GetViewLinePos(argX, argY);
	eyeVec = eVec - sVec;
	eyeVec.normalize();
	if(tmpCamera == nullptr) {
		cameraPos.set(0.0, 0.0, 0.0);
	} else {
		cameraPos = tmpCamera->getInhPosition();
	}

	return {true, cameraPos + eyeVec * argDist};
}

tuple<bool, fk_Vector> fk_GraphicsEngine::GetWindowPosition(fk_Vector &argPos)
{
	fk_HVector inVec, outVec, retPos;
	fk_Matrix mat;

	inVec = argPos;
	inVec.w = 1.0;

	if(generalID > 2) SetViewPort();

	glGetIntegerv(GL_VIEWPORT, viewArray);
	mat = *(curProj->GetMatrix()) * curDLink->getCamera()->getInhInvMatrix();
	outVec = mat * inVec;

	if(fabs(outVec.w) < fk_Math::EPS) return {false, retPos};
	outVec /= outVec.w;
	retPos.set(double(viewArray[0]) + double(viewArray[2])*(outVec.x + 1.0)/2.0,
			   double(viewArray[1] + hSize - 1) - double(viewArray[3])*(outVec.y + 1.0)/2.0,
			   (1.0 + outVec.z)/2.0);
	return {true, retPos};
}

GLenum GetBlendFactor(fk_BlendFactor factor)
{
	switch (factor) {
	case fk_BlendFactor::ZERO:
		return GL_ZERO;
	case fk_BlendFactor::ONE:
		return GL_ONE;
	case fk_BlendFactor::SRC_COLOR:
		return GL_SRC_COLOR;
	case fk_BlendFactor::ONE_MINUS_SRC_COLOR:
		return GL_ONE_MINUS_SRC_ALPHA;
	case fk_BlendFactor::DST_COLOR:
		return GL_DST_COLOR;
	case fk_BlendFactor::ONE_MINUS_DST_COLOR:
		return GL_ONE_MINUS_DST_COLOR;
	case fk_BlendFactor::SRC_ALPHA:
		return GL_SRC_ALPHA;
	case fk_BlendFactor::ONE_MINUS_SRC_ALPHA:
		return GL_ONE_MINUS_SRC_ALPHA;
	case fk_BlendFactor::DST_ALPHA:
		return GL_DST_ALPHA;
	case fk_BlendFactor::ONE_MINUS_DST_ALPHA:
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
	bool readMode = ((argMode & fk_DepthMode::READ) != fk_DepthMode::NO_USE);
	bool writeMode = ((argMode & fk_DepthMode::WRITE) != fk_DepthMode::NO_USE);

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
	if(argMode == fk_SnapProcMode::FRONT) {
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

void fk_GraphicsEngine::SetupFBO(void)
{
	if(colorTex != nullptr) delete colorTex;
	colorTex = new fk_FrameTexture();
	if(depthTex != nullptr) delete depthTex;
	depthTex = new fk_FrameTexture();

	colorTex->setSource(fk_SamplerSource::COLOR);
	depthTex->setSource(fk_SamplerSource::DEPTH);

	colorTex->setBufferSize(wSize, hSize);
	colorTex->setTexWrapMode(fk_TexWrapMode::CLAMP);
	colorTex->setTexRendMode(fk_TexRendMode::SMOOTH);
	colorTex->SetupFBO();

	depthTex->setBufferSize(wSize, hSize);
	depthTex->setTexWrapMode(fk_TexWrapMode::CLAMP);
	depthTex->setTexRendMode(fk_TexRendMode::SMOOTH);
	depthTex->SetupFBO();

	glGenFramebuffers(1, &fboHandle);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboHandle);

#ifdef WIN32	
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, wSize);
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, hSize);
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, 2);
#endif

	colorTex->AttachFBO();
	depthTex->AttachFBO();

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	FBOMode = true;
}

void fk_GraphicsEngine::PreFBODraw(void)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboHandle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);
	glDrawBuffers(sizeof(drawBuffers) / sizeof(drawBuffers[0]), drawBuffers);
	if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		fk_Window::putString("FBO Error");
	}
}

void fk_GraphicsEngine::PostFBODraw(void)
{
 	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fboHandle);

	FBOShader->ProcPreShader();
	glDrawBuffer(GL_BACK);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	colorTex->BindFBO();
	depthTex->BindFBO();

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void fk_GraphicsEngine::FBOWindowDraw(void)
{
	glBindVertexArray(rectVAO);
	glDrawArrays(GL_POINTS, 0, 1);

	FBOShader->ProcPostShader();

	colorTex->Unbind();
	depthTex->Unbind();
}	
	

void fk_GraphicsEngine::BindWindow(fk_ShaderBinder *argShader)
{
	FBOShader = argShader;

	SetupFBO();

	FBOWindowMode = true;

	GLuint handle;
	glGenBuffers(1, &handle);

	static GLfloat verts[3] = {0.0f, 0.0f, 0.0f};

	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), verts, GL_STATIC_DRAW);

	glGenVertexArrays(1, &rectVAO);
	glBindVertexArray(rectVAO);

	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}
