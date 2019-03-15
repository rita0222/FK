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

uniform mat4 fk_ProjectionMatrix;
uniform mat4 fk_ViewMatrix;
uniform mat4 fk_ModelMatrix;
uniform mat4 fk_ModelViewMatrix;
uniform mat4 fk_ModelViewProjectionMatrix;
uniform mat4 fk_NormalModelMatrix;
uniform mat4 fk_NormalModelViewMatrix;

uniform vec3 fk_CameraPosition;

uniform Material fk_Material;
uniform ParallelLight fk_ParallelLight[LIGHTNUM];
uniform PointLight fk_PointLight[LIGHTNUM];
uniform SpotLight fk_SpotLight[LIGHTNUM];
uniform int fk_ParallelLightNum;
uniform int fk_PointLightNum;
uniform int fk_SpotLightNum;

uniform vec4 fk_LineModelColor;
uniform vec4 fk_PointModelColor;
uniform sampler2D fk_TexID[TEXTURENUM];

in vec4 fk_LineElementColor;
in vec4 fk_PointElementColor;
in vec3 fk_Vertex;
in vec3 fk_Normal;
in vec2 fk_TexCoord;

out vec4 fk_Fragment;
