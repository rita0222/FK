void main()
{
	vec3 material = DifSpeColor() * ShadowValue() + fk_Material.ambient.rgb;
	vec4 texColor = texture(fk_TexID[0], varT);
	vec3 trueColor = material * (1.0 - texColor.a) + texColor.rgb * texColor.a;
	fk_Fragment = vec4(min(vec3(1.0, 1.0, 1.0), trueColor), fk_Material.diffuse.a);
}
