#version 410 core

#FKBuildIn

subroutine void surfType (out vec3 [25]);
subroutine uniform surfType surfSelect;

layout( quads, equal_spacing, ccw ) in;

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

subroutine(surfType)
void BezSurf(out vec3[25] argCP)
{
	for(int i = 0; i < (fk_Degree + 1) * (fk_Degree + 1); i++) {
		argCP[i] = gl_in[i].gl_Position.xyz;
	}
}

subroutine(surfType)
void GregSurf(out vec3[25] argCP)
{
	const float EPS = 0.00001;
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	float ou = 1.0 - u;
	float ov = 1.0 - v;

	// U_S
	argCP[0] = gl_in[0].gl_Position.xyz;
	argCP[1] = gl_in[1].gl_Position.xyz;
	argCP[2] = gl_in[2].gl_Position.xyz;
	argCP[3] = gl_in[3].gl_Position.xyz;

	// U_E
	argCP[12] = gl_in[4].gl_Position.xyz;
	argCP[13] = gl_in[5].gl_Position.xyz;
	argCP[14] = gl_in[6].gl_Position.xyz;
	argCP[15] = gl_in[7].gl_Position.xyz;

	// V_S
	argCP[4] = gl_in[8].gl_Position.xyz;
	argCP[8] = gl_in[9].gl_Position.xyz;

	// V_E
	argCP[7] = gl_in[10].gl_Position.xyz;
	argCP[11] = gl_in[11].gl_Position.xyz;

	if((u < EPS || ou < EPS) && (v < EPS || ov < EPS)) {
		argCP[5] = gl_in[12].gl_Position.xyz;
		argCP[6] = gl_in[13].gl_Position.xyz;
		argCP[9] = gl_in[14].gl_Position.xyz;
		argCP[10] = gl_in[15].gl_Position.xyz;
	} else {
		// (1, 1) = (u, v)
		vec3 U = gl_in[12].gl_Position.xyz;
		vec3 V = gl_in[16].gl_Position.xyz;
		argCP[5] = (u * U + v * V)/(u + v);

		// (1, 2) = (ou, v)
		U = gl_in[13].gl_Position.xyz;
		V = gl_in[18].gl_Position.xyz;
		argCP[6] = (ou * U + v * V)/(ou + v);

		// (2, 1) = (u, ov)
		U = gl_in[14].gl_Position.xyz;
		V = gl_in[17].gl_Position.xyz;
		argCP[9] = (u * U + ov * V)/(u + ov);

		// (2, 2) = (ou, ov)
		U = gl_in[15].gl_Position.xyz;
		V = gl_in[19].gl_Position.xyz;
		argCP[10] = (ou * U + ov * V)/(ou + ov);
	}
}

void main()
{
	vec3	cP[25];
	float	bu[5], bv[5], dbu[5], dbv[5];
	int 	i, j, k;

	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;

	surfSelect(cP);

	bezier(bu, dbu, u);
	bezier(bv, dbv, v);

	vec3 pos = vec3(0.0, 0.0, 0.0);
	vec3 dU = vec3(0.0, 0.0, 0.0);
	vec3 dV = vec3(0.0, 0.0, 0.0);

	for(i = 0; i <= fk_Degree; i++) {
		for(j = 0; j <= fk_Degree; j++) {
			int k = i*(fk_Degree + 1)+j;
			pos += bu[j] * bv[i] * cP[k];
			dU += dbu[j] * bv[i] * cP[k];
			dV += bu[j] * dbv[i] * cP[k];
		}
	}

	vec4 P = vec4(pos, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * P;
}
