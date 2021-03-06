﻿#define FK_DEF_SIZETYPE
#include <FK/TriTexture.h>
#include <FK/Error.H>
#include <FK/Window.h>

using namespace std;
using namespace FK;

vector<GLuint> fk_TriTexture::_s_faceIndex = {0, 1, 2};
GLuint fk_TriTexture::_s_faceIBO = 0;
bool fk_TriTexture::_s_faceIndexFlg = false;

fk_TriTexture::Member::Member(void)
{
	vertexPosition.setDim(3);
	vertexPosition.resize(3);
	vertexNormal.setDim(3);
	vertexNormal.resize(3);
	return;
}

fk_TriTexture::fk_TriTexture(fk_Image *argImage) :
	fk_Texture(argImage),
	_m(make_unique<Member>())
{
	SetObjectType(fk_Type::TRITEXTURE);
	GetFaceSize = []() { return 1; };
	StatusUpdate = [this]() {
		PosUpdate();
		NormUpdate();
		TexCoordUpdate();
	};

	FaceIBOSetup = []() {
		if(_s_faceIBO == 0) {
			_s_faceIBO = GenBuffer();
			_s_faceIndexFlg = true;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _s_faceIBO);
		if(_s_faceIndexFlg == true) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,
						 GLsizei(3*sizeof(GLuint)),
						 _s_faceIndex.data(), GL_STATIC_DRAW);
			_s_faceIndexFlg = false;
		}
	};

	setShaderAttribute(vertexName, 3, _m->vertexPosition.getP());
	setShaderAttribute(normalName, 3, _m->vertexNormal.getP());

	_m_texCoord->setDim(2);
	_m_texCoord->resize(3);
	setShaderAttribute(texCoordName, 2, _m_texCoord->getP());

	init();

	return;
}

fk_TriTexture::~fk_TriTexture()
{
	return;
}


void fk_TriTexture::init(void)
{
	BaseInit();
	return;
}

bool fk_TriTexture::setVertexPos(int argID,
								 double argX, double argY, double argZ)
{
	if(argID < 0 || argID > 2) {
		Error::Put("fk_TriTexture", "setVertexPos", 1, "ID Error.");
		return false;
	}

	_m->pos[argID].set(argX, argY, argZ);
	PosUpdate();
	NormUpdate();
	return true;
}

bool fk_TriTexture::setVertexPos(int argID, fk_Vector argPos)
{
	if(argID < 0 || argID > 2) {
		Error::Put("fk_TriTexture", "setVertexPos", 2, "ID Error.");
		return false;
	}

	_m->pos[argID] = argPos;
	PosUpdate();
	NormUpdate();
	return true;
}

bool fk_TriTexture::setTextureCoord(int argID, double argS, double argT)
{
	if(argID < 0 || argID > 2) {
		Error::Put("fk_TriTexture", "setTextureCoord", 1, "ID Error.");
		return false;
	}

	if(argS < -fk_Math::EPS || argS > 1.0 + fk_Math::EPS ||
	   argT < -fk_Math::EPS || argT > 1.0 + fk_Math::EPS) {
		Error::Put("fk_TriTexture", "setTextureCoord", 2, "Texture Coord Error.");
		return false;
	}

	_m->triTexCoord[argID].set(argS, argT);
	TexCoordUpdate();
	return true;
}


bool fk_TriTexture::setTextureCoord(int argID, fk_TexCoord argCoord)
{
	if(argID < 0 || argID > 2) {
		Error::Put("fk_TriTexture", "setTextureCoord", 3, "ID Error.");
		return false;
	}

	if(argCoord.x < -fk_Math::EPS || argCoord.x > 1.0 + fk_Math::EPS ||
	   argCoord.y < -fk_Math::EPS || argCoord.y > 1.0 + fk_Math::EPS) {
		Error::Put("fk_TriTexture", "setTextureCoord", 4, "Texture Coord Error.");
		return false;
	}

	_m->triTexCoord[argID].set(argCoord.x, argCoord.y);

	TexCoordUpdate();
	return true;
}

fk_Vector fk_TriTexture::getVertexPos(int argID)
{
	fk_Vector		dummy(0.0, 0.0, 0.0);

	if(argID < 0 || argID > 2) {
		Error::Put("fk_TriTexture", "getVertexPos", 1, "ID Error.");
		return dummy;
	}

	return _m->pos[argID];
}

fk_TexCoord fk_TriTexture::getTextureCoord(int argID)
{
	fk_TexCoord		dummy(0.0, 0.0);

	if(argID < 0 || argID > 2) {
		Error::Put("fk_TriTexture", "getTextureCoord", 1, "ID Error.");
		return dummy;
	}

	return _m->triTexCoord[argID];
}

void fk_TriTexture::PosUpdate(void)
{
	for(int i = 0; i < 3; ++i) _m->vertexPosition.set(i, _m->pos[i]);
	modifyAttribute(vertexName);
}

void fk_TriTexture::NormUpdate(void)
{
	fk_Vector		norm;
	norm = (_m->pos[1] - _m->pos[0]) ^ (_m->pos[2] - _m->pos[0]);
	norm.normalize();
	for(int i = 0; i < 3; ++i) _m->vertexNormal.set(i, norm);
	modifyAttribute(normalName);
}
	
		
void fk_TriTexture::TexCoordUpdate(void)
{
	const fk_Dimension *imageSize = getImageSize();
	const fk_Dimension *bufSize = getBufferSize();

	_m_texCoord->resize(3);

	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	double wScale = static_cast<double>(imageSize->w)/static_cast<double>(bufSize->w);
	double hScale = static_cast<double>(imageSize->h)/static_cast<double>(bufSize->h);
	for(int i = 0; i < 3; ++i) {
		_m_texCoord->set(i, _m->triTexCoord[i].x * wScale, _m->triTexCoord[i].y * hScale);
	}

	modifyAttribute(texCoordName);
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
