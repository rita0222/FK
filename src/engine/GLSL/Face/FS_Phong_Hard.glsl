float Shadow_Hard_Value()
{
	vec4 s = vec4(varS.xy, varS.z - fk_ShadowBias, varS.w);
	return 1.0 - fk_ShadowVisibility * (1.0 - textureProj(fk_ShadowBuf, s));
}

void main()
{
	vec3 matColor = DifSpeColor() * Shadow_Hard_Value() + fk_Material.ambient.rgb;
	vec4 addColor = vec4(min(vec3(1.0, 1.0, 1.0), matColor), fk_Material.diffuse.a);
	fk_Fragment = mix(fk_FogColor, addColor, FogValue());
}
