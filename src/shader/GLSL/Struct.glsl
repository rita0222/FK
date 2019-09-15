const int TEXTURENUM = 8;
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
	vec3 attenuation;
};

struct SpotLight {
	vec3 position;
	vec3 vec;
	vec4 diffuse;
	vec4 specular;
	vec3 attenuation;
	float cut;
	float exp;
};
