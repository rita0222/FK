/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/

#include <FK/TextureSampler.h>

using namespace FK;

fk_TextureSampler::fk_TextureSampler()
	: fk_Texture(), samplerSource(FK_TEXTURE_IMAGE)
{
	setTexWrapMode(FK_TEX_WRAP_REPEAT);
	init();
}

fk_TextureSampler::fk_TextureSampler(fk_Image *argImage)
	: fk_Texture(argImage), samplerSource(FK_TEXTURE_IMAGE)
{
	setTexWrapMode(FK_TEX_WRAP_REPEAT);
	init();
}

fk_TextureSampler::~fk_TextureSampler()
{
}

void fk_TextureSampler::init()
{
	fk_Image *image = getImage();
	if(image == nullptr) return;

	GLuint tmpID = image->GetTexID();
	if (tmpID != 0) {
		glDeleteTextures(1, &tmpID);
		image->SetTexID(0);
	}
}

bool fk_TextureSampler::BindTexture(bool forceLoad)
{
	bool 		loaded = true;
	fk_Image	*image = getImage();
	if (image == nullptr) return false;

	const fk_Dimension	*bufSize = image->getBufferSize();
	if(bufSize == nullptr) return false;

	GLuint			id = image->GetTexID();

	if(id == 0) {
		glGenTextures(1, &id);
		image->SetTexID(id);
		loaded = false;
	}

	glBindTexture(GL_TEXTURE_2D, id);

	GLint tmpWrapModeGl = (getTexWrapMode() == FK_TEX_WRAP_REPEAT) ? GL_REPEAT : GL_CLAMP_TO_EDGE;
	GLint tmpRendMode = (getTexRendMode() == FK_TEX_REND_NORMAL) ? GL_NEAREST : GL_LINEAR;
	GLint tmpTexMode = GL_REPLACE;

	switch (getTextureMode()) {
	  case FK_TEX_REPLACE:
		tmpTexMode = GL_REPLACE;
		break;

#ifndef OPENGL4
	  case FK_TEX_MODULATE:
		tmpTexMode = GL_MODULATE;
		break;
	  case FK_TEX_DECAL:
		tmpTexMode = GL_DECAL;
		break;
#endif

	  default:
		break;
	}

#ifndef OPENGL4
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, tmpTexMode);
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tmpWrapModeGl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tmpWrapModeGl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tmpRendMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tmpRendMode);

	if (loaded == false || forceLoad) {
		if (samplerSource == FK_TEXTURE_IMAGE) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufSize->w, bufSize->h,
						 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getBufPointer());
		}  else if (samplerSource == FK_COLOR_BUFFER) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufSize->w, bufSize->h,
						 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, bufSize->w, bufSize->h,
						 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
		}
	}

	if (samplerSource != FK_TEXTURE_IMAGE) {
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, bufSize->w, bufSize->h);
	}

	return true;
}

void fk_TextureSampler::setSamplerSource(fk_SamplerSource argMode)
{
	samplerSource = argMode;
}

fk_SamplerSource fk_TextureSampler::getSamplerSource(void)
{
	return samplerSource;
}
