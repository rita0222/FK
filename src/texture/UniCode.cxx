#define FK_DEF_SIZETYPE
#include <map>
#include <FK/UniCode.h>
#include <FK/Error.H>
//#include <iconv.h>
#include <sstream>
#include <unicode/unistr.h>
#include <FK/Window.h>

using namespace std;
using namespace FK;

#if defined(_MACOSX_) || defined(_LINUX_)
using iconvpp = char **;
#else
using iconvpp = const char **;
#endif

namespace FK {
	class fk_StrStack {
	private:
		vector<char *>		stack;

	public:
		fk_StrStack(void);
		~fk_StrStack();

		void	push(const string &);
		char *	get(int);
	};

	class fk_StrConverterBase {
	private:
		vector<char>	buffer;
		string CodeName(fk_StringCode);

	public:
		fk_StrConverterBase();
		~fk_StrConverterBase();

		void CommonConvert(fk_StringCode, fk_StringCode, const string &, fk_UniStr *);
		void CommonConvert(fk_StringCode, fk_StringCode, const string &, string *);
	};
}

static fk_StrConverter * getStrConverter(void)
{
	static fk_StrConverter	sc;
	return &sc;
}

static map<string, _st> * getStrMap(void)
{
	static map<string, _st>		strMap;
	return &strMap;
}

static fk_StrStack * getStrStack(void)
{
	static fk_StrStack	strStack;
	return &strStack;
}

static fk_StringCode	defCode = fk_StringCode::UTF16;

fk_UniChar::fk_UniChar(int argCode)
	: fk_BaseObject(fk_Type::UNICHAR)
{
	setCode(argCode);
	return;
}

fk_UniChar::fk_UniChar(const fk_UniChar &argUC)
	: fk_BaseObject()
{
	code = argUC.code;
	return;
}

fk_UniChar & fk_UniChar::operator =(const fk_UniChar &argUC)
{
	code = argUC.code;

	return *this;
}

bool fk_UniChar::readFile(FILE *argFP)
{
	unsigned char	buffer[3];

	if(argFP == nullptr) return false;
	if(fread(buffer, sizeof(unsigned char), 2, argFP) !=
	   2*sizeof(unsigned char)) {
		return false;
	}

	setBuffer(buffer[0], buffer[1]);

	return true;
}

void fk_UniChar::setBuffer(unsigned char argC1, unsigned char argC2)
{
	code = static_cast<int>(argC1) + static_cast<int>(argC2)*256;
	return;
}

void fk_UniChar::setCode(int argCode)
{
	code = argCode;
	return;
}

int fk_UniChar::getCode(void)
{
	return code;
}

bool fk_UniChar::isAscii(void)
{
	if(code < 128) {
		return true;
	}
	return false;
}

char fk_UniChar::getAscii(void)
{
	return char(code);
}

fk_UniStr::fk_UniStr(void)
	: fk_BaseObject(fk_Type::UNISTR)
{
	clear();
	return;
}

fk_UniStr::~fk_UniStr()
{
	clear();
	return;
}

fk_UniStr::fk_UniStr(const fk_UniStr &argStr)
	: fk_BaseObject()
{
	_st		i;
	clear();
	for(i = 0; i < argStr.uniStr.size(); i++) {
		push_back(argStr.uniStr[i]);
	}

	mark = argStr.mark;

	return;
}

fk_UniStr & fk_UniStr::operator =(const fk_UniStr &argStr)
{
	_st		i;

	clear();
	for(i = 0; i < argStr.uniStr.size(); i++) {
		push_back(argStr.uniStr[i]);
	}
	mark = argStr.mark;

	return *this;
}

void fk_UniStr::clear(void)
{
	uniStr.clear();
	markClear();
	return;
}

int fk_UniStr::getLength(void) const
{
	return static_cast<int>(uniStr.size());
}

bool fk_UniStr::fgetLine(FILE *argFP, fk_StringCode argCode)
{
	char		buffer[512];

	if(argFP == nullptr) return false;
	if(feof(argFP) != 0) return false;

	if(argCode == fk_StringCode::UTF16) {
		return fgetLine_UTF16(argFP);
	}

	if(fgets(buffer, 511, argFP) == nullptr) {
		return false;
	}

	buffer[511] = 0;

	convert(buffer, argCode);
	return true;
}

bool fk_UniStr::fgetLine(ifstream *argIFS, fk_StringCode argCode)
{
	string		buffer;

	if(argIFS == nullptr) return false;
	if(argIFS->eof() == true) return false;

	if(argCode == fk_StringCode::UTF16) {
		return fgetLine_UTF16(argIFS);
	}

	if(getline(*argIFS, buffer)) {
		return false;
	}

	convert(buffer, argCode);
	return true;
}

void fk_UniStr::convert(const string &argStr, fk_StringCode argCode)
{
	_st				i;
	fk_UniChar		uniChar;

	clear();
	switch(argCode) {
	  case fk_StringCode::UTF16:
		for(i = 0; i < argStr.size(); i += 2) {
			uniChar.setBuffer(static_cast<unsigned char>(argStr[i]),
							  static_cast<unsigned char>(argStr[i+1]));
			push_back(&uniChar);
		}
		break;

	  case fk_StringCode::JIS:
		getStrConverter()->convertJIS(argStr, this);
		break;

	  case fk_StringCode::SJIS:
		getStrConverter()->convertSJIS(argStr, this);
		break;

	  case fk_StringCode::EUC:
		getStrConverter()->convertEUC(argStr, this);
		break;

	  case fk_StringCode::UTF8:
		getStrConverter()->convertUTF8(argStr, this);
		break;

	  default:
		break;
	}

	return;
}

bool fk_UniStr::fgetLine_UTF16(FILE *argFP)
{
	unsigned char	buffer[3];
	fk_UniChar		uniChar;

	if(argFP == nullptr) return false;

	if(fread(static_cast<unsigned char *>(&buffer[0]),
			 sizeof(unsigned char), 2, argFP) != 2) {
		return false;
	}

	do {

		uniChar.setBuffer(buffer[0], buffer[1]);
		if(uniChar.getCode() == 10) {	// CR
			if(getLength() != 0) {
				if(getCode(getLength()-1) == 13) {
					pop_back();
				}
			}
			push_back(uniChar.getCode());
			break;
		}

		if(uniChar.getCode() != 65279) {
			push_back(uniChar.getCode());
		}

	} while(fread(static_cast<unsigned char *>(&buffer[0]),
				  sizeof(unsigned char), 2, argFP) == 2);

	return true;
}

bool fk_UniStr::fgetLine_UTF16(ifstream *argIFS)
{
	unsigned char	buffer[3];
	fk_UniChar		uniChar;

	if(argIFS == nullptr) return false;

	argIFS->read((char *)(&buffer[0]), sizeof(unsigned char) * 2);
	do {
		if(argIFS->bad()) return false;
		uniChar.setBuffer(buffer[0], buffer[1]);
		if(uniChar.getCode() == 10) {	// CR
			if(getLength() != 0) {
				if(getCode(getLength()-1) == 13) {
					pop_back();
				}
			}
			push_back(uniChar.getCode());
			break;
		}

		if(uniChar.getCode() != 65279) {
			push_back(uniChar.getCode());
		}

	} while(argIFS->read((char *)(&buffer[0]), sizeof(unsigned char) * 2));

	return true;
}

bool fk_UniStr::readFile(string argFileName, fk_StringCode argCode)
{
	ifstream	ifs(argFileName);

	if(ifs.fail()) {
		fk_PutError("fk_UniStr", "readFile", 1);
		return false;
	}

	clear();

	while(fgetLine(&ifs, argCode) == true) {};
	ifs.close();

	return true;
}

int fk_UniStr::getCode(int argID) const
{
	if(argID < 0 || argID >= getLength()) {
		return -1;
	}

	return uniStr[static_cast<_st>(argID)];
}

#ifndef FK_CLI_CODE
void fk_UniStr::printf(fk_StringCode argCode, const char *argFormat, ...)
{
	va_list		ap;
	char		buffer[65536];
	string		str;

	va_start(ap, argFormat);
	vsnprintf(buffer, 65535, argFormat, ap);
	va_end(ap);
	str = buffer;
	convert(buffer, argCode);
	return;
}
#endif

int fk_UniStr::find(int argStart, int argCode)
{
	int		i;

	if(argStart < 0 || argStart >= getLength()) {
		return -1;
	}

	for(i = argStart; i < getLength(); i++) {
		if(argCode == uniStr[static_cast<_st>(i)]) {
			return i;
		}
	}

	return -1;
}

int fk_UniStr::find(int argStart, unsigned char argC1, unsigned char argC2)
{
	int		code;

	code = static_cast<int>(argC1) * static_cast<int>(argC2)*256;
	return find(argStart, code);
}

void fk_UniStr::pop_back(void)
{
	if(getLength() == 0) return;

	uniStr.pop_back();
	return;
}

void fk_UniStr::push_back(fk_UniChar *argUC)
{
	if(argUC == nullptr) return;

	uniStr.push_back(argUC->getCode());
	return;
}

void fk_UniStr::push_back(fk_UniChar argUC)
{
	uniStr.push_back(argUC.getCode());
	return;
}

void fk_UniStr::push_back(int argUC)
{
	uniStr.push_back(argUC);
	return;
}

void fk_UniStr::copyStr(fk_UniStr *argStr)
{
	_st		i;

	if(argStr == nullptr) return;

	clear();
	for(i = 0; i < argStr->uniStr.size(); i++) {
		uniStr.push_back(argStr->uniStr[i]);
	}

	return;
}

void fk_UniStr::Print(string argStr)
{
	string			prefix;
	int				i;
	stringstream	ss;
	
	if(argStr.length() == 0) {
		prefix = "str";
	} else {
		prefix = argStr;
	}

	for(i = 0; i < getLength(); i++) {
		ss.clear();
		ss << prefix << "[" << i << "] = " << getCode(i) << endl;
		fk_PutError(ss.str());
	}
	return;
}

void fk_UniStr::markClear(void)
{
	mark = 0;
	return;
}

bool fk_UniStr::getLine(fk_UniStr *argStr)
{
	if(mark == getLength()) return false;

	if(argStr == nullptr) return false;

	argStr->clear();

	for(;mark < getLength(); mark++) {
		if(getCode(mark) == 10) {
			mark++;
			break;
		}

		argStr->push_back(uniStr[static_cast<_st>(mark)]);
	}

	return true;
}

fk_StrConverterBase::fk_StrConverterBase(void)
{
	return;
}

fk_StrConverterBase::~fk_StrConverterBase()
{
	return;
}

string fk_StrConverterBase::CodeName(fk_StringCode argCode)
{
	switch(argCode) {
	  case fk_StringCode::UTF16:
		return "utf16";

	  case fk_StringCode::UTF8:
		return "utf8";

	  case fk_StringCode::JIS:
		return "jis8";

	  case fk_StringCode::SJIS:
		return "shift-jis";

	  case fk_StringCode::EUC:
		return "euc-jp";

	  default:
		break;
	}
	return "";
}

void fk_StrConverterBase::CommonConvert(fk_StringCode argInCode, fk_StringCode argOutCode,
										const string &argInStr, string *argOutStr)
{
	string inName = CodeName(argInCode);
	string outName = CodeName(argOutCode);

	icu::UnicodeString src(argInStr.c_str(), inName.c_str());
	int32_t length = src.extract(0, src.length(), nullptr, outName.c_str());

	buffer.resize(_st(length+1));
	src.extract(0, src.length(), &buffer[0], outName.c_str());
	*argOutStr = string(buffer.begin(), buffer.end()-1);
}

void fk_StrConverterBase::CommonConvert(fk_StringCode argInCode, fk_StringCode argOutCode,
										const string &argInStr, fk_UniStr *argOutStr)
{
	string outStr;
	fk_UniChar uniChar;

	CommonConvert(argInCode, argOutCode, argInStr, &outStr);
	argOutStr->clear();

	for(_st i = 2; i < outStr.length(); i += 2) {
		uniChar.setBuffer(static_cast<unsigned char>(outStr[i]),
						  static_cast<unsigned char>(outStr[i+1]));
		argOutStr->push_back(&uniChar);
		//fk_Window::printf("c = (%d, %d)", int(outStr[i]), int(outStr[i+1]));
	}
}


fk_StrConverter::fk_StrConverter(void)
{
	base = new fk_StrConverterBase();

	return;
}

fk_StrConverter::~fk_StrConverter()
{
	delete base;
	return;
}
void fk_StrConverter::convertJIS(const string &argStr, fk_UniStr *outStr)
{
	base->CommonConvert(fk_StringCode::JIS, fk_StringCode::UTF16, argStr, outStr);
	return;
}

void fk_StrConverter::convertSJIS(const string &argStr, fk_UniStr *outStr)
{
	base->CommonConvert(fk_StringCode::SJIS, fk_StringCode::UTF16, argStr, outStr);
	return;
}

void fk_StrConverter::convertEUC(const string &argStr, fk_UniStr *outStr)
{
	base->CommonConvert(fk_StringCode::EUC, fk_StringCode::UTF16, argStr, outStr);
	return;
}

void fk_StrConverter::convertUTF8(const string &argStr, fk_UniStr *outStr)
{
	base->CommonConvert(fk_StringCode::UTF8, fk_StringCode::UTF16, argStr, outStr);
	return;
}

void fk_StrConverter::ConvertJIS_UTF8(const string &argStr, string *outStr)
{
	base->CommonConvert(fk_StringCode::JIS, fk_StringCode::UTF8, argStr, outStr);
	return;
}

void fk_StrConverter::ConvertSJIS_UTF8(const string &argStr, string *outStr)
{
	base->CommonConvert(fk_StringCode::SJIS, fk_StringCode::UTF8, argStr, outStr);
	return;
}

void fk_StrConverter::ConvertEUC_UTF8(const string &argStr, string *outStr)
{
	base->CommonConvert(fk_StringCode::EUC, fk_StringCode::UTF8, argStr, outStr);
	return;
}

void fk_StrConverter::ConvertUTF16_UTF8(const string &argStr, string *outStr)
{
	base->CommonConvert(fk_StringCode::UTF16, fk_StringCode::UTF8, argStr, outStr);
	return;
}

void fk_StrConverter::convert_UTF8(const string &argStr, string *outStr, fk_StringCode argCode)
{
	if(outStr == nullptr) return;

	switch(argCode) {
	  case fk_StringCode::JIS:
		ConvertJIS_UTF8(argStr, outStr);
		break;

	  case fk_StringCode::SJIS:
		ConvertSJIS_UTF8(argStr, outStr);
		break;

	  case fk_StringCode::EUC:
		ConvertEUC_UTF8(argStr, outStr);
		break;

	  case fk_StringCode::UTF16:
		ConvertUTF16_UTF8(argStr, outStr);
		break;

	  case fk_StringCode::UTF8:
		*outStr = argStr;
		break;

	  default:
		return;
	}
	return;
}

void fk_StrConverter::ConvertJIS_SJIS(const string &argStr, string *outStr)
{
	base->CommonConvert(fk_StringCode::JIS, fk_StringCode::SJIS, argStr, outStr);
	return;
}

void fk_StrConverter::ConvertEUC_SJIS(const string &argStr, string *outStr)
{
	base->CommonConvert(fk_StringCode::EUC, fk_StringCode::SJIS, argStr, outStr);
	return;
}

void fk_StrConverter::ConvertUTF8_SJIS(const string &argStr, string *outStr)
{
	base->CommonConvert(fk_StringCode::UTF8, fk_StringCode::SJIS, argStr, outStr);
	return;
}

void fk_StrConverter::ConvertUTF16_SJIS(const string &argStr, string *outStr)
{
	base->CommonConvert(fk_StringCode::UTF16, fk_StringCode::SJIS, argStr, outStr);
	return;
}

void fk_StrConverter::convert_SJIS(const string &argStr, string *outStr, fk_StringCode argCode)
{
	if(outStr == nullptr) return;

	switch(argCode) {
	  case fk_StringCode::JIS:
		ConvertJIS_SJIS(argStr, outStr);
		break;

	  case fk_StringCode::EUC:
		ConvertEUC_SJIS(argStr, outStr);
		break;

	  case fk_StringCode::UTF8:
		ConvertUTF8_SJIS(argStr, outStr);
		break;

	  case fk_StringCode::UTF16:
		ConvertUTF16_SJIS(argStr, outStr);
		break;

	  case fk_StringCode::SJIS:
		*outStr = argStr;
		break;

	  default:
		return;
	}
	return;
}

fk_StrStack::fk_StrStack(void)
{
	stack.clear();
	return;
}

fk_StrStack::~fk_StrStack()
{
	_st		i;

	for(i = 0; i < stack.size(); i++) {
		delete [] stack[i];
	}
	stack.clear();
	return;
}

void fk_StrStack::push(const string &argStr)
{
	char *p;

	p = new char [argStr.length()+1];
	// copy(p, string::npos)はオーバーランの危険性があるので非推奨らしい
	memcpy(p, argStr.c_str(), argStr.length());
	p[argStr.length()] = 0;
	stack.push_back(p);
	return;
}

char * fk_StrStack::get(int argID)
{
	return stack[static_cast<_st>(argID)];
}

void fk_Code::setInputCoding(fk_StringCode argCode)
{
	defCode = argCode;
}

char * fk_Code::utf8(const string &argStr)
{
	return utf8(argStr, defCode);
}

char * fk_Code::utf8(const string &argStr, fk_StringCode argCode)
{
	string		newStr;
	_st			id;

	if(getStrMap()->find(argStr) == getStrMap()->end()) {
		getStrConverter()->convert_UTF8(argStr, &newStr, argCode);
		id = getStrMap()->size();
		(*getStrMap())[argStr] = id;
		getStrStack()->push(newStr);
	} else {
		id = (*getStrMap())[argStr];
	}

	return getStrStack()->get(static_cast<int>(id));
}

char * fk_Code::sjis(const string &argStr)
{
	return sjis(argStr, defCode);
}

char * fk_Code::sjis(const string &argStr, fk_StringCode argCode)
{
	string		newStr;
	_st			id;

	if(getStrMap()->find(argStr) == getStrMap()->end()) {
		getStrConverter()->convert_SJIS(argStr, &newStr, argCode);
		id = getStrMap()->size();
		(*getStrMap())[argStr] = id;
		getStrStack()->push(newStr);
	} else {
		id = (*getStrMap())[argStr];
	}

	return getStrStack()->get(static_cast<int>(id));
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
