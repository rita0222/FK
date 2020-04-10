#version 410 core

#FKBuildIn

in vec4 varC;
in vec2 varT;
in vec4 varP;

float FogValue();

void main()
{
	vec4 matColor = min(vec4(1.0, 1.0, 1.0, 1.0), varC * texture(fk_TexID[0], varT));
	fk_Fragment = mix(fk_FogColor, matColor, FogValue());
}
