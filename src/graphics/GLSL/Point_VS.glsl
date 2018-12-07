R"(
#version 410 core
uniform mat4 modelview;
uniform mat4 projection;
uniform vec4 color;
in vec3 position;
in int alive;
flat out vec4 f_color;
void main()
{
	vec4 p = vec4(position, 1.0);
	gl_Position = projection * modelview * p;
	f_color = color;
	if(alive == 2) {
		f_color = vec4(1.0, 0.0, 0.0, 1.0);
	}
}
)"
