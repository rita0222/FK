#include "DList_CLI.h"

namespace FK_CLI {

	::FK::fk_DisplayLink * fk_DisplayLink::GetP(void)
	{
		return (::FK::fk_DisplayLink *)(pBase);
	}

	void fk_DisplayLink::CameraUpdate(void)
	{
		_camera = gcnew fk_Model(const_cast<::FK::fk_Model *>(GetP()->getCamera()));
	}

	::FK::fk_StereoChannel fk_DisplayLink::GetStereo(FK_CLI::fk_StereoChannel argC)
	{
		if(argC == fk_StereoChannel::STEREO_LEFT) {
			return ::FK::FK_STEREO_LEFT;
		}
		return ::FK::FK_STEREO_RIGHT;
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
		GetP()->entryStereoCamera(::FK::FK_STEREO_LEFT, argM->GetP());
		_lCamera = argM;
	}

	fk_Model^ fk_DisplayLink::RightCamera::get()
	{
		return _rCamera;
	}

	void fk_DisplayLink::RightCamera::set(fk_Model^ argM)
	{
		if(!argM) return;
		GetP()->entryStereoCamera(::FK::FK_STEREO_RIGHT, argM->GetP());
		_rCamera = argM;
	}
		
	fk_ProjectBase^ fk_DisplayLink::Projection::get()
	{
		if(!_proj) {
			const ::FK::fk_ProjectBase *cP = GetP()->getProjection();
			::FK::fk_ProjectBase *proj = const_cast<::FK::fk_ProjectBase *>(cP);

			switch(proj->getMode()) {
			case ::FK::FK_PERSPECTIVE_MODE:
				_proj = gcnew fk_Perspective(false);
				break;

			case ::FK::FK_FRUSTUM_MODE:
				_proj = gcnew fk_Frustum(false);
				break;

			case ::FK::FK_ORTHO_MODE:
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
			const ::FK::fk_ProjectBase *cP = GetP()->getStereoProjection(::FK::FK_STEREO_LEFT);
			::FK::fk_ProjectBase *proj = const_cast<::FK::fk_ProjectBase *>(cP);

			switch(proj->getMode()) {
			case ::FK::FK_PERSPECTIVE_MODE:
				_lProj = gcnew fk_Perspective(false);
				break;

			case ::FK::FK_FRUSTUM_MODE:
				_lProj = gcnew fk_Frustum(false);
				break;

			case ::FK::FK_ORTHO_MODE:
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
		GetP()->setStereoProjection(::FK::FK_STEREO_LEFT, argP->GetP());
		_lProj = argP;
	}
		
	fk_ProjectBase^ fk_DisplayLink::RightProjection::get()
	{
		if(!_rProj) {
			const ::FK::fk_ProjectBase *cP = GetP()->getStereoProjection(::FK::FK_STEREO_RIGHT);
			::FK::fk_ProjectBase *proj = const_cast<::FK::fk_ProjectBase *>(cP);

			switch(proj->getMode()) {
			case ::FK::FK_PERSPECTIVE_MODE:
				_rProj = gcnew fk_Perspective(false);
				break;

			case ::FK::FK_FRUSTUM_MODE:
				_rProj = gcnew fk_Frustum(false);
				break;

			case ::FK::FK_ORTHO_MODE:
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
		GetP()->setStereoProjection(::FK::FK_STEREO_RIGHT, argP->GetP());
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

/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/
