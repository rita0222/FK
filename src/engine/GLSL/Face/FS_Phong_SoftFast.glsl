float Shadow_Soft_Fast_Value()
{
	float sum = 0.0;
	vec4 s = vec4(varS.xy, varS.z - fk_ShadowBias, varS.w);
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-1, -1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-1, 0));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-1, 1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(0, -1));
	sum += textureProj(fk_ShadowBuf, s);
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(0, 1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(1, -1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(1, 0));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(1, 1));

	return (1.0 - fk_ShadowVisibility * (1.0 - sum/9.0));
}

void main()
{
	vec3 matColor = DifSpeColor() * Shadow_Soft_Fast_Value() + fk_Material.ambient.rgb;
	vec4 addColor = vec4(min(vec3(1.0, 1.0, 1.0), matColor), fk_Material.diffuse.a);
	fk_Fragment = mix(fk_FogColor, addColor, FogValue());
}
