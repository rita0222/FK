#version 410 core

#FKBuildIn

in vec4 varC;

void main()
{
	fk_Fragment = varC;
}
