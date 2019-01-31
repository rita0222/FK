#version 330 core

uniform mat4 fk_ModelViewProjectionMatrix;
uniform vec4 fk_PointModelColor;

in vec3 fk_Vertex;
in int fk_PointElementAlive;
flat out vec4 put_color;
flat out int draw_flag;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	put_color = fk_PointModelColor;
	draw_flag = fk_PointElementAlive;
}
