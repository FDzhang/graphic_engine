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
   if(Flag == 0.0)
   {
 
        texrgb = texture2D(sampler2d, varCoord).rgb;
        
        gl_FragColor.r = 0.7*(cofLinear.z-1.0)+(0.3*cofLinear.x+0.7*cofLinear.z)*texrgb.r+(0.587*(cofLinear.x-cofLinear.z))*texrgb.g+(0.114*(cofLinear.x-cofLinear.z))*texrgb.b;
        gl_FragColor.g = 0.1715*(1.0-cofLinear.y)+0.3555*(1.0-cofLinear.z)+(0.3*cofLinear.x+0.058*cofLinear.y-0.358*cofLinear.z)*texrgb.r+(0.587*cofLinear.x+0.1135*cofLinear.y+0.2979*cofLinear.z)*texrgb.g+(0.114*cofLinear.x-0.1715*cofLinear.y+0.0576*cofLinear.z)*texrgb.b;   
        gl_FragColor.b = 0.8825*(cofLinear.y-1.0)+(0.3*(cofLinear.x-cofLinear.y))*texrgb.r+0.587*(cofLinear.x-cofLinear.y)*texrgb.g+(0.114*cofLinear.x+0.886*cofLinear.y)*texrgb.b;
      // gl_FragColor.rgb = cofLinear;
     
      //gl_FragColor.a = texture2D(sampler2d, varCoord).a; 
     gl_FragColor.a = varAlpha; 
     //gl_FragColor.rgb = CofL1;
    }
    else
    {
        // gl_FragColor = vec4(1.0,0.0,0.0,1.0); 
       gl_FragColor=  texture2D(sampler2d, varCoord);  
    }
}