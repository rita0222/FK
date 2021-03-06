#version 410 core

#FKBuildIn

uniform float Thresshold;

float getMono(vec2 argPos)
{
	vec4 col = texture(fk_ColorBuf, argPos);
	return min(1.0, col.r * 0.298912 + col.g * 0.586611 + col.b * 0.114478);
}

//フラグメント

void main(void)
{
	float dx = 1.0/fk_FBOSize.x;
	float dy = 1.0/fk_FBOSize.y;

	float c_00 = getMono(fk_FBOTexCoord + vec2(-dx, -dy));
	float c_01 = getMono(fk_FBOTexCoord + vec2(0, -dy));
	float c_02 = getMono(fk_FBOTexCoord + vec2(dx, -dy));
	float c_10 = getMono(fk_FBOTexCoord + vec2(-dx, 0));
	float c_11 = getMono(fk_FBOTexCoord + vec2(0, 0));
	float c_12 = getMono(fk_FBOTexCoord + vec2(dx, 0));
	float c_20 = getMono(fk_FBOTexCoord + vec2(-dx, dy));
	float c_21 = getMono(fk_FBOTexCoord + vec2(0, dy));
	float c_22 = getMono(fk_FBOTexCoord + vec2(dx, dy));

	float Sx = -c_00 + c_02 - 2.0*c_10 + 2.0*c_12 - c_20 + c_22;
	float Sy = -c_00 + c_20 - 2.0*c_01 + 2.0*c_21 - c_02 + c_22;
	float Val = Sx * Sx + Sy * Sy;
	
	if(Val > Thresshold) {
		fk_Fragment = vec4(1.0, 1.0, 1.0, 1.0);
	} else {
		fk_Fragment = vec4(0.0, 0.0, 0.0, 1.0);
	}
}
