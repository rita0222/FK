#version 330 core

uniform sampler2D fk_tex1;

in vec2 varT;
out vec4 fragment;

void main()
{
    fragment = texture(fk_tex1, varT);
}
