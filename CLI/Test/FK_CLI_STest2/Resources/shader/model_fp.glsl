//varying変数
varying vec3 normal;
varying vec4 vertexPos;

//フラグメント
void main(void)
{
	////  ambientの計算  ////
	vec4 ambient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;

	////  diffuse計算  ////
	vec3 N = normalize(normal);
	vec3 L = normalize(gl_LightSource[0].position.xyz);
	float NdotL = dot(N, L);
	vec4 diffuse = max(0.0, NdotL) * gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;

	////  specular計算(Bilnのモデルを使用)  ////
	vec3 V = -normalize(vertexPos.xyz);
	vec3 H = normalize(V + L);
	float NdotH = dot(N, H);
	float k_specular = pow(max(0.0, NdotH), gl_FrontMaterial.shininess);
	vec4 specular = k_specular * gl_LightSource[0].specular * gl_FrontMaterial.specular;

	gl_FragColor = ambient + diffuse + specular;
}
