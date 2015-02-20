// DataAccess_CLI.h

#pragma once

#include <FK/DataAccess.h>
#include "Reference_CLI.h"

namespace FK_CLI
{
	public ref class fk_DataAccess : fk_Reference {
	internal:
		::fk_DataAccess * GetP(void)
		{
			return (::fk_DataAccess *)(pBase);
		}

	public:
		fk_DataAccess::fk_DataAccess(bool argNewFlg) : fk_Reference(false)
		{
		}

		fk_DataAccess::~fk_DataAccess()
		{
			this->!fk_DataAccess();
		}

		fk_DataAccess::!fk_DataAccess()
		{
		}

		property int VNum {
			int get()
			{
				return GetP()->getVNum();
			}
		}

		property int HNum {
			int get()
			{
				return GetP()->getHNum();
			}
		}

		property int ENum {
			int get()
			{
				return GetP()->getENum();
			}
		}

		property int LNum {
			int get()
			{
				return GetP()->getLNum();
			}
		}
		
		bool CheckDB(void);
		bool CheckTopology(void);
		bool ExistVertex(fk_Vertex^ vertex);
		bool ExistVertex(int ID);
		bool ExistHalf(fk_Half^ half);
		bool ExistHalf(int ID);
		bool ExistEdge(fk_Edge^ edge);
		bool ExistEdge(int ID);
		bool ExistLoop(fk_Loop^ loop);
		bool ExistLoop(int ID);
		fk_Vertex^ GetVData(int ID);
		fk_Half^ GetHData(int ID);
		fk_Edge^ GetEData(int ID);
		fk_Loop^ GetLData(int ID);
		fk_Vertex^ GetNextV(fk_Vertex^ vertex);
		fk_Half^ GetNextH(fk_Half^ half);
		fk_Edge^ GetNextE(fk_Edge^ edge);
		fk_Loop^ GetNextL(fk_Loop^ loop);
		fk_Vertex^ GetLastV(void);
		fk_Half^ GetLastH(void);
		fk_Edge^ GetLastE(void);
		fk_Loop^ GetLastL(void);
		array<fk_Vertex^>^ GetVertexList(void);
		array<fk_Half^>^ GetHalfList(void);
		array<fk_Edge^>^ GetEdgeList(void);
		array<fk_Loop^>^ GetLoopList(void);
	};
}
