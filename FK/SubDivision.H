#ifndef __FK_SUBDIVISION_H__
#define __FK_SUBDIVISION_H__
 
#include <FK/Modify.h>
 
#if defined(_MINGW_) || defined(_MSC_VER)
typedef unsigned int uint;
#endif

class fk_SubDivision
{
public:
	fk_SubDivision();
	virtual ~fk_SubDivision();
 
	// 分割回数を指定すると、その分だけ分割する
	void    calcCatmull(int count, fk_Modify *solid);

	// Catmull_Clark法による細分割処理(1回分)
	void    Catmull_Clark(fk_Modify *solid);
 
private:
	void    createState(fk_Modify *s);
	void    deleteState(void);
 
	void        division(fk_Modify *s);
	fk_Vertex * divideTriangle(fk_Modify *s, fk_Half *h);
	fk_Vertex * divideQuad(fk_Modify *s, fk_Half *h);
 
	fk_Half *   findStarthalf(fk_Modify *s, fk_Loop *l);
 
	fk_Vector   calcSourceVertexPosition(fk_Modify *s, fk_Vertex *v);
	fk_Vector   calcEdgeVertexPosition(fk_Modify *s, fk_Edge *e);
 
	fk_Vector   calcVertexAverage(std::vector<fk_Vertex *> v);
 
	uint        _vNum, _eNum, _fNum;
	std::vector<fk_Vector>		_vPos, _ePos, _fPos;
	std::vector<fk_Vertex *>	_verts;
	std::vector<fk_Edge *>		_edges;
	std::vector<fk_Loop *>		_faces;
	std::vector<fk_Half *>		_half;
};
 
#endif
