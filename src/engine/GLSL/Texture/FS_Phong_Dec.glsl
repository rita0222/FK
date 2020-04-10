void main()
{
	vec3 material = DifSpeColor() * ShadowValue() + fk_Material.ambient.rgb;
	vec4 texColor = texture(fk_TexID[0], varT);
	vec4 matColor = vec4(min(vec3(1.0, 1.0, 1.0), mix(material, texColor.rgb, texColor.a)),
						 fk_Material.diffuse.a);
	fk_Fragment = mix(fk_FogColor, matColor, FogValue());
}
