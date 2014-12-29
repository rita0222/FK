#include "../Vertex_CLI.h"
#include "../Half_CLI.h"

namespace FK_CLI {
	fk_Vector^ fk_Vertex::getPosition(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = GetP()->getPosition();
		return V;
	}

	fk_Half^ fk_Vertex::getOneHalf(void)
	{
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getOneHalf();
		H->dFlg = false;
		return H;
	}

	fk_Vector^ fk_Vertex::getNormal(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = GetP()->getNormal();
		return V;
	}
				
	double fk_Vertex::getDrawSize(void)
	{
		return GetP()->getDrawSize();
	}

	void fk_Vertex::setDrawSize(double argSize)
	{
		GetP()->setDrawSize(argSize);
	}
}
