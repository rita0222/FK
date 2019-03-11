#version 410 core

#FKBuildIn

in vec4 varP;
in vec4 varN;

vec3 ParallelDiffuse(vec3 argN)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_ParallelLightNum) break;
		float k = clamp(-dot(argN, fk_ParallelLight[i].vec), 0.0, 1.0);
		sum += fk_ParallelLight[i].diffuse.rgb * k;
	}

	return sum;
}

float GetSpecular(vec3 argN, vec3 argV, vec3 argL, float argExp)
{
	float specProd = dot(argN, normalize(argV - argL));
	return pow(max(0.0, specProd), fk_Material.shininess * argExp);
}

vec3 ParallelSpecular(vec3 argN, vec3 argV)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_ParallelLightNum) break;
		float k = min(1.0, GetSpecular(argN, argV, fk_ParallelLight[i].vec, 1.0));
		sum += k * fk_ParallelLight[i].specular.rgb;
	}

	return sum;
}

void main(void)
{
	vec3 Vn = normalize(varN.xyz);
	vec3 viewVec = normalize(fk_CameraPosition - varP.xyz);

	vec3 difSumColor = ParallelDiffuse(Vn);
	vec3 speSumColor = ParallelSpecular(Vn, viewVec);

	difSumColor *= fk_Material.diffuse.rgb;
	speSumColor *= fk_Material.specular.rgb;

	vec3 addColor = difSumColor + speSumColor + fk_Material.ambient.rgb;
	fragment = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
}
