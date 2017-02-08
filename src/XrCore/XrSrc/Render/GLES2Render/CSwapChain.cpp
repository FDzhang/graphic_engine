#include "CSwapChain.h"

#ifndef USE_DX11

CSwapChain::CSwapChain():
	eglDisplay(0),
	eglSurface(0),
	eglContext(0)
{
}

bool CSwapChain::Init()
{
	return true;
}

Void CSwapChain::Swap()
{
#ifdef WIN_32
	eglSwapBuffers(eglDisplay, eglSurface);
#endif
}

#endif