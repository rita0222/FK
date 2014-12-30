// Operation_CLI.h

#pragma once

#include <FK/Operation.h>
#include "DataAccess_CLI.h"

namespace FK_CLI
{
	public ref class fk_Operation : fk_DataAccess {
	internal:
		::fk_Operation * GetP(void)
		{
			return (::fk_Operation *)(pBase);
		}

	public:
		fk_Operation::fk_Operation(bool argNewFlg) : fk_DataAccess(false)
		{
		}

		fk_Operation::~fk_Operation()
		{
			this->!fk_Operation();
		}

		fk_Operation::!fk_Operation()
		{
		}

		fk_Vertex^ makeVertex(fk_Vector^ P);
		bool deleteVertex(fk_Vertex^ V);
		bool moveVertex(fk_Vertex^ V, fk_Vector^ P);
		fk_Edge^ makeEdge(fk_Vertex^ V_1, fk_Vertex^ V_2,
						  fk_Half^ H_11, fk_Half^ H_12, fk_Half^ H_21, fk_Half^ H_22);
		fk_Edge^ makeEdge(fk_Vertex^ V_1, fk_Vertex^ V_2);
		bool deleteEdge(fk_Edge^ E);
		fk_Loop^ makeLoop(fk_Half ^H);
		bool deleteLoop(fk_Loop^ L);
		fk_Edge^ separateLoop(fk_Half^ H1, fk_Half^ H2);
		bool uniteLoop(fk_Edge^ E);
		fk_Vertex^ separateEdge(fk_Edge^ E);
		bool uniteEdge(fk_Vertex^ V);
		void negateBody(void);
		void setHistoryMode(bool mode);
		bool getHistoryMode(void);
		void setHistoryMark(void);
		bool undoHistory(void);
		bool redoHistory(void);
		void setTesselateMode(bool mode);
		bool getTesselateMode(void);
	};
}
