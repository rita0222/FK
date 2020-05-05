#include <FK/FrameController.h>
#include <FK/Time.h>
#include <FK/Error.H>
#include <FK/Window.h>

using namespace FK;
using namespace std;

fk_FrameController::Member::Member(bool argFrameSkip) :
	nowTime(0.0), lastMinitues(0.0), frameRate(0), skipRate(0),
	frameTime(0.0), drawFlag(false), frameSkip(argFrameSkip),
	init(true), frameCount(0), skipCount(0)
{
	return;
}
	

//======================================================
//コンストラクタ
//======================================================
fk_FrameController::fk_FrameController(int argFPS, bool argFrameSkip) :
	_m(make_unique<Member>(argFrameSkip))
{
	setFPS(argFPS);
}

//======================================================
//デストラクタ
//======================================================
fk_FrameController::~fk_FrameController()
{
}

void fk_FrameController::SleepOneMSec(void)
{
	fk_Time::sleep(0.0001);
	return;
}

//======================================================
//ここで時間制御をします。
//======================================================
void fk_FrameController::timeRegular()
{
	_m->frameCount++;
	_m->nowTime = fk_Time::now();

	if(_m->init == true) {
		_m->lastMinitues = _m->nowTime;
		_m->init = false;
		_m->drawFlag = true;
		return;
	}

	double tmpTime = (double(_m->frameCount) + 1.0) * _m->frameTime;
	if(_m->frameSkip == true && _m->nowTime > tmpTime + _m->lastMinitues) {
		_m->drawFlag = false;
		_m->skipCount++;
	} else {
		tmpTime = double(_m->frameCount) * _m->frameTime;
		double dwTime = tmpTime + _m->lastMinitues;
		while(fk_Time::now() < dwTime) {
			SleepOneMSec();
		}
		_m->drawFlag = true;
	}

	double nowTime_ = fk_Time::now();
	if(nowTime_ - _m->lastMinitues >= 1.0) {
		_m->lastMinitues = nowTime_;
		_m->frameRate = _m->frameCount;
		_m->frameCount = 0;
		_m->skipRate = _m->skipCount;
		_m->skipCount = 0;
	}
}

//======================================================
//フレームスキップをするかしないかを設定します。
//======================================================
void fk_FrameController::setFrameSkipMode(bool argFrameSkip)
{
	_m->frameSkip = argFrameSkip;
}

//======================================================
//ここでFPSを設定する。
//======================================================
void fk_FrameController::setFPS(int fps)
{
	_m->frameTime = 1.0 / double(fps);
}


//======================================================
//ここでフレームレートを取得します。
//======================================================
unsigned long fk_FrameController::getFrameRate()
{
	return _m->frameRate;
}

//======================================================
//ここでスキップレートを取得します。
//======================================================
unsigned long fk_FrameController::getSkipRate()
{
	return _m->skipRate;
}

//======================================================
//描画するかしないかを判定
//======================================================
bool fk_FrameController::getDrawFlag()
{
	return _m->drawFlag;
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
