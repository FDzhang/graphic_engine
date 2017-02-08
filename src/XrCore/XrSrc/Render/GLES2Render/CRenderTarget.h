#ifndef __C_RENDERTEXTURE_H_
#define __C_RENDERTEXTURE_H_
#include "utilityGLES2.h"
#include "../intrinsic.h"
#include "CTexture.h"

class CRenderTarget {
public:
	enum DepthType {
		Depth24,
		Depth16,
		NoDepth
	};
	enum ColorType {
		RGB888,
		RGBA8888,
		HDR = 1000,
		RG16F,
		RGB16F,
		RGBA16F,
	};

	CRenderTarget();
	~CRenderTarget();
	bool Init(int width, int height, ColorType color, DepthType depth);
	bool InitFromSwapChain(int width, int height, class CSwapChain* pSwapChain);
	void GetPBOData(void* pData);
	void SetPBOData(void* pData);

	void ActivateFB();
	void DeactivateFB();
	int GetWidth() { return m_renderTexture.width; }
	int GetHeight() { return m_renderTexture.height; }
	void GetSize(int* w, int* h) { *w = m_renderTexture.width; *h = m_renderTexture.height; }
	CTexture* GetRenderTexture() { return &m_renderTexture; }
	CTexture* GetDepthStencilTexture() { return &m_depthStencilTexture; }
	void BindTexture() { }

	void Release() { }
	void GetTex(int id);

	void SaveCurrentFB();
	void RestoreSaveDFB();

	unsigned int fboid;

 private:
	friend class CRenderContext;
	friend class CRenderDevice;

	CTexture					m_renderTexture;
	CTexture					m_renderTextureStaging;
	CTexture					m_depthStencilTexture;
};

#endif  // __C_RENDERTEXTURE_H_
