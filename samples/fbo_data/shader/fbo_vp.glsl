#version 410 core

#FKBuildIn

//in vec3 fk_Vertex;
//in vec2 fk_TexCoord;

out vec2 varT;

void main(void)
{
	gl_Position = vec4(fk_Vertex, 1.0);
	varT = fk_TexCoord;
}
