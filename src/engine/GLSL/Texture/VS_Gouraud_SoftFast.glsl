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
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	vec3 addColor = DifSpeColor() * Shadow_Soft_Fast_Value() + fk_Material.ambient.rgb;
	varC = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
	varT = fk_TexCoord;
	varP = fk_ModelMatrix * p;
}
