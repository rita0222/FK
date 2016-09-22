#pragma once

#include "MeshTexture_CLI.h"

//using namespace System;
//using namespace System::Collections::Generic;

namespace FK_CLI
{
	// ���f���̕`�惂�[�h��\���񋓌^
	public enum class fk_TexWrapMode {
		REPEAT,
		CLAMP,
	};

	// �t���[���o�b�t�@�̃T���v�����O�\�[�X��\���񋓌^
	public enum class fk_SamplerSource {
		TEXTURE_IMAGE,
		COLOR_BUFFER,
		DEPTH_BUFFER,
	};

	public ref class fk_TextureSampler : fk_MeshTexture
	{
	public:
		fk_TextureSampler();
		fk_TextureSampler(fk_Image^ image);

		~fk_TextureSampler();
		!fk_TextureSampler();

		property fk_TexWrapMode WrapMode;
		property fk_SamplerSource SamplerSource;

		void Init(void);

	internal:
		bool BindTexture(bool forceLoad);

	private:
		// ���̃N���X�ŗ��p�ł��Ȃ��v���p�e�B�ł��B
		property int TriNum;

		// ���̃N���X�ŗ��p�ł��Ȃ��֐��ł��B
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

		// �t�B�[���h
		UInt32			id;
		bool			loaded;
	};
}
