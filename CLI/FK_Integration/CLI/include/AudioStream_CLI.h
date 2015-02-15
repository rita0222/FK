// AudioStream_CLI.h

#pragma once

#include <FK/Audio.h>
#include "AudioBase_CLI.h"

namespace FK_CLI
{
	public ref class fk_AudioStream : fk_AudioBase {
	internal:
		::fk_AudioStream * GetP(void)
		{
			return (::fk_AudioStream *)(pAudio);
		}

	public:
		fk_AudioStream::fk_AudioStream()
		{
			pAudio = new ::fk_AudioStream();
		}

		fk_AudioStream::~fk_AudioStream()
		{
			this->!fk_AudioStream();
		}

		fk_AudioStream::!fk_AudioStream()
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
