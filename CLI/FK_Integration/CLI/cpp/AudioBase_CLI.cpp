#include "AudioBase_CLI.h"

namespace FK_CLI {

	void fk_AudioBase::pause(void)
	{
		GetP()->pause();
	}
	
	void fk_AudioBase::setGain(double argGain)
	{
		GetP()->setGain(argGain);
	}
	
	double fk_AudioBase::getGain(void)
	{
		return GetP()->getGain();
	}
	
	void fk_AudioBase::setQueueSize(int argSize)
	{
		GetP()->setQueueSize(argSize);
	}
	
	int fk_AudioBase::getQueueSize(void)
	{
		return GetP()->getQueueSize();
	}
	
	void fk_AudioBase::setLoopMode(bool argMode)
	{
		GetP()->setLoopMode(argMode);
	}
		
	bool fk_AudioBase::getLoopMode(void)
	{
		return GetP()->getLoopMode();
	}
	
	void fk_AudioBase::setLoopArea(double argStart, double argEnd)
	{
		GetP()->setLoopArea(argStart, argEnd);
	}
	
	double fk_AudioBase::getLoopStartTime(void)
	{
		return GetP()->getLoopStartTime();
	}
	
	double fk_AudioBase::getLoopEndTime(void)
	{
		return GetP()->getLoopEndTime();
	}
	
	void fk_AudioBase::setPosition(fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->setPosition(*argPos->pVec);
	}
	
	fk_Vector^ fk_AudioBase::getPosition(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = GetP()->getPosition();
		return V;
	}
	
	void fk_AudioBase::setModel(fk_Model^ argModel)
	{
		if(!argModel) return;
		GetP()->setModel(argModel->GetP());
	}
	
	fk_Model^ fk_AudioBase::getModel(void)
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = GetP()->getModel();
		M->dFlg = false;
		return M;
	}
	
	void fk_AudioBase::setReferenceDist(double argDist)
	{
		GetP()->setReferenceDist(argDist);
	}
	
	double fk_AudioBase::getReferenceDist(void)
	{
		return GetP()->getReferenceDist();
	}
	
	void fk_AudioBase::setSurroundMode(bool argMode)
	{
		GetP()->setSurroundMode(argMode);
	}
	
	bool fk_AudioBase::getSurroundMode(void)
	{
		return GetP()->getSurroundMode();
	}
	
	bool fk_AudioBase::init(void)
	{
		return ::fk_AudioBase::init();
	}
	
	bool fk_AudioBase::getInit(void)
	{
		return ::fk_AudioBase::getInit();
	}
	
	void fk_AudioBase::sleep(double argTime)
	{
		::fk_AudioBase::sleep(argTime);
	}
	
	void fk_AudioBase::setListenerModel(fk_Model^ argModel)
	{
		if(!argModel) return;
		::fk_AudioBase::setListenerModel(argModel->GetP());
	}
	
	fk_Model^ fk_AudioBase::getListenerModel(void)
	{
		::fk_Model *pM = ::fk_AudioBase::getListenerModel();
		if(pM == nullptr) return nullptr;
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = ::fk_AudioBase::getListenerModel();
		M->dFlg = false;
		return M;
	}
}
