﻿/****************************************************************************
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
#include <FK/FaceDraw.H>
#include <FK/OpenGL.H>
#include <FK/IndexFace.h>
#include <FK/Solid.h>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Loop.h>
#include <FK/Surface.h>

using namespace std;
using namespace FK;

typedef list<fk_Loop *>::iterator			loopIte;
typedef list<fk_Loop *>::reverse_iterator	loopRIte;

fk_FaceDraw::fk_FaceDraw(void)
	: shader(nullptr)
{
	return;
}

fk_FaceDraw::~fk_FaceDraw()
{
	delete shader;
	return;
}

void fk_FaceDraw::DrawShapeFace(fk_Model *argModel)
{
	fk_RealShapeType	shapeType = argModel->getShape()->getRealShapeType();
	fk_DrawMode			drawMode = argModel->getDrawMode();

	if(shader == nullptr) ShaderSetup();
	PolygonModeSet(drawMode);

	auto parameter = shader->getParameter();
	SetParameter(parameter);

	if((drawMode & FK_SHADERMODE) == FK_NONEMODE) shader->ProcPreShader();

	switch(shapeType) {
	  case FK_SHAPE_IFS:
		Draw_IFS(argModel, parameter);
		break;

	  default:
		break;
	}

	if((drawMode & FK_SHADERMODE) == FK_NONEMODE) shader->ProcPostShader();
	return;
}

void fk_FaceDraw::PolygonModeSet(fk_DrawMode argDMode)
{
	if((argDMode & FK_FRONTBACK_POLYMODE) == FK_FRONTBACK_POLYMODE) {
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} else if((argDMode & FK_BACK_POLYMODE) == FK_BACK_POLYMODE) {
		glCullFace(GL_FRONT);
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_BACK, GL_FILL);
	} else {
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}

void fk_FaceDraw::ShaderSetup(void)
{
	shader = new fk_ShaderBinder();
	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Face_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Face_FS.out"
		;
	
	if(prog->validate() == false) {
		fk_Window::printf("Shader Error");
		fk_Window::putString(prog->getLastError());
	}

	param->reserveAttribute(fk_Shape::vertexName);
	param->reserveAttribute(fk_Shape::normalName);
	glBindFragDataLocation(prog->getProgramID(), 0, fragmentName.c_str());

	prog->link();
	return;
}

GLuint fk_FaceDraw::VAOSetup(fk_Shape *argShape)
{
	GLuint 			vao;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	argShape->SetFaceVAO(vao);
	argShape->DefineVBO();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return vao;
}

void fk_FaceDraw::Draw_IFS(fk_Model *argModel, fk_ShaderParameter *argParam)
{
	fk_IndexFaceSet *ifs = dynamic_cast<fk_IndexFaceSet *>(argModel->getShape());
	GLuint			vao = ifs->GetFaceVAO();

	if(vao == 0) {
		vao = VAOSetup(ifs);
	}
	glBindVertexArray(vao);
	ifs->BindShaderBuffer(argParam->getAttrTable());
	ifs->FaceIBOSetup();
	glDrawElements(GL_TRIANGLES, GLint(ifs->getFaceSize()*3), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return;
}
/*
void fk_FaceDraw::DrawShapeFaceMaterial(fk_Model *argObj, bool argLightFlag)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSFaceMaterial(argObj, argLightFlag);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidFaceMaterial(argObj, argLightFlag);
		break;

	  case FK_SHAPE_SURFACE:
		DrawSurfaceFaceNormal(argObj, argLightFlag, true);

	  default:
		break;
	}
	return;
}

void fk_FaceDraw::DrawSolidFaceMaterial(fk_Model *argObj, bool lightFlag)
{
	fk_Solid				*solidP;
	int						oldMateID, paletteSize;
	vector<fk_Material>		*matV;
	list<fk_Loop *>			*loopStack;
	bool					reverseFlag = argObj->getReverseDrawMode();
	loopIte					ite;
	loopRIte				rite;


	solidP = static_cast<fk_Solid *>(argObj->getShape());
	if(solidP->checkDB() == false) return;
	if(solidP->getNextL(nullptr) == nullptr) return;

	if(solidP->GetLCacheStatus() == false) {
		solidP->MakeLCache();
	}

	loopStack = solidP->GetLCache();

	oldMateID = -2;

#ifndef OPENGL4
	glShadeModel(GL_FLAT);
#endif

	paletteSize = solidP->getPaletteSize();
	matV = solidP->getMaterialVector();

	if(reverseFlag == false) {
		for(ite = loopStack->begin(); ite != loopStack->end(); ++ite) {
			oldMateID = DrawSolidFaceMaterialElem(argObj, *ite, oldMateID,
												  paletteSize, matV, lightFlag);
		}
	} else {
		for(rite = loopStack->rbegin(); rite != loopStack->rend(); ++rite) {
			oldMateID = DrawSolidFaceMaterialElem(argObj, *rite, oldMateID,
												  paletteSize, matV, lightFlag);
		}
	}

	return;
}

int fk_FaceDraw::DrawSolidFaceMaterialElem(fk_Model *argObj, fk_Loop *argL,
										   int argOldMateID,
										   int argPaletteSize,
										   vector<fk_Material> *argMatV,
										   bool argLightFlag)
{
	fk_Half					*startH, *curH;
	fk_Vertex				*curV;
	fk_Vector				*tmpPosP, *tmpNormP;
	int						retMateID, curMateID;
	fk_Surface				*surf;
	_st						i;
	vector<fk_Vertex *>		*tesseVertexArray;
	vector<int>				*tesseIDArray;


	FK_UNUSED(tmpPosP);
	FK_UNUSED(i);
	FK_UNUSED(curV);
	
	retMateID = argOldMateID;

	switch(argL->getElemMaterialMode()) {
	  case FK_CHILD_MODE:
		curMateID = argL->getElemMaterialID();
		if(curMateID < 0 || curMateID >= argPaletteSize) {
			curMateID = FK_UNDEFINED;
		}
		break;
	  case FK_NONE_MODE:
		return argOldMateID;
	  default:
		curMateID = FK_UNDEFINED;
		break;
	}

	if(curMateID != argOldMateID) {
		if(curMateID == FK_UNDEFINED) {
			CommonMateSet(argObj, argLightFlag, true);
			retMateID = FK_UNDEFINED;
		} else {
			LocalMateSet(&((*argMatV)[_st(curMateID)]), argLightFlag);
			retMateID = curMateID;
		}
	}

	if((surf = argL->getSurfGeometry()) != nullptr) {
		DrawSurfaceNormalElem(surf);
	} else if(argL->isTesselated() == true) {
		if((tmpNormP = argL->getNormal()) == nullptr) {
			return retMateID;
		}

		tesseVertexArray = argL->GetTesselateVertex();
		tesseIDArray = argL->GetTesselateIndex();

#ifndef OPENGL4
		glBegin(GL_TRIANGLES);
		glNormal3dv(static_cast<GLdouble *>(&(tmpNormP->x)));
		for(i = 0; i < tesseIDArray->size(); i++) {
			_st index = static_cast<_st>(tesseIDArray->at(i));
			tmpPosP = tesseVertexArray->at(index)->GetPositionP();
			glVertex3dv(static_cast<GLdouble *>(&(tmpPosP->x)));
		}
		glEnd();
#endif

	} else {
		if((tmpNormP = argL->getNormal()) == nullptr) {
			return retMateID;
		}
		startH = curH = argL->getOneHalf();

#ifndef OPENGL4		
		glBegin(GL_POLYGON);
		glNormal3dv(static_cast<GLdouble *>(&(tmpNormP->x)));
		do {
			curV = curH->getVertex();
			tmpPosP = curV->GetPositionP(); 
			glVertex3dv(static_cast<GLdouble *>(&(tmpPosP->x)));
			curH = curH->getNextHalf();
		} while(startH != curH);
		glEnd();
#endif
	}

	return retMateID;
}


void fk_FaceDraw::DrawIFSFaceMaterial(fk_Model *argObj, bool argLightFlag)
{
	fk_IndexFaceSet		*ifsP;
	_st					pNum;
	fk_FVector			*pos, *pNorm;
	int					*ifs;
	_st					ii, ij;
	GLenum				tmpType;
	int					oldMateID, curMateID, paletteSize;
	vector<fk_Material>	*matV;

	FK_UNUSED(ij);
	
	ifsP = static_cast<fk_IndexFaceSet *>(argObj->getShape());

	curMateID = FK_UNDEFINED;
	oldMateID = -2;

#ifndef OPENGL4
	glShadeModel(GL_FLAT);
#endif

	ifsP->ModifyPNorm();
	switch(ifsP->type) {
	  case FK_IF_TRIANGLES:
		pNum = 3;
		tmpType = GL_TRIANGLES;
		break;

	  case FK_IF_QUADS:
		pNum = 4;
		tmpType = GL_QUADS;
		break;

	  default:
		return;
	}

	pos = &ifsP->pos[0];
	pNorm = &ifsP->pNorm[0];
	ifs = &ifsP->ifs[0];

	paletteSize = ifsP->getPaletteSize();
	matV = ifsP->getMaterialVector();

#ifndef OPENGL4
	glBegin(tmpType);
#endif

	if(ifsP->colorFlg == false) CommonMateSet(argObj, argLightFlag, true);

	for(ii = 0; ii < static_cast<_st>(ifsP->faceSize); ii++) {
		if(ifsP->colorFlg == true) {
			curMateID = ifsP->colorID[ii];
			if(curMateID < 0 || curMateID >= paletteSize) {
				curMateID = FK_UNDEFINED;
			}
			if(curMateID != oldMateID) {
				if(curMateID == FK_UNDEFINED) {
					CommonMateSet(argObj, argLightFlag, true);
					oldMateID = FK_UNDEFINED;
				} else {
					LocalMateSet(&((*matV)[_st(curMateID)]),
								 argLightFlag);
					oldMateID = curMateID;
				}
			}
		}

#ifndef OPENGL4
		glNormal3fv(static_cast<GLfloat *>(&(pNorm[ii].x)));

		for(ij = 0; ij < pNum; ij++) {
			glVertex3fv(static_cast<GLfloat *>(&pos[ifs[pNum*ii+ij]].x));
		}
#endif
	}

#ifndef OPENGL4
	glEnd();
#endif

	return;
}

void fk_FaceDraw::DrawShapeFaceSmooth(fk_Model *argObj,
									  bool argLightFlag, bool argNodeFlag)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSFaceSmooth(argObj, argLightFlag, argNodeFlag);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidFaceSmooth(argObj, argLightFlag, argNodeFlag);
		break;

	  case FK_SHAPE_SURFACE:
		DrawSurfaceFaceSmooth(argObj, argLightFlag, argNodeFlag);
		break;
		
	  default:
		break;
	}
	return;
}

void fk_FaceDraw::DrawSolidFaceSmooth(fk_Model *argObj,
									bool argLightFlag, bool argNodeFlg)
{
	fk_Solid			*solidP;
	list<fk_Loop *>		*loopStack;
	bool				reverseFlag = argObj->getReverseDrawMode();
	loopIte				ite;
	loopRIte			rite;


	solidP = static_cast<fk_Solid *>(argObj->getShape());
	if(solidP->checkDB() == false) return;
	if(solidP->getNextL(nullptr) == nullptr) return;

	if(solidP->GetLCacheStatus() == false) {
		solidP->MakeLCache();
	}

	loopStack = solidP->GetLCache();

	CommonMateSet(argObj, argLightFlag, argNodeFlg);

#ifndef OPENGL4
	glShadeModel(GL_SMOOTH);
#endif
	
	if(reverseFlag == false) {
		for(ite = loopStack->begin(); ite != loopStack->end(); ++ite) {
			DrawSolidFaceSmoothElem(*ite);
		}
	} else {
		for(rite = loopStack->rbegin(); rite != loopStack->rend(); ++rite) {
			DrawSolidFaceSmoothElem(*rite);
		}
	}

	return;
}

void fk_FaceDraw::DrawSolidFaceSmoothElem(fk_Loop *argL)
{
	fk_Half				*startH, *curH;
	fk_Vertex			*curV;
	fk_Vector			*tmpPos, *tmpNorm;
	fk_Surface			*surf;


	if((surf = argL->getSurfGeometry()) != nullptr) {
		DrawSurfaceSmoothElem(surf);
	} else {
#ifndef OPENGL4		
		glBegin(GL_POLYGON);
#endif
		startH = curH = argL->getOneHalf();

		do {
			curV = curH->getVertex();
			tmpNorm = curV->GetNormalP();
			tmpPos = curV->GetPositionP(); 
			if(tmpNorm == nullptr || tmpPos == nullptr) continue;
#ifndef OPENGL4			
			glNormal3dv(static_cast<GLdouble *>(&(tmpNorm->x)));
			glVertex3dv(static_cast<GLdouble *>(&(tmpPos->x)));
#endif
			curH = curH->getNextHalf();
		} while(startH != curH);

#ifndef OPENGL4
		glEnd();
#endif
	}

	return;
}

void fk_FaceDraw::DrawIFSFaceSmooth(fk_Model *argObj,
								  bool argLightFlag, bool argNodeFlag)
{
	fk_IndexFaceSet		*ifsP;
	int					pNum;
	fk_FVector			*pos, *vNorm;
	int					*ifs;
	GLenum				tmpType;

	ifsP = (fk_IndexFaceSet *)argObj->getShape();

	CommonMateSet(argObj, argLightFlag, argNodeFlag);
#ifndef OPENGL4	
	glShadeModel(GL_SMOOTH);
#endif
	
	ifsP->ModifyVNorm();
	switch(ifsP->type) {
	  case FK_IF_TRIANGLES:
		pNum = 3;
		tmpType = GL_TRIANGLES;
		break;

	  case FK_IF_QUADS:
		pNum = 4;
		tmpType = GL_QUADS;
		break;

	  default:
		return;
	}

	pos = &ifsP->pos[0];
	vNorm = &ifsP->vNorm[0];
	ifs = &ifsP->ifs[0];

	if(arrayState == true) {
#ifndef OPENGL4
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, pos);
		glNormalPointer(GL_FLOAT, 0, vNorm);
		glDrawElements(tmpType, ifsP->faceSize * pNum,
					   GL_UNSIGNED_INT, &ifs[0]);
#endif
	} else {
#ifndef OPENGL4
		glBegin(tmpType);
		for(int ii = 0; ii < ifsP->faceSize; ii++) {
			for(int ij = 0; ij < pNum; ij++) {
				int index = ifs[pNum*ii+ij];
				glNormal3fv(static_cast<GLfloat *>(&vNorm[index].x));
				glVertex3fv(static_cast<GLfloat *>(&pos[index].x));
			}
		}
		glEnd();
#endif
	}
	return;
}

void fk_FaceDraw::DrawSurfaceFaceSmooth(fk_Model *argObj,
										bool argLightFlag, bool argNodeFlag)

{
	CommonMateSet(argObj, argLightFlag, argNodeFlag);
#ifndef OPENGL4
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glShadeModel(GL_SMOOTH);
#endif
	DrawSurfaceSmoothElem(static_cast<fk_Surface *>(argObj->getShape()));
}


void fk_FaceDraw::DrawShapeFaceNormal(fk_Model *argObj,
									  bool argLightFlag, bool argNodeFlag)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSFaceNormal(argObj, argLightFlag, argNodeFlag);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidFaceNormal(argObj, argLightFlag, argNodeFlag);
		break;

	  case FK_SHAPE_SURFACE:
		DrawSurfaceFaceNormal(argObj, argLightFlag, argNodeFlag);
		break;

	  default:
		break;
	}
	return;
}

void fk_FaceDraw::DrawSolidFaceNormal(fk_Model *argObj,
									  bool argLightFlag, bool argNodeFlg)
{
	fk_Solid			*solidP;
	list<fk_Loop *>		*loopStack;
	bool				reverseFlag = argObj->getReverseDrawMode();
	loopIte				ite;
	loopRIte			rite;


	solidP = static_cast<fk_Solid *>(argObj->getShape());
	if(solidP->checkDB() == false) return;
	if(solidP->getNextL(nullptr) == nullptr) return;

	if(solidP->GetLCacheStatus() == false) {
		solidP->MakeLCache();
	}

	loopStack = solidP->GetLCache();

	CommonMateSet(argObj, argLightFlag, argNodeFlg);

#ifndef OPENGL4
	glShadeModel(GL_FLAT);
#endif

	if(reverseFlag == false) {
		for(ite = loopStack->begin(); ite != loopStack->end(); ++ite) {
			DrawSolidFaceNormalElem(*ite);
		}
	} else {
		for(rite = loopStack->rbegin(); rite != loopStack->rend(); ++rite) {
			DrawSolidFaceNormalElem(*rite);
		}
	}

	return;
}

void fk_FaceDraw::DrawSolidFaceNormalElem(fk_Loop *argL)
{
	fk_Half				*startH, *curH;
	fk_Vertex			*curV;
	fk_Vector			*tmpPosP, *tmpNormP;
	vector<fk_Vertex *>	*tesseVertexArray;
	vector<int>			*tesseIDArray;
	fk_Surface			*surf;


	FK_UNUSED(curV);
	FK_UNUSED(tmpPosP);

	if((surf = argL->getSurfGeometry()) != nullptr) {
		DrawSurfaceNormalElem(surf);
	} else if(argL->isTesselated() == true) {
		if((tmpNormP = argL->getNormal()) == nullptr) return;
		tesseVertexArray = argL->GetTesselateVertex();
		tesseIDArray = argL->GetTesselateIndex();
#ifndef OPENGL4
		glBegin(GL_TRIANGLES);
		glNormal3dv(static_cast<GLdouble *>(&(tmpNormP->x)));
		for(_st i = 0; i < tesseIDArray->size(); i++) {
			_st index = static_cast<_st>(tesseIDArray->at(i));
			tmpPosP = tesseVertexArray->at(index)->GetPositionP();
			glVertex3dv(static_cast<GLdouble *>(&(tmpPosP->x)));
		}
		glEnd();
#endif

	} else {
		if((tmpNormP = argL->getNormal()) == nullptr) return;
		startH = curH = argL->getOneHalf();
#ifndef OPENGL4
		glBegin(GL_POLYGON);
		glNormal3dv(static_cast<GLdouble *>(&(tmpNormP->x)));

		do {
			curV = curH->getVertex();
			tmpPosP = curV->GetPositionP(); 
			glVertex3dv(static_cast<GLdouble *>(&(tmpPosP->x)));
			curH = curH->getNextHalf();
		} while(startH != curH);

		glEnd();
#endif
	}
	return;
}

void fk_FaceDraw::DrawIFSFaceNormal(fk_Model *argObj,
									bool argLightFlag, bool argNodeFlag)
{
	fk_IndexFaceSet		*ifsP;
	int					pNum;
	fk_FVector			*pos, *pNorm;
	int					*ifs;
	int					ii, ij;
	GLenum				tmpType;

	FK_UNUSED(ii);
	FK_UNUSED(ij);
	
	ifsP = static_cast<fk_IndexFaceSet *>(argObj->getShape());

	CommonMateSet(argObj, argLightFlag, argNodeFlag);

#ifndef OPENGL4	
	glShadeModel(GL_FLAT);
#endif

	ifsP->ModifyPNorm();
	switch(ifsP->type) {
	  case FK_IF_TRIANGLES:
		pNum = 3;
		tmpType = GL_TRIANGLES;
		break;

	  case FK_IF_QUADS:
		pNum = 4;
		tmpType = GL_QUADS;
		break;

	  default:
		return;
	}

	pos = &ifsP->pos[0];
	pNorm = &ifsP->pNorm[0];
	ifs = &ifsP->ifs[0];

#ifndef OPENGL4	
	glBegin(tmpType);
	for(ii = 0; ii < ifsP->faceSize; ii++) {
		glNormal3fv(static_cast<GLfloat *>(&(pNorm[ii].x)));
		for(ij = 0; ij < pNum; ij++) {
			glVertex3fv(static_cast<GLfloat *>(&pos[ifs[pNum*ii+ij]].x));
		}
	}
	glEnd();
#endif
	
	return;
}

void fk_FaceDraw::DrawSurfaceFaceNormal(fk_Model *argObj,
										bool argLightFlag, bool argNodeFlag)
{
	CommonMateSet(argObj, argLightFlag, argNodeFlag);
#ifndef OPENGL4	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glShadeModel(GL_FLAT);
#endif
	DrawSurfaceNormalElem(static_cast<fk_Surface *>(argObj->getShape()));
	return;
}

void fk_FaceDraw::DrawSurfaceNormalElem(fk_Surface *argSurf)
{
	_st div = static_cast<_st>(argSurf->getDiv());
	argSurf->makeCache();
	auto pArray = argSurf->getPosCache();
	auto nArray = argSurf->getNormCache();

	FK_UNUSED(div);
	FK_UNUSED(pArray);
	FK_UNUSED(nArray);

#ifndef OPENGL4
	glBegin(GL_TRIANGLES);
	for(_st i = 0; i < div; ++i) {
		for(_st j = 0; j < div; ++j) {
			_st i1 = i*(div+1) + j;
			_st i2 = (i+1)*(div+1) + j;

			auto p11 = &((*pArray)[i1]);
			auto p12 = &((*pArray)[i1+1]);
			auto p21 = &((*pArray)[i2]);
			auto p22 = &((*pArray)[i2+1]);

			auto n11 = &((*nArray)[i1]);

			glNormal3dv(static_cast<GLdouble *>(&(n11->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p11->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p12->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p21->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p21->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p12->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p22->x)));
		}
	}
	glEnd();
#endif

	return;
}
	
void fk_FaceDraw::DrawSurfaceSmoothElem(fk_Surface *argSurf)
{
	_st div = static_cast<_st>(argSurf->getDiv());
	argSurf->makeCache();
	auto pArray = argSurf->getPosCache();
	auto nArray = argSurf->getNormCache();


	FK_UNUSED(div);
	FK_UNUSED(pArray);
	FK_UNUSED(nArray);

#ifndef OPENGL4
	glBegin(GL_TRIANGLES);
	for(_st i = 0; i < div; ++i) {
		for(_st j = 0; j < div; ++j) {
			_st i1 = i*(div+1) + j;
			_st i2 = (i+1)*(div+1) + j;

			auto p11 = &((*pArray)[i1]);
			auto p12 = &((*pArray)[i1+1]);
			auto p21 = &((*pArray)[i2]);
			auto p22 = &((*pArray)[i2+1]);

			auto n11 = &((*nArray)[i1]);
			auto n12 = &((*nArray)[i1+1]);
			auto n21 = &((*nArray)[i2]);
			auto n22 = &((*nArray)[i2+1]);
			
			glNormal3dv(static_cast<GLdouble *>(&(n11->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p11->x)));

			glNormal3dv(static_cast<GLdouble *>(&(n12->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p12->x)));

			glNormal3dv(static_cast<GLdouble *>(&(n21->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p21->x)));


			glNormal3dv(static_cast<GLdouble *>(&(n21->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p21->x)));

			glNormal3dv(static_cast<GLdouble *>(&(n12->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p12->x)));

			glNormal3dv(static_cast<GLdouble *>(&(n22->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p22->x)));
		}
	}
	glEnd();
#endif	

	return;
}

void fk_FaceDraw::CommonMateSet(fk_Model *argObj, bool lightFlag, bool matFlag)
{
	float 		tmpShininess;
	fk_Shape	*shapeP;
	fk_Material	*curMat;
	
	
	FK_UNUSED(lightFlag);
	FK_UNUSED(tmpShininess);

	shapeP = argObj->getShape();

	if(matFlag == true || shapeP == nullptr) {
		//curMat = argObj->getInhMaterial();
	} else {
		curMat = &(*shapeP->getMaterialVector())[0];
	}
								  
#ifndef OPENGL4
	if(lightFlag == true) {
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT,
					 &curMat->getAmbient()->col[0]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,
					 &curMat->getDiffuse()->col[0]);
		glMaterialfv(GL_FRONT, GL_SPECULAR,
					 &curMat->getSpecular()->col[0]);
		glMaterialfv(GL_FRONT, GL_EMISSION,
					 &curMat->getEmission()->col[0]);
		tmpShininess = curMat->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &tmpShininess);
	} else {
		glDisable(GL_LIGHTING);
		glColor4fv(&curMat->getAmbient()->col[0]);
	}
#endif
	return;
}

void fk_FaceDraw::LocalMateSet(fk_Material *argMaterial, bool lightFlag)
{
	FK_UNUSED(argMaterial);
	FK_UNUSED(lightFlag);

#ifndef OPENGL4		
	float tmpShininess;
	if(lightFlag == true) {
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT,
					 &argMaterial->getAmbient()->col[0]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,
					 &argMaterial->getDiffuse()->col[0]);
		glMaterialfv(GL_FRONT, GL_SPECULAR,
					 &argMaterial->getSpecular()->col[0]);
		glMaterialfv(GL_FRONT, GL_EMISSION,
					 &argMaterial->getEmission()->col[0]);
		tmpShininess = argMaterial->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &tmpShininess);
	} else {
		glDisable(GL_LIGHTING);
		glColor4fv(&argMaterial->getAmbient()->col[0]);
	}
#endif

	return;
}

#endif
*/
/*
void fk_FaceDraw::DrawShapeFacePick(fk_Model *argObj)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSFacePick(argObj);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidFacePick(argObj);
		break;

	  case FK_SHAPE_SURFACE:
		DrawSurfaceFacePick(argObj);
		break;

	  default:
		break;
	}
	return;
}

void fk_FaceDraw::DrawSolidFacePick(fk_Model *argObj)
{
	fk_Solid			*solidP;
	list<fk_Loop *>		*loopStack;
	bool				reverseFlag = argObj->getReverseDrawMode();
	loopIte				ite;
	loopRIte			rite;

	solidP = static_cast<fk_Solid *>(argObj->getShape());
	if(solidP->checkDB() == false) return;
	if(solidP->getNextL(nullptr) == nullptr) return;

	if(solidP->GetLCacheStatus() == false) {
		solidP->MakeLCache();
	}

	loopStack = solidP->GetLCache();

#ifndef OPENGL4
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
	
	if(reverseFlag == false) {
		for(ite = loopStack->begin(); ite != loopStack->end(); ++ite) {
			DrawSolidFacePickElem(*ite);
		}
	} else {
		for(rite = loopStack->rbegin(); rite != loopStack->rend(); ++rite) {
			DrawSolidFacePickElem(*rite);
		}
	}

	return;
}

void fk_FaceDraw::DrawSolidFacePickElem(fk_Loop *argL)
{
	FK_UNUSED(argL);

#ifndef OPENGL4	
	vector<fk_Vertex *>	*tesseVertexArray;
	vector<int>			*tesseIDArray;
	fk_Vertex			*curV;
	fk_Half				*startH, *curH;
	fk_Vector			*tmpPosP;

	glPushName(static_cast<GLuint>(argL->getID()*3));

	if(argL->isTesselated() == true) {
		tesseVertexArray = argL->GetTesselateVertex();
		tesseIDArray = argL->GetTesselateIndex();

		glBegin(GL_TRIANGLES);
		for(_st i = 0; i < tesseIDArray->size(); i++) {
			_st index = static_cast<_st>(tesseIDArray->at(i));
			tmpPosP = tesseVertexArray->at(index)->GetPositionP();
			glVertex3dv(static_cast<GLdouble *>(&(tmpPosP->x)));
		}
		glEnd();
	} else {
		glBegin(GL_POLYGON);
		startH = curH = argL->getOneHalf();
		do {
			curV = curH->getVertex();
			tmpPosP = curV->GetPositionP(); 
			glVertex3dv(static_cast<GLdouble *>(&(tmpPosP->x)));
			curH = curH->getNextHalf();
		} while(startH != curH);

		glEnd();
	}

	glPopName();
#endif
}

void fk_FaceDraw::DrawIFSFacePick(fk_Model *argObj)
{
	FK_UNUSED(argObj);

#ifndef OPENGL4
	fk_IndexFaceSet		*ifsP;
	_st					ii, ij;
	_st					pNum;
	fk_FVector			*pos;
	int					*ifs;

	ifsP = static_cast<fk_IndexFaceSet *>(argObj->getShape());

	switch(ifsP->type) {
	  case FK_IF_TRIANGLES:
		pNum = 3;
		break;

	  case FK_IF_QUADS:
		pNum = 4;
		break;

	  default:
		return;
	}

	pos = &ifsP->pos[0];
	ifs = &ifsP->ifs[0];

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	for(ii = 0; ii < _st(ifsP->faceSize); ii++) {
		glPushName(static_cast<GLuint>(ii*3));
		glBegin(GL_POLYGON);
		for(ij = 0; ij < pNum; ij++) {
			glVertex3fv(static_cast<GLfloat *>(&(pos[ifs[pNum*ii+ij]].x)));
		}
		glEnd();
		glPopName();
	}

#endif
	return;
}

void fk_FaceDraw::DrawSurfaceFacePick(fk_Model *argObj)
{
	FK_UNUSED(argObj);

#ifndef OPENGL4	
	fk_Surface *surf = static_cast<fk_Surface *>(argObj->getShape());
	_st div = static_cast<_st>(surf->getDiv());

	surf->makeCache();
	auto pArray = surf->getPosCache();
	GLuint count = 0;

	for(_st i = 0; i < div; ++i) {
		for(_st j = 0; j < div; ++j) {
			_st i1 = i*(div+1) + j;
			_st i2 = (i+1)*(div+1) + j;

			auto p11 = &((*pArray)[i1]);
			auto p12 = &((*pArray)[i1+1]);
			auto p21 = &((*pArray)[i2]);
			auto p22 = &((*pArray)[i2+1]);

			glPushName(count*3);
			glBegin(GL_TRIANGLES);
			glVertex3dv(static_cast<GLdouble *>(&(p11->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p12->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p21->x)));
			glEnd();
			glPopName();
			++count;
			
			glPushName(count*3);
			glBegin(GL_TRIANGLES);
			glVertex3dv(static_cast<GLdouble *>(&(p21->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p12->x)));
			glVertex3dv(static_cast<GLdouble *>(&(p22->x)));
			glEnd();
			glPopName();
			++count;
		}
	}
#endif
	return;
}
*/
