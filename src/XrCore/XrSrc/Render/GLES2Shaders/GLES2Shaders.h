#ifndef __GLES2_SHADERS_H__
#define __GLES2_SHADERS_H__

#include "../../Common/XRVector.h"
#define MAX_BONE_NUM 58

#ifndef USE_DX11
#define ShaderSource2Param(ss) ss, ss##_vs, ss##_fs, sizeof(ss##_CB), ss##_layout_index, ss##_render_state
#define ShaderSource2ParamEx(ss) ss, ss##_vs, ss##_fs, sizeof(ss##_CB), sizeof(ss##_CB2), ss##_layout_index, ss##_render_state

#define DeclareShaderParam(ss)  extern const char* ss; extern const char* ss##_vs; extern const char* ss##_fs; extern XRVertexLayout ss##_layout_index; extern UInt32 ss##_render_state;

extern const char* VS_P_dummy_fx;
extern const char* VS_PT_dummy_fx;
extern const char* VS_PNT_dummy_fx;
extern const char* VS_PNTWI_dummy_fx;
extern const char* VS_PNBT_dummy_fx;
extern const char* VS_PNBTWI_dummy_fx;
extern const char* VS_PTACDEFGHJL_dummy_fx;

struct UI_Spirit_CB {
	XRMat4 TransformMatrix;
};

struct UI_Font_CB {
	XRMat4 TransformMatrix;
};

struct FR_SkyBox_CB {
	XRMat4 ViewMatrix;
	XRMat4 ProjMatrix;
};

struct FR_RigidBump_CB {
	XRMat4 ModelMatrix;
	XRMat4 ViewProjMatrix;
	XRMat4 BiasMatrix;
	XRVec4 eyePos;
	XRVec4 LightPosition;
	XRVec4 ambientTerm;
	XRVec4 diffuseTerm;
	XRVec4 SpecularTerm;
	Float32 ShininessTerm;
};

struct FR_SkinnedBump_CB {
	XRMat4 ModelMatrix;
	XRMat4 ViewProjMatrix;
	XRMat4 BiasMatrix;
	XRVec4 eyePos;
	XRVec4 LightPosition;
	XRVec4 param;
	XRMat4 boneWorld[MAX_BONE_NUM];
	XRVec4 ambientTerm;
	XRVec4 diffuseTerm;
	XRVec4 SpecularTerm;
	Float32 ShininessTerm;
};

struct FR_RigidTexture_CB {
	XRMat4 TransformMatrix;
};
struct FR_RigidColorTexture_CB {
	XRMat4 TransformMatrix;
	XRVec4 InTexColor;
};

struct FR_RigidVideoTexture_CB {
	XRMat4 TransformMatrix;
};

struct FR_RigidBlend_CB {
	XRMat4 TransformMatrix;
};
struct FR_ColorPlot_CB {
	XRMat4 TransformMatrix;
	XRVec3 WaveColor;	
};
struct FR_DynamicBlend_CB {
	XRMat4 TransformMatrix;
	Float32 TextureStep;
	XRVec3 WaveColor;
	
};

struct FR_SkinnedTexture_CB {
	XRMat4 TransformMatrix;
	XRVec4 param;
	XRMat4 boneWorld[MAX_BONE_NUM];
};
struct Pre_Shadow_CB {
	XRMat4 TransformMatrix;
};
struct Pre_Shadow_Skinned_CB {
	XRMat4 TransformMatrix;
	XRVec4 param;
	XRMat4 boneWorld[MAX_BONE_NUM];
};
//struct FR_SimpleSkeleton_CB2 {
//	XRMat4 boneWorld[80];
//};

DeclareShaderParam(VS_P_dummy)
DeclareShaderParam(VS_PT_dummy)
DeclareShaderParam(VS_PNT_dummy)
DeclareShaderParam(VS_PNTWI_dummy)
DeclareShaderParam(VS_PNBT_dummy)
DeclareShaderParam(VS_PNBTWI_dummy)

DeclareShaderParam(UI_Spirit)
DeclareShaderParam(UI_Font)

DeclareShaderParam(FR_MatObject)
DeclareShaderParam(FR_FlObject)
DeclareShaderParam(FR_FrObject)
DeclareShaderParam(FR_SkyBox)
DeclareShaderParam(FR_RigidTexture)
DeclareShaderParam(FR_RigidColorTexture)
DeclareShaderParam(FR_SkinnedTexture)
DeclareShaderParam(FR_RigidBump)
DeclareShaderParam(FR_SkinnedBump)
DeclareShaderParam(Pre_Shadow)
DeclareShaderParam(Pre_Shadow_Skinned)
DeclareShaderParam(FR_Glossy)
DeclareShaderParam(FR_GlossyColor)
DeclareShaderParam(FR_GlossyAlpha)
DeclareShaderParam(FR_Glass)
DeclareShaderParam(FR_Glass_Alpha)
DeclareShaderParam(FR_RigidBlend)
DeclareShaderParam(FR_ColorPlot)
DeclareShaderParam(FR_DynamicBlend)
DeclareShaderParam(FR_RigidVideoTexture)

struct FR_Glass_CB
{
	XRMat4 MVPMatrix;
	XRVec3 EyePosition;
	Float32 RIRSquare;
};
struct FR_Glass_Alpha_CB
{
	XRMat4 MVPMatrix;
	XRVec3 EyePosition;
	Float32 RIRSquare;
};

struct FR_Glossy_CB
{
	XRMat4 MVPMatrix;
	XRMat4 MVMatrix;
	XRMat3 MVITMatrix;
	XRVec3 AmbientColor;
	XRVec3 DiffuseColor;
	XRVec3 SpecularColor;
};
struct FR_GlossyColor_CB
{
	XRMat4 MVPMatrix;
	XRMat4 MVMatrix;
	XRMat3 MVITMatrix;
	XRVec3 AmbientColor;
	XRVec3 DiffuseColor;
	XRVec3 SpecularColor;
	XRVec3 MaterialColor;
	Float32 AlphaRate;
};

struct FR_GlossyAlpha_CB
{
	XRMat4 MVPMatrix;
	XRMat4 MVMatrix;
	XRMat3 MVITMatrix;
	XRVec3 AmbientColor;
	XRVec3 DiffuseColor;
	XRVec3 SpecularColor;
	Float32 AlphaRate;
};

struct FR_FrObject_CB
{
	XRMat4 viewProjMatrix;
	XRMat4 modelMatrix;
	XRVec4 eyePos;
	XRVec4 emission;
	XRVec4 color;
};

struct FR_FlObject_CB
{
	XRMat4 viewProjMatrix;
	XRMat4 modelMatrix;
	XRVec4 eyePos;
	XRVec4 emission;
	XRVec4 color;
};

struct PP_Blit_CB
{
};

struct PP_Down4X_CB
{
    XRVec2 twoTexelSize;
	XRVec2 halfPixelOffset;
};


struct PP_ExtractHL_CB
{
    float threshold;
    float scalar;
	XRVec2 padding;
};

struct PP_Tonemapping_CB
{
	float blurAmount;
    float effectAmount;
	float exposure;
	float gamma;
};

struct PP_GaussComp_CB
{
	XRVec4 coeff;
};

struct PP_StarStreak_CB
{
	XRVec2 stepSize;
	float stride;
	XRVec4 colorCoeff[4];
	float padding;
};

struct PP_StarComp_CB
{
};

struct PP_GlareComp_CB
{
	XRVec4 mixCoeff;
};

struct PP_GhostImage_CB
{
	XRVec4 scalar;
	XRVec4 colorCoeff[4];
};

DeclareShaderParam(PP_Blit)
DeclareShaderParam(PP_Down4X)
DeclareShaderParam(PP_ExtractHL)
DeclareShaderParam(PP_GaussComp)
DeclareShaderParam(PP_GhostImage)
DeclareShaderParam(PP_GlareComp)
DeclareShaderParam(PP_StarComp)
DeclareShaderParam(PP_StarStreak)
DeclareShaderParam(PP_Tonemapping)

#endif
#endif //__GLES2_SHADERS_H__