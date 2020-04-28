#version 410 core

#FKBuildIn

void main(void)
{
	fk_Fragment = texture(fk_ColorBuf, fk_FBOTexCoord);
}
