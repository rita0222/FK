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

#define FK_DEF_SIZETYPE
#include <FK/MQOOut.H>
#include <FK/Solid.h>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Loop.h>
#include <FK/Error.H>
#include <FK/IndexFace.h>

using namespace std;

typedef list<fk_Loop *>::iterator	loopIte;


bool fk_MQOOut::Convert(void)
{
	if(solid != NULL) {
		return Convert_Solid();
	} else if(ifs != NULL) {
		return Convert_IFS();
	}
	return false;
}

bool fk_MQOOut::Convert_Solid(void)
{
	fk_Loop					*curL;
	fk_Half					*startH, *curH;
	fk_Vertex				*curV;
	bool					tesseMode;
	vector<int>				tmpFaceArray;
	vector<fk_Vertex *>		*tesseVertexArray;
	vector<int>				*tesseIDArray;
	_st						i;
	int						curMate = -1;

	if(solid->checkDB() == false) return false;

	MakeMaterialPalette(FK_SOLID);
	MakeVertexIDMap_Solid();
	fBuf.clear();

	for(curL = solid->getNextL(NULL);
		curL != NULL;
		curL = solid->getNextL(curL)) {

		if(mBuf.empty() == false) {
			curMate = curL->getElemMaterialID();
		}
		startH = curH = curL->getOneHalf();
		tmpFaceArray.clear();
		do {
			curV = curH->getVertex();
			tmpFaceArray.push_back(vertIDMap[curV]);
			curH = curH->getNextHalf();
		} while(startH != curH);

		if(tmpFaceArray.size() < 3) continue;

		switch(tmpFaceArray.size()) {
		  case 3:
			fBuf.push_back(fk_StrPrintf("3 V(%d %d %d) M(%d)",
										tmpFaceArray[2], tmpFaceArray[1],
										tmpFaceArray[0], curMate));
			break;

		  case 4:
			fBuf.push_back(fk_StrPrintf("4 V(%d %d %d %d) M(%d)",
										tmpFaceArray[3], tmpFaceArray[2],
										tmpFaceArray[1], tmpFaceArray[0], curMate));
			break;

		  default:
			tmpFaceArray.clear();
			tesseMode = curL->getTesselateMode();
			curL->setTesselateMode(true);
			if(curL->isTesselated() == false) continue;

			tesseVertexArray = curL->GetTesselateVertex();
			tesseIDArray = curL->GetTesselateIndex();

			for(i = 0; i < tesseIDArray->size(); i++) {
				curV = tesseVertexArray->at(static_cast<_st>(tesseIDArray->at(i)));
				tmpFaceArray.push_back(vertIDMap[curV]);
			}

			for(i = 0; i < tesseIDArray->size(); i += 3) {
				fBuf.push_back(fk_StrPrintf("3 V(%d %d %d) M(%d)",
											tmpFaceArray[i+2],
											tmpFaceArray[i+1],
											tmpFaceArray[i], curMate));
			}

			curL->setTesselateMode(tesseMode);
			break;
		}


	}

	return true;
}

void fk_MQOOut::MakeVertexIDMap_Solid(void)
{
	int			id = 0;
	fk_Vertex	*v;
	fk_Vector	*p;

	vBuf.clear();
	vertIDMap.clear();
	for(v = solid->getNextV(NULL); v != NULL; v = solid->getNextV(v)) {
		vertIDMap[v] = id;
		p = v->GetPositionP();
		vBuf.push_back(fk_StrPrintf("%.4f %.4f %.4f", p->x, p->y, p->z));
		id++;
	}

	return;
}

bool fk_MQOOut::Convert_IFS(void)
{
	int				i;
	vector<int>		fData;
	int				curMate = -1;

	MakeMaterialPalette(FK_INDEXFACESET);
	MakeVertexIDMap_IFS();
	fBuf.clear();

	for(i = 0; i < ifs->getFaceSize(); i++) {
		if(mBuf.empty() == false) {
			curMate = ifs->getElemMaterialID(i);
		}
		fData = ifs->getFaceData(i);

		switch(fData.size()) {
		  case 3:
			fBuf.push_back(fk_StrPrintf("3 V(%d %d %d) M(%d)",
										fData[2], fData[1],
										fData[0], curMate));
			break;

		  case 4:
			fBuf.push_back(fk_StrPrintf("4 V(%d %d %d %d) M(%d)",
										fData[3], fData[2],
										fData[1], fData[0], curMate));
			break;

		  default:
			break;
		}
	}

	return true;
}

void fk_MQOOut::MakeVertexIDMap_IFS(void)
{
	int			i;
	fk_Vector	pos;

	vBuf.clear();
	for(i = 0; i < ifs->getPosSize(); i++) {
		pos = ifs->getPosVec(i);
		vBuf.push_back(fk_StrPrintf("%.4f %.4f %.4f",
									pos.x, pos.y, pos.z));
	}

	return;
}

float fk_MQOOut::CalcMonotoneLuminance(fk_Color *col)
{
	float maximum = col->getR();
	if (maximum < col->getG()) maximum = col->getG();
	if (maximum < col->getB()) maximum = col->getB();

	return maximum;
}

void fk_MQOOut::MakeMaterialPalette(int argType)
{
	int			i, j, mateNum;
	fk_Material	*tmpMate;
	fk_Color	baseCol;
	float		tmpDif, tmpAmb, tmpEmi, tmpSpe;

	mBuf.clear();
	if(argType == FK_SOLID) {
		mateNum = solid->getPaletteSize();
	} else if(argType == FK_INDEXFACESET) {
		mateNum = ifs->getPaletteSize();
	} else {
		return;
	}
	for(i = 0; i < mateNum; ++i) {
		if(argType == FK_SOLID) {
			tmpMate = solid->getMaterial(i);
		} else if(argType == FK_INDEXFACESET) {
			tmpMate = ifs->getMaterial(i);
		} else {
			break;
		}

		tmpDif = CalcMonotoneLuminance(tmpMate->getDiffuse());
		tmpAmb = CalcMonotoneLuminance(tmpMate->getAmbient());
		tmpEmi = CalcMonotoneLuminance(tmpMate->getEmission());
		tmpSpe = CalcMonotoneLuminance(tmpMate->getSpecular());

		baseCol = *(tmpMate->getDiffuse());
		if(tmpDif > FK_COLOR_EPS) {
			for(j = 0; j < 3; ++j) {
				float tmp = baseCol.col[j] / tmpDif;
				baseCol.col[j] = (tmp < 1.0f) ? tmp : 1.0f;
			}
		} else {
			baseCol.set(1.0f, 1.0f, 1.0f);
		}

		mBuf.push_back(
			fk_StrPrintf("\"mate%d\" col(%.3f %.3f %.3f %.3f) dif(%.3f) amb(%.3f) emi(%.3f) spc(%.3f) power(%.2f)",
			i, baseCol.getR(), baseCol.getG(), baseCol.getB(), tmpMate->getAlpha(),
			tmpDif, tmpAmb, tmpEmi, tmpSpe, tmpMate->getShininess())
		);
	}

	return;
}

void fk_MQOOut::Init(void)
{
	vertIDMap.clear();
	mBuf.clear();
	vBuf.clear();
	fBuf.clear();

	return;
}

fk_MQOOut::fk_MQOOut(void)
{
	Init();
	SetSolid(NULL);
	SetIndexFaceSet(NULL);

	return;
}

fk_MQOOut::fk_MQOOut(fk_Solid *argSolid)
{
	Init();
	SetSolid(argSolid);

	return;
}

fk_MQOOut::fk_MQOOut(fk_IndexFaceSet *argIFS)
{
	Init();
	SetIndexFaceSet(argIFS);

	return;
}

fk_MQOOut::~fk_MQOOut(void)
{
	Init();
}

void fk_MQOOut::SetSolid(fk_Solid *argSolid)
{
	solid = argSolid;
	ifs = NULL;
	return;
}

void fk_MQOOut::SetIndexFaceSet(fk_IndexFaceSet *argIFS)
{
	ifs = argIFS;
	solid = NULL;
	return;
}

bool fk_MQOOut::WriteMQOFile(string argFName)
{
	ofstream	ofs(argFName);
	_st			i;
	fk_Color	tmpCol;

	if(ofs.fail()) return false;
	
	if(!Convert()) {
		ofs.close();
		return false;
	}

	ofs << "Metasequoia Document" << endl;
	ofs << "Format Text Ver 1.0" << endl << endl;

	if(mBuf.empty() == false) {
		ofs << fk_StrPrintf("Material %d {", static_cast<int>(mBuf.size())) << endl;
		for(i = 0; i < mBuf.size(); ++i) {
			ofs << fk_StrPrintf("\t%s", mBuf[i].c_str()) << endl;
		}
		ofs << "}" << endl;
	}

	ofs << "Object \"obj1\" {" << endl;
	ofs << fk_StrPrintf("\tvertex %d {", static_cast<int>(vBuf.size())) << endl;

	for(i = 0; i < vBuf.size(); i++) {
		ofs << fk_StrPrintf("\t\t%s", vBuf.at(i).c_str()) << endl;
	}

	ofs << "\t}" << endl;
	ofs << fk_StrPrintf("\tface %d {", static_cast<int>(fBuf.size())) << endl;

	for(i = 0; i < fBuf.size(); i++) {
		ofs << fk_StrPrintf("\t\t%s", fBuf.at(i).c_str()) << endl;
	}

	ofs << "\t}" << endl;
	ofs << "}" << endl;
	ofs << "Eof" << endl;

	ofs.close();
	return true;
}
