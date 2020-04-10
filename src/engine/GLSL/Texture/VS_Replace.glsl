#version 410 core

#FKBuildIn

out vec2 varT;
out vec4 varP;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	varT = fk_TexCoord;
	varP = fk_ModelMatrix * p;
}
