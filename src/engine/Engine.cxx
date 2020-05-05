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

unsigned int fk_GraphicsEngine::generalID = 1;
unsigned int fk_GraphicsEngine::engineNum = 0;

unique_ptr<fk_PointDraw> fk_GraphicsEngine::pointDraw = nullptr;
unique_ptr<fk_LineDraw> fk_GraphicsEngine::lineDraw = nullptr;
unique_ptr<fk_FaceDraw> fk_GraphicsEngine::faceDraw = nullptr;
unique_ptr<fk_TextureDraw> fk_GraphicsEngine::textureDraw = nullptr;
unique_ptr<fk_BezCurveDraw> fk_GraphicsEngine::bezCurveLineDraw = nullptr;
unique_ptr<fk_BezCurveDraw> fk_GraphicsEngine::bezCurvePointDraw = nullptr;
unique_ptr<fk_SurfaceDraw> fk_GraphicsEngine::surfaceDraw = nullptr;
unique_ptr<fk_SurfaceDraw> fk_GraphicsEngine::surfacePointDraw = nullptr;
unique_ptr<fk_SurfaceDraw> fk_GraphicsEngine::surfaceLineDraw = nullptr;

#ifndef GL_COLOR_ATTACHMENT0
#define GL_COLOR_ATTACHMENT0 0x8CE0
#endif

#ifndef GL_DEPTH_ATTACHMENT
#define GL_DEPTH_ATTACHMENT 0x8D00
#endif

static constexpr GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};
static constexpr GLenum shadowBuffers[] = {GL_DEPTH_ATTACHMENT};

fk_GraphicsEngine::Member::Member(bool argWinMode) :
	drawCount(0), winID(0), curScene(nullptr), sceneStatus(0),
	sceneID(0), wSize(0), hSize(0), resizeFlag(false),
	srcFactor(fk_BlendFactor::SRC_ALPHA), dstFactor(fk_BlendFactor::ONE_MINUS_SRC_ALPHA),
	depthRead(true), depthWrite(true), curProj(nullptr),
	FBOMode(false), FBOWindowMode(argWinMode),
	rectVAO(0), fboHandle(0), FBOShader(nullptr),
	shadowHandle(0), shadowMode(fk_ShadowMode::OFF),
	shadowInitFlag(false), shadowSwitch(false), shadowBufferID(-1),
	shadowSize(100.0), shadowDistance(100.0),
	shadowResolution(1024), shadowVisibility(1.0), shadowBias(0.0005),
	shadowVec(fk_Vector(0.0, -1.0, 0.0)),
	fogMode(fk_FogMode::OFF), fogStart(0.0), fogEnd(0.0), fogDensity(0.0)
{
	boundaryModel.setDrawMode(fk_Draw::LINE);
	boundaryModel.setBMode(fk_BoundaryMode::NONE);
	boundaryModel.setBDrawToggle(false);
	fogColor.set(0.0, 0.0, 0.0, 1.0);
	return;
}

fk_GraphicsEngine::fk_GraphicsEngine(bool argWinMode) : _m(make_unique<Member>(argWinMode))
{
	if (fk_ShaderBinder::IsInitialized() == false) fk_ShaderBinder::Initialize();

	// エンジン用インスタンス生成
	if(pointDraw == nullptr) pointDraw = make_unique<fk_PointDraw>();
	if(lineDraw == nullptr) lineDraw = make_unique<fk_LineDraw>();
	if(faceDraw == nullptr) faceDraw = make_unique<fk_FaceDraw>();
	if(textureDraw == nullptr) textureDraw = make_unique<fk_TextureDraw>();

	if(bezCurveLineDraw == nullptr) {
		bezCurveLineDraw = make_unique<fk_BezCurveDraw>(fk_CurveDrawMode::LINE);
	}
	if(bezCurvePointDraw == nullptr) {
		bezCurvePointDraw = make_unique<fk_BezCurveDraw>(fk_CurveDrawMode::POINT);
	}
	if(surfaceDraw == nullptr) {
		surfaceDraw = make_unique<fk_SurfaceDraw>(fk_SurfaceDrawMode::FACE);
	}
	if(surfaceLineDraw == nullptr) {
		surfaceLineDraw = make_unique<fk_SurfaceDraw>(fk_SurfaceDrawMode::LINE);
	}
	if(surfacePointDraw == nullptr) {
		surfacePointDraw = make_unique<fk_SurfaceDraw>(fk_SurfaceDrawMode::POINT);
	}

	engineNum++;

	return;
}

fk_GraphicsEngine::~fk_GraphicsEngine()
{
	engineNum--;

	_m->snapBuffer.clear();

	if(_m->shadowBuf != nullptr) {
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		if(_m->shadowHandle != 0) glDeleteFramebuffers(1, &(_m->shadowHandle));
	}

	if(_m->FBOMode == true) {
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		if(_m->fboHandle != 0) glDeleteFramebuffers(1, &(_m->fboHandle));
	}
	return;
}

bool fk_GraphicsEngine::AllTest(void)
{
	bool retFlg = true;

	if(pointDraw->AllTest() == false) retFlg = false;
	if(lineDraw->AllTest() == false) retFlg = false;
	if(faceDraw->AllTest() == false) retFlg = false;
	if(textureDraw->AllTest() == false) retFlg = false;
	if(bezCurveLineDraw->AllTest() == false) retFlg = false;
	if(bezCurvePointDraw->AllTest() == false) retFlg = false;
	if(surfaceDraw->AllTest() == false) retFlg = false;
	if(surfaceLineDraw->AllTest() == false) retFlg = false;
	if(surfacePointDraw->AllTest() == false) retFlg = false;
	return retFlg;
}

void fk_GraphicsEngine::Init(int argW, int argH)
{
	_m->winID = generalID;
	generalID++;
	_m->curScene = nullptr;
	_m->sceneStatus = FK_UNDEFINED;
	_m->sceneID = FK_UNDEFINED;
	_m->wSize = argW;
	_m->hSize = argH;
	_m->resizeFlag = false;

	_m->defProj.setAll(40.0*fk_Math::PI/180.0, 1.0, 6000.0);

	_m->FBOMode = false;
	_m->FBOWindowMode = false;
	_m->FBOShader = nullptr;

	return;
}

void fk_GraphicsEngine::ResizeWindow(int argW, int argH)
{
	_m->wSize = argW;
	_m->hSize = argH;
	_m->resizeFlag = true;

	return;
}

void fk_GraphicsEngine::SetViewPort(void)
{
	glViewport(0, 0, _m->wSize, _m->hSize);
	if(_m->curScene == nullptr) {
		SetProjection(&(_m->defProj));
	} else {
		SetProjection(_m->curScene->getProjection());
	}
	return;
}

void fk_GraphicsEngine::SetProjection(fk_ProjectBase *argProj)
{
	_m->curProj = argProj;
	if(_m->curProj->getMode() == fk_ProjectMode::PERSPECTIVE) {
		fk_Perspective *pers = dynamic_cast<fk_Perspective *>(_m->curProj);
		pers->setAspect(GLfloat(_m->wSize)/GLfloat(_m->hSize));
	}
	_m->curProj->MakeMat();
	fk_DrawBase::SetProjectionMatrix(_m->curProj->GetMatrix());

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
	//glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);

	return;
}

void fk_GraphicsEngine::ApplySceneParameter(void)
{
	fk_Color bgColor;

	if(_m->curScene != nullptr) {
		if(_m->sceneID != _m->curScene->GetID() ||
		   _m->sceneStatus != _m->curScene->GetProjChangeStatus()) {
			_m->sceneID = _m->curScene->GetID();
			_m->sceneStatus = _m->curScene->GetProjChangeStatus();
			SetViewPort();
		} else {
		}

		if(_m->curScene->getBlendStatus() == true) {
			glEnable(GL_BLEND);
		} else {
			glDisable(GL_BLEND);
		}
		InitFogStatus(_m->curScene);
		bgColor = _m->curScene->getBGColor();
		glClearColor(bgColor.col[0], bgColor.col[1], bgColor.col[2], 1.0f);

	} else {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	return;
}

unsigned int fk_GraphicsEngine::Draw(void)
{
	if(_m->curScene != nullptr) _m->shadowMode = _m->curScene->getShadowMode();

	fk_DrawBase::SetShadowMode(_m->shadowMode);
	if(_m->shadowMode != fk_ShadowMode::OFF) {
		if(_m->shadowInitFlag == false) {
			ShadowInit();
			_m->shadowInitFlag = true;
		}
		_m->shadowSwitch = true;
		DrawShadow();
		_m->shadowSwitch = false;
	}
	DrawWorld();
	_m->drawCount++;
	return _m->drawCount;
}

void fk_GraphicsEngine::DrawWorld(void)
{
	if(_m->FBOMode == true) PreFBODraw();

	if(_m->resizeFlag == true || generalID > 2 || _m->shadowMode != fk_ShadowMode::OFF) {
		SetViewPort();
		_m->resizeFlag = false;
	}

	SetDepthMode(fk_DepthMode::READ_AND_WRITE);
	ApplySceneParameter();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	_m->curProj->MakeMat();

	if(_m->curScene != nullptr) {
		fk_DrawBase::SetCamera(_m->curScene->getCamera());

		fk_DrawBase::SetLight(_m->curScene->GetLightList(fk_LightType::PARALLEL),
							  fk_LightType::PARALLEL);

		fk_DrawBase::SetLight(_m->curScene->GetLightList(fk_LightType::POINT),
							  fk_LightType::POINT);

		fk_DrawBase::SetLight(_m->curScene->GetLightList(fk_LightType::SPOT),
							  fk_LightType::SPOT);
	}

	DrawObjs();

	if(_m->FBOMode == true) PostFBODraw();
	
	return;
}

void fk_GraphicsEngine::SetScene(fk_Scene *argScene)
{
	_m->curScene = argScene;
	return;
}

void fk_GraphicsEngine::DrawObjs(void)
{
	if(_m->curScene == nullptr) return;

	for(auto modelP : *(_m->curScene->GetModelList())) {
		SetDepthMode(modelP->getDepthMode());
		DrawModel(modelP);
	}

	if(_m->curScene->GetOverlayList()->empty() == true) return;
	SetDepthMode(fk_DepthMode::NO_USE);
	for(auto modelP : *(_m->curScene->GetOverlayList())) DrawModel(modelP);

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
		  _m->boundaryModel.glMoveTo(argModel->getInhPosition());
		  break;
		  
	  case fk_BoundaryMode::OBB:
		  _m->boundaryModel.glMoveTo(argModel->getInhPosition());
		  _m->boundaryModel.glAngle(argModel->getInhAngle());
		  break;

	  case fk_BoundaryMode::CAPSULE:
		  mat = argModel->getInhMatrix();
		  posS = mat * argModel->getCapsuleStartPos();
		  posE = mat * argModel->getCapsuleEndPos();
		  _m->boundaryModel.glMoveTo((posS + posE)/2.0);
		  _m->boundaryModel.glVec(posE - posS);
		  break;
		  
	  default:
		  return;
	}

	if(argModel->getInterMode() == true &&
	   argModel->getInterStatus() == true) {
		_m->boundaryModel.setLineColor(argModel->getBIntLineColor());
	} else {
		_m->boundaryModel.setLineColor(argModel->getBLineColor());
	}	
	_m->boundaryModel.setShape(argModel->GetBShape());
	_m->boundaryModel.setDrawMode(fk_Draw::LINE);
	DrawModel(&(_m->boundaryModel));
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

	fk_FogMode localFogMode = (argModel->getFogMode()) ? _m->fogMode : fk_FogMode::OFF;

	if((drawMode & fk_Draw::FACE) != fk_Draw::NONE) {
		faceDraw->DrawShapeFace(argModel, _m->shadowMode, _m->shadowSwitch, localFogMode);
	}

	if((drawMode & fk_Draw::TEXTURE) != fk_Draw::NONE) {
		textureDraw->DrawShapeTexture(argModel, _m->shadowMode, _m->shadowSwitch, localFogMode);
	}

	if((drawMode & fk_Draw::GEOM_FACE) != fk_Draw::NONE) {
		if(surface != nullptr) {
			surfaceDraw->DrawShapeSurface(argModel, _m->shadowMode,
										  _m->shadowSwitch, localFogMode);
		}
	}

	if((drawMode & fk_Draw::POINT) != fk_Draw::NONE) {
		if(curve != nullptr) {
			pointDraw->DrawShapePoint(argModel, curve->GetPoint(),
									  _m->shadowSwitch, localFogMode);
		} else if(surface != nullptr) {
			pointDraw->DrawShapePoint(argModel, surface->GetPoint(),
									  _m->shadowSwitch, localFogMode);
		} else if(graph != nullptr) {
			pointDraw->DrawShapePoint(argModel, graph->GetVertexShape(),
									  _m->shadowSwitch, localFogMode);
		} else {
			pointDraw->DrawShapePoint(argModel, nullptr, _m->shadowSwitch, localFogMode);
		}
	}

	if((drawMode & fk_Draw::LINE) != fk_Draw::NONE) {
		if(curve != nullptr) {
			lineDraw->DrawShapeLine(argModel, curve->GetLine(),
									_m->shadowSwitch, localFogMode);
		} else if(surface != nullptr) {
			lineDraw->DrawShapeLine(argModel, surface->GetLine(),
									_m->shadowSwitch, localFogMode);
		} else if(graph != nullptr) {
			lineDraw->DrawShapeLine(argModel, graph->GetEdgeShape(),
									_m->shadowSwitch, localFogMode);
		} else {
			lineDraw->DrawShapeLine(argModel, nullptr, _m->shadowSwitch, localFogMode);
		}
	}

	if((drawMode & fk_Draw::GEOM_LINE) != fk_Draw::NONE) {
		if(curve != nullptr) {
			bezCurveLineDraw->DrawShapeCurve(argModel, _m->shadowSwitch, localFogMode);
		} else if(surface != nullptr) {
			surfaceLineDraw->DrawShapeSurface(argModel, _m->shadowMode,
											  _m->shadowSwitch, localFogMode);
		}
	}

	if((drawMode & fk_Draw::GEOM_POINT) != fk_Draw::NONE) {
		if(curve != nullptr) {
			bezCurvePointDraw->DrawShapeCurve(argModel, _m->shadowSwitch, localFogMode);
		} else if(surface != nullptr) {
			surfacePointDraw->DrawShapeSurface(argModel, _m->shadowMode,
											   _m->shadowSwitch, localFogMode);
		}
	}
	
	return;
}

void fk_GraphicsEngine::InitFogStatus(fk_Scene *argScene)
{
	if((_m->fogMode = argScene->getFogMode()) != fk_FogMode::OFF) {
		_m->fogStart = argScene->getFogLinearStart();
		_m->fogEnd = argScene->getFogLinearEnd();
		_m->fogDensity = argScene->getFogDensity();
		_m->fogColor = argScene->getFogColor();
	}

	return;
}

tuple<fk_Vector, fk_Vector> fk_GraphicsEngine::GetViewLinePos(double argX, double argY)
{
	fk_HVector		inVec, outS, outE;
	fk_Matrix		mat;
	double			tmpY;
	double			diffX, diffY;

	mat = *(_m->curProj->GetMatrix()) * _m->curScene->getCamera()->getInhInvMatrix();
	mat.inverse();

	glGetIntegerv(GL_VIEWPORT, _m->viewArray);

	tmpY = double(_m->hSize) - argY - 1.0;
	diffX = argX - double(_m->viewArray[0]);
	diffY = tmpY - double(_m->viewArray[1]);

	inVec.x = diffX*2.0/double(_m->viewArray[2]) - 1.0;
	inVec.y = diffY*2.0/double(_m->viewArray[3]) - 1.0;
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
	if(_m->curScene == nullptr) return {false, fk_Vector()};
	if(generalID > 2) SetViewPort();

	auto [sVec, eVec] = GetViewLinePos(argX, argY);
	return argPlane.calcCrossPos(sVec, eVec);
}

tuple<bool, fk_Vector> fk_GraphicsEngine::GetProjectPosition(double argX, double argY,
															 double argDist)
{
	fk_Vector		eyeVec, cameraPos;
	const fk_Model	*tmpCamera;

	if(_m->curScene == nullptr) return {false, fk_Vector()};
	tmpCamera = _m->curScene->getCamera();
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

	glGetIntegerv(GL_VIEWPORT, _m->viewArray);
	mat = *(_m->curProj->GetMatrix()) * _m->curScene->getCamera()->getInhInvMatrix();
	outVec = mat * inVec;

	if(fabs(outVec.w) < fk_Math::EPS) return {false, retPos};
	outVec /= outVec.w;
	retPos.set(double(_m->viewArray[0]) + double(_m->viewArray[2])*(outVec.x + 1.0)/2.0,
			   double(_m->viewArray[1]) + double(_m->hSize) - 1.0 -
			   double(_m->viewArray[3])*(outVec.y + 1.0)/2.0,
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

	if(src != _m->srcFactor || dst != _m->dstFactor) {
		_m->srcFactor = src;
		_m->dstFactor = dst;
		glBlendFunc(GetBlendFactor(src), GetBlendFactor(dst));
	}
	return;
}

void fk_GraphicsEngine::SetDepthMode(fk_DepthMode argMode)
{
	bool readMode = ((argMode & fk_DepthMode::READ) != fk_DepthMode::NO_USE);
	bool writeMode = ((argMode & fk_DepthMode::WRITE) != fk_DepthMode::NO_USE);

	if (_m->depthRead != readMode) {
		if (readMode == true) {
			glEnable(GL_DEPTH_TEST);
		} else {
			glDisable(GL_DEPTH_TEST);
		}
		_m->depthRead = readMode;
	}
	if (_m->depthWrite != writeMode) {
		if(writeMode == true) {
			glDepthMask(GL_TRUE);
		} else {
			glDepthMask(GL_FALSE);
		}
		_m->depthWrite = writeMode;
	}
}

bool fk_GraphicsEngine::SnapImage(fk_Image *argImage, fk_SnapProcMode argMode)
{
	int		wCount, hCount;
	_st		index;

	if(argImage == nullptr) return false;

	if(argImage->getWidth() != _m->wSize || argImage->getHeight() != _m->hSize) {
		argImage->newImage(_m->wSize, _m->hSize);
	}
	if(static_cast<int>(_m->snapBuffer.size()) != 3 * _m->wSize * _m->hSize) {
		_m->snapBuffer.resize(3 * _st(_m->wSize) * _st(_m->hSize));
	}
	if(argMode == fk_SnapProcMode::FRONT) {
		glReadBuffer(GL_FRONT);
	} else {
		glReadBuffer(GL_BACK);
	}
	glReadPixels(0, 0, _m->wSize, _m->hSize,
				 GL_RGB, GL_UNSIGNED_BYTE,
				 static_cast<GLvoid *>(_m->snapBuffer.data()));

	for(hCount = 0; hCount < _m->hSize; ++hCount) {
		for(wCount = 0; wCount < _m->wSize; ++wCount) {
			index = 3 * _st(hCount) * _st(_m->wSize) + _st(wCount);
			argImage->setRGB(wCount, _m->hSize - hCount - 1,
							 _m->snapBuffer[index],
							 _m->snapBuffer[index+1],
							 _m->snapBuffer[index+2]);
		}
	}

	return true;
}

void fk_GraphicsEngine::SetupFBO(void)
{
	_m->colorBuf = make_unique<fk_FrameBuffer>();
	_m->depthBuf = make_unique<fk_FrameBuffer>();

	int maxUnit;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxUnit);

	_m->colorBuf->setSource(fk_SamplerSource::COLOR);
	_m->depthBuf->setSource(fk_SamplerSource::DEPTH);

	_m->colorBuf->SetBufferSize(_m->wSize, _m->hSize);
	_m->colorBuf->SetupFBO(maxUnit - 2);

	_m->depthBuf->SetBufferSize(_m->wSize, _m->hSize);
	_m->depthBuf->SetupFBO(maxUnit - 3);

	glGenFramebuffers(1, &(_m->fboHandle));
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _m->fboHandle);

#ifdef WIN32	
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, _m->wSize);
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, _m->hSize);
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, 1);
#endif

	_m->colorBuf->AttachFBO();
	_m->depthBuf->AttachFBO();

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	_m->FBOMode = true;
}

void fk_GraphicsEngine::PreFBODraw(void)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _m->fboHandle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);
	glDrawBuffers(sizeof(drawBuffers) / sizeof(drawBuffers[0]), drawBuffers);
	if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		Error::Put("fk_GraphicsEngine", "PreFBODraw", 1, "FBO Error");
	}
}

void fk_GraphicsEngine::PostFBODraw(void)
{
 	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _m->fboHandle);

	if(_m->FBOShader != nullptr) _m->FBOShader->ProcPreShader();
	glDrawBuffer(GL_BACK);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_m->colorBuf->BindFBO();
	_m->depthBuf->BindFBO();

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	if(_m->FBOWindowMode == true) FBOWindowDraw();

	_m->colorBuf->Unbind();
	_m->depthBuf->Unbind();
}

void fk_GraphicsEngine::FBOWindowDraw(void)
{
	glBindVertexArray(_m->rectVAO);
	glDrawArrays(GL_POINTS, 0, 1);

	if(_m->FBOShader != nullptr) _m->FBOShader->ProcPostShader();
}	
	
void fk_GraphicsEngine::BindWindow(fk_ShaderBinder *argShader)
{
	_m->FBOShader = argShader;

	SetupFBO();

	_m->FBOWindowMode = true;

	GLuint handle;
	glGenBuffers(1, &handle);

	static GLfloat verts[3] = {0.0f, 0.0f, 0.0f};

	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), verts, GL_STATIC_DRAW);

	glGenVertexArrays(1, &(_m->rectVAO));
	glBindVertexArray(_m->rectVAO);

	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

fk_FrameBuffer * fk_GraphicsEngine::GetColorBuffer(void)
{
	return _m->colorBuf.get();
}

fk_FrameBuffer * fk_GraphicsEngine::GetDepthBuffer(void)
{
	return _m->depthBuf.get();
}

void fk_GraphicsEngine::InitFrameBufferMode(void)
{
	_m->FBOMode = true;
	_m->FBOWindowMode = false;
	SetupFBO();
}

void fk_GraphicsEngine::ShadowInit(void)
{
	if(_m->shadowBuf != nullptr) {
		//glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		if(_m->shadowHandle != 0) glDeleteFramebuffers(1, &(_m->shadowHandle));
	}
		
	_m->shadowBuf = make_unique<fk_FrameBuffer>();
	int maxUnit;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxUnit);
	_m->shadowBufferID = maxUnit - 4;

	_m->shadowBuf->setSource(fk_SamplerSource::DEPTH);
	_m->shadowBuf->SetBufferSize(_m->shadowResolution, _m->shadowResolution);
	_m->shadowBuf->SetupFBO(_m->shadowBufferID);
	glGenFramebuffers(1, &(_m->shadowHandle));
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _m->shadowHandle);
	
#ifdef WIN32	
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, _m->shadowResolution);
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, _m->shadowResolution);
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, 1);
#endif

	_m->shadowBuf->AttachFBO();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	_m->shadowTexture.setFrameBuffer(_m->shadowBuf.get());
	_m->shadowTexture.setTextureSize(1.0, 1.0);
}

void fk_GraphicsEngine::AttachShadowBuffer(int argID)
{
	_m->shadowTexture.Replace();
	faceDraw->AttachShadowTexture(argID,
								  fk_ShaderBinder::shadowBufName,
								  &(_m->shadowTexture));
	textureDraw->AttachShadowTexture(argID,
									 fk_ShaderBinder::shadowBufName,
									 &(_m->shadowTexture));
	surfaceDraw->AttachShadowTexture(argID,
									 fk_ShaderBinder::shadowBufName,
									 &(_m->shadowTexture));
}

void fk_GraphicsEngine::PreShadowDraw(void)
{
	//glCullFace(GL_FRONT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _m->shadowHandle);
	glDrawBuffers(sizeof(shadowBuffers) / sizeof(shadowBuffers[0]), shadowBuffers);
	if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		Error::Put("fk_GraphicsEngine", "PreShadowDraw", 1, "Shadow Error");
	}
}

void fk_GraphicsEngine::PostShadowDraw(void)
{
 	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _m->shadowHandle);

	glDrawBuffer(GL_BACK);
	//glClear(GL_DEPTH_BUFFER_BIT);

	_m->shadowBuf->BindFBO();

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	_m->shadowBuf->Unbind();

	AttachShadowBuffer(_m->shadowBufferID);
	//glCullFace(GL_BACK);
}

void fk_GraphicsEngine::CopyShadowStatus(void)
{
	if(_m->curScene == nullptr) return;

	SetShadowVec(_m->curScene->getShadowVec());
	SetShadowResolution(_m->curScene->getShadowResolution());
	SetShadowAreaSize(_m->curScene->getShadowAreaSize());
	SetShadowDistance(_m->curScene->getShadowDistance());
	SetShadowVisibility(_m->curScene->getShadowVisibility());
	SetShadowBias(_m->curScene->getShadowBias());
}

void fk_GraphicsEngine::DrawShadow(void)
{
	fk_Model *camera;
	fk_Vector cameraPos, cameraVec, shadowPos;

	CopyShadowStatus();

	if(_m->curScene != nullptr) {
		camera = _m->curScene->getCamera();
		if(camera != nullptr) {
			cameraPos = camera->getInhPosition();
			cameraVec = camera->getInhVec();
		}
	}

	shadowPos = cameraPos + cameraVec * _m->shadowSize/4.0;
	_m->shadowCamera.glMoveTo(shadowPos);
	//shadowCamera.glVec(shadowVec);

	PreShadowDraw();

	glViewport(0, 0, _m->shadowResolution, _m->shadowResolution);
	_m->shadowProj.MakeMat();
	fk_DrawBase::SetProjectionMatrix(_m->shadowProj.GetMatrix());
	fk_DrawBase::SetShadowProjMatrix(_m->shadowProj.GetMatrix());
	fk_DrawBase::SetCamera(&(_m->shadowCamera));
	fk_DrawBase::SetShadowCamera(&(_m->shadowCamera));
	fk_DrawBase::SetShadowParam(_m->shadowVisibility, _m->shadowBias);
	fk_DrawBase::SetFogStatus(_m->fogMode, _m->fogStart, _m->fogEnd,
							  _m->fogDensity, _m->fogColor);

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if(_m->curScene != nullptr) {
		for(auto modelP : *(_m->curScene->GetModelList())) DrawModel(modelP);
	}

	PostShadowDraw();
}

fk_RectTexture * fk_GraphicsEngine::GetShadowTexture(void)
{
	return &(_m->shadowTexture);
}

void fk_GraphicsEngine::SetShadowTextureSize(int argW, int argH)
{
	_m->shadowTexture.setTextureSize(argW, argH);
}

int fk_GraphicsEngine::ShadowFixVal(int argVal)
{
	int x;
	for(x = 16; 2 * x <= argVal; x *= 2);
	return x;
}

void fk_GraphicsEngine::SetShadowVec(fk_Vector argV)
{
	_m->shadowVec = argV;
	_m->shadowCamera.glVec(_m->shadowVec);
}

void fk_GraphicsEngine::SetShadowResolution(int argVal)
{
	int newRes = ShadowFixVal(argVal);
	if(_m->shadowResolution != newRes) {
		_m->shadowResolution = newRes;
		if(_m->shadowInitFlag == true) ShadowInit();
	}
}

void fk_GraphicsEngine::SetShadowAreaSize(double argSize)
{
	_m->shadowSize = argSize;
	_m->shadowProj.setAll(-argSize/2.0, argSize/2.0,
						  -argSize/2.0, argSize/2.0,
						  -_m->shadowDistance/2.0, _m->shadowDistance/2.0);
}

void fk_GraphicsEngine::SetShadowDistance(double argDist)
{
	_m->shadowDistance = argDist;
	_m->shadowProj.setNear(-_m->shadowDistance/2.0);
	_m->shadowProj.setFar(_m->shadowDistance/2.0);
}

void fk_GraphicsEngine::SetShadowVisibility(double argVis)
{
	_m->shadowVisibility = argVis;
}

void fk_GraphicsEngine::SetShadowBias(double argBias)
{
	_m->shadowBias = argBias;
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
