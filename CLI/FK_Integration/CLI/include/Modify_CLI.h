// Modify_CLI.h

#pragma once

#include <FK/Modify.h>
#include "Operation_CLI.h"

namespace FK_CLI
{
	public ref class fk_Modify : fk_Operation {
	internal:
		::fk_Modify * GetP(void)
		{
			return (::fk_Modify *)(pBase);
		}

	public:
		fk_Modify::fk_Modify(bool argNewFlg) : fk_Operation(false)
		{
		}

		fk_Modify::~fk_Modify()
		{
			this->!fk_Modify();
		}

		fk_Modify::!fk_Modify()
		{
		}

		fk_Loop^ removeVertexInLoop(fk_Vertex ^V);
		bool contractEdge(fk_Edge ^E, bool R);
		bool contractEdge(fk_Edge ^E);
		bool contractEdge(fk_Edge ^E, fk_Vector ^P, bool R);
		bool contractEdge(fk_Edge ^E, fk_Vector ^P);
		bool checkContract(fk_Edge ^E);
		fk_Loop^ makePolygon(array<fk_Vector^>^ array, bool openFlg, bool initFlg);
		fk_Loop^ makePolygon(array<fk_Vector^>^ array, bool openFlg);
		fk_Loop^ pushPolygon(array<fk_Vector^>^ array, bool openFlg);
		fk_Loop^ pushPolygon(array<fk_Vector^>^ array);
		void pushPolygonVertex(fk_Vector ^pos, bool openFlg);
		void makePoint(array<fk_Vector^>^ array);
		fk_Vertex^ pushPointVertex(fk_Vector ^pos);
		void makeLines(array<fk_Vector^>^ array);
		fk_Edge^ pushLines(fk_Vector ^pos1, fk_Vector ^pos2);
		bool setLinePos(int ID, fk_Vector ^pos);
		bool setLinePos(int edgeID, int vertexID, fk_Vector^ pos);
		bool changeLine(int edgeID, fk_Vector^ pos1, fk_Vector^ pos2);
		void makeBlock(double x, double y, double z);
		void setBlockSize(double x, double y, double z);
		void setBlockSize(double length, fk_Axis axis);
		void setBlockScale(double scale);
		void setBlockScale(double scale, fk_Axis axis);
		void setBlockScale(double x, double y, double z);
		void makeCircle(int div, double rad);
		void setCircleRadius(double rad);
		void setCircleDivide(int div);
		void setCircleScale(double scale);
		void makeSphere(int div, double rad);
		void setSphereRadius(double rad);
		void setSphereDivide(int div);
		void setSphereScale(double scale);
		void makePrism(int div, double top, double bottom, double height);
		void setPrismDivide(int div);
		void setPrismTopRadius(double top);
		void setPrismBottomRadius(double bottom);
		void setPrismHeight(double height);
		void makeCone(int div, double rad, double height);
		void setConeDivide(int div);
		void setConeRadius(double rad);
		void setConeHeight(double height);
		bool moveVPosition(int vertexID, fk_Vector ^pos, int order);
		bool moveVPosition(int vertexID, fk_Vector ^pos);
		bool moveVPosition(int vertexID, double x, double y, double z, int order);
		bool moveVPosition(int vertexID, double x, double y, double z);
		void subdivShape(int count);
	};
}
