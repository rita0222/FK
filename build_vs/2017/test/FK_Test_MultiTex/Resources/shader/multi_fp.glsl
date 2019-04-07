#version 410 core

#FKBuildIn

in vec2 varT;
uniform vec2 scale;

void main(void)
{
	vec4 col1 = texture(fk_TexID[0], varT);
	vec4 col2 = texture(fk_TexID[1], varT * scale);
	fk_Fragment = min(vec4(1.0, 1.0, 1.0, 1.0), col1 + col2);
}
