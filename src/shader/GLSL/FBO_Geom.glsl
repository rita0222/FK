#version 410 core

layout( points ) in;
layout( triangle_strip, max_vertices = 4 ) out;

out vec2 fk_FBOTexCoord;

void main()
{
	gl_Position = vec4(-1.0, -1.0, 0.0, 1.0);
	fk_FBOTexCoord = vec2(0.0, 0.0);
	EmitVertex();
	gl_Position = vec4(1.0, -1.0, 0.0, 1.0);
	fk_FBOTexCoord = vec2(1.0, 0.0);
	EmitVertex();
	gl_Position = vec4(-1.0, 1.0, 0.0, 1.0);
	fk_FBOTexCoord = vec2(0.0, 1.0);
	EmitVertex();
	gl_Position = vec4(1.0, 1.0, 0.0, 1.0);
	fk_FBOTexCoord = vec2(1.0, 1.0);
	EmitVertex();
	EndPrimitive();
}
