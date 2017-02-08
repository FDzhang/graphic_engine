#include "CMesh.h"
#include "../CNode.h"
#include "../Scene/CSceneNode.h"

#include "../../3rd/PrimitiveGenerator.h"
#include "../../3rd/XrFileLoader.h"

CMesh::CMesh():
	m_vertexCount(0),
	m_indexCount(0),
	m_vbo(0),
	m_ibo(0),
	m_meshName(0),
	m_bonePalleteId(-1),
	m_maxInfNum(0),
	m_externalModel(0),
	m_externalFormat(0),
	m_enable(1)
{
	m_self = (Void*)this;

}


CMesh::~CMesh()
{
	if (m_externalModel || ( this->m_externalFormat == ModelFormat_MESH )) CleanExternalModel();
	if (m_meshName) delete m_meshName;
	ReleaseVB();
	ReleaseIB();

}

xr_state CMesh::LoadFromFile(
		/* [in] */ String name,
		/* [in] */ Float32 scale,
		/* [in] */ Boolean reserve)
{
    SetName(name);
	return _LoadModelFromFile(name, this, scale, reserve);
}

String CMesh::GetName()
{
	return m_meshName;
}

Void CMesh::SetName(String name)
{
	if (!m_meshName){ m_meshName = new CHAR[strlen(name)+1];
	}
	if (!m_meshName) return;
	strcpy(m_meshName, name);
}

CVertexBuffer* CMesh::GetVB(Int32* pSize)
{
	if (pSize) *pSize = m_vertexCount;
	return m_vbo;
}

CIndexBuffer* CMesh::GetIB(Int32* pSize)
{
	if (pSize) *pSize = m_indexCount;
	return m_ibo;
}


Void CMesh::ReleaseIB()
{
	if (m_ibo) {
		m_ibo->Release();
		delete m_ibo;
	}
	m_indexCount = 0;
} 

Void CMesh::ReleaseVB()
{
	if (m_vbo) {
		m_vbo->Release();
	    delete m_vbo;
	}
	m_vertexCount = 0;
}

xr_state CMesh::SetupVB(Void* vertexData, XRVertexLayout layout, Int32 count, XRBufferUsage usage)
{
	ReleaseVB();
	m_vbo = new CVertexBuffer;
	XRDM->device()->CreateVertexBuffer(vertexData, XR_VERTEX_SIZE(layout), count, m_vbo, usage);
	m_vertexCount = count;
	m_vertexLayout = layout;
	m_pdata = vertexData;
    if(usage == XR_BUFFER_DYNAMIC)
    {
         //dynamic buffer need to store vertexbuffer for further update
         
	}
	return XR_OK;
}

xr_state CMesh::SetupIB(Void* indexData, Int32 size, XRBufferUsage usage)
{
	ReleaseIB();
	m_ibo = new CIndexBuffer;
	XRDM->device()->CreateIndexBuffer(indexData, size, m_ibo, usage);
	m_indexCount = size/2;
	return XR_OK;
}
xr_state CMesh::SetEnable(unsigned char enable)
{
    if(enable!=0)
    {
        m_enable=1;
    }
	else
	{
	    m_enable =0;
	}
	return 0;
}
unsigned char  CMesh::GetEnable()
{

    return m_enable;
}
xr_state CMesh::LoadVertexFromArray(
	/* [in] */ Float32* pData,
	/* [in] */ XRVertexLayout format,
	/* [in] */ Int32 count)
{
	SetupVB(pData, format, count, XR_BUFFER_DYNAMIC);

	return XR_OK;
}

xr_state CMesh::LoadIndexFromArray(
	/* [in] */ UInt16* pIndex,
	/* [in] */ Int32 count)
{
	SetupIB(pIndex, count, XR_BUFFER_STATIC);
	return XR_OK;
}

xr_state CMesh::UpdateVB(Float32* vertexData)
{
	XRDM->device()->UpdateVertexBuffer(vertexData, m_vbo);
	return XR_OK;
}

xr_state CMesh::UpdateIB(UInt16* indexData)
{
	XRDM->device()->UpdateIndexBuffer(indexData, m_ibo);
	return XR_OK;
}

xr_state CMesh::GenPrimitive(Float32 xs, Float32 ys, Float32 zs, ModelType type, Region* roi)
{
	switch (type) {
		case ModelType_Cube:
			if (XRFAILED(GenCubeMesh(xs, ys, zs, this))) {
				return XR_FAILED;
			}
			break;
		case ModelType_Plane:
			if (ys != 0) {
				GenPlaneMeshV(xs, ys, 2, 2, this, roi);
			}
			else {
				GenPlaneMeshH(xs, zs, 2, 2, this, roi);
			}
			break;
		case ModelType_Line:
			GenLineMeshV(xs, ys, (Int32)zs, 2, this, roi);
			break;
		case ModelType_Plane_Dynamic:			
			GenPlaneDynamicMeshH(400, 800, xs, ys, this, roi);
			break;
		default:
			break;
	} 
	return XR_OK;
}

xr_state CMesh::GenSubdivision(Float32 sx, Float32 sy, Float32 sz, Int32 dx, Int32 dy, Int32 dz, ModelType type, CMaterial* mtl)
{
	switch (type) {
		case ModelType_Plane:
			if (sy != 0) {
				GenPlaneMeshV(sx, sy, dx, dy, this, 0);
			}
			else {
				GenPlaneMeshH(sx, sz, dx, dz, this, 0);
			}
			break;
		default:
			break;
	} 

	return XR_OK;
}


xr_state CMesh::LockData(
	/* [out] */ Float32** ppData,
	/* [out] */ XRVertexLayout* format,
	/* [out] */ Int32* vertexCount)
{
	xr_state ret = LockMeshData(this, ppData, format, vertexCount);
	if( XR_OK != ret ){
		if( ppData) *ppData = (float *)this->m_pdata;
		//if (format) *format = this->m_vertexFormat;
		if (vertexCount) *vertexCount = this->m_vertexCount;
	}
	return XR_OK;
}

xr_state CMesh::UnLockData()
{
    xr_state ret = UnLockMeshData(this);
	if( XR_OK != ret )
	{
        UpdateVB((Float32 *)m_pdata);
	}
	return XR_OK;
}


Int32 CMesh::Release()
{
	Int32 refcnt = DecRef();
	if (refcnt == 0) {
		delete this;
    }
	return refcnt;
}

Void CMesh::CleanExternalModel()
{
	UnloadModel(this);
}
