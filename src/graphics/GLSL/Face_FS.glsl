#version 410 core

const int LIGHTNUM = 8;

struct Material {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	float shininess;
};

struct ParallelLight {
	vec3 vec;
	vec4 diffuse;
	vec4 specular;
};

struct PointLight {
	vec3 position;
	vec4 diffuse;
	vec4 specular;
};

struct SpotLight {
	vec3 position;
	vec3 vec;
	vec4 diffuse;
	vec4 specular;
};

uniform Material fk_Material;
uniform ParallelLight fk_ParallelLight[LIGHTNUM];
uniform PointLight fk_PointLight[LIGHTNUM];
uniform SpotLight fk_SpotLight[LIGHTNUM];
uniform int fk_ParallelLightNum;
uniform int fk_PointLightNum;
uniform int fk_SpotLightNum;
uniform vec3 fk_CameraPosition;

in vec4 varP;
in vec4 varN;
out vec4 fragment;

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

vec3 PointDiffuse(vec3 argN)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_PointLightNum) break;
		vec3 Vl = normalize(varP.xyz - fk_PointLight[i].position);
		float k = clamp(-dot(argN, Vl), 0.0, 1.0);
		sum  += fk_PointLight[i].diffuse.rgb * k;
	}
	return sum;
}

vec3 SpotDiffuse(vec3 argN)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_SpotLightNum) break;
		vec3 Vl = normalize(varP.xyz - fk_SpotLight[i].position);
		float k = clamp(-dot(argN, Vl), 0.0, 1.0);
		sum  += fk_SpotLight[i].diffuse.rgb * k;
	}
	return sum;
}

float GetSpecular(vec3 argN, vec3 argV, vec3 argL)
{
	float specProd = dot(argN, normalize(argV - argL));
	return pow(max(0.0, specProd), fk_Material.shininess);
}

vec3 ParallelSpecular(vec3 argN, vec3 argV)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_ParallelLightNum) break;
		float k = GetSpecular(argN, argV, fk_ParallelLight[i].vec);
		sum += k * fk_ParallelLight[i].specular.rgb;
	}

	return sum;
}

vec3 PointSpecular(vec3 argN, vec3 argV)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_PointLightNum) break;
		vec3 Vl = normalize(varP.xyz - fk_PointLight[i].position);
		float k = GetSpecular(argN, argV, Vl);
		sum += k * fk_PointLight[i].specular.rgb;
	}

	return sum;
}

vec3 SpotSpecular(vec3 argN, vec3 argV)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_SpotLightNum) break;
		vec3 Vl = normalize(varP.xyz - fk_SpotLight[i].position);
		float k = GetSpecular(argN, argV, Vl);
		sum += k * fk_SpotLight[i].specular.rgb;
	}

	return sum;
}

void main()
{
	vec3 Vn = normalize(varN.xyz);
	vec3 difSumColor = vec3(0.0, 0.0, 0.0);
	vec3 speSumColor = vec3(0.0, 0.0, 0.0);
	vec3 viewVec = normalize(fk_CameraPosition - varP.xyz);

	difSumColor += ParallelDiffuse(Vn);
	difSumColor += PointDiffuse(Vn);
	difSumColor += SpotDiffuse(Vn);

	speSumColor += ParallelSpecular(Vn, viewVec);
	speSumColor += PointSpecular(Vn, viewVec);
	speSumColor += SpotSpecular(Vn, viewVec);

	difSumColor *= fk_Material.diffuse.rgb;
	speSumColor *= fk_Material.specular.rgb;

	vec3 addColor = difSumColor + speSumColor + fk_Material.ambient.rgb;
    fragment = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
}
