#version 410 core

#FKBuildIn

in vec4 varP;

float FogValue();

void main()
{
	fk_Fragment = mix(fk_FogColor, fk_CurveModelColor, FogValue());
}
