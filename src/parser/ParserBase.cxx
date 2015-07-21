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
#include <FK/ParserBase.H>
#include <algorithm>

using namespace std;

fk_ParserBase::fk_ParserBase(void)
{
	meshData = nullptr;
	commentStack.clear();

	return;
}

fk_ParserBase::~fk_ParserBase()
{
	return;
}

void fk_ParserBase::SetMeshData(fk_ParserData *argMesh)
{
	meshData = argMesh;
	return;
}

int fk_ParserBase::Str2Int(const string &argStr)
{
	return atoi(argStr.c_str());
}

float fk_ParserBase::Str2Float(const string &argStr)
{
	return float(atof(argStr.c_str()));
}

double fk_ParserBase::Str2Double(const string &argStr)
{
	return atof(argStr.c_str());
}

string fk_ParserBase::PopWord(string *argStr, string argSep)
{
	string				retStr;
	string::size_type	start, end;

	retStr.erase();
	start = argStr->find_first_not_of(" \t\n\r,");
	if(start == string::npos) return retStr;

	if(argSep.length() != 0 &&
	   argStr->find_first_of(argSep, start) == start) {
		end = start + 1;
	} else {
		end = argStr->find_first_of(" \t\n\r," + argSep, start+1);
	}
	
	retStr = argStr->substr(start, end - start);
	argStr->erase(0, end);

	return retStr;
}

string::size_type fk_ParserBase::SearchWord(string *argStr,
											const string &argKey,
											string::size_type argOffset)
{
	string::size_type	findOffset, curOffset;
	string				getWordStr;
	bool				startFlag, endFlag;
	string::size_type	addLen;
	string::size_type	end;

	startFlag = false;
	endFlag = false;

	curOffset = argOffset;
	while(true) {
		addLen = 2;

		if((findOffset = argStr->find(argKey, curOffset)) == string::npos) {
			break;
		}

		if(findOffset == 0) {
			startFlag = true;
			findOffset = 1;
			addLen--;
		} else if(findOffset == argStr->length() - argKey.length()) {
			endFlag = true;
			addLen--;
		}

		getWordStr = argStr->substr(findOffset - 1, argKey.length() + addLen);

		end = getWordStr.length() - 1;
		if(startFlag == true ||
		   getWordStr[0] == ' ' || getWordStr[0] == '\t' ||
		   getWordStr[0] == '\n' ||
		   getWordStr[0] == '}' || getWordStr[0] == '{' ||
		   getWordStr[0] == ']' || getWordStr[0] == '[' ||
		   getWordStr[0] == ',' || getWordStr[0] == '\r') {
			if(endFlag == true ||
			   getWordStr[end] == ' ' ||
			   getWordStr[end] == '\t' || getWordStr[end] == '\n' ||
			   getWordStr[end] == '}' || getWordStr[end] == '{' ||
			   getWordStr[end] == ']' || getWordStr[end] == '[' ||
			   getWordStr[end] == ',' || getWordStr[end] == '\r') {
				return findOffset;
			}
		}

		curOffset = findOffset + 1;
	}

	return string::npos;
}

void fk_ParserBase::PushOneLineCommentSep(const string argSep)
{
	if(find(commentStack.begin(),
			commentStack.end(), argSep) == commentStack.end()) {
		commentStack.push_back(argSep);
	}
	return;
}

bool fk_ParserBase::AddLineList(ifstream &argIFS, string *argLineList)
{
	string				line;
	unsigned int		i;
	string::size_type	index;


	if(!getline(argIFS, line)) return false;
	line += "\n";
	for(i = 0; i < commentStack.size(); i++) {
		index = line.find(commentStack[i]);
		if(index != string::npos) {
			line.erase(index);
		}
	}

	argLineList->append(line);
	return true;
}

bool fk_ParserBase::GetWord(ifstream &argIFS, const string argSep,
							string *argLineList, string *argWord)
{

	*argWord = PopWord(argLineList);
	TrimString(argWord);
	while(argWord->size() == 0) {
		if(AddLineList(argIFS, argLineList) == false) return false;
		ReplaceString(argLineList, argSep, " ");
		*argWord = PopWord(argLineList);
	}
	return true;
}

void fk_ParserBase::StringToLower(string *argStr)
{
	string::size_type	i, size;

	if(argStr == nullptr) return;
	size = argStr->size();

	for(i = 0; i < size; i++) {
		if((*argStr)[i] >= 'A' && (*argStr)[i] <= 'Z') {
			(*argStr)[i] = char((*argStr)[i] + 32);
		}
	}

	return;
}

void fk_ParserBase::TrimString(string *argStr)
{
	if(argStr == nullptr) return;
	if(argStr->size() == 0) return;
	if(argStr->find_first_of(" \t\n\r") == 0) {
		argStr->erase(0, argStr->find_first_not_of(" \t\n\r"));
	}
	if(argStr->find_last_of(" \t\n\r") == argStr->size()-1) {
		argStr->erase(argStr->find_last_not_of(" \t\n\r")+1, string::npos);
	}
	return;
}

int fk_ParserBase::CharCount(const string &argStr, const string &argChar)
{
	int						count = 0;
	string::size_type		p = 0;

	while((p = argStr.find_first_of(argChar, p)) != string::npos) {
		count++;
		p++;
	}
	return count;
}

void fk_ParserBase::ReplaceString(string *argStr,
								  const string &argOld,
								  const string &argNew)
{
	string::size_type		pos;
	
	while((pos = argStr->find_first_of(argOld)) != string::npos) {
		argStr->replace(pos, 1, argNew);
	}
	return;
}


bool fk_ParserBase::IsInteger(const string &argStr)
{
	if(argStr.find_first_not_of("-0123456789 \t") != string::npos) {
		return false;
	}

	return true;
}

bool fk_ParserBase::IsNumeric(const string &argStr)
{
	if(argStr.find_first_not_of("-0123456789. Ee\t") != string::npos) {
		return false;
	}

	return true;
}

void fk_ParserBase::BSwap(int *argP)
{
	int		tmp = *argP;
	char	*p = (char *)argP;
	char	*pTmp = (char *)&tmp;

	p[0] = pTmp[3];
	p[1] = pTmp[2];
	p[2] = pTmp[1];
	p[3] = pTmp[0];
	return;
}

void fk_ParserBase::BSwap(float *argP)
{
	float	tmp = *argP;
	char	*p = (char *)argP;
	char	*pTmp = (char *)&tmp;

	p[0] = pTmp[3];
	p[1] = pTmp[2];
	p[2] = pTmp[1];
	p[3] = pTmp[0];
	return;
}

void fk_ParserBase::BSwap(double *argP)
{
	double	tmp = *argP;
	char	*p = (char *)argP;
	char	*pTmp = (char *)&tmp;

	p[0] = pTmp[7];
	p[1] = pTmp[6];
	p[2] = pTmp[5];
	p[3] = pTmp[4];
	p[4] = pTmp[3];
	p[5] = pTmp[2];
	p[6] = pTmp[1];
	p[7] = pTmp[0];
	return;
}

bool fk_ParserBase::BRead(int *argP, size_t argSize, ifstream &argIFS)
{
	
	argIFS.read((char *)(argP),
				 static_cast<streamsize>(sizeof(int)*argSize));
	if(argIFS.bad()) return false;
	
#ifdef __BIG_ENDIAN__
	for(size_t i = 0; i < argSize; i++) BSwap(&argP[i]);
#endif

	return true;
}

bool fk_ParserBase::BRead(float *argP, size_t argSize, ifstream &argIFS)
{
	
	argIFS.read((char *)(argP),
				 static_cast<streamsize>(sizeof(float)*argSize));
	if(argIFS.bad()) return false;
	
#ifdef __BIG_ENDIAN__
	for(size_t i = 0; i < argSize; i++) BSwap(&argP[i]);
#endif

	return true;
}

bool fk_ParserBase::BRead(double *argP, size_t argSize, ifstream &argIFS)
{
	argIFS.read((char *)(argP),
				 static_cast<streamsize>(sizeof(double)*argSize));
	if(argIFS.bad()) return false;
	
#ifdef __BIG_ENDIAN__
	for(size_t i = 0; i < argSize; i++) BSwap(&argP[i]);
#endif

	return true;
}

bool fk_ParserBase::BWrite(int *argP, size_t argSize, ofstream &argOFS)
{

#ifdef __BIG_ENDIAN__
	for(size_t i = 0; i < argSize; i++) {
		BSwap(&argP[i]);
	}
#endif
	
	argOFS.write((char *)(argP),
				  static_cast<streamsize>(sizeof(int)*argSize));
	if(argOFS.bad()) return false;
	return true;
}

bool fk_ParserBase::BWrite(float *argP, size_t argSize, ofstream &argOFS)
{

#ifdef __BIG_ENDIAN__
	for(size_t i = 0; i < argSize; i++) {
		BSwap(&argP[i]);
	}
#endif
	argOFS.write((char *)(argP),
				  static_cast<streamsize>(sizeof(int)*argSize));
	if(argOFS.bad()) return false;
	return true;
}

bool fk_ParserBase::BWrite(double *argP, size_t argSize, ofstream &argOFS)
{

#ifdef __BIG_ENDIAN__
	for(size_t i = 0; i < argSize; i++) {
		BSwap(&argP[i]);
	}
#endif
	argOFS.write((char *)(argP),
				  static_cast<streamsize>(sizeof(int)*argSize));
	if(argOFS.bad()) return false;
	return true;
}
