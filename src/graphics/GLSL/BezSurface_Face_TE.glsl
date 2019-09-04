#version 410 core

#FKBuildIn

layout( quads ) in;

out vec4 varP;
out vec4 varN;
/*
void bezier(out float[4] b, out float[4] db, float t)
{
	float ot = 1.0 - t;

	b[0] = ot * ot * ot;
	b[1] = 3.0 * ot * ot * t;
	b[2] = 3.0 * ot * t * t;
	b[3] = t * t * t;

	db[0] = -3.0 * ot * ot;
	db[1] = -6.0 * t * ot + 3.0 * ot * ot;
	db[2] = -3.0 * t * t + 6.0 * t * ot;
	db[3] = 3.0 * t * t;
}
*/
void main()
{
/*
	float	u = gl_TessCoord.x;
	float	v = gl_TessCoord.y;
	vec3	cP[16];
	int		i, j;
	float	bu[4], bv[4];
	float	dbu[4], dbu[4];

	for(i = 0; i < 16; i++) {
		cP[i] = gl_in[i].gl_Position.xyz;
	}

	bezier(bu, dbu, u);
	bezier(bv, dbv, v);

	vec3 pos = vec3(0.0, 0.0, 0.0);
	vec3 dU = vec3(0.0, 0.0, 0.0);
	vec3 dV = vec3(0.0, 0.0, 0.0);

	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			pos += bu[j] * bv[i] * cP[i * 4 + j];
			dU += dbu[j] * bv[i] * cP[i * 4 + j];
			dV += bu[j] * dbv[i] * cP[i * 4 + j];
		}
	}

	vec4 P = vec4(pos, 1.0);
	vec4 N = vec4(normalize(cross(dU, dV)), 1.0);
*/
	float	u = gl_TessCoord.x;
	float	v = gl_TessCoord.y;
	float	uu = 1.0 - u;
	float	vv = 1.0 - v;

	vec3 cP00 = gl_in[0].gl_Position.xyz;
	vec3 cP10 = gl_in[1].gl_Position.xyz;
	vec3 CP01 = gl_in[4].gl_Position.xyz;
	vec3 CP11 = gl_in[5].gl_Position.xyz;
	
	vec3 pos = CP00 * uu * vv + CP10 * u * vv + CP01 * uu * v + CP11 * u * v;
	vec3 norm = normalize(cross(CP10 - CP00, CP01 - CP00));
	varP = fk_ModelMatrix * vec4(pos, 1.0);
	varN = fk_NormalMatrix * vec4(norm, 0.0);
	gl_Position = fk_ModelViewProjectionMatrix * vec4(pos, 1.0);
}
