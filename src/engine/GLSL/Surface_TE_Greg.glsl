void makeSurf(out vec3[25] argCP)
{
	const float EPS = 0.00001;
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	float ou = 1.0 - u;
	float ov = 1.0 - v;

	argCP[0] = gl_in[0].gl_Position.xyz;
	argCP[1] = gl_in[1].gl_Position.xyz;
	argCP[2] = gl_in[2].gl_Position.xyz;
	argCP[3] = gl_in[3].gl_Position.xyz;
	argCP[12] = gl_in[4].gl_Position.xyz;
	argCP[13] = gl_in[5].gl_Position.xyz;
	argCP[14] = gl_in[6].gl_Position.xyz;
	argCP[15] = gl_in[7].gl_Position.xyz;
	argCP[4] = gl_in[8].gl_Position.xyz;
	argCP[8] = gl_in[9].gl_Position.xyz;
	argCP[7] = gl_in[10].gl_Position.xyz;
	argCP[11] = gl_in[11].gl_Position.xyz;

	if((u < EPS || ou < EPS) && (v < EPS || ov < EPS)) {
		argCP[5] = vec3(0.0, 0.0, 0.0);
		argCP[6] = vec3(0.0, 0.0, 0.0);
		argCP[9] = vec3(0.0, 0.0, 0.0);
		argCP[10] = vec3(0.0, 0.0, 0.0);
	} else {
		vec3 U = gl_in[12].gl_Position.xyz;
		vec3 V = gl_in[16].gl_Position.xyz;
		argCP[5] = (u * U + v * V)/(u + v);

		U = gl_in[13].gl_Position.xyz;
		V = gl_in[18].gl_Position.xyz;
		argCP[6] = (ou * U + v * V)/(ou + v);

		U = gl_in[14].gl_Position.xyz;
		V = gl_in[17].gl_Position.xyz;
		argCP[9] = (u * U + ov * V)/(u + ov);

		U = gl_in[15].gl_Position.xyz;
		V = gl_in[19].gl_Position.xyz;
		argCP[10] = (ou * U + ov * V)/(ou + ov);
	}
}
