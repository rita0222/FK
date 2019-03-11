#version 410 core

layout (location = 0) in vec3 fk_Vertex;
layout (location = 2) in vec2 fk_TexCoord;

out vec2 varT;

void main(void)
{
	gl_Position = vec4(fk_Vertex, 1.0);
	varT = fk_TexCoord;
}
