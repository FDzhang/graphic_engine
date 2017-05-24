#ifndef __C_VERTEX_LAYOUT_H__
#define __C_VERTEX_LAYOUT_H__

#include "../intrinsic.h"
#include "utilityGLES2.h"

enum XRPrimitiveType {
    XRPT_NONE						= 0x00000000,
	XRPT_TRIANGLE_LIST				= 0x00000001,
	XRPT_TRIANGLE_STRIP				= 0x00000002,
	XRPT_TRIANGLE_FAN				= 0x00000003,
	XRPT_TRIANGLE_POINT             = 0x00000004,
};

typedef struct XR_VERTEX_LAYOUT {
    String			semanticName;
    UInt32			index;
    XRBufferFormat  format;
    UInt32			offset;
} 	XR_VERTEX_LAYOUT;

class CVertexLayout
{
public:
	CVertexLayout():
	  elementNum(0)
	{
	}
	bool Init(XR_VERTEX_LAYOUT* pLayout, Int32 num);
	Int32 GetVertexSize();

private:
	friend class CRenderDevice;
	friend class CRenderContext;

	//ID3D11InputLayout*	m_pDX11VertexLayout;
	Int32				elementNum;
	XR_VERTEX_LAYOUT	desc[8];
	XRVertexLayout      layout;
};

#endif  //__C_VERTEX_LAYOUT_H__
