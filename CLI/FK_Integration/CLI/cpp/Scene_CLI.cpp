#include "../Scene_CLI.h"

namespace FK_CLI {
	::fk_StereoChannel GetStereo(FK_CLI::fk_StereoChannel argC)
	{
		if(argC == fk_StereoChannel::STEREO_LEFT) {
			return FK_STEREO_LEFT;
		}
		return FK_STEREO_RIGHT;
	}
}
