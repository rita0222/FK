#include "Edge_CLI.h"
#include "Half_CLI.h"

namespace FK_CLI {
	fk_Half^ fk_Edge::LeftHalf::get()
	{
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getLeftHalf();
		H->dFlg = false;
		return H;
	}
  
	fk_Half^ fk_Edge::RightHalf::get()
	{
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getRightHalf();
		H->dFlg = false;
		return H;
	}

	double fk_Edge::DrawWidth::get()
	{
		return GetP()->getDrawWidth();
	}

	void fk_Edge::DrawWidth::set(double argW)
	{
		GetP()->setDrawWidth(argW);
	}
}
