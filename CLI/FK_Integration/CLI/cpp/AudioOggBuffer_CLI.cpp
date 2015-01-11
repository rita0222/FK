#include "AudioOggBuffer_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;
	
	bool fk_AudioOggBuffer::open(String^ argName)
	{
		if(!argName) return false;
		return GetP()->open(marshal_as<string>(argName));
	}

	bool fk_AudioOggBuffer::ready(void)
	{
		return GetP()->ready();
	}
	
	bool fk_AudioOggBuffer::play(void)
	{
		return GetP()->play();
	}
	
	double fk_AudioOggBuffer::tell(void)
	{
		return GetP()->tell();
	}
		
	void fk_AudioOggBuffer::seek(double argTime)
	{
		GetP()->seek(argTime);
	}
	
	void fk_AudioOggBuffer::stop(void)
	{
		GetP()->stop();
	}

	void fk_AudioOggBuffer::end(void)
	{
		GetP()->end();
	}
}
