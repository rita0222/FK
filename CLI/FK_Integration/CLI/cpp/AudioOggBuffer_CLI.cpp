#include "AudioOggBuffer_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;
	
	bool fk_AudioOggBuffer::Open(String^ argName)
	{
		if(!argName) return false;
		return GetP()->open(marshal_as<string>(argName));
	}

	bool fk_AudioOggBuffer::Ready(void)
	{
		return GetP()->ready();
	}
	
	bool fk_AudioOggBuffer::Play(void)
	{
		return GetP()->play();
	}
	
	double fk_AudioOggBuffer::Tell(void)
	{
		return GetP()->tell();
	}
		
	void fk_AudioOggBuffer::Seek(double argTime)
	{
		GetP()->seek(argTime);
	}
	
	void fk_AudioOggBuffer::Stop(void)
	{
		GetP()->stop();
	}

	void fk_AudioOggBuffer::End(void)
	{
		GetP()->end();
	}
}
