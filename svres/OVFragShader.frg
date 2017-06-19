#extension GL_OES_EGL_image_external : require
uniform lowp samplerExternalOES srcImage;
uniform lowp sampler2D maskImage;
varying mediump vec2 TexCoord;
varying mediump vec2 TexCoord2;
varying mediump vec3 Luminance;
void main (void)
{
	lowp vec3 texyuv,texrgb;
	
	

	
    //if(TexCoord.x<0.0||TexCoord.y<0.0||TexCoord.y>1.0||TexCoord.x>1.0)
    //{ 
	  //  gl_FragColor.rgb = vec3(0.0,0.0,0.0);
	//}
	//else
    //{
        texrgb = texture2D(srcImage, vec2(TexCoord.x,TexCoord.y)).rgb;
        // gl_FragColor.rgb=texrgb;//*Luminance;
        gl_FragColor.r = 0.7*(Luminance.z-1.0)+(0.3*Luminance.x+0.7*Luminance.z)*texrgb.r+(0.587*(Luminance.x-Luminance.z))*texrgb.g+(0.114*(Luminance.x-Luminance.z))*texrgb.b;
        gl_FragColor.g = 0.1715*(1.0-Luminance.y)+0.3555*(1.0-Luminance.z)+(0.3*Luminance.x+0.058*Luminance.y-0.358*Luminance.z)*texrgb.r+(0.587*Luminance.x+0.1135*Luminance.y+0.2979*Luminance.z)*texrgb.g+(0.114*Luminance.x-0.1715*Luminance.y+0.0576*Luminance.z)*texrgb.b;   
        gl_FragColor.b = 0.8825*(Luminance.y-1.0)+(0.3*(Luminance.x-Luminance.y))*texrgb.r+0.587*(Luminance.x-Luminance.y)*texrgb.g+(0.114*Luminance.x+0.886*Luminance.y)*texrgb.b;
   // }

    gl_FragColor.a=texture2D(maskImage, TexCoord2).r;

	
}
