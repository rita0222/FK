#version 410 core

#FKBuildIn

layout( quads, equal_spacing, ccw, point_mode ) in;

out vec4 varP;
out vec4 varN;

void bezier(out float[5] b, out float[5] db, float t)
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
	vec3	cP[25];
	float	bu[5], bv[5], dbu[5], dbv[5];
	int 	i, j, k;

	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	float ou = 1.0 - u;
	float ov = 1.0 - v;

	for(i = 0; i < (fk_Degree + 1) * (fk_Degree + 1); i++) {
		cP[i] = gl_in[i].gl_Position.xyz;
	}

	bezier(bu, dbu, u);
	bezier(bv, dbv, v);

	vec3 pos = vec3(0.0, 0.0, 0.0);
	vec3 dU = vec3(0.0, 0.0, 0.0);
	vec3 dV = vec3(0.0, 0.0, 0.0);


	for(i = 0; i <= fk_Degree; i++) {
		for(j = 0; j <= fk_Degree; j++) {
			int k = i*(fk_Degree + 1)+j;
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
