#version 410 core

#FKBuildIn

subroutine void lineDrawType ();
subroutine uniform lineDrawType lineDrawFunc;

flat in vec4 put_color;
flat in int draw_flag;

subroutine(lineDrawType)
void LineLineFS()
{
	if(draw_flag == 0) discard;
}

subroutine(lineDrawType)
void LineIFSFS()
{
}

void main()
{
	lineDrawFunc();
	fk_Fragment = put_color;
}
