#version 410 core

uniform mat4 fk_modelview;
uniform mat4 fk_projection;
in vec3 fk_point_elem_position;
in vec4 fk_point_elem_color;
in int fk_point_elem_alive;
flat out vec4 put_color;
flat out int draw_flag;
void main()
{
	vec4 p = vec4(fk_point_elem_position, 1.0);
	gl_Position = fk_projection * fk_modelview * p;
	put_color = fk_point_elem_color;
	draw_flag = fk_point_elem_alive;
}
