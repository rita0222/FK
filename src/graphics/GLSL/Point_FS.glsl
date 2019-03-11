#version 410 core

#FKBuildIn

subroutine void pointDrawType ();
subroutine uniform pointDrawType pointDrawFunc;

flat in vec4 put_color;
flat in int draw_flag;

subroutine(pointDrawType)
void PointPointFS()
{
	if(draw_flag == 2) discard;
}

subroutine(pointDrawType)
void PointIFSFS()
{
}

void main()
{
	pointDrawFunc();
    fragment = put_color;
}
