float ShadowValue()
{
	return 1.0 - fk_ShadowVisibility * (1.0 - textureProj(fk_ShadowBuf, varS));
}
