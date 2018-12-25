#version 410 core

in float outCol;
out vec4 fragment;

void main()
{
    fragment = vec4(outCol, outCol, 0.0, 1.0);
}
