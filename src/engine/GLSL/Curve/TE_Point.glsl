#version 410 core

#FKBuildIn

layout( isolines , point_mode ) in;

vec4 curveFunc();

void main()
{
	gl_Position = fk_ModelViewProjectionMatrix * curveFunc();
}
