#ifndef __C_TEXTURE_H_
#define __C_TEXTURE_H_

#include "../intrinsic.h"
#include "utilityGLES2.h"

class CTexture {
public:

	CTexture():
	  //m_pDX11Texture(0),
	  //m_pDX11ShaderResourceView(0),
	  width(0),
	  height(0),
	  format(0),
	  type(0),
	  m_id(0),
	  samplerMode(XR_SAMPLER_CLAMP)
	{
	}
	~CTexture() {};

	void operator=(const CTexture& rhs)
	{
		//m_pDX11Texture = rhs.m_pDX11Texture;
		//m_pDX11ShaderResourceView = rhs.m_pDX11ShaderResourceView;
	}

	Int32 GetWidth () { return width; }
	Int32 GetHeight () { return height; }

	Void Release() {
		//SAFE_RELEASE(m_pDX11Texture);
		//SAFE_RELEASE(m_pDX11ShaderResourceView);
	}
	UInt32 type;
	Int32 m_id;
	UInt32 texid;
	UInt32 samplerMode;
	Int32 width;
	Int32 height;
	UInt32 format;

	//ID3D11Texture2D*					m_pDX11Texture;
	//ID3D11ShaderResourceView*           m_pDX11ShaderResourceView;
};

#endif  // __C_TEXTURE_H_
