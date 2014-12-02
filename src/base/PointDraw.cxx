/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#include "PointDraw_D3D.cxx"
#else

#define FK_DEF_SIZETYPE
#include <FK/PointDraw.H>
#include <FK/OpenGL.H>
#include <FK/Model.h>
#include <FK/Point.h>
#include <FK/Solid.h>
#include <FK/IndexFace.h>
#include <FK/Vertex.h>

using namespace std;

fk_PointDraw::fk_PointDraw(void)
{
	SetArrayState(false);
}

fk_PointDraw::~fk_PointDraw()
{
	return;
}

void fk_PointDraw::SetArrayState(bool argState)
{
	arrayState = argState;
	return;
}

void fk_PointDraw::DrawShapePoint(fk_Model *argObj, bool argPickFlag)
{
	fk_MaterialMode	shapeMateMode;
	fk_MaterialMode	modelMateMode;

	shapeMateMode = argObj->getShape()->getMaterialMode();
	modelMateMode = argObj->getMaterialMode();

	glDisable(GL_LIGHTING);
	glPointSize((GLfloat)argObj->getSize());

	if(argPickFlag == true) {
		DrawShapePointPick(argObj);
	} else if(modelMateMode == FK_PARENT_MODE) {
		if(shapeMateMode == FK_PARENT_MODE) {
			DrawShapePointMaterial(argObj);
		} else if(shapeMateMode == FK_CHILD_MODE) {
			DrawShapePointNormal(argObj, false);
		}
	} else if(modelMateMode == FK_CHILD_MODE) {
		DrawShapePointNormal(argObj, true);
	}

	return;
}

void fk_PointDraw::DrawShapePointPick(fk_Model *argObj)
{
	
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSPointPick(argObj);
		break;

	  case FK_SHAPE_POINT:
		DrawParticlePointPick(argObj);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidPointPick(argObj);
		break;

	  default:
		break;
	}
	return;
}

void fk_PointDraw::DrawSolidPointPick(fk_Model *argObj)
{
	fk_Solid				*solidP;
	list<fk_Vertex *>		*vertexStack;
	bool					reverseFlag = argObj->getReverseDrawMode();

	list<fk_Vertex *>::iterator				ite;
	list<fk_Vertex *>::reverse_iterator		rite;


	solidP = static_cast<fk_Solid *>(argObj->getShape());
	if(solidP->checkDB() == false) return;
	if(solidP->getNextV(NULL) == NULL) return;

	if(solidP->GetVCacheStatus() == false) {
		solidP->MakeVCache();
	}

	vertexStack = solidP->GetVCache();

	glDisableClientState(GL_VERTEX_ARRAY);

	if(reverseFlag == false) {
		for(ite = vertexStack->begin(); ite != vertexStack->end(); ++ite) {
			DrawSolidPointPickElem(*ite);
		}
	} else {
		for(rite = vertexStack->rbegin(); rite != vertexStack->rend(); ++rite) {
			DrawSolidPointPickElem(*rite);
		}
	}

	return;
}

void fk_PointDraw::DrawSolidPointPickElem(fk_Vertex *argV)
{
	glPushName(static_cast<GLuint>(argV->getID()*3 + 2));
	glBegin(GL_POINTS);

	glVertex3dv(static_cast<GLdouble *>(&(argV->GetPositionP()->x)));

	glEnd();
	glPopName();
	return;
}


void fk_PointDraw::DrawIFSPointPick(fk_Model *argObj)
{
	fk_IndexFaceSet		*ifsetP;
	_st					ii;

	ifsetP = static_cast<fk_IndexFaceSet *>(argObj->getShape());

	glDisableClientState(GL_VERTEX_ARRAY);

	for(ii = 0; ii < static_cast<_st>(ifsetP->posSize); ii++) {
		glPushName(static_cast<GLuint>(ii*3 + 2));
		glBegin(GL_POINTS);
		glVertex3fv(static_cast<GLfloat *>(&ifsetP->pos[ii].x));
		glEnd();
		glPopName();
	}

	return;
}

void fk_PointDraw::DrawParticlePointPick(fk_Model *argObj)
{
	fk_Point		*point;
	fk_FVector		*pos;
	int				id;

	point = static_cast<fk_Point *>(argObj->getShape());
	pos = point->vec.at(0);

	id = point->vec.next(-1);

	glDisableClientState(GL_VERTEX_ARRAY);

	while(id >= 0) {
		if(point->getDrawMode(id) == true) {
			glPushName(static_cast<GLuint>(id* 3 + 2));
			glBegin(GL_POINTS);
			glVertex3fv(static_cast<GLfloat *>(&pos[id].x));
			glEnd();
			glPopName();
		}
		id = point->vec.next(id);
	}

	return;
}

void fk_PointDraw::DrawShapePointMaterial(fk_Model *argObj)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSPointNormal(argObj, true);
		break;

	  case FK_SHAPE_POINT:
		DrawParticlePointMaterial(argObj);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidPointMaterial(argObj);

	  default:
		break;
	}
	return;
}

void fk_PointDraw::DrawSolidPointMaterial(fk_Model *argObj)
{
	fk_Solid				*solidP;
	fk_Color				*modelColor;
	int						oldMateID, paletteSize;
	double					orgSize;
	vector<fk_Material>		*matV;
	list<fk_Vertex *>		*vertexStack;
	bool					reverseFlag = argObj->getReverseDrawMode();

	list<fk_Vertex *>::iterator				ite;
	list<fk_Vertex *>::reverse_iterator		rite;
	

	solidP = static_cast<fk_Solid *>(argObj->getShape());
	if(solidP->checkDB() == false) return;
	if(solidP->getNextV(NULL) == NULL) return;

	if(solidP->GetVCacheStatus() == false) {
		solidP->MakeVCache();
	}

	vertexStack = solidP->GetVCache();

	modelColor = argObj->getInhPointColor();

	if(modelColor == NULL) {
		modelColor = argObj->getInhMaterial()->getAmbient();
	}

	oldMateID = -2;
	orgSize = argObj->getSize();

	paletteSize = solidP->getPaletteSize();
	matV = solidP->getMaterialVector();

	if(reverseFlag == false) {
		for(ite = vertexStack->begin(); ite != vertexStack->end(); ++ite) {
			oldMateID = DrawSolidPointMaterialElem(*ite, oldMateID,
												   paletteSize, orgSize,
												   matV, modelColor);
		}
	} else {
		for(rite = vertexStack->rbegin();
			rite != vertexStack->rend(); ++rite) {
			oldMateID = DrawSolidPointMaterialElem(*rite, oldMateID,
												   paletteSize, orgSize,
												   matV, modelColor);
		}
	}

	return;
}

int fk_PointDraw::DrawSolidPointMaterialElem(fk_Vertex *argV,
											 int argOldMateID,
											 int argPaletteSize,
											 double argOrgSize,
											 vector<fk_Material> *argMatV,
											 fk_Color *argModelColor)
{
	int			curMateID, retMateID;
	double		trueSize;
	fk_Color	*curColor;

	retMateID = argOldMateID;
	switch(argV->getElemMaterialMode()) {
	  case FK_CHILD_MODE:
		curMateID = argV->getElemMaterialID();
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
			glColor4fv(&argModelColor->col[0]);	
			retMateID = FK_UNDEFINED;
		} else {
			curColor = (*argMatV)[static_cast<_st>(curMateID)].getAmbient();
			glColor4fv(&curColor->col[0]);
			retMateID = curMateID;
		}
	}

	trueSize = argV->getDrawSize();
	if(trueSize < 0.0) {
		glPointSize(static_cast<GLfloat>(argOrgSize));
	} else {
		glPointSize(static_cast<GLfloat>(trueSize));
	}

	glBegin(GL_POINTS);
	glVertex3dv(static_cast<GLdouble *>(&(argV->GetPositionP()->x)));
	glEnd();

	return retMateID;
}

void fk_PointDraw::DrawParticlePointMaterial(fk_Model *argObj)
{
	fk_Point				*point;
	fk_FVector				*pos;
	fk_Color				*modelColor, *curColor;
	vector<fk_Material>		*matV;
	fk_Material				*mat;
	int						id;
	int						oldMateID, curMateID, paletteSize;


	point = static_cast<fk_Point *>(argObj->getShape());
	pos = point->vec.at(0);

	modelColor = argObj->getInhPointColor();

	if(modelColor == NULL) {
		modelColor = argObj->getInhMaterial()->getAmbient();
	}

	oldMateID = -2;

	id = point->vec.next(-1);
	matV = point->getMaterialVector();
	paletteSize = point->getPaletteSize();
	glBegin(GL_POINTS);
	while(id >= 0) {
		if(point->getDrawMode(id) == true) {
			curMateID = point->getColorID(id);

			if(curMateID < 0 || curMateID >= paletteSize) {
				curMateID = FK_UNDEFINED;
			}

			if(curMateID != oldMateID) {
				if(curMateID == FK_UNDEFINED) {
					glColor4fv(&modelColor->col[0]);	
					oldMateID = FK_UNDEFINED;
				} else {
					mat = &(*matV)[static_cast<_st>(curMateID)];
					curColor = mat->getAmbient();
					glColor4fv(&curColor->col[0]);
					oldMateID = curMateID;
				}
				oldMateID = curMateID;
			}

			glVertex3fv(static_cast<GLfloat *>(&pos[id].x));
		}
		id = point->vec.next(id);
	}
	glEnd();
	return;
}

void fk_PointDraw::DrawShapePointNormal(fk_Model *argObj, bool argFlag)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSPointNormal(argObj, argFlag);
		break;

	  case FK_SHAPE_POINT:
		DrawParticlePointNormal(argObj, argFlag);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidPointNormal(argObj, argFlag);

	  default:
		break;
	}
	return;
}

void fk_PointDraw::DrawSolidPointNormal(fk_Model *argObj, bool argFlg)
{
	fk_Solid				*solidP;
	fk_Color				*ModelColor;
	double					orgSize;
	list<fk_Vertex *>		*vertexStack;
	bool					reverseFlag = argObj->getReverseDrawMode();

	list<fk_Vertex *>::iterator				ite;
	list<fk_Vertex *>::reverse_iterator		rite;


	solidP = static_cast<fk_Solid *>(argObj->getShape());
	if(solidP->checkDB() == false) return;
	if(solidP->getNextV(NULL) == NULL) return;

	if(solidP->GetVCacheStatus() == false) {
		solidP->MakeVCache();
	}

	vertexStack = solidP->GetVCache();

	if(argFlg == true) {
		ModelColor = argObj->getInhPointColor();
		if(ModelColor == NULL) {
			ModelColor = argObj->getInhMaterial()->getAmbient();
		}
	} else {
		ModelColor = (*solidP->getMaterialVector())[0].getAmbient();
	}

	glColor4fv(&ModelColor->col[0]);
	orgSize = argObj->getSize();

	if(reverseFlag == false) {
		for(ite = vertexStack->begin(); ite != vertexStack->end(); ++ite) {
			DrawSolidPointNormalElem(*ite, orgSize);
		}
	} else {
		for(rite = vertexStack->rbegin(); rite != vertexStack->rend(); ++rite) {
			DrawSolidPointNormalElem(*rite, orgSize);
		}
	}

	return;
}

void fk_PointDraw::DrawSolidPointNormalElem(fk_Vertex *argV, double argOrgSize)
{
	double trueSize;

	trueSize = argV->getDrawSize();
	if(trueSize < 0.0) {
		glPointSize(static_cast<GLfloat>(argOrgSize));
	} else {
		glPointSize(static_cast<GLfloat>(trueSize));
	}

	glBegin(GL_POINTS);
	glVertex3dv(static_cast<GLdouble *>(&(argV->GetPositionP()->x)));
	glEnd();

	return;
}


void fk_PointDraw::DrawIFSPointNormal(fk_Model *argObj, bool argFlag)
{
	fk_IndexFaceSet		*ifsetP;
	fk_Color			*modelColor;

	ifsetP = static_cast<fk_IndexFaceSet *>(argObj->getShape());

	if(argFlag == true) {
		modelColor = argObj->getInhPointColor();
		if(modelColor == NULL) {
			modelColor = argObj->getInhMaterial()->getAmbient();
		}
	} else {
		modelColor = (*ifsetP->getMaterialVector())[0].getAmbient();
	}

	glColor4fv(&modelColor->col[0]);

	if(arrayState == true) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &ifsetP->pos[0]);
		glDrawArrays(GL_POINTS, 0, ifsetP->posSize);
	} else {
		glBegin(GL_POINTS);
		for(_st id = 0; id < static_cast<_st>(ifsetP->posSize); id++) {
			glVertex3fv(static_cast<GLfloat *>(&ifsetP->pos[id].x));
		}
		glEnd();
	}
	return;
}

void fk_PointDraw::DrawParticlePointNormal(fk_Model *argObj, bool argFlag)
{
	fk_Point		*point;
	fk_FVector		*pos;
	fk_Color		*modelColor;

	point = static_cast<fk_Point *>(argObj->getShape());
	pos = point->vec.at(0);

	if(argFlag == true) {
		modelColor = argObj->getInhPointColor();
		if(modelColor == NULL) {
			modelColor = argObj->getInhMaterial()->getAmbient();
		}
	} else {
		modelColor = (*point->getMaterialVector())[0].getAmbient();
	}

	glColor4fv(&modelColor->col[0]);

	if(point->vec.isSerial() == true && arrayState == true) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, point->vec.at(0));
		glDrawArrays(GL_POINTS, 0, point->vec.size());
	} else {
		int id = point->vec.next(-1);
		glBegin(GL_POINTS);
		while(id >= 0) {
			if(point->getDrawMode(id) == true) {
				_st		i = static_cast<_st>(id);
				glVertex3fv(static_cast<GLfloat *>(&pos[i].x));
			}
			id = point->vec.next(id);
		}
		glEnd();
	}
	return;
}

#endif
