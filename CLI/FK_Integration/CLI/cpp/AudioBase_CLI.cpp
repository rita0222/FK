#include "AudioBase_CLI.h"

namespace FK_CLI {

	::fk_AudioBase * fk_AudioBase::GetP(void)
	{
		return pAudio;
	}

	fk_AudioBase::fk_AudioBase()
	{
		dFlg = true;
	}

	fk_AudioBase::~fk_AudioBase()
	{
		this->!fk_AudioBase();
	}

	fk_AudioBase::!fk_AudioBase()
	{
		if(dFlg == true) delete pAudio;
		pAudio = nullptr;
	}

	double fk_AudioBase::Gain::get()
	{
		return GetP()->getGain();
	}

	void fk_AudioBase::Gain::set(double v)
	{
		GetP()->setGain(v);
	}

	int fk_AudioBase::QueueSize::get()
	{
		return GetP()->getQueueSize();
	}

	void fk_AudioBase::QueueSize::set(int v)
	{
		GetP()->setQueueSize(v);
	}

	bool fk_AudioBase::LoopMode::get()
	{
		return GetP()->getLoopMode();
	}

	void fk_AudioBase::LoopMode::set(bool mode)
	{
		GetP()->setLoopMode(mode);
	}

	fk_Vector^ fk_AudioBase::Position::get()
	{
		fk_Vector^ V = gcnew fk_Vector(GetP()->getPosition());
		return V;
	}

	void fk_AudioBase::Position::set(fk_Vector^ argP)
	{
		GetP()->setPosition(argP);
	}

	fk_Model^ fk_AudioBase::Model::get()	
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = GetP()->getModel();
		M->dFlg = false;
		return M;
	}

	void fk_AudioBase::Model::set(fk_Model^ argM)
	{
		if(!argM) return;
		GetP()->setModel(argM->GetP());
	}

	double fk_AudioBase::Distance::get()
	{
		return GetP()->getReferenceDist();
	}

	void fk_AudioBase::Distance::set(double d)
	{
		GetP()->setReferenceDist(d);
	}

	bool fk_AudioBase::SurroundMode::get()
	{
		return GetP()->getSurroundMode();
	}

	void fk_AudioBase::SurroundMode::set(bool argMode)
	{
		GetP()->setSurroundMode(argMode);
	}
	
	void fk_AudioBase::Pause(void)
	{
		GetP()->pause();
	}

	void fk_AudioBase::SetLoopArea(double argStart, double argEnd)
	{
		GetP()->setLoopArea(argStart, argEnd);
	}
	
	double fk_AudioBase::GetLoopStartTime(void)
	{
		return GetP()->getLoopStartTime();
	}
	
	double fk_AudioBase::GetLoopEndTime(void)
	{
		return GetP()->getLoopEndTime();
	}
	
	bool fk_AudioBase::Init(void)
	{
		return ::fk_AudioBase::init();
	}
	
	bool fk_AudioBase::GetInit(void)
	{
		return ::fk_AudioBase::getInit();
	}
	
	void fk_AudioBase::Sleep(double argTime)
	{
		::fk_AudioBase::sleep(argTime);
	}
	
	void fk_AudioBase::SetListenerModel(fk_Model^ argModel)
	{
		if(!argModel) return;
		::fk_AudioBase::setListenerModel(argModel->GetP());
	}
	
	fk_Model^ fk_AudioBase::GetListenerModel(void)
	{
		::fk_Model *pM = ::fk_AudioBase::getListenerModel();
		if(pM == nullptr) return nullptr;
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = ::fk_AudioBase::getListenerModel();
		M->dFlg = false;
		return M;
	}
}
