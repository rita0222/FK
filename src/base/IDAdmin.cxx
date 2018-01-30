/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
#include <FK/Base.h>
#include <FK/IDAdmin.H>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_IDAdmin::fk_IDAdmin(int argOrder)
{
	eraseIDSet = nullptr;
	Init(argOrder);

	return;
}

fk_IDAdmin::~fk_IDAdmin()
{
	delete eraseIDSet;
	existFlagSet.clear();
	return;
}

void fk_IDAdmin::CloneData(fk_IDAdmin *argIDA)
{
	order = argIDA->order;
	MaxID = argIDA->MaxID;
	(*eraseIDSet) = *(argIDA->eraseIDSet);
	existFlagSet = argIDA->existFlagSet;

	return;
}	 

void fk_IDAdmin::Init(int argOrder)
{
	order = argOrder;
	MaxID = order - 1;

	delete eraseIDSet;
	eraseIDSet = new list<int>;
	existFlagSet.clear();

	return;
}

void fk_IDAdmin::Resize(int argSize)
{
	_st		i, size;

	size = static_cast<_st>(argSize);

	Init(order);

	MaxID = (argSize > 0) ? argSize + order - 1 : order - 1;
	existFlagSet.resize(size);
	for(i = 0; i < size; i++) {
		existFlagSet[i] = static_cast<char>(true);
	}

	return;
}

int fk_IDAdmin::NewID(void) const
{
	if(eraseIDSet->empty()) {
		return MaxID + 1;
	} else {
		return eraseIDSet->back();
	}
}

int fk_IDAdmin::CreateID(void)
{
	int 	retID;
	_st		index;

	if(eraseIDSet == nullptr) {
		eraseIDSet = new list<int>;
	}

	if(eraseIDSet->empty() == true) {
		retID = MaxID + 1;
		MaxID++;
		existFlagSet.push_back(static_cast<char>(true));
	} else {
		retID = eraseIDSet->back();
		eraseIDSet->pop_back();
		index = static_cast<_st>(retID - order);
		existFlagSet[index] = static_cast<char>(true);
	}

	return retID;
}

bool fk_IDAdmin::CreateID(int argID)
{
	_st		index = static_cast<_st>(argID - order);

	if(argID < order || argID > MaxID) {
		return false;
	}

	if(existFlagSet[index] == static_cast<char>(true)) {
		return false;
	}

	existFlagSet[index] = static_cast<char>(true);
	eraseIDSet->remove(argID);
	return true;
}

bool fk_IDAdmin::EraseID(int argID)
{
	_st		index = static_cast<_st>(argID - order);

	if(ExistID(argID) == false) return false;
	eraseIDSet->push_back(argID);
	existFlagSet[index] = static_cast<char>(false);

	return true;
}


bool fk_IDAdmin::ExistID(int argID) const
{
	_st		index = static_cast<_st>(argID - order);

	if(argID > MaxID || argID < order) return false;
	if(existFlagSet.size() <= index) {
		return false;
	}
	if(existFlagSet[index] == static_cast<char>(true)) return true;
	return false;
}

int fk_IDAdmin::GetMaxID(void) const
{
	int tmpMaxID;

	if(GetIDNum() == 0) return order-1;

	tmpMaxID = MaxID;
	while(ExistID(tmpMaxID) == false) {
		tmpMaxID--;
	}

	return tmpMaxID;
}

int fk_IDAdmin::GetIDNum(void) const
{
	return MaxID - static_cast<int>(eraseIDSet->size()) - order + 1;
}

int fk_IDAdmin::GetNext(int argID) const
{
	int tmpID;
	int	validMaxID = GetMaxID();

	// 最初の要素を返す
	if(argID > validMaxID) return order;

	// nullptr 相当を返す
	if(argID == validMaxID) return order-1;

	// 検索候補
	if(argID < order) {
		// 最初の要素
		tmpID = order;
	} else {
		tmpID = argID + 1;
	}

	// 検索
	while(tmpID <= validMaxID) {
		if(existFlagSet[static_cast<_st>(tmpID-order)] == static_cast<char>(true)) break;
		tmpID++;
	}

	// nullptr 相当を返す
	if(tmpID == validMaxID + 1) return order-1;

	// 検索結果
	return tmpID;
}

int fk_IDAdmin::GetOrder(void) const
{
	return order;
}
