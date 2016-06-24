#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace FK_CLI;

namespace FK_ShaderPlugin
{
	public ref class fk_TextureSampler : fk_MeshTexture
	{
	public:
		fk_TextureSampler();
		fk_TextureSampler(fk_Image^ image);

		~fk_TextureSampler();
		!fk_TextureSampler();

		void Init(void);

	private:
		// このクラスで利用できないプロパティです。
		property int TriNum {
			void set(int) {};
			int get() { return 0; };
		}

		// このクラスで利用できない関数です。
		bool SetTextureCoord(int tID, int vID, double x, double y) { return false; };
		bool SetTextureCoord(int tID, int vID, fk_TexCoord^ coord) { return false; };
		bool SetTriTextureCoord(int tID, IEnumerable<fk_TexCoord^>^ array) { return false; };
		fk_TexCoord^ GetTextureCoord(int tID, int vID) { return nullptr; };
		bool SetVertexPos(int tID, int vID, double x, double y, double z) { return false; };
		bool SetVertexPos(int tID, int vID, fk_Vector^ pos) { return false; };
		bool SetTriPos(int tID, IEnumerable<fk_Vector^>^ array) { return false; };
		fk_Vector^ GetVertexPos(int tID, int vID) { return nullptr; };
		void PutIndexFaceSet(fk_IndexFaceSet^ ifs) {};
		bool ReadMQOFile(String^ fileName, String^ objName, bool contFlg) { return false; };
		bool ReadMQOFile(String^ fileName, String^ objName) { return false; };

		void LoadTexture(void);

		UInt32	id;
	};
}
