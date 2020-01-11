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
#include <FK/SMFParser.H>
#include <algorithm>

using namespace std;
using namespace FK;

fk_SMFParser::fk_SMFParser(void)
{
	return;
}

fk_SMFParser::~fk_SMFParser()
{
	return;
}

bool fk_SMFParser::ReadSMFFile(string argFileName)
{
	ifstream				ifs(argFileName);
	int						VtNum;
	int						TriNum;
	vector<fk_Vector>		VData;
	vector< vector<int> >	LIndex;

	if(meshData == nullptr) return false;

	meshData->Init();

	if(ifs.fail()) return false;
	
	if(CheckSMFFile(ifs) == false) {
		ifs.close();
		return false;
	}

	ifs.seekg(0, ios_base::beg);

	if(ReadSMFNumData(ifs, &VtNum, &TriNum) == false) {
		ifs.close();
		return false;
	}

	ifs.seekg(0, ios_base::beg);

	if(ReadSMFVertexData(VtNum, ifs, &VData) == false) {
		ifs.close();
		return false;
	}

	ifs.seekg(0, ios_base::beg);

	if(ReadSMFPolygonData(TriNum, ifs, &LIndex) == false) {
		ifs.close();
		return false;
	}

	ifs.close();
	return meshData->MakeMesh(&VData, &LIndex);
}

bool fk_SMFParser::CheckSMFFile(ifstream &argIFS)
{
	string		line;
	bool		vCheck, fCheck;

	vCheck = false;
	fCheck = false;

	while(getline(argIFS, line)) {
		line += "\n";
		if(vCheck == false) {
			if(line.find("#$vertices") != string::npos) vCheck = true;
		}
		if(fCheck == false) {
			if(line.find("#$faces") != string::npos) fCheck = true;
		}
		if(vCheck == true && fCheck == true) return true;
	}

	return false;
}


bool fk_SMFParser::ReadSMFNumData(ifstream &argIFS, int *argVtNum, int *argTriNum)
{
	bool		loopFlg;
	string		strLine, segName;
	int			tmpVtNum = 0;
	int			tmpTriNum = 0;

	loopFlg = false;

	while(loopFlg == false || getline(argIFS, strLine)) {
		strLine += "\n";
		segName = PopWord(&strLine);
		if(segName == "#$vertices") {
			tmpVtNum = Str2Int(PopWord(&strLine));
		} else if(segName == "#$faces") {
			tmpTriNum = Str2Int(PopWord(&strLine));
		}

		if(tmpVtNum > 0 && tmpTriNum > 0) loopFlg = true;
	}

	*argVtNum = tmpVtNum;
	*argTriNum = tmpTriNum;

	return true;
}

bool fk_SMFParser::ReadSMFVertexData(int argVtNum, ifstream &argIFS,
									 vector<fk_Vector> *argVData)
{
	string		segName, strLine;
	bool		loopFlg;
	double		tmpX, tmpY, tmpZ;
	fk_Vector	tmpVec;

	argVData->clear();
	loopFlg = false;

	while(loopFlg == false || getline(argIFS, strLine)) {
		strLine += "\n";
		segName = PopWord(&strLine);
		if(segName == "v") {
			tmpX = Str2Double(PopWord(&strLine));
			tmpY = Str2Double(PopWord(&strLine));
			tmpZ = Str2Double(PopWord(&strLine));
			tmpVec.set(tmpX, tmpY, tmpZ);
			argVData->push_back(tmpVec);
		}

		if(static_cast<int>(argVData->size()) == argVtNum) loopFlg = true;
	}

	if(loopFlg == false) {
		argVData->clear();
	}

	return loopFlg;
}

bool fk_SMFParser::ReadSMFPolygonData(int argTriNum, ifstream &argIFS,
									  vector< vector<int> > *argLIndex)
{
	vector<int>							polyIndex;
	string								segStr, numStr;
	string::size_type					sIndex, eIndex;
	string::size_type					nsIndex, neIndex;
	int									vID;
	bool								loopFlg;
	int									minID;
	vector< vector<int> >::iterator		indexP;
	vector<int>::iterator				polyP;

	argLIndex->clear();

	loopFlg = false;
	minID = 1;

	while(loopFlg == false && getline(argIFS, segStr)) {
		segStr += "\n";
		sIndex = segStr.find_first_not_of(" \t");

		if(sIndex == string::npos) continue;
		if(segStr[sIndex] != 'f') continue;

		eIndex = segStr.find(",", sIndex+1);
		eIndex = segStr.find_last_of("0123456789", eIndex) + 1;
		neIndex = sIndex;
		polyIndex.clear();

		do {
			nsIndex = neIndex + 1;
			nsIndex = segStr.find_first_of("0123456789", nsIndex);
			neIndex = segStr.find_first_of(" ,", nsIndex + 1);
			numStr = segStr.substr(nsIndex, neIndex - nsIndex);
			vID = atoi(numStr.c_str());
			polyIndex.push_back(vID);
			if(minID > vID) minID = vID;
		} while(neIndex < eIndex);
		reverse(polyIndex.begin(), polyIndex.end());
		argLIndex->push_back(polyIndex);

		if(static_cast<int>(argLIndex->size()) == argTriNum) {
			loopFlg = true;
		} else {
			loopFlg = false;
		}
	}

	if(loopFlg == false) argLIndex->clear();

	if(minID != 1) {
		for(indexP = argLIndex->begin(); indexP != argLIndex->end(); ++indexP) {
			for(polyP = indexP->begin(); polyP != indexP->end(); ++polyP) {
				*polyP += 1 - minID;
			}
		}
	}

	return loopFlg;
}
