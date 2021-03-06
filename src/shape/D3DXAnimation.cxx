﻿#define FK_DEF_SIZETYPE
#include <FK/D3DXAnimation.H>
#include <FK/D3DXData.H>
#include <FK/D3DXShapeParser.H>
#include <FK/BVHMotion.h>
#include <FK/Math.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_D3DXSkinMap::Member::Member(void) :
	frame(nullptr), weight(-1.0)
{
	return;
}

fk_D3DXSkinMap::fk_D3DXSkinMap(void) : _m(make_unique<Member>())
{
	return;
}

fk_D3DXSkinMap::fk_D3DXSkinMap(const fk_D3DXSkinMap &argSkinMap)
{
	_m->frame = argSkinMap._m->frame;
	_m->weight = argSkinMap._m->weight;
}

fk_D3DXSkinMap::~fk_D3DXSkinMap()
{
	return;
}

void fk_D3DXSkinMap::SetFrame(fk_D3DXFrame *argFrame)
{
	_m->frame = argFrame;
	return;
}

void fk_D3DXSkinMap::SetWeight(double argWeight)
{
	_m->weight = argWeight;
	return;
}

fk_D3DXFrame * fk_D3DXSkinMap::GetFrame(void)
{
	return _m->frame;
}

double fk_D3DXSkinMap::GetWeight(void)
{
	return _m->weight;
}

fk_D3DXAnimation::Member::Member(void) : tree(nullptr)
{
	return;
}

fk_D3DXAnimation::fk_D3DXAnimation(void) : _m(make_unique<Member>())
{
	return;
}

fk_D3DXAnimation::~fk_D3DXAnimation()
{
	return;
}

void fk_D3DXAnimation::SetTree(fk_Tree *argTree)
{
	_m->tree = argTree;
	return;
}

bool fk_D3DXAnimation::GetVector(ifstream &argIFS,
								 string *argLine, fk_Vector *argVec)
{
	string word;
	fk_Vector vec;

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argVec->x = Str2Double(word);

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argVec->y = Str2Double(word);

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argVec->z = Str2Double(word);

	return true;
}

bool fk_D3DXAnimation::GetQuaternion(ifstream &argIFS, string *argLine,
									 fk_Quaternion *argQ)
{
	string word;
	fk_Vector vec;

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argQ->s = -Str2Double(word);

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argQ->v.x = Str2Double(word);

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argQ->v.y = Str2Double(word);

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argQ->v.z = Str2Double(word);

	return true;
}

bool fk_D3DXAnimation::ReadSkinData(ifstream &argIFS)
{
	string word, lineList;
	fk_D3DXSkinData *curSkin;
	int i, j;

	_m->skinData.push_back(make_unique<fk_D3DXSkinData>());
	curSkin = _m->skinData.back().get();

	word.clear();
	lineList.clear();

	if(GetWord(argIFS, ";,", &lineList, &word) == false) return false;
	
	TrimString(&word);
	while(word.find("\"") != string::npos) {
		word.replace(word.find("\""), 1, "");
	}
	curSkin->SetName(word);

	if(GetWord(argIFS, ";,", &lineList, &word) == false) return false;
	TrimString(&word);
	if(IsInteger(word) == false) return false;
	curSkin->SetNum(Str2Int(word));

	for(i = 0; i < curSkin->GetNum(); i++) {
		if(GetWord(argIFS, ";,", &lineList, &word) == false) return false;
		TrimString(&word);
		if(IsInteger(word) == false) return false;
		curSkin->SetVID(i, Str2Int(word));
	}

	for(i = 0; i < curSkin->GetNum(); i++) {
		if(GetWord(argIFS, ";,", &lineList, &word) == false) return false;
		TrimString(&word);
		if(IsNumeric(word) == false) return false;
		curSkin->SetVWeight(i, Str2Double(word));
	}

	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if(GetWord(argIFS, ";,", &lineList, &word) == false) return false;
			TrimString(&word);
			if(IsNumeric(word) == false) return false;
			curSkin->SetOffsetMatrixValue(j, i, Str2Double(word));
		}
	}

	return true;
}

void fk_D3DXAnimation::MakeNewAnimation(void)
{
	_m->animData.push_back(make_unique<fk_D3DXFrameAnimation>());
	return;
}

bool fk_D3DXAnimation::SetAnimationName(string *argLine)
{
	string word;

	word = *argLine;
	while(word.find("{") != string::npos) {
		word.replace(word.find("{"), 1, "");
	}

	while(word.find("}") != string::npos) {
		word.replace(word.find("}"), 1, "");
	}

	TrimString(&word);

	if(word.empty() == true) return false;
	if(_m->animData.empty() == true) return false;
	_m->animData.back().get()->SetName(word);
	return true;
}

bool fk_D3DXAnimation::ReadAnimationKey(ifstream &argIFS)
{
	string lineList, word;
	int type;

	lineList.clear();
	word.clear();
	if(GetWord(argIFS, ";,", &lineList, &word) == false) return false;
	if(IsInteger(word) == false) return false;
	type = Str2Int(word);
	switch(type) {
	  case 0:
		return ReadAnimationRotData(argIFS, &lineList);
	  case 1:
		return ReadAnimationScaleData(argIFS, &lineList);
	  case 2:
		return ReadAnimationTransData(argIFS, &lineList);

	  default:
		break;
	}

	return false;
}

bool fk_D3DXAnimation::ReadAnimationRotData(ifstream &argIFS, string *argLine)
{
	fk_D3DXFrameAnimation *cur;
	string word;
	int i, num;
	double key;
	fk_Quaternion quat;

	cur = _m->animData.back().get();
	word.clear();
	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	TrimString(&word);
	if(IsInteger(word) == false) return false;
	num = Str2Int(word);
	cur->SetRotKeyNum(num);
	for(i = 0; i < num; i++) {
		if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
		TrimString(&word);
		if(IsInteger(word) == false) return false;
		key = Str2Double(word);
		cur->SetRotKey(i, key);

		if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
		TrimString(&word);
		if(IsInteger(word) == false) return false;
		if(Str2Int(word) != 4) return false;

		if(GetQuaternion(argIFS, argLine, &quat) == false) return false;

		cur->SetRotData(i, quat);
	}

	return true;
}

bool fk_D3DXAnimation::ReadAnimationScaleData(ifstream &argIFS, string *argLine){
	fk_D3DXFrameAnimation *cur;
	string word;
	int i, num;
	double key;
	fk_Vector vec;

	cur = _m->animData.back().get();
	word.clear();
	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	TrimString(&word);
	if(IsInteger(word) == false) return false;
	num = Str2Int(word);
	cur->SetScaleKeyNum(num);
	for(i = 0; i < num; i++) {
		if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
		TrimString(&word);
		if(IsInteger(word) == false) return false;
		key = Str2Double(word);
		cur->SetScaleKey(i, key);

		if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
		TrimString(&word);
		if(IsInteger(word) == false) return false;
		if(Str2Int(word) != 3) return false;

		if(GetVector(argIFS, argLine, &vec) == false) return false;

		cur->SetScaleData(i, vec);
	}

	return true;
}

bool fk_D3DXAnimation::ReadAnimationTransData(ifstream &argIFS, string *argLine)
{
	fk_D3DXFrameAnimation *cur;
	string word;
	int i, num;
	double key;
	fk_Vector vec;

	cur = _m->animData.back().get();
	word.clear();
	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	TrimString(&word);
	if(IsInteger(word) == false) return false;
	num = Str2Int(word);
	cur->SetTransKeyNum(num);

	for(i = 0; i < num; i++) {
		if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
		TrimString(&word);
		if(IsInteger(word) == false) return false;
		key = Str2Double(word);
		cur->SetTransKey(i, key);

		if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
		TrimString(&word);
		if(IsInteger(word) == false) return false;
		if(Str2Int(word) != 3) return false;

		if(GetVector(argIFS, argLine, &vec) == false) return false;

		cur->SetTransData(i, vec);
	}

	return true;
}

void fk_D3DXAnimation::MakeAnimationData(void)
{
	fk_TreeData *treeData;
	fk_D3DXPropertyList *propList;
	_st i;
	fk_D3DXFrame *frame;

	if(_m->tree == nullptr) return;

	for(treeData = _m->tree->foreachData(nullptr); treeData != nullptr;
		treeData = _m->tree->foreachData(treeData)) {

		propList = static_cast<fk_D3DXPropertyList *>(treeData->getObject());
		if(propList == nullptr) continue;

		if(propList->GetProperty() == "Frame") {
			frame = MakeNewFrame(treeData);
		} else {
			continue;
		}

		for(i = 0; i < _m->skinData.size(); i++) {
			if(_m->skinData[i]->GetName() == propList->GetData()) {
				frame->SetSkin(_m->skinData[i].get());
				break;
			}
		}

		for(i = 0; i < _m->animData.size(); i++) {
			if(_m->animData[i]->GetName() == propList->GetData()) {
				frame->SetAnimation(_m->animData[i].get());
				break;
			}
		}

		frame->SetUpMatrix();
	}

	return;
}

fk_D3DXFrame * fk_D3DXAnimation::MakeNewFrame(fk_TreeData *argData)
{
	fk_D3DXPropertyList *prop, *parentProp;
	fk_TreeData *parentData;
	fk_D3DXFrame *frame, *parentFrame;

	prop = static_cast<fk_D3DXPropertyList *>(argData->getObject());

	_m->frameData.push_back(make_unique<fk_D3DXFrame>());
	frame = _m->frameData.back().get();

	frame->SetName(prop->GetData());
	prop->SetFrame(frame);
	frame->SetInitMatrix(prop->GetFrameMatrix());

	parentData = argData->getParent();
	if(parentData == nullptr) return frame;

	parentProp = (fk_D3DXPropertyList *)(parentData->getObject());
	if(parentProp == nullptr) return frame;

	parentFrame = parentProp->GetFrame();
	if(parentFrame == nullptr) return frame;

	frame->SetParentFrame(parentFrame);
	return frame;
}

void fk_D3DXAnimation::MakeSkinMap(fk_D3DXShapeParser *argShape)
{
	_st i, j;
	int vID;
	fk_D3DXSkinMap *skinMap;
	fk_D3DXSkinData *tmpSkinData;
	double weight;

	_m->mapData.resize(_st(argShape->GetOptVSize()));

	for(i = 0; i < _m->frameData.size(); i++) {
		tmpSkinData = _m->frameData[i]->GetSkin();
		if(tmpSkinData == nullptr) continue;

		for(j = 0; j < static_cast<_st>(tmpSkinData->GetNum()); j++) {
			vID = argShape->GetVMap(tmpSkinData->GetVID(static_cast<int>(j)));
			if(vID < 0) continue;
			if(vID >= argShape->GetOptVSize()) {
				return;
			}

			weight = tmpSkinData->GetWeight(static_cast<int>(j));

			if(weight > fk_Math::EPS) {
				_m->mapData[static_cast<_st>(vID)].push_back(make_unique<fk_D3DXSkinMap>());
				skinMap = _m->mapData[static_cast<_st>(vID)].back().get();
				skinMap->SetFrame(_m->frameData[i].get());
				skinMap->SetWeight(weight);
			}
		}
	}

	return;
}

void fk_D3DXAnimation::MakeDummySkinWeights(fk_TreeData *argData, int argVNum)
{
	fk_D3DXPropertyList *prop;
	fk_D3DXFrame *frame;
	fk_D3DXSkinData *curSkin;
	int i;
	fk_Matrix offsetMatrix;

	prop = static_cast<fk_D3DXPropertyList *>(argData->getObject());
	if(prop == nullptr) return;
	frame = prop->GetFrame();
	if(frame == nullptr) return;

	_m->skinData.push_back(make_unique<fk_D3DXSkinData>());
	curSkin = _m->skinData.back().get();

	curSkin->SetName(frame->GetName());
	curSkin->SetNum(argVNum);

	for(i = 0; i < argVNum; i++) {
		curSkin->SetVID(i, i);
		curSkin->SetVWeight(i, 1.0);
	}

	frame->SetSkin(curSkin);
	frame->SetUpMatrix();

	return;
}

void fk_D3DXAnimation::SetTime(double argTime)
{
	for(_st i = 0; i < _m->frameData.size(); i++) {
		_m->frameData[i]->SetTime(argTime);
	}

	return;
}

fk_FVector fk_D3DXAnimation::GetMovePos(int argID, const fk_FVector &argV)
{
	fk_Vector retV, orgV;
	fk_D3DXFrame *frame;
	double weight;

	if(argID < 0 || argID >= static_cast<int>(_m->mapData.size())) {
		return fk_FVector(retV);
	}

	retV.set(0.0, 0.0, 0.0);
	orgV = fk_Vector(argV);

	for(_st i = 0; i < _m->mapData[_st(argID)].size(); ++i) {
		frame = _m->mapData[_st(argID)][i]->GetFrame();
		weight = _m->mapData[_st(argID)][i]->GetWeight();

		retV += weight * (*(frame->GetTotalMatrix()) * orgV);
	}

	return fk_FVector(retV);
}

void fk_D3DXAnimation::SetBVHMotion(fk_BVHBase *argBVH)
{
	int						i, j;
	fk_Quaternion			q;
	fk_D3DXFrameAnimation	*cur;
	double					timeD;
	int						fTime;
	int						posSize, rotSize;

	if(argBVH == nullptr) return;

	for(i = 0; i < int(_m->frameData.size()); i++) {
		_m->frameData.at(_st(i))->SetAnimation(nullptr);
	}
	_m->animData.clear();

	for(i = 0; i < argBVH->getNodeNum(); i++) {

		if(argBVH->getNodeName(i) == "End Site") continue;

		MakeNewAnimation();

		cur = _m->animData.back().get();

		cur->SetName(argBVH->getNodeName(i));
		posSize = argBVH->getPosSize(i);
		rotSize = argBVH->getRotSize(i);
		cur->SetTransKeyNum(posSize);
		cur->SetRotKeyNum(rotSize);

		if(posSize > rotSize) {
			cur->SetScaleKeyNum(posSize);
		} else {
			cur->SetScaleKeyNum(rotSize);
		}

		for(j = 0; j < cur->GetTransKeyNum(); j++) {
			fTime = int(argBVH->getOneFrameTime()*1000.0);
			timeD = double(fTime)*(double(j)+1.0);
															 
			cur->SetTransKey(j, timeD);
			cur->SetTransData(j, argBVH->getPos(i, j));
		}
		for(j = 0; j < cur->GetRotKeyNum(); j++) {
			fTime = int(argBVH->getOneFrameTime()*1000.0);
			timeD = double(fTime)*(double(j)+1.0);

			cur->SetRotKey(j, timeD);
			q.makeEuler(argBVH->getRot(i, j));
			cur->SetRotData(j, q);
		}
		for(j = 0; j < cur->GetScaleKeyNum(); j++) {
			fTime = int(argBVH->getOneFrameTime()*1000.0);
			timeD = double(fTime)*(double(j)+1.0);

			cur->SetScaleKey(j, timeD);
			cur->SetScaleData(j, fk_Vector(1.0, 1.0, 1.0));
		}

		for(j = 0; j < int(_m->frameData.size()); j++) {
			if(cur->GetName() == _m->frameData.at(_st(j))->GetName()) {
				_m->frameData.at(_st(j))->SetAnimation(cur);
				_m->frameData.at(_st(j))->SetUpMatrix();
				break;
			}
		}
	}

	return;
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
