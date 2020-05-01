#define __FK_ERROR_CODE__
#include <FK/Error.H>
#include <list>
#include <sstream>

using namespace std;
using namespace FK;
using namespace FK::Error;

Data::Data(void)
{
	className = "";
	funcName = "";
	errCode = -1;
	message = "";
	modeFlg = true;

	return;
}

Data::~Data() {}

void Data::Set(const string argClass, const string argFunc,
			   const int argErrCode, const string argMessage)
{
	className = argClass;
	funcName = argFunc;
	errCode = argErrCode;
	message = argMessage;
	modeFlg = true;

	return;
}

void Data::Set(const string argClass, const string argFunc, const int argErrCode)
{
	className = argClass;
	funcName = argFunc;
	errCode = argErrCode;
	message = "";
	modeFlg = true;

	return;
}

void Data::Set(const string argMessage)
{
	message = argMessage;
	modeFlg = false;
	return;
}


void Data::SetClassName(const string argClass)
{
	className = argClass;
	return;
}

void Data::SetFuncName(const string argFunc)
{
	funcName = argFunc;
	return;
}

void Data::SetErrCode(const int argErrCode)
{
	errCode = argErrCode;
	return;
}

void Data::SetErrMessage(const string argMessage)
{
	message = argMessage;
	return;
}

string Data::GetClassName(void) const
{
	return className;
}

string Data::GetFuncName(void) const
{
	return funcName;
}

int Data::GetErrCode(void) const
{
	return errCode;
}

string Data::GetErrMessage(void) const
{
	return message;
}

bool Data::GetMode(void) const
{
	return modeFlg;
}

DataBase::DataBase(void) :
	mode(Mode::NONE), fileMode(false)
{
	_DB.clear();
	return;
}

DataBase::~DataBase()
{
	if(fileMode == true) {
		ofs.close();
	}

	return;
}

void DataBase::SetMode(const Mode argMode)
{
	mode = argMode;
	return;
}

Mode DataBase::GetMode(void) const
{
	return mode;
}

void DataBase::Put(const string argClass, const string argFunc,
				   const int argErrCode, const string argMessage)
{
	if(mode == Mode::NONE) return;

	_DB.push_back(make_unique<Data>());
	auto data = _DB.back().get();

	data->Set(argClass, argFunc, argErrCode, argMessage);

	switch(mode) {
	  case Mode::INTERACTIVE:
	  case Mode::CONSOLE_INTERACTIVE:
	  case Mode::OUT_CONSOLE_INTERACTIVE:
	  case Mode::BROWSER_INTERACTIVE:
	  case Mode::FILE:
		Print();
		break;

	  default:
		break;
	}

	return;
}

void DataBase::Put(const string argClass, const string argFunc, const int argErrCode)
{
	if(mode == Mode::NONE) return;

	_DB.push_back(make_unique<Data>());
	auto data = _DB.back().get();

	data->Set(argClass, argFunc, argErrCode);

	switch(mode) {
	  case Mode::INTERACTIVE:
	  case Mode::CONSOLE_INTERACTIVE:
	  case Mode::OUT_CONSOLE_INTERACTIVE:
	  case Mode::BROWSER_INTERACTIVE:
	  case Mode::FILE:
		Print();
		break;

	  default:
		break;
	}

	return;
}

void DataBase::Put(const string argMessage)
{
	if(mode == Mode::NONE) return;

	_DB.push_back(make_unique<Data>());
	auto data = _DB.back().get();

	data->Set(argMessage);

	switch(mode) {
	  case Mode::INTERACTIVE:
	  case Mode::CONSOLE_INTERACTIVE:
	  case Mode::OUT_CONSOLE_INTERACTIVE:
	  case Mode::BROWSER_INTERACTIVE:
	  case Mode::FILE:
		Print();
		break;

	  default:
		break;
	}

	return;
}

bool DataBase::IsEmpty(void) const
{
	return _DB.empty();
}

bool DataBase::SetFileName(string argFileName)
{
	if(fileMode == true) {
		ofs.close();
	}

	ofs.open(argFileName);

	if(ofs.fail()) {
		fileMode = false;
	} else {
		fileMode = true;
	}

	return fileMode;
}

Browser * DataBase::GetBrowser(void)
{
	return errorBrowser.get();
}

Browser * DataBase::MakeBrowser(void)
{
	errorBrowser = make_unique<Browser>();
	return errorBrowser.get();
}

Browser::Browser(void)
{
	return;
}

Browser::~Browser()
{
	return;
}

bool DataBase::Print(void)
{
	string outStr;
	stringstream ss;

	if(mode == Mode::NONE) return false;
	if(IsEmpty() == true) return false;

	auto data = _DB.front().get();

	outStr.erase();

	if(data->GetMode() == true) {
		outStr = data->GetClassName() + "::" + data->GetFuncName();
		ss << " -- ErrorCode " << data->GetErrCode() << endl;
		outStr += ss.str();
	}

	outStr += data->GetErrMessage();

	switch(mode) {
	  case Mode::INTERACTIVE:
	  case Mode::QUEUE:
		if(errorBrowser != nullptr) errorBrowser->PutAlert(outStr.c_str());
		break;

	  case Mode::CONSOLE_INTERACTIVE:
	  case Mode::CONSOLE_QUEUE:
		cerr << outStr << endl;
		break;

	  case Mode::OUT_CONSOLE_INTERACTIVE:
	  case Mode::OUT_CONSOLE_QUEUE:
		cout << outStr << endl;
		break;

	  case Mode::BROWSER_INTERACTIVE:
	  case Mode::BROWSER_QUEUE:
		if(errorBrowser != nullptr) errorBrowser->PutBrowser(outStr);
		break;

	  case Mode::FILE:
		if(fileMode == true) {
			ofs << outStr << endl;
		}
		break;

	  default:
		break;
	}

	_DB.pop_front();
	return true;
}

namespace FK::Error {
	void SetMode(const Mode argMode)
	{
		GetDB()->SetMode(argMode);
		return;
	}

	Mode GetMode(void)
	{
		return GetDB()->GetMode();
	}

	void Put(const string argClassName, const string argFuncName, const int argErrCode)
	{
		GetDB()->Put(argClassName, argFuncName, argErrCode);
		return;
	}

	void Put(const string argClassName, const string argFuncName,
			 const int argErrCode, const string argMessage)
	{
		GetDB()->Put(argClassName, argFuncName, argErrCode, argMessage);
		return;
	}

	void Put(const string argMessage)
	{
		GetDB()->Put(argMessage);
		return;
	}

	bool fk_ErrorPrint(void)
	{
		return GetDB()->Print();
	}

	bool fk_SetErrorFile(string argFileName)
	{
		return GetDB()->SetFileName(argFileName);
	}

	DataBase * GetDB(void)
	{
		static DataBase errDB;
		return &errDB;
	}

#ifndef FK_CLI_CODE

	void Printf(const char *argFormat, ...)
	{
		va_list			ap;
		char			*buffer = new char [8192];

		va_start(ap, argFormat);
		vsnprintf(&buffer[0], 8191, argFormat, ap);
		va_end(ap);
		GetDB()->Put(buffer);
		delete [] buffer;
		return;
	}

	string StrPrintf(const char *argFormat, ...)
	{
		va_list		ap;
		char		*buffer = new char [8192];
		string		str;

		va_start(ap, argFormat);
		vsnprintf(&buffer[0], 8191, argFormat, ap);
		va_end(ap);
		str = buffer;
		delete [] buffer;
		return str;
	}

#endif // !FK_CLI_CODE
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
