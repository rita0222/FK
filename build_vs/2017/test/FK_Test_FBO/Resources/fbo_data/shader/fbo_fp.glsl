#version 410 core

#FKBuildIn

void main(void)
{
	fk_Fragment = vec4(texture(fk_ColorBuf, fk_FBOTexCoord).rgb, 1.0);
	//fk_Fragment = vec4(fk_FBOTexCoord, 1.0, 1.0);
}
