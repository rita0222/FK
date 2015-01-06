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
			if(dFlg == true) delete pAudio;
			pAudio = NULL;
		}

		virtual bool open(String^ name) override;
		virtual bool ready(void) override;
		virtual bool play(void) override;
		virtual double tell(void) override;
		virtual void seek(double time) override;
		virtual void stop(void) override;
		virtual void end(void) override;
	};
}
