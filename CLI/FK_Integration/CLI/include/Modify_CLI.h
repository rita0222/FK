// Modify_CLI.h

#pragma once

#include <FK/Modify.h>
#include "Operation_CLI.h"

namespace FK_CLI
{
	public ref class fk_Modify : fk_Operation {
	internal:
		::fk_Modify * GetP(void);

	public:
		fk_Modify(bool argNewFlg);
		~fk_Modify();
		!fk_Modify();

		fk_Loop^ RemoveVertexInLoop(fk_Vertex ^V);
		bool ContractEdge(fk_Edge ^E, bool R);
		bool ContractEdge(fk_Edge ^E);
		bool ContractEdge(fk_Edge ^E, fk_Vector ^P, bool R);
		bool ContractEdge(fk_Edge ^E, fk_Vector ^P);
		bool CheckContract(fk_Edge ^E);
		fk_Loop^ MakePolygon(array<fk_Vector^>^ array, bool openFlg, bool initFlg);
		fk_Loop^ MakePolygon(array<fk_Vector^>^ array, bool openFlg);
		fk_Loop^ PushPolygon(array<fk_Vector^>^ array, bool openFlg);
		fk_Loop^ PushPolygon(array<fk_Vector^>^ array);
		void PushPolygonVertex(fk_Vector ^pos, bool openFlg);
		void MakePoint(array<fk_Vector^>^ array);
		fk_Vertex^ PushPointVertex(fk_Vector ^pos);
		void MakeLines(array<fk_Vector^>^ array);
		fk_Edge^ PushLines(fk_Vector ^pos1, fk_Vector ^pos2);
		bool SetLinePos(int ID, fk_Vector ^pos);
		bool SetLinePos(int edgeID, int vertexID, fk_Vector^ pos);
		bool ChangeLine(int edgeID, fk_Vector^ pos1, fk_Vector^ pos2);
		void MakeBlock(double x, double y, double z);
		void SetBlockSize(double x, double y, double z);
		void SetBlockSize(double length, fk_Axis axis);
		void SetBlockScale(double scale);
		void SetBlockScale(double scale, fk_Axis axis);
		void SetBlockScale(double x, double y, double z);
		void MakeCircle(int div, double rad);
		void SetCircleRadius(double rad);
		void SetCircleDivide(int div);
		void SetCircleScale(double scale);
		void MakeSphere(int div, double rad);
		void SetSphereRadius(double rad);
		void SetSphereDivide(int div);
		void SetSphereScale(double scale);
		void MakePrism(int div, double top, double bottom, double height);
		void SetPrismDivide(int div);
		void SetPrismTopRadius(double top);
		void SetPrismBottomRadius(double bottom);
		void SetPrismHeight(double height);
		void MakeCone(int div, double rad, double height);
		void SetConeDivide(int div);
		void SetConeRadius(double rad);
		void SetConeHeight(double height);
		bool MoveVPosition(int vertexID, fk_Vector ^pos, int order);
		bool MoveVPosition(int vertexID, fk_Vector ^pos);
		bool MoveVPosition(int vertexID, double x, double y, double z, int order);
		bool MoveVPosition(int vertexID, double x, double y, double z);
		void SubDivShape(int count);
	};
}
