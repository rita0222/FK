#version 410 core

#FKBuildIn

in int fk_PointElementAlive;
flat out vec4 put_color;
flat out int draw_flag;
out vec4 varP;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	put_color = fk_PointModelColor;
	draw_flag = fk_PointElementAlive;
	varP = fk_ModelMatrix * p;
}
