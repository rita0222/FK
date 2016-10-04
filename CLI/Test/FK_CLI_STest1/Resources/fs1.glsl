uniform sampler2D tex;
varying vec4 pos;
varying vec2 fUV;
void main(void)
{
    gl_FragColor.rgb = texture2D(tex, fUV).rgb;
    gl_FragColor.a = 1.0;
}
