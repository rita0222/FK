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
#include <FK/History.H>
#include <FK/Error.H>

using namespace std;

static const fk_Command		dummyCom;
static const fk_Vector		dummyVec;
static const string			dummyStr;

fk_History::fk_History(void)
{
	Init();
	return;
}

fk_History::~fk_History(void)
{
	Init();
	return;
}

void fk_History::Init(void)
{
	comStack.clear();
	boolStack.clear();
	intStack.clear();
	vecStack.clear();
	doubleStack.clear();
	strStack.clear();

	curIndex = -1;
	defFlag = false;
	return;
}

bool fk_History::Open(const int argComID)
{
	fk_Command		com;
	bool			maxFlg = true;

	if(defFlag == true) return false;
	defFlag = true;
	curIndex++;
	if(static_cast<int>(comStack.size()) > curIndex) {
		maxFlg = false;
	}

	comStack.resize(static_cast<_st>(curIndex+1));

	if(maxFlg == true) {
		com.SetCommandID(argComID);
		com.SetBoolIndex(static_cast<unsigned int>(boolStack.size()));
		com.SetIntIndex(static_cast<unsigned int>(intStack.size()));
		com.SetVecIndex(static_cast<unsigned int>(vecStack.size()));
		com.SetDoubleIndex(static_cast<unsigned int>(doubleStack.size()));
		com.SetStrIndex(static_cast<unsigned int>(strStack.size()));
		comStack[static_cast<_st>(curIndex)] = com;
	} else {
		com = comStack[static_cast<_st>(curIndex)];
		boolStack.resize(static_cast<_st>(com.GetBoolIndex()));
		intStack.resize(static_cast<_st>(com.GetIntIndex()));
		vecStack.resize(static_cast<_st>(com.GetVecIndex()));
		doubleStack.resize(static_cast<_st>(com.GetDoubleIndex()));
		strStack.resize(static_cast<_st>(com.GetStrIndex()));
		comStack[static_cast<_st>(curIndex)].SetCommandID(argComID);
	}

	return true;
}

bool fk_History::Close(void)
{
	if(defFlag == false) return false;
	defFlag = false;
	return true;
}

void fk_History::PushBool(const bool argBool)
{
	if(defFlag == false) {
		fk_PutError("fk_History", "PushBool", 1, "Command Open Error.");
		return;
	}

	if(argBool == true) {
		boolStack.push_back(static_cast<char>(1));
	} else {
		boolStack.push_back(static_cast<char>(0));
	}
	return;
}

void fk_History::PushInt(const int argInt)
{
	if(defFlag == false) {
		fk_PutError("fk_History", "PushBool", 1, "Command Open Error.");
		return;
	}

	intStack.push_back(argInt);
	return;
}

void fk_History::PushVec(const fk_Vector argVec)
{
	if(defFlag == false) {
		fk_PutError("fk_History", "PushVec", 1, "Command Open Error.");
		return;
	}

	vecStack.push_back(argVec);
	return;
}

void fk_History::PushDouble(const double argDouble)
{
	if(defFlag == false) {
		fk_PutError("fk_History", "PushDouble", 1, "Command Open Error.");
		return;
	}

	doubleStack.push_back(argDouble);
	return;
}

void fk_History::PushStr(const string argStr)
{
	if(defFlag == false) {
		fk_PutError("fk_History", "PushStr", 1, "Command Open Error.");
		return;
	}

	strStack.push_back(argStr);
	return;
}

int fk_History::GetComIndex(void) const
{
	if(defFlag == true) {
		fk_PutError("fk_History", "GetComIndex", 1, "Command Open Error.");
		return -1;
	}

	return curIndex;
}

fk_Command fk_History::GetCom(void) const
{
	if(defFlag == true) {
		fk_PutError("fk_History", "GetCom", 1, "Command Open Error.");
		return dummyCom;
	}

	if(curIndex == -1) {
		fk_PutError("fk_History", "GetCom", 2, "Stack Empty Error.");
		return dummyCom;
	}
	return comStack[static_cast<_st>(curIndex)];
}

fk_Command fk_History::GetCom(const unsigned int argIndex) const
{
	if(defFlag == true) {
		fk_PutError("fk_History", "GetCom", 3, "Command Open Error.");
		return dummyCom;
	}

	if(curIndex == -1 || static_cast<int>(argIndex) > curIndex) {
		fk_PutError("fk_History", "GetCom", 4, "Stack OverFlow Error.");
		return dummyCom;
	}
	return comStack[argIndex];
}

bool fk_History::GetBool(const unsigned int argIndex) const
{
	if(defFlag == true) {
		fk_PutError("fk_History", "GetBool", 1, "Command Open Error.");
		return true;
	}

	if(argIndex >= boolStack.size()) {
		fk_PutError("fk_History", "GetBool", 2, "Stack OverFlow Error.");
		return true;
	}

	if(boolStack[argIndex] == char(1)) {
		return true;
	}
	return false;
}

int fk_History::GetInt(const unsigned int argIndex) const
{
	if(defFlag == true) {
		fk_PutError("fk_History", "GetInt", 1, "Command Open Error.");
		return -1;
	}

	if(argIndex >= intStack.size()) {
		fk_PutError("fk_History", "GetInt", 2, "Stack OverFlow Error.");
		return -1;
	}

	return intStack[argIndex];
}

fk_Vector fk_History::GetVec(const unsigned int argIndex) const
{
	if(defFlag == true) {
		fk_PutError("fk_History", "GetVec", 1, "Command Open Error.");
		return dummyVec;
	}

	if(argIndex >= vecStack.size()) {
		fk_PutError("fk_History", "GetVec", 2, "Stack OverFlow Error.");
		return dummyVec;
	}

	return vecStack[argIndex];
}


double fk_History::GetDouble(const unsigned int argIndex) const
{
	if(defFlag == true) {
		fk_PutError("fk_History", "GetDouble", 1, "Command Open Error.");
		return 0.0;
	}

	if(argIndex >= doubleStack.size()) {
		fk_PutError("fk_History", "GetDouble", 2, "Stack OverFlow Error.");
		return 0.0;
	}

	return doubleStack[argIndex];
}

string fk_History::GetStr(const unsigned int argIndex) const
{
	if(defFlag == true) {
		fk_PutError("fk_History", "GetStr", 1, "Command Open Error.");
		return dummyStr;
	}

	if(argIndex >= strStack.size()) {
		fk_PutError("fk_History", "GetStr", 2, "Stack OverFlow Error.");
		return dummyStr;
	}

	return strStack[argIndex];
}

void fk_History::SetMark(bool argFlg)
{
	if(defFlag == true) {
		fk_PutError("fk_History", "SetMark", 1, "Command Open Error.");
		return;
	}

	if(curIndex < 0) return;

	comStack[static_cast<_st>(curIndex)].SetMarkStatus(argFlg);
	return;
}

bool fk_History::GetMarkStatus(void)
{
	if(defFlag == true) {
		fk_PutError("fk_History", "GetMarkStatus", 1, "Command Open Error.");
		return false;
	}
	
	if(curIndex < 0) return false;
	
	return comStack[static_cast<_st>(curIndex)].GetMarkStatus();
}

bool fk_History::Undo(void)
{
	if(defFlag == true) {
		fk_PutError("fk_History", "Undo", 1, "Command Open Error.");
		return false;
	}

	if(curIndex == -1) {
		return false;
	}

	curIndex--;
	return true;
}

bool fk_History::Undo(unsigned int argTimes)
{
	int times, trueTimes;
	times = static_cast<int>(argTimes);
	
	if(defFlag == true) {
		fk_PutError("fk_History", "Undo", 2, "Command Open Error.");
		return false;
	}
	
	trueTimes = (times <= curIndex) ? times : curIndex + 1;
	curIndex -= trueTimes;
	return true;
}

bool fk_History::Redo(void)
{
	if(defFlag == true) {
		fk_PutError("fk_History", "Redo", 1, "Command Open Error.");
		return false;
	}

	if(curIndex + 1 == static_cast<int>(comStack.size())) {
		return false;
	}

	curIndex++;
	return true;
}

bool fk_History::Redo(unsigned int argTimes)
{
	int trueTimes, maxSize, times;
	times = static_cast<int>(argTimes);
	
	if(defFlag == true) {
		fk_PutError("fk_History", "Redo", 2, "Command Open Error.");
		return false;
	}
	
	maxSize = static_cast<int>(comStack.size());
	trueTimes = (curIndex + times >= maxSize) ? maxSize - curIndex - 1: times;
	
	curIndex += trueTimes;
	return true;
}

void fk_History::Print(void)
{
	_st			i, j;
	string		str;
	fk_Command	com1, com2;

	for(i = 0; i <= (unsigned int)(curIndex); i++) {
		com1 = comStack[i];
		if(i == comStack.size() - 1) {
			com2.SetBoolIndex(static_cast<unsigned int>(boolStack.size()));
			com2.SetIntIndex(static_cast<unsigned int>(intStack.size()));
			com2.SetVecIndex(static_cast<unsigned int>(vecStack.size()));
			com2.SetDoubleIndex(static_cast<unsigned int>(doubleStack.size()));
			com2.SetStrIndex(static_cast<unsigned int>(strStack.size()));
		} else {
			com2 = comStack[i+1];
		}

		fk_Printf("Com[%d] (%d) = ", i, com1.GetCommandID());

		str = "\tBool = (";
		for(j = com1.GetBoolIndex(); j < com2.GetBoolIndex(); j++) {
			if(boolStack[j] == char(1)) {
				str += "t";
			} else {
				str += "f";
			}

			if(j != com2.GetBoolIndex()-1) {
				str += ", ";
			}
		}
		str += ")";
		fk_PutError(str);

		str = "\tInt = (";
		for(j = com1.GetIntIndex(); j < com2.GetIntIndex(); j++) {
			str += fk_StrPrintf("%d", intStack[j]);

			if(j != com2.GetIntIndex()-1) {
				str += ", ";
			}
		}
		str += ")";
		fk_PutError(str);

		str = "\tVec = (";
		for(j = com1.GetVecIndex(); j < com2.GetVecIndex(); j++) {
			str += fk_StrPrintf("(%g, %g, %g)",
								vecStack[j].x, vecStack[j].y, vecStack[j].z);
			if(j != com2.GetVecIndex()-1) {
				str += ", ";
			}
		}
		str += ");";
		fk_PutError(str);

		str = "\tdouble = (";
		for(j = com1.GetDoubleIndex(); j < com2.GetDoubleIndex(); j++) {
			str += fk_StrPrintf("%f", doubleStack[j]);
			if(j != com2.GetDoubleIndex()-1) {
				str += ", ";
			}
		}
		str += ");";
		fk_PutError(str);

		str = "\tString = (";
		for(j = com1.GetStrIndex(); j < com2.GetStrIndex(); j++) {
			str += strStack[j];
			if(j != com2.GetStrIndex()-1) {
				str += ", ";
			}
		}
		str += ");";
		fk_PutError(str);
	}

	return;
}

void fk_History::PrintSize(void)
{
	fk_Printf("ComSize = %d", comStack.size());
	fk_Printf("boolSize = %d", boolStack.size());
	fk_Printf("intSize = %d", intStack.size());
	fk_Printf("vecSize = %d", vecStack.size());

	return;
}
