// AudioOggBuffer_CLI.h

#pragma once

#include <FK/Audio.h>
#include "AudioBase_CLI.h"

namespace FK_CLI
{
	public ref class fk_AudioOggBuffer : fk_AudioBase {
	internal:
		::fk_AudioOggBuffer * GetP(void)
		{
			return (::fk_AudioOggBuffer *)(pAudio);
		}

	public:
		fk_AudioOggBuffer::fk_AudioOggBuffer()
		{
			pAudio = new ::fk_AudioOggBuffer();
		}

		fk_AudioOggBuffer::~fk_AudioOggBuffer()
		{
			this->!fk_AudioOggBuffer();
		}

		fk_AudioOggBuffer::!fk_AudioOggBuffer()
		{
			if(pAudio == nullptr) return;
			if(dFlg == true) delete GetP();
			pAudio = nullptr;
		}

		virtual bool Open(String^ name) override;
		virtual bool Ready(void) override;
		virtual bool Play(void) override;
		virtual double Tell(void) override;
		virtual void Seek(double time) override;
		virtual void Stop(void) override;
		virtual void End(void) override;
	};
}
