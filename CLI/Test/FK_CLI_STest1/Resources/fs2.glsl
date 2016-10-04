uniform sampler2D tex;
varying vec2 fUV;
void main(void)
{
    gl_FragColor.rgb = texture2D(tex, fUV).rrr; 
    gl_FragColor.a = 1.0; 
}
