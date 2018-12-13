#version 410 core

flat in vec4 put_color;
out vec4 fragment;

void main()
{
    fragment = put_color;
}
