/****************************************************************************
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
#include <FK/RectTexture.h>
#include <FK/Error.H>
#include <FK/Window.h>

using namespace std;
using namespace FK;

vector<GLuint> fk_RectTexture::faceIndex = {0, 1, 3, 1, 2, 3};
GLuint fk_RectTexture::faceIBO = 0;
bool fk_RectTexture::faceIndexFlg = false;

fk_RectTexture::fk_RectTexture(fk_Image *argImage)
	: fk_Texture(argImage)
{
	SetObjectType(FK_RECTTEXTURE);
	GetFaceSize = []() { return 2; };
	StatusUpdate = [this]() {
		SizeUpdate();
		NormalUpdate();
		TexCoordUpdate();
	};

	FaceIBOSetup = []() {
		if(faceIBO == 0) {
			faceIBO = GenBuffer();
			faceIndexFlg = true;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceIBO);
		if(faceIndexFlg == true) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,
						 GLsizei(6*sizeof(GLuint)),
						 faceIndex.data(), GL_STATIC_DRAW);
			faceIndexFlg = false;
		}
	};
		
	vertexPosition.setDim(3);
	vertexPosition.resize(6);
	setShaderAttribute(vertexName, 3, vertexPosition.getP());

	vertexNormal.setDim(3);
	vertexNormal.resize(6);
	setShaderAttribute(normalName, 3, vertexNormal.getP());

	texCoord.setDim(2);
	texCoord.resize(6);
	setShaderAttribute(texCoordName, 2, texCoord.getP());

	init();
	return;
}

fk_RectTexture::~fk_RectTexture()
{
	return;
}

void fk_RectTexture::init(void)
{
	BaseInit();
	RectInit();
	return;
}

void fk_RectTexture::RectInit(void)
{
	texSize.set(2.0, 2.0);
	setRepeatMode(false);
	repeatParam.set(1.0, 1.0);
	rectSE[0].set(0.0, 0.0);
	rectSE[1].set(1.0, 1.0);

	SizeUpdate();
	NormalUpdate();
	TexCoordUpdate();
}	

void fk_RectTexture::SizeUpdate(void)
{
	double tmpX = texSize.x/2.0;
	double tmpY = texSize.y/2.0;
		
	vertexPosition.resize(4);
	vertexPosition.set(0, -tmpX, -tmpY);
	vertexPosition.set(1, tmpX, -tmpY);
	vertexPosition.set(2, tmpX, tmpY);
	vertexPosition.set(3, -tmpX, tmpY);
	modifyAttribute(vertexName);
}

void fk_RectTexture::NormalUpdate(void)
{
	fk_Vector		norm(0.0, 0.0, 1.0);
	vertexNormal.resize(4);
	for(int i = 0; i < 4; i++) vertexNormal.set(i, norm);
	modifyAttribute(normalName);
}

void fk_RectTexture::TexCoordUpdate(void)
{
	fk_TexCoord		s, e;
	const fk_Dimension *imageSize = getImageSize();
	const fk_Dimension *bufSize = getBufferSize();

	texCoord.resize(4);

	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	if(getRepeatMode() == true) {
		s.set(0.0, 0.0);
		e = getRepeatParam();
	} else {
		double wScale = double(imageSize->w)/double(bufSize->w);
		double hScale = double(imageSize->h)/double(bufSize->h);
		s.set(wScale * rectSE[0].x, hScale * rectSE[0].y);
		e.set(wScale * rectSE[1].x, hScale * rectSE[1].y);
	}

	texCoord.set(0, s.x, s.y);
	texCoord.set(1, e.x, s.y);
	texCoord.set(2, e.x, e.y);
	texCoord.set(3, s.x, e.y);

	modifyAttribute(texCoordName);
}


bool fk_RectTexture::setTextureSize(double argX, double argY)
{
	if(argX < -FK_EPS || argY < -FK_EPS) {
		return false;
	}

	texSize.set(argX, argY);
	SizeUpdate();

	return true;
}

fk_TexCoord fk_RectTexture::getTextureSize(void)
{
	return texSize;
}

void fk_RectTexture::setRepeatMode(bool argFlag)
{
	repeatFlag = argFlag;
	return;
}

bool fk_RectTexture::getRepeatMode(void)
{
	return repeatFlag;
}

void fk_RectTexture::setRepeatParam(double argS, double argT)
{
	repeatParam.set(argS, argT);
	TexCoordUpdate();
	return;
}

fk_TexCoord fk_RectTexture::getRepeatParam(void)
{
	return repeatParam;
}

void fk_RectTexture::setTextureCoord(double argSU, double argSV,
									 double argEU, double argEV)
{
	if(argSU < -FK_EPS || argSU > 1.0 + FK_EPS ||
	   argSV < -FK_EPS || argSV > 1.0 + FK_EPS ||
	   argEU < -FK_EPS || argEU > 1.0 + FK_EPS ||
	   argEV < -FK_EPS || argEV > 1.0 + FK_EPS) {
		fk_PutError("fk_RectTexture", "setTextureCoord", 1,
					"Texture Coord Error.");
		return;
	}

	rectSE[0].set(argSU, argSV);
	rectSE[1].set(argEU, argEV);

	TexCoordUpdate();

	return;
}

void fk_RectTexture::setTextureCoord(const fk_TexCoord &argS,
									 const fk_TexCoord &argE)
{
	if(argS.x < -FK_EPS || argS.x > 1.0 + FK_EPS ||
	   argS.y < -FK_EPS || argS.y > 1.0 + FK_EPS ||
	   argE.x < -FK_EPS || argE.x > 1.0 + FK_EPS ||
	   argE.y < -FK_EPS || argE.y > 1.0 + FK_EPS) {
		fk_PutError("fk_RectTexture", "setTextureCoord", 2,
					"Texture Coord Error.");
		return;
	}

	rectSE[0].set(argS.x, argS.y);
	rectSE[1].set(argE.x, argE.y);

	TexCoordUpdate();
	return;
}

fk_TexCoord fk_RectTexture::getTextureCoord(int argID)
{
	if(argID < 0 || argID > 1) {
		fk_PutError("fk_RectTexture", "getTextureCoord", 1, "ID Error");
		return fk_TexCoord(0.0, 0.0);
	}
	return rectSE[argID];
}
