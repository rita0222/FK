float Shadow_Soft_Nice_Value()
{
	float sum = 0.0;
	vec4 s = vec4(varS.xy, varS.z - fk_ShadowBias, varS.w);
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-2, -2));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-2, -1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-2, 0));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-2, 1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-2, 2));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-1, -2));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-1, -1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-1, 0));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-1, 1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(-1, 2));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(0, -2));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(0, -1));
	sum += textureProj(fk_ShadowBuf, s);
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(0, 1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(0, 2));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(1, -2));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(1, -1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(1, 0));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(1, 1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(1, 2));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(2, -2));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(2, -1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(2, 0));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(2, 1));
	sum += textureProjOffset(fk_ShadowBuf, s, ivec2(2, 2));

	return (1.0 - fk_ShadowVisibility * (1.0 - sum/25.0));
}

void main()
{
	gl_Position = fk_ModelViewProjectionMatrix * vec4(fk_Vertex, 1.0);
	vec3 addColor = DifSpeColor() * Shadow_Soft_Nice_Value() + fk_Material.ambient.rgb;
	varC = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
	varT = fk_TexCoord;
}
