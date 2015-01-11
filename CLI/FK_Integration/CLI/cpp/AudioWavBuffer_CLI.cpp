#include "AudioWavBuffer_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;
	
	bool fk_AudioWavBuffer::open(String^ argName)
	{
		if(!argName) return false;
		return GetP()->open(marshal_as<string>(argName));
	}
}
