#version 330 core

#FKBuildIn

in vec2 varT;

void main()
{
	fragment = texture(fk_TexID[0], varT);
}
