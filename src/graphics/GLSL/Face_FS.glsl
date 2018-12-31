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
uniform vec3 fk_CameraPosition;

in vec4 varP;
in vec4 varN;
out vec4 fragment;
const int LIGHTNUM = 8;

void main()
{
	vec3 Vn = normalize(varN.xyz);
	vec3 difSumColor = vec3(0.0, 0.0, 0.0);
	vec3 speSumColor = vec3(0.0, 0.0, 0.0);
	vec3 Vl;
	vec3 viewVec = normalize(varP.xyz - fk_CameraPosition);

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_LightNum) break;
		if(fk_Light[i].type == 1) {
			Vl = fk_Light[i].vec;
		} else if(fk_Light[i].type == 2 || fk_Light[i].type == 3) {
			Vl = normalize(varP.xyz - fk_Light[i].position);
		} else {
			Vl = vec3(0.0, 0.0, 1.0);
		}
		difSumColor += fk_Light[i].diffuse.rgb * clamp(-dot(Vn, Vl), 0.0, 1.0);

		float specProd = dot(Vn, normalize(viewVec + Vl));
		float k_spec = pow(max(0.0, specProd), fk_Material.shininess);
		speSumColor += k_spec * fk_Material.specular.rgb;
	}
	difSumColor *= fk_Material.diffuse.rgb;
	speSumColor *= fk_Material.specular.rgb;
	vec3 addColor = difSumColor + speSumColor + fk_Material.ambient.rgb;
    fragment = vec4(min(addColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
}
