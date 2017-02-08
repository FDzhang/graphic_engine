#ifndef __DX11RENDER_H__
#define __DX11RENDER_H__

#include "CSwapChain.h"
#include "utilityGLES2.h"

bool XrCreateDeviceContextAndSwapChain(int width, int height, int context, class CRenderContext** ppCContext, class CRenderDevice** ppCDevice, class CSwapChain** ppCSwapChain, int type=0);

#endif  //__C_DX11RENDER_H__
