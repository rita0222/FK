#include "DList_CLI.h"

namespace FK_CLI {
	::fk_StereoChannel fk_DisplayLink::GetStereo(FK_CLI::fk_StereoChannel argC)
	{
		if(argC == fk_StereoChannel::STEREO_LEFT) {
			return FK_STEREO_LEFT;
		}
		return FK_STEREO_RIGHT;
	}

	void fk_DisplayLink::ClearDisplay(void)
	{
		GetP()->clearDisplay();
		modelList->Clear();
		overlayList->Clear();
		CameraUpdate();
	}

	void fk_DisplayLink::EntryModel(fk_Model ^argM)
	{
		if(!argM) return;
		GetP()->entryModel(argM->GetP());
		if(modelList->Contains(argM) == false) modelList->Add(argM);
	}			

	void fk_DisplayLink::RemoveModel(fk_Model ^argM)
	{
		if(!argM) return;
		GetP()->removeModel(argM->GetP());
		while(modelList->Contains(argM) == true) {
			modelList->Remove(argM);
		}
 	}

	void fk_DisplayLink::ClearModel(void)
	{
		GetP()->clearModel();
		modelList->Clear();
	}

	void fk_DisplayLink::EntryOverlayModel(fk_Model ^argM)
	{
		if(!argM) return;
		GetP()->entryOverlayModel(argM->GetP());
		if(overlayList->Contains(argM) == false) overlayList->Add(argM);
	}
		
	void fk_DisplayLink::RemoveOverlayModel(fk_Model^ argM)
	{
		if(!argM) return;
		GetP()->removeOverlayModel(argM->GetP());
		while(overlayList->Contains(argM) == true) {
			overlayList->Remove(argM);
		}
	}
			
	void fk_DisplayLink::ClearOverlayModel(void)
	{
		GetP()->clearOverlayModel();
		overlayList->Clear();
	}
				
	void fk_DisplayLink::SetProjection(fk_ProjectBase ^argP)
	{
		if(!argP) return;
		GetP()->setProjection(argP->GetP());
		_proj = argP;
	}

	void fk_DisplayLink::SetStereoProjection(fk_StereoChannel argChannel,
											 fk_ProjectBase ^argP)
	{
		if(!argP) return;
		GetP()->setStereoProjection(GetStereo(argChannel), argP->GetP());
		switch(argChannel) {
			case fk_StereoChannel::STEREO_RIGHT:
				_rProj = argP;
				break;

			case fk_StereoChannel::STEREO_LEFT:
				_lProj = argP;
				break;

			default:
				break;
		}
	}

	void fk_DisplayLink::ClearStereo(void)
	{
		GetP()->clearStereo();
	}

	void fk_DisplayLink::SetStereoOverlayMode(bool argMode)
	{
		GetP()->setStereoOverlayMode(argMode);
	}

	bool fk_DisplayLink::GetStereoOverlayMode(void)
	{
		return GetP()->getStereoOverlayMode();
	}
}
