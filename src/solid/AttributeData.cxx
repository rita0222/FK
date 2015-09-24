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
#define FK_DEF_SIZETYPE
#include <FK/AttributeData.H>
#include <FK/Error.H>

using namespace std;

fk_Attribute_Data::fk_Attribute_Data(void)
{
	ItoIIndex = nullptr;
	ItoIValue = nullptr;

	ItoDIndex = nullptr;
	ItoDValue = nullptr;

	ItoSIndex = nullptr;
	ItoSValue = nullptr;

	StoIIndex = nullptr;
	StoIValue = nullptr;

	StoDIndex = nullptr;
	StoDValue = nullptr;

	StoSIndex = nullptr;
	StoSValue = nullptr;

	return;
}

fk_Attribute_Data::~fk_Attribute_Data()
{
	AttrInit();
	return;
}

void fk_Attribute_Data::AttrInit(void)
{
	delete ItoIIndex;
	delete ItoIValue;

	delete ItoDIndex;
	delete ItoDValue;

	delete ItoSIndex;
	delete ItoSValue;

	delete StoIIndex;
	delete StoIValue;

	delete StoDIndex;
	delete StoDValue;

	delete StoSIndex;
	delete StoSValue;

	ItoIIndex = nullptr;
	ItoIValue = nullptr;

	ItoDIndex = nullptr;
	ItoDValue = nullptr;

	ItoSIndex = nullptr;
	ItoSValue = nullptr;

	StoIIndex = nullptr;
	StoIValue = nullptr;

	StoDIndex = nullptr;
	StoDValue = nullptr;

	StoSIndex = nullptr;
	StoSValue = nullptr;

	return;
}

int fk_Attribute_Data::CreateNewIndexI(vector<int> *argArray, int argKey)
{
	_st		i, size = argArray->size();

	for(i = 0; i < size; i++) {
		if((*argArray)[i] == FK_UNDEFINED) {
			(*argArray)[i] = argKey;
			return static_cast<int>(i);
		}
	}

	argArray->push_back(argKey);
	return static_cast<int>(size);
}

int fk_Attribute_Data::CreateNewIndexS(vector<string> *argArray, string argKey)
{
	_st		i, size = argArray->size();

	for(i = 0; i < size; i++) {
		if((*argArray)[i] == "") {
			(*argArray)[i] = argKey;
			return static_cast<int>(i);
		}
	}

	argArray->push_back(argKey);
	return static_cast<int>(size);
}

int fk_Attribute_Data::GetIndexAttrII(const int Key) const
{
	_st		i, size;

	if(ItoIIndex == nullptr) {
		return FK_UNDEFINED;
	}

	size = ItoIIndex->size();

	for(i = 0; i < size; i++) {
		if((*ItoIIndex)[i] == Key) return static_cast<int>(i);
	}
	return FK_UNDEFINED;
}

int fk_Attribute_Data::GetIndexAttrID(const int Key) const
{
	_st		i, size;

	if(ItoDIndex == nullptr) {
		return FK_UNDEFINED;
	}

	size = ItoDIndex->size();

	for(i = 0; i < size; i++) {
		if((*ItoDIndex)[i] == Key) return static_cast<int>(i);
	}
	return FK_UNDEFINED;
}

int fk_Attribute_Data::GetIndexAttrIS(const int Key) const
{
	_st		i, size;

	if(ItoSIndex == nullptr) {
		return FK_UNDEFINED;
	}

	size = ItoSIndex->size();

	for(i = 0; i < size; i++) {
		if((*ItoSIndex)[i] == Key) return static_cast<int>(i);
	}
	return FK_UNDEFINED;
}

int fk_Attribute_Data::GetIndexAttrSI(const string Key) const
{
	_st		i, size;

	if(StoIIndex == nullptr) {
		return FK_UNDEFINED;
	}

	size = StoIIndex->size();

	for(i = 0; i < size; i++) {
		if((*StoIIndex)[i] == Key) return static_cast<int>(i);
	}
	return FK_UNDEFINED;
}

int fk_Attribute_Data::GetIndexAttrSD(const string Key) const
{
	_st		i, size;

	if(StoDIndex == nullptr) {
		return FK_UNDEFINED;
	}

	size = StoDIndex->size();

	for(i = 0; i < size; i++) {
		if((*StoDIndex)[i] == Key) return static_cast<int>(i);
	}
	return FK_UNDEFINED;
}

int fk_Attribute_Data::GetIndexAttrSS(const string Key) const
{
	_st		i, size;

	if(StoSIndex == nullptr) {
		return FK_UNDEFINED;
	}

	size = StoSIndex->size();

	for(i = 0; i < size; i++) {
		if((*StoSIndex)[i] == Key) return static_cast<int>(i);
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
	int			Index;

	if(Key < 0) {
		fk_PutError("fk_Attribute", "setAttrII", 1,
					"Key Value Error.");
		return false;
	}

	Index = GetIndexAttrII(Key);

	if(Index == FK_UNDEFINED) {
		if(ItoIIndex == nullptr) {
			ItoIIndex = new vector<int>;
			ItoIValue = new vector<int>;
		}

		Index = CreateNewIndexI(ItoIIndex, Key);

		if(Index == static_cast<int>(ItoIValue->size())) {
			ItoIValue->push_back(Value);
		} else {
			(*ItoIValue)[static_cast<_st>(Index)] = Value;
		}

		return false;
	} else {
		(*ItoIValue)[static_cast<_st>(Index)] = Value;
	}
	return true;
}

bool fk_Attribute_Data::SetAttrID(const int Key, const double Value)
{
	int			Index;

	if(Key < 0) {
		fk_PutError("fk_Attribute", "setAttrID", 1,
					"Key Value Error.");
		return false;
	}

	Index = GetIndexAttrID(Key);

	if(Index == FK_UNDEFINED) {
		if(ItoDIndex == nullptr) {
			ItoDIndex = new vector<int>;
			ItoDValue = new vector<double>;
		}

		Index = CreateNewIndexI(ItoDIndex, Key);

		if(Index == static_cast<int>(ItoDValue->size())) {
			ItoDValue->push_back(Value);
		} else {
			(*ItoDValue)[static_cast<_st>(Index)] = Value;
		}

		return false;
	} else {
		(*ItoDValue)[static_cast<_st>(Index)] = Value;
	}
	return true;
}

bool fk_Attribute_Data::SetAttrIS(const int Key, const string Value)
{
	int			Index;

	if(Key < 0) {
		fk_PutError("fk_Attribute", "setAttrIS", 1,
					"Key Value Error.");
		return false;
	}

	Index = GetIndexAttrIS(Key);

	if(Index == FK_UNDEFINED) {
		if(ItoSIndex == nullptr) {
			ItoSIndex = new vector<int>;
			ItoSValue = new vector<string>;
		}

		Index = CreateNewIndexI(ItoSIndex, Key);

		if(Index == static_cast<int>(ItoSValue->size())) {
			ItoSValue->push_back(Value);
		} else {
			(*ItoSValue)[static_cast<_st>(Index)] = Value;
		}

		return false;
	} else {
		(*ItoSValue)[static_cast<_st>(Index)] = Value;
	}
	return true;
}

bool fk_Attribute_Data::SetAttrSI(const string Key, const int Value)
{
	int			Index;

	if(Key.length() == 0) {
		fk_PutError("fk_Attribute", "setAttrSI", 1,
					"Key Value Error.");
		return false;
	}

	Index = GetIndexAttrSI(Key);

	if(Index == FK_UNDEFINED) {
		if(StoIIndex == nullptr) {
			StoIIndex = new vector<string>;
			StoIValue = new vector<int>;
		}

		Index = CreateNewIndexS(StoIIndex, Key);

		if(Index == static_cast<int>(StoIValue->size())) {
			StoIValue->push_back(Value);
		} else {
			(*StoIValue)[static_cast<_st>(Index)] = Value;
		}

		return false;
	} else {
		(*StoIValue)[static_cast<_st>(Index)] = Value;
	}
	return true;
}

bool fk_Attribute_Data::SetAttrSD(const string Key, const double Value)
{
	int			Index;

	if(Key.length() == 0) {
		fk_PutError("fk_Attribute", "setAttrSD", 1,
					"Key Value Error.");
		return false;
	}

	Index = GetIndexAttrSD(Key);

	if(Index == FK_UNDEFINED) {
		if(StoDIndex == nullptr) {
			StoDIndex = new vector<string>;
			StoDValue = new vector<double>;
		}

		Index = CreateNewIndexS(StoDIndex, Key);

		if(Index == static_cast<int>(StoDValue->size())) {
			StoDValue->push_back(Value);
		} else {
			(*StoDValue)[static_cast<_st>(Index)] = Value;
		}

		return false;
	} else {
		(*StoDValue)[static_cast<_st>(Index)] = Value;
	}
	return true;
}

bool fk_Attribute_Data::SetAttrSS(const string Key, const string Value)
{
	int			Index;

	if(Key.length() == 0) {
		fk_PutError("fk_Attribute", "setAttrSS", 1,
					"Key Value Error.");
		return false;
	}

	Index = GetIndexAttrSS(Key);

	if(Index == FK_UNDEFINED) {
		if(StoSIndex == nullptr) {
			StoSIndex = new vector<string>;
			StoSValue = new vector<string>;
		}

		Index = CreateNewIndexS(StoSIndex, Key);

		if(Index == static_cast<int>(StoSValue->size())) {
			StoSValue->push_back(Value);
		} else {
			(*StoSValue)[static_cast<_st>(Index)] = Value;
		}

		return false;
	} else {
		(*StoSValue)[static_cast<_st>(Index)] = Value;
	}
	return true;
}

int fk_Attribute_Data::GetAttrII(const int Key) const
{
	int		Index = GetIndexAttrII(Key);

	if(Index == FK_UNDEFINED) {
		return 0;
	} else {
		return (*ItoIValue)[static_cast<_st>(Index)];
	}
}

double fk_Attribute_Data::GetAttrID(const int Key) const
{
	int		Index = GetIndexAttrID(Key);

	if(Index == FK_UNDEFINED) {
		return 0.0;
	} else {
		return (*ItoDValue)[static_cast<_st>(Index)];
	}
}

string fk_Attribute_Data::GetAttrIS(const int Key) const
{
	int		Index = GetIndexAttrIS(Key);

	if(Index == FK_UNDEFINED) {
		return "";
	} else {
		return (*ItoSValue)[static_cast<_st>(Index)];
	}
}

int fk_Attribute_Data::GetAttrSI(const string Key) const
{
	int		Index = GetIndexAttrSI(Key);

	if(Index == FK_UNDEFINED) {
		return 0;
	} else {
		return (*StoIValue)[static_cast<_st>(Index)];
	}
}

double fk_Attribute_Data::GetAttrSD(const string Key) const
{
	int		Index = GetIndexAttrSD(Key);

	if(Index == FK_UNDEFINED) {
		return 0.0;
	} else {
		return (*StoDValue)[static_cast<_st>(Index)];
	}
}

string fk_Attribute_Data::GetAttrSS(const string Key) const
{
	int		Index = GetIndexAttrSS(Key);

	if(Index == FK_UNDEFINED) {
		return "";
	} else {
		return (*StoSValue)[static_cast<_st>(Index)];
	}
}

bool fk_Attribute_Data::DeleteAttrII(const int argKey)
{
	int		Index = GetIndexAttrII(argKey);

	if(Index != FK_UNDEFINED) {
		(*ItoIIndex)[static_cast<_st>(Index)] = FK_UNDEFINED;
		return true;
	}
	return false;
}

bool fk_Attribute_Data::DeleteAttrID(const int argKey)
{
	int		Index = GetIndexAttrID(argKey);

	if(Index != FK_UNDEFINED) {
		(*ItoDIndex)[static_cast<_st>(Index)] = FK_UNDEFINED;
		return true;
	}
	return false;
}

bool fk_Attribute_Data::DeleteAttrIS(const int argKey)
{
	int		Index = GetIndexAttrIS(argKey);

	if(Index != FK_UNDEFINED) {
		(*ItoSIndex)[static_cast<_st>(Index)] = FK_UNDEFINED;
		return true;
	}
	return false;
}

bool fk_Attribute_Data::DeleteAttrSI(const string argKey)
{
	int		Index = GetIndexAttrSI(argKey);

	if(Index != FK_UNDEFINED) {
		(*StoIIndex)[static_cast<_st>(Index)].erase();
		return true;
	}
	return false;
}

bool fk_Attribute_Data::DeleteAttrSD(const string argKey)
{
	int		Index = GetIndexAttrSD(argKey);

	if(Index != FK_UNDEFINED) {
		(*StoDIndex)[static_cast<_st>(Index)].erase();
		return true;
	}
	return false;
}

bool fk_Attribute_Data::DeleteAttrSS(const string argKey)
{
	int		Index = GetIndexAttrSS(argKey);

	if(Index != FK_UNDEFINED) {
		(*StoSIndex)[static_cast<_st>(Index)].erase();
		return true;
	}
	return false;
}
