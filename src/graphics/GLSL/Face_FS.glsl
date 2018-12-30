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

in vec4 varP;
in vec4 varN;
out vec4 fragment;
const int LIGHTNUM = 8;

void main()
{
	vec3 Vn = normalize(varN.xyz);
	vec3 sumColor = vec3(0.0, 0.0, 0.0);
	float col = 0.0;

	for(int i = 0; i < LIGHTNUM; i++) {
		if(i == fk_LightNum) break;
		if(fk_Light[i].type == 1) {
			col = clamp(-dot(Vn, fk_Light[i].vec), 0.0, 1.0);
		} else if(fk_Light[i].type == 2) {
			vec3 Vl = normalize(varP.xyz - fk_Light[i].position);
			col = clamp(-dot(Vn, Vl), 0.0, 1.0);
		} else {
			col = 0.0;
		}
		sumColor += fk_Light[i].diffuse.rgb * col;
	}
	sumColor *= fk_Material.diffuse.rgb;
	sumColor += fk_Material.ambient.rgb;
    fragment = vec4(min(sumColor, vec3(1.0, 1.0, 1.0)), fk_Material.diffuse.a);
}
