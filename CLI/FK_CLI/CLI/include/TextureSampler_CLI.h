#pragma once

#include "MeshTexture_CLI.h"

//using namespace System;
//using namespace System::Collections::Generic;

namespace FK_CLI
{
	// モデルの描画モードを表す列挙型
	public enum class fk_TexWrapMode {
		REPEAT,
		CLAMP,
	};

	// フレームバッファのサンプリングソースを表す列挙型
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
		// このクラスで利用できないプロパティです。
		property int TriNum;

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

		// フィールド
		UInt32			id;
		bool			loaded;
	};
}
