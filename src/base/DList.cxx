/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#include <FK/DList.h>
#include <FK/Model.h>
#include <FK/Shape.h>
#include <FK/IDAdmin.H>

using namespace std;

static fk_IDAdmin & fk_DLManager(void)
{
	static fk_IDAdmin	fk_DLManager(1);
	return fk_DLManager;
}

fk_DisplayLink::fk_DisplayLink(void)
	: fk_BaseObject(FK_DISPLAYLINK)
{
	camera = &localCamera;
	modelList.clear();
	lightList.clear();
	overlayList.clear();

	displayID = fk_DLManager().CreateID();
	proj = &perspective;
	projStatus = 0;

	clearStereo();
	stereoOverlayMode = true;

	return;
}

fk_DisplayLink::~fk_DisplayLink()
{
	modelList.clear();
	lightList.clear();
	overlayList.clear();

	fk_DLManager().EraseID(displayID);

	return;
}

void fk_DisplayLink::clearDisplay(void)
{
	clearModel();
	clearOverlayModel();

	camera = &localCamera;
	proj = &perspective;
	projStatus++;

	clearStereo();

	return;
}

void fk_DisplayLink::entryModel(fk_Model *argModel)
{
	if(argModel == nullptr) return;

	if(argModel->getShape() != nullptr) {
		if(argModel->getShape()->getRealShapeType() == FK_SHAPE_LIGHT) {
			lightList.remove(argModel);
			lightList.push_back(argModel);
			return;
		}
	}

	modelList.remove(argModel);
	modelList.push_back(argModel);

	return;
}

void fk_DisplayLink::removeModel(fk_Model *argModel)
{
	lightList.remove(argModel);
	modelList.remove(argModel);

	return;
}

void fk_DisplayLink::clearModel(void)
{
	lightList.clear();
	modelList.clear();

	return;
}

void fk_DisplayLink::entryOverlayModel(fk_Model *argModel)
{
	if(argModel == nullptr) return;

	if(argModel->getShape() != nullptr) {
		if(argModel->getShape()->getRealShapeType() == FK_SHAPE_LIGHT) {
			return;
		}
	}

	overlayList.remove(argModel);
	overlayList.push_back(argModel);

	return;
}

void fk_DisplayLink::removeOverlayModel(fk_Model *argModel)
{
	overlayList.remove(argModel);

	return;
}

void fk_DisplayLink::clearOverlayModel(void)
{
	overlayList.clear();

	return;
}

void fk_DisplayLink::entryCamera(fk_Model *argModel)
{
	if(argModel == nullptr) {
		camera = &localCamera;
	} else {
		camera = argModel;
	}
	return;
}

list<fk_Model *> * fk_DisplayLink::GetModelList(void)
{
	return &modelList;
}

list<fk_Model *> * fk_DisplayLink::GetLightList(void)
{
	return &lightList;
}

list<fk_Model *> * fk_DisplayLink::GetOverlayList(void)
{
	return &overlayList;
}

const fk_Model * fk_DisplayLink::getCamera(void) const
{
	return camera;
}

int fk_DisplayLink::GetID(void) const
{
	return displayID;
}

void fk_DisplayLink::setProjection(fk_ProjectBase *argProj)
{
	if(argProj == nullptr) return;

	switch(argProj->getMode()) {
	  case FK_PERSPECTIVE_MODE:
		perspective = *(static_cast<fk_Perspective *>(argProj));
		proj = &perspective;
		break;

	  case FK_FRUSTUM_MODE:
		frustum = *(static_cast<fk_Frustum *>(argProj));
		proj = &frustum;
		break;

	  case FK_ORTHO_MODE:
		ortho = *(static_cast<fk_Ortho *>(argProj));
		proj = &ortho;
		break;

	  default:
		break;
	}

	projStatus++;

	return;
}

const fk_ProjectBase * fk_DisplayLink::getProjection(void) const
{
	return proj;
}

int fk_DisplayLink::GetProjChangeStatus(void) const
{
	return projStatus;
}

void fk_DisplayLink::entryStereoCamera(fk_StereoChannel channel,
									   fk_Model *argModel)
{
	if(channel == FK_STEREO_LEFT) {
		stereoCamera[0] = argModel;
	} else if(channel == FK_STEREO_RIGHT) {
		stereoCamera[1] = argModel;
	}
}

void fk_DisplayLink::setStereoProjection(fk_StereoChannel channel,
										 fk_ProjectBase *argProj)
{
	int index;

	if(channel == FK_STEREO_LEFT) {
		index = 0;
	} else if(channel == FK_STEREO_RIGHT) {
		index = 1;
	} else {
		return;
	}

	if(argProj == nullptr) {
		stereoProj[index] = proj;
		return;
	}

	switch(argProj->getMode()) {
	  case FK_PERSPECTIVE_MODE:
		stereoPers[index] = *(static_cast<fk_Perspective *>(argProj));
		stereoProj[index] = &stereoPers[index];
		break;

	  case FK_FRUSTUM_MODE:
		stereoFrus[index] = *(static_cast<fk_Frustum *>(argProj));
		stereoProj[index] = &stereoFrus[index];
		break;

	  case FK_ORTHO_MODE:
		stereoOrtho[index] = *(static_cast<fk_Ortho *>(argProj));
		stereoProj[index] = &stereoOrtho[index];
		break;

	  default:
		break;
	}
}

const fk_Model * fk_DisplayLink::getStereoCamera(fk_StereoChannel channel)
{
	if(channel == FK_STEREO_LEFT) {
		return stereoCamera[0];
	} else if(channel == FK_STEREO_RIGHT) {
		return stereoCamera[1];
	}
	return nullptr;
}

const fk_ProjectBase * fk_DisplayLink::getStereoProjection(fk_StereoChannel channel)
{
	if(channel == FK_STEREO_LEFT) {
		return stereoProj[0];
	} else if(channel == FK_STEREO_RIGHT) {
		return stereoProj[1];
	}
	return nullptr;
}

void fk_DisplayLink::clearStereo(void)
{
	stereoCamera[0] = nullptr;
	stereoCamera[1] = nullptr;
	stereoProj[0] = proj;
	stereoProj[1] = proj;
}

void fk_DisplayLink::setStereoOverlayMode(bool argFlg)
{
	stereoOverlayMode = argFlg;
	return;
}

bool fk_DisplayLink::getStereoOverlayMode(void)
{
	return stereoOverlayMode;
}

void fk_DisplayLink::SetFinalizeMode(void)
{
	localCamera.SetTreeDelMode(false);
	return;
}

