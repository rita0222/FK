#version 410 core

#FKBuildIn

float FogValue();

in vec4 varP;

void main()
{
	fk_Fragment = mix(fk_FogColor, fk_CurveModelColor, FogValue());
}
