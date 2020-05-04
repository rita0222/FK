#include <FK/Audio.h>
#include <FK/Error.H>

#include <iostream>
#include <vector>

#include <vorbis/vorbisfile.h>
#include <AL/al.h>
#include <AL/alc.h>

#ifdef __BIG_ENDIAN__
const int _ENDIAN = 1;
#else
const int _ENDIAN = 0;
#endif

using namespace std;
using namespace FK;

fk_AudioStream::Member::Member(void) :
	ovOpenStatus(false),
	current(0),
	buffer(fk_AudioBase::BUFSIZE, char(0)),
	nowTime(0.0),
	vf(make_unique<OggVorbis_File>())
{
}

fk_AudioStream::fk_AudioStream(void)
{
	_m = make_unique<Member>();
	_m_AudioBase->startStatus = _m_AudioBase->endStatus = false;
	return;
}

fk_AudioStream::~fk_AudioStream()
{
	end();
}

bool fk_AudioStream::open(const std::string &argFileName)
{
	if(getInit() == false) init();
	if(_m->ovOpenStatus == true) ov_clear(_m->vf.get());

	int ovStatus;
	if((ovStatus = ov_fopen(argFileName.c_str(), _m->vf.get())) < 0) {
		switch(ovStatus) {
		  case OV_EREAD:
			Error::Put("fk_AudioStream", "open", 1, "Read Error");
			break;

		  case OV_ENOTVORBIS:
			Error::Put("fk_AudioStream", "open", 1, "Not Vorbis Error");
			break;

		  case OV_EVERSION:
			Error::Put("fk_AudioStream", "open", 1, "Version Error");
			break;

		  case OV_EBADHEADER:
			Error::Put("fk_AudioStream", "open", 1, "Header Error");
			break;

		  case OV_EFAULT:
			Error::Put("fk_AudioStream", "open", 1, "Fault Error");
			break;

		  default:
			Error::Put("fk_AudioStream", "open", 1, "Undefined Error");
			break;
		}

		return false;
	}
	_m->ovOpenStatus = true;
	_m_AudioBase->startStatus = _m_AudioBase->endStatus = false;
	return true;
}

bool fk_AudioStream::ready(void)
{
	if(_m->ovOpenStatus == false) return false;
	if(_m_AudioBase->startStatus == false) StartQueue(true);
	return true;
}

bool fk_AudioStream::play(void)
{
	if(_m->ovOpenStatus == false) return false;
	if(_m_AudioBase->startStatus == false) {
		if(ready() == false) return false;
	}
	
	return PlayStream();
}

void fk_AudioStream::StartQueue(bool argInitFlg)
{
	_m_AudioBase->startStatus = true;

	if(argInitFlg == true) {
		_m->current = 0;
		CreateID();
	}

	UnQueue(true);

	for(unsigned int i = 0; i < _m_AudioBase->queueSize; ++i) {

		ALsizei size = ALsizei(ov_read(_m->vf.get(), _m->buffer.data(),
									   int(fk_AudioBase::BUFSIZE*sizeof(char)),
									   _ENDIAN, 2, 1, &_m->current));

		if(size <= 0) {
			_m_AudioBase->endStatus = true;
			break;
		}

		if(i == 0) MakeOVInfo(_m->vf.get());

		ALuint bufferID;
		alGenBuffers(1, &bufferID);
		alBufferData(bufferID, _m_AudioBase->format, _m->buffer.data(), size, _m_AudioBase->rate);
		alSourceQueueBuffers(_m_AudioBase->source, 1, &bufferID);
	}

	return;
}

void fk_AudioStream::UnQueue(bool argBufferFlg)
{
	ALint queueNum;
	alGetSourcei(_m_AudioBase->source, AL_BUFFERS_QUEUED, &queueNum);

	for(ALint i = 0; i < queueNum; ++i) {
		ALuint bufferID;
		alSourceUnqueueBuffers(_m_AudioBase->source, 1, &bufferID);
		if(argBufferFlg == true) {
			alDeleteBuffers(1, &bufferID);
		}
	}
	return;
}

bool fk_AudioStream::PlayStream(void)
{
	ALint status;
	alGetSourcei(_m_AudioBase->source, AL_SOURCE_STATE, &status);
	
	// 再生していなければ、再生命令を出す
	if(status != AL_PLAYING) {
		alSourcePlay(_m_AudioBase->source);
		sleep(0.001);
	}

	// 再生済みバッファの個数を取得
	ALint procNum;
	alGetSourcei(_m_AudioBase->source, AL_BUFFERS_PROCESSED, &procNum);

	for(ALint i = 0; i < procNum; ++i) {
		ALuint bufferID;
		alSourceUnqueueBuffers(_m_AudioBase->source, 1, &bufferID);

		// 既にファイルを読み終えてる場合、バッファを消去
		if(_m_AudioBase->endStatus == true) {
			alDeleteBuffers(1, &bufferID);
			continue;
		}

		ogg_int64_t length = ogg_int64_t(fk_AudioBase::BUFSIZE*sizeof(char));
		_m->nowTime = ov_time_tell(_m->vf.get());
		bool need_rewind = false;
		if (_m_AudioBase->loopMode && _m_AudioBase->loopEndTime > 0.0)
		{
			ogg_int64_t now_pcm = ov_pcm_tell(_m->vf.get());
			ov_time_seek(_m->vf.get(), _m_AudioBase->loopEndTime);
			ogg_int64_t end_pcm = ov_pcm_tell(_m->vf.get());
			ov_pcm_seek(_m->vf.get(), now_pcm);
			if (now_pcm > end_pcm)
			{
				length = 0;
				need_rewind = true;
			}
			else if (length > end_pcm - now_pcm)
			{
				length = static_cast<int>(end_pcm - now_pcm);
				need_rewind = true;
			}
		}

		// ファイル読み込み
		ALsizei size = ALsizei(ov_read(_m->vf.get(), _m->buffer.data(),
									   int(length), _ENDIAN, 2, 1, &_m->current));
		if (need_rewind)
		{
			ov_time_seek_lap(_m->vf.get(), _m_AudioBase->loopStartTime);
		}

		if(size == 0)
		{
			// 終端
			if (!_m_AudioBase->loopMode)
			{
				_m_AudioBase->endStatus = true;
				alDeleteBuffers(1, &bufferID);
			}
			else
			{
				ov_time_seek(_m->vf.get(), _m_AudioBase->loopStartTime);
			}

			continue;
		}

		alBufferData(bufferID, _m_AudioBase->format, _m->buffer.data(), size, _m_AudioBase->rate);
		alSourceQueueBuffers(_m_AudioBase->source, 1, &bufferID);
	}

	// 終了判定
	if(status != AL_PLAYING && _m_AudioBase->endStatus == true) return false;
	return true;
}

void fk_AudioStream::stop(void)
{
	if(_m_AudioBase->startStatus == false) return;

	ALint status;
	alGetSourcei(_m_AudioBase->source, AL_SOURCE_STATE, &status);

	if(status != AL_STOPPED) {
		alSourceStop(_m_AudioBase->source);
	}

	ALint procNum;
	alGetSourcei(_m_AudioBase->source, AL_BUFFERS_PROCESSED, &procNum);
	for(ALint i = 0; i < procNum; ++i) {
		ALuint bufferID;
		alSourceUnqueueBuffers(_m_AudioBase->source, 1, &bufferID);
		alDeleteBuffers(1, &bufferID);
	}
}

void fk_AudioStream::end(void)
{
	if(_m->ovOpenStatus == false) return;

	stop();

	if(_m_AudioBase->startStatus == true) alDeleteSources(1, &_m_AudioBase->source);
	_m_AudioBase->startStatus = _m_AudioBase->endStatus = false;
	EraseID();
	ov_clear(_m->vf.get());
	_m->ovOpenStatus = false;

	return;
}	

double fk_AudioStream::tell(void)
{
	if(_m_AudioBase->startStatus == false) return -1.0;

	ALfloat bufTell;
	ALint queueNum;
	alGetSourcei(_m_AudioBase->source, AL_BUFFERS_QUEUED, &queueNum);
	alGetSourcef(_m_AudioBase->source, AL_SEC_OFFSET, &bufTell);
	return _m->nowTime + (double)bufTell;
}

void fk_AudioStream::seek(double argTime)
{
	if(_m->ovOpenStatus == false) return;

	stop();
	ov_time_seek_lap(_m->vf.get(), argTime);
	_m_AudioBase->endStatus = false;
	StartQueue(!_m_AudioBase->startStatus);

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
