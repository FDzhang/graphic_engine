#include "CSpirit.h"
#include "../Mesh/CMesh.h"
#include "../../3rd/PrimitiveGenerator.h"

CSpirit::CSpirit(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, CMaterial* pMtl, Float32 opacity):
	CLayer(x, y, z, width, height, pMtl, opacity)
{
	r._Set(1);
	g._Set(1);
	b._Set(1);

	m_layerType = LayerType_Spirit;
	//ptr = this;
	m_self = (Void*)this;
}

CSpirit::~CSpirit()
{
	//xrprint("spirit destroy~\n");
}

xr_state CSpirit::GenPlaneMesh(
	/* [in] */ Int32 x,
	/* [in] */ Int32 y,
	/* [in] */ Int32 dx,
	/* [in] */ Int32 dy,
	/* [in] */ Float32 texScaleX,
	/* [in] */ Float32 texScaleY)
{
	m_mesh = new CMesh();
	if (!m_mesh) return XR_FAILED;

	if (XRFAILED(GenLayerMesh(x, y, texScaleX, texScaleY, dx, dy, m_mesh))) {
		delete m_mesh;
		m_mesh = 0;
		return XR_FAILED;
	}
	//m_mesh = 0;
	return XR_OK;
}
