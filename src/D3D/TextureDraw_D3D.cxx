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
#include <FK/D3D/TextureDraw.h>
#include <FK/IFSTexture.h>
#include <FK/Model.h>
#include <FK/D3D/FaceDraw.h>

#include <FK/Error.H>
#include <algorithm>

using namespace std;

// 頂点の定義
struct TEXTURECUSTOMVERTEX
{
    fk_FVector	p;	// 頂点座標
    fk_FVector	n;	// 法線
	fk_TexCoord	uv;	// テクスチャ座標
};
#define D3DFVF_TEXTURECUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

// 描画用バッファ
static vector<TEXTURECUSTOMVERTEX>	workVertexArray;
// vector<int>				workTexIndexArray;

// テクスチャ管理配列
vector<LPDIRECT3DTEXTURE9>	fk_TextureDraw::texObjArray(1);
vector<fk_Dimension>		fk_TextureDraw::texSizeArray(1);
vector<fk_TexID>			fk_TextureDraw::texNameArray;
unsigned long				fk_TextureDraw::texLoadedSize = 0;
vector<fk_Image *>			fk_TextureDraw::texImageArray;

// ライトなし時のダミーライト
static D3DLIGHT9	dummyLight;


fk_TextureDraw::fk_TextureDraw(void)
{
	ref_lpD3DDEV = NULL;
	texObjArray[0] = NULL;
	texSizeArray[0].set(0, 0);
	setArrayState(false);
	setBindMode(false);
	oldTexID = 0;

	ZeroMemory(&dummyLight, sizeof(D3DLIGHT9));
	dummyLight.Type = D3DLIGHT_DIRECTIONAL;
	dummyLight.Direction.x = 0.0f;
	dummyLight.Direction.y = 0.0f;
	dummyLight.Direction.z = 1.0f;

	return;
}

fk_TextureDraw::~fk_TextureDraw()
{
	clearTextureMemory();
	workVertexArray.clear();
	return;
}

void fk_TextureDraw::setD3DDevice(LPDIRECT3DDEVICE9 argDev)
{
	ref_lpD3DDEV = argDev;
	return;
}

void fk_TextureDraw::setArrayState(bool argState)
{
	arrayState = argState;
	return;
}

void fk_TextureDraw::startUp(void)
{
	string		str;

	oldTexID = 0;
	return;
}

void fk_TextureDraw::drawTextureObj(fk_Model *argObj, bool argLightFlag, bool argPickFlag)
{
	fk_Texture		*texObj;
	int				mateID = -2;
	fk_TexID		texID;

	if((argObj->getDrawMode() & FK_TEXTUREMODE) == FK_NONEMODE) return;

	texObj = (fk_Texture *)argObj->getShape();

	if(texObj->getBufferSize() == (fk_Dimension *)NULL) return;

	// ピックモードが ON の場合
	if(argPickFlag == true) {
		// テクスチャの種類の選択
		switch(texObj->getObjectType()) {
		case FK_RECTTEXTURE:
			DrawRectTexturePick((fk_RectTexture *)texObj);
			break;

		case FK_TRITEXTURE:
			DrawTriTexturePick((fk_TriTexture *)texObj);
			break;

		case FK_MESHTEXTURE:
			DrawMeshTexturePick((fk_MeshTexture *)texObj);
			break;

		case FK_IFSTEXTURE:
			DrawIFSTexturePick((fk_IFSTexture *)texObj);
			break;

		default:
			break;
		}
		return;
	}

	// ライトの状態に応じてアンビエントライトの設定を変更
	ref_lpD3DDEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	if(argLightFlag == true) {
		ref_lpD3DDEV->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));
	} else {
		ref_lpD3DDEV->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255));
		ref_lpD3DDEV->SetLight(0, &dummyLight);
		ref_lpD3DDEV->LightEnable(0, TRUE);
	}

	// マテリアルモードによるマテリアルの決定
	switch(texObj->getMaterialMode()) {
	  case FK_CHILD_MODE:
		mateID = texObj->getObjMaterialID();
		break;

	  case FK_NONE_MODE:
		return;

	  default:
		mateID = FK_UNDEFINED;
		break;
	}

	if(mateID == FK_UNDEFINED) {
		fk_FaceDraw::commonMateSet(ref_lpD3DDEV, argObj, argLightFlag, true);
	} else {
		fk_FaceDraw::localMateSet(ref_lpD3DDEV, texObj->getMaterial(mateID), argLightFlag);
	}

	// (必要なら)テクスチャオブジェクトの生成
	texID = texObj->GetTexID();
	if(texID > texNameArray.size() || texID == 0) {
		GenTextureObj(texObj);
	} else if(texObj->GetInitFlag() == true) {
		ReplaceTextureObj(texObj);
	}

	// テクスチャ表示の初期化
	InitTextureEnv(texObj);

	// rita_ext: カスタムテクスチャ描画処理の実行ポイント
	argObj->connectShader(texObj->GetTexID());

	// テクスチャの種類の選択
	switch(texObj->getObjectType()) {
	  case FK_RECTTEXTURE:
		DrawRectTextureObj((fk_RectTexture *)texObj);
		break;

	  case FK_TRITEXTURE:
		DrawTriTextureObj((fk_TriTexture *)texObj);
		break;

	  case FK_MESHTEXTURE:
		DrawMeshTextureObj((fk_MeshTexture *)texObj);
		break;

	  case FK_IFSTEXTURE:
		DrawIFSTextureObj((fk_IFSTexture *)texObj);

	  default:
		break;
	}

	// これを付けると複数テクスチャの共存ができない
	// ref_lpD3DDEV->SetTexture(0, NULL);

	if(argLightFlag == true) {
	    ref_lpD3DDEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	} else {
	    ref_lpD3DDEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	return;
}

void fk_TextureDraw::DrawRectTextureObj(fk_RectTexture *argTexObj)
{
	fk_TexCoord		texSize, startParam, endParam;
	float			tmpX, tmpY;

	const fk_Dimension *imageSize = argTexObj->getImageSize();
	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == (fk_Dimension *)NULL) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	if(argTexObj->getRepeatMode() == true) {
		startParam.set(0.0, 0.0);
		endParam = argTexObj->getRepeatParam();
	} else {
		double wScale = double(imageSize->w)/double(bufSize->w);
		double hScale = double(imageSize->h)/double(bufSize->h);
		startParam.set(wScale * argTexObj->texCoord[0].x,
					   hScale * argTexObj->texCoord[0].y);
		endParam.set(wScale * argTexObj->texCoord[1].x,
					 hScale * argTexObj->texCoord[1].y);
	}

	texSize = argTexObj->getTextureSize();
	tmpX = float(texSize.x/2.0);
	tmpY = float(texSize.y/2.0);

	workVertexArray.resize(4);

	workVertexArray[0].n.x = 0.0f;	workVertexArray[0].n.y = 0.0f;	workVertexArray[0].n.z = 1.0f;
	workVertexArray[0].p.x = -tmpX;	workVertexArray[0].p.y = -tmpY;	workVertexArray[0].p.z = 0.0f;
	workVertexArray[0].uv.x = startParam.x;		workVertexArray[0].uv.y = startParam.y;

	workVertexArray[1].n.x = 0.0f;	workVertexArray[1].n.y = 0.0f;	workVertexArray[1].n.z = 1.0f;
	workVertexArray[1].p.x =  tmpX;	workVertexArray[1].p.y = -tmpY;	workVertexArray[1].p.z = 0.0f;
	workVertexArray[1].uv.x = endParam.x;		workVertexArray[1].uv.y = startParam.y;

	workVertexArray[2].n.x = 0.0f;	workVertexArray[2].n.y = 0.0f;	workVertexArray[2].n.z = 1.0f;
	workVertexArray[2].p.x =  tmpX;	workVertexArray[2].p.y =  tmpY;	workVertexArray[2].p.z = 0.0f;
	workVertexArray[2].uv.x = endParam.x;		workVertexArray[2].uv.y = endParam.y;

	workVertexArray[3].n.x = 0.0f;	workVertexArray[3].n.y = 0.0f;	workVertexArray[3].n.z = 1.0f;
	workVertexArray[3].p.x = -tmpX;	workVertexArray[3].p.y =  tmpY;	workVertexArray[3].p.z = 0.0f;
	workVertexArray[3].uv.x = startParam.x;		workVertexArray[3].uv.y = endParam.y;

	ref_lpD3DDEV->SetFVF(D3DFVF_TEXTURECUSTOMVERTEX);
	ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &(workVertexArray[0]), sizeof(TEXTURECUSTOMVERTEX));

	return;
}

void fk_TextureDraw::DrawTriTextureObj(fk_TriTexture *argTexObj)
{
	fk_Vector		*pos;
	fk_TexCoord		*coord;
	double			wScale, hScale;
	register int	counter;
	fk_Vector		norm;

	const fk_Dimension *imageSize = argTexObj->getImageSize();
	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == (fk_Dimension *)NULL) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	wScale = double(imageSize->w)/double(bufSize->w);
	hScale = double(imageSize->h)/double(bufSize->h);

	pos = argTexObj->getPos();
	coord = argTexObj->getCoord();

	norm = (pos[1] - pos[0]) ^ (pos[2] - pos[0]);
	if(norm.normalize() == false) {
		fk_PutError("fk_Window", "DrawTriTextureObj", 1,
					"Triangle Normal Vector Error.");
		return;
	}

	workVertexArray.resize(3);
	for(counter = 0; counter < 3; counter++) {
		workVertexArray[counter].n = norm;
		workVertexArray[counter].uv.x = coord[counter].x * float(wScale);
		workVertexArray[counter].uv.y = coord[counter].y * float(hScale);
		workVertexArray[counter].p = pos[counter];
	}
	ref_lpD3DDEV->SetFVF(D3DFVF_TEXTURECUSTOMVERTEX);
	ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, &(workVertexArray[0]), sizeof(TEXTURECUSTOMVERTEX));

	return;
}

void fk_TextureDraw::DrawMeshTextureObj(fk_MeshTexture *argTexObj)
{
	fk_Vector			*posArray;
	vector<fk_TexCoord>	*coordArray;
	double				wScale, hScale;
	int					triNum;
	register int		ii, ij;
	fk_Vector			norm;

	TEXTURECUSTOMVERTEX	tmpVertex;

	// rita: メッシュ枚数チェックを先に
	triNum = argTexObj->getTriNum();
	if(triNum <= 0) return;

	const fk_Dimension *imageSize = argTexObj->getImageSize();
	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == (fk_Dimension *)NULL) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	wScale = double(imageSize->w)/double(bufSize->w);
	hScale = double(imageSize->h)/double(bufSize->h);

	posArray = &(argTexObj->getPos()->at(0));
	coordArray = argTexObj->getCoord();

	workVertexArray.clear();
	for(ii = 0; ii < triNum; ii++) {
		norm = (posArray[ii*3 + 1] - posArray[ii*3]) ^
				(posArray[ii*3 + 2] - posArray[ii*3]);
		if(norm.normalize() == false) {
			fk_PutError("fk_Window", "DrawMeshTextureObj", 1,
						"Normal Vector Error.");
			continue;
		}

		for(ij = 0; ij < 3; ij++) {
			tmpVertex.n = norm;
			tmpVertex.uv.x = (*coordArray)[ii*3+ij].x * float(wScale);
			tmpVertex.uv.y = (*coordArray)[ii*3+ij].y * float(hScale);
			tmpVertex.p = posArray[ii*3+ij];
			workVertexArray.push_back(tmpVertex);
		}
	}
	// メッシュ枚数チェック済み
	ref_lpD3DDEV->SetFVF(D3DFVF_TEXTURECUSTOMVERTEX);
	ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLELIST, static_cast<UINT>(workVertexArray.size()/3), &(workVertexArray[0]), sizeof(TEXTURECUSTOMVERTEX));

	return;
}

void fk_TextureDraw::DrawIFSTextureObj(fk_IFSTexture *argTexObj)
{
	fk_IndexFaceSet		*ifsP;
	fk_FVector			*pos, *vNorm;
	int					*ifs;
	int					pNum;
	fk_TexCoord			*texCoord;
	int					ii, ij, index;

	TEXTURECUSTOMVERTEX	tmpVertex;

	// const fk_Dimension *imageSize = argTexObj->getImageSize();
	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == (fk_Dimension *)NULL) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	ifsP = argTexObj->getIFS();
	if(ifsP->faceSize <= 0) return;

	if(ifsP->modifyFlg == true) {
		ifsP->ModifyVNorm();
	}

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

	ref_lpD3DDEV->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	pos = &ifsP->pos[0];
	vNorm = &ifsP->vNorm[0];
	ifs = &ifsP->ifs[0];
	texCoord = &(argTexObj->coordArray[0]);

	workVertexArray.clear();
	switch(pNum) {
	  case 3:
		for(ii = 0; ii < ifsP->faceSize; ii++) {
			for(ij = 0; ij < pNum; ij++) {
				index = ifs[pNum*ii+ij];
				tmpVertex.p = pos[index];
				tmpVertex.n = vNorm[index];
				tmpVertex.uv = texCoord[index];
				workVertexArray.push_back(tmpVertex);
			}
		}
		ref_lpD3DDEV->SetFVF(D3DFVF_TEXTURECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLELIST, ifsP->faceSize, &(workVertexArray[0]), sizeof(TEXTURECUSTOMVERTEX));
		break;

	  case 4:
		for(ii = 0; ii < ifsP->faceSize; ii++) {
			for(ij = 0; ij < pNum-1; ij++) {
				index = ifs[pNum*ii+ij];
				tmpVertex.p = pos[index];
				tmpVertex.n = vNorm[index];
				tmpVertex.uv = texCoord[index];
				workVertexArray.push_back(tmpVertex);
			}
			index = ifs[pNum*ii+0];
			tmpVertex.p = pos[index];
			tmpVertex.n = vNorm[index];
			tmpVertex.uv = texCoord[index];
			workVertexArray.push_back(tmpVertex);
			index = ifs[pNum*ii+2];
			tmpVertex.p = pos[index];
			tmpVertex.n = vNorm[index];
			tmpVertex.uv = texCoord[index];
			workVertexArray.push_back(tmpVertex);
			index = ifs[pNum*ii+3];
			tmpVertex.p = pos[index];
			tmpVertex.n = vNorm[index];
			tmpVertex.uv = texCoord[index];
			workVertexArray.push_back(tmpVertex);
		}
		ref_lpD3DDEV->SetFVF(D3DFVF_TEXTURECUSTOMVERTEX);
		ref_lpD3DDEV->DrawPrimitiveUP(D3DPT_TRIANGLELIST, ifsP->faceSize*2, &(workVertexArray[0]), sizeof(TEXTURECUSTOMVERTEX));
		/*
		workTexIndexArray.clear();
		for(ii = 0; ii < ifsP->faceSize; ii++) {
			for(ij = 0; ij < pNum; ij++) {
				index = ifs[pNum*ii+ij];
				tmpVertex.p = pos[index];
				tmpVertex.n = vNorm[index];
				tmpVertex.uv = texCoord[index];
				workVertexArray.push_back(tmpVertex);
			}
			workTexIndexArray.push_back(pNum*ii+0);
			workTexIndexArray.push_back(pNum*ii+1);
			workTexIndexArray.push_back(pNum*ii+2);
			workTexIndexArray.push_back(pNum*ii+0);
			workTexIndexArray.push_back(pNum*ii+2);
			workTexIndexArray.push_back(pNum*ii+3);
		}
		ref_lpD3DDEV->SetFVF(D3DFVF_TEXTURECUSTOMVERTEX);
		ref_lpD3DDEV->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST, 0, workVertexArray.size(), ifsP->faceSize*2, &(workTexIndexArray[0]), D3DFMT_INDEX32,
			&(workVertexArray[0]), sizeof(TEXTURECUSTOMVERTEX)
		);
		*/
		break;

	  default:
		return;
	}

	return;
}

void fk_TextureDraw::GenTextureObj(fk_Texture *argTexObj)
{
	fk_TexID		tmpTexName;

	LPDIRECT3DTEXTURE9	tmpTexObj;
	D3DLOCKED_RECT		rect;
	unsigned char		*pDst;

	const fk_Dimension *bufSize = argTexObj->getBufferSize();
	const fk_ImType *imageBuf = argTexObj->getImageBuf();

	D3DXCreateTexture(ref_lpD3DDEV, bufSize->w, bufSize->h, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &tmpTexObj);
	tmpTexName = static_cast<fk_TexID>(texObjArray.size());

	tmpTexObj->LockRect(0, &rect, NULL, 0);
	pDst = (unsigned char*)(rect.pBits);
	for(int i = 0; i < bufSize->w*bufSize->h; i++) {
		*(pDst+i*4+2) = *(imageBuf+i*4);
		*(pDst+i*4+1) = *(imageBuf+i*4+1);
		*(pDst+i*4)   = *(imageBuf+i*4+2);
		*(pDst+i*4+3) = *(imageBuf+i*4+3);
	}
	tmpTexObj->UnlockRect(0);

	argTexObj->SetTexID(tmpTexName);
	argTexObj->SetInitFlag(false);

	texObjArray.push_back(tmpTexObj);
	texSizeArray.push_back(*bufSize);

	texNameArray.push_back(tmpTexName);
	texImageArray.push_back(argTexObj->getImage());

	texLoadedSize += bufSize->w*bufSize->h*4;

	return;
}

// テクスチャオブジェクトの更新処理(by rita)
void fk_TextureDraw::ReplaceTextureObj(fk_Texture *argTexObj)
{
	fk_TexID		tmpTexName;

	D3DLOCKED_RECT	rect;
	unsigned char	*pDst;

	tmpTexName = argTexObj->GetTexID();
	const fk_Dimension *bufSize = argTexObj->getBufferSize();
	const fk_ImType *imageBuf = argTexObj->getImageBuf();

	// 同じバッファサイズなら更新だけ、違っていたら一度削除して再生成
	if(texSizeArray[tmpTexName].w != bufSize->w || texSizeArray[tmpTexName].h != bufSize->h) {
		RELEASE(texObjArray[tmpTexName]);
		D3DXCreateTexture(ref_lpD3DDEV, bufSize->w, bufSize->h, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texObjArray[tmpTexName]);
		texLoadedSize -= texSizeArray[tmpTexName].w*texSizeArray[tmpTexName].h*4;
		texLoadedSize += bufSize->w*bufSize->h*4;
	}

	texObjArray[tmpTexName]->LockRect(0, &rect, NULL, 0);
	pDst = (unsigned char*)(rect.pBits);
	for(int i = 0; i < bufSize->w*bufSize->h; i++) {
		*(pDst+i*4+2) = *(imageBuf+i*4);
		*(pDst+i*4+1) = *(imageBuf+i*4+1);
		*(pDst+i*4)   = *(imageBuf+i*4+2);
		*(pDst+i*4+3) = *(imageBuf+i*4+3);
	}
	texObjArray[tmpTexName]->UnlockRect(0);

	argTexObj->SetTexID(tmpTexName);
	argTexObj->SetInitFlag(false);
	texSizeArray[tmpTexName] = *bufSize;

	return;
}

void fk_TextureDraw::clearTextureMemory(void)
{
	if(texNameArray.empty() == false) {
		for(unsigned int i = 0; i < texNameArray.size(); i++) {
			RELEASE(texObjArray[texNameArray[i]]);
			if(texImageArray[i] == (fk_Image *)NULL) continue;
			fk_Texture::ClearTexState(texImageArray[i]);
		}
		texObjArray.resize(1);
		texObjArray[0] = NULL;
		texSizeArray.resize(1);
		texSizeArray[0].set(0, 0);

		texNameArray.clear();
		texImageArray.clear();
		texLoadedSize = 0;
	}
	return;
}

unsigned long fk_TextureDraw::getUsingTextureMemory(void)
{
	return texLoadedSize;
}

void fk_TextureDraw::ReleaseTexture(fk_Image *argImage)
{
	if(argImage->GetTexID() == 0) return;
	for(unsigned int i = 0; i < texNameArray.size(); i++) {
		if(argImage->GetTexID() == texNameArray[i]) {
			const fk_Dimension *bufSize = argImage->getBufferSize();
			RELEASE(texObjArray[texNameArray[i]]);
			texSizeArray[texNameArray[i]].set(0, 0);
			fk_Texture::ClearTexState(argImage);
			texNameArray[i] = 0;
			texImageArray[i] = (fk_Image *)NULL;
			texLoadedSize -= bufSize->w*bufSize->h*4;
			break;
		}
	}
	return;
}

void fk_TextureDraw::InitTextureEnv(fk_Texture *argTexObj)
{
	fk_TexID	curID = argTexObj->GetTexID();
	// 強制的に毎回通るように
	// if(bindMode == false || curID != oldTexID) {

		ref_lpD3DDEV->SetTexture(0, texObjArray[curID]);

		switch(argTexObj->getTextureMode()) {
		case FK_TEX_REPLACE:
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
			break;

		case FK_TEX_MODULATE:
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
			break;

		case FK_TEX_DECAL:
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
			ref_lpD3DDEV->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
			break;

		default:
			break;
		}

		ref_lpD3DDEV->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		ref_lpD3DDEV->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

		switch(argTexObj->getTexRendMode()) {
		case FK_TEX_REND_NORMAL:
			ref_lpD3DDEV->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
			ref_lpD3DDEV->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
			break;

		case FK_TEX_REND_SMOOTH:
			ref_lpD3DDEV->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			ref_lpD3DDEV->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			break;

		}
	//}

	oldTexID = curID;

	return;
}

void fk_TextureDraw::setBindMode(bool argFlg)
{
	bindMode = argFlg;
	return;
}

bool fk_TextureDraw::getBindMode(void)
{
	return bindMode;
}

void fk_TextureDraw::DrawRectTexturePick(fk_RectTexture *argTexObj)
{
	fk_TexCoord		texSize;
	double			tmpX, tmpY;

	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == (fk_Dimension *)NULL) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	texSize = argTexObj->getTextureSize();
	tmpX = texSize.x/2.0;
	tmpY = texSize.y/2.0;

	glPushName(0);
	glBegin(GL_QUADS);

	glVertex3d(-tmpX, -tmpY, 0.0);
	glVertex3d(tmpX, -tmpY, 0.0);
	glVertex3d(tmpX, tmpY, 0.0);
	glVertex3d(-tmpX, tmpY, 0.0);

	glEnd();
	glPopName();

	return;
}

void fk_TextureDraw::DrawTriTexturePick(fk_TriTexture *argTexObj)
{
	fk_Vector		*pos;
	register int	counter;

	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == (fk_Dimension *)NULL) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	pos = argTexObj->getPos();

	glPushName(0);
	glBegin(GL_TRIANGLES);

	for(counter = 0; counter < 3; counter++) {
		glVertex3d(pos[counter].x,
				   pos[counter].y,
				   pos[counter].z);
	}

	glEnd();
	glPopName();

	return;
}

void fk_TextureDraw::DrawMeshTexturePick(fk_MeshTexture *argTexObj)
{
	fk_Vector			*posArray;
	int					triNum;
	register int		ii, ij;

	// rita: メッシュ枚数チェックを先に
	triNum = argTexObj->getTriNum();
	if(triNum <= 0) return;

	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == (fk_Dimension *)NULL) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	posArray = &(argTexObj->getPos()->at(0));

	for(ii = 0; ii < triNum; ii++) {
		glPushName(ii*3);
		glBegin(GL_TRIANGLES);

		for(ij = 0; ij < 3; ij++) {
			glVertex3dv((GLdouble *)&(posArray[ii*3+ij].x));
		}

		glEnd();
		glPopName();
	}

	return;
}

void fk_TextureDraw::DrawIFSTexturePick(fk_IFSTexture *argObj)
{
	fk_IndexFaceSet		*ifsP;
	int					ii, ij;
	int					pNum;
	fk_FVector			*pos;
	int					*ifs;

	ifsP = (fk_IndexFaceSet *)argObj->getIFS();
	if(ifsP->faceSize <= 0) return;

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

