#ifndef __C_VERTEX_BUFFER_H__
#define __C_VERTEX_BUFFER_H__
#include "utilityGLES2.h"
#include "../intrinsic.h"
#include "CVertexLayout.h"

class CVertexBuffer
{
public:
	CVertexBuffer():
	  size(0),
	  vertexSize(0)
	{ }

	~CVertexBuffer() {
	}
	//XRBufferFormat GetFormat() { return m_format; }
	void Release() { }

	Int32 size;
	Int32 vertexSize;
	unsigned int vboId;
	unsigned int mode;

private: 

	friend class CRenderDevice;
	friend class CRenderContext;

};

#endif // __C_VERTEX_BUFFER_H__
