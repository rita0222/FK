#version 410 core

uniform mat4 fk_modelview;
uniform mat4 fk_projection;

in vec3 fk_line_elem_position;
in vec4 fk_line_elem_color;
flat out vec4 put_color;

void main()
{
	vec4 p = vec4(fk_line_elem_position, 1.0);
	gl_Position = fk_projection * fk_modelview * p;
	put_color = fk_line_elem_color;
}
