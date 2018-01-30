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

#define FK_DEF_SIZETYPE
#include <FK/FileOutput.H>
#include <FK/DataBase.H>
#include <FK/Palette.h>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Edge.h>
#include <FK/Loop.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;
using namespace FK;

fk_FileOutput::fk_FileOutput(void)
{
	DB = nullptr;
	palette = nullptr;
	sizeMode = true;
	return;
}

fk_FileOutput::~fk_FileOutput()
{
	return;
}

void fk_FileOutput::SetDataBase(fk_DataBase *argDB)
{
	DB = argDB;
	return;
}

void fk_FileOutput::SetPalette(fk_Palette *argPal)
{
	palette = argPal;
	return;
}

bool fk_FileOutput::PutShapeData(string argFileName, fk_DataFormatMode argMode)
{
	ofstream	ofs(argFileName);

	if(ofs.fail()) return false;

	PutHeader(argMode, ofs);
	if(PutShapeData_(argMode, ofs) == false) {
		ofs.close();
		return false;
	}

	ofs.close();
	return true;
}	
	
bool fk_FileOutput::PutShapeData(ofstream &argOFS, fk_DataFormatMode argMode)
{
	return PutShapeData_(argMode, argOFS);
}

bool fk_FileOutput::PutPaletteData(string argFileName,
								   fk_DataFormatMode argMode)
{
	ofstream	ofs(argFileName);

	if(ofs.fail()) return false;

	PutHeader(argMode, ofs);
	if(PutPaletteData_(argMode, ofs) == false) {
		ofs.close();
		return false;
	}

	ofs.close();
	return true;
}	
	
bool fk_FileOutput::PutPaletteData(ofstream &argOFS, fk_DataFormatMode argMode)
{
	return PutPaletteData_(argMode, argOFS);
}

void fk_FileOutput::PutHeader(fk_DataFormatMode argMode, ofstream &argOFS)
{
	int buffer[4];
	
	switch(argMode) {
	  case FK_TEXT_FILE:
		argOFS << "$FK_DATA_FILE$" << endl;
		argOFS << "$VER: ";
		argOFS << FK_FILE_CURRENT_MAJOR_VERSION << " ";
		argOFS << FK_FILE_CURRENT_MINOR_VERSION << " ";
		argOFS << FK_FILE_CURRENT_SUBMINOR_VERSION << " $" << endl;
		return;

	  case FK_BINARY_FILE:
		
		buffer[0] = FK_FILE_MASK;
		buffer[1] = FK_FILE_CURRENT_MAJOR_VERSION;
		buffer[2] = FK_FILE_CURRENT_MINOR_VERSION;
		buffer[3] = FK_FILE_CURRENT_SUBMINOR_VERSION;
		
		BWrite(buffer, 4, argOFS);
		return;

	  default:
		break;
	}
	return;
}

bool fk_FileOutput::PutShapeData_(fk_DataFormatMode argMode, ofstream &argOFS)
{
	_st		i, vSize, hSize, eSize, lSize;
	int		setSize[5];

	vSize = DB->vSet.size();
	hSize = DB->hSet.size();
	eSize = DB->eSet.size();
	lSize = DB->lSet.size();
	
	setSize[0] = int(vSize);
	setSize[1] = int(hSize);
	setSize[2] = int(eSize);
	setSize[3] = int(lSize);
	setSize[4] = 0;

	switch(argMode) {
		argOFS << "num\t";
		argOFS << setSize[0] << "\t";
		argOFS << setSize[1] << "\t";
		argOFS << setSize[2] << "\t";
		argOFS << setSize[3] << endl;
		break;

	  case FK_BINARY_FILE:

		BWrite(setSize, 5, argOFS);
		break;

	  default:
		return false;
	}

	if(argMode == FK_TEXT_FILE) argOFS << "vData" << endl;
	for(i = 0; i < vSize; i++) {
		PutVertexData(argMode, argOFS, DB->vSet[i]);
	}

	if(argMode == FK_TEXT_FILE) argOFS << "hData" << endl;
	for(i = 0; i < hSize; i++) {
		PutHalfData(argMode, argOFS, DB->hSet[i]);
	}

	if(argMode == FK_TEXT_FILE) argOFS << "eData" << endl;
	for(i = 0; i < eSize; i++) {
		PutEdgeData(argMode, argOFS, DB->eSet[i]);
	}

	if(argMode == FK_TEXT_FILE) argOFS << "lData" << endl;
	for(i = 0; i < lSize; i++) {
		PutLoopData(argMode, argOFS, DB->lSet[i]);
	}

	PutAdminDataFile(argMode, argOFS, &(DB->vAdmin), "vadmin");
	PutAdminDataFile(argMode, argOFS, &(DB->hAdmin), "hadmin");
	PutAdminDataFile(argMode, argOFS, &(DB->eAdmin), "eadmin");
	PutAdminDataFile(argMode, argOFS, &(DB->lAdmin), "ladmin");

	return true;
}


void fk_FileOutput::PutVertexData(fk_DataFormatMode argMode,
								  ofstream &argOFS, fk_Vertex *argV)
{
	fk_Vector	position;
	int			IDSet[3];
	double		pos[3], size;

	IDSet[0] = argV->getElemMaterialID();
	IDSet[1] = argV->getElemMaterialMode();

	if(argV->getOneHalf() != nullptr) {
		IDSet[2] = argV->getOneHalf()->getID();
	} else {
		IDSet[2] = FK_UNDEFINED;
	}

	position = argV->getPosition();
	pos[0] = position.x;
	pos[1] = position.y;
	pos[2] = position.z;
	size = argV->getDrawSize();

	switch(argMode) {
	  case FK_TEXT_FILE:
		argOFS << "\tv\t";
		argOFS << argV->getID() << "\t";
		argOFS << IDSet[0] << "\t";
		argOFS << IDSet[1] << "\t";
		argOFS << IDSet[2] << "\t";
		argOFS << pos[0] << " ";
		argOFS << pos[1] << " ";
		argOFS << pos[2];
		if(sizeMode == true) {
			argOFS << " " << size;
		}
		argOFS << endl;
		break;
		
	  case FK_BINARY_FILE:
		
		BWrite(IDSet, 3, argOFS);
		BWrite(pos, 3, argOFS);
		if(sizeMode == true) {
			BWrite(&size, 1, argOFS);
		}
		
		break;
		
	  default:
		break;
	}

	return;
}

void fk_FileOutput::PutHalfData(fk_DataFormatMode argMode,
								ofstream &argOFS, fk_Half *argH)
{
	int			nHID, pHID, pLID;
	fk_Half		*nH;
	fk_Half		*pH;
	fk_Loop		*pL;
	fk_Vertex	*v;
	int			IDSet[4];

	nHID = pHID = pLID = FK_UNDEFINED;
	nH = argH->getNextHalf();
	pH = argH->getPrevHalf();
	pL = argH->getParentLoop();
	v = argH->getVertex();

	if(nH != nullptr) {
		nHID = nH->getID();
	}
	if(pH != nullptr) {
		pHID = pH->getID();
	}
	if(pL != nullptr) {
		pLID = pL->getID();
	}

	IDSet[0] = v->getID();
	IDSet[1] = nHID;
	IDSet[2] = pHID;
	IDSet[3] = pLID;

	switch(argMode) {
	  case FK_TEXT_FILE:
		argOFS << "\th\t";
		argOFS << argH->getID() << "\t";
		argOFS << IDSet[0] << "\t";
		argOFS << IDSet[1] << "\t";
		argOFS << IDSet[2] << "\t";
		argOFS << IDSet[3] << endl;
		break;
		
	  case FK_BINARY_FILE:		
		
		BWrite(IDSet, 4, argOFS);
		break;
		
	  default:
		break;
	}

	return;
}

void fk_FileOutput::PutEdgeData(fk_DataFormatMode argMode,
								ofstream &argOFS, fk_Edge *argE)
{
	fk_Half		*lH, *rH;
	int			IDSet[4];
	double		width;

	lH = argE->getLeftHalf();
	rH = argE->getRightHalf();

	IDSet[0] = argE->getElemMaterialID();
	IDSet[1] = argE->getElemMaterialMode();
	IDSet[2] = lH->getID();
	IDSet[3] = rH->getID();
	width = argE->getDrawWidth();

	switch(argMode) {
	  case FK_TEXT_FILE:
		argOFS << "\te\t";
		argOFS << argE->getID() << "\t";
		argOFS << IDSet[0] << "\t";
		argOFS << IDSet[1] << "\t";
		argOFS << IDSet[2] << "\t";
		argOFS << IDSet[3];
		if(sizeMode == true) {
			argOFS << " " << width;
		}
		argOFS << endl;
		break;
		
	  case FK_BINARY_FILE:
		
		BWrite(IDSet, 4, argOFS);
		if(sizeMode == true) {
			BWrite(&width, 1, argOFS);
		}
		break;
		
	  default:
		break;
	}

	return;
}

void fk_FileOutput::PutLoopData(fk_DataFormatMode argMode,
								ofstream &argOFS, fk_Loop *argL)
{
	fk_Half		*h;
	int			oneHID = FK_UNDEFINED;
	int			IDSet[3];

	h = argL->getOneHalf();
	if(h != nullptr) {
		oneHID = h->getID();
	}

	IDSet[0] = argL->getElemMaterialID();
	IDSet[1] = argL->getElemMaterialMode();
	IDSet[2] = oneHID;

	switch(argMode) {
	  case FK_TEXT_FILE:
		argOFS << "\tl\t";
		argOFS << argL->getID() << "\t";
		argOFS << IDSet[0] << "\t";
		argOFS << IDSet[1] << "\t";
		argOFS << IDSet[2] << endl;
		break;
		
	  case FK_BINARY_FILE:
		
		BWrite(IDSet, 3, argOFS);
		break;
		
	  default:
		break;
	}

	return;
}

bool fk_FileOutput::PutAdminDataFile(fk_DataFormatMode argMode,
									 ofstream &argOFS, fk_IDAdmin *argAdmin,
									 const string &argTag)
{
	vector<int>		listArray;

	for(auto listP : *(argAdmin->eraseIDSet)) {
		listArray.push_back(listP);
	}

	PutAdminHeader(argMode, argOFS, argAdmin, argTag);
	PutAdminEraseList(argMode, argOFS, &(listArray[0]),
					  int(argAdmin->eraseIDSet->size()));

	return true;
}

void fk_FileOutput::PutAdminHeader(fk_DataFormatMode argMode,
								   ofstream &argOFS, fk_IDAdmin *argAdmin,
								   const string &argTag)
{
	int		sizeSet[2];

	sizeSet[0] = int(argAdmin->eraseIDSet->size());
	sizeSet[1] = int(argAdmin->existFlagSet.size());

	switch(argMode) {
	  case FK_TEXT_FILE:
		argOFS << argTag << endl;
		argOFS << "\t" << sizeSet[0] << "\t" << sizeSet[1] << endl;
		break;
		
	  case FK_BINARY_FILE:
		
		BWrite(sizeSet, 2, argOFS);
		break;
		
	  default:
		break;
	}

	return;
}

void fk_FileOutput::PutAdminEraseList(fk_DataFormatMode argMode, ofstream &argOFS,
									  int *argArray, int argSize)
{
	int		i;

	switch(argMode) {
	  case FK_TEXT_FILE:
		for(i = 0; i < argSize; i++) {
			argOFS << "\t\t" << argArray[i] << endl;
		}
		break;
		
	  case FK_BINARY_FILE:
		if(argSize != 0) {
			BWrite(argArray, size_t(argSize), argOFS);
		}
		break;
		
	  default:
		break;
	}

	return;
}

bool fk_FileOutput::PutPaletteData_(fk_DataFormatMode argMode, ofstream &argOFS)
{
	unsigned int			i;
	vector<fk_Material>		*matVec;
	int						valueSet[2];
	fk_Material				dummyMat;


	matVec = palette->getMaterialVector();

	switch(argMode) {
	  case FK_TEXT_FILE:
		argOFS << "mat\t" << palette->getObjMaterialID();
		argOFS << "\t" << matVec->size() << endl;

		if(PutMaterialData(FK_TEXT_FILE, argOFS, &dummyMat) == false) {
			return false;
		}

		for(i = 0; i < matVec->size(); i++) {
			if(PutMaterialData(FK_TEXT_FILE, argOFS,
							   &((*matVec)[i])) == false) {
				return false;
			}
		}

		break;

	  case FK_BINARY_FILE:
		valueSet[0] = palette->getObjMaterialID();
		valueSet[1] = static_cast<int>(matVec->size());

		BWrite(valueSet, 2, argOFS);

		if(PutMaterialData(FK_BINARY_FILE, argOFS, &dummyMat) == false) {
			return false;
		}

		for(i = 0; i < matVec->size(); i++) {
			if(PutMaterialData(FK_BINARY_FILE, argOFS,
							   &((*matVec)[i])) == false) {
				return false;
			}
		}

		break;

	  default:
		return false;
	}

	return true;
}

bool fk_FileOutput::PutMaterialData(fk_DataFormatMode argMode, ofstream &argOFS,
									fk_Material *argMat)
{
	fk_Color		*col;
	float			value;
	float			colArray[12];

	switch(argMode) {
	  case FK_TEXT_FILE:
		argOFS << "\talpha\t" << argMat->getAlpha() << endl;

		col = argMat->getAmbient();
		argOFS << "\tamb\t";
		argOFS << col->col[0] << "\t";
		argOFS << col->col[1] << "\t";
		argOFS << col->col[2] << endl;

		col = argMat->getDiffuse();
		argOFS << "\tdiff\t";
		argOFS << col->col[0] << "\t";
		argOFS << col->col[1] << "\t";
		argOFS << col->col[2] << endl;

		col = argMat->getSpecular();
		argOFS << "\tspec\t";
		argOFS << col->col[0] << "\t";
		argOFS << col->col[1] << "\t";
		argOFS << col->col[2] << endl;

		col = argMat->getEmission();
		argOFS << "\temis\t";
		argOFS << col->col[0] << "\t";
		argOFS << col->col[1] << "\t";
		argOFS << col->col[2] << endl;

		argOFS << "\tshini\t" << argMat->getShininess() << endl;

		break;

	  case FK_BINARY_FILE:
		value = argMat->getAlpha();
		if(BWrite(&value, 1, argOFS) != 1) return false;

		for(int i = 0; i < 3; i++) {
			colArray[i] = argMat->getAmbient()->col[i];
			colArray[i+3] = argMat->getDiffuse()->col[i];
			colArray[i+6] = argMat->getSpecular()->col[i];
			colArray[i+9] = argMat->getEmission()->col[i];
		}
		
		if(BWrite(colArray, 12, argOFS) == false) return false;
		
		value = argMat->getShininess();
		if(BWrite(&value, 1, argOFS) != 1) return false;

		break;

	  default:
		return false;

	}

	return true;
}

void fk_FileOutput::SetSizeMode(bool argMode)
{
	sizeMode = argMode;
	return;
}
