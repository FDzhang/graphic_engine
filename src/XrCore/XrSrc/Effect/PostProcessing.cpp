//----------------------------------------------------------------------------------
// File:        hdr_app.cpp
// SDK Version: v10.10 
// Email:       jackh@nvidia.com
// Site:        http://developer.nvidia.com/
//
// Copyright (c) 2007-2012, NVIDIA CORPORATION.  All rights reserved.
//
// TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
// *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
// OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA OR ITS SUPPLIERS
// BE  LIABLE  FOR  ANY  SPECIAL,  INCIDENTAL,  INDIRECT,  OR  CONSEQUENTIAL DAMAGES
// WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS OF BUSINESS PROFITS,
// BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
// ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
//
//----------------------------------------------------------------------------------


#include "stdio.h"
#include "stdlib.h"

#include "blur_shader_generator.h"
#include "PostProcessing.h"
#include "../XrCore/CDeviceManager.h"
#include "../3rd/hdr_images.h"
#include "../3rd/XrFileLoader.h"

#include "../Platform/XrPath.h"
const char* maskTex_Core ={XR_RES"mask.bmp"};
//void __cdecl xrprintfd(const char *format, ...)
//{
//char    buf[4096], *p = buf;
//va_list args;
//int     n;
//        va_start(args, format);
//        n = _vsnprintf(p, sizeof buf - 3, format, args); // buf-3 is room for CR/LF/NUL
//        va_end(args);
//
//        p += (n < 0) ? sizeof buf - 3 : n;
//
//        while ( p > buf  &&  isspace(p[-1]) )
//                *--p = '\0';
//
//        *p++ = '\r';
//        *p++ = '\n';
//        *p   = '\0';
//
//        OutputDebugStringA(buf);
//}

#ifdef USE_DX11
static float QuadVertices[] = { -1.0f, -1.0f, 0.5f,  0.0, 1.0,
						  1.0f, -1.0f, 0.5f, 1.0, 1.0,
		                  1.0f, 1.0f, 0.5f, 1.0, 0.0,
						 -1.0f, 1.0f, 0.5f, 0.0, 0.0,};
#else
static float QuadVertices[] = { -1.0f, -1.0f, 0.5f,  0.0, 0.0,
						  1.0f, -1.0f, 0.5f, 1.0, 0.0,
		                  1.0f, 1.0f, 0.5f, 1.0, 1.0,
						 -1.0f, 1.0f, 0.5f, 0.0, 1.0,};
#endif
static unsigned short QuadIndices[] =
{
		0,1,2,
		2,3,0,};

float lastExpLog=0.0f;
int exp_w = 8, exp_h = 8;

float color_modulation1st[16];
float color_modulation2nd[16];
float color_modulation3rd[16];
float color_modulationGhost1st[16];
float color_modulationGhost2nd[16];

void ColorModulation(float* color, float r, float g, float b, int num)
{
	color[4*num] = color[4*num]*r;
	color[4*num+1] = color[4*num]*g;
	color[4*num+2] = color[4*num]*b;
	//color[4*num+3] = color[4*num]*a;
}

void modulateColor()
{
	//color modulation coefficients for star streak & ghost image
	for (int i=0;i<16; i++) {
	   color_modulation1st[i]=0.25;
	   color_modulation2nd[i]=0.25;
	   color_modulation3rd[i]=0.25;
	   color_modulationGhost1st[i] = 1.0;
	   color_modulationGhost2nd[i] = 1.0;
	}
    ColorModulation(color_modulation1st, 1.0, 0.75, 0.8,0);
	ColorModulation(color_modulation1st, 0.7, 1.0, 0.8,1);
	ColorModulation(color_modulation1st, 0.8, 0.8, 1.0,2);
	ColorModulation(color_modulation1st, 0.8, 1.0, 0.8,3);

	ColorModulation(color_modulation2nd, 1.0, 0.9, 0.8,0);
    ColorModulation(color_modulation2nd, 1.0, 0.9, 0.8,1);
	ColorModulation(color_modulation2nd, 0.8, 1.0, 0.9,2);
	ColorModulation(color_modulation2nd, 0.9, 0.8, 1.0,3);

	ColorModulation(color_modulation3rd, 1.0, 0.8, 0.8,1);
	ColorModulation(color_modulation3rd, 0.8, 1.0, 0.8,2);
	ColorModulation(color_modulation3rd, 0.6, 0.6, 1.0,3);

	ColorModulation(color_modulationGhost1st, 1.0, 0.9, 0.8,0);
    ColorModulation(color_modulationGhost1st, 1.0, 0.6, 0.5,1);
	ColorModulation(color_modulationGhost1st, 0.5, 1.0, 0.6,2);
	ColorModulation(color_modulationGhost1st, 1.0, 0.7, 0.3,3);

	ColorModulation(color_modulationGhost2nd, 0.2, 0.3, 0.7,0);
    ColorModulation(color_modulationGhost2nd, 0.5, 0.3, 0.2,1);
	ColorModulation(color_modulationGhost2nd, 0.1, 0.5, 0.2,2);
	ColorModulation(color_modulationGhost2nd, 0.13, 0.10, 1.0,3);
}

int GetRandFromRange(int h, int l)
{
	if (h<=l) return l;
	else {
		return l+rand()%(h-l+1);
	}
}

CHDRPostProcessing::~CHDRPostProcessing(void)
{
	cleanup();
}

//bool CHDRPostProcessing::cleanupGL()
//{
//	//glDeleteTextures(4, hdr_tex);
//	//glDeleteTextures(4, hdr_tex_rough);
//	//glDeleteTextures(4, hdr_tex_irrad);
//	//glDeleteTextures(1, &m_lensMask);
//	//glDeleteTextures(2, m_matTex);
//	for (int i=0; i<4; i++) {
//		if (image[i]) delete image[i];
//		if (image_rough[i]) delete image_rough[i];
//		if (image_irrad[i]) delete image_irrad[i];
//		image[i] = 0;
//		image_rough[i] = 0;
//		image_irrad[i] = 0;
//	}
//
//	return true;
//}

bool CHDRPostProcessing::cleanup()
{
	if(m_bInitialized)
	{
		//ui.DeInit();
		m_bInitialized = false;
		//return cleanupGL();
	}

	return true;
}


void CHDRPostProcessing::GetBufferPyramidSize(BUFFER_PYRAMID level, int* w, int* h)
{
    int width = m_internalWidth/2;
    int height = m_internalHeight/2;
	int lvl = level;
	while (lvl>LEVEL_0) {
		width /= 2;
		height /= 2;
		lvl--;
	}
	*w = width;
	*h = height;
}

void CHDRPostProcessing::InitRenderTexture(int width, int height)
{
	m_externalWidth = width;
	m_externalHeight = height;
	//renderBuffer for the whole scene

	XRDM->device()->CreateRenderTarget(m_internalWidth, m_internalHeight, XR_R16G16B16A16F, XR_D24S8, &scene_buffer.m_rt);

	//renderBuffer for final glare composition
	XRDM->device()->CreateRenderTarget(m_internalWidth/2, m_internalHeight/2, XR_R16G16B16A16F, XR_NONE, &glare_buffer);

    int w = m_internalWidth/4;
    int h = m_internalHeight/4;

	//buffer pyramid for wide range gaussian blur
    for (int i=0; i<LEVEL_TOTAL; i++) {
		XRDM->device()->CreateRenderTarget(w, h, XR_R16G16B16A16F, XR_NONE, &compose_buffer[i]);
		XRDM->device()->CreateRenderTarget(w, h, XR_R16G16B16A16F, XR_NONE, &blur_bufferA[i]);
		XRDM->device()->CreateRenderTarget(w, h, XR_R16G16B16A16F, XR_NONE, &blur_bufferB[i]);

		w /= 2;
        h /= 2;
    }

	//get resolution for star streak rendering
	GetBufferPyramidSize(LEVEL_1, &w, &h);

	//4 directions
	for(int i=0; i<4; i++) { 
		XRDM->device()->CreateRenderTarget(w, h, XR_R16G16B16A16F, XR_NONE, &streak_bufferA[i]);
		XRDM->device()->CreateRenderTarget(w, h, XR_R16G16B16A16F, XR_NONE, &streak_bufferB[i]);
	}

	//star streak composition renderbuffer
	XRDM->device()->CreateRenderTarget(w, h, XR_R16G16B16A16F, XR_NONE, &streak_bufferFinal);

	//renderbuffer for ghost image
	XRDM->device()->CreateRenderTarget(m_internalWidth/2, m_internalHeight/2, XR_R16G16B16A16F, XR_NONE, &ghost1st_buffer);
	XRDM->device()->CreateRenderTarget(m_internalWidth/2, m_internalHeight/2, XR_R16G16B16A16F, XR_NONE, &ghost2nd_buffer);

	//2 buffers for downsampling to get exposure info
	XRDM->device()->CreateRenderTarget(m_internalWidth/16, m_internalHeight/16, XR_R16G16B16A16F, XR_NONE, &exp_buffer[0]);
	XRDM->device()->CreateRenderTarget(m_internalWidth/16/4, m_internalHeight/16/4, XR_R16G16B16A16F, XR_NONE, &exp_buffer[1]);
	exp_w = m_internalWidth/16/16; exp_h = m_internalHeight/16/16;
	XRDM->device()->CreateAccessibleRenderTarget(exp_w, exp_h, XR_R16G16B16A16F, XR_NONE, &exp_buffer[2]);
	
}

void CHDRPostProcessing::SetInternalSize(int width, int height)
{
	m_internalWidth = width;
	m_internalHeight = height;
	m_aspectRatio= float(width)/float(height);
}

bool CHDRPostProcessing::init(int width, int height)
{
	int i;
	if (m_bInitialized) return true;

	//XRDM->device()->Init();

	SetInternalSize(width, height);

	InitRenderTexture(width, height);

	initShaders();

	XRCreateTextureFromFile(maskTex_Core, XR_TEXTURE_TYPE_DIFFUSE, &m_lensMask);
	XRDM->device()->CreateSampler(XR_SAMPLER_CLAMP, &m_sampler);
	//XRDM->device()->CreateRenderState(XR_CULLMODE_NONE | XR_FRONTFACE_CCW |  XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT, &m_quadRS);
	XRDM->device()->CreateRenderState(XR_CULLMODE_NONE | XR_FRONTFACE_CCW | XR_DEPTHTEST_LT, &m_quadRS);
	XRDM->device()->CreateVertexBuffer(QuadVertices, sizeof( float ) * 5, 4, &m_quadVB);
	XRDM->device()->CreateIndexBuffer(QuadIndices, sizeof( unsigned short ) * 6, &m_quadIB);
	//XRDM->context()->SetPrimitiveType(XRPT_TRIANGLE_LIST);
	
	modulateColor();

	m_bInitialized = 1;
	//orginalFB.RestoreSaveDFB();

	return true;
}

bool CHDRPostProcessing::initShaders()
{
	m_effect[DOWNSAMPLE].InitShaderFromMemory(ShaderSource2Param(PP_Blit));
	m_effect[DOWNSAMPLE4X].InitShaderFromMemory(ShaderSource2Param(PP_Down4X));
	m_effect[EXTRACTHL].InitShaderFromMemory(ShaderSource2Param(PP_ExtractHL));
	m_effect[TONEMAPPING].InitShaderFromMemory(ShaderSource2Param(PP_Tonemapping));
	m_effect[GAUSCOMP].InitShaderFromMemory(ShaderSource2Param(PP_GaussComp));
	m_effect[STARSTREAK].InitShaderFromMemory(ShaderSource2Param(PP_StarStreak));
	m_effect[GLARECOMP].InitShaderFromMemory(ShaderSource2Param(PP_GlareComp));
	m_effect[STARCOMP].InitShaderFromMemory(ShaderSource2Param(PP_StarComp));
	m_effect[GHOSTIMAGE].InitShaderFromMemory(ShaderSource2Param(PP_GhostImage));

	initBlurCode();

	return true;
}

void CHDRPostProcessing::initBlurCode()
{
//	int size, i, Program,s[4]={2,3,5,6};
	int size, i, Program;
	float s[4]={0.55,0.30,0.20,0.17};
	float *weights;
    int width, w, h, id;

	//start from quarter size
	w = m_internalWidth/4;
	h = m_internalHeight/4;

	//gen blur code at each level
	for (i=0; i<4; i++) {
		id = BLURH4+i*2;
		weights = generateGaussianWeights(s[i], width);

		generate1DConvolutionFP_filter(weights, width, false, true, w, h, &m_blur[id]);
		generate1DConvolutionFP_filter(weights, width, true, true, w, h, &m_blur[id+1]);

		delete [] weights;
		w /=2;
		h /=2;
	}
}

// downsample image 2x in each dimension
void CHDRPostProcessing::downsample(CRenderTarget *src, CRenderTarget *dest)
{
    XRDM->context()->SetRenderTarget(dest);


	CShaderObject* pShader;
	CUniformBlock* pUB;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	m_effect[DOWNSAMPLE].GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	XRDM->context()->SetShaders(pShader);
	XRDM->context()->PSSetTexture(0, src->GetRenderTexture(), &m_sampler);	
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);
	XRDM->context()->SetIndexBuffer(&m_quadIB);

	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);
}

// downsample image 4x in each dimension
void CHDRPostProcessing::downsample4x(CRenderTarget *src, CRenderTarget *dest)
{
    XRDM->context()->SetRenderTarget(dest);

	PP_Down4X_CB cb;
	CShaderObject* pShader;
	CUniformBlock* pUB;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	m_effect[DOWNSAMPLE4X].GetEffectParam(&pShader, &pUB, &pRS, &pLayout);
	XRDM->context()->SetShaders(pShader);

	cb.twoTexelSize.Set(float(1.0)/src->GetWidth(), float(1.0)/src->GetHeight());
	cb.halfPixelOffset.Set(float(0)/src->GetWidth(), float(0)/src->GetHeight());
	XRDM->context()->PSSetTexture(0, src->GetRenderTexture(), &m_sampler);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);
	XRDM->context()->SetIndexBuffer(&m_quadIB);
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);
}

// extract high light from scene
void CHDRPostProcessing::extractHL(CRenderTarget *src, CRenderTarget *dest)
{
    XRDM->context()->SetRenderTarget(dest);

	PP_ExtractHL_CB cb;
	CShaderObject* pShader;
	CUniformBlock* pUB;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	m_effect[EXTRACTHL].GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	XRDM->context()->SetShaders(pShader);

	XRDM->context()->PSSetTexture(0, src->GetRenderTexture(), &m_sampler);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);
	XRDM->context()->SetIndexBuffer(&m_quadIB);

	cb.scalar = m_lumScaler;
	cb.threshold = m_lumThreshold;
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->PSSetUniformBlock(0, pUB);

	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);
}

void CHDRPostProcessing::run_pass(HDR_PROGRAM prog, CRenderTarget *src, CRenderTarget *dest)
{
    XRDM->context()->SetRenderTarget(dest);

	XRDM->context()->SetShaders(&m_blur[prog]);

	XRDM->context()->PSSetTexture(0, src->GetRenderTexture(), &m_sampler);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, XRDM->GetVertexLayout(XR_VERTEX_LAYOUT_PT));

	XRDM->context()->SetIndexBuffer(&m_quadIB);

	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);
}

void CHDRPostProcessing::blur(CRenderTarget *src, CRenderTarget *dest, CRenderTarget *temp, int blurWidth)
{
    run_pass((HDR_PROGRAM)(blurWidth), src, temp);
    run_pass((HDR_PROGRAM)(blurWidth+1), temp, dest);
}

// read from float texture, apply tone mapping, render to regular RGB888 display
void CHDRPostProcessing::toneMappingPass(CRenderTarget*	pFrame_buffer)
{
	XRDM->context()->SetRenderTarget(pFrame_buffer);

	PP_Tonemapping_CB cb;
	CShaderObject* pShader;
	CUniformBlock* pUB;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	m_effect[TONEMAPPING].GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	XRDM->context()->SetShaders(pShader);

	XRDM->context()->PSSetTexture(0, scene_buffer.GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(1, glare_buffer.GetRenderTexture(), &m_sampler);

	float transitionSpeed = 0.02;
	float adjustSensitivity = 0.8;
	float expLog = log(1.0/(lum+0.001));
	float base = 0.1;
	float newExpLog = lastExpLog + (expLog - lastExpLog)* transitionSpeed;
	lastExpLog = newExpLog;

	float newExp = exp(base+(newExpLog-base)*adjustSensitivity);// * m_expMask;
	newExp = 1.0;
	cb.blurAmount = m_blendAmount;
	cb.effectAmount = m_effectAmount;
	cb.exposure = newExp;
	cb.gamma = m_gamma;
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);

	XRDM->context()->SetIndexBuffer(&m_quadIB);
	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);

}

void CHDRPostProcessing::ComposeEffect()
{
	////////compose gaussian blur buffers///////////////
	XRDM->context()->SetRenderTarget(&compose_buffer[LEVEL_0]);

	PP_GaussComp_CB cb0;
	CShaderObject* pShader;
	CUniformBlock* pUB;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	m_effect[GAUSCOMP].GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	XRDM->context()->SetShaders(pShader);
	XRDM->context()->PSSetTexture(0, blur_bufferA[LEVEL_0].GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(1, blur_bufferA[LEVEL_1].GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(2, blur_bufferA[LEVEL_2].GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(3, blur_bufferA[LEVEL_3].GetRenderTexture(), &m_sampler);

	cb0.coeff.Set(0.5, 0.3, 0.23, 0.18);

	XRDM->context()->UpdateUniformBlock(pUB, &cb0);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);

	XRDM->context()->SetIndexBuffer(&m_quadIB);
	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);
	
	////////compose star streak from 4 directions///////////////
	XRDM->context()->SetRenderTarget(&streak_bufferFinal);

	//PP_StarComp_CB cb1;
	m_effect[STARCOMP].GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	XRDM->context()->SetShaders(pShader);
	XRDM->context()->PSSetTexture(0, streak_bufferA[0].GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(1, streak_bufferA[1].GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(2, streak_bufferA[2].GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(3, streak_bufferA[3].GetRenderTexture(), &m_sampler);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);

	XRDM->context()->SetIndexBuffer(&m_quadIB);
	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);

	////////////////final glare composition/////////////
	XRDM->context()->SetRenderTarget(&glare_buffer);

	PP_GlareComp_CB cb1;
	m_effect[GLARECOMP].GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	XRDM->context()->SetShaders(pShader);
	XRDM->context()->PSSetTexture(0, compose_buffer[LEVEL_0].GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(1, streak_bufferFinal.GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(2, ghost2nd_buffer.GetRenderTexture(), &m_sampler);

	cb1.mixCoeff.Set(1.2, 1.2, 0.1, 0.0);
	XRDM->context()->UpdateUniformBlock(pUB, &cb1);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);
	XRDM->context()->SetIndexBuffer(&m_quadIB);
	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);
}


void CHDRPostProcessing::genStarStreak(int dir)
{
	int n,s,w,h;
	float step[2];
	float stride = 1.0;
	GetBufferPyramidSize(LEVEL_2, &w, &h);
	switch (dir) {
	case 0:
		step[1] = float(0.6)/w*m_aspectRatio;
        step[0] = float(0.6)/w;
		break;
	case 1:
		step[1] = float(0.6)/w*m_aspectRatio;
		step[0] = -float(0.6)/w;
		break;
	case 2:
		step[1] = -float(0.6)/w*m_aspectRatio;
		step[0] = float(0.6)/w;
		break;
	case 3:
		step[1] = -float(0.6)/w*m_aspectRatio;
		step[0] = -float(0.6)/w;
		break;
	default:
		break;
	}
	
	#define DEC 0.87
	float colorCoeff[16];

	//3 passes to generate 64 pixel blur in each direction
	//1st pass
	n=1;
	for (s=0; s<4; s+=1) {
		colorCoeff[s*4] = color_modulation1st[s*4] * pow(float(DEC), pow(float(4),n-1)*s);
		colorCoeff[s*4+1] = color_modulation1st[s*4+1] * pow(float(DEC), pow(float(4),n-1)*s);
		colorCoeff[s*4+2] = color_modulation1st[s*4+2] * pow(float(DEC), pow(float(4),n-1)*s);
		colorCoeff[s*4+3] = color_modulation1st[s*4+3] * pow(float(DEC), pow(float(4),n-1)*s);
	}
	

	XRDM->context()->SetRenderTarget(&streak_bufferA[dir]);

	PP_StarStreak_CB cb;
	CShaderObject* pShader;
	CUniformBlock* pUB;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	m_effect[STARSTREAK].GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	XRDM->context()->SetShaders(pShader);
	XRDM->context()->PSSetTexture(0, compose_buffer[LEVEL_0].GetRenderTexture(), &m_sampler);

	cb.stepSize = step;
	cb.stride = stride;
	cb.colorCoeff[0].Set(&colorCoeff[0]);
	cb.colorCoeff[1].Set(&colorCoeff[4]);
	cb.colorCoeff[2].Set(&colorCoeff[8]);
	cb.colorCoeff[3].Set(&colorCoeff[12]);
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);
	XRDM->context()->SetIndexBuffer(&m_quadIB);
	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);

	// 2nd pass
	n=2;
	for (s=0; s<4; s+=1) {
		colorCoeff[s*4] = color_modulation2nd[s*4] * pow(float(DEC), pow(float(4),n-1)*s);
		colorCoeff[s*4+1] = color_modulation2nd[s*4+1] * pow(float(DEC), pow(float(4),n-1)*s);
		colorCoeff[s*4+2] = color_modulation2nd[s*4+2] * pow(float(DEC), pow(float(4),n-1)*s);
		colorCoeff[s*4+3] = color_modulation2nd[s*4+3] * pow(float(DEC), pow(float(4),n-1)*s);
	}
	stride = 4;
	XRDM->context()->SetRenderTarget(&streak_bufferB[dir]);
	XRDM->context()->PSSetTexture(0, streak_bufferA[dir].GetRenderTexture(), &m_sampler);
	cb.stepSize = step;
	cb.stride = stride;
	cb.colorCoeff[0].Set(&colorCoeff[0]);
	cb.colorCoeff[1].Set(&colorCoeff[4]);
	cb.colorCoeff[2].Set(&colorCoeff[8]);
	cb.colorCoeff[3].Set(&colorCoeff[12]);
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);
	XRDM->context()->SetIndexBuffer(&m_quadIB);
	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);

	// 3rd pass
	n=3;
	for (s=0; s<4; s+=1) {
		colorCoeff[s*4] =  color_modulation3rd[s*4] * pow(float(DEC), pow(float(4),n-1)*s);
		colorCoeff[s*4+1] = color_modulation3rd[s*4+1] * pow(float(DEC), pow(float(4),n-1)*s);
		colorCoeff[s*4+2] = color_modulation3rd[s*4+2] * pow(float(DEC), pow(float(4),n-1)*s);
		colorCoeff[s*4+3] = color_modulation3rd[s*4+3] * pow(float(DEC), pow(float(4),n-1)*s);
	}
	stride = 16;
	XRDM->context()->SetRenderTarget(&streak_bufferA[dir]);
	XRDM->context()->PSSetTexture(0, streak_bufferB[dir].GetRenderTexture(), &m_sampler);
	cb.stepSize = step;
	cb.stride = stride;
	cb.colorCoeff[0].Set(&colorCoeff[0]);
	cb.colorCoeff[1].Set(&colorCoeff[4]);
	cb.colorCoeff[2].Set(&colorCoeff[8]);
	cb.colorCoeff[3].Set(&colorCoeff[12]);
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);
	XRDM->context()->SetIndexBuffer(&m_quadIB);
	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);
}

void CHDRPostProcessing::genGhostImage()
{
	XRDM->context()->SetRenderTarget(&ghost1st_buffer);

	PP_GhostImage_CB cb;
	CShaderObject* pShader;
	CUniformBlock* pUB;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	m_effect[GHOSTIMAGE].GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	XRDM->context()->SetShaders(pShader);
	XRDM->context()->PSSetTexture(0, blur_bufferA[LEVEL_0].GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(1, blur_bufferA[LEVEL_1].GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(2, blur_bufferA[LEVEL_1].GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(3, &m_lensMask, &m_sampler);

	//glUniform4fv(m_shader[GHOSTIMAGE].auiLocation[0], 1, scalar);
	//glUniform4fv(m_shader[GHOSTIMAGE].auiLocation[1], 4, color_modulationGhost1st);


	cb.scalar.Set(-4.0, 3.0, -2.0, 0.5);
	cb.colorCoeff[0].Set(&color_modulationGhost1st[0]);
	cb.colorCoeff[1].Set(&color_modulationGhost1st[4]);
	cb.colorCoeff[2].Set(&color_modulationGhost1st[8]);
	cb.colorCoeff[3].Set(&color_modulationGhost1st[12]);
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);

	XRDM->context()->SetIndexBuffer(&m_quadIB);
	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);


	XRDM->context()->SetRenderTarget(&ghost2nd_buffer);
	XRDM->context()->SetShaders(pShader);
	XRDM->context()->PSSetTexture(0, ghost1st_buffer.GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(1, ghost1st_buffer.GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(2, blur_bufferA[LEVEL_1].GetRenderTexture(), &m_sampler);
	XRDM->context()->PSSetTexture(3, &m_lensMask, &m_sampler);


	cb.scalar.Set(6.6, 2.5, 0.9, -0.55);
	cb.colorCoeff[0].Set(&color_modulationGhost2nd[0]);
	cb.colorCoeff[1].Set(&color_modulationGhost2nd[4]);
	cb.colorCoeff[2].Set(&color_modulationGhost2nd[8]);
	cb.colorCoeff[3].Set(&color_modulationGhost2nd[12]);
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	XRDM->context()->SetVertexBuffer(0, &m_quadVB, pLayout);
	XRDM->context()->SetIndexBuffer(&m_quadIB);
	XRDM->context()->DrawIndexedPrimitive(6, 0, 0);

}

bool CHDRPostProcessing::render(CRenderTarget* pFrame_buffer)
{
	int i;

	XRDM->context()->SetRenderState(&m_quadRS);

	//2.Downsize scene buffer to quarter size.
	downsample4x(&scene_buffer.m_rt, &blur_bufferA[LEVEL_0]);
	//lum=2.0;
	//goto skip;
	downsample4x(&blur_bufferA[LEVEL_0], &exp_buffer[0]);
	downsample4x(&exp_buffer[0], &exp_buffer[1]);
	downsample4x(&exp_buffer[1], &exp_buffer[2]);
	

	//3.Extract high light area for further processing.
	extractHL(&blur_bufferA[LEVEL_0], &compose_buffer[LEVEL_0]);

	//4.Gaussian blur on pyramid buffers.
	blur(&compose_buffer[LEVEL_0], &blur_bufferA[LEVEL_0], &blur_bufferB[LEVEL_0], BLURH4);

	for (i=LEVEL_1;i<LEVEL_TOTAL;i++) {
		downsample(&compose_buffer[i-1], &compose_buffer[i]);
		blur(&compose_buffer[i], &blur_bufferA[i], &blur_bufferB[i], (BLURH4+i*2) > BLURH12 ? BLURH12 : (BLURH4+i*2));
	}

	////////5.Generate streaks in 4 directions.
	genStarStreak(0);
	genStarStreak(1);
	genStarStreak(2);
	genStarStreak(3);

	////////6.Generate ghost image in 2 passes.
	genGhostImage();

	//////7.Final glare composition.
	ComposeEffect();

	//downsample(streak_bufferA[3] ,glare_buffer);
	//downsample(&compose_buffer[LEVEL_0] ,&glare_buffer);

	GetSceneExposure();
skip:
	//8.tonemapping to RGB888
	toneMappingPass(pFrame_buffer);

	return true;
}

//char exps[1024];
void CHDRPostProcessing::GetSceneExposure()
{
	
	return;
	int size;
	static int count, pitch;
	hfloat* exps;
	if (count==0) {
		static float LUMINANCE_VECTOR[3]  = {0.2125f, 0.7154f, 0.0721f};
		lum = 0.0f;
		pitch = 0;
		XRDM->context()->LockRenderedData(&exp_buffer[2], (void**)&exps, &pitch);
		float max,min;
		//LOGW("%f, %f, %f, %f", exps[0], exps[1],exps[2],exps[3]);
		for (int y=0;y<exp_h;y++) {
			for (int x=0;x<exp_w;x++) {
			lum+= convertHFloatToFloat(exps[x*4])*LUMINANCE_VECTOR[0];
			lum+= convertHFloatToFloat(exps[x*4+1])*LUMINANCE_VECTOR[1];
			lum+= convertHFloatToFloat(exps[x*4+2])*LUMINANCE_VECTOR[2];
			}
			((UInt8*&)exps)+=pitch;
		}
		XRDM->context()->UnlockRenderedData(&exp_buffer[2]);
		lum = lum/2;
		if (lum<=0.0) lum=0.0;
		//lum = 0.1;
		//xrprintf("avg exp=%f", lum);
	}
	count++;
	if (count>10) count=0;
}
