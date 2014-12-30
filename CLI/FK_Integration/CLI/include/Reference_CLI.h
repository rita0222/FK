// Shape_CLI.h

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
		::fk_ReferenceL3 * GetP(void)
		{
			return (::fk_ReferenceL3 *)(pBase);
		}

	public:
		fk_Reference::fk_Reference(bool argNewFlg) : fk_Shape(false)
		{
		}

		fk_Reference::~fk_Reference()
		{
			this->!fk_Reference();
		}

		fk_Reference::!fk_Reference()
		{
		}

		// from ReferenceL1
		fk_Half^ getOneHOnV(fk_Vertex^ V);
		fk_Edge^ getOneEOnV(fk_Vertex^ V);
		fk_Vertex^ getVOnH(fk_Half^ H);
		fk_Half^ getMateHOnH(fk_Half^ H);
		fk_Edge^ getParentEOnH(fk_Half^ H);
		fk_Loop^ getParentLOnH(fk_Half^ H);
		fk_Vertex^ getRightVOnE(fk_Edge^ E);
		fk_Vertex^ getLeftVOnE(fk_Edge^ E);
		fk_Half^ getRightHOnE(fk_Edge^ E);
		fk_Half^ getLeftHOnE(fk_Edge^ E);
		fk_Loop^ getRightLOnE(fk_Edge^ E);
		fk_Loop^ getLeftLOnE(fk_Edge^ E);
		fk_EdgeStatus getEdgeStatus(fk_Edge^ E);
		fk_Vertex^ getOneVOnL(fk_Loop^ L);
		fk_Half^ getOneHOnL(fk_Loop^ L);
		fk_Edge^ getOneEOnL(fk_Loop^ L);

		// from ReferenceL2
		fk_Vertex^ getOneNeighborVOnV(fk_Vertex^ V);
		array<fk_Half^>^ getAllHOnV(fk_Vertex^ V);
		array<fk_Edge^>^ getAllEOnV(fk_Vertex^ V);
		array<fk_Loop^>^ getAllLOnV(fk_Vertex^ V);
		int getENumOnV(fk_Vertex^ V);
		array<fk_Vertex^>^ getAllVOnL(fk_Loop^ L);
		array<fk_Half^>^ getAllHOnL(fk_Loop^ L);
		array<fk_Edge^>^ getAllEOnL(fk_Loop^ L);
		fk_Loop^ getOneNeighborLOnL(fk_Loop^ L);
		fk_Loop^ getNeighborLOnLH(fk_Loop^ L, fk_Half^ H);
		int getVNumOnL(fk_Loop^ L);

		// from ReferenceL3
		array<fk_Vertex^>^ getAllNeighborVOnV(fk_Vertex^ V);
		array<fk_Edge^>^ getEOnVV(fk_Vertex^ V1, fk_Vertex^ V2);
		fk_Loop^ getOneLOnV(fk_Vertex^ V);
		fk_Loop^ getNeighborLOnLE(fk_Loop^ L, fk_Edge^ E);
		array<fk_Loop^>^ getAllNeighborLOnL(fk_Loop^ L);
	};
}
