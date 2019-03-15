#version 330 core

#FKBuildIn

in vec2 varT;

void main()
{
	fk_Fragment = texture(fk_TexID[0], varT);
}
