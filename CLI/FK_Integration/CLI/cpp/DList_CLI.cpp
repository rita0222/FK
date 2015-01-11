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
	}

	void fk_DisplayLink::entryModel(fk_Model ^argM)
	{
		GetP()->entryModel(argM->GetP());
	}			

	void fk_DisplayLink::removeModel(fk_Model ^argM)
	{
		GetP()->removeModel(argM->GetP());
	}

	void fk_DisplayLink::clearModel(void)
	{
		GetP()->clearModel();
	}

	void fk_DisplayLink::entryOverlayModel(fk_Model ^argM)
	{
		GetP()->entryOverlayModel(argM->GetP());
	}
		
	void fk_DisplayLink::removeOverlayModel(fk_Model^ argM)
	{
		GetP()->removeOverlayModel(argM->GetP());
	}
			
	void fk_DisplayLink::clearOverlayModel(void)
	{
		GetP()->clearOverlayModel();
	}

	void fk_DisplayLink::entryCamera(fk_Model ^argM)
	{
		GetP()->entryCamera(argM->GetP());
	}

	fk_Model^ fk_DisplayLink::getCamera(void)
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = const_cast<::fk_Model *>(GetP()->getCamera());
		M->dFlg = false;
		return M;
	}
				
	void fk_DisplayLink::setProjection(fk_ProjectBase ^argP)
	{
		GetP()->setProjection(argP->GetP());
	}

	void fk_DisplayLink::entryStereoCamera(fk_StereoChannel argChannel, fk_Model^ argM)
	{
		GetP()->entryStereoCamera(GetStereo(argChannel), argM->GetP());
	}

	void fk_DisplayLink::setStereoProjection(fk_StereoChannel argChannel, fk_ProjectBase ^argP)
	{
		GetP()->setStereoProjection(GetStereo(argChannel), argP->GetP());
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
