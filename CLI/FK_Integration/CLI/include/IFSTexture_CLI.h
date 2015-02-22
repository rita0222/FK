// IFSTexture_CLI.h

#pragma once

#include <FK/IFSTexture.h>
#include "Texture_CLI.h"
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	public ref class fk_IFSTexture : fk_Texture {
	internal:

		::fk_IFSTexture * GetP(void);

	public:
		fk_IFSTexture();
		fk_IFSTexture(bool argNewFlg);
		fk_IFSTexture(fk_Image^ argImage);
		~fk_IFSTexture();
		!fk_IFSTexture();

		property fk_IndexFaceSet^ IFS {
			fk_IndexFaceSet^ get();
		}

		property double AnimationTime {
			void set(double);
		}
		
		property fk_BVHMotion^ BVHMotion {
			void set(fk_BVHMotion^);
		}
		
		property bool ConnectMode {
			void set(bool);
			bool get();
		}

		void Init(void);
		fk_TexCoord^ GetTextureCoord(int triID, int vertexID);
		void CloneShape(fk_IFSTexture^ IFSTexture);
		void SetTextureCoord(int triID, int vertexID, fk_TexCoord^ texCoord);
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID, bool contFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID);
		bool ReadMQOFile(String^ fileName, String^ objName);
		bool ReadD3DXFile(String^ fileName, String^ objName, int materialID);
		bool ReadD3DXFile(String^ fileName, String^ objName);
		bool MoveVPosition(int vertexID, const fk_Vector^ pos, int order);
		bool MoveVPosition(int vertexID, const fk_Vector^ pos);
		bool MoveVPosition(int vertexID, double x, double y, double z, int order);
		bool MoveVPosition(int vertexID, double x, double y, double z);
	};
}
