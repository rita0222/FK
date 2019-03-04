#version 410 core

#FKBuildIn

flat in vec4 put_color;

void main()
{
    fragment = put_color;
}
