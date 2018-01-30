/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
#include <FK/MotionData.H>

using namespace std;
using namespace FK;

typedef string::size_type	st;

fk_PerformerMotion::fk_PerformerMotion()
{
	init();

	return;
}
fk_PerformerMotion::~fk_PerformerMotion()
{
	init();
}

void fk_PerformerMotion::init(void)
{
	qArray.clear();
	frameArray.clear();
	interTypeArray.clear();
	basePosArray.clear();
	scaleArray.clear();

	return;
}

fk_Vector fk_PerformerMotion::getInterVec(const fk_Vector &vecA, const fk_Vector &vecB, double t, fk_MotionInterType argType)
{
	if(vecA == vecB) return vecA;

	switch(argType) {
	case LINEAR:
		return (1.0-t)*vecA + t*vecB;
	case SPHERE:
		return pow(cos(t*FK_PI/2.0), 2)*vecA + pow(sin(t*FK_PI/2.0), 2)*vecB;
	case POWER:
		return (1.0-pow(t, 3))*vecA + pow(t, 3)*vecB;
	case REV_POWER:
		return pow(1.0-t, 3)*vecA + (1.0-pow(1.0-t, 3))*vecB;
	case FREEZE:
	case HIDE:		// <----------------------------------------------------オブジェクトのすげ替え対応のため追加
		return vecB;
	default:
		break;
	}

	return fk_Vector();
}

fk_Quaternion fk_PerformerMotion::getInterQ(const fk_Quaternion &qA, const fk_Quaternion &qB, double t, fk_MotionInterType argType)
{
	if(qA == qB) return qA;

	switch(argType) {
	case LINEAR:
	case SPHERE:
		return fk_Math::quatInterSphere(qA, qB, t);
	case POWER:
		return fk_Math::quatInterSphere(qA, qB, pow(t, 3));
	case REV_POWER:
		return fk_Math::quatInterSphere(qA, qB, (1.0-pow(1.0-t, 3)));
	case FREEZE:
	case HIDE:		// <----------------------------------------------------オブジェクトのすげ替え対応のため追加
		return qB;
	default:
		return fk_Quaternion();
	}
}

// スケールなし
void fk_PerformerMotion::pushKeyFrame(const fk_Quaternion &argQ, const fk_Vector &argBasePos, int argFrame, fk_MotionInterType argType, int argKeyPos)
{
	pushKeyFrame(argQ, argBasePos, fk_Vector(1.0, 1.0, 1.0), argFrame, argType, argKeyPos);
}
bool fk_PerformerMotion::changeKeyFrame(int argKeyID, const fk_Quaternion &argQ, const fk_Vector &argBasePos, int argFrame, fk_MotionInterType argType)
{
	return changeKeyFrame(argKeyID, argQ, argBasePos, fk_Vector(1.0, 1.0, 1.0), argFrame, argType);
}
// スケールあり
void fk_PerformerMotion::pushKeyFrame(const fk_Quaternion &argQ, const fk_Vector &argBasePos, const fk_Vector &argScale,
								   int argFrame, fk_MotionInterType argType, int argKeyPos)
{
	if(argKeyPos == -1) {
		qArray.push_back(argQ);
		frameArray.push_back(argFrame);
		interTypeArray.push_back(argType);
		basePosArray.push_back(argBasePos);
		scaleArray.push_back(argScale);
	} else if(argKeyPos < (int)qArray.size()){
		qArray.insert(qArray.begin()+argKeyPos, argQ);
		frameArray.insert(frameArray.begin()+argKeyPos, argFrame);
		interTypeArray.insert(interTypeArray.begin()+argKeyPos, argType);
		basePosArray.insert(basePosArray.begin()+argKeyPos, argBasePos);
		scaleArray.insert(scaleArray.begin()+argKeyPos, argScale);
	}
	return;
}
bool fk_PerformerMotion::changeKeyFrame(int argKeyID, const fk_Quaternion &argQ, const fk_Vector &argBasePos, const fk_Vector &argScale,
									 int argFrame, fk_MotionInterType argType)
{
	if(argKeyID >= getTotalKeyNum()) return false;

	st keyID = st(argKeyID);

	qArray[keyID] = argQ;
	frameArray[keyID] = argFrame;
	interTypeArray[keyID] = argType;
	basePosArray[keyID] = argBasePos;
	scaleArray[keyID] = argScale;

	return true;
}

bool fk_PerformerMotion::deleteKeyFrame(int argKeyID)
{
	if(argKeyID >= getTotalKeyNum()) return false;

	qArray.erase(qArray.begin()+argKeyID);
	frameArray.erase(frameArray.begin()+argKeyID);
	interTypeArray.erase(interTypeArray.begin()+argKeyID);

	if(isBaseMotion()) basePosArray.erase(basePosArray.begin()+argKeyID);
	scaleArray.erase(scaleArray.begin()+argKeyID);

	return true;
}

bool fk_PerformerMotion::isBaseMotion(void)
{
	if(basePosArray.size() != 0) return true;
	else return false;
}
int fk_PerformerMotion::getTotalKeyNum(void)
{
	return (int)qArray.size();
}

int fk_PerformerMotion::getTotalFrameNum(int argKeyID)
{
	int retVal = 0;

	if(argKeyID != -1) {
		for(st i = 0; i <= st(argKeyID); i++) {
			retVal += frameArray[i];
		}
	} else {
		for(st i = 0; i < st(getTotalKeyNum()); i++) {
			retVal += frameArray[i];
		}
	}

	return retVal;
}
bool fk_PerformerMotion::getFrameToKeyID(int argFrame, int *outID, int *outFrame)
{
	if(argFrame >= getTotalFrameNum()) return false;
	if(getTotalFrameNum() == 0) return false;

	int	nowKey = 0, nowFrame = 0;
	for(st i = 0; i < st(getTotalKeyNum()); i++) {
		nowKey = int(i);
		nowFrame += frameArray[i];
		if(argFrame < nowFrame) break;
	}

	*outID = nowKey;
	*outFrame = argFrame-(nowFrame-frameArray[st(nowKey)]);

	return true;
}

int fk_PerformerMotion::setFrameState(int argFrame, fk_Model *argModel)
{
	static st				nowKey = 0;
	static int				stepFrame = 0;
	static int				tmpKey = 0;
	static fk_Quaternion	q;
	static fk_Vector		sc;
	const fk_Vector			dirV(0.0, 0.0, -1.0);
	const fk_Vector			upV(0.0, 1.0, 0.0);
	
	if(!getFrameToKeyID(argFrame, &tmpKey, &stepFrame)) return 0;
	nowKey = st(tmpKey);

	if(nowKey != 0 && stepFrame == 0) {
		argModel->glVec(qArray[nowKey-1]*dirV);
		argModel->glUpvec(qArray[nowKey-1]*upV);
		if(isBaseMotion()) {
			argModel->glMoveTo(basePosArray[nowKey-1]);//-basePosArray[0]);
		}
		argModel->setScale(scaleArray[nowKey-1].x, scaleArray[nowKey-1].y, scaleArray[nowKey-1].z);
	} else if(nowKey != 0) {
       	q = getInterQ(qArray[nowKey-1], qArray[nowKey], (double)(stepFrame+1)/(double)frameArray[nowKey], interTypeArray[nowKey]);
		argModel->glVec(q*dirV);
		argModel->glUpvec(q*upV);
		if(isBaseMotion()) {
			argModel->glMoveTo(getInterVec(basePosArray[nowKey-1], basePosArray[nowKey],
				(double)(stepFrame+1)/(double)frameArray[nowKey], interTypeArray[nowKey]));//-basePosArray[0]);
		}
		sc = getInterVec(scaleArray[nowKey-1], scaleArray[nowKey], (double)(stepFrame)/(double)frameArray[nowKey], interTypeArray[nowKey]);
		argModel->setScale(sc.x, sc.y, sc.z);
	} else {
		static fk_Quaternion	nowQ;
		static fk_Vector		nowSc;
		nowQ.makeEuler(argModel->getAngle());
		nowSc.set(argModel->getScale(fk_X), argModel->getScale(fk_Y), argModel->getScale(fk_Z));

       	q = getInterQ(nowQ, qArray[nowKey], (double)(stepFrame+1)/(double)frameArray[nowKey]);
		argModel->glVec(q*dirV);
		argModel->glUpvec(q*upV);
		if(isBaseMotion()) {
			argModel->glMoveTo(getInterVec(argModel->getPosition(), basePosArray[nowKey],
				(double)(stepFrame+1)/(double)frameArray[nowKey]));//-basePosArray[0]);
		}
		sc = getInterVec(nowSc, scaleArray[nowKey], (double)(stepFrame)/(double)frameArray[nowKey], interTypeArray[nowKey]);
		argModel->setScale(sc.x, sc.y, sc.z);
	}

	if(interTypeArray[nowKey] == HIDE) {
		return -1;
	}

	return 1;
}
