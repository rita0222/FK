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
		fk_Model^ _camera;
		fk_Model^ _lCamera;
		fk_Model^ _rCamera;
		fk_ProjectBase^ _proj;
		fk_ProjectBase^ _lProj;
		fk_ProjectBase^ _rProj;

		::fk_DisplayLink * GetP(void)
		{
			return (::fk_DisplayLink *)(pBase);
		}

		void CameraUpdate(void)
		{
			_camera = gcnew fk_Model(false);
			_camera->pBase = const_cast<::fk_Model *>(GetP()->getCamera());
			_camera->dFlg = false;
		}

		::fk_StereoChannel GetStereo(fk_StereoChannel);
	
	public:
		fk_DisplayLink::fk_DisplayLink(bool argNewFlg)
			: fk_BaseObject(false),
			modelList(gcnew List<fk_Model^>()),
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

		property fk_Model^ Camera {
			fk_Model^ get()
			{
				CameraUpdate();
				return _camera;
			}

			void set(fk_Model^ argM)
			{
				if(!argM) return;
				GetP()->entryCamera(argM->GetP());
				_camera = argM;
			}
		}			

		property fk_Model^ LeftCamera {
			fk_Model^ get()
			{
				return _lCamera;
			}

			void set(fk_Model^ argM)
			{
				if(!argM) return;
				GetP()->entryStereoCamera(FK_STEREO_LEFT, argM->GetP());
				_lCamera = argM;
			}
		}

		property fk_Model^ RightCamera {
			fk_Model^ get()
			{
				return _rCamera;
			}

			void set(fk_Model^ argM)
			{
				if(!argM) return;
				GetP()->entryStereoCamera(FK_STEREO_RIGHT, argM->GetP());
				_rCamera = argM;
			}
		}
		
		property fk_ProjectBase^ Projection {
			fk_ProjectBase^ get()
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

			void set(fk_ProjectBase^ argP)
			{
				if(!argP) return;
				GetP()->setProjection(argP->GetP());
				_proj = argP;
			}
		}			

		property fk_ProjectBase^ LeftProjection {
			fk_ProjectBase^ get()
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

			void set(fk_ProjectBase^ argP)
			{
				if(!argP) return;
				GetP()->setStereoProjection(FK_STEREO_LEFT, argP->GetP());
				_lProj = argP;
			}
		}
		
		property fk_ProjectBase^ RightProjection {
			fk_ProjectBase^ get()
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

			void set(fk_ProjectBase^ argP)
			{
				if(!argP) return;
				GetP()->setStereoProjection(FK_STEREO_RIGHT, argP->GetP());
				_rProj = argP;
			}
		}

		property bool StereoOverlayMode {
			bool get()
			{
				return GetP()->getStereoOverlayMode();
			}

			void set(bool argMode)
			{
				GetP()->setStereoOverlayMode(argMode);
			}
		}
		

		void ClearStereo(void);
		void ClearDisplay(void);
		void EntryModel(fk_Model ^model);
		void RemoveModel(fk_Model ^model);
		void ClearModel(void);
		void EntryOverlayModel(fk_Model ^model);
		void RemoveOverlayModel(fk_Model^ model);
		void ClearOverlayModel(void);
	};
}
