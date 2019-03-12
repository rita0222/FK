#version 330 core

#FKBuildIn

in int fk_PointElementAlive;
flat out vec4 put_color;

void main()
{
	vec4 p = vec4(fk_Vertex, 1.0);
	gl_Position = fk_ModelViewProjectionMatrix * p;
	put_color = fk_PointModelColor;
}
