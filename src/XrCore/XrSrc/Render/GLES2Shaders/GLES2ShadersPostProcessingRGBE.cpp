
#include "GLES2Shaders.h"

#include "../XrRender.h"

#ifndef USE_DX11
const char* PP_Blit = "PP_Blit";
/////////////////// 001 Shader_UI_Spirit /////////////////////
const char* PP_Blit_vs = "\
attribute vec3 PosAttribute;\n\
attribute vec2 TexAttribute; \
precision highp float;\n\
varying highp vec2 TexCoord;\n\
void main()\n\
{\n\
	gl_Position = vec4(PosAttribute, 1.0);\n\
	TexCoord    = TexAttribute; \
}";
const char* PP_Blit_fs = "\
precision highp float;\n\
varying highp vec2 TexCoord;\n\
uniform sampler2D sampler;\n\
void main()\n\
{\n\
	gl_FragColor = texture2D(sampler, TexCoord);\n\
}";

XRVertexLayout PP_Blit_layout_index = XR_VERTEX_LAYOUT_PT;
UInt32 PP_Blit_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;

const char* PP_Down4X = "PP_Down4X";
/////////////////// 001 Shader_UI_Spirit /////////////////////
const char* PP_Down4X_vs = "\
attribute highp vec3 PosAttribute;\n\
attribute highp vec2 TexAttribute;\n\
precision highp float;\n\
uniform highp vec2 twoTexelSize;\n\
varying highp vec2 TexCoord1;\n\
varying highp vec2 TexCoord2;\n\
varying highp vec2 TexCoord3;\n\
varying highp vec2 TexCoord4;\n\
void main()\n\
{\n\
  TexCoord1 = TexAttribute;\n\
  TexCoord2 = TexAttribute + vec2(twoTexelSize.x, 0);\n\
  TexCoord3 = TexAttribute + vec2(twoTexelSize.x, twoTexelSize.y);\n\
  TexCoord4 = TexAttribute + vec2(0, twoTexelSize.y);\n\
  gl_Position = vec4(PosAttribute, 1.0);\n\
}";
const char* PP_Down4X_fs = "\
precision highp float;\n\
varying highp vec2 TexCoord1;\n\
varying highp vec2 TexCoord2;\n\
varying highp vec2 TexCoord3;\n\
varying highp vec2 TexCoord4;\n\
uniform sampler2D sampler;\n\
void main()\n\
{\n\
		gl_FragColor = (texture2D(sampler, TexCoord1) + \
            				texture2D(sampler, TexCoord2) +\
            				texture2D(sampler, TexCoord3) +\
            				texture2D(sampler, TexCoord4)) * 0.25;\n\
}";

XRVertexLayout PP_Down4X_layout_index = XR_VERTEX_LAYOUT_PT;
UInt32 PP_Down4X_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;



const char* PP_ExtractHL = "PP_ExtractHL";
/////////////////// 001 Shader_UI_Spirit /////////////////////
const char* PP_ExtractHL_vs = "\
attribute vec3 PosAttribute;\n\
attribute vec2 TexAttribute;\n\
precision highp float;\n\
varying highp vec2 TexCoord;\n\
void main()\n\
{\n\
	gl_Position = vec4(PosAttribute, 1.0);\n\
	TexCoord    = TexAttribute; \
}";
const char* PP_ExtractHL_fs = "\
precision highp float;\n\
varying highp vec2 TexCoord;\n\
uniform highp float threshold;\n\
uniform highp float scalar;\n\
uniform sampler2D sampler;\n\
highp vec4 EncodeRGBE8( highp vec3 rgb )\n\
{\n\
	highp vec4 ret ;\n\
	highp float fLen = max(rgb.r, rgb.g) ;\n\
	fLen = max(fLen, rgb.b) ;\n\
	highp float fExp = floor( log(fLen)/log(1.05) ) ;\n\
	ret.a = clamp( (fExp + 128.0) / 256.0, 0.0, 1.0 ) ;\n\
	ret.rgb = rgb / pow(1.05, ret.a * 256.0 - 128.0) ;\n\
	return ret;\n\
}\n\
highp vec3 texture2DRGBE8( sampler2D sampler, highp vec2 texCoord)\n\
{\n\
    highp vec4 rgbe = texture2D(sampler, texCoord);\n\
	highp float fExp = rgbe.a * 256.0 - 128.0 ;\n\
	highp float fScaler = pow(1.05, fExp);\n\
	return (rgbe.rgb * fScaler) ;\n\
}\n\
void main()\n\
{\n\
	gl_FragColor = EncodeRGBE8(max((texture2DRGBE8(sampler, TexCoord) - threshold)*scalar, vec3(0.0,0.0,0.0)));\n\
}";

XRVertexLayout PP_ExtractHL_layout_index = XR_VERTEX_LAYOUT_PT;
UInt32 PP_ExtractHL_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;

const char* PP_GaussComp = "PP_GaussComp";
/////////////////// 001 Shader_UI_Spirit /////////////////////
const char* PP_GaussComp_vs = "\
attribute vec3 PosAttribute;\n\
attribute vec2 TexAttribute;\n\
precision highp float;\n\
varying highp vec2 TexCoord;\n\
void main()\n\
{\n\
	gl_Position = vec4(PosAttribute, 1.0);\n\
	TexCoord    = TexAttribute;\n\
}";
const char* PP_GaussComp_fs = "\
precision highp float;\n\
varying highp vec2 TexCoord;\n\
uniform highp vec4 coeff;\n\
uniform sampler2D sampler1;\n\
uniform sampler2D sampler2;\n\
uniform sampler2D sampler3;\n\
uniform sampler2D sampler4;\n\
highp vec4 EncodeRGBE8( highp vec3 rgb )\n\
{\n\
	highp vec4 ret ;\n\
	highp float fLen = max(rgb.r, rgb.g) ;\n\
	fLen = max(fLen, rgb.b) ;\n\
	highp float fExp = floor( log(fLen)/log(1.05) ) ;\n\
	ret.a = clamp( (fExp + 128.0) / 256.0, 0.0, 1.0 ) ;\n\
	ret.rgb = rgb / pow(1.05, ret.a * 256.0 - 128.0) ;\n\
	return ret;\n\
}\n\
highp vec3 texture2DRGBE8( sampler2D sampler, highp vec2 texCoord)\n\
{\n\
    highp vec4 rgbe = texture2D(sampler, texCoord);\n\
	highp float fExp = rgbe.a * 256.0 - 128.0 ;\n\
	highp float fScaler = pow(1.05, fExp);\n\
	return (rgbe.rgb * fScaler) ;\n\
}\n\
void main()\n\
{\n\
	gl_FragColor = EncodeRGBE8(texture2DRGBE8(sampler1, TexCoord)*coeff.x + texture2DRGBE8(sampler2, TexCoord)*coeff.y + texture2DRGBE8(sampler3, TexCoord)*coeff.z + texture2DRGBE8(sampler4, TexCoord)*coeff.w);\n\
}";

XRVertexLayout PP_GaussComp_layout_index = XR_VERTEX_LAYOUT_PT;
UInt32 PP_GaussComp_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;

const char* PP_GhostImage = "PP_GhostImage";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* PP_GhostImage_vs = "\
attribute highp vec3 PosAttribute;\n\
attribute highp vec2 TexAttribute;\n\
precision highp float;\n\
uniform highp vec4 scalar;\n\
varying highp vec2 TexCoord1;\n\
varying highp vec2 TexCoord2;\n\
varying highp vec2 TexCoord3;\n\
varying highp vec2 TexCoord4;\n\
void main()\n\
{\n\
  TexCoord1 = (TexAttribute - 0.5) * scalar[0] + 0.5;\n\
  TexCoord2 = (TexAttribute - 0.5) * scalar[1] + 0.5;\n\
  TexCoord3 = (TexAttribute - 0.5) * scalar[2] + 0.5;\n\
  TexCoord4 = (TexAttribute - 0.5) * scalar[3] + 0.5;\n\
  gl_Position = vec4(PosAttribute, 1.0);\n\
}";
const char* PP_GhostImage_fs = "\
precision highp float;\n\
uniform highp vec4 colorCoeff[4];\n\
varying highp vec2 TexCoord1;\n\
varying highp vec2 TexCoord2;\n\
varying highp vec2 TexCoord3;\n\
varying highp vec2 TexCoord4;\n\
uniform sampler2D sampler1;\n\
uniform sampler2D sampler2;\n\
uniform sampler2D sampler3;\n\
uniform sampler2D sampler4;\n\
highp vec4 EncodeRGBE8( highp vec3 rgb )\n\
{\n\
	highp vec4 ret ;\n\
	highp float fLen = max(rgb.r, rgb.g) ;\n\
	fLen = max(fLen, rgb.b) ;\n\
	highp float fExp = floor( log(fLen)/log(1.05) ) ;\n\
	ret.a = clamp( (fExp + 128.0) / 256.0, 0.0, 1.0 ) ;\n\
	ret.rgb = rgb / pow(1.05, ret.a * 256.0 - 128.0) ;\n\
	return ret;\n\
}\n\
highp vec3 texture2DRGBE8( sampler2D sampler, highp vec2 texCoord)\n\
{\n\
    highp vec4 rgbe = texture2D(sampler, texCoord);\n\
	highp float fExp = rgbe.a * 256.0 - 128.0 ;\n\
	highp float fScaler = pow(1.05, fExp);\n\
	return (rgbe.rgb * fScaler) ;\n\
}\n\
void main()\n\
{\n\
gl_FragColor = EncodeRGBE8(texture2DRGBE8(sampler1, TexCoord1)*texture2D(sampler4, TexCoord1).r*colorCoeff[0].rgb + texture2DRGBE8(sampler1, TexCoord2)*texture2D(sampler4, TexCoord2).r*colorCoeff[1].rgb + texture2DRGBE8(sampler2, TexCoord3)*texture2D(sampler4, TexCoord3).r*colorCoeff[2].rgb + texture2DRGBE8(sampler3, TexCoord4)*texture2D(sampler4, TexCoord4).r*colorCoeff[3].rgb);\n\
}";

XRVertexLayout PP_GhostImage_layout_index = XR_VERTEX_LAYOUT_PT;
UInt32 PP_GhostImage_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;



const char* PP_GlareComp = "PP_GlareComp";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* PP_GlareComp_vs = "\
attribute vec3 PosAttribute;\n\
attribute vec2 TexAttribute;\n\
precision highp float;\n\
varying highp vec2 TexCoord;\n\
void main()\n\
{\n\
	gl_Position = vec4(PosAttribute, 1.0);\n\
	TexCoord    = TexAttribute;\n\
}";

const char* PP_GlareComp_fs = "\
precision highp float;\n\
varying highp vec2 TexCoord;\n\
uniform highp vec4 mixCoeff;\n\
uniform sampler2D sampler1;\n\
uniform sampler2D sampler2;\n\
uniform sampler2D sampler3;\n\
highp vec4 EncodeRGBE8( highp vec3 rgb )\n\
{\n\
	highp vec4 ret ;\n\
	highp float fLen = max(rgb.r, rgb.g) ;\n\
	fLen = max(fLen, rgb.b) ;\n\
	highp float fExp = floor( log(fLen)/log(1.05) ) ;\n\
	ret.a = clamp( (fExp + 128.0) / 256.0, 0.0, 1.0 ) ;\n\
	ret.rgb = rgb / pow(1.05, ret.a * 256.0 - 128.0) ;\n\
	return ret;\n\
}\n\
highp vec3 texture2DRGBE8( sampler2D sampler, highp vec2 texCoord)\n\
{\n\
    highp vec4 rgbe = texture2D(sampler, texCoord);\n\
	highp float fExp = rgbe.a * 256.0 - 128.0 ;\n\
	highp float fScaler = pow(1.05, fExp);\n\
	return (rgbe.rgb * fScaler) ;\n\
}\n\
void main()\n\
{\n\
gl_FragColor = EncodeRGBE8(texture2DRGBE8(sampler1, TexCoord)*mixCoeff.x + texture2DRGBE8(sampler2, TexCoord)*mixCoeff.y + texture2DRGBE8(sampler3, TexCoord)*mixCoeff.z);\n\
}";

XRVertexLayout PP_GlareComp_layout_index = XR_VERTEX_LAYOUT_PT;
UInt32 PP_GlareComp_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;


const char* PP_StarComp = "PP_StarComp";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* PP_StarComp_vs = "\
					   attribute vec3 PosAttribute;\n\
attribute vec2 TexAttribute;\n\
precision highp float;\n\
varying highp vec2 TexCoord;\n\
void main()\n\
{\n\
	gl_Position = vec4(PosAttribute, 1.0);\n\
	TexCoord    = TexAttribute;\n\
}";

const char* PP_StarComp_fs = "\
precision highp float;\n\
varying highp vec2 TexCoord;\n\
uniform highp vec4 coeff;\n\
uniform sampler2D sampler1;\n\
uniform sampler2D sampler2;\n\
uniform sampler2D sampler3;\n\
uniform sampler2D sampler4;\n\
highp vec4 EncodeRGBE8( highp vec3 rgb )\n\
{\n\
	highp vec4 ret ;\n\
	highp float fLen = max(rgb.r, rgb.g) ;\n\
	fLen = max(fLen, rgb.b) ;\n\
	highp float fExp = floor( log(fLen)/log(1.05) ) ;\n\
	ret.a = clamp( (fExp + 128.0) / 256.0, 0.0, 1.0 ) ;\n\
	ret.rgb = rgb / pow(1.05, ret.a * 256.0 - 128.0) ;\n\
	return ret;\n\
}\n\
highp vec3 texture2DRGBE8( sampler2D sampler, highp vec2 texCoord)\n\
{\n\
    highp vec4 rgbe = texture2D(sampler, texCoord);\n\
	highp float fExp = rgbe.a * 256.0 - 128.0 ;\n\
	highp float fScaler = pow(1.05, fExp);\n\
	return (rgbe.rgb * fScaler) ;\n\
}\n\
void main()\n\
{\n\
  highp vec3 color1 = max(texture2DRGBE8(sampler1, TexCoord), texture2DRGBE8(sampler2, TexCoord));\n\
  highp vec3 color2 = max(texture2DRGBE8(sampler3, TexCoord), texture2DRGBE8(sampler4, TexCoord));\n\
  gl_FragColor = EncodeRGBE8(max(color1, color2));\n\
}";

XRVertexLayout PP_StarComp_layout_index = XR_VERTEX_LAYOUT_PT;
UInt32 PP_StarComp_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;


const char* PP_StarStreak = "PP_StarStreak";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* PP_StarStreak_vs = "\
attribute highp vec3 PosAttribute;\n\
attribute highp vec2 TexAttribute;\n\
precision highp float;\n\
uniform highp vec2 stepSize;\n\
uniform highp float Stride;\n\
varying highp vec2 TexCoord1;\n\
varying highp vec2 TexCoord2;\n\
varying highp vec2 TexCoord3;\n\
varying highp vec2 TexCoord4;\n\
void main()\n\
{\n\
  TexCoord1 = TexAttribute;\n\
  TexCoord2 = TexAttribute + stepSize*Stride;\n\
  TexCoord3 = TexAttribute + stepSize*2.0*Stride;\n\
  TexCoord4 = TexAttribute + stepSize*3.0*Stride;\n\
  gl_Position = vec4(PosAttribute, 1.0);\n\
}";
const char* PP_StarStreak_fs = "\
precision highp float;\n\
uniform highp vec4 colorCoeff[4];\n\
varying highp vec2 TexCoord1;\n\
varying highp vec2 TexCoord2;\n\
varying highp vec2 TexCoord3;\n\
varying highp vec2 TexCoord4;\n\
uniform sampler2D sampler;\n\
highp vec4 EncodeRGBE8( highp vec3 rgb )\n\
{\n\
	highp vec4 ret ;\n\
	highp float fLen = max(rgb.r, rgb.g) ;\n\
	fLen = max(fLen, rgb.b) ;\n\
	highp float fExp = floor( log(fLen)/log(1.05) ) ;\n\
	ret.a = clamp( (fExp + 128.0) / 256.0, 0.0, 1.0 ) ;\n\
	ret.rgb = rgb / pow(1.05, ret.a * 256.0 - 128.0) ;\n\
	return ret;\n\
}\n\
highp vec3 texture2DRGBE8( sampler2D sampler, highp vec2 texCoord)\n\
{\n\
    highp vec4 rgbe = texture2D(sampler, texCoord);\n\
	highp float fExp = rgbe.a * 256.0 - 128.0 ;\n\
	highp float fScaler = pow(1.05, fExp);\n\
	return (rgbe.rgb * fScaler) ;\n\
}\n\
void main()\n\
{\n\
gl_FragColor = EncodeRGBE8(texture2DRGBE8(sampler, TexCoord1)*colorCoeff[0].rgb + texture2DRGBE8(sampler, TexCoord2)*colorCoeff[1].rgb + texture2DRGBE8(sampler, TexCoord3)*colorCoeff[2].rgb + texture2DRGBE8(sampler, TexCoord4)*colorCoeff[3].rgb);\n\
}";

XRVertexLayout PP_StarStreak_layout_index = XR_VERTEX_LAYOUT_PT;
UInt32 PP_StarStreak_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;

const char* PP_Tonemapping = "PP_Tonemapping";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* PP_Tonemapping_vs = "\
attribute highp vec3 PosAttribute;\n\
attribute highp vec2 TexAttribute;\n\
precision highp float;\n\
varying highp vec2 TexCoord;\n\
void main()\n\
{\n\
	gl_Position = vec4(PosAttribute, 1.0);\n\
	TexCoord    = TexAttribute; \
}";
const char* PP_Tonemapping_fs = "\
precision highp float;\n\
varying highp vec2 TexCoord;\n\
uniform sampler2D sceneTex;\n\
uniform sampler2D blurTex;\n\
uniform highp float blurAmount;\n\
uniform highp float effectAmount;\n\
uniform highp float exposure;\n\
uniform highp float gamma;\n\
highp vec4 EncodeRGBE8( highp vec3 rgb )\n\
{\n\
	highp vec4 ret ;\n\
	highp float fLen = max(rgb.r, rgb.g);\n\
	fLen = max(fLen, rgb.b) ;\n\
	highp float fExp = floor( log(fLen)/log(1.05) ) ;\n\
	ret.a = clamp( (fExp + 128.0) / 256.0, 0.0, 1.0 ) ;\n\
	ret.rgb = rgb / pow(1.05, ret.a * 256.0 - 128.0) ;\n\
	return ret;\n\
}\n\
highp vec3 texture2DRGBE8( sampler2D sampler, highp vec2 texCoord)\n\
{\n\
    highp vec4 rgbe = texture2D(sampler, texCoord);\n\
	highp float fExp = rgbe.a * 256.0 - 128.0 ;\n\
	highp float fScaler = pow(1.05, fExp);\n\
	return (rgbe.rgb * fScaler) ;\n\
}\n\
highp float vignette(highp vec2 pos, highp float inner, highp float outer)\n\
{\n\
  highp float r = length(pos);\n\
  r = 1.0 - smoothstep(inner, outer, r);\n\
  return r;\n\
}\n\
void main()\n\
{\n\
    highp vec3 scene = texture2DRGBE8(sceneTex, TexCoord);\n\
    highp vec3 blurred = texture2DRGBE8(blurTex, TexCoord);\n\
    highp vec3 c = mix(scene, blurred, blurAmount);\n\
    c = c * exposure;\n\
    c = c * vignette(TexCoord*2.0-1.0, 0.55, 1.5);\n\
    c.r = pow(c.r, gamma);\n\
    c.g = pow(c.g, gamma);\n\
    c.b = pow(c.b, gamma);\n\
	gl_FragColor = vec4(c,1.0);\n\
}";


XRVertexLayout PP_Tonemapping_layout_index = XR_VERTEX_LAYOUT_PT;
UInt32 PP_Tonemapping_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;

#endif