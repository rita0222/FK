#version 410 core

#FKBuildIn

subroutine vec4 textureRendType ();
subroutine uniform textureRendType textureRendSelect;

in vec4 varC;
in vec2 varT;

subroutine(textureRendType)
vec4 Replace()
{
	return texture(fk_TexID[0], varT);
}

subroutine(textureRendType)
vec4 Modulate()
{
	vec4 texColor = texture(fk_TexID[0], varT);
	vec3 trueColor = varC.rgb * texColor.rgb;
	return vec4(min(vec3(1.0, 1.0, 1.0), trueColor), fk_Material.diffuse.a * texColor.a);
}

subroutine(textureRendType)
vec4 Decal()
{
	vec4 texColor = texture(fk_TexID[0], varT);
	vec3 trueColor = varC.rgb * (1.0 - texColor.a) + texColor.rgb * texColor.a;
	return vec4(min(vec3(1.0, 1.0, 1.0), trueColor), fk_Material.diffuse.a);
}	

void main()
{
	fk_Fragment = textureRendSelect();
}
