uniform mat4 scale;
varying vec4 pos;
varying vec2 fUV;
attribute vec2 vUV;
void main(void)
{
    gl_Position = gl_ModelViewProjectionMatrix * scale * gl_Vertex;
    pos = gl_ModelViewProjectionMatrix * gl_Vertex;
    fUV = vUV;
}
