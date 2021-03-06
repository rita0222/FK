#version 410 core

#FKBuildIn

out vec4 varC;
out vec2 varT;
out vec4 varP;

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

vec3 PointDiffuse(vec3 argP, vec3 argN)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_PointLightNum) break;
		vec3 Vl = normalize(argP - fk_PointLight[i].position);
		float a = Attenuation(fk_PointLight[i].attenuation, argP,
							  fk_PointLight[i].position);
		float k = clamp(-dot(argN, Vl) * a, 0.0, 1.0);
		sum += fk_PointLight[i].diffuse.rgb * k;
	}
	return sum;
}

vec3 SpotDiffuse(vec3 argP, vec3 argN)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_SpotLightNum) break;
		float cutMin = cos(fk_SpotLight[i].cut);
		vec3 Vl = normalize(argP - fk_SpotLight[i].position);
		float prod = -dot(argN, Vl);
		float a = Attenuation(fk_SpotLight[i].attenuation, argP, fk_SpotLight[i].position);
		float k = clamp(pow(prod, fk_SpotLight[i].exp) * a, 0.0, 1.0);
		sum += max(0.0, sign(prod - cutMin)) * fk_SpotLight[i].diffuse.rgb * k;
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

vec3 PointSpecular(vec3 argP, vec3 argN, vec3 argV)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_PointLightNum) break;
		vec3 Vl = normalize(argP - fk_PointLight[i].position);
		float k = GetSpecular(argN, argV, Vl, 1.0);
		float a = Attenuation(fk_PointLight[i].attenuation, argP, fk_PointLight[i].position);
		sum += k * a * fk_PointLight[i].specular.rgb;
	}

	return sum;
}

vec3 SpotSpecular(vec3 argP, vec3 argN, vec3 argV)
{
	vec3 sum = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_SpotLightNum) break;
		float cutMin = cos(fk_SpotLight[i].cut);
		vec3 Vl = normalize(argP - fk_SpotLight[i].position);
		float prod = -dot(argN, Vl);
		float k = GetSpecular(argN, argV, Vl, fk_SpotLight[i].exp);
		float a = Attenuation(fk_SpotLight[i].attenuation, argP, fk_SpotLight[i].position);
		sum += max(0.0, sign(prod - cutMin)) * k * a * fk_SpotLight[i].specular.rgb;
	}

	return sum;
}

vec3 DifSpeColor()
{
	vec3 varP = (fk_ModelMatrix * vec4(fk_Vertex, 1.0)).xyz;
	vec4 varN = fk_NormalModelMatrix * vec4(fk_Normal, 0.0);
	vec3 Vn = normalize(varN.xyz);
	vec3 viewVec = normalize(fk_CameraPosition - gl_Position.xyz);

	vec3 difColor = (ParallelDiffuse(Vn) +
					 PointDiffuse(varP, Vn) +
					 SpotDiffuse(varP, Vn)) * fk_Material.diffuse.rgb;

	vec3 speColor = (ParallelSpecular(Vn, viewVec) +
					 PointSpecular(varP, Vn, viewVec) +
					 SpotSpecular(varP, Vn, viewVec)) * fk_Material.specular.rgb;

	return (difColor + speColor);
}
