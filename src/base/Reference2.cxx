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
#include <FK/Reference.h>

#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Edge.h>
#include <FK/Loop.h>

using namespace std;

fk_Vertex * fk_ReferenceL2::getOneNeighborVOnV(fk_Vertex *argV) const
{
	fk_Half	*tmpH;

	if(argV == NULL) return NULL;
	tmpH = argV->getOneHalf();
	if(tmpH == NULL) return NULL;
	return getMateHOnH(tmpH)->getVertex();
}

vector<fk_Half *> fk_ReferenceL2::getAllHOnV(fk_Vertex *argV) const
{
	vector<fk_Half *>	retVec;
	fk_Half				*startH, *countH;

	retVec.clear();
	if(argV == NULL) return retVec;
	countH = NULL;
	startH = argV->getOneHalf();
	if(startH == NULL) return retVec;

	retVec.push_back(startH);	 

	countH = getMateHOnH(startH)->getNextHalf();

	while(countH != startH) {
		retVec.push_back(countH);
		countH = getMateHOnH(countH)->getNextHalf();
	}

	return retVec;
}

vector<fk_Edge *> fk_ReferenceL2::getAllEOnV(fk_Vertex *argV) const
{
	vector<fk_Edge *>	retVec;
	fk_Half				*startH, *countH;

	retVec.clear();
	if(argV == NULL) return retVec;
	countH = NULL;
	startH = argV->getOneHalf();
	if(startH == NULL) return retVec;

	retVec.push_back(startH->getParentEdge());	  

	countH = getMateHOnH(startH)->getNextHalf();

	while(countH != startH) {
		retVec.push_back(countH->getParentEdge());
		countH = getMateHOnH(countH)->getNextHalf();
	}

	return retVec;
}

int fk_ReferenceL2::getENumOnV(fk_Vertex *argV) const
{
	int				retNum;
	fk_Half			*startH, *countH;

	retNum = 1;
	if(argV == NULL) return 0;
	countH = NULL;
	startH = argV->getOneHalf();
	if(startH == NULL) return 0;

	countH = getMateHOnH(startH)->getNextHalf();

	while(countH != startH) {
		countH = getMateHOnH(countH)->getNextHalf();
		retNum++;
	}

	return retNum;
}

vector<fk_Loop *> fk_ReferenceL2::getAllLOnV(fk_Vertex *argV) const
{
	vector<fk_Loop *>	retVec;
	fk_Half				*startH, *countH;
	fk_Loop				*tmpL;

	retVec.clear();
	if(argV == NULL) return retVec;
	countH = NULL;
	startH = argV->getOneHalf();
	if(startH == NULL) return retVec;

	tmpL = startH->getParentLoop();

	if(tmpL != NULL) retVec.push_back(tmpL);
	countH = getMateHOnH(startH)->getNextHalf();

	while(countH != startH) {
		tmpL = countH->getParentLoop();
		if(tmpL != NULL) retVec.push_back(tmpL);
		countH = getMateHOnH(countH)->getNextHalf();
	}

	return retVec;
}

vector<fk_Vertex *> fk_ReferenceL2::getAllVOnL(fk_Loop *argL) const
{
	vector<fk_Vertex *>		retVec;
	fk_Half					*startH, *countH;

	retVec.clear();
	if(argL == NULL) return retVec;
	startH = argL->getOneHalf();
	retVec.push_back(startH->getVertex());
	
	for(countH = startH->getNextHalf();
		countH != startH; countH = countH->getNextHalf()) {
		retVec.push_back(countH->getVertex());
	}

	return retVec;
}

int fk_ReferenceL2::getVNumOnL(fk_Loop *argL) const
{
	int			retNum;
	fk_Half		*startH, *countH;

	retNum = 1;

	if(argL == NULL) return 0;
	startH = argL->getOneHalf();
	
	for(countH = startH->getNextHalf();
		countH != startH; countH = countH->getNextHalf()) {
		retNum++;
	}

	return retNum;
}

vector<fk_Half *> fk_ReferenceL2::getAllHOnL(fk_Loop *argL) const
{
	vector<fk_Half *>	retVec;
	fk_Half				*startH, *countH;

	retVec.clear();
	if(argL == NULL) return retVec;
	startH = argL->getOneHalf();
	retVec.push_back(startH);
	
	for(countH = startH->getNextHalf();
		countH != startH; countH = countH->getNextHalf()) {

		retVec.push_back(countH);
	}

	return retVec;
}

vector<fk_Edge *> fk_ReferenceL2::getAllEOnL(fk_Loop *argL) const
{
	vector<fk_Edge *>	retVec;
	fk_Half				*startH, *countH;

	retVec.clear();
	if(argL == NULL) return retVec;
	startH = argL->getOneHalf();
	retVec.push_back(startH->getParentEdge());
	
	for(countH = startH->getNextHalf();
		countH != startH; countH = countH->getNextHalf()) {
		retVec.push_back(countH->getParentEdge());
	}

	return retVec;
}

fk_Loop * fk_ReferenceL2::getOneNeighborLOnL(fk_Loop *argL) const
{
	fk_Half		*startH, *tmpH;
	fk_Loop		*retL;

	if(argL == NULL) return NULL;
	startH = tmpH = argL->getOneHalf();
	do {
		retL = getMateHOnH(tmpH)->getParentLoop();
		if(retL != NULL && retL != argL) break;
		tmpH = tmpH->getNextHalf();
	} while(startH != tmpH);

	if(startH == tmpH) return NULL;
	else return retL;
}

fk_Loop * fk_ReferenceL2::getNeighborLOnLH(fk_Loop *argL, fk_Half *argH) const
{
	fk_Loop		*retL;

	if(argL == NULL || argH == NULL) {
		return NULL;
	}
	if(argH->getParentLoop() != argL) return NULL;
	retL = getMateHOnH(argH)->getParentLoop();
	if(retL == NULL || retL == argL) return NULL;
	else return retL;
}
