uniform sampler2D sampler2d;	 
varying mediump vec2 varCoord;
void main (void)
{
     gl_FragColor =  texture2D(sampler2d, varCoord);
}