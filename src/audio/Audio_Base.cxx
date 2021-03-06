﻿#include <FK/Audio.h>
#include <FK/Error.H>
#include <FK/Model.h>
#include <FK/Math.h>
#include <FK/Time.h>

#include <iostream>
#include <vector>

#include <vorbis/vorbisfile.h>

using namespace std;
using namespace FK;

unique_ptr<fk_IDAdmin> fk_AudioBase::admin = make_unique<fk_IDAdmin>(0);

bool fk_AudioBase::initStatus = false;
ALCcontext * fk_AudioBase::alContext = nullptr;
int fk_AudioBase::sourceNum = 0;
fk_Model * fk_AudioBase::listenerCamera = nullptr;

fk_AudioBase::Member::Member(void)
{
	queueSize = DEFAULT_QUEUE_SIZE;
	format = AL_FORMAT_STEREO16;
	rate = 0;
	source_id = -1;
	source = 99999;
	gain = 1.0;
	loopMode = false;
	loopStartTime = 0.0;
	loopEndTime = -1.0;
	refDist = 1.0;
	ref_model = nullptr;
}

bool fk_AudioBase::ALInit(void)
{
	ALCdevice *device = alcOpenDevice(nullptr);
	if(device == nullptr) {
		return false;
	}

	alContext = alcCreateContext(device, nullptr);

	if(alContext == nullptr) {
		alcCloseDevice (device);
		return false;
    }

	if(!alcMakeContextCurrent(alContext)) {
		alcDestroyContext(alContext);
		alcCloseDevice(device);
		return false;
	}

	return true;
}

bool fk_AudioBase::ALExit(void)
{
	if(!alcMakeContextCurrent(nullptr)) {
		return false;
	}

	ALCdevice *device = alcGetContextsDevice(alContext);
	alcDestroyContext(alContext);
	if(alcGetError(device) != ALC_NO_ERROR) {
		return false;
	}

	if(!alcCloseDevice(device)) {
		return false;
	}

	return true;
}

fk_AudioBase::fk_AudioBase(void)
{
	_m_AudioBase = make_unique<Member>();
	init();
	return;
}

fk_AudioBase::~fk_AudioBase()
{
	if(_m_AudioBase->source_id != -1) {
		admin.get()->EraseID(_m_AudioBase->source_id);
		sourceNum--;
	}
	if(sourceNum != 0) return;
	
	if(initStatus) {
		if(!ALExit()) {
			cerr << "ALExit() error." << endl;
		}
	}
}

bool fk_AudioBase::init(void)
{
	if(initStatus == false) {
		if(!ALInit()) {
			cerr << "ALInit() error." << endl;
			return false;
		}
	}
	initStatus = true;

	return true;
}

bool fk_AudioBase::getInit(void)
{
	return initStatus;
}

void fk_AudioBase::CreateID(void)
{
	_m_AudioBase->source_id = admin.get()->CreateID();
	sourceNum++;
	alGenSources(1, &(_m_AudioBase->source));
	alSourcef(_m_AudioBase->source, AL_GAIN, ALfloat(_m_AudioBase->gain));
	alSourcei(_m_AudioBase->source, AL_SOURCE_RELATIVE, AL_TRUE);
	return;
}

void fk_AudioBase::EraseID(void)
{
	admin.get()->EraseID(_m_AudioBase->source_id);
	_m_AudioBase->source_id = -1;
	if(sourceNum > 0) sourceNum--;
	return;
}

void fk_AudioBase::setGain(double argGain)
{
	if(argGain < -0.00001 || argGain > 1.00001) return;
	_m_AudioBase->gain = argGain;
	if(_m_AudioBase->source_id != -1) {
		alSourcef(_m_AudioBase->source, AL_GAIN, ALfloat(_m_AudioBase->gain));
	}
	return;
}

double fk_AudioBase::getGain(void)
{
	return _m_AudioBase->gain;
}


void fk_AudioBase::setQueueSize(int argSize)
{
	if(argSize < 1) return;
	_m_AudioBase->queueSize = (unsigned int)(argSize);
	return;
}

int fk_AudioBase::getQueueSize(void)
{
	return int(_m_AudioBase->queueSize);
}

void fk_AudioBase::setLoopMode(bool argMode)
{
	_m_AudioBase->loopMode = argMode;
	return;
}

bool fk_AudioBase::getLoopMode(void)
{
	return _m_AudioBase->loopMode;
}

void fk_AudioBase::setLoopArea(double argST, double argED)
{
	if(argST < -fk_Math::EPS || argST > argED) return;
	_m_AudioBase->loopStartTime = (argST < 0.0) ? 0.0 : argST;
	_m_AudioBase->loopEndTime = argED;
	_m_AudioBase->loopMode = true;

	return;
}

double fk_AudioBase::getLoopStartTime(void)
{
	return _m_AudioBase->loopStartTime;
}

double fk_AudioBase::getLoopEndTime(void)
{
	return _m_AudioBase->loopEndTime;
}

void fk_AudioBase::MakeOVInfo(OggVorbis_File *argVF)
{
	vorbis_info *info = ov_info(argVF, -1);

	if(info->channels == 1) {
		_m_AudioBase->format = AL_FORMAT_MONO16;
	} else {
		_m_AudioBase->format = AL_FORMAT_STEREO16;
	}
	_m_AudioBase->rate = static_cast<ALsizei>(info->rate);

	return;
}

void fk_AudioBase::sleep(double argTime)
{
	fk_Time::sleep(argTime);
	return;
}

void fk_AudioBase::pause(void)
{
	ALint status;

	if(_m_AudioBase->source_id == -1) return;
	alGetSourcei(_m_AudioBase->source, AL_SOURCE_STATE, &status);
	if(status == AL_PLAYING) {
		alSourcePause(_m_AudioBase->source);
	}
	return;
}

void fk_AudioBase::setListenerModel(fk_Model *argModel)
{
	listenerCamera = argModel;
}

void fk_AudioBase::setListenerModel(fk_Model &argModel)
{
	listenerCamera = &argModel;
}

fk_Model * fk_AudioBase::getListenerModel(void)
{
	return listenerCamera;
}

void fk_AudioBase::UpdateListener(void)
{
	static fk_Vector	camPos, camVec, camUpvec;
	static ALfloat		orient[6];

	if(listenerCamera != nullptr) {
		camPos = listenerCamera->getInhPosition();
		camVec = listenerCamera->getInhVec();
		camUpvec = listenerCamera->getInhUpvec();
		orient[0] = (float)camVec.x;	orient[1] = (float)camVec.y;	orient[2] = (float)camVec.z;
		orient[3] = (float)camUpvec.x;	orient[4] = (float)camUpvec.y;	orient[5] = (float)camUpvec.z;
		alListener3f(AL_POSITION, (float)camPos.x, (float)camPos.y, (float)camPos.z); 
		alListenerfv(AL_ORIENTATION, orient); 
	}

	return;
}

void fk_AudioBase::setPosition(const fk_Vector &argPos)
{
	_m_AudioBase->sourcePos = argPos;
	_m_AudioBase->surround = true;

	return;
}

void fk_AudioBase::setModel(fk_Model *argModel)
{
	_m_AudioBase->ref_model = argModel;
	if(argModel != nullptr) {
		_m_AudioBase->sourcePos = argModel->getInhPosition();
		_m_AudioBase->surround = true;
	}

	return;
}

void fk_AudioBase::setModel(fk_Model &argModel)
{
	setModel(&argModel);
}

void fk_AudioBase::setReferenceDist(double argDist)
{
	_m_AudioBase->refDist = argDist;
}

/*
  void fk_AudioBase::disableSurround(void)
  {
  ref_model = nullptr;
  sourcePos.init();
  refDist = 1.0;
  surround = false;

  return;
  }
*/

fk_Model * fk_AudioBase::getModel(void)
{
	return _m_AudioBase->ref_model;
}

fk_Vector fk_AudioBase::getPosition(void)
{
	return _m_AudioBase->sourcePos;
}

double fk_AudioBase::getReferenceDist(void)
{
	return _m_AudioBase->refDist;
}

void fk_AudioBase::setSurroundMode(bool argMode)
{
	_m_AudioBase->surround = argMode;
	return;
}

bool fk_AudioBase::getSurroundMode(void)
{
	return _m_AudioBase->surround;
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
