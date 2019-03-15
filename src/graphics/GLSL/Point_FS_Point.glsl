#version 330 core

#FKBuildIn

flat in vec4 put_color;
flat in int draw_flag;

void main()
{
	if(draw_flag == 2) discard;
    fk_Fragment = put_color;
}
