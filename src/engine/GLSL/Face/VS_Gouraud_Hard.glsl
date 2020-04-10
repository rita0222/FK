float Shadow_Hard_Value()
{
	vec4 v = fk_ShadowMatrix * vec4(fk_Vertex, 1.0);
	return 1.0 - fk_ShadowVisibility * (1.0 - textureProj(fk_ShadowBuf, v));
}

void main()
{
	vec4 P = vec4(fk_Vertex, 1.0);

	gl_Position = fk_ModelViewProjectionMatrix * P;
	varP = fk_ModelMatrix * P;
	vec3 addColor = DifSpeColor() * Shadow_Hard_Value() + fk_Material.ambient.rgb;
	varC = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
}
