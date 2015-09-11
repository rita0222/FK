#include "DList_CLI.h"

namespace FK_CLI {

	::fk_DisplayLink * fk_DisplayLink::GetP(void)
	{
		return (::fk_DisplayLink *)(pBase);
	}

	void fk_DisplayLink::CameraUpdate(void)
	{
		_camera = gcnew fk_Model(false);
		_camera->pBase = const_cast<::fk_Model *>(GetP()->getCamera());
		_camera->dFlg = false;
	}

	::fk_StereoChannel fk_DisplayLink::GetStereo(FK_CLI::fk_StereoChannel argC)
	{
		if(argC == fk_StereoChannel::STEREO_LEFT) {
			return FK_STEREO_LEFT;
		}
		return FK_STEREO_RIGHT;
	}

	fk_DisplayLink::fk_DisplayLink(bool argNewFlg)
		: fk_BaseObject(false), modelList(gcnew List<fk_Model^>()),
		  overlayList(gcnew List<fk_Model^>()),
		  _camera(nullptr), _rCamera(nullptr), _lCamera(nullptr),
		  _proj(nullptr), _rProj(nullptr), _lProj(nullptr)
	{
	}

	fk_DisplayLink::~fk_DisplayLink()
	{
		this->!fk_DisplayLink();
	}

	fk_DisplayLink::!fk_DisplayLink()
	{
	}

	fk_Model^ fk_DisplayLink::Camera::get()
	{
		CameraUpdate();
		return _camera;
	}

	void fk_DisplayLink::Camera::set(fk_Model^ argM)
	{
		if(!argM) return;
		GetP()->entryCamera(argM->GetP());
		_camera = argM;
	}

	fk_Model^ fk_DisplayLink::LeftCamera::get()
	{
		return _lCamera;
	}

	void fk_DisplayLink::LeftCamera::set(fk_Model^ argM)
	{
		if(!argM) return;
		GetP()->entryStereoCamera(FK_STEREO_LEFT, argM->GetP());
		_lCamera = argM;
	}

	fk_Model^ fk_DisplayLink::RightCamera::get()
	{
		return _rCamera;
	}

	void fk_DisplayLink::RightCamera::set(fk_Model^ argM)
	{
		if(!argM) return;
		GetP()->entryStereoCamera(FK_STEREO_RIGHT, argM->GetP());
		_rCamera = argM;
	}
		
	fk_ProjectBase^ fk_DisplayLink::Projection::get()
	{
		if(!_proj) {
			const ::fk_ProjectBase *cP = GetP()->getProjection();
			::fk_ProjectBase *proj = const_cast<::fk_ProjectBase *>(cP);

			switch(proj->getMode()) {
			  case FK_PERSPECTIVE_MODE:
				_proj = gcnew fk_Perspective(false);
				break;

			  case FK_FRUSTUM_MODE:
				_proj = gcnew fk_Frustum(false);
				break;

			  case FK_ORTHO_MODE:
				_proj = gcnew fk_Ortho(false);
				break;
						
			  default:
				return nullptr;
			}
			_proj->pProj = proj;
		}
		return _proj;
	}

	void fk_DisplayLink::Projection::set(fk_ProjectBase^ argP)
	{
		if(!argP) return;
		GetP()->setProjection(argP->GetP());
		_proj = argP;
	}


	fk_ProjectBase^ fk_DisplayLink::LeftProjection::get()
	{
		if(!_lProj) {
			const ::fk_ProjectBase *cP = GetP()->getStereoProjection(FK_STEREO_LEFT);
			::fk_ProjectBase *proj = const_cast<::fk_ProjectBase *>(cP);

			switch(proj->getMode()) {
			  case FK_PERSPECTIVE_MODE:
				_lProj = gcnew fk_Perspective(false);
				break;

			  case FK_FRUSTUM_MODE:
				_lProj = gcnew fk_Frustum(false);
				break;

			  case FK_ORTHO_MODE:
				_lProj = gcnew fk_Ortho(false);
				break;
						
			  default:
				return nullptr;
			}
			_lProj->pProj = proj;
		}
		return _lProj;
	}

	void fk_DisplayLink::LeftProjection::set(fk_ProjectBase^ argP)
	{
		if(!argP) return;
		GetP()->setStereoProjection(FK_STEREO_LEFT, argP->GetP());
		_lProj = argP;
	}
		
	fk_ProjectBase^ fk_DisplayLink::RightProjection::get()
	{
		if(!_rProj) {
			const ::fk_ProjectBase *cP = GetP()->getStereoProjection(FK_STEREO_RIGHT);
			::fk_ProjectBase *proj = const_cast<::fk_ProjectBase *>(cP);

			switch(proj->getMode()) {
			  case FK_PERSPECTIVE_MODE:
				_rProj = gcnew fk_Perspective(false);
				break;

			  case FK_FRUSTUM_MODE:
				_rProj = gcnew fk_Frustum(false);
				break;

			  case FK_ORTHO_MODE:
				_rProj = gcnew fk_Ortho(false);
				break;
						
			  default:
				return nullptr;
			}
			_rProj->pProj = proj;
		}
		return _rProj;
	}

	void fk_DisplayLink::RightProjection::set(fk_ProjectBase^ argP)
	{
		if(!argP) return;
		GetP()->setStereoProjection(FK_STEREO_RIGHT, argP->GetP());
		_rProj = argP;
	}


	bool fk_DisplayLink::StereoOverlayMode::get()
	{
		return GetP()->getStereoOverlayMode();
	}

	void fk_DisplayLink::StereoOverlayMode::set(bool argMode)
	{
		GetP()->setStereoOverlayMode(argMode);
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

	void fk_DisplayLink::ClearStereo(void)
	{
		GetP()->clearStereo();
	}
}
