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

		::fk_AudioBase * GetP(void);

	public:
		fk_AudioBase();
		~fk_AudioBase();
		!fk_AudioBase();

		property double Gain {
			double get();
			void set(double);
		}

		property int QueueSize {
			int get();
			void set(int);
		}

		property bool LoopMode {
			bool get();
			void set(bool);
		}

		property fk_Vector^ Position {
			fk_Vector^ get();
			void set(fk_Vector^);
		}
					
		property fk_Model^ Model {
			fk_Model^ get();
			void set(fk_Model^);
		}

		property double Distance {
			double get();
			void set(double);
		}

		property bool SurroundMode {
			bool get();
			void set(bool);
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
