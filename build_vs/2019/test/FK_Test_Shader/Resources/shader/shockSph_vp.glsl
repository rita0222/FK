#version 410 core

#FKBuildIn

out vec4 varN;

//頂点シェーダ
void main(void)
{
	vec4 p = vec4(fk_Vertex, 1.0);

	gl_Position = fk_ModelViewProjectionMatrix * p;
	varN = fk_NormalModelViewMatrix * vec4(fk_Normal, 0.0);
}
