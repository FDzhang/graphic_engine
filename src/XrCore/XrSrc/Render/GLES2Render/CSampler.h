#ifndef __C_SAMPLER_H_
#define __C_SAMPLER_H_
#include "utilityGLES2.h"
#include "../intrinsic.h"

class CSampler {
public:

	CSampler()
	{
	}
	  ~CSampler() {}

	Void Bind(UInt32 type);
	UInt32   mode;
private:
	friend class CRenderDevice;
	friend class CRenderContext;

	//ID3D11SamplerState*           m_pDX11Sampler;
};

#endif  // __C_SAMPLER_H_
