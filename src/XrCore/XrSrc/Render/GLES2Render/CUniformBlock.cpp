#include "CUniformBlock.h"

//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
xr_state CUniformBlock::Alloc(Int32 size)
{
	pData = new char[size];
	dataSize = size;
	return XR_OK;
}


Void CUniformBlock::Update(Void* data, Int32 offset, Int32 size)
{
	memcpy((char*)pData+offset, data, size);
}
