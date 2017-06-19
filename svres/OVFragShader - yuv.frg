uniform lowp sampler2D srcImage;
varying mediump vec2 TexCoord;
varying mediump vec2 TexCoord2;
varying mediump vec3 Luminance;
void main (void)
{
	lowp vec3 texyuv,texrgb;

	
    if(TexCoord.x<0.0||TexCoord.y<0.0||TexCoord.y>1.0||TexCoord.x>1.0)
    { 
	    gl_FragColor.rgb = vec3(0.0,0.0,0.0);
	}
	else
    {
	texyuv.x= 1.1643*(texture2D(srcImage, vec2(TexCoord.x,(TexCoord.y/2.0+0.5))).r-0.0625);
	texyuv.y= texture2D(srcImage, vec2(TexCoord.x,(TexCoord.y/2.0+0.5))).g-0.5;	
	texyuv.z= texture2D(srcImage, vec2(TexCoord.x,(TexCoord.y/2.0+0.5))).b-0.5;
	texrgb.r = texyuv.x+1.5958*texyuv.z;
	texrgb.g = texyuv.x-0.39173*texyuv.y-0.8129*texyuv.z;
    texrgb.b = texyuv.x+2.017*texyuv.y;		
	gl_FragColor.rgb = texrgb*Luminance;    
 	  // gl_FragColor.rgb = texture2D(srcImage, vec2(TexCoord.x,TexCoord.y/2.0)).rgb*Luminance;   
    }
	gl_FragColor.a = TexCoord2.x;
}
