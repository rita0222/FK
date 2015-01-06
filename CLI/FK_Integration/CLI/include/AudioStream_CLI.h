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
