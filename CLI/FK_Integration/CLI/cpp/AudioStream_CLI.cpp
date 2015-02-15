#include "AudioStream_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;
	
	bool fk_AudioStream::Open(String^ argName)
	{
		if(!argName) return false;
		return GetP()->open(marshal_as<string>(argName));
	}

	bool fk_AudioStream::Ready(void)
	{
		return GetP()->ready();
	}
	
	bool fk_AudioStream::Play(void)
	{
		return GetP()->play();
	}
	
	double fk_AudioStream::Tell(void)
	{
		return GetP()->tell();
	}
		
	void fk_AudioStream::Seek(double argTime)
	{
		GetP()->seek(argTime);
	}
	
	void fk_AudioStream::Stop(void)
	{
		GetP()->stop();
	}

	void fk_AudioStream::End(void)
	{
		GetP()->end();
	}
}
