vec4 curveFunc()
{
	float t1 = gl_TessCoord.x;
	float t2 = (1.0 - t1);
	float b0 = t2 * t2 * gl_in[0].gl_Position.w;
	float b1 = 2.0 * t1 * t2 * gl_in[1].gl_Position.w;
	float b2 = t1 * t1 * gl_in[2].gl_Position.w;

	vec3 p0 = gl_in[0].gl_Position.xyz;
	vec3 p1 = gl_in[1].gl_Position.xyz;
	vec3 p2 = gl_in[2].gl_Position.xyz;

	vec3 p = (p0 * b0 + p1 * b1 + p2 * b2)/(b0 + b1 + b2);
	return vec4(p, 1.0);
}
