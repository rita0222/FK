#version 410 core

#FKBuildIn

flat in vec4 put_color;
flat in int draw_flag;
in vec4 varP;

float FogValue();

void main()
{
	if(draw_flag == 0) discard;
	fk_Fragment = mix(fk_FogColor, put_color, FogValue());
}
