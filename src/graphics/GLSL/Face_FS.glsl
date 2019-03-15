#version 330 core

#FKBuildIn

in vec4 varP;
in vec4 varN;

float Attenuation(vec3 argA, vec3 argP1, vec3 argP2)
{
	float dist = distance(argP1, argP2);
	return 1.0/(argA[0] * dist + argA[1] * dist * dist + argA[2]);
}

float GetSpecular(vec3 argN, vec3 argV, vec3 argL, float argExp)
{
	float specProd = dot(argN, normalize(argV - argL));
	return pow(max(0.0, specProd), fk_Material.shininess * argExp);
}

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
		float a = Attenuation(fk_PointLight[i].attenuation, varP.xyz,
							  fk_PointLight[i].position);
		float k = clamp(-dot(argN, Vl) * a, 0.0, 1.0);
		sum += fk_PointLight[i].diffuse.rgb * k;
	}
	return sum;
}

vec3 SpotDiffuse(vec3 argN)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_SpotLightNum) break;
		float cutMin = cos(fk_SpotLight[i].cut);
		vec3 Vl = normalize(varP.xyz - fk_SpotLight[i].position);
		float prod = -dot(argN, Vl);
		if(prod > cutMin) {
			float a = Attenuation(fk_SpotLight[i].attenuation, varP.xyz,
								  fk_SpotLight[i].position);
			float k = clamp(pow(prod, fk_SpotLight[i].exp) * a, 0.0, 1.0);
			sum += fk_SpotLight[i].diffuse.rgb * k;
		}
	}
	return sum;
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

vec3 PointSpecular(vec3 argN, vec3 argV)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_PointLightNum) break;
		vec3 Vl = normalize(varP.xyz - fk_PointLight[i].position);
		float k = GetSpecular(argN, argV, Vl, 1.0);
		float a = Attenuation(fk_PointLight[i].attenuation, varP.xyz,
							  fk_PointLight[i].position);
		sum += k * a * fk_PointLight[i].specular.rgb;
	}

	return sum;
}

vec3 SpotSpecular(vec3 argN, vec3 argV)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_SpotLightNum) break;
		float cutMin = cos(fk_SpotLight[i].cut);
		vec3 Vl = normalize(varP.xyz - fk_SpotLight[i].position);
		float prod = -dot(argN, Vl);
		if(prod > cutMin) {
			float k = GetSpecular(argN, argV, Vl, fk_SpotLight[i].exp);
			float a = Attenuation(fk_SpotLight[i].attenuation, varP.xyz,
								  fk_SpotLight[i].position);
			sum += k * a * fk_SpotLight[i].specular.rgb;
		}
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
    fk_Fragment = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
}
