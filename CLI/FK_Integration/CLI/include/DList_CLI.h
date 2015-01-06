// DList_CLI.h

#pragma once

#include <FK/DList.h>
#include "Base_CLI.h"
#include "Model_CLI.h"
#include "Projection_CLI.h"

namespace FK_CLI
{
	public enum class fk_StereoChannel {
		STEREO_LEFT,
		STEREO_RIGHT
	};

	public ref class fk_DisplayLink : fk_BaseObject {
	internal:
		::fk_DisplayLink * GetP(void)
		{
			return (::fk_DisplayLink *)(pBase);
		}

		::fk_StereoChannel GetStereo(fk_StereoChannel);
	
	public:
		fk_DisplayLink::fk_DisplayLink(bool argNewFlg) : fk_BaseObject(false)
		{
		}

		fk_DisplayLink::~fk_DisplayLink()
		{
			this->!fk_DisplayLink();
		}

		fk_DisplayLink::!fk_DisplayLink()
		{
		}

		void clearDisplay(void);
		void entryModel(fk_Model ^model);
		void removeModel(fk_Model ^model);
		void clearModel(void);
		void entryOverlayModel(fk_Model ^model);
		void removeOverlayModel(fk_Model^ model);
		void clearOverlayModel(void);
		void entryCamera(fk_Model ^model);
		fk_Model^ getCamera(void);
		void setProjection(fk_ProjectBase ^argP);
		void entryStereoCamera(fk_StereoChannel channel, fk_Model^ model);
		void setStereoProjection(fk_StereoChannel channel, fk_ProjectBase ^projection);
		void clearStereo(void);
		void setStereoOverlayMode(bool mode);
		bool getStereoOverlayMode(void);
	};
}
