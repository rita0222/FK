#version 410 core

struct Material {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	float shininess;
};

struct Light {
	int type;
	vec3 position;
	vec3 vec;
	vec4 diffuse;
	vec4 specular;
};

uniform Material fk_Material;
uniform Light fk_Light[8];
uniform int fk_LightNum;

in vec4 outVec;
out vec4 fragment;

void main()
{
	vec3 v = normalize(outVec.xyz);
	vec3 lightVec = vec3(1.0, 0.0, 0.0);
	if(fk_LightNum > 0) {
		lightVec = fk_Light[0].vec;
	}
	float col = clamp(-dot(v, lightVec), 0.0, 1.0);
	vec3 dif = fk_Material.diffuse.rgb * col;
	vec3 sum = dif + fk_Material.ambient.rgb;
	float alpha = (fk_Material.diffuse.a * col + fk_Material.ambient.a)/(1.0 + col);
    fragment = vec4(min(1.0, sum.r), min(1.0, sum.g), min(1.0, sum.b), alpha);
}
