/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
#include "FaceDraw_D3D.cxx"
#else

#define FK_DEF_SIZETYPE
#include <FK/FaceDraw.H>
#include <FK/OpenGL.H>
#include <FK/IndexFace.h>
#include <FK/Solid.h>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Loop.h>

using namespace std;

typedef list<fk_Loop *>::iterator			loopIte;
typedef list<fk_Loop *>::reverse_iterator	loopRIte;

fk_FaceDraw::fk_FaceDraw(void)
{
	SetArrayState(false);
}

fk_FaceDraw::~fk_FaceDraw()
{
	return;
}

void fk_FaceDraw::SetArrayState(bool argState)
{
	arrayState = argState;
	return;
}

void fk_FaceDraw::DrawShapeFace(fk_Model *argObj, bool lightFlag,
								fk_DrawMode argDMode, bool argPickFlag)
{
	fk_MaterialMode	shapeMateMode;
	fk_MaterialMode	modelMateMode;
	bool			smoothMode;

	shapeMateMode = argObj->getShape()->getMaterialMode();
	modelMateMode = argObj->getMaterialMode();
	smoothMode = argObj->getSmoothMode();

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

	if(argPickFlag == true) {
		// ピックモードが ON の場合
		DrawShapeFacePick(argObj);

	} else if(shapeMateMode == FK_PARENT_MODE &&
			  modelMateMode == FK_PARENT_MODE) {
		// マテリアルが個別に設定してある場合
		DrawShapeFaceMaterial(argObj, lightFlag);

	} else {
		bool drawMode = false;
		bool nodeMode = false;
		if(modelMateMode == FK_CHILD_MODE) {
			drawMode = true;
			nodeMode = true;
		} else if(modelMateMode == FK_PARENT_MODE &&
				  shapeMateMode == FK_CHILD_MODE) {
			drawMode = true;
			nodeMode = false;
		}

		if(drawMode == true) {
			if(smoothMode == true) {
				// マテリアルがモデル別で、スムースシェーディングが ON の場合
				DrawShapeFaceSmooth(argObj, lightFlag, nodeMode);
			} else {
				// マテリアルがモデル別で、フラットシェーディングの場合
				DrawShapeFaceNormal(argObj, lightFlag, nodeMode);
			}
		}
	}

	return;
}

void fk_FaceDraw::DrawShapeFacePick(fk_Model *argObj)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSFacePick(argObj);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidFacePick(argObj);
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

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

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

}

void fk_FaceDraw::DrawIFSFacePick(fk_Model *argObj)
{
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

	return;
}

void fk_FaceDraw::DrawShapeFaceMaterial(fk_Model *argObj, bool argLightFlag)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSFaceMaterial(argObj, argLightFlag);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidFaceMaterial(argObj, argLightFlag);
		break;

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
	glShadeModel(GL_FLAT);

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
		DrawSurface(surf);
	} else if(argL->isTesselated() == true) {
		if((tmpNormP = argL->getNormal()) == nullptr) {
			return retMateID;
		}

		tesseVertexArray = argL->GetTesselateVertex();
		tesseIDArray = argL->GetTesselateIndex();

		glBegin(GL_TRIANGLES);
		glNormal3dv(static_cast<GLdouble *>(&(tmpNormP->x)));
		for(i = 0; i < tesseIDArray->size(); i++) {
			_st index = static_cast<_st>(tesseIDArray->at(i));
			tmpPosP = tesseVertexArray->at(index)->GetPositionP();
			glVertex3dv(static_cast<GLdouble *>(&(tmpPosP->x)));
		}
		glEnd();
	} else {
		if((tmpNormP = argL->getNormal()) == nullptr) {
			return retMateID;
		}
		startH = curH = argL->getOneHalf();
		glBegin(GL_POLYGON);
		glNormal3dv(static_cast<GLdouble *>(&(tmpNormP->x)));
		do {
			curV = curH->getVertex();
			tmpPosP = curV->GetPositionP(); 
			glVertex3dv(static_cast<GLdouble *>(&(tmpPosP->x)));
			curH = curH->getNextHalf();
		} while(startH != curH);
		glEnd();
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

	ifsP = static_cast<fk_IndexFaceSet *>(argObj->getShape());

	curMateID = FK_UNDEFINED;
	oldMateID = -2;

	glShadeModel(GL_FLAT);
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

	glBegin(tmpType);

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

		glNormal3fv(static_cast<GLfloat *>(&(pNorm[ii].x)));

		for(ij = 0; ij < pNum; ij++) {
			glVertex3fv(static_cast<GLfloat *>(&pos[ifs[pNum*ii+ij]].x));
		}
	}
	glEnd();

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

	glShadeModel(GL_SMOOTH);

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
		DrawSurface(surf);
	} else {
		glBegin(GL_POLYGON);
		startH = curH = argL->getOneHalf();

		do {
			curV = curH->getVertex();
			tmpNorm = curV->GetNormalP();
			tmpPos = curV->GetPositionP(); 
			if(tmpNorm == nullptr || tmpPos == nullptr) continue;
			glNormal3dv(static_cast<GLdouble *>(&(tmpNorm->x)));
			glVertex3dv(static_cast<GLdouble *>(&(tmpPos->x)));
			curH = curH->getNextHalf();
		} while(startH != curH);

		glEnd();
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
	glShadeModel(GL_SMOOTH);

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
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, pos);
		glNormalPointer(GL_FLOAT, 0, vNorm);
		glDrawElements(tmpType, ifsP->faceSize * pNum,
					   GL_UNSIGNED_INT, &ifs[0]);
	} else {
		glBegin(tmpType);
		for(int ii = 0; ii < ifsP->faceSize; ii++) {
			for(int ij = 0; ij < pNum; ij++) {
				int index = ifs[pNum*ii+ij];
				glNormal3fv(static_cast<GLfloat *>(&vNorm[index].x));
				glVertex3fv(static_cast<GLfloat *>(&pos[index].x));
			}
		}
		glEnd();
	}
	return;
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

	glShadeModel(GL_FLAT);

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

	if((surf = argL->getSurfGeometry()) != nullptr) {
		DrawSurface(surf);
	} else if(argL->isTesselated() == true) {
		if((tmpNormP = argL->getNormal()) == nullptr) return;
		tesseVertexArray = argL->GetTesselateVertex();
		tesseIDArray = argL->GetTesselateIndex();
		glBegin(GL_TRIANGLES);
		glNormal3dv(static_cast<GLdouble *>(&(tmpNormP->x)));
		for(_st i = 0; i < tesseIDArray->size(); i++) {
			_st index = static_cast<_st>(tesseIDArray->at(i));
			tmpPosP = tesseVertexArray->at(index)->GetPositionP();
			glVertex3dv(static_cast<GLdouble *>(&(tmpPosP->x)));
		}
		glEnd();

	} else {
		if((tmpNormP = argL->getNormal()) == nullptr) return;
		startH = curH = argL->getOneHalf();
		glBegin(GL_POLYGON);
		glNormal3dv(static_cast<GLdouble *>(&(tmpNormP->x)));

		do {
			curV = curH->getVertex();
			tmpPosP = curV->GetPositionP(); 
			glVertex3dv(static_cast<GLdouble *>(&(tmpPosP->x)));
			curH = curH->getNextHalf();
		} while(startH != curH);

		glEnd();
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

	ifsP = static_cast<fk_IndexFaceSet *>(argObj->getShape());

	CommonMateSet(argObj, argLightFlag, argNodeFlag);
	glShadeModel(GL_FLAT);

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

	glBegin(tmpType);
	for(ii = 0; ii < ifsP->faceSize; ii++) {
		glNormal3fv(static_cast<GLfloat *>(&(pNorm[ii].x)));
		for(ij = 0; ij < pNum; ij++) {
			glVertex3fv(static_cast<GLfloat *>(&pos[ifs[pNum*ii+ij]].x));
		}
	}
	glEnd();

	return;
}

void fk_FaceDraw::DrawSurface(fk_Surface *)
{
	return;
}


void fk_FaceDraw::CommonMateSet(fk_Model *argObj, bool lightFlag, bool matFlag)
{
	float 		tmpShininess;
	fk_Shape	*shapeP;
	fk_Material	*curMat;

	shapeP = argObj->getShape();

	if(matFlag == true || shapeP == nullptr) {
		curMat = argObj->getInhMaterial();
	} else {
		curMat = &(*shapeP->getMaterialVector())[0];
	}
								  
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
	return;
}

void fk_FaceDraw::LocalMateSet(fk_Material *argMaterial, bool lightFlag)
{
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

	return;
}

#endif
