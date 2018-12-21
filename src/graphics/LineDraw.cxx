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
#include <FK/LineDraw.H>
#include <FK/OpenGL.H>
#include <FK/Model.h>
#include <FK/Curve.h>
#include <FK/Surface.h>
#include <FK/Solid.h>
#include <FK/IndexFace.h>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_LineDraw::fk_LineDraw(void)
	: modelShader(nullptr), elemShader(nullptr)
{
	return;
}

fk_LineDraw::~fk_LineDraw()
{
	delete modelShader;
	delete elemShader;
	return;
}

void fk_LineDraw::ModelShaderSetup(void)
{
	modelShader = new fk_ShaderBinder();
 	auto prog = modelShader->getProgram();
	auto param = modelShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Line_Model_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Line_FS.out"
		;

	if(prog->validate() == false) {
		fk_Window::printf("Shader Error");
		fk_Window::putString(prog->getLastError());
	}

	param->reserveAttribute(fk_Shape::vertexName);
	glBindFragDataLocation(prog->getProgramID(), 0, fragmentName.c_str());

	prog->link();
	return;
}

void fk_LineDraw::ElemShaderSetup(void)
{
	elemShader = new fk_ShaderBinder();
 	auto prog = elemShader->getProgram();
	auto param = elemShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Line_Elem_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Line_FS.out"
		;

	if(prog->validate() == false) {
		fk_Window::printf("Shader Error");
		fk_Window::putString(prog->getLastError());
	}

	param->reserveAttribute(fk_Line::vertexName);
	param->reserveAttribute(fk_Line::lineElementColorName);
	
	glBindFragDataLocation(prog->getProgramID(), 0, fragmentName.c_str());

	prog->link();
	return;
}

GLuint fk_LineDraw::VAOSetup(fk_Shape *argShape)
{
	GLuint 			vao;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	argShape->SetLineVAO(vao);
	argShape->DefineVBO();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return vao;
}

void fk_LineDraw::DrawShapeLine(fk_Model *argObj)
{
	fk_RealShapeType shapeType = argObj->getShape()->getRealShapeType();
	vector<float> * col = &(argObj->getLineColor()->col);
	fk_ShaderBinder *shader;
	fk_ElementMode mode = argObj->getElementMode();

	if(modelShader == nullptr) ModelShaderSetup();
	if(elemShader == nullptr) ElemShaderSetup();

	switch(mode) {
	  case FK_ELEM_MODEL:
		  shader = modelShader;
		  break;

	  case FK_ELEM_ELEMENT:
		  shader = elemShader;
		  break;

	  default:
		  return;
	}
	
	auto parameter = shader->getParameter();

	SetCommonParameter(argObj, parameter);
	parameter->setRegister(fk_Shape::lineModelColorName, col);

	glEnable(GL_LINE_SMOOTH);
	if((argObj->getDrawMode() & FK_SHADERMODE) == FK_NONEMODE) shader->ProcPreShader();

	switch(shapeType) {
	  case FK_SHAPE_LINE:
		  Draw_Line(argObj, parameter);
		  break;

	  case FK_SHAPE_IFS:
		  Draw_IFS(argObj, parameter);
		  break;
		  
	  default:
		break;
	}

	if((argObj->getDrawMode() & FK_SHADERMODE) == FK_NONEMODE) shader->ProcPostShader();
	return;
}

void fk_LineDraw::DrawBoundaryLine(fk_Model *argObj)
{
	FK_UNUSED(argObj);
	return;
}

void fk_LineDraw::Draw_Line(fk_Model *argObj, fk_ShaderParameter *argParam)
{
	fk_Line		*line = dynamic_cast<fk_Line *>(argObj->getShape());
	GLuint		vao = line->GetLineVAO();

	if(vao == 0) {
		vao = VAOSetup(line);
	}
	glBindVertexArray(vao);
	line->BindShaderBuffer(argParam->getAttrTable());
	glEnable(GL_LINE_SMOOTH);
	glDrawArrays(GL_LINES, 0, line->getSize()*2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return;
}

void fk_LineDraw::Draw_IFS(fk_Model *argObj, fk_ShaderParameter *argParam)
{
	fk_IndexFaceSet *ifs = dynamic_cast<fk_IndexFaceSet *>(argObj->getShape());
	GLuint			vao = ifs->GetLineVAO();

	if(vao == 0) {
		vao = VAOSetup(ifs);
	}
	glBindVertexArray(vao);
	ifs->BindShaderBuffer(argParam->getAttrTable());
	ifs->EdgeIBOSetup();
	glEnable(GL_LINE_SMOOTH);
	glDrawElements(GL_LINES, GLint(ifs->getEdgeSize()*2), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return;
}

/*
void fk_LineDraw::DrawShapeLineMaterial(fk_Model *argObj)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSLineNormal(argObj, true);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidLineMaterial(argObj);
		break;

	  default:
		break;
	}
	return;
}

void fk_LineDraw::DrawSolidLineMaterial(fk_Model *argObj)
{
	fk_Solid				*solidP;
	int						oldMateID = FK_UNDEFINED;
	int						paletteSize;
	fk_Color				*modelColor;
	double					orgWidth;
	vector<fk_Material>		*matV;
	list<fk_Edge *>			*edgeStack;
	bool					reverseFlag = argObj->getReverseDrawMode();

	list<fk_Edge *>::iterator			ite;
	list<fk_Edge *>::reverse_iterator	rite;

	solidP = static_cast<fk_Solid *>(argObj->getShape());
	if(solidP->checkDB() == false) return;
	if(solidP->getNextE(nullptr) == nullptr) return;

	if(solidP->GetECacheStatus() == false) {
		solidP->MakeECache();
	}

	edgeStack = solidP->GetECache();

	modelColor = argObj->getLineColor();
	if(modelColor == nullptr) {
		modelColor = argObj->getMaterial()->getAmbient();
	}

	oldMateID = -2;
	paletteSize = solidP->getPaletteSize();
	matV = solidP->getMaterialVector();
	orgWidth = argObj->getWidth();

	if(reverseFlag == false) {
		for(ite = edgeStack->begin(); ite != edgeStack->end(); ++ite) {
			oldMateID = DrawSolidLineMaterialElem(*ite, oldMateID,
												  paletteSize, orgWidth,
												  matV, modelColor);
		}
	} else {
		for(rite = edgeStack->rbegin(); rite != edgeStack->rend(); ++rite) {
			oldMateID = DrawSolidLineMaterialElem(*rite, oldMateID,
												  paletteSize, orgWidth,
												  matV, modelColor);
		}
	}

	return;
}

int fk_LineDraw::DrawSolidLineMaterialElem(fk_Edge *argE,
										   int argOldMateID,
										   int argPaletteSize,
										   double argOrgWidth,
										   vector<fk_Material> *argMatV,
										   fk_Color *argModelColor)
{
	int			curMateID, retMateID;
	double		trueWidth;
	fk_Color	*curColor;

	FK_UNUSED(argModelColor);
	
	retMateID = argOldMateID;
	switch(argE->getElemMaterialMode()) {
	  case FK_CHILD_MODE:
		curMateID = argE->getElemMaterialID();
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
#ifndef OPENGL4
			glColor4fv(&argModelColor->col[0]);
#endif
			retMateID = FK_UNDEFINED;
		} else {
			curColor = (*argMatV)[static_cast<_st>(curMateID)].getAmbient();
#ifndef OPENGL4			
			glColor4fv(&curColor->col[0]);
#endif
			retMateID = curMateID;
		}
	}


	trueWidth = argE->getDrawWidth();

	if(trueWidth < 0.0) {
		glLineWidth(static_cast<GLfloat>(argOrgWidth));
	} else {
		glLineWidth(static_cast<GLfloat>(trueWidth));
	}

#ifndef OPENGL4
	glBegin(GL_LINES);
#endif

	CommonLineDrawFunc(argE, false);

#ifndef OPENGL4
	glEnd();
#endif

	return retMateID;
}


void fk_LineDraw::DrawShapeLineNormal(fk_Model *argObj, bool argFlag)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSLineNormal(argObj, argFlag);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidLineNormal(argObj, argFlag);
		break;

	  case FK_SHAPE_CURVE:
		DrawCurveLineNormal(argObj, argFlag);
		break;

	  case FK_SHAPE_SURFACE:
		DrawSurfaceLineNormal(argObj, argFlag);
		break;
		
	  default:
		break;
	}
	return;
}

void fk_LineDraw::DrawSolidLineNormal(fk_Model *argObj, bool argFlg)
{
	fk_Solid			*solidP;
	fk_Color			*ModelColor;
	double				orgWidth;
	list<fk_Edge *>		*edgeStack;
	bool				reverseFlag = argObj->getReverseDrawMode();

	list<fk_Edge *>::iterator			ite;
	list<fk_Edge *>::reverse_iterator	rite;


	solidP = static_cast<fk_Solid *>(argObj->getShape());
	if(solidP->checkDB() == false) return;
	if(solidP->getNextE(nullptr) == nullptr) return;

	if(solidP->GetECacheStatus() == false) {
		solidP->MakeECache();
	}

	edgeStack = solidP->GetECache();

	if(argFlg == true) {
		ModelColor = argObj->getLineColor();
		if(ModelColor == nullptr) {
			ModelColor = argObj->getMaterial()->getAmbient();
		}
	} else {
		ModelColor = solidP->getMaterial(0)->getAmbient();
	}

#ifndef OPENGL4
	glDisable(GL_LIGHTING);
	glColor4fv(&ModelColor->col[0]);
#endif

	orgWidth = argObj->getWidth();

	if(reverseFlag == false) {
		for(ite = edgeStack->begin(); ite != edgeStack->end(); ++ite) {
			DrawSolidLineNormalElem(*ite, orgWidth);
		}
	} else {
		for(rite = edgeStack->rbegin(); rite != edgeStack->rend(); ++rite) {
			DrawSolidLineNormalElem(*rite, orgWidth);
		}
	}

	return;
}

void fk_LineDraw::DrawSolidLineNormalElem(fk_Edge *argE, double argOrgWidth)
{
	double		trueWidth;

	trueWidth = argE->getDrawWidth();
	if(trueWidth < 0.0) {
		glLineWidth(static_cast<GLfloat>(argOrgWidth));
	} else {
		glLineWidth(static_cast<GLfloat>(trueWidth));
	}

#ifndef OPENGL4
	glBegin(GL_LINES);
#endif

	CommonLineDrawFunc(argE, false);

#ifndef OPENGL4	
	glEnd();
#endif
}


void fk_LineDraw::DrawIFSLineNormal(fk_Model *argObj, bool argFlag)
{
	fk_IndexFaceSet		*ifsetP;
	fk_Color			*modelColor;

	ifsetP = static_cast<fk_IndexFaceSet *>(argObj->getShape());

	if(argFlag == true) {
		modelColor = argObj->getLineColor();
		if(modelColor == nullptr) {
			modelColor = argObj->getMaterial()->getAmbient();
		}
	} else {
		modelColor = ifsetP->getMaterial(0)->getAmbient();
	}

#ifndef OPENGL4
	glDisable(GL_LIGHTING);
	glColor4fv(&modelColor->col[0]);
#endif

	DrawIFSLineSub(ifsetP);

	return;
}

void fk_LineDraw::DrawIFSLineSub(fk_IndexFaceSet *argIFS)
{
	fk_FVector	*pos;
	int			*edgeSet;
	int			lineSize;

	pos = &argIFS->pos[0];
	edgeSet = &argIFS->edgeSet[0];
	lineSize = static_cast<int>(argIFS->edgeSet.size());

	if(arrayState == true) {
#ifndef OPENGL4
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, pos);
#endif		
		glDrawElements(GL_LINES, lineSize,
					   GL_UNSIGNED_INT, edgeSet);
	} else {
#ifndef OPENGL4
		glBegin(GL_LINES);
		for(_st ii = 0; ii < static_cast<_st>(lineSize); ++ii) {
			glVertex3fv(static_cast<GLfloat *>(&pos[edgeSet[ii]].x));
		}
		glEnd();
#endif
	}
	return;
}

void fk_LineDraw::CommonLineDrawFunc(fk_Edge *argE, bool argMode)
{
	fk_Vector			*vPos;
	fk_Curve			*curv;
	vector<fk_Vector>	*vArray;
	fk_Half				*lH, *rH;
	fk_Vertex			*lV, *rV;

	FK_UNUSED(argMode);
	FK_UNUSED(vPos);

	if((curv = argE->getCurveGeometry()) != nullptr) {
		curv->makeCache();
		int div = curv->getDiv();
		vArray = curv->getPosCache();

		FK_UNUSED(div);

#ifndef OPENGL4
		if(argMode == false) {
			glEnd();
		}

		glBegin(GL_LINE_STRIP);
		for(_st ii = 0; ii <= static_cast<_st>(div); ++ii) {
			vPos = &((*vArray)[ii]);
			glVertex3dv(static_cast<GLdouble *>(&(vPos->x)));
		}
		glEnd();

		if(argMode == false) {
			glBegin(GL_LINES);
		}
#endif
		
	} else {

		rH = argE->getRightHalf();
		lH = argE->getLeftHalf();
		if(rH == nullptr || lH == nullptr) return;
		lV = lH->getVertex();
		rV = rH->getVertex();
		if(lV == nullptr || rV == nullptr) return;

#ifndef OPENGL4
		if(argMode == true) {
			glBegin(GL_LINES);
		}

		vPos = rV->GetPositionP();
		glVertex3dv(static_cast<GLdouble *>(&(vPos->x)));
		vPos = lV->GetPositionP();
		glVertex3dv(static_cast<GLdouble *>(&(vPos->x)));

		if(argMode == true) {
			glEnd();
		}
#endif
	}

	return;
}

void fk_LineDraw::DrawCurveLineNormal(fk_Model *argObj, bool argMode)
{
	fk_Curve	*curve = static_cast<fk_Curve *>(argObj->getShape());
	fk_Color	*modelColor;

	if(argMode == true) {
		modelColor = argObj->getLineColor();
		if(modelColor == nullptr) {
			modelColor = argObj->getMaterial()->getAmbient();
		}
	} else {
		modelColor = curve->getMaterial(0)->getAmbient();
	}

#ifndef OPENGL4
	glDisable(GL_LIGHTING);
	glColor4fv(&modelColor->col[0]);	
#endif
	
	curve->makeCache();
	_st div = static_cast<_st>(curve->getDiv());
	auto vArray = curve->getPosCache();

	FK_UNUSED(div);
	FK_UNUSED(vArray);

#ifndef OPENGL4
	glBegin(GL_LINE_STRIP);
	for(_st i = 0; i < div; ++i) {
		auto vPos = &((*vArray)[i]);
		glVertex3dv(static_cast<GLdouble *>(&(vPos->x)));
	}
	glEnd();
#endif
	
	return;
}

void fk_LineDraw::DrawSurfaceLineNormal(fk_Model *argObj, bool argMode)
{
	fk_Surface	*surf = static_cast<fk_Surface *>(argObj->getShape());
	fk_Color	*modelColor;
	
	if(argMode == true) {
		modelColor = argObj->getLineColor();
		if(modelColor == nullptr) {
			modelColor = argObj->getMaterial()->getAmbient();
		}
	} else {
		modelColor = surf->getMaterial(0)->getAmbient();
	}

#ifndef OPENGL4	
	glDisable(GL_LIGHTING);
	glColor4fv(&modelColor->col[0]);	
#endif
	
	surf->makeCache();
	_st div = static_cast<_st>(surf->getDiv());
	auto vArray = surf->getPosCache();

	FK_UNUSED(div);
	FK_UNUSED(vArray);
	
#ifndef OPENGL4
	for(_st i = 0; i <= div; ++i) {
		glBegin(GL_LINE_STRIP);
		for(_st j = 0; j <= div; ++j) {
			auto vPos = &((*vArray)[i*(div+1)+j]);
			glVertex3dv(static_cast<GLdouble *>(&(vPos->x)));
		}
		glEnd();
	}

	for(_st i = 0; i <= div; ++i) {
		glBegin(GL_LINE_STRIP);
		for(_st j = 0; j <= div; ++j) {
			auto vPos = &((*vArray)[j*(div+1)+i]);
			glVertex3dv(static_cast<GLdouble *>(&(vPos->x)));
		}
		glEnd();
	}
#endif

	return;
}

#endif

void fk_LineDraw::DrawShapeLinePick(fk_Model *argObj)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		DrawIFSLinePick(argObj);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidLinePick(argObj);
		break;

	  case FK_SHAPE_CURVE:
		DrawCurveLinePick(argObj);
		break;

	  case FK_SHAPE_SURFACE:
		DrawSurfaceLinePick(argObj);
		break;

	  default:
		break;
	}
	return;
}

void fk_LineDraw::DrawSolidLinePick(fk_Model *argObj)
{
	fk_Solid			*solidP;
	list<fk_Edge *>		*edgeStack;
	bool				reverseFlag = argObj->getReverseDrawMode();

	list<fk_Edge *>::iterator			ite;
	list<fk_Edge *>::reverse_iterator	rite;


	solidP = static_cast<fk_Solid *>(argObj->getShape());
	if(solidP->checkDB() == false) return;
	if(solidP->getNextE(nullptr) == nullptr) return;

	if(solidP->GetECacheStatus() == false) {
		solidP->MakeECache();
	}

#ifndef OPENGL4	
	glDisableClientState(GL_VERTEX_ARRAY);
#endif

	edgeStack = solidP->GetECache();

	if(reverseFlag == false) {
		for(ite = edgeStack->begin(); ite != edgeStack->end(); ++ite) {
			DrawSolidLinePickElem(*ite);
		}
	} else {
		for(rite = edgeStack->rbegin(); rite != edgeStack->rend(); ++rite) {
			DrawSolidLinePickElem(*rite);
		}
	}

	return;
}

void fk_LineDraw::DrawSolidLinePickElem(fk_Edge *argE)
{
	FK_UNUSED(argE);
#ifndef OPENGL4	
	glPushName(static_cast<GLuint>(argE->getID()*3 + 1));
	CommonLineDrawFunc(argE, true);
	glPopName();
#endif
	return;
}


void fk_LineDraw::DrawIFSLinePick(fk_Model *argObj)
{
	fk_IndexFaceSet		*ifsetP;
	int					ii;
	int					lineNum;
	fk_FVector			*pos;
	int					*lineSet;

	FK_UNUSED(ii);
	ifsetP = static_cast<fk_IndexFaceSet *>(argObj->getShape());

	pos = &ifsetP->pos[0];
	lineNum = static_cast<int>(ifsetP->edgeSet.size())/2;
	lineSet = &ifsetP->edgeSet[0];

#ifndef OPENGL4
	glDisableClientState(GL_VERTEX_ARRAY);
	for(ii = 0; ii < lineNum; ++ii) {
		glPushName(static_cast<GLuint>(ii*3 + 1));
		glBegin(GL_LINE);
		glVertex3fv(static_cast<GLfloat *>(&pos[lineSet[2*ii]].x));
		glVertex3fv(static_cast<GLfloat *>(&pos[lineSet[2*ii+1]].x));
		glEnd();
		glPopName();
	}
#endif

	return;
}

void fk_LineDraw::DrawCurveLinePick(fk_Model *argObj)
{
	fk_Curve *curve = static_cast<fk_Curve *>(argObj->getShape());

#ifndef OPENGL4
	glDisableClientState(GL_VERTEX_ARRAY);
#endif

	curve->makeCache();
	_st div = static_cast<_st>(curve->getDiv());
	auto vArray = curve->getPosCache();
	FK_UNUSED(div);
	FK_UNUSED(vArray);

#ifndef OPENGL4
	for(_st i = 0; i < div; ++i) {
		auto vPos1 = &((*vArray)[i]);
		auto vPos2 = &((*vArray)[i+1]);
		glPushName(static_cast<GLuint>(i*3 + 1));
		glBegin(GL_LINE);
		glVertex3dv(static_cast<GLdouble *>(&(vPos1->x)));
		glVertex3dv(static_cast<GLdouble *>(&(vPos2->x)));
		glEnd();
		glPopName();
	}
#endif

	return;
}

void fk_LineDraw::DrawSurfaceLinePick(fk_Model *argObj)
{
	fk_Surface *surf = static_cast<fk_Surface *>(argObj->getShape());
	GLuint count = 0;

	FK_UNUSED(count);

#ifndef OPENGL4
	glDisableClientState(GL_VERTEX_ARRAY);
#endif

	surf->makeCache();
	_st div = static_cast<_st>(surf->getDiv());
	auto vArray = surf->getPosCache();

	FK_UNUSED(div);
	FK_UNUSED(vArray);

#ifndef OPENGL4
	for(_st i = 0; i <= div; ++i) {
		for(_st j = 0; j < div; ++j) {
			auto vPos1 = &((*vArray)[i*(div+1)+j]);
			auto vPos2 = &((*vArray)[i*(div+1)+j+1]);
			glPushName(static_cast<GLuint>(count*3 + 1));
			glBegin(GL_LINE);
			glVertex3dv(static_cast<GLdouble *>(&(vPos1->x)));
			glVertex3dv(static_cast<GLdouble *>(&(vPos2->x)));
			glEnd();
			glPopName();
			++count;
		}
	}
#endif

#ifndef OPENGL4	
	for(_st i = 0; i <= div; ++i) {
		for(_st j = 0; j < div; ++j) {
			auto vPos1 = &((*vArray)[j*(div+1)+i]);
			auto vPos2 = &((*vArray)[(j+1)*(div+1)+i]);
			glPushName(static_cast<GLuint>(count*3 + 1));
			glBegin(GL_LINE);
			glVertex3dv(static_cast<GLdouble *>(&(vPos1->x)));
			glVertex3dv(static_cast<GLdouble *>(&(vPos2->x)));
			glEnd();
			glPopName();
			++count;
		}
	}
#endif
	return;
}
*/
