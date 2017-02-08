
#include "GLES2Shaders.h"

#include "../XrRender.h"

#ifndef USE_DX11

const char* Pre_Shadow = "Pre_Shadow";
/////////////////// 001 Shader_UI_Spirit /////////////////////
const char* Pre_Shadow_vs = "\
attribute highp vec4 VertexPos;\n\
attribute highp vec4 VertexNormal;\n\
attribute highp vec4 VertexTangent;\n\
attribute highp vec2 InTexCood;\n\
uniform highp mat4 ViewProjMatrix;\n\
varying highp vec2 TexCoord;\n\
varying highp vec3 Normal;\n\
void main(void)\n\
{\n\
	gl_Position = ViewProjMatrix * VertexPos;\n\
	TexCoord = InTexCood;\n\
	Normal = VertexNormal.xyz+VertexTangent.xyz;\n\
}";

const char* Pre_Shadow_fs = "\
	varying highp vec2 TexCoord;\n\
	varying highp vec3 Normal;\n\
	void main (void)\n\
	{\n\
		gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n\
	}";

XRVertexLayout Pre_Shadow_layout_index = XR_VERTEX_LAYOUT_PNBT;
UInt32 Pre_Shadow_render_state = XR_CULLMODE_BACK | XR_FRONTFACE_CW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;

const char* Pre_Shadow_Skinned = "Pre_Shadow_Skinned";
/////////////////// 001 Shader_UI_Spirit /////////////////////
const char* Pre_Shadow_Skinned_vs = "\
attribute highp vec4 VertexPos;\n\
attribute highp vec4 VertexNormal;\n\
attribute highp vec4 VertexTangent;\n\
attribute highp vec2 InTexCood;\n\
attribute highp vec4 inBoneWeights;\n\
attribute highp vec4 inBoneIndex;\n\
uniform highp mat4 ViewProjMatrix;\n\
uniform highp vec4 param;\n\
uniform highp mat4 boneWorld[58];\n\
varying highp vec2 TexCoord;\n\
varying highp vec3 Normal;\n\
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
	Normal = VertexNormal.xyz+VertexTangent.xyz;\n\
}";

const char* Pre_Shadow_Skinned_fs = "\
	varying highp vec2 TexCoord;\n\
	varying highp vec3 Normal;\n\
	void main (void)\n\
	{\n\
		gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n\
	}";

XRVertexLayout Pre_Shadow_Skinned_layout_index = XR_VERTEX_LAYOUT_PNBTWI;
UInt32 Pre_Shadow_Skinned_render_state = XR_CULLMODE_BACK | XR_FRONTFACE_CW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT;

#endif
//UInt32 UI_Font_render_state = XR_CULLMODE_BACK | XR_FRONTFACE_CW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT | XR_BLEND_DEFAULT;