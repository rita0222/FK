#version 410 core

uniform mat4 fk_ModelViewProjectionMatrix;

in vec3 fk_Vertex;
in vec2 fk_TexCoord;
out vec2 varT;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	varT = fk_TexCoord;
}
