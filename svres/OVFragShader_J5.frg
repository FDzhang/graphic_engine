#ifdef GL_IMG_texture_stream2
#extension GL_IMG_texture_stream2 : enable
#endif
precision mediump float;
uniform samplerStreamIMG srcImage;
varying mediump vec2 TexCoord;
varying mediump vec2 TexCoord2;
varying mediump vec3 Luminance;
void main (void)
{
	gl_FragColor.rgb = textureStreamIMG(srcImage, TexCoord).rgb*Luminance;
	gl_FragColor.a = TexCoord2.x;
}

