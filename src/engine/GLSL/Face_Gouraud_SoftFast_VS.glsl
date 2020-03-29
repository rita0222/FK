float Shadow_Soft_Fast_Value()
{
	vec4 v = fk_ShadowMatrix * vec4(fk_Vertex, 1.0);
	return 1.0 - fk_ShadowVisibility * (1.0 - textureProj(fk_ShadowBuf, v));
}

void main()
{
	gl_Position = fk_ModelViewProjectionMatrix * vec4(fk_Vertex, 1.0);
	vec3 addColor = DifSpeColor() * Shadow_Soft_Fast_Value() + fk_Material.ambient.rgb;
	varC = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
}
