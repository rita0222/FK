#version 410 core

#FKBuildIn

subroutine void lineColorType ();
subroutine uniform lineColorType lineColorFunc;

in int fk_LineElementAlive;
flat out vec4 put_color;
flat out int draw_flag;

subroutine(lineColorType)
void LineModelVS()
{
	put_color = fk_LineModelColor;
	draw_flag = fk_LineElementAlive;
}

subroutine(lineColorType)
void LineElemVS()
{
	put_color = fk_LineElementColor;
	draw_flag = fk_LineElementAlive;
}

subroutine(lineColorType)
void LineIFSVS()
{
	put_color = fk_LineModelColor;
	draw_flag = 1;
}

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	lineColorFunc();
}
