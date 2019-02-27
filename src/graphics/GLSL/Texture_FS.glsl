#version 330 core

uniform sampler2D fk_TexID;
in vec2 varT;
out vec4 fragment;

void main()
{
    fragment = texture(fk_TexID, varT);
    //fragment = vec4(varT.r, varT.g, 1.0, 1.0);
	//fragment = vec4(1.0, 1.0, 0.0, 1.0);
}
