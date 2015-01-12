// DList_CLI.h

#pragma once

#include <FK/DList.h>
#include "Base_CLI.h"
#include "Model_CLI.h"
#include "Projection_CLI.h"

namespace FK_CLI
{
	using namespace System::Collections::Generic;

	public enum class fk_StereoChannel {
		STEREO_LEFT,
		STEREO_RIGHT
	};

	public ref class fk_DisplayLink : fk_BaseObject {
	internal:
		List<fk_Model^>^ modelList;
		List<fk_Model^>^ overlayList;
		fk_Model^ camera;
		fk_Model^ rCamera;
		fk_Model^ lCamera;
		fk_ProjectBase^ proj;
		fk_ProjectBase^ rProj;
		fk_ProjectBase^ lProj;

		::fk_DisplayLink * GetP(void)
		{
			return (::fk_DisplayLink *)(pBase);
		}

		void CameraUpdate(void)
		{
			camera = gcnew fk_Model(false);
			camera->pBase = const_cast<::fk_Model *>(GetP()->getCamera());
			camera->dFlg = false;
		}

		::fk_StereoChannel GetStereo(fk_StereoChannel);
	
	public:
		fk_DisplayLink::fk_DisplayLink(bool argNewFlg)
			: fk_BaseObject(false),
			modelList(gcnew List<fk_Model^>()),
			overlayList(gcnew List<fk_Model^>()),
			rCamera(nullptr), lCamera(nullptr),
			proj(nullptr), rProj(nullptr), lProj(nullptr)
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
