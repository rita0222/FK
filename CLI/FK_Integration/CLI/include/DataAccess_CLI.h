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

		bool checkDB(void);
		bool checkTopology(void);
		bool existVertex(fk_Vertex^ vertex);
		bool existVertex(int ID);
		bool existHalf(fk_Half^ half);
		bool existHalf(int ID);
		bool existEdge(fk_Edge^ edge);
		bool existEdge(int ID);
		bool existLoop(fk_Loop^ loop);
		bool existLoop(int ID);
		fk_Vertex^ getVData(int ID);
		fk_Half^ getHData(int ID);
		fk_Edge^ getEData(int ID);
		fk_Loop^ getLData(int ID);
		fk_Vertex^ getNextV(fk_Vertex^ vertex);
		fk_Half^ getNextH(fk_Half^ half);
		fk_Edge^ getNextE(fk_Edge^ edge);
		fk_Loop^ getNextL(fk_Loop^ loop);
		fk_Vertex^ getLastV(void);
		fk_Half^ getLastH(void);
		fk_Edge^ getLastE(void);
		fk_Loop^ getLastL(void);
		int getVNum(void);
		int getHNum(void);
		int getENum(void);
		int getLNum(void);
		array<fk_Vertex^>^ getVertexList(void);
		array<fk_Half^>^ getHalfList(void);
		array<fk_Edge^>^ getEdgeList(void);
		array<fk_Loop^>^ getLoopList(void);
	};
}
