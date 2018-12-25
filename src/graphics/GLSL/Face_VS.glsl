#version 410 core

uniform mat4 fk_ModelViewProjectionMatrix;
uniform mat4 fk_ModelMatrix;

in vec3 fk_Vertex;
in vec3 fk_Normal;
out float outCol;

const vec3 lightVec = vec3(1.0, 0.0, 0.0);

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	vec4 n = vec4(fk_Normal, 0.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	vec4 tmp = fk_ModelMatrix * n;
	outCol = clamp(-dot(tmp.xyz, lightVec), 0.0, 1.0);
}
