varying vec2 fUV;
void main(void)
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    fUV = gl_MultiTexCoord0.xy;
}
