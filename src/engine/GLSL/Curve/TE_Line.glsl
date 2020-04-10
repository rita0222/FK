#version 410 core

#FKBuildIn

layout( isolines ) in;

out vec4 varP;

vec4 curveFunc();

void main()
{
	vec4 p = curveFunc();
	gl_Position = fk_ModelViewProjectionMatrix * p;
	varP = fk_ModelMatrix * p;
}
