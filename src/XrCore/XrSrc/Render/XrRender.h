#ifndef __XR_RENDER_H__
#define __XR_RENDER_H__

//#define USE_DX11

#ifdef USE_DX11
#include "./DX11Render/DX11Render.h"
#include "./DX11Shaders/DX11Shaders.h"
#else
#include "./GLES2Render/GLES2Render.h"
#include "./GLES2Shaders/GLES2Shaders.h"

#define XR_TEXTURE_TYPE_HDR XR_TEXTURE_TYPE_RGBE
#endif // USE_DX11



#endif