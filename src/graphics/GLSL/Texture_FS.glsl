#version 330 core

const int TEXTURENUM = 8;

uniform sampler2D fk_TexID[TEXTURENUM];
in vec2 varT;
out vec4 fragment;

void main()
{
    fragment = texture(fk_TexID[0], varT);
}
