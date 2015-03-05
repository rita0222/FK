// AudioWavBuffer_CLI.h

#pragma once

#include <FK/Audio.h>
#include "AudioOggBuffer_CLI.h"

namespace FK_CLI
{
	public ref class fk_AudioWavBuffer : fk_AudioOggBuffer {
	internal:
		::fk_AudioWavBuffer * GetP(void);

	public:
		fk_AudioWavBuffer();
		~fk_AudioWavBuffer();
		!fk_AudioWavBuffer();
		virtual bool Open(String^ name) override;
	};
}
