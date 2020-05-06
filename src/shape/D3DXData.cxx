#define FK_DEF_SIZETYPE
#include <FK/D3DXData.H>
#include <FK/Tree.h>
#include <FK/Math.h>

using namespace std;
using namespace FK;

fk_D3DXFrameAnimation::Member::Member(void)
{
	return;
}

fk_D3DXFrameAnimation::fk_D3DXFrameAnimation(void) : _m(make_unique<Member>())
{
	return;
}

fk_D3DXFrameAnimation::~fk_D3DXFrameAnimation()
{
	return;
}

void fk_D3DXFrameAnimation::SetName(const string &argName)
{
	_m->name.assign(argName);
	return;
}

string fk_D3DXFrameAnimation::GetName(void)
{
	return _m->name;
}

void fk_D3DXFrameAnimation::SetRotKeyNum(int argNum)
{
	if(argNum < 0) return;
	_m->rotKey.resize(_st(argNum));
	_m->rotData.resize(_st(argNum));
	return;
}

void fk_D3DXFrameAnimation::SetScaleKeyNum(int argNum)
{
	if(argNum < 0) return;
	_m->scaleKey.resize(_st(argNum));
	_m->scaleData.resize(_st(argNum));
	return;
}

void fk_D3DXFrameAnimation::SetTransKeyNum(int argNum)
{
	if(argNum < 0) return;
	_m->transKey.resize(_st(argNum));
	_m->transData.resize(_st(argNum));
	return;
}

int fk_D3DXFrameAnimation::GetRotKeyNum(void)
{
	return int(_m->rotKey.size());
}

int fk_D3DXFrameAnimation::GetScaleKeyNum(void)
{
	return int(_m->scaleKey.size());
}

int fk_D3DXFrameAnimation::GetTransKeyNum(void)
{
	return int(_m->transKey.size());
}

void fk_D3DXFrameAnimation::SetRotKey(int argID, double argKey)
{
	if(argID < 0 || argID >= int(_m->rotKey.size())) return;
	_m->rotKey[_st(argID)] = argKey;
	return;
}

void fk_D3DXFrameAnimation::SetScaleKey(int argID, double argKey)
{
	if(argID < 0 || argID >= int(_m->scaleKey.size())) return;
	_m->scaleKey[_st(argID)] = argKey;
	return;
}

void fk_D3DXFrameAnimation::SetTransKey(int argID, double argKey)
{
	if(argID < 0 || argID >= int(_m->transKey.size())) return;
	_m->transKey[_st(argID)] = argKey;
	return;
}

double fk_D3DXFrameAnimation::GetRotKey(int argID)
{
	if(argID < 0 || argID >= int(_m->rotKey.size())) return -1;
	return _m->rotKey[_st(argID)];
}

double fk_D3DXFrameAnimation::GetScaleKey(int argID)
{
	if(argID < 0 || argID >= int(_m->scaleKey.size())) return -1;
	return _m->scaleKey[_st(argID)];
}

double fk_D3DXFrameAnimation::GetTransKey(int argID)
{
	if(argID < 0 || argID >= int(_m->transKey.size())) return -1;
	return _m->transKey[_st(argID)];
}

void fk_D3DXFrameAnimation::SetRotData(int argID, const fk_Quaternion &argQ)
{
	if(argID < 0 || argID >= int(_m->rotData.size())) return;
	_m->rotData[_st(argID)] = argQ;
	return;
}

void fk_D3DXFrameAnimation::SetScaleData(int argID, const fk_Vector &argV)
{
	if(argID < 0 || argID >= int(_m->scaleData.size())) return;
	_m->scaleData[_st(argID)] = argV;
	return;
}

void fk_D3DXFrameAnimation::SetTransData(int argID, const fk_Vector &argV)
{
	if(argID < 0 || argID >= int(_m->transData.size())) return;
	_m->transData[_st(argID)] = argV;
	return;
}

fk_Quaternion fk_D3DXFrameAnimation::GetRotData(int argID)
{
	if(argID < 0 || argID >= int(_m->rotData.size())) {
		return fk_Quaternion();
	}
	return _m->rotData[_st(argID)];
}

fk_Vector fk_D3DXFrameAnimation::GetScaleData(int argID)
{
	if(argID < 0 || argID >= int(_m->scaleData.size())) {
		return fk_Vector();
	}
	return _m->scaleData[_st(argID)];
}

fk_Vector fk_D3DXFrameAnimation::GetTransData(int argID)
{
	if(argID < 0 || argID >= int(_m->transData.size())) {
		return fk_Vector();
	}
	return _m->transData[_st(argID)];
}

void fk_D3DXFrameAnimation::LinearDiv(double argTime, vector<double> *argArray,
									  int *retID, double *retDiv)
{
	double startTime, endTime;

	if(argArray->size() == 0) {
		*retID = -1;
		*retDiv = 0.0;
		return;
	}

	startTime = argArray->front();
	endTime = argArray->back();

	if(startTime + fk_Math::EPS > argTime) {
		*retID = 0;
		*retDiv = 0.0;
		return;
	}

	if(endTime - fk_Math::EPS < argTime) {
		*retID = int(argArray->size())-1;
		*retDiv = 0.0;
		return;
	}

	for(_st i = 1; i < argArray->size(); i++) {
		if(argArray->at(i) > argTime) {
			*retID = int(i-1);
			*retDiv = (argTime - argArray->at(i-1))/(argArray->at(i) - argArray->at(i-1));
			break;
		}
	}

	return;
}

void fk_D3DXFrameAnimation::SetTime(double argTime)
{
	fk_Matrix rotMat, scaleMat, transMat, retMat;
	fk_Quaternion q;
	fk_Angle angle;
	fk_Vector scaleV, transV;
	int rID = 0, sID = 0, tID = 0;
	double rDiv = 0.0, sDiv = 0.0, tDiv = 0.0;
	fk_Vector v1, v2;

	LinearDiv(argTime, &_m->rotKey, &rID, &rDiv);
	LinearDiv(argTime, &_m->scaleKey, &sID, &sDiv);
	LinearDiv(argTime, &_m->transKey, &tID, &tDiv);

	if(rID != -1) {
		if(rID == int(_m->rotKey.size()-1)) {
			q = _m->rotData[_st(rID)];
		} else {
			q = fk_Q_Inter_Sphere(_m->rotData[_st(rID)], _m->rotData[_st(rID)+1], rDiv);
		}
		angle = q.getEuler();
		rotMat.makeEuler(angle);
	}

	if(sID != -1) {
		if(sID == int(_m->scaleKey.size()-1)) {
			scaleV = _m->scaleData[_st(sID)];
		} else {
			v1 = _m->scaleData[_st(sID)];
			v2 = _m->scaleData[_st(sID)+1];
			scaleV = (1.0-sDiv) * v1 + sDiv * v2;
		}
		scaleMat.makeScale(scaleV);
	}

	if(tID != -1) {
		if(tID == int(_m->transKey.size()-1)) {
			transV = _m->transData[_st(tID)];
		} else {
			v1 = _m->transData[_st(tID)];
			v2 = _m->transData[_st(tID)+1];
			transV = (1.0-tDiv) * v1 + tDiv * v2;
		}
		transMat.makeTrans(transV);
	}

	_m->frameMatrix = transMat * rotMat * scaleMat;

	return;
}

double fk_D3DXFrameAnimation::GetStartTime(void)
{
	double		rS, sS, tS;

	rS = sS = tS = -1.0;
	if(_m->rotKey.empty() == false) rS = _m->rotKey[0];
	if(_m->scaleKey.empty() == false) sS = _m->scaleKey[0];
	if(_m->transKey.empty() == false) tS = _m->transKey[0];

	if(rS > sS + fk_Math::EPS || rS < sS - fk_Math::EPS ||
	   rS > tS + fk_Math::EPS || rS < tS - fk_Math::EPS) {
		return -1.0;
	}

	return rS;
}

fk_Matrix fk_D3DXFrameAnimation::GetFrameMatrix(void)
{
	return _m->frameMatrix;
}

fk_D3DXSkinData::Member::Member(void) : vNum(0)
{
	return;
}

fk_D3DXSkinData::fk_D3DXSkinData(void) : _m(make_unique<Member>())
{
	return;
}

fk_D3DXSkinData::~fk_D3DXSkinData()
{
	return;
}

void fk_D3DXSkinData::SetName(const string &argName)
{
	_m->name = argName;
	return;
}

void fk_D3DXSkinData::SetNum(int argNum)
{
	if(argNum <= 0) return;
	_m->vNum = argNum;
	_m->vArray.resize(_st(_m->vNum));
	_m->wArray.resize(_st(_m->vNum));
	return;
}

void fk_D3DXSkinData::SetVID(int argIndex, int argID)
{
	if(argIndex < 0 || argIndex >= _m->vNum) return;
	_m->vArray[_st(argIndex)] = argID;
	return;
}

void fk_D3DXSkinData::SetVWeight(int argIndex, double argWeight)
{
	if(argIndex < 0 || argIndex >= _m->vNum) return;
	_m->wArray[_st(argIndex)] = argWeight;
	return;
}

void fk_D3DXSkinData::SetOffsetMatrixValue(int argI, int argJ,
										   double argValue)
{
	if(argI < 0 || argI > 3 || argJ < 0 || argJ > 3) return;
	_m->offsetMatrix.set(argI, argJ, argValue);
	return;
}

string fk_D3DXSkinData::GetName(void)
{
	return _m->name;
}

int fk_D3DXSkinData::GetNum(void)
{
	return _m->vNum;
}

int fk_D3DXSkinData::GetVID(int argIndex)
{
	if(argIndex < 0 || argIndex >= _m->vNum) return -1;
	return _m->vArray[_st(argIndex)];
}

double fk_D3DXSkinData::GetWeight(int argIndex)
{
	if(argIndex < 0 || argIndex >= _m->vNum) return -1.0;
	return _m->wArray[_st(argIndex)];
}

fk_Matrix fk_D3DXSkinData::GetOffsetMatrix(void)
{
	return _m->offsetMatrix;
}

fk_D3DXFrame::Member::Member(void) :
	skin(nullptr), anim(nullptr), parentMatrix(nullptr)
{
	return;
}

fk_D3DXFrame::fk_D3DXFrame(void) : _m(make_unique<Member>())
{
	return;
}

fk_D3DXFrame::~fk_D3DXFrame()
{
	return;
}

void fk_D3DXFrame::SetName(const string &argName)
{
	_m->name = argName;
	return;
}

string fk_D3DXFrame::GetName(void)
{
	return _m->name;
}

void fk_D3DXFrame::SetSkin(fk_D3DXSkinData *argSkin)
{
	_m->skin = argSkin;
	return;
}

fk_D3DXSkinData * fk_D3DXFrame::GetSkin(void)
{
	return _m->skin;
}

void fk_D3DXFrame::SetAnimation(fk_D3DXFrameAnimation *argAnim)
{
	_m->anim = argAnim;
	return;
}

fk_D3DXFrameAnimation * fk_D3DXFrame::GetAnimation(void)
{
	return _m->anim;
}

void fk_D3DXFrame::SetParentFrame(fk_D3DXFrame *argParent)
{
	if(argParent == nullptr) return;
	_m->parentMatrix = &(argParent->_m->curMatrix);
	return;
}

void fk_D3DXFrame::SetInitMatrix(const fk_Matrix *argMat)
{
	_m->initMatrix = *argMat;
	return;
}

void fk_D3DXFrame::SetUpMatrix(void)
{
	if(_m->skin != nullptr) {
		_m->offsetMatrix = _m->skin->GetOffsetMatrix();
	} else {
		_m->offsetMatrix.init();
	}

	if(_m->parentMatrix != nullptr) {
		_m->curMatrix = *(_m->parentMatrix) * _m->initMatrix;
	} else {
		_m->curMatrix = _m->initMatrix;
	}

	_m->totalMatrix = _m->curMatrix * _m->offsetMatrix;

	return;
}

void fk_D3DXFrame::SetTime(double argTime)
{
	double startTime;

	if(_m->anim == nullptr) return;

	startTime = _m->anim->GetStartTime();
	if(startTime < -fk_Math::EPS || argTime < startTime - fk_Math::EPS) {
		SetUpMatrix();
		return;
	}

	_m->anim->SetTime(argTime);

	if(_m->parentMatrix != nullptr) {
		_m->curMatrix = *(_m->parentMatrix) * _m->anim->GetFrameMatrix();
	} else {
		_m->curMatrix = _m->anim->GetFrameMatrix();
	}

	_m->totalMatrix = _m->curMatrix * _m->offsetMatrix;

	return;
}

fk_Matrix * fk_D3DXFrame::GetTotalMatrix(void)
{
	return &(_m->totalMatrix);
}

fk_D3DXPropertyList::Member::Member(void) : matrixFlg(false), frame(nullptr)
{
	return;
}

fk_D3DXPropertyList::fk_D3DXPropertyList(void) : _m(make_unique<Member>())
{
	return;
}

fk_D3DXPropertyList::~fk_D3DXPropertyList()
{
	return;
}

void fk_D3DXPropertyList::SetProperty(const string &argProp)
{
	_m->property = argProp;
	return;
}

string fk_D3DXPropertyList::GetProperty(void)
{
	return _m->property;
}

void fk_D3DXPropertyList::SetData(const string &argData)
{
	_m->data = argData;
	return;
}

string fk_D3DXPropertyList::GetData(void)
{
	return _m->data;
}

void fk_D3DXPropertyList::SetFrameMatrixValue(int argI, int argJ, double argValue)
{
	_m->frameMatrix.set(argI, argJ, argValue);
	return;
}

fk_Matrix * fk_D3DXPropertyList::GetFrameMatrix(void)
{
	return &(_m->frameMatrix);
}

void fk_D3DXPropertyList::SetFrame(fk_D3DXFrame *argFrame)
{
	_m->frame = argFrame;
	return;
}

fk_D3DXFrame * fk_D3DXPropertyList::GetFrame(void)
{
	return _m->frame;
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
