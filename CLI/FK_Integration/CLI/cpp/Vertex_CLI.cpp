#include "Vertex_CLI.h"
#include "Half_CLI.h"

namespace FK_CLI {

	::fk_Vertex * fk_Vertex::GetP(void)
	{
		return (::fk_Vertex *)(pBase);
	}

	fk_Vertex::fk_Vertex(bool argNewFlg) : fk_TopologyMaterial(false)
	{
	}

	fk_Vertex::~fk_Vertex()
	{
		this->!fk_Vertex();
	}

	fk_Vertex::!fk_Vertex()
	{
	}

	fk_Vector^ fk_Vertex::Position::get(void)
	{
		return gcnew fk_Vector(GetP()->getPosition());
	}

	fk_Vector^ fk_Vertex::Normal::get(void)
	{
		return gcnew fk_Vector(GetP()->getNormal());
	}
				
	fk_Half^ fk_Vertex::OneHalf::get(void)
	{
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getOneHalf();
		H->dFlg = false;
		return H;
	}

	double fk_Vertex::DrawSize::get(void)
	{
		return GetP()->getDrawSize();
	}

	void fk_Vertex::DrawSize::set(double argSize)
	{
		GetP()->setDrawSize(argSize);
	}
}
