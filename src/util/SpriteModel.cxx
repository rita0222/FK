#include <FK/SpriteModel.h>

using namespace std;
using namespace FK;

double fk_SpriteModel::distPut = 1.0;

fk_SpriteModel::fk_SpriteModel(void) : fk_Model(), fontReady(false)
{
	setParent(&pixelBase);

	texShape.setTextureMode(fk_TexMode::REPLACE);
	texShape.setTexRendMode(fk_TexRendMode::SMOOTH);
	setShape(&texShape);

	absMate.setAmbDiff(1.0, 1.0, 1.0);
	absMate.setEmission(1.0, 1.0, 1.0);
	absMate.setAlpha(1.0);
	setMaterial(absMate);

	return;
}

fk_SpriteModel::~fk_SpriteModel(void)
{
}

bool fk_SpriteModel::entryFirst(fk_Window *argWin, fk_Scene *argScn, fk_Model *argCam)
{
	if(texShape.getImage()->getWidth() == 0) {
		argScn->removeModel(this);
		argScn->removeOverlayModel(this);
		return false;
	}

	if(argCam != nullptr) argScn->entryCamera(argCam);

	MakePixelBase(fk_Dimension(argWin->w(), argWin->h()), argScn);
	argScn->entryOverlayModel(this);

	return true;
}

void fk_SpriteModel::MakePixelBase(const fk_Dimension &argWinSize, fk_Scene *argScn)
{
	fk_Perspective	*pers = nullptr;
	fk_Ortho		*orth = nullptr;
	fk_Frustum		*frus = nullptr;
	fk_ProjectBase	*proj = nullptr;

	double	dW = static_cast<double>(argWinSize.w);
	double	dH = static_cast<double>(argWinSize.h);
	double	trueD = (dW < dH) ? dW : dH;

	if(argScn->getCamera() == nullptr) return;
	pixelBase.setParent(const_cast<fk_Model *>(argScn->getCamera()));

	proj = const_cast<fk_ProjectBase *>(argScn->getProjection());

	if(proj->getMode() == fk_ProjectMode::PERSPECTIVE) {
		pers = dynamic_cast<fk_Perspective *>(proj);
		double halfFovy = pers->getFovy()*0.5;
		double nearPut = pers->getNear()+distPut;

		pixelBase.glMoveTo(0.0, 0.0, -nearPut);
		pixelBase.setScale((nearPut*tan(halfFovy)*2.0/trueD),
						   (nearPut*tan(halfFovy)*2.0/trueD), 1.0);

	} else if(argScn->getProjection()->getMode() == fk_ProjectMode::ORTHO){
		orth = dynamic_cast<fk_Ortho *>(proj);

		pixelBase.glMoveTo(0.0, 0.0, -(orth->getNear()+distPut));
		pixelBase.setScale((orth->getRight() - orth->getLeft())/trueD,
						   (orth->getTop() - orth->getBottom())/trueD, 1.0);

	} else if(argScn->getProjection()->getMode() == fk_ProjectMode::FRUSTUM) {
		frus = dynamic_cast<fk_Frustum *>(proj);

		double nearPut = frus->getNear();
		double regL = frus->getLeft();
		double regR = frus->getRight();
		double regB = frus->getBottom();
		double regT = frus->getTop();
		regL /= nearPut;	regR /= nearPut;
		regB /= nearPut;	regT /= nearPut;
		nearPut += distPut;
		regL *= nearPut;	regR *= nearPut;
		regB *= nearPut;	regT *= nearPut;

		pixelBase.glMoveTo((regR + regL)/2.0, (regT + regB)/2.0, -nearPut);
		pixelBase.setScale((regR - regL)/dW, (regT - regB)/dH, 1.0);
	}

	pixelBase.glAngle(0.0, 0.0, 0.0);

	return;
}

void fk_SpriteModel::setSpriteSize(double width, double height)
{
	if(width < 0.0) width = static_cast<double>(getImage()->getWidth());
	if(height < 0.0) height = static_cast<double>(getImage()->getHeight());
	texShape.setTextureSize(width, height);
	return;
}

fk_TexCoord	fk_SpriteModel::getSpriteSize(void)
{
	return texShape.getTextureSize();
}

bool fk_SpriteModel::readBMP(const string argFileName)
{
	if(!texShape.readBMP(argFileName)) return false;
	setSpriteSize();
	return true;
}

bool fk_SpriteModel::readPNG(const string argFileName)
{
	if(!texShape.readPNG(argFileName)) return false;
	setSpriteSize();
	return true;
}

bool fk_SpriteModel::readJPG(const string argFileName)
{
	if(!texShape.readJPG(argFileName)) return false;
	setSpriteSize();
	return true;
}

void fk_SpriteModel::setImage(fk_Image *argImage)
{
	texShape.setImage(argImage);
	setSpriteSize();
	return;
}

void fk_SpriteModel::setImage(fk_Image &argImage)
{
	texShape.setImage(&argImage);
	setSpriteSize();
	return;
}

fk_Image * fk_SpriteModel::getImage(void)
{
	return texShape.getImage();
}

bool fk_SpriteModel::initFont(const string argFontFile)
{
	if(!text.initFont(argFontFile)) {
		fontReady = false;
		return false;
	}

	text.setDPI(96);
	text.setPTSize(18);
	text.setForeColor(1.0, 1.0, 1.0, 1.0);
	text.setBackColor(0.0, 0.0, 0.0, 0.5);
	text.setAlign(fk_TextAlign::CENTER);

	setImage(text);

	fontReady = true;
	return true;
}

void fk_SpriteModel::clearText(void)
{
	textStr.clear();
	text.loadUniStr(&textStr);
	setImage(text);

	return;
}

void fk_SpriteModel::drawText(const string argStr, bool argFlag, fk_StringCode argCode)
{
	if(!fontReady) return;

	if(argFlag) textStr.clear();
	textStr.convert(argStr, argCode);
	text.loadUniStr(&textStr);
	setImage(text);

	return;
}

void fk_SpriteModel::drawText(const string argStr, fk_StringCode argCode)
{
	drawText(argStr, false, argCode);
}

void fk_SpriteModel::setSpriteSmoothMode(bool flag)
{
	if(flag) texShape.setTexRendMode(fk_TexRendMode::SMOOTH);
	else texShape.setTexRendMode(fk_TexRendMode::NORMAL);
}

bool fk_SpriteModel::getSpriteSmoothMode(void)
{
	if(texShape.getTexRendMode() == fk_TexRendMode::SMOOTH) return true;
	return false;
}

void fk_SpriteModel::setSpriteArea(double left, double top, double width, double height)
{
	double imgWidth  = static_cast<double>(getImage()->getWidth());
	double imgHeight = static_cast<double>(getImage()->getHeight());
	if(imgWidth < 8.0 || imgHeight < 8.0 || fabs(width) < 8.0 || fabs(height) < 8.0) return;

	fk_TexCoord	lb, rt;

	lb.set(left/imgWidth, 1.0-(top+height)/imgHeight);
	rt.set((left+width)/imgWidth, 1.0-top/imgHeight);
	texShape.setTextureCoord(lb, rt);
	setSpriteSize(fabs(width), fabs(height));

	return;
}

void fk_SpriteModel::setPositionLT(double x, double y)
{
	fk_TexCoord	size = getSpriteSize();
	glMoveTo(x + size.x/2.0, y - size.y/2.0, 0.0);
}

void fk_SpriteModel::SetFinalizeMode(void)
{
	pixelBase.SetTreeDelMode(false);
	SetTreeDelMode(false);
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
