#version 410 core

#FKBuildIn

subroutine void curveDrawType ();
subroutine uniform curveDrawType curveDrawFunc;

subroutine(curveDrawType)
void ShadowDraw()
{
	discard;
}

subroutine(curveDrawType)
void ElemDraw()
{
	fk_Fragment = fk_CurveModelColor;
}

void main()
{
	curveDrawFunc();
}
