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

		::fk_DisplayLink * GetP(void);
		void CameraUpdate(void);
		::fk_StereoChannel GetStereo(fk_StereoChannel);
	
	public:
		fk_DisplayLink(bool argNewFlg);
		~fk_DisplayLink();
		!fk_DisplayLink();

		property fk_Model^ Camera {
			fk_Model^ get();
			void set(fk_Model^ argM);
		}			

		property fk_Model^ LeftCamera {
			fk_Model^ get();
			void set(fk_Model^ argM);
		}

		property fk_Model^ RightCamera {
			fk_Model^ get();
			void set(fk_Model^ argM);
		}
		
		property fk_ProjectBase^ Projection {
			fk_ProjectBase^ get();
			void set(fk_ProjectBase^ argP);
		}			

		property fk_ProjectBase^ LeftProjection {
			fk_ProjectBase^ get();
			void set(fk_ProjectBase^ argP);
		}
		
		property fk_ProjectBase^ RightProjection {
			fk_ProjectBase^ get();
			void set(fk_ProjectBase^ argP);
		}

		property bool StereoOverlayMode {
			bool get();
			void set(bool argMode);
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
