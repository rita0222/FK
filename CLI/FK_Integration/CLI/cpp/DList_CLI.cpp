#include "DList_CLI.h"

namespace FK_CLI {
	::fk_StereoChannel fk_DisplayLink::GetStereo(FK_CLI::fk_StereoChannel argC)
	{
		if(argC == fk_StereoChannel::STEREO_LEFT) {
			return FK_STEREO_LEFT;
		}
		return FK_STEREO_RIGHT;
	}

	void fk_DisplayLink::clearDisplay(void)
	{
		GetP()->clearDisplay();
		modelList->Clear();
		overlayList->Clear();
		CameraUpdate();
	}

	void fk_DisplayLink::entryModel(fk_Model ^argM)
	{
		if(!argM) return;
		GetP()->entryModel(argM->GetP());
		if(modelList->Contains(argM) == false) modelList->Add(argM);
	}			

	void fk_DisplayLink::removeModel(fk_Model ^argM)
	{
		if(!argM) return;
		GetP()->removeModel(argM->GetP());
		while(modelList->Contains(argM) == true) {
			modelList->Remove(argM);
		}
 	}

	void fk_DisplayLink::clearModel(void)
	{
		GetP()->clearModel();
		modelList->Clear();
	}

	void fk_DisplayLink::entryOverlayModel(fk_Model ^argM)
	{
		if(!argM) return;
		GetP()->entryOverlayModel(argM->GetP());
		if(overlayList->Contains(argM) == false) overlayList->Add(argM);
	}
		
	void fk_DisplayLink::removeOverlayModel(fk_Model^ argM)
	{
		if(!argM) return;
		GetP()->removeOverlayModel(argM->GetP());
		while(overlayList->Contains(argM) == true) {
			overlayList->Remove(argM);
		}
	}
			
	void fk_DisplayLink::clearOverlayModel(void)
	{
		GetP()->clearOverlayModel();
		overlayList->Clear();
	}

	void fk_DisplayLink::entryCamera(fk_Model ^argM)
	{
		GetP()->entryCamera(argM->GetP());
		camera = argM;
	}

	fk_Model^ fk_DisplayLink::getCamera(void)
	{
		CameraUpdate();
		return camera;
	}
				
	void fk_DisplayLink::setProjection(fk_ProjectBase ^argP)
	{
		if(!argP) return;
		GetP()->setProjection(argP->GetP());
		proj = argP;
	}

	void fk_DisplayLink::entryStereoCamera(fk_StereoChannel argChannel, fk_Model^ argM)
	{
		if(!argM) return;
		GetP()->entryStereoCamera(GetStereo(argChannel), argM->GetP());
		switch(argChannel) {
			case fk_StereoChannel::STEREO_RIGHT:
				rCamera = argM;
				break;

			case fk_StereoChannel::STEREO_LEFT:
				lCamera = argM;
				break;

			default:
				break;
		}
	}

	void fk_DisplayLink::setStereoProjection(fk_StereoChannel argChannel,
											 fk_ProjectBase ^argP)
	{
		if(!argP) return;
		GetP()->setStereoProjection(GetStereo(argChannel), argP->GetP());
		switch(argChannel) {
			case fk_StereoChannel::STEREO_RIGHT:
				rProj = argP;
				break;

			case fk_StereoChannel::STEREO_LEFT:
				lProj = argP;
				break;

			default:
				break;
		}
	}

	void fk_DisplayLink::clearStereo(void)
	{
		GetP()->clearStereo();
	}

	void fk_DisplayLink::setStereoOverlayMode(bool argMode)
	{
		GetP()->setStereoOverlayMode(argMode);
	}

	bool fk_DisplayLink::getStereoOverlayMode(void)
	{
		return GetP()->getStereoOverlayMode();
	}
}
