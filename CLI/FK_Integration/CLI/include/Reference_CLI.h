// Reference_CLI.h

#pragma once

#include <FK/Reference.h>
#include "Shape_CLI.h"
#include "Vertex_CLI.h"
#include "Half_CLI.h"
#include "Edge_CLI.h"
#include "Loop_CLI.h"

namespace FK_CLI
{
	public ref class fk_Reference : fk_Shape {
	internal:
		::fk_ReferenceL3 * GetP(void);

	public:
		fk_Reference::fk_Reference(bool argNewFlg);
		fk_Reference::~fk_Reference();
		fk_Reference::!fk_Reference();

		// from ReferenceL1
		fk_Half^			GetOneHOnV(fk_Vertex^ V);
		fk_Edge^			GetOneEOnV(fk_Vertex^ V);
		fk_Vertex^			GetVOnH(fk_Half^ H);
		fk_Half^			GetMateHOnH(fk_Half^ H);
		fk_Edge^			GetParentEOnH(fk_Half^ H);
		fk_Loop^			GetParentLOnH(fk_Half^ H);
		fk_Vertex^			GetRightVOnE(fk_Edge^ E);
		fk_Vertex^			GetLeftVOnE(fk_Edge^ E);
		fk_Half^			GetRightHOnE(fk_Edge^ E);
		fk_Half^			GetLeftHOnE(fk_Edge^ E);
		fk_Loop^			GetRightLOnE(fk_Edge^ E);
		fk_Loop^			GetLeftLOnE(fk_Edge^ E);
		fk_EdgeStatus		GetEdgeStatus(fk_Edge^ E);
		fk_Vertex^			GetOneVOnL(fk_Loop^ L);
		fk_Half^			GetOneHOnL(fk_Loop^ L);
		fk_Edge^			GetOneEOnL(fk_Loop^ L);

		// from ReferenceL2
		fk_Vertex^			GetOneNeighborVOnV(fk_Vertex^ V);
		array<fk_Half^>^	GetAllHOnV(fk_Vertex^ V);
		array<fk_Edge^>^	GetAllEOnV(fk_Vertex^ V);
		array<fk_Loop^>^	GetAllLOnV(fk_Vertex^ V);
		int					GetENumOnV(fk_Vertex^ V);
		array<fk_Vertex^>^	GetAllVOnL(fk_Loop^ L);
		array<fk_Half^>^	GetAllHOnL(fk_Loop^ L);
		array<fk_Edge^>^	GetAllEOnL(fk_Loop^ L);
		fk_Loop^			GetOneNeighborLOnL(fk_Loop^ L);
		fk_Loop^			GetNeighborLOnLH(fk_Loop^ L, fk_Half^ H);
		int					GetVNumOnL(fk_Loop^ L);

		// from ReferenceL3
		array<fk_Vertex^>^	GetAllNeighborVOnV(fk_Vertex^ V);
		array<fk_Edge^>^	GetEOnVV(fk_Vertex^ V1, fk_Vertex^ V2);
		fk_Loop^			GetOneLOnV(fk_Vertex^ V);
		fk_Loop^			GetNeighborLOnLE(fk_Loop^ L, fk_Edge^ E);
		array<fk_Loop^>^	GetAllNeighborLOnL(fk_Loop^ L);
	};
}
