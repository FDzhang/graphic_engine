#ifndef __C_INDEX_BUFFER_H__
#define __C_INDEX_BUFFER_H__

#include "utilityGLES2.h"
#include "../intrinsic.h"
//#include "XrVertexLayout.h"

class CIndexBuffer
{
public:
	CIndexBuffer()
	{ }
	~CIndexBuffer() {
	}

	Void Release() {
		//if (g_pDX11IndexBuffer) g_pDX11IndexBuffer->Release();
	}

	Int32 GetIBO() { return m_iboId; }
	int m_size;
	unsigned int m_mode;
	unsigned int m_iboId;
private:

	friend class CRenderDevice;
	friend class CRenderContext;

};

#endif // __C_INDEX_BUFFER_H__
