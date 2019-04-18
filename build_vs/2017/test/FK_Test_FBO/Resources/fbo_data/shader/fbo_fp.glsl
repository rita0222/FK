#version 410 core

uniform sampler2D tex0;
in vec2 fk_TexCoord;

void main(void)
{
	//fk_Fragment = texture(fk_ColorBuf, fk_TexCoord);
	fk_Fragment = vec4(1.0, 0.0, 0.0, 1.0);
}
