#version 410 core

#FKBuildIn

layout( quads, equal_spacing, ccw, point_mode ) in;

out vec4 varP;

void bezier(out float[5] b, float t)
{
	float ot = 1.0 - t;
	b[0] = ot * ot * ot;
	b[1] = 3.0 * ot * ot * t;
	b[2] = 3.0 * ot * t * t;
	b[3] = t * t * t;
}

void main()
{
	vec3	cP[25];
	float	bu[5], bv[5];
	int 	i, j, k;

	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;

	makeSurf(cP);

	bezier(bu, u);
	bezier(bv, v);

	vec3 pos = vec3(0.0, 0.0, 0.0);

	for(i = 0; i <= fk_Degree; i++) {
		for(j = 0; j <= fk_Degree; j++) {
			int k = i*(fk_Degree + 1)+j;
			pos += bu[j] * bv[i] * cP[k];
		}
	}
	
	vec4 P = vec4(pos, 1.0);

	varP = fk_ModelMatrix * P;
	gl_Position = fk_ModelViewProjectionMatrix * P;
}
