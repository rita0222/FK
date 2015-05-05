// Operation_CLI.h

#pragma once

#include <FK/Operation.h>
#include "DataAccess_CLI.h"

namespace FK_CLI
{
	public ref class fk_Operation : fk_DataAccess {
	internal:
		::fk_Operation * GetP(void);

	public:
		fk_Operation(bool argNewFlg);
		~fk_Operation();
		!fk_Operation();

		property bool HistoryMode {
			void set(bool);
			bool get();
		}

		property bool TesselateMode {
			void set(bool);
			bool get();
		}
		
		fk_Vertex^	MakeVertex(fk_Vector^ P);
		bool		DeleteVertex(fk_Vertex^ V);
		bool		MoveVertex(fk_Vertex^ V, fk_Vector^ P);
		fk_Edge^	MakeEdge(fk_Vertex^ V_1, fk_Vertex^ V_2,
							 fk_Half^ H_11, fk_Half^ H_12, fk_Half^ H_21, fk_Half^ H_22);
		fk_Edge^	MakeEdge(fk_Vertex^ V_1, fk_Vertex^ V_2);
		bool		DeleteEdge(fk_Edge^ E);
		fk_Loop^	MakeLoop(fk_Half ^H);
		bool		DeleteLoop(fk_Loop^ L);
		fk_Edge^	SeparateLoop(fk_Half^ H1, fk_Half^ H2);
		bool		UniteLoop(fk_Edge^ E);
		fk_Vertex^	SeparateEdge(fk_Edge^ E);
		bool		UniteEdge(fk_Vertex^ V);
		void		NegateBody(void);
		void		SetHistoryMark(void);
		bool		UndoHistory(void);
		bool		RedoHistory(void);
	};
}
