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
#include "TextureDraw_D3D.cxx"
#else

#define FK_DEF_SIZETYPE
#include <FK/TextureDraw.H>
#include <FK/IFSTexture.h>
#include <FK/Model.h>
#include <FK/FaceDraw.H>
#include <FK/ARTexture.h>

#include <FK/Error.H>
#include <algorithm>

using namespace std;

vector<GLuint>		fk_TextureDraw::texNameArray;
unsigned long		fk_TextureDraw::texLoadedSize = 0;
vector<fk_Image *>	fk_TextureDraw::texImageArray;

fk_TextureDraw::fk_TextureDraw(void) : oldTexID(0)
{
	SetArrayState(false);
	SetBindMode(false);
}
		
fk_TextureDraw::~fk_TextureDraw()
{
	ClearTextureMemory();
	return;
}

void fk_TextureDraw::ReleaseTexture_(fk_Image *argImage)
{
	if(argImage->GetTexID() == 0) return;
	for(_st i = 0; i < texNameArray.size(); ++i) {
		if(argImage->GetTexID() == texNameArray[i]) {
			const fk_Dimension *bufSize = argImage->getBufferSize();
			glDeleteTextures(1, &texNameArray[i]);
			fk_Texture::ClearTexState(argImage);
			texNameArray[i] = 0;
			texImageArray[i] = nullptr;
			texLoadedSize -= static_cast<unsigned long>(bufSize->w*bufSize->h*4);
			break;
		}
	}
	return;
}	

void fk_TextureDraw::SetArrayState(bool argState)
{
	arrayState = argState;
	return;
}

void fk_TextureDraw::StartUp(void)
{
	oldTexID = 0;
	return;
}

void fk_TextureDraw::DrawTextureObj(fk_Model *argObj, bool argLightFlag, bool argPickFlag)
{
	fk_Texture	*texObj;
	int			mateID = -2;
	GLboolean	texStatus;
	fk_TexID	texID;

	if((argObj->getDrawMode() & FK_TEXTUREMODE) == FK_NONEMODE) return;

	texObj = static_cast<fk_Texture *>(argObj->getShape());

	if(texObj->getObjectType() != FK_ARTEXTURE && texObj->getBufferSize() == nullptr) return;

	fk_Image		*image = texObj->getImage();
	image->ReleaseTexture = fk_TextureDraw::ReleaseTexture_;

	// ピックモードが ON の場合
	if(argPickFlag == true) {
		// テクスチャの種類の選択 
		switch(texObj->getObjectType()) {
		  case FK_RECTTEXTURE:
			DrawRectTexturePick(static_cast<fk_RectTexture *>(texObj));
			break;

		  case FK_TRITEXTURE:
			DrawTriTexturePick(static_cast<fk_TriTexture *>(texObj));
			break;

		  case FK_MESHTEXTURE:
			DrawMeshTexturePick(static_cast<fk_MeshTexture *>(texObj));
			break;

		  case FK_IFSTEXTURE:
			DrawIFSTexturePick(static_cast<fk_IFSTexture *>(texObj));
			break;

		  default:
			break;
		}
		return;
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
		fk_FaceDraw::CommonMateSet(argObj, argLightFlag, true);
	} else {
		fk_FaceDraw::LocalMateSet(texObj->getMaterial(mateID), argLightFlag);
	}

	// (必要なら)テクスチャオブジェクトの生成 
	texID = texObj->GetTexID();
	texStatus = glIsTexture(texID);
	if(texStatus == GL_FALSE || texObj->GetInitFlag() == true) {
		// 生成か更新かの分岐(by rita)
		if(texStatus == GL_TRUE) {
			ReplaceTextureObj(texObj);
		} else {
			GenTextureObj(texObj);
		}
	}

	// テクスチャ表示の初期化 
	InitTextureEnv(texObj);

	// rita_ext: カスタムテクスチャ描画処理の実行ポイント
	argObj->connectShader(texObj->GetTexID());

	// テクスチャの種類の選択 
	switch(texObj->getObjectType()) {
	  case FK_RECTTEXTURE:
		DrawRectTextureObj(static_cast<fk_RectTexture *>(texObj));
		break;

	  case FK_TRITEXTURE:
		DrawTriTextureObj(static_cast<fk_TriTexture *>(texObj));
		break;

	  case FK_MESHTEXTURE:
		DrawMeshTextureObj(static_cast<fk_MeshTexture *>(texObj));
		break;

	  case FK_IFSTEXTURE:
		DrawIFSTextureObj(static_cast<fk_IFSTexture *>(texObj));
		break;

	  case FK_ARTEXTURE:
		DrawARTextureObj(static_cast<fk_ARTexture *>(texObj));
		break;

	  default:
		break;
	}

	// glFlush();
	// glDisable(GL_TEXTURE_2D);

	if(argLightFlag == true) {
		glEnable(GL_LIGHTING);
	} else {
		glDisable(GL_LIGHTING);
	}

	return;
}

void fk_TextureDraw::DrawRectTextureObj(fk_RectTexture *argTexObj)
{
	fk_TexCoord	texSize, startParam, endParam;
	double		tmpX, tmpY;

	const fk_Dimension *imageSize = argTexObj->getImageSize();
	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	if(argTexObj->getRepeatMode() == true) {
		startParam.set(0.0, 0.0);
		endParam = argTexObj->getRepeatParam();
	} else {
		double wScale = static_cast<double>(imageSize->w)/static_cast<double>(bufSize->w);
		double hScale = static_cast<double>(imageSize->h)/static_cast<double>(bufSize->h);
		startParam.set(wScale * argTexObj->texCoord[0].x,
					   hScale * argTexObj->texCoord[0].y);
		endParam.set(wScale * argTexObj->texCoord[1].x,
					 hScale * argTexObj->texCoord[1].y);
	}

	texSize = argTexObj->getTextureSize();
	tmpX = texSize.x/2.0;
	tmpY = texSize.y/2.0;

	glNormal3d(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);

	glTexCoord2d(startParam.x, startParam.y);
	glVertex3d(-tmpX, -tmpY, 0.0);

	glTexCoord2d(endParam.x, startParam.y);
	glVertex3d(tmpX, -tmpY, 0.0);

	glTexCoord2d(endParam.x, endParam.y);
	glVertex3d(tmpX, tmpY, 0.0);

	glTexCoord2d(startParam.x, endParam.y);
	glVertex3d(-tmpX, tmpY, 0.0);

	glEnd();

	return;
}

void fk_TextureDraw::DrawTriTextureObj(fk_TriTexture *argTexObj)
{
	fk_Vector		*pos;
	fk_TexCoord		*coord;
	double			wScale, hScale;
	_st				counter;
	fk_Vector		norm;

	const fk_Dimension *imageSize = argTexObj->getImageSize();
	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	wScale = static_cast<double>(imageSize->w)/static_cast<double>(bufSize->w);
	hScale = static_cast<double>(imageSize->h)/static_cast<double>(bufSize->h);

	pos = argTexObj->getPos();
	coord = argTexObj->getCoord();

	norm = (pos[1] - pos[0]) ^ (pos[2] - pos[0]);
	if(norm.normalize() == false) {
		fk_PutError("fk_Window", "DrawTriTextureObj", 1,
					"Triangle Normal Vector Error.");
		return;
	}

	glBegin(GL_TRIANGLES);

	glNormal3dv((GLdouble *)&(norm.x));
	for(counter = 0; counter < 3; ++counter) {
		glTexCoord2f(coord[counter].x * float(wScale),
					 coord[counter].y * float(hScale));
		glVertex3d(pos[counter].x,
				   pos[counter].y,
				   pos[counter].z);
	}

	glEnd();

	return;
}

void fk_TextureDraw::DrawMeshTextureObj(fk_MeshTexture *argTexObj)
{
	fk_Vector			*posArray;
	vector<fk_TexCoord>	*coordArray;
	double				wScale, hScale;
	int					triNum;
	_st					ii, ij;
	fk_Vector			norm;

	const fk_Dimension *imageSize = argTexObj->getImageSize();
	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	// rita: メッシュ枚数チェックを先に
	triNum = argTexObj->getTriNum();
	if(triNum <= 0) return;

	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	wScale = static_cast<double>(imageSize->w)/static_cast<double>(bufSize->w);
	hScale = static_cast<double>(imageSize->h)/static_cast<double>(bufSize->h);

	posArray = &(argTexObj->getPos()->at(0));
	coordArray = argTexObj->getCoord();

	glBegin(GL_TRIANGLES);
	for(ii = 0; ii < static_cast<_st>(triNum); ++ii) {
		norm = (posArray[ii*3 + 1] - posArray[ii*3]) ^
				(posArray[ii*3 + 2] - posArray[ii*3]);
		if(norm.normalize() == false) {
			fk_PutError("fk_Window", "DrawMeshTextureObj", 1,
						"Normal Vector Error.");
			continue;
		}
						
		glNormal3dv(static_cast<GLdouble *>(&(norm.x)));
		for(ij = 0; ij < 3; ++ij) {
			glTexCoord2f((*coordArray)[ii*3+ij].x * static_cast<float>(wScale),
						 (*coordArray)[ii*3+ij].y * static_cast<float>(hScale));
			glVertex3dv(static_cast<GLdouble *>(&(posArray[ii*3+ij].x)));
		}
	}

	glEnd();
	return;
}

void fk_TextureDraw::DrawIFSTextureObj(fk_IFSTexture *argTexObj)
{
	fk_IndexFaceSet	*ifsP;
	_st				pNum;
	fk_TexCoord		*texCoord;
	GLenum			tmpType;

	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	ifsP = argTexObj->getIFS();

	if(ifsP->modifyFlg == true) {
		ifsP->ModifyVNorm();
	}

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

	texCoord = &(argTexObj->coordArray[0]);

	glShadeModel(GL_SMOOTH);

	if(arrayState == true) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, &ifsP->pos[0]);
		glNormalPointer(GL_FLOAT, 0, &ifsP->vNorm[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &texCoord[0]);
		
		glDrawElements(tmpType, ifsP->faceSize * static_cast<GLsizei>(pNum),
					   GL_UNSIGNED_INT, &ifsP->ifs[0]);
	} else {
		glBegin(tmpType);
		for(_st ii = 0; ii < static_cast<_st>(ifsP->faceSize); ++ii) {
			for(_st ij = 0; ij < pNum; ++ij) {
				_st index = static_cast<_st>(ifsP->ifs[pNum*ii+ij]);
				glNormal3fv((GLfloat *)&(ifsP->vNorm[index]));
				glTexCoord2fv((GLfloat *)&texCoord[index]);
				glVertex3fv((GLfloat *)&(ifsP->pos[index]));
			}
		}
		glEnd();
	}
	return;
}

void fk_TextureDraw::DrawARTextureObj(fk_ARTexture *argTexObj)
{
	fk_TexCoord		texSize = argTexObj->getTextureSize();
	double			tmpX, tmpY;

	tmpX = texSize.x/2.0;
	tmpY = texSize.y/2.0;
	
	glNormal3d(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	
	glTexCoord2d(0.0, 0.0);
	glVertex3d(-tmpX, -tmpY, 0.0);
	
	glTexCoord2d(1.0, 0.0);
	glVertex3d(tmpX, -tmpY, 0.0);
	
	glTexCoord2d(1.0, 1.0);
	glVertex3d(tmpX, tmpY, 0.0);
	
	glTexCoord2d(0.0, 1.0);
	glVertex3d(-tmpX, tmpY, 0.0);

	glEnd();

	return;
}

void fk_TextureDraw::GenTextureObj(fk_Texture *argTexObj)
{
	fk_TexID	tmpTexName;

	const fk_ImType		*imageBuf = argTexObj->getImageBuf();
	const fk_Dimension	*bufSize = argTexObj->getBufferSize();

	glGenTextures(1, &tmpTexName);
	glBindTexture(GL_TEXTURE_2D, tmpTexName);

	switch(argTexObj->getTexWrapMode()) {
	  case FK_TEX_WRAP_REPEAT:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;

	  case FK_TEX_WRAP_CLAMP:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		break;
	}
	
	switch(argTexObj->getTexRendMode()) {
	  case FK_TEX_REND_NORMAL:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;

	  case FK_TEX_REND_SMOOTH:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		break;

	}
	
	if(argTexObj->getObjectType() == FK_ARTEXTURE) {
		GenARTextureObj(static_cast<fk_ARTexture *>(argTexObj));
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufSize->w, bufSize->h,
					 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuf);
	}

	argTexObj->SetTexID(tmpTexName);
	argTexObj->SetInitFlag(false);
	texNameArray.push_back(tmpTexName);
	texImageArray.push_back(argTexObj->getImage());

	texLoadedSize += static_cast<unsigned long>(bufSize->w*bufSize->h*4);

	return;
}

void fk_TextureDraw::GenARTextureObj(fk_ARTexture *argTexObj)
{
	fk_Dimension			bufSize = argTexObj->getVideoSize();
	const unsigned char		*arImageBuf = argTexObj->getVideoBuf();
	fk_PixelFormatType		type = argTexObj->getPixelFormatType();

	switch (type) {
	  case FK_PIXEL_FORMAT_RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
					 bufSize.w, bufSize.h,
					 0, GL_RGB,
					 GL_UNSIGNED_BYTE,
					 arImageBuf);
		break;
			
	  case FK_PIXEL_FORMAT_BGR:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
					 bufSize.w, bufSize.h,
					 0, GL_BGR,
					 GL_UNSIGNED_BYTE,
					 arImageBuf);
		break;
			
	  case FK_PIXEL_FORMAT_RGBA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
					 bufSize.w, bufSize.h,
					 0, GL_RGBA,
					 GL_UNSIGNED_BYTE,
					 arImageBuf);
		break;
			
	  case FK_PIXEL_FORMAT_BGRA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
					 bufSize.w, bufSize.h,
					 0, GL_BGRA,
					 GL_UNSIGNED_BYTE,
					 arImageBuf);
		break;
			
	  case FK_PIXEL_FORMAT_MONO:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
					 bufSize.w, bufSize.h,
					 0, GL_LUMINANCE,
					 GL_UNSIGNED_BYTE,
					 arImageBuf);
		break;
			
	  case FK_PIXEL_FORMAT_ARGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
					 bufSize.w, bufSize.h,
					 0, GL_BGRA,
					 GL_UNSIGNED_INT_8_8_8_8,
					 arImageBuf);
		break;
			
	  case FK_PIXEL_FORMAT_2vuy:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
					 bufSize.w, bufSize.h,
					 0, GL_YCBCR_422_APPLE,
					 GL_UNSIGNED_SHORT_8_8_APPLE,
					 arImageBuf);
		break;
			
	  case FK_PIXEL_FORMAT_yuvs:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
					 bufSize.w, bufSize.h,
					 0, GL_YCBCR_422_APPLE,
					 GL_UNSIGNED_SHORT_8_8_APPLE,
					 arImageBuf);
		break;
			
	  default:
		break;			
	}
	// =====================================================================
	return;
}

// テクスチャオブジェクトの更新処理(by rita)
void fk_TextureDraw::ReplaceTextureObj(fk_Texture *argTexObj)
{
	fk_TexID	tmpTexName;
	GLint		texW, texH;

	const fk_ImType		*imageBuf = argTexObj->getImageBuf();
	const fk_Dimension	*bufSize = argTexObj->getBufferSize();

	tmpTexName = argTexObj->GetTexID();

	glBindTexture(GL_TEXTURE_2D, tmpTexName);
	// 現在読み込んでいるテクスチャのサイズを取得
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texW);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texH);

	// 同じバッファサイズなら SubImage による更新、違っていたら一度削除して再生成
	if(texW == bufSize->w && texH == bufSize->h) {

		if(argTexObj->getObjectType() == FK_ARTEXTURE) {
			GenARTextureObj(static_cast<fk_ARTexture *>(argTexObj));
		} else {
			static fk_Rect				tmpRect;	// 部分更新矩形情報
			static vector<fk_ImType>	subBuffer;	// 部分更新用バッファ
			const fk_Dimension			*imageSize = argTexObj->getImageSize();

			// 更新領域取得
			tmpRect = argTexObj->getImage()->GetUpdateArea();
			if(tmpRect.w < 1 || tmpRect.h < 1) {	// 矩形が指定されていなかったら全体更新
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, bufSize->w, bufSize->h,
								GL_RGBA, GL_UNSIGNED_BYTE, imageBuf);
			} else {	// 指定されていたら部分更新
				subBuffer.resize(static_cast<_st>(tmpRect.w*tmpRect.h*4));
				for(int i = 0; i < tmpRect.h; ++i) {
					memcpy(&(subBuffer[static_cast<_st>((tmpRect.h-i-1)*tmpRect.w*4)]),
						   imageBuf+((imageSize->h - (tmpRect.y+i) - 1)*bufSize->w + tmpRect.x)*4,
						   static_cast<size_t>(tmpRect.w*4));
				}
				if(!subBuffer.empty()) {
					glTexSubImage2D(GL_TEXTURE_2D, 0, tmpRect.x,
									imageSize->h - tmpRect.h - tmpRect.y,
									tmpRect.w, tmpRect.h,
									GL_RGBA, GL_UNSIGNED_BYTE, &(subBuffer[0]));
				}
			}
		}
	} else {
		if(argTexObj->getObjectType() == FK_ARTEXTURE) {
			GenARTextureObj(static_cast<fk_ARTexture *>(argTexObj));
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufSize->w, bufSize->h,
						 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuf);
			texLoadedSize -= static_cast<unsigned long>(texW*texH*4);
			texLoadedSize += static_cast<unsigned long>(bufSize->w*bufSize->h*4);
		}
	}
	// フラグ解除
	argTexObj->SetInitFlag(false);

	return;
}

void fk_TextureDraw::ClearTextureMemory(void)
{
	if(texNameArray.empty() == false) {
		glDeleteTextures(static_cast<GLsizei>(texNameArray.size()), &texNameArray[0]);
		for(_st i = 0; i < texImageArray.size(); ++i) {
			if(texImageArray[i] == nullptr) continue;
			fk_Texture::ClearTexState(texImageArray[i]);
		}
		texNameArray.clear();
		texImageArray.clear();
		texLoadedSize = 0;
	}
	return;
}

unsigned long fk_TextureDraw::GetUsingTextureMemory(void)
{
	return texLoadedSize;
}

void fk_TextureDraw::InitTextureEnv(fk_Texture *argTexObj)
{
	GLint		texMode = GL_MODULATE;
	fk_TexID	curID;

	switch(argTexObj->getTextureMode()) {
	  case FK_TEX_REPLACE:
		texMode = GL_REPLACE;
		break;

	  case FK_TEX_MODULATE:
		texMode = GL_MODULATE;
		break;

	  case FK_TEX_DECAL:
		texMode = GL_DECAL;
		break;

	  default:
		break;
	}

	curID = argTexObj->GetTexID();

	if(bindMode == false || curID != oldTexID) {
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, texMode);
		
		switch(argTexObj->getTexWrapMode()) {
		  case FK_TEX_WRAP_REPEAT:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;

		  case FK_TEX_WRAP_CLAMP:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			break;
		}

		glBindTexture(GL_TEXTURE_2D, curID);
	}

	oldTexID = curID;

	return;
}

void fk_TextureDraw::SetBindMode(bool argFlg)
{
	bindMode = argFlg;
	return;
}

bool fk_TextureDraw::GetBindMode(void)
{
	return bindMode;
}

void fk_TextureDraw::DrawRectTexturePick(fk_RectTexture *argTexObj)
{
	fk_TexCoord	texSize;
	double		tmpX, tmpY;

	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == nullptr) return;
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
	int				counter;

	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	pos = argTexObj->getPos();

	glPushName(0);
	glBegin(GL_TRIANGLES);

	for(counter = 0; counter < 3; ++counter) {
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
	fk_Vector	*posArray;
	int			triNum;
	_st			ii, ij;

	const fk_Dimension *bufSize = argTexObj->getBufferSize();

	// rita: メッシュ枚数チェックを先に
	triNum = argTexObj->getTriNum();
	if(triNum <= 0) return;

	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	posArray = &(argTexObj->getPos()->at(0));

	for(ii = 0; ii < static_cast<_st>(triNum); ++ii) {
		glPushName(static_cast<GLuint>(ii*3));
		glBegin(GL_TRIANGLES);

		for(ij = 0; ij < 3; ++ij) {
			glVertex3dv(static_cast<GLdouble *>(&(posArray[ii*3+ij].x)));
		}

		glEnd();
		glPopName();
	}

	return;
}

void fk_TextureDraw::DrawIFSTexturePick(fk_IFSTexture *argObj)
{
	fk_IndexFaceSet	*ifsP;
	int				ii, ij;
	int				pNum;
	fk_FVector		*pos;
	int				*ifs;

	ifsP = (fk_IndexFaceSet *)argObj->getIFS();

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

	for(ii = 0; ii < ifsP->faceSize; ++ii) {
		glPushName(static_cast<GLuint>(ii*3));
		glBegin(GL_POLYGON);
		for(ij = 0; ij < pNum; ++ij) {
			glVertex3fv(static_cast<GLfloat *>(&pos[ifs[pNum*ii+ij]].x));
		}
		glEnd();
		glPopName();
	}

	return;
}

#endif
