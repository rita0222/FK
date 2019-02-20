#version 330 core

flat in vec4 put_color;
flat in int draw_flag;
out vec4 fragment;

void main()
{
	if(draw_flag == 2) discard;
    fragment = put_color;
}
