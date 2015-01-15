// AudioWavBuffer_CLI.h

#pragma once

#include <FK/Audio.h>
#include "AudioOggBuffer_CLI.h"

namespace FK_CLI
{
	public ref class fk_AudioWavBuffer : fk_AudioOggBuffer {
	internal:
		::fk_AudioWavBuffer * GetP(void)
		{
			return (::fk_AudioWavBuffer *)(pAudio);
		}

	public:
		fk_AudioWavBuffer::fk_AudioWavBuffer()
		{
			pAudio = new ::fk_AudioWavBuffer();
		}

		fk_AudioWavBuffer::~fk_AudioWavBuffer()
		{
			this->!fk_AudioWavBuffer();
		}

		fk_AudioWavBuffer::!fk_AudioWavBuffer()
		{
			if(pAudio == nullptr) return;
			if(dFlg == true) delete GetP();
			pAudio = nullptr;
		}

		virtual bool open(String^ name) override;
	};
}
