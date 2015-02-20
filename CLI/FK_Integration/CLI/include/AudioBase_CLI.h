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
			pAudio = nullptr;
		}

		property double Gain {
			double get()
			{
				return GetP()->getGain();
			}

			void set(double v)
			{
				GetP()->setGain(v);
			}
		}

		property int QueueSize {
			int get()
			{
				return GetP()->getQueueSize();
			}

			void set(int v)
			{
				GetP()->setQueueSize(v);
			}
		}

		property bool LoopMode {
			bool get()
			{
				return GetP()->getLoopMode();
			}

			void set(bool mode)
			{
				GetP()->setLoopMode(mode);
			}
		}

		property fk_Vector^ Position {
			fk_Vector^ get()
			{
				fk_Vector^ V = gcnew fk_Vector();
				*V->pVec = GetP()->getPosition();
				return V;
			}

			void set(fk_Vector^ argP)
			{
				GetP()->setPosition(*argP->pVec);
			}
		}
					
		property fk_Model^ Model {
			fk_Model^ get()
			{
				fk_Model^ M = gcnew fk_Model(false);
				M->pBase = GetP()->getModel();
				M->dFlg = false;
				return M;
			}

			void set(fk_Model^ argM)
			{
				if(!argM) return;
				GetP()->setModel(argM->GetP());
			}
		}

		property double Dist {
			double get()
			{
				return GetP()->getReferenceDist();
			}

			void set(double d)
			{
				GetP()->setReferenceDist(d);
			}
		}

		property bool SurroundMode {
			bool get()
			{
				return GetP()->getSurroundMode();
			}

			void set(bool argMode)
			{
				GetP()->setSurroundMode(argMode);
			}
		}					

		virtual bool Open(String^ name) abstract;
		virtual bool Ready(void) abstract;
		virtual bool Play(void) abstract;
		virtual double Tell(void) abstract;
		virtual void Seek(double time) abstract;
		virtual void Stop(void) abstract;
		virtual void End(void) abstract;

		void SetLoopArea(double start, double end);
		double GetLoopStartTime(void);
		double GetLoopEndTime(void);
		void Pause(void);

		static bool Init(void);
		static bool GetInit(void);
		static void Sleep(double time);
		static void SetListenerModel(fk_Model^ model);
		static fk_Model^ GetListenerModel(void);
	};
}
