/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#include <FK/VRMLParser.H>
#include <FK/Error.H>

using namespace std;

fk_VRMLParser::fk_VRMLParser(void)
{
	return;
}

fk_VRMLParser::~fk_VRMLParser()
{
	return;
}

bool fk_VRMLParser::ReadVRMLFile(string argFileName,
								 bool argMaterialFlag, bool argSolidFlag)
{
	ifstream				ifs(argFileName);
	string					ShapeString;
	vector<fk_Vector>		VecSet;
	vector< vector<int> >	IndexFaceSet;
	vector<int>				ColIDArray;

	if(meshData == NULL) return false;

	if(ifs.fail()) return false;

	if(CheckVRMLFile(ifs) == false) {
		ifs.close();
		return false;
	}

	ifs.seekg(0, ios_base::beg);

	ReadVRMLShapeData(ifs, &ShapeString);

	ifs.close();

	MakeVRMLIFSet(&ShapeString, &VecSet, &IndexFaceSet,
				  &ColIDArray, argSolidFlag);

	meshData->Init();
	if(meshData->MakeMesh(&VecSet, &IndexFaceSet,
						  &ColIDArray, argSolidFlag) == false) {
		return false;
	}

	if(argMaterialFlag == true) {
		if(meshData->getPaletteSize() == 0) {
			meshData->setMaterialMode(FK_CHILD_MODE);
		} else {
			meshData->setMaterialMode(FK_PARENT_MODE);
		}
	} else {
		meshData->setMaterialMode(FK_CHILD_MODE);
	}

	return true;
}

bool fk_VRMLParser::CheckVRMLFile(ifstream &argIFS)
{
	string	lineString;

	getline(argIFS, lineString);
	if(lineString.find("#VRML V2.0") != 0) {
		return false;
	}
	return true;
}

void fk_VRMLParser::ReadVRMLShapeData(ifstream &argIFS, string *argStr)
{
	string				lineString;
	bool				shapeMode, shapeFlag;
	int					bressNum = 0;
	string::size_type	index, comment;

	shapeFlag = false;
	shapeMode = false;
	argStr->erase();

	while(getline(argIFS, lineString)) {
		lineString += "\n";
		comment = lineString.find("#");
		if(comment != string::npos) {
			lineString.erase(comment, string::npos);
		}

		if(SearchWord(&lineString, "Shape") != string::npos) {
			shapeFlag = true;
			shapeMode = true;
			bressNum = 0;
		}

		if(shapeMode == true) {

			*argStr += lineString;

			index = lineString.find("{");

			if(index != string::npos) {
				shapeFlag = false;
				bressNum++;
				while((index = lineString.find("{", index+1)) != string::npos) {
					bressNum++;
				}
			}

			index = lineString.find("}");

			if(index != string::npos) {
				bressNum--;
				while((index = lineString.find("}", index+1)) != string::npos) {
					bressNum--;
				}
			}

			if(shapeFlag == false && bressNum <= 0) {
				shapeMode = false;
			}
		}
	}

	return;
}

void fk_VRMLParser::MakeVRMLIFSet(string *argStr,
								  vector<fk_Vector> *argVSet,
								  vector< vector<int> > *argIF,
								  vector<int> *argMateIDSet,
								  bool argSolidFlag)
{
	string::size_type		sIndex, shapeLast;
	fk_Material				ShapeMaterial;
	int						loopMaterialID;	
	vector<int>				IDMap;
	int						loopNum;
	vector<int>::size_type	lNumS;
	fk_HeapBase<fk_Vector>	heap;


	argVSet->clear();
	argIF->clear();
	argMateIDSet->clear();
	meshData->clearMaterial();

	sIndex = SearchWord(argStr, "Shape");
	do {
		// Shape の終了場所の検出
		shapeLast = SearchVRMLShapeLast(argStr, sIndex);

		// Shape 中のマテリアル情報の取得
		if((GetVRMLShapeMaterial(argStr, &ShapeMaterial,
								 sIndex, shapeLast) == true)) {
			loopMaterialID = meshData->getPaletteSize();
			meshData->pushPalette(ShapeMaterial);
		} else {
			loopMaterialID = FK_UNDEFINED;
		}

		// 頂点座標情報と ID マッピング作成
		IDMap.clear();
		GetVRMLVertexInfo(argStr, argVSet, &heap, &IDMap,
						  sIndex, shapeLast, argSolidFlag);
		loopNum = GetVRMLIndexFSetInfo(argStr, &IDMap, argIF,
									   sIndex, shapeLast);
		lNumS = vector<int>::size_type(loopNum);
		argMateIDSet->insert(argMateIDSet->end(), lNumS, loopMaterialID);

	} while((sIndex = SearchWord(argStr, "Shape", sIndex+1)) != string::npos);
}

string::size_type fk_VRMLParser::SearchVRMLShapeLast(string *argStr,
													 string::size_type argIndex)
{
	string::size_type	curBress, upBress, downBress;
	int					BressNum;

	curBress = argStr->find("{", argIndex);
	BressNum = 1;
	while(BressNum > 0) {
		upBress = argStr->find("{", curBress+1);
		downBress = argStr->find("}", curBress+1);
		if(upBress < downBress) {
			BressNum++;
			curBress = upBress;
		} else {
			BressNum--;
			curBress = downBress;
		}
	}
	return curBress;
}

bool fk_VRMLParser::GetVRMLShapeMaterial(string *argStr, fk_Material *argMate,
										 string::size_type argStart,
										 string::size_type argEnd)
{
	float				tmpR, tmpG, tmpB, tmpValue;
	string::size_type	mateIndex, tmpIndex, lineEnd;
	string				LineStr, valStr;

	argMate->init();
	mateIndex = SearchWord(argStr, "Material", argStart);
	if(mateIndex == string::npos || mateIndex > argEnd) {
		return false;
	}

	// Ambient
	tmpIndex = SearchWord(argStr, "ambientIntensity", mateIndex);
	if(tmpIndex != string::npos && tmpIndex < argEnd) {
		lineEnd = argStr->find("\n", tmpIndex + 1);
		LineStr = argStr->substr(tmpIndex, lineEnd - tmpIndex);
		valStr = LineStr.substr(17);
		tmpValue = Str2Float(PopWord(&valStr));
	} else {
		tmpValue = 0.2f;
	}

	argMate->setAmbient(tmpValue, tmpValue, tmpValue);

	// Diffuse
	tmpIndex = SearchWord(argStr, "diffuseColor", mateIndex);
	if(tmpIndex != string::npos && tmpIndex < argEnd) {
		lineEnd = argStr->find("\n", tmpIndex + 1);
		LineStr = argStr->substr(tmpIndex, lineEnd - tmpIndex);
		valStr = LineStr.substr(13);
		tmpR = Str2Float(PopWord(&valStr));
		tmpG = Str2Float(PopWord(&valStr));
		tmpB = Str2Float(PopWord(&valStr));
	} else {
		tmpR = tmpG = tmpB = 0.2f;
	}
	argMate->setDiffuse(tmpR, tmpG, tmpB);

	// Specular
	tmpIndex = SearchWord(argStr, "specularColor", mateIndex);
	if(tmpIndex != string::npos && tmpIndex < argEnd) {
		lineEnd = argStr->find("\n", tmpIndex + 1);
		LineStr = argStr->substr(tmpIndex, lineEnd - tmpIndex);
		valStr = LineStr.substr(14);
		tmpR = Str2Float(PopWord(&valStr));
		tmpG = Str2Float(PopWord(&valStr));
		tmpB = Str2Float(PopWord(&valStr));
	} else {
		tmpR = tmpG = tmpB = 0.2f;
	}
	argMate->setSpecular(tmpR, tmpG, tmpB);

	// Emission
	tmpIndex = SearchWord(argStr, "emissiveColor", mateIndex);
	if(tmpIndex != string::npos && tmpIndex < argEnd) {
		lineEnd = argStr->find("\n", tmpIndex + 1);
		LineStr = argStr->substr(tmpIndex, lineEnd - tmpIndex);
		valStr = LineStr.substr(14);
		tmpR = Str2Float(PopWord(&valStr));
		tmpG = Str2Float(PopWord(&valStr));
		tmpB = Str2Float(PopWord(&valStr));
	} else {
		tmpR = tmpG = tmpB = 0.0f;
	}
	argMate->setEmission(tmpR, tmpG, tmpB);

	// Shininess
	tmpIndex = SearchWord(argStr, "shininess", mateIndex);
	if(tmpIndex != string::npos && tmpIndex < argEnd) {
		lineEnd = argStr->find("\n", tmpIndex + 1);
		LineStr = argStr->substr(tmpIndex, lineEnd - tmpIndex);
		valStr = LineStr.substr(11);
		tmpValue = Str2Float(PopWord(&valStr));
	} else {
		tmpValue = 0.1f;
	}
	argMate->setShininess(tmpValue);

	return true;
}

void fk_VRMLParser::GetVRMLVertexInfo(string *argStr,
									  vector<fk_Vector> *argVecArray,
									  fk_HeapBase<fk_Vector> *argHeap,
									  vector<int> *argIDMap,
									  string::size_type argSIndex,
									  string::size_type argSLast,
									  bool argSolidFlag)
{
	double				tmpX, tmpY, tmpZ;
	string::size_type	vecIndex, startIndex, endIndex;
	string::size_type	tmpSIndex, tmpEIndex;
	string				vecStr;
	fk_Vector			tmpVec;
	_st					size;
	int					index;
	bool				vecFlag, commaFlg;

	vecIndex = SearchWord(argStr, "Coordinate", argSIndex);
	if(vecIndex == string::npos || vecIndex > argSLast) return;

	startIndex = argStr->find("[", vecIndex);
	endIndex = argStr->find("]", startIndex + 1);
	
	tmpSIndex = argStr->find_first_of("-.0123456789", startIndex + 1);

	commaFlg = (argStr->find(",", tmpSIndex + 1) <
				argStr->find("\n", tmpSIndex + 1)) ? true : false;

	tmpEIndex = argStr->find_first_of(",\n", tmpSIndex + 1);
	vecStr = argStr->substr(tmpSIndex, tmpEIndex - tmpSIndex);

	while(tmpEIndex != string::npos && tmpEIndex <= endIndex &&
		  tmpSIndex != string::npos && tmpSIndex < tmpEIndex) {

		tmpX = Str2Double(PopWord(&vecStr));
		tmpY = Str2Double(PopWord(&vecStr));
		tmpZ = Str2Double(PopWord(&vecStr));

		tmpVec.set(tmpX, tmpY, tmpZ);

		size = argVecArray->size();
		vecFlag = false;
		if(argSolidFlag == true) {

			index = argHeap->getID(&tmpVec);
			if(index != static_cast<int>(size)+1) {
				argIDMap->push_back(index);
				vecFlag = true;
			}
		}

		if(vecFlag == false) {
			argVecArray->push_back(tmpVec);
			argIDMap->push_back(static_cast<int>(size) + 1);
		}

		tmpSIndex = argStr->find_first_of("0123456789.-", tmpEIndex + 1);
		if(commaFlg == true) {
			tmpEIndex = argStr->find_first_of(",]", tmpEIndex + 1);
		} else {
			tmpEIndex = argStr->find_first_of("]\n", tmpEIndex + 1);
		}

		if(tmpSIndex < tmpEIndex) {
			vecStr = argStr->substr(tmpSIndex, tmpEIndex - tmpSIndex);
		}
	}

	return;
}

int fk_VRMLParser::GetVRMLIndexFSetInfo(string *argStr, vector<int> *argIDMap,
										vector< vector<int> > *argIFSet,
										string::size_type argSIndex,
										string::size_type argSLast)
{
	int					tmpID;
	string::size_type	IFIndex, startIndex, endIndex;
	string::size_type	tmpSIndex, tmpEIndex;
	string				IDStr, tmpWord;
	vector<int>			LoopSet;
	int					loopNum;

	IFIndex = SearchWord(argStr, "coordIndex", argSIndex);
	if(IFIndex == string::npos || IFIndex > argSLast) return 0;

	startIndex = argStr->find("[", IFIndex);
	endIndex = argStr->find("]", startIndex + 1);

	tmpSIndex = startIndex + 1;
	tmpEIndex = argStr->find(",", tmpSIndex + 1);

	tmpEIndex = argStr->find_first_of("-.0123456789", tmpSIndex + 1);
	tmpEIndex = argStr->find_first_of(", \t", tmpEIndex+1);

	LoopSet.clear();
	loopNum = 0;
	while(tmpEIndex != string::npos && tmpEIndex <= endIndex) {

		IDStr = argStr->substr(tmpSIndex, tmpEIndex - tmpSIndex);

		if(IDStr.find_first_of("-.0123456789") != string::npos) {

			tmpWord = PopWord(&IDStr);
			tmpID = Str2Int(tmpWord);
			if(tmpID == -1) {
				argIFSet->push_back(LoopSet);
				LoopSet.clear();
				loopNum++;
			} else {
				LoopSet.push_back((*argIDMap)[static_cast<_st>(tmpID)]);
			}

		}

		tmpSIndex = tmpEIndex + 1;
		tmpEIndex = argStr->find_first_of(",] \t", tmpSIndex + 1);
	}

	return loopNum;
}
