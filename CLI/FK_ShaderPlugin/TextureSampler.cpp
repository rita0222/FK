#include "TextureSampler.h"
#include "GL/glew.h"


namespace FK_ShaderPlugin
{
	fk_TextureSampler::fk_TextureSampler() : fk_MeshTexture(true)
	{
	}

	fk_TextureSampler::fk_TextureSampler(fk_Image^ argImage) : fk_MeshTexture(argImage)
	{
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
	}

	void fk_TextureSampler::LoadTexture()
	{
		fk_Image^ image = this->Image;
		if (image == nullptr) return;

		fk_Dimension^	bufSize = image->BufferSize;
		GLuint	tmpId = id;

		if (tmpId != 0) glDeleteTextures(1, &tmpId);
		glGenTextures(1, &tmpId);
		glBindTexture(GL_TEXTURE_2D, tmpId);

		id = tmpId;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufSize->w, bufSize->h,
			0, GL_RGBA, GL_UNSIGNED_BYTE, image->Buffer);

		glBindTexture(GL_TEXTURE_2D, 0);

		return;
	}
}
