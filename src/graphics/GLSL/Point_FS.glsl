R"(
#version 410 core
flat in vec4 f_color;
out vec4 fragment;
void main()
{
    fragment = f_color;
}
)"
