#version 410 core

#FKBuildIn

out vec2 varT;

void main()
{
	gl_Position = fk_ModelViewProjectionMatrix * vec4(fk_Vertex, 1.0);
	varT = fk_TexCoord;
}
