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
	return;
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
	fk_Vector *vPos, *ePos, *fPos;

	vNum = this->_vNum = static_cast<uint>(s->getVNum());
	eNum = this->_eNum = static_cast<uint>(s->getENum());
	fNum = this->_fNum = static_cast<uint>(s->getLNum());

	vPos = this->_vPos = new fk_Vector[vNum];
	ePos = this->_ePos = new fk_Vector[eNum];
	fPos = this->_fPos = new fk_Vector[fNum];

	fk_Vertex **verts;
	fk_Edge **edges;
	fk_Loop **faces;

	verts = this->_verts = new fk_Vertex *[vNum];
	edges = this->_edges = new fk_Edge *[eNum];
	faces = this->_faces = new fk_Loop *[fNum];

	this->_half = new fk_Half *[fNum];

	uint i;
	fk_Loop *l = s->getNextL(NULL);
	i = 0;
	while(l != NULL)
	{
		faces[i] = l;

		fPos[i] = this->calcVertexAverage(s->getAllVOnL(l));

		l = s->getNextL(l);
		i++;
	}

	fk_Vertex *v = s->getNextV(NULL);
	i = 0;
	while(v != NULL)
	{
		verts[i] = v;

		vPos[i] = this->calcSourceVertexPosition(s, v);

		v = s->getNextV(v);
		i++;
	}

	fk_Edge *e = s->getNextE(NULL);
	i = 0;
	while(e != NULL)
	{
		edges[i] = e;

		ePos[i] = this->calcEdgeVertexPosition(s, e);

		e = s->getNextE(e);
		i++;
	}

	return;
}

void fk_SubDivision::deleteState(void)
{
	delete [] this->_vPos;
	delete [] this->_ePos;
	delete [] this->_fPos;

	delete [] this->_verts;
	delete [] this->_edges;
	delete [] this->_faces;

	delete [] this->_half;

	this->_vPos = 0;
	this->_ePos = 0;
	this->_fPos = 0;

	this->_verts = 0;
	this->_edges = 0;
	this->_faces = 0;

	this->_half = 0;
	return;
}


// Catmull_Clark法による細分割処理
void fk_SubDivision::Catmull_Clark(fk_Modify *s)
{
	this->createState(s);

	uint size = this->_vNum;
	fk_Vertex **v = this->_verts;
	fk_Vector *vPos = this->_vPos;
	for(uint i=0; i<size; ++i)
		s->moveVertex(v[i], vPos[i]);

	this->division(s);

	this->deleteState();

	return;
}

void fk_SubDivision::division(fk_Modify *s)
{
	//uint eNum = static_cast<uint>(s->getENum());
	//uint fNum = static_cast<uint>(s->getLNum());
	fk_Vector *ePos = this->_ePos;
	fk_Vector *fPos = this->_fPos;
	fk_Edge **edges = this->_edges;
	uint size = this->_eNum;
	fk_Half **h = this->_half;
	fk_Loop *l, **faces = this->_faces;

	for(uint i=0; i<size; ++i) s->moveVertex(s->separateEdge(edges[i]), ePos[i]);

	size = this->_fNum;

	for(uint i=0; i<size; ++i)
		h[i] = this->findStarthalf(s, faces[i]);

	for(uint i=0; i<size; ++i)
	{
		l = faces[i];
		switch(l->getVNum())
		{
			case 6:
				s->moveVertex(this->divideTriangle(s, h[i]), fPos[i]);
				break;
			case 8:
				s->moveVertex(this->divideQuad(s, h[i]), fPos[i]);
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
	if(l1 != NULL)
		f1 = this->calcVertexAverage(s->getAllVOnL(l1));
	if(l2 != NULL)
		f2 = this->calcVertexAverage(s->getAllVOnL(l2));

	v1 = e->getLeftHalf()->getVertex();
	v2 = e->getRightHalf()->getVertex();

	return (v1->getPosition() + v2->getPosition() + f1 + f2) / 4.0;
}
