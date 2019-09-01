#version 410 core

#FKBuildIn

layout( isolines ) in;

void main()
{
	float t1 = gl_TessCoord.x;
	float t2 = (1.0 - t1);
	float b0 = t2 * t2 * t2;
	float b1 = 3.0 * t1 * t2 * t2;
	float b2 = 3.0 * t1 * t1 * t2;
	float b3 = t1 * t1 * t1;

	vec3 p0 = gl_in[0].gl_Position.xyz;
	vec3 p1 = gl_in[1].gl_Position.xyz;
	vec3 p2 = gl_in[2].gl_Position.xyz;
	vec3 p3 = gl_in[3].gl_Position.xyz;

	vec3 p = p0 * b0 + p1 * b1 + p2 * b2 + p3 * b3;

	gl_Position = fk_ModelViewProjectionMatrix * vec4(p, 1.0);
}
