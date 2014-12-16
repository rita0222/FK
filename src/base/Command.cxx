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
#include <FK/Command.H>

fk_Command::fk_Command(int argComID)
{
	SetCommandID(argComID);
	SetBoolIndex(0);
	SetIntIndex(0);
	SetVecIndex(0);
	SetDoubleIndex(0);
	SetStrIndex(0);
	SetMarkStatus(false);

	return;
}

fk_Command::~fk_Command()
{
	return;
}

fk_Command::fk_Command(const fk_Command &argCom)
{
	commandID = argCom.commandID;
	boolIndex = argCom.boolIndex;
	intIndex = argCom.intIndex;
	vecIndex = argCom.vecIndex;
	doubleIndex = argCom.doubleIndex;
	strIndex = argCom.strIndex;
	mark = argCom.mark;
}	

fk_Command & fk_Command::operator =(const fk_Command &argCom)
{
	commandID = argCom.commandID;
	boolIndex = argCom.boolIndex;
	intIndex = argCom.intIndex;
	vecIndex = argCom.vecIndex;
	doubleIndex = argCom.doubleIndex;
	strIndex = argCom.strIndex;
	mark = argCom.mark;

	return *this;
}	

void fk_Command::SetCommandID(const int argComID)
{
	commandID = argComID;
	return;
}

void fk_Command::SetBoolIndex(const unsigned int argIndex)
{
	boolIndex = argIndex;
	return;
}

void fk_Command::SetIntIndex(const unsigned int argIndex)
{
	intIndex = argIndex;
	return;
}

void fk_Command::SetVecIndex(const unsigned int argIndex)
{
	vecIndex = argIndex;
	return;
}

void fk_Command::SetDoubleIndex(const unsigned int argIndex)
{
	doubleIndex = argIndex;
	return;
}

void fk_Command::SetStrIndex(const unsigned int argIndex)
{
	strIndex = argIndex;
	return;
}

void fk_Command::SetMarkStatus(const bool argMark)
{
	mark = argMark;
	return;
}

int fk_Command::GetCommandID(void) const
{
	return commandID;
}

unsigned int fk_Command::GetBoolIndex(void) const
{
	return boolIndex;
}

unsigned int fk_Command::GetIntIndex(void) const
{
	return intIndex;
}

unsigned int fk_Command::GetVecIndex(void) const
{
	return vecIndex;
}

unsigned int fk_Command::GetDoubleIndex(void) const
{
	return doubleIndex;
}

unsigned int fk_Command::GetStrIndex(void) const
{
	return strIndex;
}

bool fk_Command::GetMarkStatus(void) const
{
	return mark;
}
