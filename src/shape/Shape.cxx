﻿/****************************************************************************
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
#include <FK/Shape.h>

using namespace std;

fk_Shape::fk_Shape(fk_ObjectType argObjType)
{
	SetObjectType(argObjType);
	materialMode = FK_NONE_MODE;
	return;
}

fk_Shape::~fk_Shape()
{
	return;
}

void fk_Shape::SetPaletteData(fk_Palette *argPal)
{
	palette = argPal;
	return;
}

void fk_Shape::setPaletteData(fk_Palette *argPal)
{
	SetPaletteData(argPal);
	return;
}

fk_Palette * fk_Shape::getPaletteData(void)
{
	return palette;
}

void fk_Shape::clearMaterial(void)
{
	palette->clearMaterial();
	return;
}

void fk_Shape::setObjMaterialID(int argID)
{
	palette->setObjMaterialID(argID);
	materialMode = FK_CHILD_MODE;
	return;
}

void fk_Shape::pushPalette(fk_Material &argMat)
{
	palette->pushPalette(&argMat);
	materialMode = FK_PARENT_MODE;
	return;
}

void fk_Shape::setPalette(fk_Material &argMat, int argID)
{
	palette->setPalette(&argMat, argID);
	materialMode = FK_PARENT_MODE;
	return;
}

void fk_Shape::setMaterialMode(fk_MaterialMode argMode)
{
	materialMode = argMode;
	return;
}

fk_MaterialMode fk_Shape::getMaterialMode(void)
{
	return materialMode;
}

int fk_Shape::getObjMaterialID(void)
{
	return palette->getObjMaterialID();
}

int fk_Shape::getPaletteSize(void)
{
	return palette->getPaletteSize();
}

fk_Material * fk_Shape::getMaterial(int argID)
{
	return palette->getMaterial(argID);
}

vector<fk_Material> * fk_Shape::getMaterialVector(void)
{
	return palette->getMaterialVector();
}

fk_RealShapeType fk_Shape::getRealShapeType(void)
{
	switch(getObjectType()) {
	  case FK_INDEXFACESET:
	  case FK_BLOCK:
	  case FK_CIRCLE:
	  case FK_SPHERE:
	  case FK_PRISM:
	  case FK_CONE:
	  case FK_CAPSULE:
		return FK_SHAPE_IFS;

	  case FK_SOLID:
	  case FK_POLYGON:
	  case FK_POLYLINE:
	  case FK_CLOSEDLINE:
	  case FK_LINE:
		return FK_SHAPE_SOLID;

	  case FK_RECTTEXTURE:
	  case FK_TRITEXTURE:
	  case FK_MESHTEXTURE:
	  case FK_IFSTEXTURE:
		return FK_SHAPE_TEXTURE;

	  case FK_POINT:
	  case FK_PARTICLESET:
		return FK_SHAPE_POINT;

	  case FK_CURVE:
	  case FK_BEZCURVE:
	  case FK_BSPLCURVE:
		return FK_SHAPE_CURVE;

	  case FK_SURFACE:
	  case FK_BEZSURFACE:
	  case FK_BSPLSURFACE:
		return FK_SHAPE_SURFACE;
		
	  case FK_LIGHT:
		return FK_SHAPE_LIGHT;

	  default:
		break;
	}
	return FK_SHAPE_OTHER;
}
