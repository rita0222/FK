#version 410 core

#FKBuildIn

in vec4 varC;
in vec2 varT;

void main()
{
	vec4 texColor = texture(fk_TexID[0], varT);
	fk_Fragment = vec4(min(vec3(1.0, 1.0, 1.0), mix(varC.rgb, texColor.rgb, texColor.a)), varC.a);
}
