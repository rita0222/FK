#version 410 core

#FKBuildIn

in vec4 varC;
in vec2 varT;
in vec4 varP;

float FogValue();

void main()
{
	vec4 texColor = texture(fk_TexID[0], varT);
	vec4 matColor = vec4(min(vec3(1.0, 1.0, 1.0), mix(varC.rgb, texColor.rgb, texColor.a)), varC.a);
	fk_Fragment = mix(fk_FogColor, matColor, FogValue());
}
