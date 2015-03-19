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
#include <FK/AttributeData.H>
#include <FK/Attribute.h>

using namespace std;

fk_Attribute::fk_Attribute(void)
{
	attr_data = nullptr;
	return;
}

fk_Attribute::~fk_Attribute()
{
	delete attr_data;
	return;
}

bool fk_Attribute::IsExistData(void) const
{
	if(attr_data == nullptr) {
		return false;
	}

	return true;
}

void fk_Attribute::AttrInit(void)
{
	if(IsExistData() == false) return;
	attr_data->AttrInit();
	return;
}

bool fk_Attribute::existAttrII(const int argKey) const
{
	if(IsExistData() == false) return false;
	return attr_data->ExistAttrII(argKey);
}

bool fk_Attribute::existAttrID(const int argKey) const
{
	if(IsExistData() == false) return false;
	return attr_data->ExistAttrID(argKey);
}

bool fk_Attribute::existAttrIS(const int argKey) const
{
	if(IsExistData() == false) return false;
	return attr_data->ExistAttrIS(argKey);
}

bool fk_Attribute::existAttrSI(const string argKey) const
{
	if(IsExistData() == false) return false;
	return attr_data->ExistAttrSI(argKey);
}

bool fk_Attribute::existAttrSD(const string argKey) const
{
	if(IsExistData() == false) return false;
	return attr_data->ExistAttrSD(argKey);
}

bool fk_Attribute::existAttrSS(const string argKey) const
{
	if(IsExistData() == false) return false;
	return attr_data->ExistAttrSS(argKey);
}

bool fk_Attribute::setAttrII(const int argKey, const int argValue)
{
	if(IsExistData() == false) {
		attr_data = new fk_Attribute_Data();
	}

	return attr_data->SetAttrII(argKey, argValue);
}

bool fk_Attribute::setAttrID(const int argKey, const double argValue)
{
	if(IsExistData() == false) {
		attr_data = new fk_Attribute_Data();
	}

	return attr_data->SetAttrID(argKey, argValue);
}

bool fk_Attribute::setAttrIS(const int argKey, const string argValue)
{
	if(IsExistData() == false) {
		attr_data = new fk_Attribute_Data();
	}

	return attr_data->SetAttrIS(argKey, argValue);
}

bool fk_Attribute::setAttrSI(const string argKey, const int argValue)
{
	if(IsExistData() == false) {
		attr_data = new fk_Attribute_Data();
	}

	return attr_data->SetAttrSI(argKey, argValue);
}

bool fk_Attribute::setAttrSD(const string argKey, const double argValue)
{
	if(IsExistData() == false) {
		attr_data = new fk_Attribute_Data();
	}

	return attr_data->SetAttrSD(argKey, argValue);
}

bool fk_Attribute::setAttrSS(const string argKey, const string argValue)
{
	if(IsExistData() == false) {
		attr_data = new fk_Attribute_Data();
	}

	return attr_data->SetAttrSS(argKey, argValue);
}

int fk_Attribute::getAttrII(const int argKey) const
{
	if(IsExistData() == false) {
		return 0;
	}
	return attr_data->GetAttrII(argKey);
}

double fk_Attribute::getAttrID(const int argKey) const
{
	if(IsExistData() == false) {
		return 0.0;
	}
	return attr_data->GetAttrID(argKey);
}

string fk_Attribute::getAttrIS(const int argKey) const
{
	if(IsExistData() == false) {
		return "";
	}
	return attr_data->GetAttrIS(argKey);
}

int fk_Attribute::getAttrSI(const string argKey) const
{
	if(IsExistData() == false) {
		return 0;
	}
	return attr_data->GetAttrSI(argKey);
}

double fk_Attribute::getAttrSD(const string argKey) const
{
	if(IsExistData() == false) {
		return 0.0;
	}
	return attr_data->GetAttrSD(argKey);
}

string fk_Attribute::getAttrSS(const string argKey) const
{
	if(IsExistData() == false) {
		return "";
	}
	return attr_data->GetAttrSS(argKey);
}

bool fk_Attribute::deleteAttrII(const int argKey)
{
	if(IsExistData() == false) {
		return false;
	}

	return attr_data->DeleteAttrII(argKey);
}


bool fk_Attribute::deleteAttrID(const int argKey)
{
	if(IsExistData() == false) {
		return false;
	}

	return attr_data->DeleteAttrID(argKey);
}


bool fk_Attribute::deleteAttrIS(const int argKey)
{
	if(IsExistData() == false) {
		return false;
	}

	return attr_data->DeleteAttrIS(argKey);
}


bool fk_Attribute::deleteAttrSI(const string argKey)
{
	if(IsExistData() == false) {
		return false;
	}

	return attr_data->DeleteAttrSI(argKey);
}

bool fk_Attribute::deleteAttrSD(const string argKey)
{
	if(IsExistData() == false) {
		return false;
	}

	return attr_data->DeleteAttrSD(argKey);
}

bool fk_Attribute::deleteAttrSS(const string argKey)
{
	if(IsExistData() == false) {
		return false;
	}

	return attr_data->DeleteAttrSS(argKey);
}
