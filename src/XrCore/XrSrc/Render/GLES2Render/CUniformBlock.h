#ifndef __C_UNIFORM_BLOCK_H__
#define __C_UNIFORM_BLOCK_H__
#include "utilityGLES2.h"
#include "../intrinsic.h"

class CUniformBlock
{
public:
	CUniformBlock()
	{
		pData = 0;
		dataSize = 0;
		//offset = 0;
	}

	~CUniformBlock() {
		SAFE_DELETE(pData);
	}
	//int GenLocation(const char** Attribs, int AttribsArraySize, const char** Uniforms, int UniformsArraySize, const char** Textures, int TextureArraySize);
	xr_state Alloc(Int32 size);

	Void* GetData() {
		return pData;
	}
	//Int32 GetOffset() {
	//	return offset;
	//}
	Int32 GetSize() {
		return dataSize;
	}
	Void Update(Void* data, Int32 offset, Int32 size);

private:
	//friend class CRenderDevice;
	//friend class CRenderContext;
	Void* pData;
	//Int32 offset;
	Int32 dataSize;
};

#endif // __C_UNIFORM_BLOCK_H__
