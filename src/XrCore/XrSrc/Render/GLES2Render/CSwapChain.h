#ifndef __C_SWAP_CHAIN_H__
#define __C_SWAP_CHAIN_H__

#include "utilityGLES2.h"
#include "CRenderContext.h"
#include "CRenderDevice.h"

class CSwapChain
{
public:
	CSwapChain();
	Boolean Init();
	Void Swap();

	friend bool XrCreateDeviceContextAndSwapChain(int width, int height, int context, class CRenderContext** ppCContext, class CRenderDevice** ppCDevice, class CSwapChain** ppCSwapChain, int type);

	EGLDisplay			eglDisplay;
	EGLSurface			eglSurface;
	EGLContext			eglContext;

	Int32	fbid;
	UInt32	m_width;
	UInt32	m_height;
	//IDXGISwapChain*         m_pDX11SwapChain;
}; 

#endif  //__C_SWAP_CHAIN_H__
