#version 410 core

uniform mat4 fk_ModelViewProjectionMatrix;

in vec3 fk_Vertex;
in vec4 fk_LineElementColor;
flat out vec4 put_color;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	put_color = fk_LineElementColor;
}
