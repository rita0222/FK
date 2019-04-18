#version 410 core

uniform sampler2D fk_ColorBuf;
in vec2 fk_TexCoord;
out vec4 fk_Fragment;

void main(void)
{
	fk_Fragment = texture(fk_ColorBuf, fk_TexCoord);
	//fk_Fragment = vec4(1.0, 0.0, 0.0, 1.0);
}
