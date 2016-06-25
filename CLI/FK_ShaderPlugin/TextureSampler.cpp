#include "TextureSampler.h"
#include "GL/glew.h"


namespace FK_ShaderPlugin
{
	fk_TextureSampler::fk_TextureSampler() : fk_MeshTexture(true)
	{
		loaded = false;
		Init();
	}

	fk_TextureSampler::fk_TextureSampler(fk_Image^ argImage) : fk_MeshTexture(argImage)
	{
		loaded = false;
		Init();
	}

	fk_TextureSampler::~fk_TextureSampler()
	{
		this->!fk_TextureSampler();
	}

	fk_TextureSampler::!fk_TextureSampler()
	{
	}

	void fk_TextureSampler::Init()
	{
		if (!loaded)
		{
			GLuint	tmpId = id;
			if (tmpId != 0) glDeleteTextures(1, &tmpId);
		}

		id = 0;
		loaded = false;
	}

	bool fk_TextureSampler::BindTexture(bool forceLoad)
	{
		if (this->Image == nullptr) return false;

		fk_Dimension^	bufSize = this->Image->BufferSize;
		GLuint			tmpId = id;

		if (!loaded || forceLoad)
		{
			if (tmpId != 0) glDeleteTextures(1, &tmpId);
			glGenTextures(1, &tmpId);
		}

		if (tmpId == 0) return false;

		glBindTexture(GL_TEXTURE_2D, tmpId);

		id = tmpId;

		GLint wrapModeGl = WrapMode == fk_TexWrapMode::REPEAT ? GL_REPEAT : GL_CLAMP_TO_EDGE;
		GLint rendMode = RendMode == fk_TexRendMode::NORMAL ? GL_NEAREST : GL_LINEAR;
		GLint texMode;
		switch (TextureMode) {
		case fk_TexMode::REPLACE:
			texMode = GL_REPLACE;
			break;
		case fk_TexMode::MODULATE:
			texMode = GL_MODULATE;
			break;
		case fk_TexMode::DECAL:
			texMode = GL_DECAL;
			break;
		}

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, texMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeGl);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeGl);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, rendMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, rendMode);

		if (!loaded || forceLoad)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufSize->w, bufSize->h,
				0, GL_RGBA, GL_UNSIGNED_BYTE, this->Image->Buffer);
			loaded = true;
		}

		return true;
	}
}
