#version 410 core

#FKBuildIn

layout( points ) in;
layout( triangle_strip, max_vertices = 3 ) out;

in vec2 pointV[];

void main()
{
	vec4 p;
	vec4 v1 = vec4(pointV[0].x, pointV[0].y, 0.0, 0.0);
	vec4 v2 = vec4(-v1.y, v1.x, 0.0, 0.0);

	p = gl_in[0].gl_Position + v1;
	gl_Position = fk_ModelViewProjectionMatrix * p;
	EmitVertex();

	p = gl_in[0].gl_Position + v2;
	gl_Position = fk_ModelViewProjectionMatrix * p;
	EmitVertex();

	p = gl_in[0].gl_Position - v2;
	gl_Position = fk_ModelViewProjectionMatrix * p;
	EmitVertex();

	EndPrimitive();
}
