float Shadow_Hard_Value()
{
	vec4 s = vec4(varS.xy, varS.z - fk_ShadowBias, varS.w);
	return 1.0 - fk_ShadowVisibility * (1.0 - textureProj(fk_ShadowBuf, s));
}

void main()
{
	vec3 addColor = DifSpeColor() * Shadow_Hard_Value() + fk_Material.ambient.rgb;
	fk_Fragment = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
}
