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
#include <FK/VRMLOut.H>
#include <FK/Vertex.h>
#include <FK/Loop.h>
#include <FK/Solid.h>
#include <FK/IndexFace.h>
#include <FK/Material.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;


fk_VRMLOut::fk_VRMLOut(fk_Solid *argSolid)
{
	solid = argSolid;
	ifset = nullptr;

	return;
}

fk_VRMLOut::fk_VRMLOut(fk_IndexFaceSet *argIFSet)
{
	ifset = argIFSet;
	solid = nullptr;

	return;
}

fk_VRMLOut::~fk_VRMLOut()
{
	return;
}

bool fk_VRMLOut::WriteVRMLFile(string argFileName, fk_Material *argMaterial,
							   bool triFlag)
{
	ofstream	ofs(argFileName);

	if(solid == nullptr && ifset == nullptr) {
		return false;
	}

	if(ofs.fail()) return false;

	WriteVRMLHeader(ofs);
	WriteVRMLShape(ofs, argMaterial, triFlag, nullptr, nullptr);
	WriteVRMLFooter(ofs, FK_VRML_NONE);

	ofs.close();

	return true;
}

bool fk_VRMLOut::WriteVRMLFile(string argFileName,
							   vector<double> *argTime,
							   vector<fk_Vector> *argPos,
							   fk_Material *argMaterial,
							   bool triFlag)
{
	ofstream	ofs(argFileName);

	if(ofs.fail()) return false;

	WriteVRMLHeader(ofs);
	WriteVRMLShape(ofs, argMaterial, triFlag, argTime, argPos);
	WriteVRMLFooter(ofs, FK_VRML_INTR);

	ofs.close();

	return true;
}

void fk_VRMLOut::WriteVRMLHeader(ofstream &argOFS)
{
	argOFS << "#VRML V2.0 utf8" << endl << endl;
	argOFS << "Transform {" << endl;
	argOFS << "\tchildren [" << endl;

	return;
}

void fk_VRMLOut::WriteVRMLShape(ofstream &argOFS,
								fk_Material *argMaterial, bool triFlag,
								vector<double> *argTime,
								vector<fk_Vector> *argPos)
{
	WriteVRMLLightInfo(argOFS);
	WriteVRMLNaviInfo(argOFS);

	if(argTime != nullptr && argPos != nullptr) {
		WriteVRMLCoordInterp(argOFS, argTime, argPos);
	}

	argOFS << "\t\tShape {" << endl;

	WriteVRMLMaterial(argOFS, argMaterial);
	if(solid != nullptr) {
		WriteVRMLPointData_Solid(argOFS);
		WriteVRMLIFData_Solid(argOFS, triFlag);
	} else {
		WriteVRMLPointData_IFS(argOFS);
		WriteVRMLIFData_IFS(argOFS, triFlag);
	}

	argOFS << "\t\t\t\tcolorPerVertex TRUE" << endl;
	argOFS << "\t\t\t\tconvex TRUE" << endl;
	argOFS << "\t\t\t}" << endl;
	argOFS << "\t\t}" << endl;

	return;
}

void fk_VRMLOut::WriteVRMLLightInfo(ofstream &argOFS)
{
	string	tab, outStr;

	tab = "\t\t";
	outStr = tab + "DirectionalLight {\n";
	
	tab = "\t\t\t";
	outStr += tab + "ambientIntensity 1.0\n";
	outStr += tab + "direction -1.0 -1.0 1.0\n";

	tab = "\t\t";
	outStr += tab + "}\n\n";
	argOFS << outStr;

	return;
}

void fk_VRMLOut::WriteVRMLNaviInfo(ofstream &argOFS)
{
	string	outStr, tab;

	tab = "\t\t";
	outStr = tab + "NavigationInfo {\n";

	tab = "\t\t\t";
	outStr += tab + "speed 5.0\n";
	outStr += tab + "type \"EXAMINE\"\n";

	tab = "\t\t";
	outStr += tab + "}\n\n";

	argOFS << outStr;
}

void fk_VRMLOut::WriteVRMLMaterial(ofstream &argOFS, fk_Material *argMaterial)
{
	fk_Color		*curColor;
	stringstream	ss;

	if(argMaterial == nullptr) return;

	ss << "\t\t\tappearance Appearance {" << endl;
	ss << "\t\t\t\tmaterial Material {" << endl;

	// Ambient
	curColor = argMaterial->getAmbient();
	ss << "\t\t\t\t\tambientIntensity\t";
	ss << (curColor->getR() + curColor->getG() + curColor->getB())/3.0 << endl;

	// Diffuse
	curColor = argMaterial->getDiffuse();
	ss << "\t\t\t\t\tdiffuseColor\t";
	ss << curColor->getR() << " ";
	ss << curColor->getG() << " ";
	ss << curColor->getB() << endl;

	// Specular
	curColor = argMaterial->getSpecular();
	ss << "\t\t\t\t\tspecularColor\t";
	ss << curColor->getR() << " ";
	ss << curColor->getG() << " ";
	ss << curColor->getB() << endl;

	// Emission
	curColor = argMaterial->getEmission();
	ss << "\t\t\t\t\temissiveColor\t";
	ss << curColor->getR() << " ";
	ss << curColor->getG() << " ";
	ss << curColor->getB() << endl;

	// Shininess
	ss << "\t\t\t\t\tshininess\t";
	ss << argMaterial->getShininess()/128.0 << endl;

	ss << "\t\t\t\t}" << endl;
	ss << "\t\t\t}" << endl;

	argOFS << ss.str();
	return;
}


void fk_VRMLOut::WriteVRMLPointData_Solid(ofstream &argOFS)
{
	fk_Vertex		*curV;
	fk_Vector		pos;
	stringstream	ss;
	
	curV = solid->getNextV(nullptr);

    argOFS << "\t\t\tgeometry IndexedFaceSet {" << endl;
	argOFS << "\t\t\t\tcoord DEF C Coordinate {" << endl;
	argOFS << "\t\t\t\t\tpoint [" << endl;

	while(curV != nullptr) {
		pos = curV->getPosition();
		argOFS << "\t\t\t\t\t\t";
		argOFS << pos.x << " " << pos.y << " " << pos.z;

		curV = solid->getNextV(curV);

		if(curV != nullptr) {
			argOFS << ",";
		}

		argOFS << endl;
		argOFS << ss.str();
	}

	argOFS << "\t\t\t\t\t]" << endl;
	argOFS << "\t\t\t\t}" << endl;

	return;
}

void fk_VRMLOut::WriteVRMLPointData_IFS(ofstream &argOFS)
{
	fk_Vector		pos;
	int				i, pSize;
	
	argOFS << "\t\t\tgeometry IndexedFaceSet {" << endl;
	argOFS << "\t\t\t\tcoord DEF C Coordinate {" << endl;
	argOFS << "\t\t\t\t\tpoint [" << endl;

	pSize = ifset->getPosSize();
	for(i = 0; i < pSize; i++) {
		
		pos = ifset->getPosVec(i);
		argOFS << "\t\t\t\t\t\t";
		argOFS << pos.x << " " << pos.y << " " << pos.z;

		if(i != pSize - 1) argOFS << ",";

		argOFS << endl;
	}

	argOFS << "\t\t\t\t\t]" << endl;
	argOFS << "\t\t\t\t}" << endl;

	return;
}

void fk_VRMLOut::WriteVRMLIFData_Solid(ofstream &argOFS, bool triFlag)
{
	fk_Loop					*curL;
	vector<fk_Vertex *>		vArray;
	fk_Vertex				*tmpV;
	_st						i, maxID, mapID;
	vector<_st>				vMap;
	int						tmpI;

	vMap.clear();
	tmpV = solid->getLastV();
	if(tmpV == nullptr) return;
	maxID = static_cast<_st>(tmpV->getID());
	vMap.resize(maxID+1);
	mapID = 0;
	for(i = 1; i <= maxID; i++) {
		if(solid->existVertex(static_cast<int>(i)) == true) {
			vMap[i] = mapID;
			mapID++;
		}
	}

	curL = solid->getNextL(nullptr);

	argOFS << "\t\t\t\tcoordIndex [" << endl;

	while(curL != nullptr) {
		vArray = solid->getAllVOnL(curL);

		if(triFlag == true && vArray.size() == 4) {
			// 四角形を二つの三角形に分割

			argOFS << "\t\t\t\t\t\t";
			tmpI = static_cast<int>(vMap[static_cast<_st>(vArray[0]->getID())]);
			argOFS << tmpI << ", ";
								   
			tmpI = static_cast<int>(vMap[static_cast<_st>(vArray[1]->getID())]);
			argOFS << tmpI << ", ";

			tmpI = static_cast<int>(vMap[static_cast<_st>(vArray[3]->getID())]);
			argOFS << tmpI << ", ";
					
			argOFS << "-1," << endl;
			argOFS << "\t\t\t\t\t\t";

			tmpI = static_cast<int>(vMap[static_cast<_st>(vArray[3]->getID())]);
			argOFS << tmpI << ", ";
					
			tmpI = static_cast<int>(vMap[static_cast<_st>(vArray[1]->getID())]);
			argOFS << tmpI << ", ";

			tmpI = static_cast<int>(vMap[static_cast<_st>(vArray[2]->getID())]);
			argOFS << tmpI << ", ";
			argOFS << "-1";

		} else {
			// Index データをそのまま出力

			argOFS << "\t\t\t\t\t\t";
			for(i = 0; i < vArray.size(); i++) {
				tmpI = static_cast<int>(vMap[static_cast<_st>(vArray[i]->getID())]);
				argOFS << tmpI << ", ";
			}
			argOFS << "-1";
		}

		curL = solid->getNextL(curL);
		if(curL != nullptr) {
			argOFS << ",";
		}
		argOFS << endl;
	}
 
	argOFS << "\t\t\t\t]" << endl;

	return;
}

void fk_VRMLOut::WriteVRMLIFData_IFS(ofstream &argOFS, bool)
{
	vector<int>		fData;
	_st				fSize, i, j;


	fSize = static_cast<_st>(ifset->getFaceSize());

	argOFS << "\t\t\t\tcoordIndex [" << endl;
	
	for(i = 0; i < fSize; i++) {
		argOFS << "\t\t\t\t\t\t";
		fData = ifset->getFaceData(static_cast<int>(i));
		for(j = 0; j < fData.size(); j++) {
			argOFS << fData[j] << ", ";
		}
		argOFS << "-1";
		if(i != fSize - 1) {
			argOFS << ",";
		}
		argOFS << endl;
	}

	argOFS << "\t\t\t\t]" << endl;
	return;
}

void fk_VRMLOut::WriteVRMLFooter(ofstream &argOFS, fk_VRMLOutMode argMode)
{
	string 	outStr, tab;

	outStr.erase();

	if(argMode == FK_VRML_INTR) {
		tab = "\t\t";
		outStr += tab + "DEF TS TimeSensor {\n";
		tab = "\t\t\t";
		outStr += tab + "cycleInterval 5.0\n";
		outStr += tab + "loop TRUE\n";
		tab = "\t\t";
		outStr += tab + "}\n";
	}

	outStr += "\t]\n";
	outStr += "}\n";

	if(argMode == FK_VRML_INTR) {
		outStr += "ROUTE CI.value_changed TO C.point\n";
		outStr += "ROUTE TS.fraction_changed TO CI.set_fraction\n";
	}

	argOFS << outStr;
	return;
}

void fk_VRMLOut::WriteVRMLCoordInterp(ofstream &argOFS,
									  vector<double> *argTime,
									  vector<fk_Vector> *argPos)
{
	_st				i;
	string			baseTab = "\t\t";
	string			tab;
	string			buf;
	fk_Vector		tmpPos;
	stringstream	ss;
	
	tab = baseTab;
	buf = tab + "DEF CI CoordinateInterpolator {\n";

	tab = baseTab + "\t";
	buf += tab + "key [\n";
	argOFS << buf;

	tab = baseTab + "\t\t";
	for(i = 0; i < argTime->size(); i++) {
		ss.clear();
		ss << (*argTime)[i];
		buf = tab + ss.str();
		if(i != argTime->size() - 1) {
			buf += ",";
		}
		buf += "\n";
		argOFS << buf;
	}

	tab = baseTab + "\t";
	buf = tab + "]\n";
	buf += tab + "keyValue [\n";
	argOFS << buf;

	tab = baseTab + "\t\t";
	for(i = 0; i < argPos->size(); i++) {
		ss.clear();
		tmpPos = (*argPos)[i];
		ss << tmpPos.x << " " << tmpPos.y << " " << tmpPos.z;
		buf = tab + ss.str();
		if(i != argPos->size() - 1) {
			buf += ",";
		}
		buf += "\n";
		argOFS << buf;
	}

	tab = baseTab + "\t";
	buf = tab + "]\n";
	tab = baseTab;
	buf += tab + "}\n";
	argOFS << buf;

	return;
}
