#version 410 core

#FKBuildIn

in vec4 varC;
in vec2 varT;

void main()
{
	fk_Fragment = min(vec4(1.0, 1.0, 1.0, 1.0), varC * texture(fk_TexID[0], varT));
}
