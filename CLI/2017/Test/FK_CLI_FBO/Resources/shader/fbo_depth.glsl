#version 410 core

#FKBuildIn

void main(void)
{
	float r = pow(texture(fk_DepthBuf, fk_FBOTexCoord).r, 10.0);
	fk_Fragment = vec4(r, r, r, 1.0);
}
