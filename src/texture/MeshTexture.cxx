#define FK_DEF_SIZETYPE
#include <FK/MeshTexture.h>
#include <FK/MQOParser.H>
#include <FK/Math.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_MeshTexture::Member::Member(void) :
	triNum(0), faceIBO(0), faceIndexFlg(false)
{
	return;
}

fk_MeshTexture::fk_MeshTexture(fk_Image *argImage)
	: fk_Texture(argImage), _m(make_unique<Member>())
{
	SetObjectType(fk_Type::MESHTEXTURE);

	GetFaceSize = [this]() { return _m->triNum; };
	StatusUpdate = [this]() {
		modifyAttribute(vertexName);
		modifyAttribute(normalName);
		modifyAttribute(texCoordName);
	};

	FaceIBOSetup = [this]() {
		if(_m->faceIBO == 0) {
			_m->faceIBO = GenBuffer();
			_m->faceIndexFlg = true;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _m->faceIBO);
		if(_m->faceIndexFlg == true) {
			GLsizeiptr size = 3 * GLsizeiptr(_m->triNum) * GLsizeiptr(sizeof(GLuint));
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size,
						 _m->faceIndex.data(), GL_STATIC_DRAW);
			_m->faceIndexFlg = false;
		}
	};

	_m->vertexPosition.setDim(3);
	_m->vertexNormal.setDim(3);
	_m_texCoord->setDim(2);
	
	setShaderAttribute(vertexName, 3, _m->vertexPosition.getP());
	setShaderAttribute(normalName, 3, _m->vertexNormal.getP());
	setShaderAttribute(texCoordName, 2, _m_texCoord->getP());
		
	init();

	return;
}

fk_MeshTexture::~fk_MeshTexture()
{
	_m->posArray.clear();
	_m->coordArray.clear();
	_m->faceIndex.clear();
	_m->vertexPosition.clear();
	_m->vertexNormal.clear();
	_m_texCoord->clear();

	return;
}

void fk_MeshTexture::init(void)
{
	BaseInit();
	_m->triNum = 0;
	_m->posArray.clear();
	_m->coordArray.clear();

	_m->faceIndex.clear();
	_m->vertexPosition.clear();
	_m->vertexNormal.clear();
	_m_texCoord->clear();

	StatusUpdate();

	if(_m->faceIBO != 0) {
		DeleteBuffer(_m->faceIBO);
		_m->faceIBO = 0;
	}
	_m->faceIndexFlg = true;
	
	return;
}

void fk_MeshTexture::FaceUpdate(void)
{
	_st		oldSize = _m->faceIndex.size();
	_m->faceIndex.resize(_st(_m->triNum)*3);
	for(_st i = oldSize; i < _st(_m->triNum)*3; ++i) {
		_m->faceIndex[i] = GLuint(i);
	}
	_m->faceIndexFlg = true;
}


void fk_MeshTexture::PosUpdate(void)
{
	_m->vertexPosition.resize(_m->triNum*3);
	for(int i = 0; i < _m->triNum*3; ++i) {
		_m->vertexPosition.set(i, _m->posArray[_st(i)]);
	}
	modifyAttribute(vertexName);
}

void fk_MeshTexture::PosUpdate(int argTID, int argVID)
{
	if(_m->vertexPosition.getSize() <= (argTID+1)*3) _m->vertexPosition.resize((argTID+1)*3);
	_m->vertexPosition.set(argTID*3 + argVID, _m->posArray[_st(argTID)*3 + _st(argVID)]);
	modifyAttribute(vertexName);
}

void fk_MeshTexture::NormUpdate(void)
{
	_m->vertexNormal.resize(_m->triNum*3);
	for(int i = 0; i < _m->triNum; ++i) {
		_st tid = _st(i)*3;
		fk_Vector norm = (_m->posArray[tid+1] - _m->posArray[tid]) ^
			(_m->posArray[tid+2] - _m->posArray[tid]);
		if(norm.normalize() == false) continue;
		for(int j = 0; j < 3; ++j) {
			_m->vertexNormal.set(i*3 + j, norm);
		}
	}
	modifyAttribute(normalName);
}

void fk_MeshTexture::NormUpdate(int argTID)
{
	if(_m->vertexNormal.getSize() <= (argTID+1)*3) _m->vertexNormal.resize((argTID+1)*3);
	_st id = _st(argTID)*3;
	fk_Vector norm = (_m->posArray[id+1] - _m->posArray[id]) ^
		(_m->posArray[id+2] - _m->posArray[id]);
	if(norm.normalize() == false) return;
	for(int i = 0; i < 3; i++) _m->vertexNormal.set(argTID*3 + i, norm);
	modifyAttribute(normalName);
}

void fk_MeshTexture::TexCoordUpdate(void)
{
	_m_texCoord->resize(_m->triNum*3);

	const fk_Dimension *imageSize = getImageSize();
	const fk_Dimension *bufSize = getBufferSize();

	if(_m->triNum <= 0) return;
	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	double wScale = double(imageSize->w)/double(bufSize->w);
	double hScale = double(imageSize->h)/double(bufSize->h);

	for(int i = 0; i < _m->triNum*3; ++i) {
		_m_texCoord->set(i, _m->coordArray[_st(i)].x * wScale, _m->coordArray[_st(i)].y * hScale);
	}
	modifyAttribute(texCoordName);
}

void fk_MeshTexture::TexCoordUpdate(int argTID, int argVID)
{
	const fk_Dimension *imageSize = getImageSize();
	const fk_Dimension *bufSize = getBufferSize();

	if(_m->triNum <= 0) return;
	if(_m_texCoord->getSize() <= (argTID+1)*3) _m_texCoord->resize((argTID+1)*3);

	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	double wScale = double(imageSize->w)/double(bufSize->w);
	double hScale = double(imageSize->h)/double(bufSize->h);
	int id = argTID*3 + argVID;
	
	_m_texCoord->set(id, _m->coordArray[_st(id)].x * wScale, _m->coordArray[_st(id)].y * hScale);
	modifyAttribute(texCoordName);
}
	
bool fk_MeshTexture::setTriNum(int argNum)
{
	if(argNum < 0) {
		Error::Put("fk_MeshTexture", "setTriNum", 1, "Triangle Number Error.");
		return false;
	}

	_m->triNum = argNum;
	if(argNum == 0) {
		_m->posArray.clear();
		_m->coordArray.clear();
	} else {
		_m->posArray.resize(_st(_m->triNum) * 3);
		_m->coordArray.resize(_st(_m->triNum) * 3);
	}
	FaceUpdate();
	PosUpdate();
	NormUpdate();
	TexCoordUpdate();

	return true;
}

bool fk_MeshTexture::setVertexPos(int argTID, int argVID,
								  double argX, double argY, double argZ)
{
	if(argTID < 0 ||
	   argVID < 0 || argVID > 2) {
		Error::Put("fk_MeshTexture", "setVertexPos", 1, "ID Error.");
		return false;
	}

	if(argTID >= _m->triNum) {
		setTriNum(argTID+1);
	}

	_m->posArray[3 * _st(argTID) + _st(argVID)].set(argX, argY, argZ);
	PosUpdate(argTID, argVID);
	NormUpdate(argTID);

	return true;
}

bool fk_MeshTexture::setVertexPos(int argTID, int argVID, fk_Vector argPos)
{
	if(argTID < 0 ||
	   argVID < 0 || argVID > 2) {
		Error::Put("fk_MeshTexture", "setVertexPos", 2, "ID Error.");
		return false;
	}

	if(argTID >= _m->triNum) {
		setTriNum(argTID+1);
	}

	_m->posArray[3 * _st(argTID) + _st(argVID)] = argPos;
	PosUpdate(argTID, argVID);
	NormUpdate(argTID);

	return true;
}

bool fk_MeshTexture::setTriPos(int argTID, vector<fk_Vector> *argTPos)
{
	_st		tid = _st(argTID);

	if(argTID < 0) {
		Error::Put("fk_MeshTexture", "setTriPos", 1, "ID Error.");
		return false;
	}

	if(argTPos->size() != 3) {
		Error::Put("fk_MeshTexture", "setTriPos", 2, "Vertex Number Error.");
		return false;
	}

	if(argTID >= _m->triNum) {
		setTriNum(argTID+1);
	}

	for(_st i = 0; i < 3; ++i) {
		_m->posArray[tid*3 + i] = (*argTPos)[i];
		PosUpdate(argTID, int(i));
	}
	NormUpdate(argTID);

	return true;
}

bool fk_MeshTexture::setTriPos(int argTID, fk_Vector *argTPos)
{
	_st		tid = _st(argTID);

	if(argTID < 0) {
		Error::Put("fk_MeshTexture", "setTriPos", 3, "Triangle ID Error.");
		return false;
	}

	if(argTID >= _m->triNum) {
		setTriNum(argTID+1);
	}

	for(_st i = 0; i < 3; ++i) {
		_m->posArray[tid*3 + i] = argTPos[i];
		PosUpdate(argTID, int(i));
	}
	NormUpdate(argTID);
			
	return true;
}

bool fk_MeshTexture::setTextureCoord(int argTID, int argVID,
									 double argS, double argT)
{
	if(argTID < 0 ||
	   argVID < 0 || argVID > 2) {
		Error::Put("fk_MeshTexture", "setTextureCoord", 1, "Triangle ID Error.");
		return false;
	}

	if(argS < -fk_Math::EPS || argS > 1.0 + fk_Math::EPS ||
	   argT < -fk_Math::EPS || argT > 1.0 + fk_Math::EPS) {
		Error::Put("fk_MeshTexture", "setTextureCoord", 2, "Texture Coord Error.");
		return false;
	}

	if(argTID >= _m->triNum) {
		setTriNum(argTID+1);
	}

	_m->coordArray[3 * _st(argTID) + _st(argVID)].set(argS, argT);
	TexCoordUpdate(argTID, argVID);

	return true;
}

bool fk_MeshTexture::setTextureCoord(int argTID, int argVID,
									 fk_TexCoord argCoord)
{
	if(argTID < 0 ||
	   argVID < 0 || argVID > 2) {
		Error::Put("fk_MeshTexture", "setTextureCoord", 3, "Triangle ID Error.");
		return false;
	}

	if(argCoord.x < -fk_Math::EPS || argCoord.x > 1.0 + fk_Math::EPS ||
	   argCoord.y < -fk_Math::EPS || argCoord.y > 1.0 + fk_Math::EPS) {
		Error::Put("fk_MeshTexture", "setTextureCoord", 4, "Texture Coord Error.");
		return false;
	}

	if(argTID >= _m->triNum) {
		setTriNum(argTID+1);
	}

	_m->coordArray[3 * _st(argTID) + _st(argVID)] = argCoord;
	TexCoordUpdate(argTID, argVID);
	return true;
}

bool fk_MeshTexture::setTriTextureCoord(int argTID,
										vector<fk_TexCoord> *argTCoord)
{
	_st		tid = _st(argTID);

	if(argTID < 0) {
		Error::Put("fk_MeshTexture", "setTriTextureCoord", 1, "Triangle ID Error.");
		return false;
	}

	if(argTCoord->size() != 3) {
		Error::Put("fk_MeshTexture", "setTriTextureCoord", 2, "Vertex Number Error.");
		return false;
	}

	if(argTID >= _m->triNum) {
		setTriNum(argTID+1);
	}

	for(_st i = 0; i < 3; ++i) {
		_m->coordArray[tid*3 + i] = (*argTCoord)[i];
		TexCoordUpdate(argTID, int(i));
	}
	return true;
}

bool fk_MeshTexture::setTriTextureCoord(int argTID, fk_TexCoord *argTCoord)
{
	_st		tid = _st(argTID);

	if(argTID < 0) {
		Error::Put("fk_MeshTexture", "setTriTextureCoord", 3, "Triangle ID Error.");
		return false;
	}

	if(argTID >= _m->triNum) {
		setTriNum(argTID+1);
	}

	for(_st i = 0; i < 3; ++i) {
		_m->coordArray[tid*3 + i] = argTCoord[i];
		TexCoordUpdate(argTID, int(i));
	}

	return true;
}

int fk_MeshTexture::getTriNum(void)
{
	return _m->triNum;
}

fk_Vector fk_MeshTexture::getVertexPos(int argTID, int argVID)
{
	fk_Vector	dummy(0.0, 0.0, 0.0);

	if(argTID < 0 ||
	   argVID < 0 || argVID > 2) {
		Error::Put("fk_MeshTexture", "getVertexPos", 1, "Triangle ID Error.");
		return dummy;
	}

	return _m->posArray[3 * _st(argTID) + _st(argVID)];
}

fk_TexCoord fk_MeshTexture::getTextureCoord(int argTID, int argVID)
{
	fk_TexCoord	dummy(0.0, 0.0);

	if(argTID < 0 || argTID >= _m->triNum ||
	   argVID < 0 || argVID > 2) {
		Error::Put("fk_MeshTexture", "getTextureCoord", 1, "Triangle ID Error.");
		return dummy;
	}

	return _m->coordArray[3 * _st(argTID) + _st(argVID)];
}

void fk_MeshTexture::putIndexFaceSet(fk_IndexFaceSet *argIF)
{
	vector<int> ifset(_st(_m->triNum) * 3);
	vector<fk_Vector> pos(_st(_m->triNum) * 3);

	for(_st i = 0; i < _st(_m->triNum * 3); i++) {
		ifset[i] = int(i);
		pos[i] = _m->posArray[i];
	}

	argIF->makeIFSet(_m->triNum, 3, ifset.data(), _m->triNum*3, pos.data(), 0);
	return;
}

bool fk_MeshTexture::readMQOFile(string argFileName, string argObjName,
								 bool argContFlg)
{
	unique_ptr<fk_MQOParser> mqoParser(new fk_MQOParser());

	mqoParser->SetMeshTexture(this);
	mqoParser->SetContMode(argContFlg);
	if(mqoParser->ReadMQOFile(argFileName, argObjName, -1, true) == false) return false;
	FaceUpdate();
	PosUpdate();
	NormUpdate();
	TexCoordUpdate();
	return true;
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
