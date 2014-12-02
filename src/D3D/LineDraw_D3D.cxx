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
#include <FK/D3D/LineDraw.h>
#include <FK/OpenGL.h>
#include <FK/Model.h>
#include <FK/Curve.h>
#include <FK/Solid.h>
#include <FK/IndexFace.h>
#include <FK/Vertex.h>
#include <FK/Half.h>

using namespace std;

// 頂点の定義
struct LINECUSTOMVERTEX
{
    FLOAT x, y, z;	// 頂点座標
	FLOAT psize;	// 線の太さ
	DWORD color;	// 線の色
};
#define D3DFVF_LINECUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE)

// 描画用バッファ
static vector<LINECUSTOMVERTEX>	workCustomVertexArray;
static vector<fk_FVector>		workVertexArray;
static float					g_width;

fk_LineDraw::fk_LineDraw(void)
{
	ref_lpD3DDEV = NULL;
	// m_lpD3DXLine = NULL;
	setArrayState(false);
}

fk_LineDraw::~fk_LineDraw()
{
	// RELEASE(m_lpD3DXLine);
	workCustomVertexArray.clear();
	// workVertexArray.clear();

	return;
}

void fk_LineDraw::setD3DDevice(LPDIRECT3DDEVICE9 argDev)
{
	ref_lpD3DDEV = argDev;
	/*
	D3DXCreateLine(ref_lpD3DDEV, &m_lpD3DXLine);
	m_lpD3DXLine->SetGLLines(TRUE);
	m_lpD3DXLine->SetAntialias(TRUE);
	*/

	return;
}

/*
LPD3DXLINE	fk_LineDraw::getD3DXLine(void)
{
	return m_lpD3DXLine;
}
*/

void fk_LineDraw::setArrayState(bool argState)
{
	arrayState = argState;

	return;
}

void fk_LineDraw::drawShapeLine(fk_Model *argObj, bool argPickFlag)
{
	fk_MaterialMode	shapeMateMode;
	fk_MaterialMode	modelMateMode;

	shapeMateMode = argObj->getShape()->getMaterialMode();
	modelMateMode = argObj->getMaterialMode();

	// ライトオフは全種共通なのでここでのみ設定
    ref_lpD3DDEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ラインデバイスに渡す行列をここで作成
	/*
	ref_lpD3DDEV->GetTransform(D3DTS_PROJECTION, &m_projMat);
	ref_lpD3DDEV->GetTransform(D3DTS_VIEW, &m_viewMat);
	ref_lpD3DDEV->GetTransform(D3DTS_WORLD, &m_transMat);
	m_transMat = m_transMat * m_viewMat * m_projMat;
	*/

	if(argPickFlag == true) {
		DrawShapeLinePick(argObj);
	} else if(modelMateMode == FK_PARENT_MODE) {
		if(shapeMateMode == FK_PARENT_MODE) {
			DrawShapeLineMaterial(argObj);
		} else if(shapeMateMode == FK_CHILD_MODE) {
			DrawShapeLineNormal(argObj, false);
		}
	} else if(modelMateMode == FK_CHILD_MODE) {
		DrawShapeLineNormal(argObj, true);
	}

	return;
}

void fk_LineDraw::DrawShapeLinePick(fk_Model *argObj)
{
	switch(argObj->getShape()->getObjectType()) {
	  case FK_INDEXFACESET:
	  case FK_BLOCK:
	  case FK_CIRCLE:
	  case FK_SPHERE:
	  case FK_PRISM:
	  case FK_CONE:
		DrawIFSLinePick(argObj);
		break;

	  case FK_SOLID:
	  case FK_POLYGON:
	  case FK_POLYLINE:
	  case FK_CLOSEDLINE:
	  case FK_LINE:
		DrawSolidLinePick(argObj);
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


	solidP = (fk_Solid *)argObj->getShape();
	if(solidP->checkDB() == false) return;
	if(solidP->getNextE((fk_Edge *)NULL) == (fk_Edge *)NULL) return;

	if(solidP->GetECacheStatus() == false) {
		solidP->MakeECache();
	}

	glDisableClientState(GL_VERTEX_ARRAY);

	edgeStack = solidP->GetECache();

	glLineWidth((GLfloat)argObj->getWidth());

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
	glPushName(argE->getID()*3 + 1);
	PickLineDrawFunc(argE, true);
	glPopName();
	return;
}


void fk_LineDraw::DrawIFSLinePick(fk_Model *argObj)
{
	fk_IndexFaceSet		*ifsetP;
	int					ii;
	int					lineNum;
	fk_FVector			*pos;
	int					*lineSet;

	ifsetP = (fk_IndexFaceSet *)argObj->getShape();

	glLineWidth((GLfloat)argObj->getWidth());

	pos = &ifsetP->pos[0];
	lineNum = int(ifsetP->edgeSet.size())/2;
	lineSet = &ifsetP->edgeSet[0];

	glDisableClientState(GL_VERTEX_ARRAY);

	for(ii = 0; ii < lineNum; ii++) {
		glPushName(ii*3 + 1);
		glBegin(GL_LINES);
		glVertex3fv((GLfloat *)&pos[lineSet[2*ii]]);
		glVertex3fv((GLfloat *)&pos[lineSet[2*ii+1]]);
		glEnd();
		glPopName();
	}

	return;
}

void fk_LineDraw::DrawShapeLineMaterial(fk_Model *argObj)
{
	switch(argObj->getShape()->getObjectType()) {
	  case FK_INDEXFACESET:
	  case FK_BLOCK:
	  case FK_CIRCLE:
	  case FK_SPHERE:
	  case FK_PRISM:
	  case FK_CONE:
		DrawIFSLineNormal(argObj, true);
		break;

	  case FK_SOLID:
	  case FK_POLYGON:
	  case FK_POLYLINE:
	  case FK_CLOSEDLINE:
	  case FK_LINE:
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

	solidP = (fk_Solid *)argObj->getShape();
	if(solidP->checkDB() == false) return;
	if(solidP->getNextE((fk_Edge *)NULL) == (fk_Edge *)NULL) return;

	if(solidP->GetECacheStatus() == false) {
		solidP->MakeECache();
	}

	edgeStack = solidP->GetECache();

	modelColor = argObj->getInhLineColor();
	if(modelColor == (fk_Color *)NULL) {
		modelColor = argObj->getInhMaterial()->getAmbient();
	}

	// m_lpD3DXLine->SetWidth((float)argObj->getWidth());

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
	DWORD		packedCol, modelCol;

	modelCol = GetPackedColor(argModelColor);
	packedCol = modelCol;

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
			packedCol = modelCol;
			retMateID = FK_UNDEFINED;
		} else {
			curColor = (*argMatV)[curMateID].getAmbient();
			packedCol = GetPackedColor(curColor);
			retMateID = curMateID;
		}
	}

	trueWidth = argE->getDrawWidth();
	if(trueWidth < 0.0) {
		// m_lpD3DXLine->SetWidth((float)orgWidth);
		g_width = (float)argOrgWidth;
	} else {
		// m_lpD3DXLine->SetWidth((float)trueWidth);
		g_width = (float)trueWidth;
	}

	CommonLineDrawFunc(argE, false, packedCol);

	return retMateID;
}

void fk_LineDraw::DrawShapeLineNormal(fk_Model *argObj, bool argFlag)
{
	switch(argObj->getShape()->getObjectType()) {
	  case FK_INDEXFACESET:
	  case FK_BLOCK:
	  case FK_CIRCLE:
	  case FK_SPHERE:
	  case FK_PRISM:
	  case FK_CONE:
		DrawIFSLineNormal(argObj, argFlag);
		break;

	  case FK_SOLID:
	  case FK_POLYGON:
	  case FK_POLYLINE:
	  case FK_CLOSEDLINE:
	  case FK_LINE:
		DrawSolidLineNormal(argObj, argFlag);
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
	DWORD				packedCol;

	list<fk_Edge *>::iterator			ite;
	list<fk_Edge *>::reverse_iterator	rite;


	solidP = (fk_Solid *)argObj->getShape();
	if(solidP->checkDB() == false) return;
	if(solidP->getNextE((fk_Edge *)NULL) == (fk_Edge *)NULL) return;

	if(solidP->GetECacheStatus() == false) {
		solidP->MakeECache();
	}

	edgeStack = solidP->GetECache();

	if(argFlg == true) {
		ModelColor = argObj->getInhLineColor();
		if(ModelColor == (fk_Color *)NULL) {
			ModelColor = argObj->getInhMaterial()->getAmbient();
		}
	} else {
		ModelColor = solidP->getMaterial(0)->getAmbient();
	}

	// m_lpD3DXLine->SetWidth((float)argObj->getWidth());

	packedCol = GetPackedColor(ModelColor);

	orgWidth = argObj->getWidth();
	
	if(reverseFlag == false) {
		for(ite = edgeStack->begin(); ite != edgeStack->end(); ++ite) {
			DrawSolidLineNormalElem(*ite, orgWidth, packedCol);
		}
	} else {
		for(rite = edgeStack->rbegin(); rite != edgeStack->rend(); ++rite) {
			DrawSolidLineNormalElem(*rite, orgWidth, packedCol);
		}
	}

	return;
}

void fk_LineDraw::DrawSolidLineNormalElem(fk_Edge *argE, double argOrgWidth, DWORD argPackedCol)
{
	double		trueWidth;

	trueWidth = argE->getDrawWidth();
	if(trueWidth < 0.0) {
		// m_lpD3DXLine->SetWidth((float)orgWidth);
		g_width = (float)argOrgWidth;
	} else {
		// m_lpD3DXLine->SetWidth((float)trueWidth);
		g_width = (float)trueWidth;
	}

	CommonLineDrawFunc(argE, false, argPackedCol);
}


void fk_LineDraw::DrawIFSLineNormal(fk_Model *argObj, bool argFlag)
{
	fk_IndexFaceSet		*ifsetP;
	int					ii;
	int					lineSize;
	fk_FVector			*pos;
	int					*edgeSet;
	fk_Color			*modelColor;
	DWORD				packedCol;
	float				lineWidth;
	LINECUSTOMVERTEX	tmpVertex;

	ifsetP = (fk_IndexFaceSet *)argObj->getShape();

	if(argFlag == true) {
		modelColor = argObj->getInhLineColor();
		if(modelColor == (fk_Color *)NULL) {
			modelColor = argObj->getInhMaterial()->getAmbient();
		}
	} else {
		modelColor = ifsetP->getMaterial(0)->getAmbient();
	}

	pos = &ifsetP->pos[0];
	edgeSet = &ifsetP->edgeSet[0];
	lineSize = int(ifsetP->edgeSet.size());
	lineWidth = (float)argObj->getWidth();
	packedCol = GetPackedColor(modelColor);

	// D3DXLine 使わずに書くならこんな感じ
	workCustomVertexArray.clear();
	for(ii = 0; ii < lineSize; ii++) {
		memcpy(&(tmpVertex.x), &pos[edgeSet[ii]], sizeof(fk_FVector));
		tmpVertex.color = packedCol;
		tmpVertex.psize = lineWidth;
		workCustomVertexArray.push_back(tmpVertex);
	}
	if(workCustomVertexArray.empty()) return;
	ref_lpD3DDEV->SetFVF(D3DFVF_LINECUSTOMVERTEX);
	ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_LINELIST, static_cast<UINT>(workCustomVertexArray.size()/2), &(workCustomVertexArray[0]), sizeof(LINECUSTOMVERTEX));

	/*
	workVertexArray.resize(2);
	m_lpD3DXLine->SetWidth(lineWidth);
	m_lpD3DXLine->Begin();
	for(ii = 0; ii < lineSize; ii+=2) {
		workVertexArray[0] = pos[edgeSet[ii]];
		workVertexArray[1] = pos[edgeSet[ii+1]];
		m_lpD3DXLine->DrawTransform((D3DXVECTOR3 *)&(workVertexArray[0]), 2, &m_transMat, packedCol);
	}
	m_lpD3DXLine->End();
	*/

	return;
}

void fk_LineDraw::CommonLineDrawFunc(fk_Edge *argE, bool argMode, DWORD argColor)
{
	fk_Vector			*vPos;
	fk_Curve			*curv;
	vector<fk_Vector>	*vArray;
	fk_Half				*lH, *rH;
	fk_Vertex			*lV, *rV;
	LINECUSTOMVERTEX	tmpVertex;
	int					ii;

	if((curv = argE->getCurveGeometry()) != (fk_Curve *)NULL) {

		curv->makeCache();
		int div = curv->getDiv();
		vArray = curv->getPosCache();

		workVertexArray.clear();
		for(ii = 0; ii <= div; ii++) {
			vPos = &((*vArray)[ii]);
			workVertexArray.push_back(fk_FVector());
			workVertexArray.back() = *vPos;
		}

		workCustomVertexArray.clear();
		for(ii = 0; ii < (int)workVertexArray.size(); ii++) {
			memcpy(&tmpVertex.x, &workVertexArray[ii], sizeof(fk_FVector));
			tmpVertex.color = argColor;
			tmpVertex.psize = g_width;
			workCustomVertexArray.push_back(tmpVertex);
		}
		ref_lpD3DDEV->SetFVF(D3DFVF_LINECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_LINELIST, static_cast<UINT>(workCustomVertexArray.size()/2), &workCustomVertexArray[0], sizeof(LINECUSTOMVERTEX));

		/*
		m_lpD3DXLine->Begin();
		m_lpD3DXLine->DrawTransform((D3DXVECTOR3 *)&(workVertexArray[0]), workVertexArray.size(), &m_transMat, argColor);
		m_lpD3DXLine->End();
		*/

	} else {

		rH = argE->getRightHalf();
		lH = argE->getLeftHalf();
		if(rH == (fk_Half *)NULL || lH == (fk_Half *)NULL) return;
		lV = lH->getVertex();
		rV = rH->getVertex();
		if(lV == (fk_Vertex *)NULL || rV == (fk_Vertex *)NULL) return;

		workVertexArray.resize(2);

		vPos = rV->GetPositionP();
		workVertexArray[0] = *vPos;

		vPos = lV->GetPositionP();
		workVertexArray[1] = *vPos;

		workCustomVertexArray.clear();
		for(ii = 0; ii < 2; ii++) {
			memcpy(&tmpVertex.x, &workVertexArray[ii], sizeof(fk_FVector));
			tmpVertex.color = argColor;
			tmpVertex.psize = g_width;
			workCustomVertexArray.push_back(tmpVertex);
		}
		ref_lpD3DDEV->SetFVF(D3DFVF_LINECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_LINELIST, 1, &workCustomVertexArray[0], sizeof(LINECUSTOMVERTEX));

		/*
		m_lpD3DXLine->Begin();
		m_lpD3DXLine->DrawTransform((D3DXVECTOR3 *)&(workVertexArray[0]), 2, &m_transMat, argColor);
		m_lpD3DXLine->End();
		*/
	}

	return;
}

void fk_LineDraw::PickLineDrawFunc(fk_Edge *argE, bool argMode)
{
	fk_Vector			*vPos;
	fk_Curve			*curv;
	vector<fk_Vector>	*vArray;
	fk_Half				*lH, *rH;
	fk_Vertex			*lV, *rV;

	if((curv = argE->getCurveGeometry()) != (fk_Curve *)NULL) {
		curv->makeCache();
		int div = curv->getDiv();
		vArray = curv->getPosCache();

		if(argMode == false) {
			glEnd();
		}

		glBegin(GL_LINE_STRIP);
		for(int ii = 0; ii <= div; ii++) {
			vPos = &((*vArray)[ii]);
			glVertex3dv((GLdouble *)&(vPos->x));
		}
		glEnd();

		if(argMode == false) {
			glBegin(GL_LINES);
		}

	} else {

		rH = argE->getRightHalf();
		lH = argE->getLeftHalf();
		if(rH == (fk_Half *)NULL || lH == (fk_Half *)NULL) return;
		lV = lH->getVertex();
		rV = rH->getVertex();
		if(lV == (fk_Vertex *)NULL || rV == (fk_Vertex *)NULL) return;

		if(argMode == true) {
			glBegin(GL_LINES);
		}

		vPos = rV->GetPositionP();
		glVertex3dv((GLdouble *)&(vPos->x));
		vPos = lV->GetPositionP();
		glVertex3dv((GLdouble *)&(vPos->x));

		if(argMode == true) {
			glEnd();
		}
	}

	return;
}
