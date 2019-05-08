#version 410 core

in vec3 fk_Vertex;

void main(void)
{
	gl_Position = vec4(fk_Vertex, 1.0);
}
