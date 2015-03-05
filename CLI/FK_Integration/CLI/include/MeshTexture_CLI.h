// MeshTexture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"
#include "Vector_CLI.h"
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	public ref class fk_MeshTexture : fk_Texture {
	internal:
		::fk_MeshTexture * GetP(void);

	public:
		fk_MeshTexture();
		fk_MeshTexture(bool argNewFlg);
		fk_MeshTexture(fk_Image^ argImage);
		~fk_MeshTexture();
		!fk_MeshTexture();

		property int TriNum {
			void set(int);
			int get();
		}

		void Init(void);
		bool SetTextureCoord(int triID, int vertexID, double x, double y);
		bool SetTextureCoord(int triID, int vertexID, fk_TexCoord^ color);
		bool SetTriTextureCoord(int triID, array<fk_TexCoord^>^ array);
		fk_TexCoord^ GetTextureCoord(int triID, int vertexID);
		bool SetVertexPos(int triID, int vertexID, double x, double y, double z);
		bool SetVertexPos(int triID, int vertexID, fk_Vector^ pos);
		bool SetTriPos(int triID, array<fk_Vector^>^ array);
		fk_Vector^ GetVertexPos(int triID, int vertexID);
		void PutIndexFaceSet(fk_IndexFaceSet^ IFS);
		bool ReadMQOFile(String^ fileName, String^ objName, bool contFlg);
		bool ReadMQOFile(String^ fileName, String^ objName);
	};
}
