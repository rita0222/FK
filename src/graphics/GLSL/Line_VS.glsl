#version 410 core

#FKBuildIn

subroutine vec4 lineColorType ();
subroutine uniform lineColorType lineColorSelect;

flat out vec4 put_color;

subroutine(lineColorType)
vec4 ModelColor()
{
	return fk_LineModelColor;
}

subroutine(lineColorType)
vec4 ElementColor()
{
	return fk_LineElementColor;
}

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	put_color = lineColorSelect();
}
