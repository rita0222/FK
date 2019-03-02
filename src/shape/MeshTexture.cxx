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
#include <FK/MeshTexture.h>
#include <FK/MQOParser.H>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_MeshTexture::fk_MeshTexture(fk_Image *argImage)
	: fk_Texture(argImage)
{
	SetObjectType(FK_MESHTEXTURE);

	GetFaceSize = [this]() { return triNum; };
	StatusUpdate = [this]() {
		modifyAttribute(vertexName);
		modifyAttribute(normalName);
		modifyAttribute(texCoordName);
	};

	FaceIBOSetup = [this]() {
		if(faceIBO == 0) {
			glGenBuffers(1, &faceIBO);
			faceIndexFlg = true;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceIBO);
		if(faceIndexFlg == true) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,
						 GLsizei(3*triNum*int(sizeof(GLuint))),
						 faceIndex.data(), GL_STATIC_DRAW);
			faceIndexFlg = false;
		}
	};

	vertexPosition.setDim(3);
	vertexNormal.setDim(3);
	texCoord.setDim(2);
	
	setShaderAttribute(vertexName, 3, vertexPosition.getP());
	setShaderAttribute(normalName, 3, vertexNormal.getP());
	setShaderAttribute(texCoordName, 2, texCoord.getP());
		
	init();

	return;
}

fk_MeshTexture::~fk_MeshTexture()
{
	posArray.clear();
	coordArray.clear();
	faceIndex.clear();
	vertexPosition.clear();
	vertexNormal.clear();
	texCoord.clear();

	return;
}

void fk_MeshTexture::init(void)
{
	BaseInit();
	triNum = 0;
	posArray.clear();
	coordArray.clear();

	faceIndex.clear();
	vertexPosition.clear();
	vertexNormal.clear();
	texCoord.clear();

	StatusUpdate();
	if(faceIBO != 0) {
		glDeleteBuffers(1, &faceIBO);
		faceIBO = 0;
	}
	faceIndexFlg = true;
	
	return;
}

void fk_MeshTexture::FaceUpdate(void)
{
	_st		oldSize = faceIndex.size();
	faceIndex.resize(_st(triNum*3));
	for(_st i = oldSize; i < _st(triNum*3); ++i) {
		faceIndex[i] = GLuint(i);
	}
	faceIndexFlg = true;
}

void fk_MeshTexture::PosUpdate(void)
{
	vertexPosition.resize(triNum*3);
	for(int i = 0; i < triNum*3; ++i) {
		vertexPosition.set(i, posArray[_st(i)]);
	}
	modifyAttribute(vertexName);
}

void fk_MeshTexture::PosUpdate(int argTID, int argVID)
{
	if(vertexPosition.getSize() <= (argTID+1)*3) vertexPosition.resize((argTID+1)*3);
	vertexPosition.set(argTID*3 + argVID, posArray[_st(argTID*3 + argVID)]);
	modifyAttribute(vertexName);
}

void fk_MeshTexture::NormUpdate(void)
{
	vertexNormal.resize(triNum*3);
	for(int i = 0; i < triNum; ++i) {
		_st tid = _st(i*3);
		fk_Vector norm = (posArray[tid+1] - posArray[tid]) ^ (posArray[tid+2] - posArray[tid]);
		if(norm.normalize() == false) continue;
		for(int j = 0; j < 3; ++j) {
			vertexNormal.set(i*3 + j, norm);
		}
	}
	modifyAttribute(normalName);
}

void fk_MeshTexture::NormUpdate(int argTID)
{
	if(vertexNormal.getSize() <= (argTID+1)*3) vertexNormal.resize((argTID+1)*3);
	_st id = _st(argTID*3);
	fk_Vector norm = (posArray[id+1] - posArray[id]) ^ (posArray[id+2] - posArray[id]);
	if(norm.normalize() == false) return;
	for(int i = 0; i < 3; i++) vertexNormal.set(argTID*3 + i, norm);
	modifyAttribute(normalName);
}

void fk_MeshTexture::TexCoordUpdate(void)
{
	texCoord.resize(triNum*3);

	const fk_Dimension *imageSize = getImageSize();
	const fk_Dimension *bufSize = getBufferSize();

	if(triNum <= 0) return;
	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	double wScale = double(imageSize->w)/double(bufSize->w);
	double hScale = double(imageSize->h)/double(bufSize->h);

	for(int i = 0; i < triNum*3; ++i) {
		texCoord.set(i, coordArray[_st(i)].x * wScale, coordArray[_st(i)].y * hScale);
	}
	modifyAttribute(texCoordName);
}

void fk_MeshTexture::TexCoordUpdate(int argTID, int argVID)
{
	const fk_Dimension *imageSize = getImageSize();
	const fk_Dimension *bufSize = getBufferSize();

	if(triNum <= 0) return;
	if(texCoord.getSize() <= (argTID+1)*3) texCoord.resize((argTID+1)*3);

	if(bufSize == nullptr) return;
	if(bufSize->w < 64 || bufSize->h < 64) return;

	double wScale = double(imageSize->w)/double(bufSize->w);
	double hScale = double(imageSize->h)/double(bufSize->h);
	int id = argTID*3 + argVID;
	
	texCoord.set(id, coordArray[_st(id)].x * wScale, coordArray[_st(id)].y * hScale);
	modifyAttribute(texCoordName);
}
	
bool fk_MeshTexture::setTriNum(int argNum)
{
	if(argNum < 0) {
		fk_PutError("fk_MeshTexture", "setTriNum", 1,
					"Triangle Number Error.");
		return false;
	}

	triNum = argNum;
	if(argNum == 0) {
		posArray.clear();
		coordArray.clear();
	} else {
		posArray.resize(_st(triNum * 3));
		coordArray.resize(_st(triNum * 3));
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
		fk_PutError("fk_MeshTexture", "setVertexPos", 1, "ID Error.");
		return false;
	}

	if(argTID >= triNum) {
		setTriNum(argTID+1);
	}

	posArray[_st(3*argTID + argVID)].set(argX, argY, argZ);
	PosUpdate(argTID, argVID);
	NormUpdate(argTID);

	return true;
}

bool fk_MeshTexture::setVertexPos(int argTID, int argVID, fk_Vector argPos)
{
	if(argTID < 0 ||
	   argVID < 0 || argVID > 2) {
		fk_PutError("fk_MeshTexture", "setVertexPos", 2, "ID Error.");
		return false;
	}

	if(argTID >= triNum) {
		setTriNum(argTID+1);
	}

	posArray[_st(3*argTID + argVID)] = argPos;
	PosUpdate(argTID, argVID);
	NormUpdate(argTID);

	return true;
}

bool fk_MeshTexture::setTriPos(int argTID, vector<fk_Vector> *argTPos)
{
	_st		tid = _st(argTID);

	if(argTID < 0) {
		fk_PutError("fk_MeshTexture", "setTriPos", 1,
					"ID Error.");
		return false;
	}

	if(argTPos->size() != 3) {
		fk_PutError("fk_MeshTexture", "setTriPos", 2,
					"Vertex Number Error.");
		return false;
	}

	if(argTID >= triNum) {
		setTriNum(argTID+1);
	}

	for(_st i = 0; i < 3; ++i) {
		posArray[tid*3 + i] = (*argTPos)[i];
		PosUpdate(argTID, int(i));
	}
	NormUpdate(argTID);

	return true;
}

bool fk_MeshTexture::setTriPos(int argTID, fk_Vector *argTPos)
{
	_st		tid = _st(argTID);

	if(argTID < 0) {
		fk_PutError("fk_MeshTexture", "setTriPos", 3,
					"Triangle ID Error.");
		return false;
	}

	if(argTID >= triNum) {
		setTriNum(argTID+1);
	}

	for(_st i = 0; i < 3; ++i) {
		posArray[tid*3 + i] = argTPos[i];
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
		fk_PutError("fk_MeshTexture", "setTextureCoord", 1,
					"Triangle ID Error.");
		return false;
	}

	if(argS < -FK_EPS || argS > 1.0 + FK_EPS ||
	   argT < -FK_EPS || argT > 1.0 + FK_EPS) {
		fk_PutError("fk_MeshTexture", "setTextureCoord", 2,
					"Texture Coord Error.");
		return false;
	}

	if(argTID >= triNum) {
		setTriNum(argTID+1);
	}

	coordArray[_st(argTID*3 + argVID)].set(argS, argT);
	TexCoordUpdate(argTID, argVID);

	return true;
}

bool fk_MeshTexture::setTextureCoord(int argTID, int argVID,
									 fk_TexCoord argCoord)
{
	if(argTID < 0 ||
	   argVID < 0 || argVID > 2) {
		fk_PutError("fk_MeshTexture", "setTextureCoord", 3,
					"Triangle ID Error.");
		return false;
	}

	if(argCoord.x < -FK_EPS || argCoord.x > 1.0 + FK_EPS ||
	   argCoord.y < -FK_EPS || argCoord.y > 1.0 + FK_EPS) {
		fk_PutError("fk_MeshTexture", "setTextureCoord", 4,
					"Texture Coord Error.");
		return false;
	}

	if(argTID >= triNum) {
		setTriNum(argTID+1);
	}

	coordArray[_st(argTID*3 + argVID)] = argCoord;
	TexCoordUpdate(argTID, argVID);
	return true;
}

bool fk_MeshTexture::setTriTextureCoord(int argTID,
										vector<fk_TexCoord> *argTCoord)
{
	_st		tid = _st(argTID);

	if(argTID < 0) {
		fk_PutError("fk_MeshTexture", "setTriTextureCoord", 1,
					"Triangle ID Error.");
		return false;
	}

	if(argTCoord->size() != 3) {
		fk_PutError("fk_MeshTexture", "setTriTextureCoord", 2,
					"Vertex Number Error.");
		return false;
	}

	if(argTID >= triNum) {
		setTriNum(argTID+1);
	}

	for(_st i = 0; i < 3; ++i) {
		coordArray[tid*3 + i] = (*argTCoord)[i];
		TexCoordUpdate(argTID, int(i));
	}
	return true;
}

bool fk_MeshTexture::setTriTextureCoord(int argTID, fk_TexCoord *argTCoord)
{
	_st		tid = _st(argTID);

	if(argTID < 0) {
		fk_PutError("fk_MeshTexture", "setTriTextureCoord", 3,
					"Triangle ID Error.");
		return false;
	}

	if(argTID >= triNum) {
		setTriNum(argTID+1);
	}

	for(_st i = 0; i < 3; ++i) {
		coordArray[tid*3 + i] = argTCoord[i];
		TexCoordUpdate(argTID, int(i));
	}

	return true;
}

int fk_MeshTexture::getTriNum(void)
{
	return triNum;
}

fk_Vector fk_MeshTexture::getVertexPos(int argTID, int argVID)
{
	fk_Vector	dummy(0.0, 0.0, 0.0);

	if(argTID < 0 ||
	   argVID < 0 || argVID > 2) {
		fk_PutError("fk_MeshTexture", "getVertexPos", 1,
					"Triangle ID Error.");
		return dummy;
	}

	return posArray[_st(argTID * 3 + argVID)];
}

fk_TexCoord fk_MeshTexture::getTextureCoord(int argTID, int argVID)
{
	fk_TexCoord	dummy(0.0, 0.0);

	if(argTID < 0 || argTID >= triNum ||
	   argVID < 0 || argVID > 2) {
		fk_PutError("fk_MeshTexture", "getTextureCoord", 1,
					"Triangle ID Error.");
		return dummy;
	}

	return coordArray[_st(argTID * 3 + argVID)];
}

void fk_MeshTexture::putIndexFaceSet(fk_IndexFaceSet *argIF)
{
	int			i;
	int			*ifset;
	fk_Vector	*pos;

	ifset = new int [static_cast<size_t>(triNum * 3)];
	pos = new fk_Vector [static_cast<size_t>(triNum * 3)];

	for(i = 0; i < triNum * 3; i++) {
		ifset[i] = i;
		pos[i] = posArray[_st(i)];
	}

	argIF->makeIFSet(triNum, 3, ifset, triNum*3, pos, 0);

	delete [] ifset;
	delete [] pos;

	return;
}

bool fk_MeshTexture::readMQOFile(string argFileName, string argObjName,
								 bool argContFlg)
{
	fk_MQOParser		mqoParser;

	mqoParser.SetMeshTexture(this);
	mqoParser.SetContMode(argContFlg);
	if(mqoParser.ReadMQOFile(argFileName, argObjName, -1, true) == false) return false;
	FaceUpdate();
	PosUpdate();
	NormUpdate();
	TexCoordUpdate();
	return true;
}
