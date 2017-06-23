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
   if(Flag == 0.0)
   {
     // gl_FragColor.rgb =  textureStreamIMG(streamtexture, varCoord).rgb*CofRGB;
     //gl_FragColor = vec4(1.0,0.0,0.0,1.0);  
     gl_FragColor.rgb =  texture2D(sampler2d, varCoord).rgb*cofLinear;  
     gl_FragColor.a = varAlpha; 
    }
    else
    {
        // gl_FragColor = vec4(1.0,0.0,0.0,1.0); 
       gl_FragColor=  texture2D(sampler2d, varCoord);  
    }
}