#include "AudioStream_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;
	
	::fk_AudioStream * fk_AudioStream::GetP(void)
	{
		return (::fk_AudioStream *)(pAudio);
	}

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
