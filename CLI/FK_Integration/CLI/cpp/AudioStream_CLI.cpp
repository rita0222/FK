#include "AudioStream_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;
	
	bool fk_AudioStream::open(String^ argName)
	{
		if(!argName) return false;
		return GetP()->open(marshal_as<string>(argName));
	}

	bool fk_AudioStream::ready(void)
	{
		return GetP()->ready();
	}
	
	bool fk_AudioStream::play(void)
	{
		return GetP()->play();
	}
	
	double fk_AudioStream::tell(void)
	{
		return GetP()->tell();
	}
		
	void fk_AudioStream::seek(double argTime)
	{
		GetP()->seek(argTime);
	}
	
	void fk_AudioStream::stop(void)
	{
		GetP()->stop();
	}

	void fk_AudioStream::end(void)
	{
		GetP()->end();
	}
}
