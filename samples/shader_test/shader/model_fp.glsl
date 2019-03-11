<<<<<<< HEAD
#version 120

//varying変数
varying vec3 normal;
varying vec4 vertexPos;
//out vec4 fragment
=======
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

>>>>>>> NewOGL

void main(void)
{
<<<<<<< HEAD
	////  ambientの計算  ////
	vec4 ambient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;

	////  diffuse計算  ////
	vec3 N = normalize(normal);
	vec3 L = normalize(gl_LightSource[0].position.xyz);
	float NdotL = dot(N, L);
	vec4 diffuse = max(0.0, NdotL) * gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;

	////  specular計算(Bilnのモデルを使用)  ////
	vec3 V = -normalize(vertexPos.xyz);
	vec3 H = normalize(V + L);
	float NdotH = dot(N, H);
	float k_specular = pow(max(0.0, NdotH), gl_FrontMaterial.shininess);
	vec4 specular = k_specular * gl_LightSource[0].specular * gl_FrontMaterial.specular;

	//fragment = ambient + diffuse + specular;
	gl_FragColor = ambient + diffuse + specular;
=======
	vec3 Vn = normalize(varN.xyz);
	vec3 viewVec = normalize(fk_CameraPosition - varP.xyz);

	vec3 difSumColor = ParallelDiffuse(Vn);
	vec3 speSumColor = ParallelSpecular(Vn, viewVec);

	difSumColor *= fk_Material.diffuse.rgb;
	speSumColor *= fk_Material.specular.rgb;

	vec3 addColor = difSumColor + speSumColor + fk_Material.ambient.rgb;
	fragment = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
>>>>>>> NewOGL
}
