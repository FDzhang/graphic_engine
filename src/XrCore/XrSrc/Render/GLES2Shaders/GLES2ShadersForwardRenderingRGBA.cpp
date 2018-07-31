
#include "GLES2Shaders.h"

#include "../XrRender.h"
#ifndef USE_DX11

const char* FR_RigidTexture = "FR_RigidTexture";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* FR_RigidTexture_vs = "\
attribute highp vec4 VertexPos;\n\
attribute highp vec4 VertexNormal;\n\
attribute highp vec2 InTexCood;\n\
uniform highp mat4 ViewProjMatrix;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
void main(void)\n\
{\n\
	gl_Position = ViewProjMatrix * VertexPos;\n\
	Normal = VertexNormal.xyz;\n\
	TexCoord = InTexCood;\n\
}";
const char* FR_RigidTexture_fs = "\
uniform highp sampler2D sampler2d;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
void main (void)\n\
{\n\
	gl_FragColor = texture2D(sampler2d, TexCoord);\n\
}";

XRVertexLayout FR_RigidTexture_layout_index = XR_VERTEX_LAYOUT_PNT;

UInt32 FR_RigidTexture_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;
//UInt32 FR_RigidTexture_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;

const char* FR_RigidColorTexture = "FR_RigidColorTexture";
/////////////////// 00X Shader_GhostImage /////////////////////
const char* FR_RigidColorTexture_vs = "\
attribute highp vec4 VertexPos;\n\
attribute highp vec4 VertexNormal;\n\
attribute highp vec2 InTexCood;\n\
uniform highp mat4 ViewProjMatrix;\n\
uniform mediump vec4 InTexColor;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
varying mediump vec4 TextColor;\n\
void main(void)\n\
{\n\
	gl_Position = ViewProjMatrix * VertexPos;\n\
	Normal = VertexNormal.xyz;\n\
	TexCoord = InTexCood;\n\
    if((VertexPos.x<0.0&&InTexColor.w == 1.0)||(VertexPos.x>0.0&&InTexColor.w == 2.0)\
    ||(InTexColor.w ==3.0))\n\
    {\n\
        TextColor.xyz=InTexColor.xyz;\n\
        TextColor.w=0.0;\n\
    }\n\
    else\n\
	{\n\
        TextColor.xyz = vec3(1.0,1.0,1.0);\n\
        TextColor.w=1.0;\n\
    }\n\
}";
const char* FR_RigidColorTexture_fs = "\
uniform highp sampler2D sampler2d;\n\
uniform highp sampler2D samplerAlpha;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
varying mediump vec4 TextColor;\n\
void main (void)\n\
{\n\
    gl_FragColor = texture2D(sampler2d, TexCoord)*TextColor.w+texture2D(samplerAlpha,TexCoord)*(1.0-TextColor.a);\n\
}";

XRVertexLayout FR_RigidColorTexture_layout_index = XR_VERTEX_LAYOUT_PNT;

UInt32 FR_RigidColorTexture_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;
//gl_FragColor = texture2D(sampler2d, TexCoord);\n\
//    gl_FragColor.rgb = gl_FragColor.rgb*TextColor;\n\
//gl_FragColor.rgb = gl_FragColor.rgb*TextColor.rgb;\n\

const char* FR_RigidVideoTexture = "FR_RigidVideoTexture";
/////////////////// 002  FR_RIGID_VIDEO_TEXTURE/////////////////////
const char* FR_RigidVideoTexture_vs = "\
attribute highp vec4 VertexPos;\n\
attribute highp vec4 VertexNormal;\n\
attribute highp vec2 InTexCood;\n\
uniform highp mat4 ViewProjMatrix;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
void main(void)\n\
{\n\
	gl_Position = ViewProjMatrix * VertexPos;\n\
	Normal = VertexNormal.xyz;\n\
	TexCoord = InTexCood;\n\
}";
const char* FR_RigidVideoTexture_fs = "\
uniform highp sampler2D sampler2d;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
void main (void)\n\
{\n\
	gl_FragColor = texture2D(sampler2d, TexCoord);\n\
    gl_FragColor.rgb = gl_FragColor.bgr;\n\
}";

XRVertexLayout FR_RigidVideoTexture_layout_index = XR_VERTEX_LAYOUT_PNT;

UInt32 FR_RigidVideoTexture_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;





//UInt32 FR_RigidTexture_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;

const char* FR_SkinnedTexture = "FR_SkinnedTexture";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* FR_SkinnedTexture_vs = "\
attribute highp vec4 VertexPos;\n\
attribute highp vec4 VertexNormal;\n\
attribute highp vec2 InTexCood;\n\
attribute highp vec4 inBoneWeights;\n\
attribute highp vec4 inBoneIndex;\n\
uniform highp mat4 ViewProjMatrix;\n\
uniform highp vec4 param;\n\
uniform highp mat4 boneWorld[64];\n\
varying highp vec2  TexCoord;\n\
varying highp vec3  Normal;\n\
void main(void)\n\
{\n\
	highp vec4 position;\n\
	highp ivec4 boneIndex=ivec4(inBoneIndex);\n\
	highp vec4 boneWeight=inBoneWeights;\n\
	position = boneWorld[boneIndex.x] * VertexPos * boneWeight.x;\n\
	int maxBone = int(param.x);\n\
	for (int iBone = 1; iBone < maxBone; iBone++)\n\
    {\n\
        boneIndex = boneIndex.yzwx;\n\
        boneWeight = boneWeight.yzwx;\n\
        position += boneWorld[boneIndex.x] * VertexPos * boneWeight.x;\n\
    }\n\
	gl_Position = ViewProjMatrix * position;\n\
	TexCoord = InTexCood;\n\
	Normal = VertexNormal.xyz;\n\
}";

//gl_Position = vec4(1.0,1.0,1.0,1.0);
const char* FR_SkinnedTexture_fs = "\
uniform highp sampler2D sampler2d;\n\
varying highp vec2 TexCoord;\n\
varying highp vec3  Normal;\n\
void main (void)\n\
{\n\
	gl_FragColor = texture2D(sampler2d, TexCoord);\n\
}";

XRVertexLayout FR_SkinnedTexture_layout_index = XR_VERTEX_LAYOUT_PNTWI;
UInt32 FR_SkinnedTexture_render_state = XR_CULLMODE_NONE | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;

/////////////////// 007 Shader_Effect_Glass /////////////////////
const char* FR_Glass = "FR_Glass";
const char* FR_Glass_vs = "\
attribute highp vec4 inVertex;\
attribute highp vec3 inNormal;\
attribute highp vec2 inTexCoord;\
uniform highp mat4 MVPMatrix;\
uniform highp vec3 EyePosition;\
uniform highp float RIRSquare;\
varying mediump vec2 ReflectCoord;\
varying lowp float ReflectRatio;\
void main()\
{\
	gl_Position = MVPMatrix * inVertex;\
	highp vec3 eyeDir = normalize(EyePosition - inVertex.xyz);\
	highp float c = abs(dot(eyeDir, inNormal));\
	highp float g = sqrt(RIRSquare + c * c - 1.0);\
	highp float f1 = (g - c) / (g + c);\
	highp float f2 = (c * (g + c) - 1.0) / (c * (g - c) + 1.0);\
	ReflectRatio = 0.5 * f1 * f1 * (1.0 + f2 * f2);\
	ReflectCoord = normalize(reflect(eyeDir, inNormal)).xy * 0.5;\
}";

const char* FR_Glass_fs = "\
uniform sampler2D sReflectTex;\
varying mediump vec2 ReflectCoord;\
varying lowp float ReflectRatio;\
void main()\
{\
	gl_FragColor = vec4(vec3(texture2D(sReflectTex, ReflectCoord)), ReflectRatio);\
}";

XRVertexLayout FR_Glass_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 FR_Glass_render_state = XR_CULLMODE_NONE;

/////////////////// 008 Shader_Effect_Glossy /////////////////////
const char* FR_Glossy = "FR_Glossy";
const char* FR_Glossy_vs = "\
attribute highp vec3 myVertex;\
attribute highp vec3 myNormal;\
attribute highp vec2 myUV;\
uniform highp mat4 MVPMatrix;\
uniform highp mat4 MVMatrix;\
uniform highp mat3 MVITMatrix;\
uniform highp mat4 MMatrix;\
uniform highp vec3 EyePosition;\
varying mediump vec3 normal;\
varying mediump vec3 worldnormal;\
varying lowp float ReflectRatio;\
varying mediump vec2 ReflectCoord;\
varying mediump vec2 TexCoord;\
varying mediump vec3 LightDir;\
varying mediump vec3 viewDir;\
varying mediump vec3 CalReflectDir;\
lowp float RIRSquare = 2.5;\
void main()\
{\
	gl_Position = MVPMatrix * vec4(myVertex, 1.0);\
	gl_PointSize=10.0;\
	normal = normalize(MVITMatrix * myNormal);\
	highp vec4 ecPosition = MVMatrix * vec4(myVertex,1.0);\
	highp vec3 vPosition3 = ecPosition.xyz/ecPosition.z;\
	highp vec3 eyeDirection = -normalize(ecPosition.xyz);\
	LightDir = normalize(MVITMatrix*vec3(0,1000,0)-vPosition3);\
	highp float c = abs(dot(eyeDirection, normal));\
	highp float g = sqrt(RIRSquare + c * c - 1.0);\
	highp float f1 = (g - c) / (g + c);\
	highp float f2 = (c * (g + c) - 1.0) / (c * (g - c) + 1.0);\
	ReflectRatio = 0.5 * f1 * f1 * (1.0 + f2 * f2);\
	ReflectCoord = normalize(reflect(eyeDirection, normal)).xy * 0.5;\
	TexCoord = myUV;\
	worldnormal=normalize(myNormal);\
	highp vec4 real_vertex = MMatrix*vec4(myVertex,1.0);\
	highp vec4 real_normal = MMatrix*vec4(myNormal,0.0);\
	viewDir=normalize(-real_vertex.xyz+EyePosition);\
	CalReflectDir =reflect(-viewDir,real_normal.xyz);\
	normal = normalize(real_normal.xyz);\
	LightDir = normalize(vec3(0.0,800.0,-800.0)-real_vertex.xyz);\
}";

const char* FR_Glossy_fs = "\
uniform sampler2D sBaseTex;\
uniform samplerCube sReflectTex;\
varying mediump vec3 normal;\
varying mediump vec3 worldnormal;\
varying mediump vec2 ReflectCoord;\
varying mediump vec2 TexCoord;\
varying mediump vec3 LightDir;\
varying mediump vec3 viewDir;\
varying lowp float ReflectRatio;\
uniform lowp vec3 AmbientColor;\
uniform lowp vec3 DiffuseColor;\
uniform lowp vec3 SpecularColor;\
varying mediump vec3 CalReflectDir;\
lowp float cShininess = 12.0;\
void main()\
{\
	mediump vec3 nor = normal;\
	mediump float NdotL = max(dot(nor, LightDir), 0.0);\
	lowp  vec3 reflection =normalize(reflect(-LightDir,nor));\
	lowp vec3 reflecttex = vec3(0.5, 0.5, 0.5);\
	lowp vec3 DiffuseLight =0.8*texture2D(sBaseTex, TexCoord).rgb+ 0.3*NdotL+0.2*reflecttex;\
	lowp  vec3 texColor  = DiffuseLight;\
	lowp  vec3  color = texColor;\
	mediump float NdotH = max(dot(nor, reflection), 0.0);\
	mediump float specular = pow(NdotH, cShininess);\
	lowp vec3 SpecularLight = 0.1*specular * vec3(1.0,1.0,1.0);\
	lowp vec3 fcolor = color;\
	gl_FragColor = vec4(texColor+SpecularLight, 1.0);\
	gl_FragColor.a = texture2D(sBaseTex,TexCoord).a;\
}";
XRVertexLayout FR_Glossy_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 FR_Glossy_render_state = XR_CULLMODE_FRONT | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT| XR_BLEND_DEFAULT;
//lowp  vec3	color = mix(texColor, reflection, ReflectRatio);

/////////////////// 008 Shader_Effect_Glossy /////////////////////
const char* FR_GlossyColor = "FR_GlossyColor";
const char* FR_GlossyColor_vs = "\
attribute highp vec3 myVertex;\
attribute highp vec3 myNormal;\
attribute highp vec2 myUV;\
uniform highp mat4 MVPMatrix;\
uniform highp mat4 MVMatrix;\
uniform highp mat3 MVITMatrix;\
varying mediump vec3 normal;\
varying mediump vec3 halfVector;\
varying lowp float ReflectRatio;\
varying mediump vec2 ReflectCoord;\
varying mediump vec2 TexCoord;\
lowp float RIRSquare = 2.5;\
void main()\
{\
	gl_Position = MVPMatrix * vec4(myVertex, 1.0);\
	normal = normalize(MVITMatrix * myNormal);\
	highp vec3 ecPosition = vec3(MVMatrix * vec4(myVertex,1.0));\
	highp vec3 eyeDirection = -normalize(ecPosition);\
	halfVector = vec3(0.0, 1.0, 0.0) + eyeDirection;\
	highp float c = abs(dot(eyeDirection, normal));\
	highp float g = sqrt(RIRSquare + c * c - 1.0);\
	highp float f1 = (g - c) / (g + c);\
	highp float f2 = (c * (g + c) - 1.0) / (c * (g - c) + 1.0);\
	ReflectRatio = 0.5 * f1 * f1 * (1.0 + f2 * f2);\
	ReflectCoord = normalize(reflect(eyeDirection, normal)).xy * 0.5;\
	TexCoord = myUV;\
}";

const char* FR_GlossyColor_fs = "\
uniform sampler2D sBaseTex;\
uniform sampler2D  sReflectTex;\
uniform sampler2D sColorMaskTex;\
varying mediump vec3 normal;\
varying mediump vec3 halfVector;\
varying mediump vec2 ReflectCoord;\
varying mediump vec2 TexCoord;\
varying lowp float ReflectRatio;\
uniform lowp vec3 AmbientColor;\
uniform lowp vec3 DiffuseColor;\
uniform lowp vec3 SpecularColor;\
uniform lowp vec3 MaterialColor;\
uniform lowp float AlphaRate;\
lowp float cShininess = 36.0;\
void main()\
{\
	mediump vec3 nor = normalize(normal);\
	mediump float NdotL = max(dot(nor, vec3(0.0, 1.0, 0.0)), 0.0);\
	lowp vec3 DiffuseLight = vec3(0.8,0.8,0.8) + NdotL * DiffuseColor;\
	lowp float fmask = texture2D(sColorMaskTex,TexCoord).g;\
	lowp  vec3 texColor  = vec3(texture2D(sBaseTex, TexCoord)) *fmask +(1.0-fmask)*MaterialColor;\
	texColor  = texColor * DiffuseLight;\
	lowp  vec3 reflection = vec3(texture2D(sReflectTex, ReflectCoord));\
	lowp  vec3  color = mix(texColor, reflection, ReflectRatio);\
	mediump float NdotH = max(dot(nor, normalize(halfVector)), 0.0);\
	mediump float specular = pow(NdotH, cShininess);\
	lowp vec3 SpecularLight = specular * SpecularColor;\
	lowp vec3 fcolor = color + SpecularLight;\
	gl_FragColor = vec4(fcolor, texture2D(sBaseTex, TexCoord).a);\
}";
//	gl_FragColor.a = texture2D(sBaseTex, TexCoord).a;
XRVertexLayout FR_GlossyColor_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 FR_GlossyColor_render_state = XR_CULLMODE_FRONT | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT| XR_BLEND_DEFAULT ;
//lowp float fmask = texture2D(sColorMaskTex,TexCoord).g;\
//lowp  vec3 texColor  = vec3(texture2D(sBaseTex, TexCoord)) *fmask +(1.0-fmask)*MaterialColor;\
//lowp  vec3 texColor  = vec3(texture2D(sBaseTex, TexCoord)) * DiffuseLight;\
//lowp  vec3 reflection = vec3(texture2D(sReflectTex, ReflectCoord));\| XR_BLEND_DEFAULT
/////////////////// 009  Shader_Effect_Glossy_Alpha /////////////////////
const char* FR_GlossyAlpha = "FR_GlossyAlpha";
const char* FR_GlossyAlpha_vs = "\
attribute highp vec3 myVertex;\
attribute highp vec3 myNormal;\
attribute highp vec2 myUV;\
uniform highp mat4 MVPMatrix;\
uniform highp mat4 MVMatrix;\
uniform highp mat3 MVITMatrix;\
varying mediump vec3 normal;\
varying mediump vec3 halfVector;\
varying lowp float ReflectRatio;\
varying mediump vec2 ReflectCoord;\
varying mediump vec2 TexCoord;\
lowp float RIRSquare = 2.5;\
void main()\
{\
	gl_Position = MVPMatrix * vec4(myVertex, 1.0);\
	normal = normalize(MVITMatrix * myNormal);\
	highp vec3 ecPosition = vec3(MVMatrix * vec4(myVertex,1.0));\
	highp vec3 eyeDirection = -normalize(ecPosition);\
	halfVector = vec3(0.0, 1.0, 0.0) + eyeDirection;\
	highp float c = abs(dot(eyeDirection, normal));\
	highp float g = sqrt(RIRSquare + c * c - 1.0);\
	highp float f1 = (g - c) / (g + c);\
	highp float f2 = (c * (g + c) - 1.0) / (c * (g - c) + 1.0);\
	ReflectRatio = 0.5 * f1 * f1 * (1.0 + f2 * f2);\
	ReflectCoord = normalize(reflect(eyeDirection, normal)).xy * 0.5;\
	TexCoord = myUV;\
    gl_PointSize = 10.0;\
}";

const char* FR_GlossyAlpha_fs = "\
uniform sampler2D sBaseTex;\
uniform sampler2D sReflectTex;\
varying mediump vec3 normal;\
varying mediump vec3 halfVector;\
varying mediump vec2 ReflectCoord;\
varying mediump vec2 TexCoord;\
varying lowp float ReflectRatio;\
uniform lowp vec3 AmbientColor;\
uniform lowp vec3 DiffuseColor;\
uniform lowp vec3 SpecularColor;\
uniform lowp float AlphaRate;\
lowp float cShininess = 36.0;\
void main()\
{\
	mediump vec3 nor = normalize(normal);\
	mediump float NdotL = max(dot(nor, vec3(0.0, 1.0, 0.0)), 0.0);\
	lowp vec3 DiffuseLight = vec3(0.8,0.8,0.8) + NdotL * DiffuseColor;\
	lowp  vec3 texColor  = vec3(texture2D(sBaseTex, TexCoord)) * DiffuseLight;\
	lowp  vec3 reflection = vec3(texture2D(sReflectTex, ReflectCoord));\
	lowp  vec3  color = texColor;\
	mediump float NdotH = max(dot(nor, normalize(halfVector)), 0.0);\
	mediump float specular = pow(NdotH, cShininess);\
	lowp vec3 SpecularLight = specular * SpecularColor;\
	lowp vec3 fcolor = color + SpecularLight;\
	gl_FragColor = vec4(fcolor, AlphaRate);\
	if(AlphaRate > 0.95)\
	{\
		gl_FragColor.a = texture2D(sBaseTex,TexCoord).a;\
	}\	
}";
XRVertexLayout FR_GlossyAlpha_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 FR_GlossyAlpha_render_state = XR_CULLMODE_FRONT | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT| XR_BLEND_DEFAULT;

/////////////////// 010  Shader_Effect_Glass_Alpha /////////////////////
const char* FR_Glass_Alpha = "FR_Glass_Alpha";
const char* FR_Glass_Alpha_vs = "\
attribute highp vec4 inVertex;\
attribute highp vec3 inNormal;\
attribute highp vec2 inTexCoord;\
uniform highp mat4 MVPMatrix;\
uniform highp vec3 EyePosition;\
uniform highp float RIRSquare;\
varying mediump vec2 ReflectCoord;\
varying highp vec2 AlphaTexCoord;\
varying lowp float ReflectRatio;\
void main()\
{\
	gl_Position = MVPMatrix * inVertex;\
	highp vec3 eyeDir = normalize(EyePosition - inVertex.xyz);\
	highp float c = abs(dot(eyeDir, inNormal));\
	highp float g = sqrt(RIRSquare + c * c - 1.0);\
	highp float f1 = (g - c) / (g + c);\
	highp float f2 = (c * (g + c) - 1.0) / (c * (g - c) + 1.0);\
	ReflectRatio = 0.5 * f1 * f1 * (1.0 + f2 * f2);\
	ReflectCoord = normalize(reflect(eyeDir, inNormal)).xy * 0.5;\
	AlphaTexCoord=inTexCoord;\
}";

const char* FR_Glass_Alpha_fs = "\
uniform sampler2D sReflectTex;\
uniform sampler2D sAlphaTex;\
varying mediump vec2 ReflectCoord;\
varying lowp float ReflectRatio;\
varying highp vec2 AlphaTexCoord;\
void main()\
{\
	gl_FragColor = texture2D(sAlphaTex, AlphaTexCoord);\
	gl_FragColor.a =0.2;\
}";
//	gl_FragColor = vec4(vec3(texture2D(sReflectTex, ReflectCoord)), ReflectRatio);
//gl_FragColor.a = texture2D(sAlphaTex, AlphaTexCoord).r;
XRVertexLayout FR_Glass_Alpha_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 FR_Glass_Alpha_render_state = XR_CULLMODE_NONE| XR_BLEND_DEFAULT;

const char* FR_RigidBlend = "FR_RigidBlend";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* FR_RigidBlend_vs = "\
attribute highp vec4 VertexPos;\n\
attribute highp vec4 VertexNormal;\n\
attribute highp vec2 InTexCood;\n\
uniform highp mat4 ViewProjMatrix;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
void main(void)\n\
{\n\
	gl_Position = ViewProjMatrix * VertexPos;\n\
	Normal = VertexNormal.xyz;\n\
	TexCoord = InTexCood;\n\
}";

const char* FR_RigidBlend_fs = "\
uniform highp sampler2D samplerText;\n\
uniform highp sampler2D samplerAlpha;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
void main (void)\n\
{\n\
    gl_FragColor= texture2D(samplerText, TexCoord);\n\
}";
#if 0
const char* FR_RigidBlend_fs = "\
uniform highp sampler2D sampler2d;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
void main (void)\n\
{\n\
	gl_FragColor =vec4(1.0,0.0,0.0,0.3);\n\	
}";
	gl_FragColor.a =texture2D(sampler2d, TexCoord).r;\n\
gl_FragColor.a = texture2D(samplerAlpha, TexCoord).b;\n
	gl_FragColor.a = 0.3;\n
	| XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT

#endif
XRVertexLayout FR_RigidBlend_layout_index = XR_VERTEX_LAYOUT_PNT;


UInt32 FR_RigidBlend_render_state =  XR_CULLMODE_NONE| XR_BLEND_DEFAULT| XR_FRONTFACE_CCW ;
const char* FR_ColorPlot = "FR_ColorPlot";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* FR_ColorPlot_vs = "\
attribute highp vec4 VertexPos;\n\
attribute highp vec4 VertexNormal;\n\
attribute highp vec2 InTexCood;\n\
uniform highp mat4 ViewProjMatrix;\n\
uniform lowp vec3 WaveColor;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
varying lowp vec3 MaterialColor;\n\
void main(void)\n\
{\n\
	gl_Position = ViewProjMatrix * VertexPos;\n\
	Normal = VertexNormal.xyz;\n\
	TexCoord = InTexCood;\n\
	gl_PointSize = 3.0;\n\
    MaterialColor = WaveColor;\n\
}";

const char* FR_ColorPlot_fs = "\
uniform highp sampler2D samplerText;\n\
uniform highp sampler2D samplerAlpha;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
varying lowp vec3 MaterialColor;\n\
void main (void)\n\
{\n\
    gl_FragColor.rgb= MaterialColor;\n\
		gl_FragColor.a= 1.0;\n\
}";

XRVertexLayout FR_ColorPlot_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 FR_ColorPlot_render_state =  XR_CULLMODE_NONE| XR_BLEND_DEFAULT| XR_FRONTFACE_CCW ;
const char* FR_DynamicBlend = "FR_DynamicBlend";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* FR_DynamicBlend_vs = "\
attribute highp vec4 VertexPos;\n\
attribute highp vec4 VertexNormal;\n\
attribute highp vec2 InTexCood;\n\
uniform highp mat4 ViewProjMatrix;\n\
uniform highp float TextureStep;\n\
uniform lowp vec3 WaveColor;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
varying lowp vec3 MaterialColor;\n\
void main(void)\n\
{\n\
	gl_Position = ViewProjMatrix * VertexPos;\n\
	Normal = VertexNormal.xyz;\n\
	TexCoord.y = InTexCood.y-TextureStep*Normal.y;\n\
	TexCoord.x = InTexCood.x;\n\
	MaterialColor = WaveColor;\n\
}";

const char* FR_DynamicBlend_fs = "\
uniform highp sampler2D samplerText;\n\
uniform highp sampler2D samplerAlpha;\n\
varying highp vec3  Normal;\n\
varying highp vec2 TexCoord;\n\
varying lowp vec3 MaterialColor;\n\
void main (void)\n\
{\n\
    gl_FragColor.rgb = MaterialColor;\n\
    gl_FragColor.a=texture2D(samplerText, TexCoord).g*Normal.z;\n\
}";
XRVertexLayout FR_DynamicBlend_layout_index = XR_VERTEX_LAYOUT_PNT;


UInt32 FR_DynamicBlend_render_state =  XR_CULLMODE_NONE| XR_BLEND_DEFAULT| XR_FRONTFACE_CCW| XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT| XR_BLEND_DEFAULT ;

#endif
