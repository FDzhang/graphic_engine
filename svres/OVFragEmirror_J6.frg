#extension GL_OES_EGL_image_external : require
uniform lowp samplerExternalOES srcImage;
uniform lowp sampler2D maskImage;
varying mediump vec2 TexCoord;
varying mediump vec2 TexCoord2;
varying mediump vec3 Luminance;
varying mediump vec2 Alpha;
void main (void)
{
	lowp vec3 texyuv,texrgb;
	
	
        gl_FragColor=texture2D(srcImage, vec2(TexCoord.x,TexCoord.y));
        gl_FragColor.a = Alpha.x;

       

	
}
