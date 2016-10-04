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

#include <FK/BoundaryElem.H>
#include <FK/Math.h>
#include <FK/IndexFace.h>
#include <FK/Solid.h>
#include <FK/Vertex.h>
#include <FK/Point.h>
#include <FK/Texture.h>
#include <FK/IFSTexture.h>
#include <FK/Error.H>

using namespace std;

bool fk_SphereBoundary::isInter(const fk_Vector &argP1, double argR1,
								const fk_Vector &argP2, double argR2)
{
	double		dist2 = (argP1 - argP2).dist2();
	double		r2 = (argR1 + argR2)*(argR1 + argR2);

	return (dist2 <= r2);
}

bool fk_SphereBoundary::isCollision(const fk_Vector &argOldP1,
									const fk_Vector &argNewP1,
									double argRad1,
									const fk_Vector &argOldP2,
									const fk_Vector &argNewP2,
									double argRad2,
									double *argTime)
{
	fk_Vector		A, B;
	double			vecProd, orgDist2, sqValue, distA2;
	
	B = argOldP2 - argOldP1;
	A = argNewP2 - argNewP1 - B;
	distA2 = A.dist2();
	if(distA2 < FK_EPS) {
		*argTime = 0.0;
		return true;
	}

	vecProd = A * B;
	orgDist2 = (argRad1 + argRad2) * (argRad1 + argRad2);
	sqValue = (vecProd * vecProd) - distA2*(B.dist2() - orgDist2);
	if(sqValue < 0.0) return false;
	*argTime = (-vecProd - sqrt(sqValue))/distA2;
	return true;
}

double fk_SphereBoundary::getAdjustRadius(fk_Shape *argShape)
{
	switch(argShape->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		return GetAdjustIFS(static_cast<fk_IndexFaceSet *>(argShape));

	  case FK_SHAPE_SOLID:
		return GetAdjustSolid(static_cast<fk_Solid *>(argShape));

	  case FK_SHAPE_POINT:
		return GetAdjustPoint(static_cast<fk_Point *>(argShape));

	  case FK_SHAPE_TEXTURE:
		return GetAdjustTexture(static_cast<fk_Texture *>(argShape));

	  default:
		break;
	}

	return 0.0;
}

double fk_SphereBoundary::GetAdjustIFS(fk_IndexFaceSet *argIFS)
{
	int			i, iMax;
	double		len, lMax = 0.0;

	iMax = argIFS->getPosSize();
	for(i = 0; i < iMax; i++) {
		len = argIFS->getPosVec(i).dist();
		if(lMax < len) lMax = len;
	}
	return lMax;
}

double fk_SphereBoundary::GetAdjustSolid(fk_Solid *argSolid)
{
	fk_Vertex	*v;
	double		len, lMax = 0.0;
	
	for(v = argSolid->getNextV(nullptr); v != nullptr; v = argSolid->getNextV(v)) {
		len = v->getPosition().dist();
		if(lMax < len) lMax = len;
	}
	return lMax;
}

double fk_SphereBoundary::GetAdjustPoint(fk_Point *argPoint)
{
	fk_Vector	V;
	int			i, iMax;
	double		len, lMax = 0.0;

	iMax = argPoint->getSize();
	for(i = 0; i < iMax; i++) {
		V = *(argPoint->getVertex(i));
		len = V.dist();
		if(lMax < len) lMax = len;
	}
	return lMax;
}

double fk_SphereBoundary::GetAdjustTexture(fk_Texture *argTexture)
{
	fk_TexCoord		tc;
	double			x, y;
	fk_Vector		v;
	int				i;
	fk_RectTexture	*rTex;
	fk_TriTexture	*tTex;
	fk_IFSTexture	*ifsTex;
	double			len, lMax = 0.0;

	switch(argTexture->getObjectType()) {
	  case FK_RECTTEXTURE:
		rTex = static_cast<fk_RectTexture *>(argTexture);
		tc = rTex->getTextureSize();
		x = tc.x/2.0;
		y = tc.y/2.0;
		return(sqrt(x*x + y*y));

	  case FK_TRITEXTURE:
		tTex = static_cast<fk_TriTexture *>(argTexture);
		for(i = 0; i < 3; i++) {
			v = tTex->getVertexPos(i);
			len = v.dist();
			if(lMax < len) lMax = len;
		}
		return lMax;

	  case FK_MESHTEXTURE:
		return GetAdjustMeshTexture(static_cast<fk_MeshTexture *>(argTexture));

	  case FK_IFSTEXTURE:
		ifsTex = static_cast<fk_IFSTexture *>(argTexture);
		return GetAdjustIFS(ifsTex->getIFS());

	  default:
		break;
	}

	return 0.0;
}

double fk_SphereBoundary::GetAdjustMeshTexture(fk_MeshTexture *argMesh)
{
	int			i, j, tNum;
	fk_Vector	V;
	double		len, lMax = 0.0;
	
	tNum = argMesh->getTriNum();
	for(i = 0; i < tNum; i++) {
		for(j = 0; j < 3; j++) {
			V = argMesh->getVertexPos(i, j);
			len = V.dist();
			if(lMax < len) lMax = len;
		}
	}
	return lMax;
}

bool fk_AABBBoundary::isInter(const fk_Vector &argP1, const fk_Vector &argS1,
							  const fk_Vector &argP2, const fk_Vector &argS2)
{
	fk_Vector	v = (argS1 + argS2)/2.0;
	fk_Vector	d = argP1 - argP2;

	if(fabs(d.x) > v.x) return false;
	if(fabs(d.y) > v.y) return false;
	if(fabs(d.z) > v.z) return false;
	return true;
}



fk_Vector fk_AABBBoundary::getAdjustSize(fk_Shape *argShape, fk_Matrix argMat)
{
	static fk_HVector	X(1.0, 0.0, 0.0, 0.0), Y(0.0, 1.0, 0.0, 0.0), Z(0.0, 0.0, 1.0, 0.0);
	fk_Vector			X_, Y_, Z_;

	X_ = argMat * X;
	Y_ = argMat * Y;
	Z_ = argMat * Z;
	X_.normalize();
	Y_.normalize();
	Z_.normalize();

	switch(argShape->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		return GetAdjustIFS(static_cast<fk_IndexFaceSet *>(argShape), X_, Y_, Z_);

	  case FK_SHAPE_SOLID:
		return GetAdjustSolid(static_cast<fk_Solid *>(argShape), X_, Y_, Z_);

	  case FK_SHAPE_POINT:
		return GetAdjustPoint(static_cast<fk_Point *>(argShape), X_, Y_, Z_);

	  case FK_SHAPE_TEXTURE:
		return GetAdjustTexture(static_cast<fk_Texture *>(argShape), X_, Y_, Z_);

	  default:
		break;
	}

	return fk_Vector();
}

fk_Vector fk_AABBBoundary::GetAdjustIFS(fk_IndexFaceSet *argIFS,
										const fk_Vector &argX,
										const fk_Vector &argY,
										const fk_Vector &argZ)
{
	int			i, iMax;
	fk_Vector	p, pMax;

	iMax = argIFS->getPosSize();
	for(i = 0; i < iMax; i++) {
		p = argIFS->getPosVec(i);
		AdjustVec(&pMax, p, argX, argY, argZ);
	}
	return (2.0*pMax);
}

fk_Vector fk_AABBBoundary::GetAdjustSolid(fk_Solid *argSolid,
										  const fk_Vector &argX,
										  const fk_Vector &argY,
										  const fk_Vector &argZ)
{
	fk_Vertex	*v;
	fk_Vector	p, pMax;

	for(v = argSolid->getNextV(nullptr); v != nullptr; v = argSolid->getNextV(v)) {
		p = v->getPosition();
		AdjustVec(&pMax, p, argX, argY, argZ);
	}
	return (2.0*pMax);
}

fk_Vector fk_AABBBoundary::GetAdjustPoint(fk_Point *argPoint,
										  const fk_Vector &argX,
										  const fk_Vector &argY,
										  const fk_Vector &argZ)
{
	fk_Vector	p, pMax;
	int			i, iMax;

	iMax = argPoint->getSize();
	for(i = 0; i < iMax; i++) {
		p = *(argPoint->getVertex(i));
		AdjustVec(&pMax, p, argX, argY, argZ);
	}
	return (2.0*pMax);
}

fk_Vector fk_AABBBoundary::GetAdjustTexture(fk_Texture *argTexture,
											const fk_Vector &argX,
											const fk_Vector &argY,
											const fk_Vector &argZ)
{
	fk_TexCoord		tc;
	int				i;
	fk_RectTexture	*rTex;
	fk_TriTexture	*tTex;
	fk_IFSTexture	*ifsTex;
	fk_Vector		p, pMax;

	switch(argTexture->getObjectType()) {
	  case FK_RECTTEXTURE:
		rTex = static_cast<fk_RectTexture *>(argTexture);
		tc = rTex->getTextureSize();
		p.set(tc.x, tc.y, 0.0);
		AdjustVec(&pMax, p, argX, argY, argZ);
		return(pMax);

	  case FK_TRITEXTURE:
		tTex = static_cast<fk_TriTexture *>(argTexture);
		for(i = 0; i < 3; i++) {
			p = tTex->getVertexPos(i);
			AdjustVec(&pMax, p, argX, argY, argZ);
		}
		return (2.0*pMax);

	  case FK_MESHTEXTURE:
		return GetAdjustMeshTexture(static_cast<fk_MeshTexture *>(argTexture), argX, argY, argZ);

	  case FK_IFSTEXTURE:
		ifsTex = static_cast<fk_IFSTexture *>(argTexture);
		return GetAdjustIFS(ifsTex->getIFS(), argX, argY, argZ);

	  default:
		break;
	}

	return fk_Vector();
}

fk_Vector fk_AABBBoundary::GetAdjustMeshTexture(fk_MeshTexture *argMesh,
												const fk_Vector &argX,
												const fk_Vector &argY,
												const fk_Vector &argZ)
{
	int			i, j, tNum;
	fk_Vector	p, pMax;
	
	tNum = argMesh->getTriNum();
	for(i = 0; i < tNum; i++) {
		for(j = 0; j < 3; j++) {
			p = argMesh->getVertexPos(i, j);
			AdjustVec(&pMax, p, argX, argY, argZ);
		}
	}
	return pMax;
}


void fk_AABBBoundary::AdjustVec(fk_Vector *argMax, const fk_Vector &argV,
								const fk_Vector &argX,
								const fk_Vector &argY,
								const fk_Vector &argZ)
{
	fk_Vector		tmp;

	tmp.x = fabs(argV * argX);
	tmp.y = fabs(argV * argY);
	tmp.z = fabs(argV * argZ);
	if(argMax->x < fabs(tmp.x)) argMax->x = fabs(tmp.x);
	if(argMax->y < fabs(tmp.y)) argMax->y = fabs(tmp.y);
	if(argMax->z < fabs(tmp.z)) argMax->z = fabs(tmp.z);
	return;
}

bool fk_OBBBoundary::isInter(const fk_Vector A[3],
							 const fk_Vector B[3],
							 const double a[3], const double b[3], const fk_Vector &P)
{
	double		r;
	int			i, j, k;
	fk_Vector	N;

	for(i = 0; i < 3; i++) {
		r = a[i];
		for(j = 0; j < 3; j++) r += b[j] * fabs(B[j] * A[i]);
		if(fabs(P * A[i]) > r) return false;
	}

	for(i = 0; i < 3; i++) {
		r = b[i];
		for(j = 0; j < 3; j++) r += a[j] * fabs(A[j] * B[i]);
		if(fabs(P * B[i]) > r) return false;

	}

	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			N = A[i] ^ B[j];
			if(N.dist2() < FK_EPS) continue;
			N.normalize();
			r = 0.0;
			for(k = 0; k < 3; k++) {
				r += a[k] * fabs(A[k] * N);
				r += b[k] * fabs(B[k] * N);
			}
			if(fabs(P * N) > r) return false;
		}
	}

	return true;
}

fk_Vector fk_OBBBoundary::getAdjustSize(fk_Shape *argShape)
{
	switch(argShape->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		return GetAdjustIFS(static_cast<fk_IndexFaceSet *>(argShape));

	  case FK_SHAPE_SOLID:
		return GetAdjustSolid(static_cast<fk_Solid *>(argShape));

	  case FK_SHAPE_POINT:
		return GetAdjustPoint(static_cast<fk_Point *>(argShape));

	  case FK_SHAPE_TEXTURE:
		return GetAdjustTexture(static_cast<fk_Texture *>(argShape));

	  default:
		break;
	}

	return fk_Vector();
}

fk_Vector fk_OBBBoundary::GetAdjustIFS(fk_IndexFaceSet *argIFS)
{
	int			i, iMax;
	fk_Vector	p, pMax;

	iMax = argIFS->getPosSize();
	for(i = 0; i < iMax; i++) {
		p = argIFS->getPosVec(i);
		AdjustVec(&pMax, p);
	}
	return (2.0*pMax);
}

fk_Vector fk_OBBBoundary::GetAdjustSolid(fk_Solid *argSolid)
{
	fk_Vertex	*v;
	fk_Vector	p, pMax;

	for(v = argSolid->getNextV(nullptr); v != nullptr; v = argSolid->getNextV(v)) {
		p = v->getPosition();
		AdjustVec(&pMax, p);
	}
	return (2.0*pMax);
}

fk_Vector fk_OBBBoundary::GetAdjustPoint(fk_Point *argPoint)
{
	fk_Vector	p, pMax;
	int			i, iMax;

	iMax = argPoint->getSize();
	for(i = 0; i < iMax; i++) {
		p = *(argPoint->getVertex(i));
		AdjustVec(&pMax, p);
	}
	return (2.0*pMax);
}

fk_Vector fk_OBBBoundary::GetAdjustTexture(fk_Texture *argTexture)
{
	fk_TexCoord		tc;
	int				i;
	fk_RectTexture	*rTex;
	fk_TriTexture	*tTex;
	fk_IFSTexture	*ifsTex;
	fk_Vector		p, pMax;

	switch(argTexture->getObjectType()) {
	  case FK_RECTTEXTURE:
		rTex = static_cast<fk_RectTexture *>(argTexture);
		tc = rTex->getTextureSize();
		p.x = tc.x;
		p.y = tc.y;
		return(p);

	  case FK_TRITEXTURE:
		tTex = static_cast<fk_TriTexture *>(argTexture);
		for(i = 0; i < 3; i++) {
			p = tTex->getVertexPos(i);
			AdjustVec(&pMax, p);
		}
		return (2.0*pMax);

	  case FK_MESHTEXTURE:
		return GetAdjustMeshTexture(static_cast<fk_MeshTexture *>(argTexture));

	  case FK_IFSTEXTURE:
		ifsTex = static_cast<fk_IFSTexture *>(argTexture);
		return GetAdjustIFS(ifsTex->getIFS());

	  default:
		break;
	}

	return fk_Vector();
}

fk_Vector fk_OBBBoundary::GetAdjustMeshTexture(fk_MeshTexture *argMesh)
{
	int			i, j, tNum;
	fk_Vector	p, pMax;
	
	tNum = argMesh->getTriNum();
	for(i = 0; i < tNum; i++) {
		for(j = 0; j < 3; j++) {
			p = argMesh->getVertexPos(i, j);
			AdjustVec(&pMax, p);
		}
	}
	return pMax;
}

void fk_OBBBoundary::AdjustVec(fk_Vector *argMax, const fk_Vector &argV)
{
	if(argMax->x < fabs(argV.x)) argMax->x = fabs(argV.x);
	if(argMax->y < fabs(argV.y)) argMax->y = fabs(argV.y);
	if(argMax->z < fabs(argV.z)) argMax->z = fabs(argV.z);
	return;
}

bool fk_CapsuleBoundary::isInter(const fk_Vector &argS1,
								 const fk_Vector &argE1,
								 double argR1,
								 const fk_Vector &argS2,
								 const fk_Vector &argE2,
								 double argR2)
{
	static double		s, t, l;
	static fk_Vector	P, Q;

	l = fk_Math::calcClosestPtSegToSeg(argS1, argE1, argS2, argE2,
									   &s, &t, &P, &Q);

	if(l < argR1 + argR2 + FK_EPS) return true;
	return false;
}

double fk_CapsuleBoundary::getAdjustRadius(fk_Shape *argShape,
										   const fk_Vector &argS, const fk_Vector &argE)
{
	switch(argShape->getRealShapeType()) {
	  case FK_SHAPE_IFS:
		return GetAdjustIFS(static_cast<fk_IndexFaceSet *>(argShape), argS, argE);

	  case FK_SHAPE_SOLID:
		return GetAdjustSolid(static_cast<fk_Solid *>(argShape), argS, argE);

	  case FK_SHAPE_POINT:
		return GetAdjustPoint(static_cast<fk_Point *>(argShape), argS, argE);

	  case FK_SHAPE_TEXTURE:
		return GetAdjustTexture(static_cast<fk_Texture *>(argShape), argS, argE);

	  default:
		break;
	}

	return 0.0;
}

double fk_CapsuleBoundary::GetAdjustIFS(fk_IndexFaceSet *argIFS,
										const fk_Vector &argS, const fk_Vector &argE)

{
	int			i, iMax;
	double		len, lMax = 0.0;
	fk_Vector	p;

	iMax = argIFS->getPosSize();
	for(i = 0; i < iMax; i++) {
		p = argIFS->getPosVec(i);
		len = CalcLen(p, argS, argE);
		if(lMax < len) lMax = len;
	}
	return lMax;
}

double fk_CapsuleBoundary::GetAdjustSolid(fk_Solid *argSolid,
										  const fk_Vector &argS, const fk_Vector &argE)
{
	fk_Vertex	*v;
	double		len, lMax = 0.0;
	fk_Vector	p;
	
	for(v = argSolid->getNextV(nullptr); v != nullptr; v = argSolid->getNextV(v)) {
		p = v->getPosition();
		len = CalcLen(p, argS, argE);
		if(lMax < len) lMax = len;
	}
	return lMax;
}

double fk_CapsuleBoundary::GetAdjustPoint(fk_Point *argPoint,
										  const fk_Vector &argS, const fk_Vector &argE)
{
	int			i, iMax;
	double		len, lMax = 0.0;
	fk_Vector	p;

	iMax = argPoint->getSize();
	for(i = 0; i < iMax; i++) {
		p = *(argPoint->getVertex(i));
		len = CalcLen(p, argS, argE);
		if(lMax < len) lMax = len;
	}
	return lMax;
}


double fk_CapsuleBoundary::GetAdjustTexture(fk_Texture *argTexture,
											const fk_Vector &argS, const fk_Vector &argE)
{
	fk_IFSTexture *ifsTex;

	switch(argTexture->getObjectType()) {
	  case FK_RECTTEXTURE:
		return GetAdjustRectTexture(static_cast<fk_RectTexture *>(argTexture), argS, argE);

	  case FK_TRITEXTURE:
		return GetAdjustTriTexture(static_cast<fk_TriTexture *>(argTexture), argS, argE);

	  case FK_MESHTEXTURE:
		return GetAdjustMeshTexture(static_cast<fk_MeshTexture *>(argTexture), argS, argE);

	  case FK_IFSTEXTURE:
		ifsTex = static_cast<fk_IFSTexture *>(argTexture);
		return GetAdjustIFS(ifsTex->getIFS(), argS, argE);

	  default:
		break;
	}

	return 0.0;
}

double fk_CapsuleBoundary::GetAdjustRectTexture(fk_RectTexture *argTex,
												const fk_Vector &argS, const fk_Vector &argE)
{	
	static vector<fk_Vector>		p(4);
	fk_TexCoord						tc;
	double							x, y, len, lMax = 0.0;
	vector<fk_Vector>::size_type	i;

	tc = argTex->getTextureSize();
	x = tc.x/2.0;
	y = tc.y/2.0;
	p[0].set(x, y, 0.0);
	p[1].set(-x, y, 0.0);
	p[2].set(x, -y, 0.0);
	p[3].set(-x, -y, 0.0);

	for(i = 0; i < 4; i++) {
		len = CalcLen(p[i], argS, argE);
		if(lMax < len) lMax = len;
	}
	return lMax;
}

double fk_CapsuleBoundary::GetAdjustTriTexture(fk_TriTexture *argTex,
											   const fk_Vector &argS, const fk_Vector &argE)
{	
	int			i;
	double		len, lMax = 0.0;
	fk_Vector	p;

	for(i = 0; i < 3; i++) {
		p = argTex->getVertexPos(i);
		len = CalcLen(p, argS, argE);
		if(lMax < len) lMax = len;
	}

	return lMax;
}

double fk_CapsuleBoundary::GetAdjustMeshTexture(fk_MeshTexture *argMesh,
												const fk_Vector &argS, const fk_Vector &argE)
{
	int			i, j, tNum;
	fk_Vector	p;
	double		len, lMax = 0.0;
	
	tNum = argMesh->getTriNum();
	for(i = 0; i < tNum; i++) {
		for(j = 0; j < 3; j++) {
			p = argMesh->getVertexPos(i, j);
			len = CalcLen(p, argS, argE);
			if(lMax < len) lMax = len;
		}
	}
	return lMax;
}

double fk_CapsuleBoundary::CalcLen(const fk_Vector &argP,
								   const fk_Vector &argS,
								   const fk_Vector &argE)
{
	fk_Vector	q;
	double		t;

	fk_Math::calcClosestPtPtToSeg(argP, argS, argE, &t, &q);
	return (argP-q).dist();
}
