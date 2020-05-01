#define FK_DEF_SIZETYPE

#include <FK/Base.h>
#include <FK/AttributeData.H>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_Attribute_Data::fk_Attribute_Data(void)
{
	return;
}

fk_Attribute_Data::~fk_Attribute_Data()
{
	return;
}

void fk_Attribute_Data::AttrInit(void)
{
	ItoIIndex.clear();
	ItoIValue.clear();
	
	ItoDIndex.clear();
	ItoDValue.clear();

	ItoSIndex.clear();
	ItoSValue.clear();

	StoIIndex.clear();
	StoIValue.clear();

	StoDIndex.clear();
	StoDValue.clear();

	StoSIndex.clear();
	StoSValue.clear();

	return;
}

int fk_Attribute_Data::CreateNewIndexI(vector<int> *argArray, int argKey)
{
	_st size = argArray->size();

	for(_st i = 0; i < size; i++) {
		if((*argArray)[i] == FK_UNDEFINED) {
			(*argArray)[i] = argKey;
			return int(i);
		}
	}

	argArray->push_back(argKey);
	return int(size);
}

int fk_Attribute_Data::CreateNewIndexS(vector<string> *argArray, string argKey)
{
	_st size = argArray->size();

	for(_st i = 0; i < size; i++) {
		if((*argArray)[i] == "") {
			(*argArray)[i] = argKey;
			return int(i);
		}
	}

	argArray->push_back(argKey);
	return int(size);
}

int fk_Attribute_Data::GetIndexAttrII(const int Key) const
{
	if(ItoIIndex.empty()) {
		return FK_UNDEFINED;
	}

	_st size = ItoIIndex.size();

	for(_st i = 0; i < size; i++) {
		if(ItoIIndex[i] == Key) return int(i);
	}
	return FK_UNDEFINED;
}

int fk_Attribute_Data::GetIndexAttrID(const int Key) const
{
	if(ItoDIndex.empty()) {
		return FK_UNDEFINED;
	}

	_st size = ItoDIndex.size();

	for(_st i = 0; i < size; i++) {
		if(ItoDIndex[i] == Key) return int(i);
	}
	return FK_UNDEFINED;
}

int fk_Attribute_Data::GetIndexAttrIS(const int Key) const
{
	if(ItoSIndex.empty()) {
		return FK_UNDEFINED;
	}

	_st size = ItoSIndex.size();

	for(_st i = 0; i < size; i++) {
		if(ItoSIndex[i] == Key) return int(i);
	}
	return FK_UNDEFINED;
}

int fk_Attribute_Data::GetIndexAttrSI(const string Key) const
{
	if(StoIIndex.empty()) {
		return FK_UNDEFINED;
	}

	_st size = StoIIndex.size();

	for(_st i = 0; i < size; i++) {
		if(StoIIndex[i] == Key) return int(i);
	}
	return FK_UNDEFINED;
}

int fk_Attribute_Data::GetIndexAttrSD(const string Key) const
{
	if(StoDIndex.empty()) {
		return FK_UNDEFINED;
	}

	_st size = StoDIndex.size();

	for(_st i = 0; i < size; i++) {
		if(StoDIndex[i] == Key) return int(i);
	}
	return FK_UNDEFINED;
}

int fk_Attribute_Data::GetIndexAttrSS(const string Key) const
{
	if(StoSIndex.empty()) {
		return FK_UNDEFINED;
	}

	_st size = StoSIndex.size();

	for(_st i = 0; i < size; i++) {
		if(StoSIndex[i] == Key) return int(i);
	}
	return FK_UNDEFINED;
}

bool fk_Attribute_Data::ExistAttrII(const int Key) const
{
	if(GetIndexAttrII(Key) == FK_UNDEFINED) return false;
	return true;
}

bool fk_Attribute_Data::ExistAttrID(const int Key) const
{
	if(GetIndexAttrID(Key) == FK_UNDEFINED) return false;
	return true;
}

bool fk_Attribute_Data::ExistAttrIS(const int Key) const
{
	if(GetIndexAttrIS(Key) == FK_UNDEFINED) return false;
	return true;
}

bool fk_Attribute_Data::ExistAttrSI(const string Key) const
{
	if(GetIndexAttrSI(Key) == FK_UNDEFINED) return false;
	return true;
}

bool fk_Attribute_Data::ExistAttrSD(const string Key) const
{
	if(GetIndexAttrSD(Key) == FK_UNDEFINED) return false;
	return true;
}

bool fk_Attribute_Data::ExistAttrSS(const string Key) const
{
	if(GetIndexAttrSS(Key) == FK_UNDEFINED) return false;
	return true;
}

bool fk_Attribute_Data::SetAttrII(const int Key, const int Value)
{
	if(Key < 0) {
		Error::Put("fk_Attribute", "setAttrII", 1, "Key Value Error.");
		return false;
	}

	int Index = GetIndexAttrII(Key);

	if(Index == FK_UNDEFINED) {
		Index = CreateNewIndexI(&ItoIIndex, Key);

		if(Index == int(ItoIValue.size())) {
			ItoIValue.push_back(Value);
		} else {
			ItoIValue[_st(Index)] = Value;
		}

		return false;
	} else {
		ItoIValue[_st(Index)] = Value;
	}
	return true;
}

bool fk_Attribute_Data::SetAttrID(const int Key, const double Value)
{
	if(Key < 0) {
		Error::Put("fk_Attribute", "setAttrID", 1, "Key Value Error.");
		return false;
	}

	int Index = GetIndexAttrID(Key);

	if(Index == FK_UNDEFINED) {
		Index = CreateNewIndexI(&ItoDIndex, Key);

		if(Index == int(ItoDValue.size())) {
			ItoDValue.push_back(Value);
		} else {
			ItoDValue[_st(Index)] = Value;
		}

		return false;
	} else {
		ItoDValue[_st(Index)] = Value;
	}
	return true;
}

bool fk_Attribute_Data::SetAttrIS(const int Key, const string Value)
{
	if(Key < 0) {
		Error::Put("fk_Attribute", "setAttrIS", 1, "Key Value Error.");
		return false;
	}

	int Index = GetIndexAttrIS(Key);

	if(Index == FK_UNDEFINED) {
		Index = CreateNewIndexI(&ItoSIndex, Key);

		if(Index == int(ItoSValue.size())) {
			ItoSValue.push_back(Value);
		} else {
			ItoSValue[_st(Index)] = Value;
		}

		return false;
	} else {
		ItoSValue[_st(Index)] = Value;
	}
	return true;
}

bool fk_Attribute_Data::SetAttrSI(const string Key, const int Value)
{
	if(Key.length() == 0) {
		Error::Put("fk_Attribute", "setAttrSI", 1, "Key Value Error.");
		return false;
	}

	int Index = GetIndexAttrSI(Key);

	if(Index == FK_UNDEFINED) {
		Index = CreateNewIndexS(&StoIIndex, Key);

		if(Index == int(StoIValue.size())) {
			StoIValue.push_back(Value);
		} else {
			StoIValue[_st(Index)] = Value;
		}
		return false;
	} else {
		StoIValue[_st(Index)] = Value;
	}
	return true;
}

bool fk_Attribute_Data::SetAttrSD(const string Key, const double Value)
{
	if(Key.length() == 0) {
		Error::Put("fk_Attribute", "setAttrSD", 1, "Key Value Error.");
		return false;
	}

	int Index = GetIndexAttrSD(Key);

	if(Index == FK_UNDEFINED) {
		Index = CreateNewIndexS(&StoDIndex, Key);

		if(Index == int(StoDValue.size())) {
			StoDValue.push_back(Value);
		} else {
			StoDValue[_st(Index)] = Value;
		}

		return false;
	} else {
		StoDValue[_st(Index)] = Value;
	}
	return true;
}

bool fk_Attribute_Data::SetAttrSS(const string Key, const string Value)
{
	if(Key.length() == 0) {
		Error::Put("fk_Attribute", "setAttrSS", 1, "Key Value Error.");
		return false;
	}

	int Index = GetIndexAttrSS(Key);

	if(Index == FK_UNDEFINED) {
		Index = CreateNewIndexS(&StoSIndex, Key);

		if(Index == int(StoSValue.size())) {
			StoSValue.push_back(Value);
		} else {
			StoSValue[_st(Index)] = Value;
		}

		return false;
	} else {
		StoSValue[_st(Index)] = Value;
	}
	return true;
}

int fk_Attribute_Data::GetAttrII(const int Key) const
{
	int Index = GetIndexAttrII(Key);

	if(Index == FK_UNDEFINED) {
		return 0;
	} else {
		return ItoIValue[_st(Index)];
	}
}

double fk_Attribute_Data::GetAttrID(const int Key) const
{
	int Index = GetIndexAttrID(Key);

	if(Index == FK_UNDEFINED) {
		return 0.0;
	} else {
		return ItoDValue[_st(Index)];
	}
}

string fk_Attribute_Data::GetAttrIS(const int Key) const
{
	int Index = GetIndexAttrIS(Key);

	if(Index == FK_UNDEFINED) {
		return "";
	} else {
		return ItoSValue[_st(Index)];
	}
}

int fk_Attribute_Data::GetAttrSI(const string Key) const
{
	int Index = GetIndexAttrSI(Key);

	if(Index == FK_UNDEFINED) {
		return 0;
	} else {
		return StoIValue[_st(Index)];
	}
}

double fk_Attribute_Data::GetAttrSD(const string Key) const
{
	int Index = GetIndexAttrSD(Key);

	if(Index == FK_UNDEFINED) {
		return 0.0;
	} else {
		return StoDValue[_st(Index)];
	}
}

string fk_Attribute_Data::GetAttrSS(const string Key) const
{
	int Index = GetIndexAttrSS(Key);

	if(Index == FK_UNDEFINED) {
		return "";
	} else {
		return StoSValue[_st(Index)];
	}
}

bool fk_Attribute_Data::DeleteAttrII(const int argKey)
{
	int Index = GetIndexAttrII(argKey);

	if(Index != FK_UNDEFINED) {
		ItoIIndex[_st(Index)] = FK_UNDEFINED;
		return true;
	}
	return false;
}

bool fk_Attribute_Data::DeleteAttrID(const int argKey)
{
	int Index = GetIndexAttrID(argKey);

	if(Index != FK_UNDEFINED) {
		ItoDIndex[_st(Index)] = FK_UNDEFINED;
		return true;
	}
	return false;
}

bool fk_Attribute_Data::DeleteAttrIS(const int argKey)
{
	int Index = GetIndexAttrIS(argKey);

	if(Index != FK_UNDEFINED) {
		ItoSIndex[_st(Index)] = FK_UNDEFINED;
		return true;
	}
	return false;
}

bool fk_Attribute_Data::DeleteAttrSI(const string argKey)
{
	int Index = GetIndexAttrSI(argKey);

	if(Index != FK_UNDEFINED) {
		StoIIndex[_st(Index)].erase();
		return true;
	}
	return false;
}

bool fk_Attribute_Data::DeleteAttrSD(const string argKey)
{
	int Index = GetIndexAttrSD(argKey);

	if(Index != FK_UNDEFINED) {
		StoDIndex[_st(Index)].erase();
		return true;
	}
	return false;
}

bool fk_Attribute_Data::DeleteAttrSS(const string argKey)
{
	int Index = GetIndexAttrSS(argKey);

	if(Index != FK_UNDEFINED) {
		StoSIndex[_st(Index)].erase();
		return true;
	}
	return false;
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
