#ifdef GL_IMG_texture_stream2
#extension GL_IMG_texture_stream2 : enable
#endif
precision mediump float;
uniform sampler2D srcImage;
varying mediump vec2 TexCoord;
varying mediump vec2 TexCoord2;
void main (void)
{
	gl_FragColor = texture2D(srcImage, TexCoord);
       // gl_FragColor.rgb = vec3(1.0,0.0,0.0);
	//gl_FragColor.a = TexCoord2.x;
}

