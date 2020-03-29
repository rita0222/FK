#version 410 core

#FKBuildIn

subroutine void pointColorType ();
subroutine uniform pointColorType pointColorFunc;

in int fk_PointElementAlive;
flat out vec4 put_color;
flat out int draw_flag;

subroutine(pointColorType)
void PointModelVS()
{
	put_color = fk_PointModelColor;
	draw_flag = fk_PointElementAlive;
}

subroutine(pointColorType)
void PointElemVS()
{
	put_color = fk_PointElementColor;
	draw_flag = fk_PointElementAlive;
}
	
subroutine(pointColorType)
void PointIFSVS()
{
	put_color = fk_PointModelColor;
	draw_flag = 1;
}

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	pointColorFunc();
}
