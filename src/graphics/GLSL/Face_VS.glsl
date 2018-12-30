#version 410 core

uniform mat4 fk_ModelViewProjectionMatrix;
uniform mat4 fk_NormalMatrix;

in vec3 fk_Vertex;
in vec3 fk_Normal;
out vec4 outVec;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	outVec = fk_NormalMatrix * vec4(fk_Normal, 0.0);
}
