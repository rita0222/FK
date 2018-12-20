#version 410 core

uniform mat4 fk_ModelViewMatrix;
uniform mat4 fk_ProjectionMatrix;

in vec3 fk_Vertex;
in vec4 fk_PointElementColor;
in int fk_PointElementAlive;
flat out vec4 put_color;
flat out int draw_flag;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ProjectionMatrix * fk_ModelViewMatrix * p;
	put_color = fk_PointElementColor;
	draw_flag = fk_PointElementAlive;
}
