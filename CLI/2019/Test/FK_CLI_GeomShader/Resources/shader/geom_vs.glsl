#version 410 core

#FKBuildIn

in vec2 pointVec;
out vec2 pointV;

void main()
{
	gl_Position = vec4(fk_Vertex, 1.0);
	pointV = pointVec;
}
