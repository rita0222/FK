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
using namespace FK;

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
		texObj->DrawPick();
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

	// テクスチャ描画処理
	texObj->DrawTexture(arrayState);

	// glFlush();
	// glDisable(GL_TEXTURE_2D);

#ifndef OPENGL4
	if(argLightFlag == true) {
		glEnable(GL_LIGHTING);
	} else {
		glDisable(GL_LIGHTING);
	}
#endif
   
	return;
}

void fk_TextureDraw::GenTextureObj(fk_Texture *argTexObj)
{
	fk_TexID	tmpTexName;

	//const fk_ImType		*imageBuf = argTexObj->getImageBuf();
	const fk_Dimension	*bufSize = argTexObj->getBufferSize();

	glGenTextures(1, &tmpTexName);
	glBindTexture(GL_TEXTURE_2D, tmpTexName);

	switch(argTexObj->getTexWrapMode()) {
	  case FK_TEX_WRAP_REPEAT:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;

	  case FK_TEX_WRAP_CLAMP:
#ifndef OPENGL4
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
#endif
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
	
	argTexObj->GenTextureObj();

	argTexObj->SetTexID(tmpTexName);
	argTexObj->SetInitFlag(false);
	texNameArray.push_back(tmpTexName);
	texImageArray.push_back(argTexObj->getImage());

	texLoadedSize += static_cast<unsigned long>(bufSize->w*bufSize->h*4);

	return;
}

// テクスチャオブジェクトの更新処理
void fk_TextureDraw::ReplaceTextureObj(fk_Texture *argTexObj)
{
	fk_TexID	tmpTexName;
	GLint		texW, texH;

	const fk_Dimension	*bufSize = argTexObj->getBufferSize();

	tmpTexName = argTexObj->GetTexID();

	glBindTexture(GL_TEXTURE_2D, tmpTexName);
	// 現在読み込んでいるテクスチャのサイズを取得
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texW);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texH);

	// 同じバッファサイズなら SubImage による更新、違っていたら一度削除して再生成
	if(texW == bufSize->w && texH == bufSize->h) {
		argTexObj->ReplaceSubImage();
	} else {
		argTexObj->GenTextureObj();
		texLoadedSize -= static_cast<unsigned long>(texW*texH*4);
		texLoadedSize += static_cast<unsigned long>(bufSize->w*bufSize->h*4);
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
	GLint		texMode = GL_REPLACE;
	fk_TexID	curID;

	switch(argTexObj->getTextureMode()) {
	  case FK_TEX_REPLACE:
		texMode = GL_REPLACE;
		break;

#ifndef OPENGL4
	  case FK_TEX_MODULATE:
		texMode = GL_MODULATE;
		break;

	  case FK_TEX_DECAL:
		texMode = GL_DECAL;
		break;
#endif
		
	  default:
		break;
	}

	curID = argTexObj->GetTexID();

	if(bindMode == false || curID != oldTexID) {
		glEnable(GL_TEXTURE_2D);

#ifndef OPENGL4		
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, texMode);
#endif		

		switch(argTexObj->getTexWrapMode()) {
		  case FK_TEX_WRAP_REPEAT:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;

		  case FK_TEX_WRAP_CLAMP:
#ifndef OPENGL4			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
#endif
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

#endif
