#version 410 core

#FKBuildIn

in vec4 varC;
in vec2 varT;

void main()
{
	vec4 texColor = texture(fk_TexID[0], varT);
	vec3 trueColor = varC.rgb * (1.0 - texColor.a) + texColor.rgb * texColor.a;
	fk_Fragment = vec4(min(vec3(1.0, 1.0, 1.0), trueColor), varC.a);
}
