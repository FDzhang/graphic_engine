//"#ifdef GL_IMG_texture_stream2
//"#extension GL_IMG_texture_stream2 : enable
// "#endif
// uniform samplerStreamIMG streamtexture;
uniform sampler2D sampler2d1;
uniform sampler2D sampler2d2;
uniform sampler2D sampler2d3;
uniform sampler2D sampler2d4;
uniform sampler2D sampler2d5;
varying mediump vec2 varCoord1;
varying mediump float varWeight1;
varying mediump vec2 varCoord2;
varying mediump float varWeight2;
varying mediump vec2 varCoord3;
varying mediump float varWeight3;
varying mediump vec2 varCoord4;
varying mediump float varWeight4;
varying mediump vec2 varCoord5;
varying mediump float varWeight5;
void main (void)
{
    mediump vec3 texRGB1 = texture2D(sampler2d1, varCoord1).rgb;
	mediump vec3 texRGB2 = texture2D(sampler2d2, varCoord2).rgb;
	mediump vec3 texRGB3 = texture2D(sampler2d3, varCoord3).rgb;
	mediump vec3 texRGB4 = texture2D(sampler2d4, varCoord4).rgb;
	mediump vec3 texRGB5 = texture2D(sampler2d5, varCoord5).rgb;
	gl_FragColor.r = texRGB1.r * varWeight1 + texRGB2.r * varWeight2 + texRGB3.r * varWeight3 + texRGB4.r * varWeight4 + texRGB5.r * varWeight5; 
	gl_FragColor.g = texRGB1.g * varWeight1 + texRGB2.g * varWeight2 + texRGB3.g * varWeight3 + texRGB4.g * varWeight4 + texRGB5.g * varWeight5;
	gl_FragColor.b = texRGB1.b * varWeight1 + texRGB2.b * varWeight2 + texRGB3.b * varWeight3 + texRGB4.b * varWeight4 + texRGB5.b * varWeight5;
	gl_FragColor.a = 1.0;
}