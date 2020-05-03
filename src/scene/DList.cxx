#define FK_DEF_SIZETYPE

#include <FK/DList.h>
#include <FK/Window.h>

using namespace std;
using namespace FK;

unique_ptr<fk_IDAdmin> fk_DisplayLink::DLManager = make_unique<fk_IDAdmin>(1);

fk_DisplayLink::fk_DLinkData::fk_DLinkData(void) :
	camera(&localCamera), proj(&perspective), projStatus(0), stereoOverlayMode(true)
{
	return;
}

fk_DisplayLink::fk_DisplayLink(void)
	: fk_BaseObject(fk_Type::DISPLAYLINK)
{
	data = make_unique<fk_DLinkData>();
	data->displayID = DLManager->CreateID();
	clearStereo();

	return;
}

fk_DisplayLink::~fk_DisplayLink()
{
	DLManager->EraseID(data->displayID);
	return;
}

void fk_DisplayLink::clearDisplay(void)
{
	clearModel();
	clearOverlayModel();

	data->camera = &(data->localCamera);
	data->proj = &(data->perspective);
	data->projStatus++;

	clearStereo();

	return;
}

void fk_DisplayLink::entryModel(fk_Model *argModel)
{
	if(argModel == nullptr) return;

	if(argModel->getShape() != nullptr) {
		if(argModel->getShape()->getRealShapeType() == fk_RealShapeType::LIGHT) {
			fk_Light *light = dynamic_cast<fk_Light *>(argModel->getShape());
			switch(light->getLightType()) {
			  case fk_LightType::PARALLEL:
				data->parallelLightList.remove(argModel);
				data->parallelLightList.push_front(argModel);
				break;

			  case fk_LightType::POINT:
				data->pointLightList.remove(argModel);
				data->pointLightList.push_front(argModel);
				break;

			  case fk_LightType::SPOT:
				data->spotLightList.remove(argModel);
				data->spotLightList.push_front(argModel);
				break;

			  default:
				break;
			}
			return;
		}
	}

	data->modelList.remove(argModel);
	data->modelList.push_back(argModel);

	return;
}

void fk_DisplayLink::removeModel(fk_Model *argModel)
{
	data->parallelLightList.remove(argModel);
	data->pointLightList.remove(argModel);
	data->spotLightList.remove(argModel);
	data->modelList.remove(argModel);

	return;
}

void fk_DisplayLink::clearModel(void)
{
	data->parallelLightList.clear();
	data->pointLightList.clear();
	data->spotLightList.clear();
	data->modelList.clear();

	return;
}

void fk_DisplayLink::entryOverlayModel(fk_Model *argModel)
{
	if(argModel == nullptr) return;

	if(argModel->getShape() != nullptr) {
		if(argModel->getShape()->getRealShapeType() == fk_RealShapeType::LIGHT) {
			return;
		}
	}

	data->overlayList.remove(argModel);
	data->overlayList.push_back(argModel);

	return;
}

void fk_DisplayLink::removeOverlayModel(fk_Model *argModel)
{
	data->overlayList.remove(argModel);

	return;
}

void fk_DisplayLink::clearOverlayModel(void)
{
	data->overlayList.clear();

	return;
}

void fk_DisplayLink::entryCamera(fk_Model *argModel)
{
	if(argModel == nullptr) {
		data->camera = &(data->localCamera);
	} else {
		data->camera = argModel;
	}
	return;
}

list<fk_Model *> * fk_DisplayLink::GetModelList(void)
{
	return &(data->modelList);
}

list<fk_Model *> * fk_DisplayLink::GetLightList(fk_LightType argType)
{
	switch(argType) {
	  case fk_LightType::PARALLEL:
		return &(data->parallelLightList);

	  case fk_LightType::POINT:
		return &(data->pointLightList);

	  case fk_LightType::SPOT:
		return &(data->spotLightList);

	  default:
		break;
	}

	return nullptr;
}

list<fk_Model *> * fk_DisplayLink::GetOverlayList(void)
{
	return &(data->overlayList);
}

fk_Model * fk_DisplayLink::getCamera(void) const
{
	return data->camera;
}

int fk_DisplayLink::GetID(void) const
{
	return data->displayID;
}

void fk_DisplayLink::setProjection(fk_ProjectBase *argProj)
{
	if(argProj == nullptr) return;

	switch(argProj->getMode()) {
	  case fk_ProjectMode::PERSPECTIVE:
		data->perspective = *(static_cast<fk_Perspective *>(argProj));
		data->proj = &(data->perspective);
		break;

	  case fk_ProjectMode::FRUSTUM:
		data->frustum = *(static_cast<fk_Frustum *>(argProj));
		data->proj = &(data->frustum);
		break;

	  case fk_ProjectMode::ORTHO:
		data->ortho = *(static_cast<fk_Ortho *>(argProj));
		data->proj = &(data->ortho);
		break;

	  default:
		break;
	}

	data->projStatus++;

	return;
}

fk_ProjectBase * fk_DisplayLink::getProjection(void) const
{
	return data->proj;
}

int fk_DisplayLink::GetProjChangeStatus(void) const
{
	return data->projStatus;
}

void fk_DisplayLink::entryStereoCamera(fk_StereoChannel argChannel, fk_Model *argModel)
{
	switch(argChannel) {
	  case fk_StereoChannel::LEFT:
		data->stereoCamera[0] = argModel;
		break;

	  case fk_StereoChannel::RIGHT:
		data->stereoCamera[1] = argModel;
		break;

	  default:
		break;
	}
	return;
}

void fk_DisplayLink::setStereoProjection(fk_StereoChannel argChannel, fk_ProjectBase *argProj)
{
	int index;

	switch(argChannel) {
	  case fk_StereoChannel::LEFT:
		index = 0;
		break;
		
	  case fk_StereoChannel::RIGHT:
		index = 1;
		break;

	  default:
		return;
	}

	if(argProj == nullptr) {
		data->stereoProj[index] = data->proj;
		return;
	}

	switch(argProj->getMode()) {
	  case fk_ProjectMode::PERSPECTIVE:
		data->stereoPers[index] = *(static_cast<fk_Perspective *>(argProj));
		data->stereoProj[index] = &(data->stereoPers[index]);
		break;

	  case fk_ProjectMode::FRUSTUM:
		data->stereoFrus[index] = *(static_cast<fk_Frustum *>(argProj));
		data->stereoProj[index] = &(data->stereoFrus[index]);
		break;

	  case fk_ProjectMode::ORTHO:
		data->stereoOrtho[index] = *(static_cast<fk_Ortho *>(argProj));
		data->stereoProj[index] = &(data->stereoOrtho[index]);
		break;

	  default:
		break;
	}
}

const fk_Model * fk_DisplayLink::getStereoCamera(fk_StereoChannel argChannel)
{
	switch(argChannel) {
	  case fk_StereoChannel::LEFT:
		return data->stereoCamera[0];

	  case fk_StereoChannel::RIGHT:
		return data->stereoCamera[1];

	  default:
		break;
	}
	return nullptr;
}

const fk_ProjectBase * fk_DisplayLink::getStereoProjection(fk_StereoChannel argChannel)
{
	switch(argChannel) {
	  case fk_StereoChannel::LEFT:
		return data->stereoProj[0];

	  case fk_StereoChannel::RIGHT:
		return data->stereoProj[1];

	  default:
		break;
	}
	return nullptr;
}

void fk_DisplayLink::clearStereo(void)
{
	data->stereoCamera[0] = nullptr;
	data->stereoCamera[1] = nullptr;
	data->stereoProj[0] = data->proj;
	data->stereoProj[1] = data->proj;
}

void fk_DisplayLink::setStereoOverlayMode(bool argFlg)
{
	data->stereoOverlayMode = argFlg;
	return;
}

bool fk_DisplayLink::getStereoOverlayMode(void)
{
	return data->stereoOverlayMode;
}

void fk_DisplayLink::SetFinalizeMode(void)
{
	data->localCamera.SetTreeDelMode(false);
	return;
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
