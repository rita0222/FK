#version 410 core

#FKBuildIn

void main()
{
	gl_Position = vec4(fk_Vertex, 1.0);
}
