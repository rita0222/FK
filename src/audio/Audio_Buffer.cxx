#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <FK/Audio.h>
#include <FK/Error.H>
#include <FK/Model.h>

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

fk_AudioOggBuffer::fk_AudioOggBuffer(void)
{
	buffer.clear();
	chunkTime.clear();
	chunkSize.clear();
	length = current = 0;
	startStatus = endStatus = surround = false;
	refDist = 1.0;
	ref_model = nullptr;
	return;
}

fk_AudioOggBuffer::~fk_AudioOggBuffer()
{
	return;
}

bool fk_AudioOggBuffer::open(const std::string &argFileName)
{
	int				ovStatus;
	OggVorbis_File	vf;

	if(getInit() == false) init();

	if((ovStatus = ov_fopen((char *)&argFileName[0], &vf)) < 0) {
		switch(ovStatus) {
		  case OV_EREAD:
			Error::Put("fk_AudioOggBuffer", "open", 1, "Read Error");
			break;

		  case OV_ENOTVORBIS:
			Error::Put("fk_AudioOggBuffer", "open", 1, "Not Vorbis Error");
			break;

		  case OV_EVERSION:
			Error::Put("fk_AudioOggBuffer", "open", 1, "Version Error");
			break;

		  case OV_EBADHEADER:
			Error::Put("fk_AudioOggBuffer", "open", 1, "Header Error");
			break;

		  case OV_EFAULT:
			Error::Put("fk_AudioOggBuffer", "open", 1, "Fault Error");
			break;

		  default:
			Error::Put("fk_AudioOggBuffer", "open", 1, "Undefined Error");
			break;
		}

		return false;
	}

	ReadBuffer(&vf);
	ov_clear(&vf);

	startStatus = endStatus = false;
	return true;
}

void fk_AudioOggBuffer::ReadBuffer(OggVorbis_File *argVF)
{
	ALsizei			size = 1;
	unsigned int	count = 0;
	int				tmpCurrent = 0;

	buffer.clear();
	chunkTime.clear();
	chunkSize.clear();
	length = 0;

	for(count = 0;; count++) {
		buffer.resize((count+1)*fk_AudioBase::BUFSIZE);
		chunkTime.push_back(ov_time_tell(argVF));
		size = static_cast<ALsizei>(ov_read(argVF, &buffer[count*fk_AudioBase::BUFSIZE],
											static_cast<int>(fk_AudioBase::BUFSIZE * sizeof(char)),
											_ENDIAN, 2, 1, &tmpCurrent));

		if(size <= 0) break;
		chunkSize.push_back(size);
		length++;
		if(count == 0) MakeOVInfo(argVF);
	}
	buffer.resize(count * fk_AudioBase::BUFSIZE);
	chunkTime.resize(count);

	return;
}

fk_AudioWavBuffer::fk_AudioWavBuffer(void) : fk_AudioOggBuffer()
{
	return;
}

fk_AudioWavBuffer::~fk_AudioWavBuffer()
{
	return;
}

int fk_AudioWavBuffer::ReadHeaderWav(ifstream &argIFS, int *channel, int *bit,
									 unsigned int *size, int *freq)
{
	short			res16;
	int				res32;
	unsigned int	dataSize, tmpChunkSize;
	short			channelCnt, bitParSample, blockSize;
	int				samplingRate, byteParSec;
	long			dataPos = -1;
	int				flag = 0;
	
	argIFS.read((char *)(&res32), 4);
	if(res32 != 0x46464952) {	//"RIFF"
		return 1;	//error 1
	}

	//データサイズ = ファイルサイズ - 8 byte の取得
	argIFS.read((char *)(&dataSize), 4);
	
	//WAVEヘッダーの読み
	argIFS.read((char *)(&res32), 4);
	if(res32 != 0x45564157) {	//"WAVE"
		return 2;	//error 2
	}

	while(flag != 3) {
		//チャンクの読み
		argIFS.read((char *)(&res32), 4);
		argIFS.read((char *)(&tmpChunkSize), 4);
		
		switch(res32) {
		  case 0x20746d66:	//"fmt "
			//format 読み込み
			//PCM種類の取得
			argIFS.read((char *)(&res16), 2);
			if(res16 != 1) {
				//非対応フォーマット
				return 4;
			}
			//モノラル(1)orステレオ(2)
			argIFS.read((char *)(&channelCnt), 2);
			if(res16 > 2) {
				//チャンネル数間違い
				return 5;
			}
			//サンプリングレート
			argIFS.read((char *)(&samplingRate), 4);
			//データ速度(byte/sec)=サンプリングレート*ブロックサイズ
			argIFS.read((char *)(&byteParSec), 4);
			//ブロックサイズ(byte/sample)=チャンネル数*サンプルあたりのバイト数
			argIFS.read((char *)(&blockSize), 2);
			//サンプルあたりのbit数(bit/sample)：8 or 16
			argIFS.read((char *)(&bitParSample), 2);
			
			*channel = static_cast<int>(channelCnt);
			*bit = static_cast<int>(bitParSample);
			*freq = samplingRate;

			flag += 1;
				
			break;
		case 0x61746164:	//"data"

			*size = tmpChunkSize;
			dataPos = static_cast<long>(argIFS.tellg());

			flag += 2;
			break;
		}

	}
	
	//頭出し("fmt "が"data"より後にあった場合のみ動く)
	if(dataPos != argIFS.tellg()) {
		argIFS.seekg(dataPos);
	}

	return 0;
}

bool fk_AudioWavBuffer::open(const std::string &argFileName)
{
	bool			res;
	int				bit, channel, freq;
	unsigned int	size;
	ifstream		ifs(argFileName, ios::binary);

	if(getInit() == false) init();

	if(ifs.fail()) return false;

	freq = channel = bit = 0;
	size = 0;

	if(ReadHeaderWav(ifs, &channel, &bit, &size, &freq) != 0) {
		ifs.close();
		return false;
	}

	res = ReadBuffer(ifs, channel, bit, size, freq);
	ifs.close();

	startStatus = endStatus = false;
	return res;
}

bool fk_AudioWavBuffer::ReadBuffer(ifstream &argIFS, int argCh, int argBit,
								   unsigned int argSize, int argFreq)
{
	unsigned int	count = 0;
	ALsizei			adjust = 0;
	long			bytePerSec = 0;

	if(argCh == 2) {
		if(argBit == 16) {
			format = AL_FORMAT_STEREO16;
		} else {
			format = AL_FORMAT_STEREO8;
		}
	} else {
		if(argBit == 16) {
			format = AL_FORMAT_MONO16;
		} else {
			format = AL_FORMAT_MONO8;
		}
	}
	rate = argFreq;
	
	bytePerSec = rate;
	switch(format) {
	case AL_FORMAT_MONO8:
		bytePerSec *= 1;
		break;
	case AL_FORMAT_MONO16:
	case AL_FORMAT_STEREO8:
		bytePerSec *= 2;
		break;
	case AL_FORMAT_STEREO16:
		bytePerSec *= 4;
		break;
	}

	buffer.clear();
	chunkTime.clear();
	chunkSize.clear();
	length = 0;

	count = static_cast<unsigned int>(argSize / fk_AudioBase::BUFSIZE);
	adjust = static_cast<ALsizei>(argSize % fk_AudioBase::BUFSIZE);

	buffer.resize(argSize);
	argIFS.read((char *)(&buffer[0]), sizeof(char) * argSize);
	if(argIFS.bad()) {
		Error::Put("fk_AudioWavBuffer", "ReadBuffer", 1, "Read Error");
		buffer.clear();
		rate = 0;
		return false;
	}

	for(unsigned int i = 0; i < count; i++) {
		chunkTime.push_back(double(i*fk_AudioBase::BUFSIZE)/(double)bytePerSec);
		chunkSize.push_back(fk_AudioBase::BUFSIZE);
		length++;
	}

	if(adjust != 0) {
		chunkTime.push_back(double(count*fk_AudioBase::BUFSIZE)/(double)bytePerSec);
		chunkSize.push_back(adjust);
		length++;
	}

	return true;
}

bool fk_AudioOggBuffer::ready(void)
{
	current = 0;
	if(startStatus == false) StartQueue(true);
	return true;
}

bool fk_AudioOggBuffer::play(void)
{
	if(startStatus == false) {
		if(ready() == false) return false;
	}

	if(PlayBuffer() == true) return true;
	else if(endStatus & loopMode) {
		seek(loopStartTime);
		return PlayBuffer();
	}

	return false;
}

void fk_AudioOggBuffer::StartQueue(bool argInitFlg)
{
	ALuint			bufferID;

	startStatus = true;

	if(argInitFlg == true) {
		CreateID();
	}

	UnQueue(true);

	for(unsigned int i = 0; i < queueSize && current < length; i++) {
		alGenBuffers(1, &bufferID);
		alBufferData(bufferID, format,
					 &buffer[current*fk_AudioBase::BUFSIZE],
					 ALsizei(chunkSize[current]),
					 static_cast<ALsizei>(rate));
		alSourceQueueBuffers(source, 1, &bufferID);
		current++;
	}

	return;
}

void fk_AudioOggBuffer::UnQueue(bool argBufferFlg)
{
	ALint		queueNum;
	ALuint		bufferID;
	int			i;

	alGetSourcei(source, AL_BUFFERS_QUEUED, &queueNum);
	for(i = 0; i < queueNum; i++) {
		alSourceUnqueueBuffers(source, 1, &bufferID);
		if(argBufferFlg == true) {
			alDeleteBuffers(1, &bufferID);
		}
	}
	return;
}

bool fk_AudioOggBuffer::PlayBuffer(void)
{
	ALint			status, i, procNum;
	ALuint			bufferID;

	bufferID = 0;
	procNum = 0;

	if(surround == true) {
		alSourcei(source, AL_SOURCE_RELATIVE, AL_FALSE);
		if(ref_model != nullptr) {
			sourcePos = ref_model->getInhPosition();
		}
		alSource3f(source, AL_POSITION, (float)sourcePos.x, (float)sourcePos.y, (float)sourcePos.z);
		alSourcef(source, AL_REFERENCE_DISTANCE, (float)refDist);
		UpdateListener();
	} else {
		alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
	}

	alGetSourcei(source, AL_SOURCE_STATE, &status);
	
	// 再生していなければ、再生命令を出す
	if(status != AL_PLAYING) {
		alSourcePlay(source);
		sleep(0.001);
	}

	// 再生済みバッファの個数を取得
	alGetSourcei(source, AL_BUFFERS_PROCESSED, &procNum);

	for(i = 0; i < procNum; i++) {
		alSourceUnqueueBuffers(source, 1, &bufferID);

		// 既にファイルを読み終えてる場合、バッファを消去
		if(endStatus == true) {
			alDeleteBuffers(1, &bufferID);
			continue;
		}

		if(current >= length) {
			// 終端
			endStatus = true;
			alDeleteBuffers(1, &bufferID);
			continue;
		}

		alBufferData(bufferID, format,
					 &buffer[current*fk_AudioBase::BUFSIZE],
					 chunkSize[current], rate);
		alSourceQueueBuffers(source, 1, &bufferID);
		current++;
	}

	// 終了判定
	if(status != AL_PLAYING && endStatus == true) return false;
	return true;
}

void fk_AudioOggBuffer::stop(void)
{
	ALint		status, procNum, i;
	ALuint		bufferID;

	if(startStatus == false) return;
	alGetSourcei(source, AL_SOURCE_STATE, &status);
	if(status != AL_STOPPED) {
		alSourceStop(source);
	}
	alGetSourcei(source, AL_BUFFERS_PROCESSED, &procNum);
	for(i = 0; i < procNum; i++) {
		alSourceUnqueueBuffers(source, 1, &bufferID);
		alDeleteBuffers(1, &bufferID);
	}
	return;
}

void fk_AudioOggBuffer::end(void)
{
	stop();
	if(startStatus == true) alDeleteSources(1, &source);
	startStatus = endStatus = false;
	EraseID();
	return;
}	

double fk_AudioOggBuffer::tell(void)
{
	ALfloat	bufTell;

	if(startStatus == false) return -1.0;

	alGetSourcef(source, AL_SEC_OFFSET, &bufTell);
	return chunkTime[current] + (double)bufTell;
}

void fk_AudioOggBuffer::seek(double argTime)
{
	unsigned int i;

	stop();
	for(i = 0; i < length; i++) {
		if(chunkTime[i] >= argTime - 0.00001) break;
	}
	current = i;
	endStatus = false;
	StartQueue(!startStatus);

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
