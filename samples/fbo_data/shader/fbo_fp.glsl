#version 410 core

uniform sampler2D fk_DepthBuf;

uniform float Width;
uniform float Height;
uniform float Thresshold;

in vec2 varT;
out vec4 fragment;
/*
float getMono(vec2 argPos)
{
	vec4 col = texture(fk_ColorBuf, argPos);
	return min(1.0, col.r * 0.298912 + col.g * 0.586611 + col.b * 0.114478);
}
*/

//フラグメント

void main(void)
{
	/*
	float dx = 1.0/Width;
	float dy = 1.0/Height;

	float c_00 = getMono(varT + vec2(-dx, -dy));
	float c_01 = getMono(varT + vec2(0, -dy));
	float c_02 = getMono(varT + vec2(dx, -dy));
	float c_10 = getMono(varT + vec2(-dx, 0));
	float c_11 = getMono(varT + vec2(0, 0));
	float c_12 = getMono(varT + vec2(dx, 0));
	float c_20 = getMono(varT + vec2(-dx, dy));
	float c_21 = getMono(varT + vec2(0, dy));
	float c_22 = getMono(varT + vec2(dx, dy));

	float Sx = -c_00 + c_02 - 2.0*c_10 + 2.0*c_12 - c_20 + c_22;
	float Sy = -c_00 + c_20 - 2.0*c_01 + 2.0*c_21 - c_02 + c_22;
	float Val = Sx * Sx + Sy * Sy;
	
	if(Val > Thresshold) {
		fragment = vec4(1.0, 1.0, 1.0, 1.0);
	} else {
		fragment = vec4(0.0, 0.0, 0.0, 1.0);
	}
	*/
	fragment = texture(fk_DepthBuf, varT);
}
