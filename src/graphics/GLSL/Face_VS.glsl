#version 410 core

struct Material {
	vec4 diffuse;
	vec4 ambient;
};

uniform Material fk_Material;
uniform mat4 fk_ModelViewProjectionMatrix;
uniform mat4 fk_ModelMatrix;

in vec3 fk_Vertex;
in vec3 fk_Normal;
out vec4 outVec;
out vec4 outColor;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	outVec = fk_ModelMatrix * vec4(fk_Normal, 0.0);
	outColor = fk_Material.diffuse;
}
