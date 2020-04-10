void main()
{
	vec3 matColor = DifSpeColor() + fk_Material.ambient.rgb;
	vec4 addColor = vec4(min(vec3(1.0, 1.0, 1.0), matColor), fk_Material.diffuse.a);
	fk_Fragment = mix(fk_FogColor, addColor, FogValue());
}
