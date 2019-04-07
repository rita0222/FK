#version 410 core

#FKBuildIn

//varying変数
in vec4 varN;

//フラグメント
void main(void)
{
	////  diffuse計算  ////
	float NdotV = 1.0 - dot(normalize(varN.xyz), vec3(0.0, 0.0, 1.0));
	fk_Fragment = vec4(NdotV, NdotV, NdotV, NdotV);
}
