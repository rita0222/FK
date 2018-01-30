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

#define FK_DEF_SIZETYPE
#include <FK/DrawCache.h>
#include <FK/LIAdmin.H>
#include <FK/Vertex.h>
#include <FK/Error.H>
#include <algorithm>

using namespace std;
using namespace FK;

fk_LoopIndexAdmin::fk_LoopIndexAdmin(void)
{
	maxID = 0;
	return;
}

fk_LoopIndexAdmin::~fk_LoopIndexAdmin()
{
	return;
}

void fk_LoopIndexAdmin::PushRemoveID(int argNum, int argID)
{
	if(argNum <= 0) return;
	if(argNum >= static_cast<int>(IDAdmin.size())) {
		IDAdmin.resize(static_cast<_st>(argNum));
	}
	IDAdmin[static_cast<_st>(argNum-1)].push_back(argID);

	return;
}

int fk_LoopIndexAdmin::GetNewID(int argNum)
{
	int		retID;
	_st		id;

	if(argNum <= 0) return -1;
	id = static_cast<_st>(argNum-1);
	if(argNum <= static_cast<int>(IDAdmin.size())) {
		if(IDAdmin[id].empty() == false) {
			retID = IDAdmin[id][IDAdmin[id].size()-1];
			IDAdmin[id].pop_back();
			return retID;
		}
	}

	retID = maxID;
	maxID += argNum;
	return retID;
}

fk_DrawCache::fk_DrawCache(void)
{
	AllCacheClear();
	return;
}

fk_DrawCache::~fk_DrawCache()
{
	AllCacheClear();
	return;
}

void fk_DrawCache::ClearVCache(void)
{
	vertexCache.clear();
	return;
}

bool fk_DrawCache::ClearVCache(fk_Vertex *argV)
{
	list<fk_Vertex *>::iterator		ite;

	ite = find(vertexCache.begin(), vertexCache.end(), argV);
	if(ite == vertexCache.end()) return false;
	vertexCache.erase(ite);
	return true;
}

bool fk_DrawCache::ClearECache(fk_Edge *argE)
{
	list<fk_Edge *>::iterator		ite;

	ite = find(edgeCache.begin(), edgeCache.end(), argE);
	if(ite == edgeCache.end()) return false;
	edgeCache.erase(ite);
	return true;
}

bool fk_DrawCache::ClearLCache(fk_Loop *argL)
{
	list<fk_Loop *>::iterator		ite;

	ite = find(loopCache.begin(), loopCache.end(), argL);
	if(ite == loopCache.end()) return false;
	loopCache.erase(ite);
	return true;
}

void fk_DrawCache::ClearECache(void)
{
	edgeCache.clear();
	return;
}

void fk_DrawCache::ClearLCache(void)
{
	loopCache.clear();
	return;
}

bool fk_DrawCache::GetVCacheStatus(void)
{
	if(vertexCache.empty() == true && getNextV(nullptr) != nullptr) {
		return false;
	}
	return true;
}

bool fk_DrawCache::GetECacheStatus(void)
{
	if(edgeCache.empty() == true && getNextE(nullptr) != nullptr) {
		return false;
	}
	return true;
}

bool fk_DrawCache::GetLCacheStatus(void)
{
	if(loopCache.empty() == true && getNextL(nullptr) != nullptr) {
		return false;
	}

	return true;
}

void fk_DrawCache::MakeVCache(void)
{
	fk_Vertex	*curV;
	_st			vID;

	vertexCache.clear();
	curV = getNextV(nullptr);
	while(curV != nullptr) {
		vertexCache.push_back(curV);
		vID = static_cast<_st>(curV->getID() - 1);
		if(vID >= vertexArray.size()) vertexArray.resize(vID+1);
		vertexArray[vID] = curV->getPosition();
		curV = getNextV(curV);
	}
	return;
}

void fk_DrawCache::MakeECache(void)
{
	fk_Edge			*curE;

	edgeCache.clear();
	curE = getNextE(nullptr);
	while(curE != nullptr) {
		edgeCache.push_back(curE);
		curE = getNextE(curE);
	}
	return;
}

void fk_DrawCache::MakeLCache(void)
{
	fk_Loop			*curL;

	loopCache.clear();
	curL = getNextL(nullptr);
	while(curL != nullptr) {
		loopCache.push_back(curL);
		curL = getNextL(curL);
	}
	return;
}

void fk_DrawCache::AddVCache(fk_Vertex *argV)
{
	_st		vID;

	ClearVCache(argV);
	vertexCache.push_back(argV);
	vID = static_cast<_st>(argV->getID() - 1);
	if(vID >= vertexArray.size()) vertexArray.resize(vID+1);
	vertexArray[vID] = argV->getPosition();

	return;
}

void fk_DrawCache::AddECache(fk_Edge *argE)
{
	ClearECache(argE);
	edgeCache.push_back(argE);
	return;
}

void fk_DrawCache::AddLCache(fk_Loop *argL)
{
	ClearLCache(argL);
	loopCache.push_back(argL);
	return;
}

list<fk_Vertex *> * fk_DrawCache::GetVCache(void)
{
	return &vertexCache;
}

list<fk_Edge *> * fk_DrawCache::GetECache(void)
{
	return &edgeCache;
}

list<fk_Loop *> * fk_DrawCache::GetLCache(void)
{
	return &loopCache;
}

void fk_DrawCache::AllCacheClear(void)
{
	ClearVCache();
	ClearECache();
	ClearLCache();

	vertexArray.clear();
	ifsArray.clear();

	return;
}

void fk_DrawCache::AllCacheMake(void)
{
	MakeVCache();
	MakeECache();
	MakeLCache();
	return;
}

void fk_DrawCache::AllClear_(void)
{
	AllDBClear_();
	AllCacheClear();

	return;
}

fk_Vertex * fk_DrawCache::GetNewVertexObj(void)
{
	fk_Vertex		*retV = GetNewVertexObj_();

	AddVCache(retV);
	return retV;
}

fk_Vertex * fk_DrawCache::GetNewVertexObj(int argID)
{
	fk_Vertex		*retV = GetNewVertexObj_(argID);

	AddVCache(retV);
	return retV;
}

fk_Half * fk_DrawCache::GetNewHalfObj(void)
{
	return GetNewHalfObj_();
}

fk_Half * fk_DrawCache::GetNewHalfObj(int argID)
{
	return GetNewHalfObj_(argID);
}

fk_Edge * fk_DrawCache::GetNewEdgeObj(void)
{
	fk_Edge			*retE = GetNewEdgeObj_();

	AddECache(retE);
	return retE;
}

fk_Edge * fk_DrawCache::GetNewEdgeObj(int argID)
{
	fk_Edge			*retE = GetNewEdgeObj_(argID);

	AddECache(retE);
	return retE;
}

fk_Loop * fk_DrawCache::GetNewLoopObj(void)
{
	fk_Loop			*retL = GetNewLoopObj_();

	AddLCache(retL);
	return retL;
}

fk_Loop * fk_DrawCache::GetNewLoopObj(int argID)
{
	fk_Loop			*retL = GetNewLoopObj_(argID);

	AddLCache(retL);
	return retL;
}

bool fk_DrawCache::DeleteVertexObj(fk_Vertex *argV)
{
	if(DeleteVertexObj_(argV) == false) return false;
	ClearVCache(argV);
	return true;
}

bool fk_DrawCache::DeleteVertexObj(int argID)
{
	return DeleteVertexObj(getVData(argID));
}

bool fk_DrawCache::DeleteHalfObj(fk_Half *argH)
{
	return DeleteHalfObj_(argH);
}

bool fk_DrawCache::DeleteHalfObj(int argID)
{
	return DeleteHalfObj(getHData(argID));
}

bool fk_DrawCache::DeleteEdgeObj(fk_Edge *argE)
{
	if(DeleteEdgeObj_(argE) == false) return false;
	ClearECache(argE);
	return true;
}

bool fk_DrawCache::DeleteEdgeObj(int argID)
{
	return DeleteEdgeObj(getEData(argID));
}

bool fk_DrawCache::DeleteLoopObj(fk_Loop *argL)
{
	if(DeleteLoopObj_(argL) == false) return false;
	ClearLCache(argL);
	return true;
}

bool fk_DrawCache::DeleteLoopObj(int argID)
{
	return DeleteLoopObj(getLData(argID));
}

void fk_DrawCache::PrintCache(void)
{
	//fk_Printf("(vSize, lSize) = %d, %d", vertexArray.size(), ifsArray.size());
	return;
}
