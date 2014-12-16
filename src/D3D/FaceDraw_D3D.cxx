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
#include <FK/D3D/FaceDraw.h>
#include <FK/OpenGL.h>
#include <FK/IndexFace.h>
#include <FK/Solid.h>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Loop.h>

using namespace std;

typedef list<fk_Loop *>::iterator			loopIte;
typedef list<fk_Loop *>::reverse_iterator	loopRIte;

// 頂点の定義
struct FACECUSTOMVERTEX
{
	fk_FVector	p;	// 頂点座標
	fk_FVector	n;	// 法線
};
#define D3DFVF_FACECUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL)

// 描画用バッファ
static vector<FACECUSTOMVERTEX>	workVertexArray;
// vector<int>				workFaceIndexArray;

// ライトなし時のダミーライト
static D3DLIGHT9	dummyLight;

fk_FaceDraw::fk_FaceDraw(void)
{
	ref_lpD3DDEV = NULL;
	setArrayState(false);

	// ダミーライトの初期化
	ZeroMemory(&dummyLight, sizeof(D3DLIGHT9));
	dummyLight.Type = D3DLIGHT_DIRECTIONAL;
	dummyLight.Direction.x = 0.0f;
	dummyLight.Direction.y = 0.0f;
	dummyLight.Direction.z = 1.0f;

	return;
}

fk_FaceDraw::~fk_FaceDraw()
{
	workVertexArray.clear();
	return;
}

void fk_FaceDraw::setD3DDevice(LPDIRECT3DDEVICE9 argDev)
{
	ref_lpD3DDEV = argDev;
	return;
}

void fk_FaceDraw::setArrayState(bool argState)
{
	arrayState = argState;
	return;
}

void fk_FaceDraw::drawShapeFace(fk_Model *argObj, bool lightFlag,
								fk_DrawMode argDMode, bool argPickFlag)
{
	fk_MaterialMode	shapeMateMode;
	fk_MaterialMode	modelMateMode;
	bool			smoothMode;

	shapeMateMode = argObj->getShape()->getMaterialMode();
	modelMateMode = argObj->getMaterialMode();
	smoothMode = argObj->getSmoothMode();

	if((argDMode & FK_FRONTBACK_POLYMODE) == FK_FRONTBACK_POLYMODE) {
		ref_lpD3DDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	} else if((argDMode & FK_BACK_POLYMODE) == FK_BACK_POLYMODE) {
		ref_lpD3DDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	} else {
		ref_lpD3DDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
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
	switch(argObj->getShape()->getObjectType()) {
	  case FK_INDEXFACESET:
	  case FK_BLOCK:
	  case FK_CIRCLE:
	  case FK_SPHERE:
	  case FK_PRISM:
	  case FK_CONE:
		DrawIFSFacePick(argObj);
		break;

	  case FK_SOLID:
	  case FK_POLYGON:
	  case FK_POLYLINE:
	  case FK_CLOSEDLINE:
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

	solidP = (fk_Solid *)argObj->getShape();
	if(solidP->checkDB() == false) return;
	if(solidP->getNextL((fk_Loop *)NULL) == (fk_Loop *)NULL) return;

	if(solidP->GetLCacheStatus() == false) {
		solidP->MakeLCache();
	}

	loopStack = solidP->GetLCache();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

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

	glPushName(argL->getID()*3);

	if(argL->isTesselated() == true) {
		tesseVertexArray = argL->GetTesselateVertex();
		tesseIDArray = argL->GetTesselateIndex();

		glBegin(GL_TRIANGLES);
		for(unsigned int i = 0; i < tesseIDArray->size(); i++) {
			tmpPosP = tesseVertexArray->at(tesseIDArray->at(i))->GetPositionP();
			glVertex3dv((GLdouble *)&(tmpPosP->x));
		}
		glEnd();
	} else {
		glBegin(GL_POLYGON);
		startH = curH = argL->getOneHalf();

		do {
			curV = curH->getVertex();
			tmpPosP = curV->GetPositionP(); 
			glVertex3dv((GLdouble *)&(tmpPosP->x));
			curH = curH->getNextHalf();
		} while(startH != curH);

		glEnd();
	}

	glPopName();

}

void fk_FaceDraw::DrawIFSFacePick(fk_Model *argObj)
{
	fk_IndexFaceSet		*ifsP;
	int					ii, ij;
	int					pNum;
	fk_FVector			*pos;
	int					*ifs;

	ifsP = (fk_IndexFaceSet *)argObj->getShape();

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

	for(ii = 0; ii < ifsP->faceSize; ii++) {
		glPushName(ii*3);
		glBegin(GL_POLYGON);
		for(ij = 0; ij < pNum; ij++) {
			glVertex3fv((GLfloat *)&pos[ifs[pNum*ii+ij]]);
		}
		glEnd();
		glPopName();
	}

	return;
}

void fk_FaceDraw::DrawShapeFaceMaterial(fk_Model *argObj, bool argLightFlag)
{
	// ライト無し時でもアンビエントライトを表現するためにライト ON
	ref_lpD3DDEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	if(argLightFlag == true) {
		ref_lpD3DDEV->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));
	} else {
		ref_lpD3DDEV->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));
		ref_lpD3DDEV->SetLight(0, &dummyLight);
		ref_lpD3DDEV->LightEnable(0, TRUE);
	}

	switch(argObj->getShape()->getObjectType()) {
	  case FK_INDEXFACESET:
	  case FK_BLOCK:
	  case FK_CIRCLE:
	  case FK_SPHERE:
	  case FK_PRISM:
	  case FK_CONE:
		DrawIFSFaceMaterial(argObj, argLightFlag);
		break;

	  case FK_SOLID:
	  case FK_POLYGON:
	  case FK_POLYLINE:
	  case FK_CLOSEDLINE:
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


	solidP = (fk_Solid *)argObj->getShape();
	if(solidP->checkDB() == false) return;
	if(solidP->getNextL((fk_Loop *)NULL) == (fk_Loop *)NULL) return;

	if(solidP->GetLCacheStatus() == false) {
		solidP->MakeLCache();
	}

	loopStack = solidP->GetLCache();

	oldMateID = -2;
	ref_lpD3DDEV->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

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
	fk_Vector				*tmpNormP;
	int						retMateID, curMateID;
	fk_Surface				*surf;
	unsigned int			i;
	vector<fk_Vertex *>		*tesseVertexArray;
	vector<int>				*tesseIDArray;
	FACECUSTOMVERTEX		tmpVertex;


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
			commonMateSet(ref_lpD3DDEV, argObj, argLightFlag, true);
			retMateID = FK_UNDEFINED;
		} else {
			localMateSet(ref_lpD3DDEV, &((*argMatV)[curMateID]), argLightFlag);
			retMateID = curMateID;
		}
	}

	if((surf = argL->getSurfGeometry()) != (fk_Surface *)NULL) {
		DrawSurface(surf);
	} else if(argL->isTesselated() == true) {
		if((tmpNormP = argL->getNormal()) == (fk_Vector *)NULL) {
			return retMateID;
		}

		tesseVertexArray = argL->GetTesselateVertex();
		tesseIDArray = argL->GetTesselateIndex();

		workVertexArray.clear();
		for(i = 0; i < tesseIDArray->size(); i++) {
			tmpVertex.n = *tmpNormP;
			tmpVertex.p = *(tesseVertexArray->at(tesseIDArray->at(i))->GetPositionP());
			workVertexArray.push_back(tmpVertex);
		}
		if(workVertexArray.empty()) return retMateID;
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLELIST, static_cast<UINT>(workVertexArray.size()/3), &(workVertexArray[0]), sizeof(FACECUSTOMVERTEX));
	} else {
		if((tmpNormP = argL->getNormal()) == (fk_Vector *)NULL) {
			return retMateID;
		}
		startH = curH = argL->getOneHalf();

		workVertexArray.clear();
		do {
			curV = curH->getVertex();
			tmpVertex.n = *tmpNormP;
			tmpVertex.p = *(curV->GetPositionP());
			curH = curH->getNextHalf();
			workVertexArray.push_back(tmpVertex);
		} while(startH != curH);
		if(workVertexArray.empty()) return retMateID;
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, static_cast<UINT>(workVertexArray.size()-2), &(workVertexArray[0]), sizeof(FACECUSTOMVERTEX));
	}

	return retMateID;
}


void fk_FaceDraw::DrawIFSFaceMaterial(fk_Model *argObj, bool argLightFlag)
{
	fk_IndexFaceSet		*ifsP;
	int					pNum;
	fk_FVector			*pos, *pNorm;
	int					*ifs;
	int					ii, ij;
	int					oldMateID, curMateID, paletteSize;
	vector<fk_Material>	*matV;

	ifsP = (fk_IndexFaceSet *)argObj->getShape();

	curMateID = FK_UNDEFINED;
	oldMateID = -2;

	ref_lpD3DDEV->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	ifsP->ModifyPNorm();
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
	pNorm = &ifsP->pNorm[0];
	ifs = &ifsP->ifs[0];

	paletteSize = ifsP->getPaletteSize();
	matV = ifsP->getMaterialVector();

	if(ifsP->colorFlg == false) commonMateSet(ref_lpD3DDEV, argObj, argLightFlag, true);

	for(ii = 0; ii < ifsP->faceSize; ii++) {
		if(ifsP->colorFlg == true) {
			curMateID = ifsP->colorID[ii];
			if(curMateID < 0 || curMateID >= paletteSize) {
				curMateID = FK_UNDEFINED;
			}
			if(curMateID != oldMateID) {
				if(curMateID == FK_UNDEFINED) {
					commonMateSet(ref_lpD3DDEV, argObj, argLightFlag, true);
					oldMateID = FK_UNDEFINED;
				} else {
					localMateSet(ref_lpD3DDEV, &((*matV)[curMateID]),
								 argLightFlag);
					oldMateID = curMateID;
				}
			}
		}

		workVertexArray.resize(pNum);
		for(ij = 0; ij < pNum; ij++) {
			workVertexArray[ij].n = pNorm[ii];
			workVertexArray[ij].p = pos[ifs[pNum*ii+ij]];
		}
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		switch(pNum) {
		  case 3:
			ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, &(workVertexArray[0]), sizeof(FACECUSTOMVERTEX));
			break;

		  case 4:
			ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &(workVertexArray[0]), sizeof(FACECUSTOMVERTEX));
			break;
		}
	}

	return;
}

void fk_FaceDraw::DrawShapeFaceSmooth(fk_Model *argObj,
									bool argLightFlag, bool argNodeFlag)
{
	ref_lpD3DDEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	if(argLightFlag == true) {
		ref_lpD3DDEV->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));
	} else {
		ref_lpD3DDEV->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));
		ref_lpD3DDEV->SetLight(0, &dummyLight);
		ref_lpD3DDEV->LightEnable(0, TRUE);
	}

	switch(argObj->getShape()->getObjectType()) {
	  case FK_INDEXFACESET:
	  case FK_BLOCK:
	  case FK_CIRCLE:
	  case FK_SPHERE:
	  case FK_PRISM:
	  case FK_CONE:
		DrawIFSFaceSmooth(argObj, argLightFlag, argNodeFlag);
		break;

	  case FK_SOLID:
	  case FK_POLYGON:
	  case FK_POLYLINE:
	  case FK_CLOSEDLINE:
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


	solidP = (fk_Solid *)argObj->getShape();
	if(solidP->checkDB() == false) return;
	if(solidP->getNextL((fk_Loop *)NULL) == (fk_Loop *)NULL) return;

	if(solidP->GetLCacheStatus() == false) {
		solidP->MakeLCache();
	}

	loopStack = solidP->GetLCache();

	commonMateSet(ref_lpD3DDEV, argObj, argLightFlag, argNodeFlg);

	ref_lpD3DDEV->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

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
	FACECUSTOMVERTEX	tmpVertex;


	if((surf = argL->getSurfGeometry()) != (fk_Surface *)NULL) {
		DrawSurface(surf);
	} else {
		workVertexArray.clear();
		startH = curH = argL->getOneHalf();
		do {
			curV = curH->getVertex();
			tmpNorm = curV->GetNormalP();
			tmpPos = curV->GetPositionP(); 
			if(tmpNorm == (fk_Vector *)NULL ||
			   tmpPos == (fk_Vector *)NULL) {
				continue;
			}
			tmpVertex.n = *tmpNorm;
			tmpVertex.p = *tmpPos;
			curH = curH->getNextHalf();
			workVertexArray.push_back(tmpVertex);
		} while(startH != curH);
		if(workVertexArray.empty()) return;
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, static_cast<UINT>(workVertexArray.size()-2), &(workVertexArray[0]), sizeof(FACECUSTOMVERTEX));
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
	int					ii, ij;
	FACECUSTOMVERTEX	tmpVertex;

	ifsP = (fk_IndexFaceSet *)argObj->getShape();

	commonMateSet(ref_lpD3DDEV, argObj, argLightFlag, argNodeFlag);
	ref_lpD3DDEV->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	ifsP->ModifyVNorm();
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
	vNorm = &ifsP->vNorm[0];
	ifs = &ifsP->ifs[0];

	workVertexArray.clear();
	switch(pNum) {
	  case 3:
		for(ii = 0; ii < ifsP->faceSize; ii++) {
			for(ij = 0; ij < pNum; ij++) {
				tmpVertex.p = pos[ifs[pNum*ii+ij]];
				tmpVertex.n = vNorm[ifs[pNum*ii+ij]];
				workVertexArray.push_back(tmpVertex);
			}
		}
		if(workVertexArray.empty()) return;
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLELIST, ifsP->faceSize, &(workVertexArray[0]), sizeof(FACECUSTOMVERTEX));
		break;

	  case 4:
		for(ii = 0; ii < ifsP->faceSize; ii++) {
			for(ij = 0; ij < pNum-1; ij++) {
				tmpVertex.p = pos[ifs[pNum*ii+ij]];
				tmpVertex.n = vNorm[ifs[pNum*ii+ij]];
				workVertexArray.push_back(tmpVertex);
			}
			tmpVertex.p = pos[ifs[pNum*ii+0]];
			tmpVertex.n = vNorm[ifs[pNum*ii+0]];
			workVertexArray.push_back(tmpVertex);
			tmpVertex.p = pos[ifs[pNum*ii+2]];
			tmpVertex.n = vNorm[ifs[pNum*ii+2]];
			workVertexArray.push_back(tmpVertex);
			tmpVertex.p = pos[ifs[pNum*ii+3]];
			tmpVertex.n = vNorm[ifs[pNum*ii+3]];
			workVertexArray.push_back(tmpVertex);
		}
		if(workVertexArray.empty()) return;
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLELIST, ifsP->faceSize*2, &(workVertexArray[0]), sizeof(FACECUSTOMVERTEX));
		/*
		workFaceIndexArray.clear();
		for(ii = 0; ii < ifsP->faceSize; ii++) {
			for(ij = 0; ij < pNum; ij++) {
				tmpVertex.p = pos[ifs[pNum*ii+ij]];
				tmpVertex.n = vNorm[ifs[pNum*ii+ij]];
				workVertexArray.push_back(tmpVertex);
			}
			workFaceIndexArray.push_back(pNum*ii+0);
			workFaceIndexArray.push_back(pNum*ii+1);
			workFaceIndexArray.push_back(pNum*ii+2);
			workFaceIndexArray.push_back(pNum*ii+0);
			workFaceIndexArray.push_back(pNum*ii+2);
			workFaceIndexArray.push_back(pNum*ii+3);
		}
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		ref_lpD3DDEV->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST, 0, workVertexArray.size(), ifsP->faceSize*2, &(workFaceIndexArray[0]), D3DFMT_INDEX32, 
			&(workVertexArray[0]), sizeof(FACECUSTOMVERTEX)
		);
		*/
		break;
	}
	return;
}

void fk_FaceDraw::DrawShapeFaceNormal(fk_Model *argObj,
									bool argLightFlag, bool argNodeFlag)
{
	ref_lpD3DDEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	if(argLightFlag == true) {
		ref_lpD3DDEV->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));
	} else {
		ref_lpD3DDEV->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));
		ref_lpD3DDEV->SetLight(0, &dummyLight);
		ref_lpD3DDEV->LightEnable(0, TRUE);
	}

	switch(argObj->getShape()->getObjectType()) {
	  case FK_INDEXFACESET:
	  case FK_BLOCK:
	  case FK_CIRCLE:
	  case FK_SPHERE:
	  case FK_PRISM:
	  case FK_CONE:
		DrawIFSFaceNormal(argObj, argLightFlag, argNodeFlag);
		break;

	  case FK_SOLID:
	  case FK_POLYGON:
	  case FK_POLYLINE:
	  case FK_CLOSEDLINE:
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


	solidP = (fk_Solid *)argObj->getShape();
	if(solidP->checkDB() == false) return;
	if(solidP->getNextL((fk_Loop *)NULL) == (fk_Loop *)NULL) return;

	if(solidP->GetLCacheStatus() == false) {
		solidP->MakeLCache();
	}

	loopStack = solidP->GetLCache();

	commonMateSet(ref_lpD3DDEV, argObj, argLightFlag, argNodeFlg);

	ref_lpD3DDEV->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

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
	fk_Vector			*tmpNormP;
	vector<fk_Vertex *>	*tesseVertexArray;
	vector<int>			*tesseIDArray;
	fk_Surface			*surf;
	FACECUSTOMVERTEX	tmpVertex;

	if((surf = argL->getSurfGeometry()) != (fk_Surface *)NULL) {
		DrawSurface(surf);
	} else if(argL->isTesselated() == true) {
		if((tmpNormP = argL->getNormal()) == (fk_Vector *)NULL) return;
		tesseVertexArray = argL->GetTesselateVertex();
		tesseIDArray = argL->GetTesselateIndex();

		workVertexArray.clear();
		for(unsigned int i = 0; i < tesseIDArray->size(); i++) {
			tmpVertex.n = *tmpNormP;
			tmpVertex.p = *(tesseVertexArray->at(tesseIDArray->at(i))->GetPositionP());
			workVertexArray.push_back(tmpVertex);
		}
		if(workVertexArray.empty()) return;
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLELIST, static_cast<UINT>(workVertexArray.size()/3), &(workVertexArray[0]), sizeof(FACECUSTOMVERTEX));

	} else {
		if((tmpNormP = argL->getNormal()) == (fk_Vector *)NULL) return;
		startH = curH = argL->getOneHalf();

		workVertexArray.clear();
		do {
			curV = curH->getVertex();
			tmpVertex.n = *tmpNormP;
			tmpVertex.p = *(curV->GetPositionP());
			curH = curH->getNextHalf();
			workVertexArray.push_back(tmpVertex);
		} while(startH != curH);
		if(workVertexArray.empty()) return;
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, static_cast<UINT>(workVertexArray.size()-2), &(workVertexArray[0]), sizeof(FACECUSTOMVERTEX));

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
	FACECUSTOMVERTEX	tmpVertex;

	ifsP = (fk_IndexFaceSet *)argObj->getShape();

	commonMateSet(ref_lpD3DDEV, argObj, argLightFlag, argNodeFlag);
	ref_lpD3DDEV->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	ifsP->ModifyPNorm();
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
	pNorm = &ifsP->pNorm[0];
	ifs = &ifsP->ifs[0];

	workVertexArray.clear();
	switch(pNum) {
	  case 3:
		for(ii = 0; ii < ifsP->faceSize; ii++) {
			for(ij = 0; ij < pNum; ij++) {
				tmpVertex.p = pos[ifs[pNum*ii+ij]];
				tmpVertex.n = pNorm[ii];
				workVertexArray.push_back(tmpVertex);
			}
		}
		if(workVertexArray.empty()) return;
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLELIST, ifsP->faceSize, &(workVertexArray[0]), sizeof(FACECUSTOMVERTEX));
		break;

	  case 4:
		for(ii = 0; ii < ifsP->faceSize; ii++) {
			for(ij = 0; ij < pNum-1; ij++) {
				tmpVertex.p = pos[ifs[pNum*ii+ij]];
				tmpVertex.n = pNorm[ii];
				workVertexArray.push_back(tmpVertex);
			}
			tmpVertex.p = pos[ifs[pNum*ii+0]];
			tmpVertex.n = pNorm[ii];
			workVertexArray.push_back(tmpVertex);
			tmpVertex.p = pos[ifs[pNum*ii+2]];
			tmpVertex.n = pNorm[ii];
			workVertexArray.push_back(tmpVertex);
			tmpVertex.p = pos[ifs[pNum*ii+3]];
			tmpVertex.n = pNorm[ii];
			workVertexArray.push_back(tmpVertex);
		}
		if(workVertexArray.empty()) return;
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLELIST, ifsP->faceSize*2, &(workVertexArray[0]), sizeof(FACECUSTOMVERTEX));
		/*
		workFaceIndexArray.clear();
		for(ii = 0; ii < ifsP->faceSize; ii++) {
			for(ij = 0; ij < pNum; ij++) {
				tmpVertex.p = pos[ifs[pNum*ii+ij]];
				tmpVertex.n = pNorm[ii];
				workVertexArray.push_back(tmpVertex);
			}
			workFaceIndexArray.push_back(pNum*ii+0);
			workFaceIndexArray.push_back(pNum*ii+1);
			workFaceIndexArray.push_back(pNum*ii+2);
			workFaceIndexArray.push_back(pNum*ii+0);
			workFaceIndexArray.push_back(pNum*ii+2);
			workFaceIndexArray.push_back(pNum*ii+3);
		}
		ref_lpD3DDEV->SetFVF(D3DFVF_FACECUSTOMVERTEX);
		ref_lpD3DDEV->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST, 0, workVertexArray.size(), ifsP->faceSize*2, &(workFaceIndexArray[0]), D3DFMT_INDEX32, 
			&(workVertexArray[0]), sizeof(FACECUSTOMVERTEX)
		);
		*/
		break;
	}

	return;
}

void fk_FaceDraw::DrawSurface(fk_Surface *)
{
	return;
}


void fk_FaceDraw::commonMateSet(LPDIRECT3DDEVICE9 argDev, fk_Model *argObj, bool lightFlag, bool matFlag)
{
	D3DMATERIAL9	tmpMate;

	fk_Shape	*shapeP;
	fk_Material	*curMat;

	ZeroMemory(&tmpMate, sizeof(D3DMATERIAL9));

	shapeP = argObj->getShape();

	if(matFlag == true || shapeP == (fk_Shape *)NULL) {
		curMat = argObj->getInhMaterial();
	} else {
		curMat = &(*shapeP->getMaterialVector())[0];
	}

	memcpy(&(tmpMate.Ambient), curMat->getAmbient()->col, sizeof(D3DCOLORVALUE));
	memcpy(&(tmpMate.Diffuse), curMat->getDiffuse()->col, sizeof(D3DCOLORVALUE));
	memcpy(&(tmpMate.Emissive), curMat->getEmission()->col, sizeof(D3DCOLORVALUE));
	memcpy(&(tmpMate.Specular), curMat->getSpecular()->col, sizeof(D3DCOLORVALUE));
	tmpMate.Power = curMat->getShininess();

	/*
	tmpMate.Ambient.a = 1.0f;
	tmpMate.Emissive.a = 1.0f;
	tmpMate.Specular.a = tmpMate.Power;
	*/

	argDev->SetMaterial(&tmpMate);
	return;
}

void fk_FaceDraw::localMateSet(LPDIRECT3DDEVICE9 argDev, fk_Material *argMaterial, bool lightFlag)
{
	D3DMATERIAL9	tmpMate;

	ZeroMemory(&tmpMate, sizeof(D3DMATERIAL9));

	memcpy(&(tmpMate.Ambient), argMaterial->getAmbient()->col, sizeof(D3DCOLORVALUE));
	memcpy(&(tmpMate.Diffuse), argMaterial->getDiffuse()->col, sizeof(D3DCOLORVALUE));
	memcpy(&(tmpMate.Emissive), argMaterial->getEmission()->col, sizeof(D3DCOLORVALUE));
	memcpy(&(tmpMate.Specular), argMaterial->getSpecular()->col, sizeof(D3DCOLORVALUE));
	tmpMate.Power = argMaterial->getShininess();

	/*
	tmpMate.Ambient.a = 1.0f;
	tmpMate.Emissive.a = 1.0f;
	tmpMate.Specular.a = tmpMate.Power;
	*/

	argDev->SetMaterial(&tmpMate);
	return;
}
