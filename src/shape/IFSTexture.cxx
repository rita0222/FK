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
#include <FK/IFSTexture.h>
#include <FK/MQOParser.H>
#include <FK/D3DXParser.H>
#include <FK/Error.H>
#include <FK/Window.h>

using namespace std;
using namespace FK;

fk_IFSTexture::fk_IFSTexture(fk_Image *argImage)
	: fk_Texture(argImage)
{
	GetFaceSize = [this]() {
		return ifs->getFaceSize();
	};

	StatusUpdate = [this]() {
		ShapeUpdate();
		TexCoordUpdate();
	};

	FaceIBOSetup = [this]() {
		ifs->FaceIBOSetup();
	};

	SetObjectType(FK_IFSTEXTURE);
	ifs = new fk_IndexFaceSet;
	coordArray.clear();
	commonList.clear();
	connectMode = true;

	setShaderAttribute(vertexName, 3, ifs->GetVertexP());
	setShaderAttribute(normalName, 3, ifs->GetNormP());
	texCoord.setDim(2);
	setShaderAttribute(texCoordName, 2, texCoord.getP());

	modifyAttribute(vertexName);
	modifyAttribute(normalName);
	modifyAttribute(texCoordName);
	return;
}

fk_IFSTexture::~fk_IFSTexture()
{
	coordArray.clear();
	commonList.clear();
	delete ifs;
	return;
}

vector< vector<int> > * fk_IFSTexture::GetCommonList(void)
{
	return &commonList;
}

void fk_IFSTexture::init(void)
{
	BaseInit();
	coordArray.clear();
	commonList.clear();
	return;
}

fk_TexCoord fk_IFSTexture::getTextureCoord(int argTID, int argVID)
{
	fk_TexCoord	coord(0.0, 0.0);
	int			index;

	index = ifs->getFaceData(argTID, argVID);
	if(index < 0) {
		fk_PutError("fk_IFSTexture", "getTextureCoord", 1,
					"Face ID Error.");
		return coord;
	}

	return coordArray[_st(index)];
}

fk_IndexFaceSet * fk_IFSTexture::getIFS(void)
{
	return ifs;
}

void fk_IFSTexture::ShapeUpdate(void)
{
	modifyAttribute(vertexName);
	modifyAttribute(normalName);
}

void fk_IFSTexture::TexCoordUpdate(void)
{
	texCoord.resize(int(coordArray.size()));

	const fk_Dimension *imageSize = getImageSize();
	const fk_Dimension *bufSize = getBufferSize();

	if(ifs->getFaceSize() == 0) return;
	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	double wScale = double(imageSize->w)/double(bufSize->w);
	double hScale = double(imageSize->h)/double(bufSize->h);

	for(_st i = 0; i < coordArray.size(); ++i) {
		texCoord.set(int(i), coordArray[i].x * wScale, coordArray[i].y * hScale);
	}
	modifyAttribute(texCoordName);
}

void fk_IFSTexture::TexCoordUpdate(int argID)
{
	const fk_Dimension *imageSize = getImageSize();
	const fk_Dimension *bufSize = getBufferSize();

	if(ifs->getFaceSize() == 0) return;
	if(texCoord.getSize() <= argID) texCoord.resize(argID+1);

	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	double wScale = double(imageSize->w)/double(bufSize->w);
	double hScale = double(imageSize->h)/double(bufSize->h);

	if(texCoord.getSize() <= argID) texCoord.resize(argID+1);

	texCoord.set(argID, coordArray[_st(argID)].x * wScale, coordArray[_st(argID)].y * hScale);
}

void fk_IFSTexture::cloneShape(fk_IFSTexture *argIT)
{
	ifs->cloneShape(argIT->ifs);
	if(argIT->IsLocalImage() == true) {
		SetLocalImage();
		getImage()->copyImage(argIT->getImage());
	} else {
		setImage(argIT->getImage());
	}
	coordArray = argIT->coordArray;
	commonList = argIT->commonList;

	StatusUpdate();
	return;
}

void fk_IFSTexture::setTextureCoord(int argFID, int argVID,
									fk_TexCoord &argCoord)
{
	int			id;
	_st			id_;

	id = ifs->getFaceData(argFID, argVID);
	if(id < 0) return;

	id_ = _st(id);
	if(id_ >= coordArray.size()) {
		coordArray.resize(id_ + 1);
	}
	coordArray[id_] = argCoord;
	TexCoordUpdate(id);
	
	return;
}

bool fk_IFSTexture::readMQOFile(string argFileName,
								string argObjName,
								int argMateID, bool argContFlg)
{
	fk_MQOParser		*mqoParser = new fk_MQOParser();
	bool				retVal;

	mqoParser->SetIFSTexture(this, ifs);
	mqoParser->SetContMode(argContFlg);

	mqoParser->IFSListUpdate = [](fk_IFSTexture *argIFSTex, fk_MQOListSet *argListSet) {
		auto	tmpCommonList = argIFSTex->GetCommonList();

		tmpCommonList->resize(argListSet->size());
		for(_st i = 0; i < argListSet->size(); i++) {
			for(_st j = 1; j < argListSet->at(i).size(); j++) {
				tmpCommonList->at(i).push_back(argListSet->at(i).at(j).id);
			}
		}
		return;
	};

	retVal = mqoParser->ReadMQOFile(argFileName, argObjName, argMateID, true);
	delete mqoParser;

	if(retVal == false) return false;

	if(connectMode == true) SetConnectNormal();

	StatusUpdate();

	return true;
}

bool fk_IFSTexture::readMQOData(unsigned char *argBuffer,
								string argObjName,
								int argMateID, bool argContFlg)
{
	fk_MQOParser		*mqoParser = new fk_MQOParser();
	bool				retVal;

	mqoParser->SetIFSTexture(this, ifs);
	mqoParser->SetContMode(argContFlg);

	mqoParser->IFSListUpdate = [](fk_IFSTexture *argIFSTex, fk_MQOListSet *argListSet) {
		auto	tmpCommonList = argIFSTex->GetCommonList();

		tmpCommonList->resize(argListSet->size());
		for(_st i = 0; i < argListSet->size(); i++) {
			for(_st j = 1; j < argListSet->at(i).size(); j++) {
				tmpCommonList->at(i).push_back(argListSet->at(i).at(j).id);
			}
		}
		return;
	};

	retVal = mqoParser->ReadMQOData(argBuffer, argObjName, argMateID, true);
	delete mqoParser;

	if(retVal == false) return false;

	if(connectMode == true) SetConnectNormal();

	StatusUpdate();

	return true;
}

bool fk_IFSTexture::readD3DXFile(string argFileName, string argObjName,
								 int argMateID)
{
	fk_D3DXParser		*d3dxParser = new fk_D3DXParser();
	bool				retVal;
	bool				animFlg;

	d3dxParser->SetIFSTexture(this);
	retVal = d3dxParser->ReadD3DXFile(argFileName, argObjName,
									  argMateID, true, &animFlg);

	if(animFlg == true) setAnimationTime(-1.0);
	delete d3dxParser;
	StatusUpdate();
	return retVal;
}

void fk_IFSTexture::setConnectMode(bool argMode)
{
	connectMode = argMode;
	return;
}

bool fk_IFSTexture::getConnectMode(void)
{
	return connectMode;
}

void fk_IFSTexture::SetConnectNormal(void)
{
	_st			i, j;
	fk_Vector	tmpNorm;

	for(i = 0; i < commonList.size(); i++) {
		if(commonList[i].size() == 0) continue;
		tmpNorm = ifs->getVNorm(static_cast<int>(i));
		for(j = 0; j < commonList[i].size(); j++) {
			tmpNorm += ifs->getVNorm(commonList[i][j]);
		}

		tmpNorm.normalize();

		ifs->setVNorm(static_cast<int>(i), tmpNorm);
		for(j = 0; j < commonList[i].size(); j++) {
			ifs->setVNorm(commonList[i][j], tmpNorm);
		}
	}

	return;
}

bool fk_IFSTexture::moveVPosition(int argID, const fk_Vector &argV,
								  int argOrder)
{
	_st		i, trueID;
	int		tmp = argID - argOrder;

	if(tmp < 0) return false;
	trueID = _st(tmp);
	if(trueID >= commonList.size()) return false;

	if(ifs->moveVPosition(static_cast<int>(trueID), argV) == false) {
		return false;
	}
	for(i = 0; i < commonList[trueID].size(); i++) {
		if(ifs->moveVPosition(commonList[trueID][i], argV) == false) {
			return false;
		}
	}

	ShapeUpdate();
	return true;
}

bool fk_IFSTexture::moveVPosition(int argID,
								  double argX, double argY, double argZ,
								  int argOrder)
{
	fk_Vector		v(argX, argY, argZ);

	return moveVPosition(argID, v, argOrder);
}

bool fk_IFSTexture::moveVPosition(int argID, double *argP, int argOrder)
{
	fk_Vector		v(argP[0], argP[1], argP[2]);

	return moveVPosition(argID, v, argOrder);
}

void fk_IFSTexture::setAnimationTime(double argTime)
{
	ifs->setAnimationTime(argTime);
	return;
}

void fk_IFSTexture::setBVHMotion(fk_BVHBase *argBVH)
{
	ifs->setBVHMotion(argBVH);
	return;
}

void fk_IFSTexture::forceUpdateAttr(void)
{
	fk_Shape::forceUpdateAttr();
	ifs->forceUpdateAttr();
	StatusUpdate();
}
