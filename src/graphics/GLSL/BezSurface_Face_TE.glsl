#version 410 core

#FKBuildIn

layout( quads, equal_spacing, ccw ) in;

out vec4 varP;
out vec4 varN;

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

void main()
{
	vec3	cP[16];
	float	bu[4], bv[4], dbu[4], dbv[4];
	int i, j, k;

	for(i = 0; i < 16; i++) {
		cP[i] = gl_in[i].gl_Position.xyz;
	}

	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	float ou = 1.0 - u;
	float ov = 1.0 - v;

	bezier(bu, dbu, u);
	bezier(bv, dbv, v);

	vec3 pos = vec3(0.0, 0.0, 0.0);
	vec3 dU = vec3(0.0, 0.0, 0.0);
	vec3 dV = vec3(0.0, 0.0, 0.0);


	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			int k = i*4+j;
			pos += bu[i] * bv[j] * cP[k];
			dU += dbu[i] * bv[j] * cP[k];
			dV += bu[i] * dbv[j] * cP[k];
		}
	}
	
	vec4 P = vec4(pos, 1.0);
	vec4 N = vec4(normalize(cross(dU, dV)), 0.0);

	varP = fk_ModelMatrix * P;
	varN = fk_ModelMatrix * N;
	gl_Position = fk_ModelViewProjectionMatrix * P;
}
