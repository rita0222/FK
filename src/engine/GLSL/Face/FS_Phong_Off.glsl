void main()
{
	vec3 addColor = DifSpeColor() + fk_Material.ambient.rgb;
	fk_Fragment = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
}
