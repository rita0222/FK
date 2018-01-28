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
#define __FK_ERROR_CODE__
#include <FK/Error.H>
#include <list>
#include <sstream>

using namespace std;

namespace FK {
	class fk_Window;

	class fk_ErrorData {
	private:

		string		className;
		string		funcName;
		int			errCode;
		string		message;
		bool		modeFlg;

	public:
		fk_ErrorData(void);
		~fk_ErrorData();

		void	Set(const string, const string, const int, const string);
		void	Set(const string, const string, const int);
		void	Set(const string);

		void	SetClassName(const string);
		void	SetFuncName(const string);
		void	SetErrCode(const int);
		void	SetErrMessage(const string);

		string	GetClassName(void) const;
		string	GetFuncName(void) const;
		int		GetErrCode(void) const;
		string	GetErrMessage(void) const;
		bool	GetMode(void) const;
	};	  


	fk_ErrorData::fk_ErrorData(void)
	{
		className = "";
		funcName = "";
		errCode = -1;
		message = "";
		modeFlg = true;

		return;
	}
}

fk_ErrorData::~fk_ErrorData() {}

void fk_ErrorData::Set(const string argClass, const string argFunc,
					   const int argErrCode, const string argMessage)
{
	className = argClass;
	funcName = argFunc;
	errCode = argErrCode;
	message = argMessage;
	modeFlg = true;

	return;
}

void fk_ErrorData::Set(const string argClass,
					   const string argFunc, const int argErrCode)
{
	className = argClass;
	funcName = argFunc;
	errCode = argErrCode;
	message = "";
	modeFlg = true;

	return;
}

void fk_ErrorData::Set(const string argMessage)
{
	message = argMessage;
	modeFlg = false;
	return;
}


void fk_ErrorData::SetClassName(const string argClass)
{
	className = argClass;
	return;
}

void fk_ErrorData::SetFuncName(const string argFunc)
{
	funcName = argFunc;
	return;
}

void fk_ErrorData::SetErrCode(const int argErrCode)
{
	errCode = argErrCode;
	return;
}

void fk_ErrorData::SetErrMessage(const string argMessage)
{
	message = argMessage;
	return;
}

string fk_ErrorData::GetClassName(void) const
{
	return className;
}

string fk_ErrorData::GetFuncName(void) const
{
	return funcName;
}

int fk_ErrorData::GetErrCode(void) const
{
	return errCode;
}

string fk_ErrorData::GetErrMessage(void) const
{
	return message;
}

bool fk_ErrorData::GetMode(void) const
{
	return modeFlg;
}

fk_ErrorDataBase::fk_ErrorDataBase(void)
{
	mode = FK_ERR_NONE;
	DataBase.clear();
	fileMode = false;
	errorBrowser = nullptr;
	
	return;
}

fk_ErrorDataBase::~fk_ErrorDataBase()
{
	fk_ErrorData	*data;

	while(DataBase.empty() == false) {
		data = DataBase.front();
		DataBase.pop_front();
		delete data;
	}

	if(fileMode == true) {
		ofs.close();
	}

	delete errorBrowser;
	return;
}

void fk_ErrorDataBase::SetMode(const fk_ErrorMode argMode)
{
	mode = argMode;
	return;
}

fk_ErrorMode fk_ErrorDataBase::GetMode(void) const
{
	return mode;
}

void fk_ErrorDataBase::PutError(const string argClass, const string argFunc,
								const int argErrCode, const string argMessage)
{
	fk_ErrorData	*data;

	if(mode == FK_ERR_NONE) return;

	data = new fk_ErrorData();

	data->Set(argClass, argFunc, argErrCode, argMessage);
	DataBase.push_back(data);

	switch(mode) {
	  case FK_ERR_INTERACTIVE:
	  case FK_ERR_CONSOLE_INTERACTIVE:
	  case FK_ERR_OUT_CONSOLE_INTERACTIVE:
	  case FK_ERR_BROWSER_INTERACTIVE:
	  case FK_ERR_FILE:
		Print();
		break;

	  default:
		break;
	}

	return;
}

void fk_ErrorDataBase::PutError(const string argClass,
								const string argFunc, const int argErrCode)
{
	fk_ErrorData	*data;

	if(mode == FK_ERR_NONE) return;

	data = new fk_ErrorData();

	data->Set(argClass, argFunc, argErrCode);
	DataBase.push_back(data);

	switch(mode) {
	  case FK_ERR_INTERACTIVE:
	  case FK_ERR_CONSOLE_INTERACTIVE:
	  case FK_ERR_OUT_CONSOLE_INTERACTIVE:
	  case FK_ERR_BROWSER_INTERACTIVE:
	  case FK_ERR_FILE:
		Print();
		break;

	  default:
		break;
	}

	return;
}

void fk_ErrorDataBase::PutError(const string argMessage)
{
	fk_ErrorData	*data;

	if(mode == FK_ERR_NONE) return;

	data = new fk_ErrorData();

	data->Set(argMessage);
	DataBase.push_back(data);

	switch(mode) {
	  case FK_ERR_INTERACTIVE:
	  case FK_ERR_CONSOLE_INTERACTIVE:
	  case FK_ERR_OUT_CONSOLE_INTERACTIVE:
	  case FK_ERR_BROWSER_INTERACTIVE:
	  case FK_ERR_FILE:
		Print();
		break;

	  default:
		break;
	}

	return;
}

bool fk_ErrorDataBase::IsEmpty(void) const
{
	return DataBase.empty();
}

bool fk_ErrorDataBase::SetFileName(string argFileName)
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

fk_ErrorBrowser::fk_ErrorBrowser(void)
{
	return;
}

fk_ErrorBrowser::~fk_ErrorBrowser()
{
	return;
}

bool fk_ErrorDataBase::Print(void)
{
	fk_ErrorData	*data;
	string			outStr;
	stringstream	ss;

	if(mode == FK_ERR_NONE) return false;
	if(IsEmpty() == true) return false;

	data = DataBase.front();
	DataBase.pop_front();

	outStr.erase();

	if(data->GetMode() == true) {
		outStr = data->GetClassName() + "::" + data->GetFuncName();
		ss << " -- ErrorCode " << data->GetErrCode() << endl;
		outStr += ss.str();
	}

	outStr += data->GetErrMessage();

	delete data;

	switch(mode) {
	  case FK_ERR_INTERACTIVE:
	  case FK_ERR_QUEUE:
		if(errorBrowser != nullptr) errorBrowser->PutAlert(outStr.c_str());
		break;

	  case FK_ERR_CONSOLE_INTERACTIVE:
	  case FK_ERR_CONSOLE_QUEUE:
		cerr << outStr << endl;
		break;

	  case FK_ERR_OUT_CONSOLE_INTERACTIVE:
	  case FK_ERR_OUT_CONSOLE_QUEUE:
		cout << outStr << endl;
		break;

	  case FK_ERR_BROWSER_INTERACTIVE:
	  case FK_ERR_BROWSER_QUEUE:
		if(errorBrowser != nullptr) errorBrowser->PutBrowser(outStr);
		break;

	  case FK_ERR_FILE:
		if(fileMode == true) {
			ofs << outStr << endl;
		}
		break;

	  default:
		break;
	}

	return true;
}

namespace FK {
	void fk_SetErrorMode(const fk_ErrorMode argMode)
	{
		fk_GetErrorDB()->SetMode(argMode);
		return;
	}

	fk_ErrorMode fk_GetErrorMode(void)
	{
		return fk_GetErrorDB()->GetMode();
	}

	void fk_PutError(const string argClassName,
					 const string argFuncName,
					 const int argErrCode)
	{
		fk_GetErrorDB()->PutError(argClassName, argFuncName, argErrCode);
		return;
	}

	void fk_PutError(const string argClassName,
					 const string argFuncName,
					 const int argErrCode, const string argMessage)
	{
		fk_GetErrorDB()->PutError(argClassName, argFuncName, argErrCode, argMessage);
		return;
	}

	void fk_PutError(const string argMessage)
	{
		fk_GetErrorDB()->PutError(argMessage);
		return;
	}

	bool fk_ErrorPrint(void)
	{
		return fk_GetErrorDB()->Print();
	}

	bool fk_SetErrorFile(string argFileName)
	{
		return fk_GetErrorDB()->SetFileName(argFileName);
	}

	fk_ErrorDataBase * fk_GetErrorDB(void)
	{
		static fk_ErrorDataBase		errDB;
		return &errDB;
	}

#ifndef FK_CLI_CODE

	void fk_Printf(const char *argFormat, ...)
	{
		va_list			ap;
		char			*buffer = new char [8192];

		va_start(ap, argFormat);
		vsnprintf(&buffer[0], 8191, argFormat, ap);
		va_end(ap);
		fk_GetErrorDB()->PutError(buffer);
		delete [] buffer;
		return;
	}

	string fk_StrPrintf(const char *argFormat, ...)
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
