#version 410 core

#FKBuildIn

void main(void)
{
	fk_Fragment = vec4(fk_FBOTexCoord, 0.0, 1.0);
}