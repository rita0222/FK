#version 410 core

#FKBuildIn

in vec4 varC;
in vec4 varP;

float FogValue();

void main()
{
	fk_Fragment = varC;
}
