#ifndef __UTILITY_DX11_H__
#define __UTILITY_DX11_H__

#include "../intrinsic.h"
#include "../../Platform/XrCrt.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>

//template <typename T, size_t N>
//char (*RtlpNumberOf( UNALIGNED T (&)[N] ))[N];
//
//#define XR_ARRAY_SIZE(A)   (sizeof(*RtlpNumberOf(A)))

inline UInt32 GetGLDepthStencilFunction(UInt32 func)
{
	UInt32 out;
	UInt32 state = func&XR_DEPTHTEST_OP;
	switch (state) {
	case XR_DEPTHTEST_NEVER:
		out = GL_NEVER;
		break;
	case XR_DEPTHTEST_LT:
		out = GL_LESS;
		break;
	case XR_DEPTHTEST_EQ:
		out = GL_EQUAL;
		break;
	case XR_DEPTHTEST_LE:
		out = GL_LEQUAL;
		break;
	case XR_DEPTHTEST_GT:
		out = GL_GREATER;
		break;
	case XR_DEPTHTEST_NE:
		out = GL_NOTEQUAL;
		break;
	case XR_DEPTHTEST_GE:
		out = GL_GEQUAL;
		break;
	case XR_DEPTHTEST_ALWAYS:
	default:
		out = GL_ALWAYS;
		break;
	}
	return out;
}

/*
inline UInt32 GetGLSamplerType(UInt32 type)
{
	UInt32 result;
	switch (type) {
		case XR_SAMPLER_WRAP:
			result = GL_REPEAT;
			break;
		case XR_SAMPLER_MIRROR:
			result = GL_MIRRORED_REPEAT;
			break;
		case XR_SAMPLER_CLAMP:
			result = GL_CLAMP_TO_EDGE;
			break;
		case XR_SAMPLER_BORDER:
			result = GL_CLAMP_TO_EDGE;
			break;
		default:
			result = GL_CLAMP_TO_EDGE;
	}
	return result;
}
*/

inline Void GetGLTextureFormat(UInt32 format, UInt32* glformat, UInt32* gltype)
{
	switch (format) {
		case XR_R16G16B16A16F:
			*glformat = GL_RGBA;
			*gltype = GL_HALF_FLOAT_OES;
			break;
		case XR_R16G16B16F:
			*glformat = GL_RGB;
			*gltype = GL_HALF_FLOAT_OES;
			break;
		case XR_R8G8B8A8_SRGB:
		case XR_R8G8B8A8:
			*glformat = GL_RGBA;
			*gltype = GL_UNSIGNED_BYTE;
			break;
		case XR_R8G8B8_SRGB:
		case XR_R8G8B8:
			*glformat = GL_RGB;
			*gltype = GL_UNSIGNED_BYTE;
			break;
		case XR_A8:
			*glformat = GL_ALPHA;
			*gltype = GL_UNSIGNED_BYTE;
			break;
		case XR_YUV:
			*glformat = GL_RGB;
			*gltype = GL_UNSIGNED_BYTE;
			break;			
	}
}


inline Void GetGLSamplerMode(UInt32 mode, UInt32* address, UInt32* filtermag, UInt32*filtermin)
{
	switch (mode & XR_ADDRESS_BIT) {
		case XR_SAMPLER_WRAP:
			*address = GL_REPEAT;
			break;
		case XR_SAMPLER_MIRROR:
			*address = GL_MIRRORED_REPEAT;
			break;
		case XR_SAMPLER_CLAMP:
			*address = GL_CLAMP_TO_EDGE;
			break;
		case XR_SAMPLER_BORDER:
		default:
			*address = GL_CLAMP_TO_EDGE;
			break;
	}
	switch (mode & XR_FILTER_BIT) {
		case XR_SAMPLER_NEAREST:
			*filtermag = GL_NEAREST;
			*filtermin = GL_NEAREST;
			break;
		case XR_SAMPLER_LINEAR:
		default:
			*filtermag = GL_LINEAR;
			*filtermin = GL_LINEAR;
			//*filtermin = GL_LINEAR_MIPMAP_LINEAR;
			break;
	}
}

inline UInt32 BF_XR2GLES(Int32 fmt)
{
	UInt32 format = 0;
	//switch (fmt) {
	//case XR_R32G32B32A32F:
	//	format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	//	break;
	//case XR_R32G32B32F:
	//	format = DXGI_FORMAT_R32G32B32_FLOAT;
	//	break;
	//case XR_R32G32F:
	//	format = DXGI_FORMAT_R32G32_FLOAT;
	//	break;
	//case XR_R32F:
	//	format = DXGI_FORMAT_R32_FLOAT;
	//	break;
	//case XR_R16G16B16A16F:
	//	format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	//	break;
	//case XR_R8G8B8A8U:
	//	format = DXGI_FORMAT_R8G8B8A8_UINT;
	//	break;
	//case XR_R8G8B8A8:
	//	format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//	break;
	//case XR_R8G8B8A8_SRGB:
	//	format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//	break;
	//case XR_R8G8:
	//	format = DXGI_FORMAT_R8G8_UNORM;
	//	break;
	//case XR_A8:
	//case XR_R8:
	//	format = DXGI_FORMAT_R8_UNORM;
	//	break;
	//case XR_D24S8:
	//	format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//	break;
	//}
	return format;
}

#endif  //__UTILITY_DX11_H__

