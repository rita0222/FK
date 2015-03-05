// AudioStream_CLI.h

#pragma once

#include <FK/Audio.h>
#include "AudioBase_CLI.h"

namespace FK_CLI
{
	public ref class fk_AudioStream : fk_AudioBase {
	internal:
		::fk_AudioStream * GetP(void);

	public:
		fk_AudioStream();
		~fk_AudioStream();
		!fk_AudioStream();

		virtual bool Open(String^ name) override;
		virtual bool Ready(void) override;
		virtual bool Play(void) override;
		virtual double Tell(void) override;
		virtual void Seek(double time) override;
		virtual void Stop(void) override;
		virtual void End(void) override;
	};
}
