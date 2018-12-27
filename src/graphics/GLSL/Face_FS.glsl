#version 410 core

in vec4 outVec;
in vec4 outColor;
out vec4 fragment;

const vec3 lightVec = vec3(1.0, 0.0, 0.0);

void main()
{
	vec3 v = normalize(outVec.xyz);
	float col = clamp(-dot(v, lightVec), 0.1, 1.0);
    fragment = vec4(outColor.rgb * col, 1.0);
}
