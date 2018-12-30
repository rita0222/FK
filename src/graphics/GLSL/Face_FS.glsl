#version 410 core

struct Material {
	vec4 diffuse;
	vec4 ambient;
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
	float col = clamp(-dot(v, lightVec), 0.1, 1.0);
    fragment = vec4(fk_Material.diffuse.rgb * col, 1.0);
}
