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

#include <FK/SubDivision.H>
#include <FK/Modify.h>
#include <FK/Loop.h>
#include <FK/Edge.h>
#include <FK/Half.h>
#include <FK/Vertex.h>

using namespace std;

fk_SubDivision::fk_SubDivision()
{
	return;
}

fk_SubDivision::~fk_SubDivision()
{
	deleteState();
}

// 分割回数を指定すると、その分だけ分割する
void fk_SubDivision::calcCatmull(int count, fk_Modify *solid)
{
	for(int i=0; i<count; i++)
		this->Catmull_Clark(solid);

	return;
}

void fk_SubDivision::createState(fk_Modify *s)
{
	uint vNum, eNum, fNum;

	vNum = this->_vNum = static_cast<uint>(s->getVNum());
	eNum = this->_eNum = static_cast<uint>(s->getENum());
	fNum = this->_fNum = static_cast<uint>(s->getLNum());

	_vPos.resize(vNum);
	_ePos.resize(eNum);
	_fPos.resize(fNum);

	_verts.resize(vNum);
	_edges.resize(eNum);
	_faces.resize(fNum);
	_half.resize(fNum);

	uint i;
	fk_Loop *l = s->getNextL(nullptr);
	i = 0;
	while(l != nullptr)
	{
		_faces[i] = l;

		_fPos[i] = this->calcVertexAverage(s->getAllVOnL(l));

		l = s->getNextL(l);
		i++;
	}

	fk_Vertex *v = s->getNextV(nullptr);
	i = 0;
	while(v != nullptr)
	{
		_verts[i] = v;

		_vPos[i] = this->calcSourceVertexPosition(s, v);

		v = s->getNextV(v);
		i++;
	}

	fk_Edge *e = s->getNextE(nullptr);
	i = 0;
	while(e != nullptr)
	{
		_edges[i] = e;

		_ePos[i] = this->calcEdgeVertexPosition(s, e);

		e = s->getNextE(e);
		i++;
	}

	return;
}

void fk_SubDivision::deleteState(void)
{
	_vPos.clear();
	_ePos.clear();
	_fPos.clear();

	_verts.clear();
	_edges.clear();
	_faces.clear();
	_half.clear();
	return;
}


// Catmull_Clark法による細分割処理
void fk_SubDivision::Catmull_Clark(fk_Modify *s)
{
	this->createState(s);

	for(uint i = 0; i < _vNum; ++i) s->moveVertex(_verts[i], _vPos[i]);
	this->division(s);
	this->deleteState();

	return;
}

void fk_SubDivision::division(fk_Modify *s)
{
	//uint eNum = static_cast<uint>(s->getENum());
	//uint fNum = static_cast<uint>(s->getLNum());
	//fk_Vector *ePos = this->_ePos;
	//fk_Vector *fPos = this->_fPos;
	//fk_Edge **edges = this->_edges;
	uint size = this->_eNum;
	//fk_Half **h = this->_half;
	fk_Loop *l;
	//**faces = this->_faces;

	for(uint i = 0; i < size; ++i) s->moveVertex(s->separateEdge(_edges[i]), _ePos[i]);

	size = this->_fNum;

	for(uint i = 0; i < size; ++i)
		_half[i] = this->findStarthalf(s, _faces[i]);

	for(uint i = 0; i < size; ++i)
	{
		l = _faces[i];
		switch(l->getVNum())
		{
			case 6:
				s->moveVertex(this->divideTriangle(s, _half[i]), _fPos[i]);
				break;
			case 8:
				s->moveVertex(this->divideQuad(s, _half[i]), _fPos[i]);
				break;
		}
	}

	return;
}

fk_Half * fk_SubDivision::findStarthalf(fk_Modify *s, fk_Loop *l)
{
	fk_Half *h = l->getOneHalf();

	while(s->getEdgeStatus(h->getParentEdge()) != FK_BOTHDEF_EDGE || s->getAllHOnV(h->getVertex()).size() <= 2)
		h = h->getNextHalf();

	return h;
}

fk_Vertex *	fk_SubDivision::divideTriangle(fk_Modify *s, fk_Half *h)
{
	fk_Half *nh = h->getNextHalf()->getNextHalf()->getNextHalf();

	fk_Vertex *v = s->separateEdge(s->separateLoop(h, nh));

	s->separateLoop(h->getNextHalf(), nh->getNextHalf()->getNextHalf());

	return v;
}

fk_Vertex *	fk_SubDivision::divideQuad(fk_Modify *s, fk_Half *h)
{
	fk_Half *nh = h->getNextHalf()->getNextHalf()->getNextHalf()->getNextHalf()->getNextHalf();

	fk_Vertex *v = s->separateEdge(s->separateLoop(h, nh));

	s->separateLoop(h->getNextHalf(), nh->getNextHalf()->getNextHalf());

	h = s->getMateHOnH(h->getNextHalf());

	nh = h->getNextHalf()->getNextHalf()->getNextHalf();
	h = h->getPrevHalf();

	s->separateLoop(h, nh);


	return v;
}

fk_Vector fk_SubDivision::calcSourceVertexPosition(fk_Modify *s, fk_Vertex *v)
{
	fk_Vector srcV, vAve, fAve, newP, tempP;

	srcV = v->getPosition();

	double vNum = static_cast<double>(s->getAllNeighborVOnV(v).size());
	vAve = this->calcVertexAverage(s->getAllNeighborVOnV(v));

	uint size;
	vector<fk_Loop *> tempL = s->getAllLOnV(v);
	size = static_cast<uint>(tempL.size());

	for(uint i=0; i<size; i++)
		fAve += this->calcVertexAverage(s->getAllVOnL(tempL[i]));
	fAve /= size;

	newP = (fAve + vAve + (srcV * (vNum - 2.0))) / vNum;

	return newP;
}

fk_Vector fk_SubDivision::calcVertexAverage(std::vector<fk_Vertex *> v)
{
	fk_Vector ave;

	uint size = static_cast<uint>(v.size());
	for(uint i=0; i<size; ++i)
		ave += v.at(i)->getPosition();

	ave /= size;

	return ave;
}

fk_Vector fk_SubDivision::calcEdgeVertexPosition(fk_Modify *s, fk_Edge *e)
{
	fk_Loop *l1, *l2;
	fk_Vertex	*v1, *v2;

	l1 = e->getLeftHalf()->getParentLoop();
	l2 = e->getRightHalf()->getParentLoop();

	fk_Vector f1, f2;
	if(l1 != nullptr)
		f1 = this->calcVertexAverage(s->getAllVOnL(l1));
	if(l2 != nullptr)
		f2 = this->calcVertexAverage(s->getAllVOnL(l2));

	v1 = e->getLeftHalf()->getVertex();
	v2 = e->getRightHalf()->getVertex();

	return (v1->getPosition() + v2->getPosition() + f1 + f2) / 4.0;
}
