#include "Vertex_CLI.h"
#include "Half_CLI.h"

namespace FK_CLI {
	fk_Vector^ fk_Vertex::getPosition(void)
	{
		return gcnew fk_Vector(GetP()->getPosition());
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
		return gcnew fk_Vector(GetP()->getNormal());
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
