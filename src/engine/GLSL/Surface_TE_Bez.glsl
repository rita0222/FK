void makeSurf(out vec3[25] argCP)
{
	for(int i = 0; i < (fk_Degree + 1) * (fk_Degree + 1); i++) {
		argCP[i] = gl_in[i].gl_Position.xyz;
	}
}
