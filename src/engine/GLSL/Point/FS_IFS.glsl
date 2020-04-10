#version 410 core

#FKBuildIn

flat in vec4 put_color;
in vec4 varP;

float FogValue();

void main()
{
	fk_Fragment = mix(fk_FogColor, put_color, FogValue());
}
