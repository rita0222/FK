#version 410 core

in vec4 outVec;
out vec4 fragment;

const vec3 lightVec = vec3(1.0, 0.0, 0.0);

void main()
{
	vec3 v = normalize(outVec.xyz);
	float col = clamp(-dot(v, lightVec), 0.1, 1.0);
    fragment = vec4(col, col, 0.0, 1.0);
}
