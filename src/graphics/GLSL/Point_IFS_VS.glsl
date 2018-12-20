#version 410 core

uniform mat4 fk_ModelViewMatrix;
uniform mat4 fk_ProjectionMatrix;
uniform vec4 fk_PointModelColor;

in vec3 fk_Vertex;
flat out vec4 put_color;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ProjectionMatrix * fk_ModelViewMatrix * p;
	put_color = fk_PointModelColor;
}
