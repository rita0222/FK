#version 410 core

uniform sampler2D fk_ColorBuf;
uniform float Width;
uniform float Height;
uniform float Thresshold;

in vec2 fk_FBOTexCoord;
out vec4 fk_Fragment;

void main(void)
{
	//fk_Fragment = vec4(fk_FBOTexCoord.x, fk_FBOTexCoord.y, 0.0, 1.0);
	fk_Fragment = texture(fk_ColorBuf, fk_FBOTexCoord);
}
