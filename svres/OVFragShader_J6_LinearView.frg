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
        gl_FragColor = texture2D(srcImage, vec2(TexCoord.x,TexCoord.y));
   // }
	
}
