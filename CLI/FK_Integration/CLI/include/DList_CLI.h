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
		fk_Model^ _rCamera;
		fk_Model^ _lCamera;
		fk_ProjectBase^ _proj;
		fk_ProjectBase^ _rProj;
		fk_ProjectBase^ _lProj;

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

		property fk_Model^ camera {
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

		property fk_Model^ rCamera {
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
		
		property fk_Model^ lCamera {
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

		void SetProjection(fk_ProjectBase^ argP);
		void SetStereoProjection(fk_StereoChannel channel, fk_ProjectBase ^projection);
		void ClearStereo(void);
		void SetStereoOverlayMode(bool mode);
		bool GetStereoOverlayMode(void);
		void ClearDisplay(void);
		void EntryModel(fk_Model ^model);
		void RemoveModel(fk_Model ^model);
		void ClearModel(void);
		void EntryOverlayModel(fk_Model ^model);
		void RemoveOverlayModel(fk_Model^ model);
		void ClearOverlayModel(void);
	};
}
