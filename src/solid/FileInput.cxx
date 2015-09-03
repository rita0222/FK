/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
#include <FK/FileInput.H>
#include <FK/DataBase.H>
#include <FK/Palette.h>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Edge.h>
#include <FK/Loop.h>
#include <FK/Error.H>

using namespace std;

fk_FileInput::fk_FileInput(void)
{
	DB = nullptr;
	palette = nullptr;
	sizeMode = true;

	return;
}

fk_FileInput::~fk_FileInput()
{
	return;
}

void fk_FileInput::SetDataBase(fk_DataBase *argDB)
{
	DB = argDB;
	return;
}

void fk_FileInput::SetPalette(fk_Palette *argPal)
{
	palette = argPal;
	return;
}

fk_DataFormatMode fk_FileInput::GetMode(string argFileName)
{
	ifstream			ifs(argFileName);
	char				buffer[16];
	string				tag;
	int					mask;
	string::size_type	i;

	if(ifs.fail()) return FK_ERROR_FILE;
	if(BRead(&mask, 1, ifs) == false) {
		ifs.close();
		return FK_ERROR_FILE;
	}

	if(mask == FK_FILE_MASK) return FK_BINARY_FILE;
	ifs.close();

	ifs.open(argFileName);
	ifs.read(buffer, 15);
	ifs.close();

	tag = buffer;
	while((i = tag.find_first_of("\n\r")) != string::npos) {
		tag.erase(i);
	}

	if(tag.compare("$FK_DATA_FILE$") == 0) {
		return FK_TEXT_FILE;
	}

	return FK_ERROR_FILE;
}

bool fk_FileInput::GetShapeData(string argFileName)
{
	ifstream			ifs;
	bool				retFlg;
	fk_DataFormatMode	mode;


	mode = GetMode(argFileName);

	switch(mode) {
	  case FK_TEXT_FILE:
	  case FK_BINARY_FILE:
		ifs.open(argFileName);
		if(ifs.fail()) return false;
		break;
		
	  default:
		return false;
	}

	retFlg = GetShapeData_(mode, ifs, true);
	ifs.close();
	return retFlg;
}	

bool fk_FileInput::GetShapeData(ifstream &argIFS, fk_DataFormatMode argMode)
{
	return GetShapeData_(argMode, argIFS, false);
}

bool fk_FileInput::GetPaletteData(string argFileName)
{
	ifstream			ifs;
	bool				retFlg;
	fk_DataFormatMode	mode;


	mode = GetMode(argFileName);

	switch(mode) {
	  case FK_TEXT_FILE:
	  case FK_BINARY_FILE:
		ifs.open(argFileName);
		if(ifs.fail()) return false;
		break;

	  default:
		return false;
	}

	retFlg = GetPaletteData_(mode, ifs, true);
	ifs.close();
	return retFlg;
}	

bool fk_FileInput::GetPaletteData(ifstream &argIFS, fk_DataFormatMode argMode)
{
	return GetPaletteData_(argMode, argIFS, false);
}

bool fk_FileInput::GetShapeData_(fk_DataFormatMode argMode, ifstream &argIFS,
								 bool argHeaderFlg)
{
	int			vSize, hSize, eSize, lSize;
	int			majorVer, minorVer, subMinorVer;

	if(argHeaderFlg == true) GetHeader(argMode, argIFS,
									   &majorVer, &minorVer, &subMinorVer);

	GetElemNum(argMode, argIFS, &vSize, &hSize, &eSize, &lSize);
	DB->ResizeData(vSize, hSize, eSize, lSize);

	if(GetElem(argMode, argIFS, vSize, hSize, eSize, lSize) == false) {
		return false;
	}

	if(GetIDAdmin(argMode, argIFS, &(DB->vAdmin), "vadmin") == false) {
		return false;
	}
	if(GetIDAdmin(argMode, argIFS, &(DB->hAdmin), "hadmin") == false) {
		return false;
	}
	if(GetIDAdmin(argMode, argIFS, &(DB->eAdmin), "eadmin") == false) {
		return false;
	}
	if(GetIDAdmin(argMode, argIFS, &(DB->lAdmin), "ladmin") == false) {
		return false;
	}

	return true;
}

void fk_FileInput::GetHeader(fk_DataFormatMode argMode, ifstream &argIFS,
							 int *majorVer, int *minorVer, int *subMinorVer)
{
	string		line;
	int			iBuffer[5];

	switch(argMode) {
	  case FK_TEXT_FILE:
		getline(argIFS, line);
		getline(argIFS, line);
		line += "\n";
		PopWord(&line);
		*majorVer = Str2Int(PopWord(&line));
		*minorVer = Str2Int(PopWord(&line));
		*subMinorVer = Str2Int(PopWord(&line));

		break;
	  case FK_BINARY_FILE:
		BRead(iBuffer, 4, argIFS);
		*majorVer = iBuffer[1];
		*minorVer = iBuffer[2];
		*subMinorVer = iBuffer[3];

		break;
	  default:
		break;
	}
	return;
}

void fk_FileInput::GetElemNum(fk_DataFormatMode argMode, ifstream &argIFS,
							  int *argVSize, int *argHSize,
							  int *argESize, int *argLSize)
{
	string	buffer, tag;
	int		sizeList[5];

	if(argMode == FK_TEXT_FILE) {
		getline(argIFS, buffer);
		tag = PopWord(&buffer);
		*argVSize = Str2Int(PopWord(&buffer));		
		*argHSize = Str2Int(PopWord(&buffer));		
		*argESize = Str2Int(PopWord(&buffer));		
		*argLSize = Str2Int(PopWord(&buffer));		
	} else {
		BRead(sizeList, 5, argIFS);

		*argVSize = sizeList[0];
		*argHSize = sizeList[1];
		*argESize = sizeList[2];
		*argLSize = sizeList[3];
	}

	return;
}

bool fk_FileInput::GetElem(fk_DataFormatMode argMode, ifstream &argIFS,
						   int argVSize, int argHSize,
						   int argESize, int argLSize)
{
	int			i;

	if(argMode == FK_TEXT_FILE) {
		if(GetElemTag(argIFS, "vData") == false) {
			fk_PutError("fk_FileInput", "GetElem", 1, "vTag Error");
			return false;
		}
	}

	for(i = 0; i < argVSize; i++) {
		if(GetVertexData(argMode, argIFS, i+1) == false) {
			fk_PutError("fk_FileInput", "GetElem", 2, "VertexData Error");
			return false;
		}
	}

	if(argMode == FK_TEXT_FILE) {
		if(GetElemTag(argIFS, "hData") == false) {
			fk_PutError("fk_FileInput", "GetElem", 3, "hTag Error");
			return false;
		}
	}

	for(i = 0; i < argHSize; i++) {
		if(GetHalfData(argMode, argIFS, i+1) == false) {
			fk_PutError("fk_FileInput", "GetElem", 4, "HalfData Error");
			return false;
		}
	}

	if(argMode == FK_TEXT_FILE) {
		if(GetElemTag(argIFS, "eData") == false) {
			fk_PutError("fk_FileInput", "GetElem", 5, "eTag Error");
			return false;
		}
	}

	for(i = 0; i < argESize; i++) {
		if(GetEdgeData(argMode, argIFS, i+1) == false) {
			fk_PutError("fk_FileInput", "GetElem", 6, "EdgeData Error");
			return false;
		}
	}

	if(argMode == FK_TEXT_FILE) {
		if(GetElemTag(argIFS, "lData") == false) {
			fk_PutError("fk_FileInput", "GetElem", 7, "lTag Error");
			return false;
		}
	}

	for(i = 0; i < argLSize; i++) {
		if(GetLoopData(argMode, argIFS, i+1) == false) {
			fk_PutError("fk_FileInput", "GetElem", 8, "LoopData Error");
			return false;
		}
	}

	return true;
}

bool fk_FileInput::GetElemTag(ifstream &argIFS, const string &argTag)
{
	string		line, tag;

	getline(argIFS, line);
	line += "\n";
	tag = PopWord(&line);
	if(tag.compare(argTag) != 0) return false;
	return true;
}
	
bool fk_FileInput::GetVertexData(fk_DataFormatMode argMode,
								 ifstream &argIFS, int argID)
{
	string		line;
	int			id, IDSet[3];
	double		pos[3], size = -1.0;

	switch(argMode) {
	  case FK_TEXT_FILE:
		if(GetLineTagStatus(argIFS, &line, "v") == false) return false;

		id = Str2Int(PopWord(&line));
		IDSet[0] = Str2Int(PopWord(&line));
		IDSet[1] = Str2Int(PopWord(&line));
		IDSet[2] = Str2Int(PopWord(&line));
		pos[0] = Str2Double(PopWord(&line));
		pos[1] = Str2Double(PopWord(&line));
		pos[2] = Str2Double(PopWord(&line));

		if(sizeMode == true) {
			size = Str2Double(PopWord(&line));
		}

		if(id != argID && id != FK_UNDEFINED) return false;
		break;

	  case FK_BINARY_FILE:
		if(BRead(IDSet, 3, argIFS) == false) return false;
		if(BRead(pos, 3, argIFS) == false) return false;
		if(sizeMode == true) {
			if(BRead(&size, 1, argIFS) == false) return false;
		}

		break;

	  default:
		return false;
	}

	if(SetVertexData(argID, IDSet[0], IDSet[1], IDSet[2],
					 pos[0], pos[1], pos[2], size) == false) {
		return false;
	}

	return true;
}

bool fk_FileInput::GetHalfData(fk_DataFormatMode argMode,
							   ifstream &argIFS, int argID)
{
	string		line;
	int			id;
	int			IDSet[4];

	switch(argMode) {
	  case FK_TEXT_FILE:
		if(GetLineTagStatus(argIFS, &line, "h") == false) return false;

		id = Str2Int(PopWord(&line));
		IDSet[0] = Str2Int(PopWord(&line));
		IDSet[1] = Str2Int(PopWord(&line));
		IDSet[2] = Str2Int(PopWord(&line));
		IDSet[3] = Str2Int(PopWord(&line));

		if(id != argID && id != FK_UNDEFINED) return false;
		break;

	  case FK_BINARY_FILE:
		if(BRead(IDSet, 4, argIFS) == false) return false;
		break;

	  default:
		return false;
	}

	return SetHalfData(argID, IDSet[0], IDSet[1], IDSet[2], IDSet[3]);
}

bool fk_FileInput::GetEdgeData(fk_DataFormatMode argMode,
							   ifstream &argIFS, int argID)
{
	string		line;
	int			id, IDSet[4];
	double		width = -1.0;

	switch(argMode) {
	  case FK_TEXT_FILE:
		if(GetLineTagStatus(argIFS, &line, "e") == false) return false;

		id = Str2Int(PopWord(&line));
		IDSet[0] = Str2Int(PopWord(&line));
		IDSet[1] = Str2Int(PopWord(&line));
		IDSet[2] = Str2Int(PopWord(&line));
		IDSet[3] = Str2Int(PopWord(&line));
		
		if(sizeMode == true) {
			width = Str2Double(PopWord(&line));
		}

		if(id != argID && id != FK_UNDEFINED) return false;
		break;

	  case FK_BINARY_FILE:
		if(BRead(IDSet, 4, argIFS) == false) return false;
		if(sizeMode == true) {
			if(BRead(&width, 1, argIFS) == false) return false;
		}
		break;

	  default:
		return false;
	}

	return SetEdgeData(argID, IDSet[0], IDSet[1],
					   IDSet[2], IDSet[3], width);
}

bool fk_FileInput::GetLoopData(fk_DataFormatMode argMode,
							   ifstream &argIFS, int argID)
{
	string		line;
	int			id, IDSet[3];

	switch(argMode) {
	  case FK_TEXT_FILE:
		if(GetLineTagStatus(argIFS, &line, "l") == false) return false;

		id = Str2Int(PopWord(&line));
		IDSet[0] = Str2Int(PopWord(&line));
		IDSet[1] = Str2Int(PopWord(&line));
		IDSet[2] = Str2Int(PopWord(&line));

		if(id != argID && id != FK_UNDEFINED) return false;
		break;

	  case FK_BINARY_FILE:
		if(BRead(IDSet, 3, argIFS) == false) return false;
		break;

	  default:
		return false;
	}

	if(SetLoopData(argID, IDSet[0], IDSet[1], IDSet[2]) == false) {
		return false;
	}

	return true;
}

bool fk_FileInput::GetLineTagStatus(ifstream &argIFS, string *argLine,
									const string &argTag)
{
	string	word;

	getline(argIFS, *argLine);
	*argLine += "\n";
	word = PopWord(argLine);
	if(word.compare(argTag) != 0) return false;
	return true;
}
	

bool fk_FileInput::GetIDAdmin(fk_DataFormatMode argMode,
							  ifstream &argIFS, fk_IDAdmin *argIDAdmin,
							  const string &argTag)
{
	string		line, str;

	if(argMode == FK_TEXT_FILE) {
		getline(argIFS, line);
		line += "\n";
		str = PopWord(&line);
		if(str.compare(argTag) != 0) {
			return false;
		}
	}

	return GetAdminDataFile(argMode, argIFS, argIDAdmin);
}

bool fk_FileInput::GetAdminDataFile(fk_DataFormatMode argMode,
									ifstream &argIFS, fk_IDAdmin *argAdmin)
{
	int			listSize, flagSize;

	if(GetAdminHeader(argMode, argIFS, &listSize, &flagSize) == false) {
		return false;
	}

	if(GetAdminEraseList(argMode, argIFS, argAdmin, listSize) == false) {
		return false;
	}

	return true;
}

bool fk_FileInput::GetAdminHeader(fk_DataFormatMode argMode, ifstream &argIFS,
								  int *argListSize, int *argFlagSize)
{
	string	buffer;
	int		sizeSet[2];

	switch(argMode) {
	  case FK_TEXT_FILE:
		getline(argIFS, buffer);
		if(argIFS.fail()) return false;
		*argListSize = Str2Int(PopWord(&buffer));
		*argFlagSize = Str2Int(PopWord(&buffer));
		break;

	  case FK_BINARY_FILE:
		if(BRead(sizeSet, 2, argIFS) == false) return false;

		*argListSize = sizeSet[0];
		*argFlagSize = sizeSet[1];
		break;

	  default:
		return false;
	}

	return true;
}

bool fk_FileInput::GetAdminEraseList(fk_DataFormatMode argMode, ifstream &argIFS,
									 fk_IDAdmin *argAdmin, int argSize)
{
	string	buffer;
	int		i, listID, *array;

	switch(argMode) {
	  case FK_TEXT_FILE:
		for(i = 0; i < argSize; i++) {
			getline(argIFS, buffer);
			if(argIFS.fail()) {
				argAdmin->Init(1);
				return false;
			}
			listID = Str2Int(PopWord(&buffer));
			argAdmin->eraseIDSet->push_back(listID);
		}
		break;

	  case FK_BINARY_FILE:
		if(argSize == 0) break;
		array = new int [static_cast<size_t>(argSize)];

		if(BRead(array, size_t(argSize), argIFS) == false) {
			delete [] array;
			argAdmin->Init(1);
			return false;
		}

		for(i = 0; i < argSize; i++) {
			argAdmin->eraseIDSet->push_back(array[i]);
		}

		delete [] array;
		break;

	  default:
		return false;
	}

	return true;
}

bool fk_FileInput::SetVertexData(int argVID, int argMateID, int argMateMode,
								 int argHID, double argX, double argY,
								 double argZ, double argSize)
{
	fk_Vertex		*v;
	fk_Half			*h = nullptr;
	fk_Vector		pos(argX, argY, argZ);

	v = DB->GetVData(argVID);
	if(v == nullptr) return false;
	if(argHID != FK_UNDEFINED) {
		h = DB->GetHData(argHID);
	} else {
		h = nullptr;
	}

	v->SetOneHalf(h);
	v->SetPosition(pos);

	v->setElemMaterialID(argMateID);
	v->setElemMaterialMode(fk_MaterialMode(argMateMode));

	v->setDrawSize(argSize);

	return true;
}

bool fk_FileInput::SetHalfData(int argHID, int argVID,
							   int argNID, int argPID, int argLID)
{
	fk_Half		*h, *nH, *pH;
	fk_Vertex	*v;
	fk_Loop		*l;

	h = DB->GetHData(argHID);

	if(h == nullptr) return false;

	if(argVID == FK_UNDEFINED) {
		v = nullptr;
	} else {
		v = DB->GetVData(argVID);
		if(v == nullptr) return false;
	}

	nH = DB->GetHData(argNID);
	pH = DB->GetHData(argPID);
	l = DB->GetLData(argLID);

	h->SetVertex(v);
	h->SetNextHalf(nH);
	h->SetPrevHalf(pH);
	h->SetParentLoop(l);

	return true;
}

bool fk_FileInput::SetEdgeData(int argEID, int argMateID, int argMateMode,
							   int argLeftID, int argRightID,
							   double argWidth)
{
	fk_Edge		*e;
	fk_Half		*lH, *rH;

	if(argLeftID == FK_UNDEFINED) return true;

	e = DB->GetEData(argEID);
	if(e == nullptr) return false;

	if(argLeftID == FK_UNDEFINED) {
		lH = nullptr;
	} else {
		lH = DB->GetHData(argLeftID);
		if(lH == nullptr) return false;
	}

	if(argRightID == FK_UNDEFINED) {
		rH = nullptr;
	} else {
		rH = DB->GetHData(argRightID);
		if(rH == nullptr) return false;
	}

	e->SetLeftHalf(lH);
	e->SetRightHalf(rH);
	if(lH != nullptr) lH->SetParentEdge(e);
	if(rH != nullptr) rH->SetParentEdge(e);

	e->setElemMaterialID(argMateID);
	e->setElemMaterialMode(fk_MaterialMode(argMateMode));

	e->setDrawWidth(argWidth);

	return true;
}

bool fk_FileInput::SetLoopData(int argLID, int argMateID, int argMateMode,
							   int argHID)
{
	fk_Loop		*l;
	fk_Half		*h;

	l = DB->GetLData(argLID);
	if(argHID == FK_UNDEFINED) {
		h = nullptr;
	} else {
		h = DB->GetHData(argHID);
		if(h == nullptr) return false;
	}

	l->SetOneHalf(h);

	l->setElemMaterialID(argMateID);
	l->setElemMaterialMode(fk_MaterialMode(argMateMode));

	return true;
}

bool fk_FileInput::GetPaletteData_(fk_DataFormatMode argMode, ifstream &argIFS,
								   bool argHeaderFlg)
{
	int		majorVer, minorVer, subMinorVer;

	if(argHeaderFlg == true) {
		GetHeader(argMode, argIFS, &majorVer, &minorVer, &subMinorVer);
	}

	if(GetMainMaterialData(argMode, argIFS) == false) return false;
	if(GetSubMaterialData(argMode, argIFS) == false) return false;
	return true;
}

bool fk_FileInput::GetMainMaterialData(fk_DataFormatMode argMode, ifstream &argIFS)
{
	string					buffer, tagStr;
	int						valSet[2];
	fk_Material				localMat;


	switch(argMode) {
	  case FK_TEXT_FILE:
		getline(argIFS, buffer);
		tagStr = PopWord(&buffer);
		valSet[0] = Str2Int(PopWord(&buffer));
		valSet[1] = Str2Int(PopWord(&buffer));

		if(tagStr != "mat" || valSet[1] < 0) return false;
		break;

	  case FK_BINARY_FILE:
		if(BRead(valSet, 2, argIFS) == false) return false;
		if(valSet[0] < -1 || valSet[1] < 0) return false;
		break;

	  default:
		return false;
	}

	palette->setObjMaterialID(valSet[0]);
	palette->Resize(valSet[1]);

	if(GetMaterialData(argMode, argIFS, &localMat) == false) {
		return false;
	}

	return true;
}

bool fk_FileInput::GetSubMaterialData(fk_DataFormatMode argMode, ifstream &argIFS)
{
	vector<fk_Material>::size_type	i, palSize;
	vector<fk_Material>				*palStack;

	palStack = palette->getMaterialVector();
	palSize = palStack->size();

	for(i = 0; i < palSize; i++) {
		if(GetMaterialData(argMode, argIFS, &((*palStack)[i])) == false) {
			return false;
		}
	}

	return true;
}

bool fk_FileInput::GetMaterialData(fk_DataFormatMode argMode,
								   ifstream &argIFS, fk_Material *argMat)
{
	string		buffer, tag;
	float		r, g, b, a, shininess, val[12];
	
	switch(argMode) {
	  case FK_TEXT_FILE:
		getline(argIFS, buffer);
		tag = PopWord(&buffer);
		a = Str2Float(PopWord(&buffer));
		argMat->setAlpha(a);

		getline(argIFS, buffer);
		tag = PopWord(&buffer);
		r = Str2Float(PopWord(&buffer));
		g = Str2Float(PopWord(&buffer));
		b = Str2Float(PopWord(&buffer));
		argMat->setAmbient(r, g, b);

		getline(argIFS, buffer);
		tag = PopWord(&buffer);
		r = Str2Float(PopWord(&buffer));
		g = Str2Float(PopWord(&buffer));
		b = Str2Float(PopWord(&buffer));
		argMat->setDiffuse(r, g, b);

		getline(argIFS, buffer);
		tag = PopWord(&buffer);
		r = Str2Float(PopWord(&buffer));
		g = Str2Float(PopWord(&buffer));
		b = Str2Float(PopWord(&buffer));
		argMat->setSpecular(r, g, b);

		getline(argIFS, buffer);
		tag = PopWord(&buffer);
		r = Str2Float(PopWord(&buffer));
		g = Str2Float(PopWord(&buffer));
		b = Str2Float(PopWord(&buffer));
		argMat->setEmission(r, g, b);

		getline(argIFS, buffer);
		tag = PopWord(&buffer);
		shininess = Str2Float(PopWord(&buffer));
		argMat->setShininess(shininess);

		break;

	  case FK_BINARY_FILE:
		if(BRead(&a, 1, argIFS) == false) return false;
		if(BRead(val, 12, argIFS) == false) return false;
		if(BRead(&shininess, 1, argIFS) == false) return false;
		
		argMat->setAlpha(a);
		argMat->setAmbient(val[0], val[1], val[2]);
		argMat->setDiffuse(val[3], val[4], val[5]);
		argMat->setSpecular(val[6], val[7], val[8]);
		argMat->setEmission(val[9], val[10], val[11]);
		argMat->setShininess(shininess);

		break;

	  default:
		return false;
	}
	return true;
}

void fk_FileInput::SetSizeMode(bool argMode)
{
	sizeMode = argMode;
	return;
}
