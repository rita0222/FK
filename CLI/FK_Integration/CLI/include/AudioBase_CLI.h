// AudioBase_CLI.h

#pragma once

#include <FK/Audio.h>
#include "Model_CLI.h"

namespace FK_CLI
{
	public ref class fk_AudioBase abstract {
	internal:
		::fk_AudioBase *pAudio;
		bool dFlg;

		::fk_AudioBase * GetP(void)
		{
			return pAudio;
		}

	public:
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
			pAudio = NULL;
		}

		virtual bool open(String^ name) abstract;
		virtual bool ready(void) abstract;
		virtual bool play(void) abstract;
		virtual double tell(void) abstract;
		virtual void seek(double time) abstract;
		virtual void stop(void) abstract;
		virtual void end(void) abstract;
		void pause(void);
		void setGain(double gain);
		double getGain(void);
		void setQueueSize(int size);
		int getQueueSize(void);
		void setLoopMode(bool mode);
		bool getLoopMode(void);
		void setLoopArea(double start, double end);
		double getLoopStartTime(void);
		double getLoopEndTime(void);
		void setPosition(fk_Vector^ pos);
		fk_Vector^ getPosition(void);
		void setModel(fk_Model^ model);
		fk_Model^ getModel(void);
		void setReferenceDist(double dist);
		double getReferenceDist(void);
		void setSurroundMode(bool mode);
		bool getSurroundMode(void);
		static bool init(void);
		static bool getInit(void);
		static void sleep(double time);
		static void setListenerModel(fk_Model^ model);
		static fk_Model^ getListenerModel(void);
	};
}
