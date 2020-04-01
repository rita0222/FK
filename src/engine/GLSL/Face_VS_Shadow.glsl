#version 410 core

#FKBuildIn

void main()
{
	gl_Position = fk_ModelViewProjectionMatrix * vec4(fk_Vertex, 1.0);
}
