#version 410 core

#FKBuildIn

in vec2 varT;
in vec4 varP;

float FogValue();

void main()
{
	fk_Fragment = mix(fk_FogColor, texture(fk_TexID[0], varT), FogValue());
}
