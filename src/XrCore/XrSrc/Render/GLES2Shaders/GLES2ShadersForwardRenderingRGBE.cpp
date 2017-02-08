
#include "GLES2Shaders.h"

#include "../XrRender.h"
#ifndef USE_DX11
const char* FR_MatObject = "FR_MatObject";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* FR_MatObject_vs = "\
attribute vec3 PosAttribute;\n\
attribute vec3 myNormal;\n\
attribute vec2 uvTexCoord;\n\
precision highp float;\n\
uniform highp mat4 viewProjMatrix;\n\
uniform highp mat4 ModelMatrix;\n\
uniform highp vec3 eyePos;\n\
varying highp vec4 Position;\n\
varying highp vec3 Normal;\n\
varying highp vec3 IncidentVector;\n\
varying highp vec2 texcoord;\n\
void main()\n\
{\n\
   highp vec4 P = ModelMatrix * vec4(PosAttribute, 1.0);\n\
   highp vec3 N = normalize(mat3(ModelMatrix) * myNormal);\n\
   highp vec3 I = P.xyz - eyePos;\n\
   Position = P;\n\
   Normal = N;\n\
   IncidentVector = I;\n\
   texcoord = uvTexCoord;\n\
   gl_Position = viewProjMatrix * P;\n\
}";
const char* FR_MatObject_fs = "\
precision mediump float;\
varying mediump vec4 Position;\
varying mediump vec3 Normal;\
varying mediump vec3 IncidentVector;\
varying mediump vec2 texcoord;\
uniform mediump vec3 emission;\
uniform mediump vec4 color;\
uniform samplerCube envMap;\
uniform samplerCube envMapIrrad;\
uniform sampler2D diffuseMap;\
mediump float my_fresnel(mediump vec3 I, mediump vec3 N, mediump float power,  mediump float scale,  mediump float bias)\
{\
    return bias + (pow(clamp(1.0 - dot(I, N), 0.0, 1.0), power) * scale);\
}\
mediump vec4 EncodeRGBE8( mediump vec3 rgb )\
{\
	mediump vec4 ret ;\
	mediump float fLen = max(rgb.r, rgb.g) ;\
	fLen = max(fLen, rgb.b) ;\
	mediump float fExp = floor( log(fLen)/log(1.05) ) ;\
	ret.a = clamp( (fExp + 128.0) / 256.0, 0.0, 1.0 ) ;\
	ret.rgb = rgb / pow(1.05, ret.a * 256.0 - 128.0) ;\
	return ret;\
}\
mediump vec3 texture2DRGBE8( sampler2D sampler, mediump vec2 texCoord)\
{\
    mediump vec4 rgbe = texture2D(sampler, texCoord);\
	mediump float fExp = rgbe.a * 256.0 - 128.0 ;\
	mediump float fScaler = pow(1.05, fExp);\
	return (rgbe.rgb * fScaler) ;\
}\
void main()\
{\
    mediump vec3 I = normalize(IncidentVector);\
    mediump vec3 N = normalize(Normal);\
    mediump vec3 R = reflect(I, N);\
    mediump float fresnel = my_fresnel(-I, N, 5.0, 1.0, 0.1);\
    mediump vec3 Creflect = textureCube(envMap, R).rgb;\
	mediump vec3 irrad = textureCube(envMapIrrad, N).rgb;\
	mediump vec3 diffuse = texture2D(diffuseMap, texcoord).rgb * color.a + color.rgb;\
	gl_FragColor = EncodeRGBE8(mix(diffuse*irrad, Creflect, fresnel*color.a)+emission);\
}";

XRVertexLayout FR_MatObject_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 FR_MatObject_render_state = XR_CULLMODE_BACK | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;

const char* FR_FlObject = "FR_FlObject";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* FR_FlObject_vs = "\
attribute vec3 PosAttribute;\n\
attribute vec3 myNormal;\n\
precision highp float;\n\
uniform highp mat4 viewProjMatrix;   \
uniform highp mat4 ModelMatrix;    \
uniform highp vec3 eyePos;\n\
varying highp vec4 Position;\n\
varying highp vec3 Normal;\n\
varying highp vec3 IncidentVector;\n\
void main()\n\
{\n\
   highp vec4 P = ModelMatrix * vec4(PosAttribute, 1.0);\n\
   highp vec3 N = normalize(mat3(ModelMatrix) * myNormal);\n\
   highp vec3 I = P.xyz - eyePos;\n\
   Position = P;\n\
   Normal = N;\n\
   IncidentVector = I;\n\
   gl_Position = viewProjMatrix * P;\n\
}";
const char* FR_FlObject_fs = "\
precision mediump float;\
varying mediump vec4 Position;\
varying mediump vec3 Normal;\
varying mediump vec3 IncidentVector;\
uniform mediump vec3 emission;\
uniform mediump vec4 color;\
uniform samplerCube envMap;\
uniform samplerCube envMapRough;\
mediump float my_fresnel(mediump vec3 I, mediump vec3 N, mediump float power,  mediump float scale,  mediump float bias)\
{\
    return bias + (pow(clamp(1.0 - dot(I, N), 0.0, 1.0), power) * scale);\
}\
mediump vec4 EncodeRGBE8( mediump vec3 rgb )\
{\
	mediump vec4 ret ;\
	mediump float fLen = max(rgb.r, rgb.g) ;\
	fLen = max(fLen, rgb.b) ;\
	mediump float fExp = floor( log(fLen)/log(1.05) ) ;\
	ret.a = clamp( (fExp + 128.0) / 256.0, 0.0, 1.0 ) ;\
	ret.rgb = rgb / pow(1.05, ret.a * 256.0 - 128.0) ;\
	return ret;\
}\
mediump vec3 texture2DRGBE8( sampler2D sampler, mediump vec2 texCoord)\
{\
    mediump vec4 rgbe = texture2D(sampler, texCoord);\
	mediump float fExp = rgbe.a * 256.0 - 128.0 ;\
	mediump float fScaler = pow(1.05, fExp);\
	return (rgbe.rgb * fScaler) ;\
}\
void main()\
{\
    mediump vec3 I = normalize(IncidentVector);\
    mediump vec3 N = normalize(Normal);\
    mediump vec3 R = reflect(I, N);\
    mediump float fresnel = my_fresnel(-I, N, 5.0, 1.0, 0.1);\
    mediump vec3 Creflect = textureCube(envMap, R).rgb;\
	mediump vec3 CreflectRough = textureCube(envMapRough, R).rgb;\
    CreflectRough *= color.rgb;\
	Creflect *= color.rgb;\
	gl_FragColor = EncodeRGBE8(mix(mix(CreflectRough,Creflect,fresnel),mix(Creflect,CreflectRough,fresnel),color.a)+emission);\
}";

XRVertexLayout FR_FlObject_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 FR_FlObject_render_state = XR_CULLMODE_BACK | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;

const char* FR_FrObject = "FR_FrObject";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* FR_FrObject_vs = "\
attribute vec3 PosAttribute;\n\
attribute vec3 myNormal;\n\
precision highp float;\n\
uniform highp mat4 viewProjMatrix;\n\
uniform highp mat4 ModelMatrix;\n\
uniform highp vec4 eyePos;\n\
varying highp vec4 Position;\n\
varying highp vec3 Normal;\n\
varying highp vec3 IncidentVector;\n\
void main()\n\
{\n\
   highp vec4 P = ModelMatrix * vec4(PosAttribute, 1.0);\n\
   highp vec3 N = normalize(mat3(ModelMatrix) * myNormal);\n\
   highp vec3 I = P.xyz - eyePos.xyz;\n\
   Position = P;\n\
   Normal = N;\n\
   IncidentVector = I;\n\
   gl_Position = viewProjMatrix * P;\n\
}";
const char* FR_FrObject_fs = "\
precision mediump float;\
varying mediump vec4 Position;\
varying mediump vec3 Normal;\
varying mediump vec3 IncidentVector;\
uniform mediump vec3 emission;\
uniform mediump vec4 color;\
uniform samplerCube envMap;\
mediump float eta=0.7;\
mediump float deta=-0.006;\
mediump float my_fresnel(mediump vec3 I, mediump vec3 N, mediump float power,  mediump float scale,  mediump float bias)\
{\
    return bias + (pow(clamp(1.0 - dot(I, N), 0.0, 1.0), power) * scale);\
}\
mediump vec4 EncodeRGBE8( mediump vec3 rgb )\
{\
	mediump vec4 ret ;\
	mediump float fLen = max(rgb.r, rgb.g) ;\
	fLen = max(fLen, rgb.b) ;\
	mediump float fExp = floor( log(fLen)/log(1.05) ) ;\
	ret.a = clamp( (fExp + 128.0) / 256.0, 0.0, 1.0 ) ;\
	ret.rgb = rgb / pow(1.05, ret.a * 256.0 - 128.0) ;\
	return ret;\
}\
mediump vec3 texture2DRGBE8( sampler2D sampler, mediump vec2 texCoord)\
{\
    mediump vec4 rgbe = texture2D(sampler, texCoord);\
	mediump float fExp = rgbe.a * 256.0 - 128.0 ;\
	mediump float fScaler = pow(1.05, fExp);\
	return (rgbe.rgb * fScaler) ;\
}\
void main()\
{\
    mediump vec3 I = normalize(IncidentVector);\
    mediump vec3 N = normalize(Normal);\
    mediump vec3 R = reflect(I, N);\
    mediump vec3 T1 = refract(I, N, eta);\
	mediump vec3 T2 = refract(I, N, eta+deta);\
	mediump vec3 T3 = refract(I, N, eta+2.0*deta);\
    mediump float fresnel = my_fresnel(-I, N, 5.0, 1.0, 0.1);\
    mediump vec3 Creflect = textureCube(envMap, R).rgb;\
	mediump vec3 Crefract;\
    Crefract.r = textureCube(envMap, T1).r;\
	Crefract.g = textureCube(envMap, T2).g;\
	Crefract.b = textureCube(envMap, T3).b;\
    Crefract *= color.rgb;\
	gl_FragColor = EncodeRGBE8(mix(Crefract, Creflect, fresnel)+emission);\
}";

XRVertexLayout FR_FrObject_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 FR_FrObject_render_state = XR_CULLMODE_BACK | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;


const char* FR_SkyBox = "FR_SkyBox";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* FR_SkyBox_vs = "\
attribute vec3 PosAttribute;\n\
attribute vec3 NormalAttribute;\n\
attribute vec2 UvAttribute;\n\
precision highp float;\n\
uniform highp mat4 viewMatrix;\n\
uniform highp mat4 ProjMatrix;\n\
varying highp vec3 TexCoord;\n\
void main()\n\
{\n\
    TexCoord  = mat3(viewMatrix) * vec3(PosAttribute.xyz);\n\
	gl_Position = ProjMatrix * vec4(PosAttribute, 1.0);\n\
}";
const char* FR_SkyBox_fs = "\
precision highp float;\n\
varying highp vec3 TexCoord;\n\
uniform samplerCube envMap;\n\
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
highp vec3 textureCubeRGBE8( samplerCube sampler, highp vec3 texCoord)\n\
{\n\
    highp vec4 rgbe = textureCube(sampler, texCoord);\n\
	highp float fExp = rgbe.a * 256.0 - 128.0 ;\n\
	highp float fScaler = pow(1.05, fExp);\n\
	return (rgbe.rgb * fScaler) ;\n\
}\n\
void main()\n\
{\n\
	gl_FragColor = EncodeRGBE8(textureCubeRGBE8(envMap, TexCoord));\n\
}";

XRVertexLayout FR_SkyBox_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 FR_SkyBox_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;


const char* FR_RigidBump = "FR_RigidBump";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* FR_RigidBump_vs = "\
attribute highp vec4 VertexPos;\n\
attribute highp vec3 VertexNormal;\n\
attribute highp vec4 VertexTangent;\n\
attribute highp vec2 InTexCood;\n\
uniform highp mat4 ModelMatrix;\n\
uniform highp mat4 ViewProjMatrix;\n\
uniform highp mat4 BiasMatrix;\n\
uniform highp vec4 eyePos;\n\
uniform highp vec4 LightPosition;\n\
varying highp vec3 lightVec;\n\
varying highp vec3 eyeVec;\n\
varying highp vec2 TexCoord;\n\
varying highp vec4 ProjCoord;\n\
varying highp mat3 tbnMatrix;\n\
void main(void)\n\
{\n\
    highp vec3 n = normalize(mat3(ModelMatrix) * VertexNormal);\n\
    highp vec3 t = normalize(mat3(ModelMatrix) * VertexTangent.xyz);\n\
    highp vec3 b = cross(n, t)*VertexTangent.w;\n\
	tbnMatrix = mat3(t.x, t.y, t.z, b.x, b.y, b.z, n.x, n.y, n.z);\n\
	highp vec4 vertexPosition = ModelMatrix * VertexPos;\n\
	lightVec = LightPosition.xyz - vertexPosition.xyz;\n\
	eyeVec = vertexPosition.xyz - eyePos.xyz;\n\
	ProjCoord = BiasMatrix * vertexPosition;\n\
	gl_Position = ViewProjMatrix * vertexPosition;\n\
	TexCoord = InTexCood;\n\
}";
const char* FR_RigidBump_fs = "\
uniform highp sampler2D samplerDiffuse;\n\
uniform highp sampler2D samplerNormal;\n\
uniform highp sampler2D samplerSpecular;\n\
uniform highp sampler2D samplerAlpha;\n\
uniform highp sampler2D samplerShadow;\n\
uniform highp samplerCube env;\n\
uniform highp samplerCube irrad;\n\
uniform highp vec4 ambientTerm;\n\
uniform highp vec4 diffuseTerm;\n\
uniform highp vec4 SpecularTerm;\n\
uniform highp float ShininessTerm;\n\
varying highp vec3 lightVec;\n\
varying highp vec3 eyeVec;\n\
varying highp vec2 TexCoord;\n\
varying highp vec4 ProjCoord;\n\
varying highp mat3 tbnMatrix;\n\
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
highp vec3 textureCubeRGBE8(samplerCube sampler, highp vec3 texCoord)\n\
{\n\
    highp vec4 rgbe = textureCube(sampler, texCoord);\n\
	highp float fExp = rgbe.a * 256.0 - 128.0 ;\n\
	highp float fScaler = pow(1.05, fExp);\n\
	return (rgbe.rgb * fScaler) ;\n\
}\n\
void main (void)\n\
{\n\
  highp vec3 diffuse = texture2D(samplerDiffuse, TexCoord).rgb;\n\
	highp float gloss = texture2D(samplerSpecular, TexCoord).r;\n\
	highp vec3 normal = normalize(tbnMatrix * (2.0 * texture2D(samplerNormal, TexCoord).rgb - 1.0));\n\
	highp float alpha = texture2D(samplerAlpha, TexCoord).r;\n\
	if (alpha<0.1) discard;\n\
	highp float comp = (ProjCoord.z / ProjCoord.w) - 0.003;\n\
	highp float depth = texture2DProj(samplerShadow, ProjCoord).r;\n\
	highp float val = comp <= depth ? 1.0 : 0.0;\n\
	val = 1.0;\
	highp vec3 L = normalize(lightVec);\n\
	highp vec3 V = normalize(eyeVec);\n\
	highp vec3 R = normalize(reflect(L, normal));\n\
	highp float nDotL = max(0.0, dot(normal, L));\n\
	highp float rDotV = max(0.0, dot(R, V));\n\
	diffuse = diffuse * diffuse;\n\
	gl_FragColor = EncodeRGBE8((ambientTerm.rgb + val*diffuseTerm.rgb * nDotL + val*SpecularTerm.rgb * gloss * pow(rDotV, ShininessTerm)) * diffuse);\n\
}";
/*
void main (void)\n\
{\n\
    highp vec3 diffuse = texture2D(samplerDiffuse, TexCoord).rgb;\n\
	highp float gloss = texture2D(samplerSpecular, TexCoord).r;\n\
	highp vec3 normal = normalize(tbnMatrix * (2.0 * texture2D(samplerNormal, TexCoord).rgb - 1.0));\n\
	highp vec3 normal1 = normalize(tbnMatrix * vec3(0.0,1.0,0.0));\n\
	highp vec3 irradiance = textureCubeRGBE8(irrad, normal1);\n\
	highp float alpha = texture2D(samplerAlpha, TexCoord).r;\n\
	if (alpha<0.1) discard;\n\
	highp float comp = (ProjCoord.z / ProjCoord.w) - 0.003;\n\
	highp float depth = texture2DProj(samplerShadow, ProjCoord).r;\n\
	highp float val = comp <= depth ? 1.0 : 0.0;\n\
	highp vec3 L = normalize(lightVec);\n\
	highp vec3 V = normalize(eyeVec);\n\
	highp vec3 R = normalize(reflect(L, normal));\n\
	highp float fresnel = my_fresnel(-V, normal, 5.0, 1.0, 0.1);\n\
	highp vec3 envReflect = textureCubeRGBE8(env, R);\n\
	highp float nDotL = max(0.0, dot(normal, L));\n\
	highp float rDotV = max(0.0, dot(R, V));\n\
	gl_FragColor = EncodeRGBE8((irradiance + val * diffuseTerm * nDotL + val * SpecularTerm * gloss * pow(rDotV, ShininessTerm)) * diffuse + envReflect*fresnel*gloss);\n\
}";
*/
//	gl_FragColor = (0.2 + nDotL + gloss  * pow(rDotV, cShininess)) * diffuse;	if (alpha<0.2) discard; 	gl_FragColor = vec4(val, val,val,val);
XRVertexLayout FR_RigidBump_layout_index = XR_VERTEX_LAYOUT_PNBT;
UInt32 FR_RigidBump_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;

//UInt32 FR_RigidTexture_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;

const char* FR_SkinnedBump = "FR_SkinnedBump";
/////////////////// 001 Shader_GhostImage /////////////////////
const char* FR_SkinnedBump_vs = "\
attribute highp vec4 VertexPos;\n\
attribute highp vec3 VertexNormal;\n\
attribute highp vec4 VertexTangent;\n\
attribute highp vec2 InTexCood;\n\
attribute highp vec4 inBoneWeights;\n\
attribute highp vec4 inBoneIndex;\n\
uniform highp mat4 ModelMatrix;\n\
uniform highp mat4 ViewProjMatrix;\n\
uniform highp mat4 BiasMatrix;\n\
uniform highp vec4 eyePos;\n\
uniform highp vec4 LightPosition;\n\
uniform highp vec4 param;\n\
uniform highp mat4 boneWorld[58];\n\
varying highp vec3 lightVec;\n\
varying highp vec3 eyeVec;\n\
varying highp vec2 TexCoord;\n\
varying highp vec4 ProjCoord;\n\
varying highp mat3 tbnMatrix;\n\
void main(void)\n\
{\n\
	highp vec4 position;\n\
	highp vec3 n;\n\
	highp vec3 t;\n\
	highp ivec4 boneIndex=ivec4(inBoneIndex);\n\
	highp vec4 boneWeight=inBoneWeights;\n\
	position = boneWorld[boneIndex.x] * VertexPos * boneWeight.x;\n\
	n = mat3(boneWorld[boneIndex.x]) * VertexNormal * boneWeight.x;\n\
	t = mat3(boneWorld[boneIndex.x]) * VertexTangent.xyz * boneWeight.x;\n\
	int maxBone = int(param.x);\n\
	for (int iBone = 1; iBone < maxBone; iBone++)\n\
    {\n\
        boneIndex = boneIndex.yzwx;\n\
        boneWeight = boneWeight.yzwx;\n\
        position += boneWorld[boneIndex.x] * VertexPos * boneWeight.x;\n\
		n += mat3(boneWorld[boneIndex.x]) * VertexNormal * boneWeight.x;\n\
		t += mat3(boneWorld[boneIndex.x]) * VertexTangent.xyz * boneWeight.x;\n\
    }\n\
	n = normalize(mat3(ModelMatrix) * n);\n\
	t = normalize(mat3(ModelMatrix) * t);\n\
    highp vec3 b = cross(n, t)*VertexTangent.w;\n\
	tbnMatrix = mat3(t.x, t.y, t.z, b.x, b.y, b.z, n.x, n.y, n.z);\n\
	highp vec4 vertexPosition = ModelMatrix * position;\n\
	lightVec = LightPosition.xyz - vertexPosition.xyz;\n\
	eyeVec = vertexPosition.xyz - eyePos.xyz;\n\
	ProjCoord = BiasMatrix * vertexPosition;\n\
	gl_Position = ViewProjMatrix * vertexPosition;\n\
	TexCoord = InTexCood;\n\
}";

//gl_Position = vec4(1.0,1.0,1.0,1.0);
const char* FR_SkinnedBump_fs = "\
uniform highp sampler2D samplerDiffuse;\n\
uniform highp sampler2D samplerNormal;\n\
uniform highp sampler2D samplerSpecular;\n\
uniform highp sampler2D samplerShadow;\n\
uniform highp samplerCube env;\n\
uniform highp samplerCube irrad;\n\
uniform highp vec4 ambientTerm;\n\
uniform highp vec4 diffuseTerm;\n\
uniform highp vec4 SpecularTerm;\n\
uniform highp float ShininessTerm;\n\
varying highp vec3 lightVec;\n\
varying highp vec3 eyeVec;\n\
varying highp vec2 TexCoord;\n\
varying highp vec4 ProjCoord;\n\
varying highp mat3 tbnMatrix;\n\
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
highp vec3 textureCubeRGBE8(samplerCube sampler, highp vec3 texCoord)\n\
{\n\
    highp vec4 rgbe = textureCube(sampler, texCoord);\n\
	highp float fExp = rgbe.a * 256.0 - 128.0 ;\n\
	highp float fScaler = pow(1.05, fExp);\n\
	return (rgbe.rgb * fScaler) ;\n\
}\n\
highp float my_fresnel(highp vec3 I, highp vec3 N, highp float power,  highp float scale,  highp float bias)\n\
{\n\
    return bias + (pow(clamp(1.0 - dot(I, N), 0.0, 1.0), power) * scale);\n\
}\n\
void main (void)\n\
{\n\
    highp vec3 diffuse = texture2D(samplerDiffuse, TexCoord).rgb;\n\
	highp float gloss = texture2D(samplerSpecular, TexCoord).r;\n\
	highp vec3 normal = normalize(tbnMatrix * (2.0 * texture2D(samplerNormal, TexCoord).rgb - 1.0));\n\
	highp vec3 normal1 = normalize(tbnMatrix * vec3(0.0,1.0,0.0));\n\
	highp vec3 irradiance = textureCubeRGBE8(irrad, normal1);\n\
	highp float comp = (ProjCoord.z / ProjCoord.w) - 0.003;\n\
	highp float depth = texture2DProj(samplerShadow, ProjCoord).r;\n\
	highp float val = comp <= depth ? 1.0 : 0.0;\n\
	val = 1.0;\
	highp vec3 L = normalize(lightVec);\n\
	highp vec3 V = normalize(eyeVec);\n\
	highp vec3 R = normalize(reflect(L, normal));\n\
	highp float fresnel = my_fresnel(-V, normal, 5.0, 1.0, 0.1);\n\
	highp vec3 envReflect = textureCubeRGBE8(env, R);\n\
	highp float nDotL = max(0.0, dot(normal, L));\n\
	highp float rDotV = max(0.0, dot(R, V));\n\
	diffuse = diffuse * diffuse;\n\
	gl_FragColor = EncodeRGBE8((irradiance*ambientTerm.a+ val * diffuseTerm.rgb * nDotL + val * SpecularTerm.rgb * gloss * pow(rDotV, ShininessTerm)) * diffuse + envReflect*fresnel*gloss*SpecularTerm.a);\n\
}";

XRVertexLayout FR_SkinnedBump_layout_index = XR_VERTEX_LAYOUT_PNBTWI;
UInt32 FR_SkinnedBump_render_state = XR_CULLMODE_NONE | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;

#endif

