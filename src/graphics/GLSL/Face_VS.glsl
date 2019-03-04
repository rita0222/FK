#version 410 core

#FKBuildIn

out vec4 varP;
out vec4 varN;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	varP = fk_ModelMatrix * p;
	varN = fk_NormalModelMatrix * vec4(fk_Normal, 0.0);
}
