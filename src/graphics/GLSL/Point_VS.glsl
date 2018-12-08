#version 410 core
uniform mat4 modelview;
uniform mat4 projection;
uniform vec4 color;
in vec3 fk_point_elem_position;
in int fk_point_elem_alive;
flat out vec4 f_color;
void main()
{
	vec4 p = vec4(fk_point_elem_position, 1.0);
	gl_Position = projection * modelview * p;
	f_color = color;
	if(fk_point_elem_alive == 2) {
		f_color = vec4(1.0, 0.0, 0.0, 1.0);
	}
}
