#include "AudioWavBuffer_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;
	
	::fk_AudioWavBuffer * fk_AudioWavBuffer::GetP(void)
	{
		return (::fk_AudioWavBuffer *)(pAudio);
	}

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

	bool fk_AudioWavBuffer::Open(String^ argName)
	{
		if(!argName) return false;
		return GetP()->open(marshal_as<string>(argName));
	}
}
