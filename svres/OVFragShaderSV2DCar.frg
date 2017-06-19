//"#ifdef GL_IMG_texture_stream2
//"#extension GL_IMG_texture_stream2 : enable
// "#endif
// uniform samplerStreamIMG streamtexture;
uniform sampler2D sampler2d;	
uniform sampler2D sampText2D;	 
varying mediump vec2 varCoord;
varying mediump float varAlpha;
varying mediump vec3 cofLinear;
varying mediump vec3 CofL1;
varying mediump vec3 CofL2;
varying mediump float Flag;
void main (void)
{
   mediump vec3 CofRGB;	
   mediump vec3 texrgb;	
   mediump vec4 test;
   test = vec4(1.0,1.0,1.0,0.2);

       //gl_FragColor = vec4(1.0,0.0,0.0,0.2); 
       gl_FragColor=  texture2D(sampler2d, varCoord); 
       gl_FragColor.a = gl_FragColor.a*0.3;
     
 

}
