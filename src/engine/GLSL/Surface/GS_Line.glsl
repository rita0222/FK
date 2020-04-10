#version 410 core

#FKBuildIn

layout ( triangles ) in;
layout ( line_strip, max_vertices = 4 ) out;

in vec4 varPP[];
out vec4 varP;

void main()
{
	gl_Position = gl_in[0].gl_Position;
	varP = varPP[0];
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	varP = varPP[1];
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	varP = varPP[2];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position;
	varP = varPP[0];
	EmitVertex();

	EndPrimitive();
}
