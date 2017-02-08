//----------------------------------------------------------------------------------
// File:        hdr_app.h
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
//----------------------------------------------------------------------------------

#ifndef _POST_PROCESSING_H_
#define _POST_PROCESSING_H_

#include "../Render/XrRenderEffect.h"
#include "../XrCore/CDeviceManager.h"
class CHDRPostProcessing
{
public:

	enum HDR_PROGRAM { //Program ID enum
		DOWNSAMPLE=0,
		DOWNSAMPLE4X,
		TONEMAPPING,
		EXTRACTHL,
		GAUSCOMP,
		STARSTREAK,
		GLARECOMP,
		STARCOMP,
		GHOSTIMAGE,
		PROGSIZE,
	};

	enum BLUR_PROGRAM {
		BLURH4=0,
		BLURV4,
		BLURH6,
		BLURV6,
		BLURH10,
		BLURV10,
		BLURH12,
		BLURV12,
	};

	enum BUFFER_PYRAMID {
		LEVEL_0 = 0,   //half size
		LEVEL_1,        //quater size
		LEVEL_2,     
		LEVEL_3,
		LEVEL_4,
		LEVEL_5,
		LEVEL_TOTAL,
	};

	CHDRPostProcessing()
	{
	    m_useSTAR = 1;
	    m_useGHOST = 1;
		m_bInitialized = 0;
		m_gamma = 1.0 / 2.0;			//for srgb
		m_effectAmount = 1.0;
		m_expMask = 0.0;
		m_blendAmount = 0.8;			//post processing blending factor
		m_lumThreshold = 1.2;
		m_lumScaler = 0.11;
		lum = 1.2;
		m_starGenLevel = LEVEL_0;		//set at LEVEL_0 for higher quality but lower performance
	}

	virtual ~CHDRPostProcessing(void);

	bool init(int width, int height);
	void SetInternalSize(int width, int height);
	bool render(CRenderTarget*	pFrame_buffer);
	bool initShaders();

	bool cleanup(void);
	bool restart();
	inline bool isInitialized() { return m_bInitialized; }
	void initBlurCode();
	void InitRenderTexture(int width, int height);

	void ReleaseCXrRenderTarget();
	CRenderTargetEx* GetSceneBuffer() { return &scene_buffer; }

protected:
	void toneMappingPass(CRenderTarget*	pFrame_buffer);
	void downsample(CRenderTarget *src, CRenderTarget *dest);
	void downsample4x(CRenderTarget *src, CRenderTarget *dest);
	void extractHL(CRenderTarget *src, CRenderTarget *dest);
	void run_pass(HDR_PROGRAM prog, CRenderTarget *src, CRenderTarget *dest);
	void ComposeEffect();
	void genStarStreak(int dir);
	void genGhostImage();
	void GetSceneExposure();
	void blitOffScreenBuffer();
	void blur(CRenderTarget *src, CRenderTarget *dest, CRenderTarget *temp, int blurWidth);
	void GetBufferPyramidSize(BUFFER_PYRAMID level, int* w, int* h);

	CXrRenderEffect m_effect[PROGSIZE+1];
	CShaderObject m_blur[8];

	CSampler m_sampler;
	CTexture m_lensMask;
	CRenderState m_quadRS;
	CRenderState m_objectRS;
	CRenderState m_skyRS;

	CRenderTargetEx	scene_buffer;
	CRenderTarget	compose_buffer[LEVEL_TOTAL];
	CRenderTarget	blur_bufferA[LEVEL_TOTAL];
	CRenderTarget	blur_bufferB[LEVEL_TOTAL];
	CRenderTarget	streak_bufferA[4];
	CRenderTarget	streak_bufferB[4];
	CRenderTarget	streak_bufferFinal;
	CRenderTarget	ghost1st_buffer;
	CRenderTarget	ghost2nd_buffer;
	CRenderTarget	glare_buffer;
	CRenderTarget  	exp_buffer[3];		//exposure info buffer

	CVertexBuffer m_quadVB;
	CIndexBuffer m_quadIB;
	BUFFER_PYRAMID	m_starGenLevel;

	bool m_useSTAR;
	bool m_useGHOST;
	bool m_bInitialized;
	int m_internalWidth;
	int m_internalHeight;
	int m_externalWidth;
	int m_externalHeight;
	float m_aspectRatio;
	float m_blendAmount;
	float m_gamma;
	float m_effectAmount;
	float m_expMask;					//for scene fade in/out
	float m_lumThreshold;
	float m_lumScaler;
	float lum;
};

#endif /* _POST_PROCESSING_H_ */
