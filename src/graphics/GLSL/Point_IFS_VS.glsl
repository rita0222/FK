#version 410 core

uniform mat4 fk_modelview;
uniform mat4 fk_projection;
uniform vec4 fk_point_model_color;

in vec3 fk_point_elem_position;
flat out vec4 put_color;

void main()
{
	vec4 p = vec4(fk_point_elem_position, 1.0);
	gl_Position = fk_projection * fk_modelview * p;
	put_color = fk_point_model_color;
}
