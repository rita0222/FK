//varying変数
varying vec3 normal;
varying vec4 vertexPos;

//頂点シェーダ
void main(void)
{
	//投影変換 (モデルビュー * プロジェクション) * 頂点座標
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;

	////各種基本的なベクトルを計算
	normal = gl_NormalMatrix * gl_Normal;				//法線を視点座標系にする
	vertexPos = gl_ModelViewMatrix * gl_Vertex;		//視点座標系の頂点位置
}
