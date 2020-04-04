#version 410 core

#FKBuildIn

layout( isolines ) in;

vec4 curveFunc();

void main()
{
	gl_Position = fk_ModelViewProjectionMatrix * curveFunc();
}
