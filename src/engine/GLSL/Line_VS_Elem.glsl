#version 410 core

#FKBuildIn

in int fk_LineElementAlive;
flat out vec4 put_color;
flat out int draw_flag;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	put_color = fk_LineElementColor;
	draw_flag = fk_LineElementAlive;
}
