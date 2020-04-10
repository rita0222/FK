void main()
{
	vec4 P = vec4(fk_Vertex, 1.0);

	gl_Position = fk_ModelViewProjectionMatrix * P;
	varP = fk_ModelMatrix * P;
	vec3 addColor = DifSpeColor() + fk_Material.ambient.rgb;
	varC = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
}
