#define FK_DEF_SIZETYPE
#include <stack>
#include <FK/BVHMotion.h>
#include <FK/Math.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;


fk_BVHBase::fk_BVHBase(void)
{
	return;
}

fk_BVHBase::~fk_BVHBase()
{
	return;
}

fk_BVHMotion::Member::Member(void) :
	nowFrame(0), length(0), oneFrameTime(0.0)
{
	return;
}


fk_BVHMotion::fk_BVHMotion(void) : _m(make_unique<Member>())
{
	init();
}

fk_BVHMotion::~fk_BVHMotion(void)
{
	init();
}

void fk_BVHMotion::init(void)
{
	_m->nowFrame = 0;
	_m->length = 0;
	_m->oneFrameTime = 0.033;

	_m->nodeArray.clear();
	_m->nameArray.clear();
	_m->offsetArray.clear();
	_m->typeArray.clear();
	_m->nameToNodeMap.clear();
	_m->frameFormat.clear();
	_m->posArray.clear();
	_m->rotArray.clear();

	return;
}

bool fk_BVHMotion::readBVHFile(const string argFileName)
{
	ifstream ifs(argFileName);
	string tmpLine;
	vector<string> buffer(1);
	int result;

	if(ifs.fail()) return false;

	while(getline(ifs, tmpLine)) {
		buffer.push_back(tmpLine);
	}

	ifs.close();

	init();

	for(_st i = 0; i < buffer.size(); i++) {
		if(buffer[i].find("HIERARCHY") != string::npos) {
			result = ReadHierarchy(&buffer, int(i));
			if(result < 1) {
				init();
				return false;
			}
			i += _st(result);
		}
		if(buffer[i].find("MOTION") != string::npos) {
			result = ReadMotion(&buffer, int(i));
			if(result < 1) {
				init();
				return false;
			}
			i += _st(result);
		}
	}
	return true;
}

int fk_BVHMotion::SetFrameFormat(vector<string> *argBuf, int argCurLine)
{
	string lineStr, word;
	string::size_type strPos;
	pair<_st, BVH_ChannelType> tmpFmt;
	_st curLine = _st(argCurLine);

	while(argBuf->size() > curLine) {
		curLine++;
		lineStr = argBuf->at(curLine);

		if((strPos = lineStr.find("CHANNELS")) != string::npos) {
			lineStr.erase(0, strPos + 9);
			word = PopWord(&lineStr);
			while(word.length() != 0) {
				if(word == "Xposition") {
					tmpFmt.first = _m->nodeArray.size() - 1;
					tmpFmt.second = BVH_ChannelType::XPOS;
					_m->frameFormat.push_back(tmpFmt);
				} else if(word == "Yposition") {
					tmpFmt.first = _m->nodeArray.size()-1;
					tmpFmt.second = BVH_ChannelType::YPOS;
					_m->frameFormat.push_back(tmpFmt);
				} else if(word == "Zposition") {
					tmpFmt.first = _m->nodeArray.size()-1;
					tmpFmt.second = BVH_ChannelType::ZPOS;
					_m->frameFormat.push_back(tmpFmt);
				} else if(word == "Xrotation") {
					tmpFmt.first = _m->nodeArray.size()-1;
					tmpFmt.second = BVH_ChannelType::XROT;
					_m->frameFormat.push_back(tmpFmt);
				} else if(word == "Yrotation") {
					tmpFmt.first = _m->nodeArray.size()-1;
					tmpFmt.second = BVH_ChannelType::YROT;
					_m->frameFormat.push_back(tmpFmt);
				} else if(word == "Zrotation") {
					tmpFmt.first = _m->nodeArray.size()-1;
					tmpFmt.second = BVH_ChannelType::ZROT;
					_m->frameFormat.push_back(tmpFmt);
				}

				word = PopWord(&lineStr);
			}
			break;
		}
	}

	return int(curLine);
}

int fk_BVHMotion::ReadHierarchy(vector<string> *argBuf, int argLine)
{
	_st curLine = _st(argLine);
	string::size_type strPos;
	stack<fk_Model *> hieStack;
	string lineStr;
	fk_Vector tmpVec;

	while(argBuf->size() > curLine) {
		// 1 行取得
		curLine++;
		lineStr = argBuf->at(curLine);

		if((strPos = lineStr.find("ROOT")) != string::npos) {
			// Model 生成とスタックに積む
			_m->nodeArray.push_back(make_unique<fk_Model>());
			_m->typeArray.push_back(BVH_NodeType::ROOT);
			hieStack.push(_m->nodeArray.back().get());
			// ROOT の後の名前を抽出
			lineStr.erase(0, strPos + 4);

			// 名前リストとマップに追加
			_m->nameArray.push_back(PopWord(&lineStr));
			_m->nameToNodeMap[_m->nameArray.back()] = _m->nodeArray.back().get();

			while(true) {
				curLine++;
				lineStr = argBuf->at(curLine);

				if((strPos = lineStr.find("OFFSET")) != string::npos) {
					lineStr.erase(0, strPos + 7);

					tmpVec.x = Str2Double(PopWord(&lineStr));
					tmpVec.y = Str2Double(PopWord(&lineStr));
					tmpVec.z = Str2Double(PopWord(&lineStr));
					_m->nodeArray.back()->glMoveTo(tmpVec);
					_m->offsetArray.push_back(tmpVec);

					curLine = _st(SetFrameFormat(argBuf, int(curLine)));
					break;
				}
			}
		} else if((strPos = lineStr.find("JOINT")) != string::npos) {
			_m->nodeArray.push_back(make_unique<fk_Model>());
			_m->nodeArray.back()->setParent(hieStack.top());
			_m->typeArray.push_back(BVH_NodeType::JOINT);
			hieStack.push(_m->nodeArray.back().get());

			lineStr.erase(0, strPos + 6);

			_m->nameArray.push_back(PopWord(&lineStr));
			_m->nameToNodeMap[_m->nameArray.back()] = _m->nodeArray.back().get();

			while(argBuf->size() > curLine) {
				curLine++;
				lineStr = argBuf->at(curLine);

				if((strPos = lineStr.find("OFFSET")) != string::npos) {
					lineStr.erase(0, strPos + 7);
					tmpVec.x = Str2Double(PopWord(&lineStr));
					tmpVec.y = Str2Double(PopWord(&lineStr));
					tmpVec.z = Str2Double(PopWord(&lineStr));
					_m->nodeArray.back()->glMoveTo(tmpVec);
					_m->offsetArray.push_back(tmpVec);

					curLine = _st(SetFrameFormat(argBuf, int(curLine)));
					break;
				}
			}
		} else if(argBuf->at(curLine).find("End") != string::npos) {
			_m->nodeArray.push_back(make_unique<fk_Model>());
			_m->nodeArray.back()->setParent(hieStack.top());
			_m->typeArray.push_back(BVH_NodeType::END);
			hieStack.push(_m->nodeArray.back().get());

			_m->nameArray.push_back("End Site");

			while(argBuf->size() > curLine) {
				curLine++;
				lineStr = argBuf->at(curLine);

				if((strPos = lineStr.find("OFFSET")) != string::npos) {
					lineStr.erase(0, strPos + 7);
					tmpVec.x = Str2Double(PopWord(&lineStr));
					tmpVec.y = Str2Double(PopWord(&lineStr));
					tmpVec.z = Str2Double(PopWord(&lineStr));
					_m->nodeArray.back()->glMoveTo(tmpVec);
					_m->offsetArray.push_back(tmpVec);

					break;
				}
			}

			while(argBuf->size() > curLine) {
				curLine++;
				lineStr = argBuf->at(curLine);

				if(lineStr.find("}") != string::npos) {
					hieStack.pop();
				} else {
					curLine--;
					break;
				}
			}
		} else if(argBuf->at(curLine).find("MOTION") != string::npos) {
			curLine--;
			break;
		}

	}

	return (int(curLine)-argLine);
}

int fk_BVHMotion::ReadMotion(vector<string> *argBuf, int argLine)
{
	_st curLine = _st(argLine);
	string::size_type strPos;
	string lineStr, word;
	vector<double> tmpArray;
	fk_Model tmpModel;
	fk_Angle tmpAngle;
	_st prevID;
	vector<fk_Axis> rotStack;
	fk_Vector tmpVec(0.0, 0.0, -1.0);
	fk_Vector tmpUpVec(0.0, 1.0, 0.0);
	fk_Matrix rotMat;

	while(argBuf->size() > curLine) {
		curLine++;
		lineStr = argBuf->at(curLine);
		if((strPos = lineStr.find("Frames")) != string::npos) {
			lineStr.erase(0, strPos + 6);
			ReplaceString(&lineStr, ":", " ");
			_m->length = Str2Int(lineStr);
			break;
		}
	}
	while(argBuf->size() > curLine) {
		curLine++;
		lineStr = argBuf->at(curLine);
		if((strPos = lineStr.find("Frame Time")) != string::npos) {
			lineStr.erase(0, strPos + 10);
			ReplaceString(&lineStr, ":", " ");
			_m->oneFrameTime = Str2Double(lineStr);
			break;
		}
	}

	_m->posArray.resize(_st(getNodeNum()));
	_m->rotArray.resize(_st(getNodeNum()));
	for(_st i = 0; i < _st(getNodeNum()); i++) {
		_m->posArray[i].resize(_st(_m->length));
		_m->rotArray[i].resize(_st(_m->length));
	}

	for(_st j = 0; j < _st(_m->length); j++) {
		// 1 行取得
		curLine++;
		lineStr = argBuf->at(curLine);
		tmpArray.clear();

		// 1 フレーム分のデータを配列に突っ込む
		word = PopWord(&lineStr);
		while(word.length() != 0) {
			tmpArray.push_back(Str2Double(word));
			word = PopWord(&lineStr);
		}
		// 各関節の位置と角度を初期化
		for(_st i = 0; i < _st(getNodeNum()); i++) {
			_m->posArray[i][j] = _m->offsetArray[i];
			_m->rotArray[i][j].set(0.0, 0.0, 0.0);
		}
		// 回転解釈変数初期化
		prevID = _m->frameFormat[0].first;
		tmpAngle.set(0.0, 0.0, 0.0);
		rotStack.clear();

		// フレームデータ解釈開始
		for(_st i = 0; i < _m->frameFormat.size(); i++) {
			// 次の関節の情報に移ったらオイラー角を生成
			if(prevID != _m->frameFormat[i].first) {
				// BVH での記述と逆順になる(角度反転無し)
				tmpVec.set(0.0, 0.0, -1.0);
				tmpUpVec.set(0.0, 1.0, 0.0);
				for(int k = int(rotStack.size())-1; k >= 0; k--) {
					switch(rotStack[_st(k)]) {
					  case fk_Axis::X:
						rotMat.makeRot(tmpAngle.p, fk_Axis::X);
						tmpVec *= rotMat;
						tmpUpVec *= rotMat;
						break;
					  case fk_Axis::Y:
						rotMat.makeRot(tmpAngle.h, fk_Axis::Y);
						tmpVec *= rotMat;
						tmpUpVec *= rotMat;
						break;
					  case fk_Axis::Z:
						rotMat.makeRot(tmpAngle.b, fk_Axis::Z);
						tmpVec *= rotMat;
						tmpUpVec *= rotMat;
						break;
					  default:
						break;
					}
				}
				// データへ反映
				tmpModel.glVec(tmpVec);
				tmpModel.glUpvec(tmpUpVec);
				_m->rotArray[_st(prevID)][j] = tmpModel.getAngle();
				// 回転解釈変数初期化
				prevID = _m->frameFormat[i].first;
				tmpAngle.set(0.0, 0.0, 0.0);
				rotStack.clear();
			}
			// 座標値はそのまま反映、回転角度は一時的に保存し後で反映
			switch(_m->frameFormat[i].second) {
			  case BVH_ChannelType::XPOS:
				_m->posArray[_st(_m->frameFormat[i].first)][j].x = tmpArray[i];
				break;
			  case BVH_ChannelType::YPOS:
				_m->posArray[_st(_m->frameFormat[i].first)][j].y = tmpArray[i];
				break;
			  case BVH_ChannelType::ZPOS:
				_m->posArray[_st(_m->frameFormat[i].first)][j].z = tmpArray[i];
				break;
			  case BVH_ChannelType::XROT:
				tmpAngle.p = tmpArray[i]*fk_Math::PI/180.0;
				rotStack.push_back(fk_Axis::X);
				break;
			  case BVH_ChannelType::YROT:
				tmpAngle.h = tmpArray[i]*fk_Math::PI/180.0;
				rotStack.push_back(fk_Axis::Y);
				break;
			  case BVH_ChannelType::ZROT:
				tmpAngle.b = tmpArray[i]*fk_Math::PI/180.0;
				rotStack.push_back(fk_Axis::Z);
				break;
			  default:
				break;
			}
		}

		// 最後の1つに対して角度を反映
		tmpVec.set(0.0, 0.0, -1.0);
		tmpUpVec.set(0.0, 1.0, 0.0);
		for(int k = int(rotStack.size())-1; k >= 0; k--) {
			switch(rotStack[_st(k)]) {
			  case fk_Axis::X:
				rotMat.makeRot(tmpAngle.p, fk_Axis::X);
				tmpVec *= rotMat;
				tmpUpVec *= rotMat;
				break;
			  case fk_Axis::Y:
				rotMat.makeRot(tmpAngle.h, fk_Axis::Y);
				tmpVec *= rotMat;
				tmpUpVec *= rotMat;
				break;
			  case fk_Axis::Z:
				rotMat.makeRot(tmpAngle.b, fk_Axis::Z);
				tmpVec *= rotMat;
				tmpUpVec *= rotMat;
				break;
			  default:
				break;
			}
		}
		tmpModel.glVec(tmpVec);
		tmpModel.glUpvec(tmpUpVec);
		_m->rotArray[_st(prevID)][j] = tmpModel.getAngle();
	}

	return (int(curLine)-argLine);
}

int fk_BVHMotion::getNodeNum(void)
{
	return int(_m->nodeArray.size());
}

string fk_BVHMotion::getNodeName(int argID)
{
	if(argID < 0 || _st(argID) >= _m->nameArray.size()) {
		return "";
	}
	return _m->nameArray[_st(argID)];
}

fk_Model * fk_BVHMotion::getNodeModel(int argID)
{
	if(argID < 0 || _st(argID) >= _m->nodeArray.size()) {
		return nullptr;
	}
	return _m->nodeArray[_st(argID)].get();
}

fk_Model * fk_BVHMotion::getNodeModel(string argName)
{
	if(_m->nameToNodeMap.find(argName) == _m->nameToNodeMap.end()) return nullptr;
	return _m->nameToNodeMap[argName];
}

int fk_BVHMotion::nextFrame(void)
{
	for(_st i = 0; i < _st(getNodeNum()); i++) {
		_m->nodeArray[i]->glMoveTo(_m->posArray[i][_st(_m->nowFrame)]);
		_m->nodeArray[i]->glAngle(_m->rotArray[i][_st(_m->nowFrame)]);
	}

	_m->nowFrame++;
	if(_m->nowFrame >= _m->length) _m->nowFrame = 0;

	return _m->nowFrame;
}

void fk_BVHMotion::setFrameCount(int argFrame)
{
	if(argFrame < 0) _m->nowFrame = 0;
	else if(argFrame >= _m->length) _m->nowFrame = _m->length-1;
	else _m->nowFrame = argFrame;

	for(_st i = 0; i < _st(getNodeNum()); i++) {
		_m->nodeArray[i]->glMoveTo(_m->posArray[i][_st(_m->nowFrame)]);
		_m->nodeArray[i]->glAngle(_m->rotArray[i][_st(_m->nowFrame)]);
	}

	return;
}

void fk_BVHMotion::setAnimationTime(double argT)
{
	setFrameCount(int((double)argT/_m->oneFrameTime));
	return;
}

int fk_BVHMotion::getNowFrameCount(void)
{
	return _m->nowFrame;
}

int fk_BVHMotion::getFrameLength(void)
{
	return _m->length;
}

double fk_BVHMotion::getOneFrameTime(void)
{
	return _m->oneFrameTime;
}

int fk_BVHMotion::getPosSize(int argID)
{
	return int(_m->posArray[_st(argID)].size());
}

int fk_BVHMotion::getRotSize(int argID)
{
	return int(_m->rotArray[_st(argID)].size());
}

fk_Vector fk_BVHMotion::getPos(int argI, int argJ)
{
	return _m->posArray[_st(argI)][_st(argJ)];
}

fk_Angle fk_BVHMotion::getRot(int argI, int argJ)
{
	return _m->rotArray[_st(argI)][_st(argJ)];
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
