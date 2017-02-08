#ifndef __CMESH_H__
#define __CMESH_H__
#include "../../External/IMesh.h"
#include "../../Common/XrInternal.h"
#include "../../Common/XrAABBox.h"

class CMaterial;

typedef struct tagBoundingSphere {
	Float32		x;
	Float32		y;
	Float32		z;
	Float32		r;
} BoundingSphere;

typedef struct tagMeshAttributData{
	UInt32 nStride;
	UInt8* pData;
	Void Reset();
	Boolean IsEmpty() const
	{
		return ( pData == NULL && nStride == 0 );
	}
	tagMeshAttributData()
		: nStride(0),pData(NULL)
	{}
	Void Clear();
}MeshAttributData;


class CMesh: public IMesh, public CXrRef
{
	friend class CBatchRender;
public:
	CMesh();
	virtual ~CMesh();

	virtual String GetName();
	virtual Void SetName(String name);

	virtual xr_state LockData(
		/* [out] */ Float32** ppData,
		/* [out] */ XRVertexLayout* format,
		/* [out] */ Int32* vertexCount);

	virtual xr_state LoadFromFile(
		/* [in] */ String name,
		/* [in] */ Float32 scale,
		/* [in] */ Boolean reserve);

	virtual xr_state UnLockData();

	xr_state SetupVB(Void* vertexData, XRVertexLayout layout, Int32 count, XRBufferUsage usage);
	xr_state SetupIB(Void* indexData, Int32 size, XRBufferUsage usage);

	xr_state UpdateVB(Float32* vertexData);
	xr_state UpdateIB(UInt16* indexData);

	CVertexBuffer* GetVB(Int32* pSize = NULL);
	CIndexBuffer* GetIB(Int32* pSize = NULL);

	Int32 GetVertexCount() { return m_vertexCount; }
	Int32  GetIndexCount() { return m_indexCount; }
	 void  SetIndexCount(Int32 indexCount) { m_indexCount= indexCount; }
	 void  SetVertexCount(Int32 indexCount) { m_vertexCount= indexCount; }

	Void ReleaseIB();
	Void ReleaseVB();


	XRVertexLayout GetVertexLayout() { return m_vertexLayout; }

	Void SetId(Int32 id) { m_id = id; }
	Int32 GetId() { return m_id; }


	virtual Void* GetRealType() { return m_self; } 

	virtual Int32 Release();

	xr_state GenPrimitive(Float32 xs, Float32 ys, Float32 zs, ModelType type, Region* roi);

	xr_state GenSubdivision(Float32 sx, Float32 sy, Float32 sz, Int32 dx, Int32 dy, Int32 dz, ModelType type, CMaterial* mtl=0);

	const AABBox& GetBound() const { return this->m_bound; }
	AABBox& GetBound() { return m_bound; }

	Void SetBonePalleteId(Int32 id) {
		m_bonePalleteId = id;
	}

	Int32 GetBonePalleteId() {
		return m_bonePalleteId;
	}

    Boolean HasBone() {
		if (m_bonePalleteId>=0) return TRUE;
		else return FALSE;
	}

	virtual xr_state LoadVertexFromArray(
		/* [in] */ Float32* pData,
		/* [in] */ XRVertexLayout format,
		/* [in] */ Int32 count);

	virtual xr_state LoadIndexFromArray(
		/* [in] */ UInt16* pIndex,
		/* [in] */ Int32 count);

	//deprecated
	Void SetExternalModel(Void* native) { m_externalModel = native; }
	Void* GetExternalModel() { return m_externalModel; }
	Void CleanExternalModel();
	UInt32 GetExternalModelFormat() { return m_externalFormat; }
	Void SetExternalModelFormat(UInt32 format) { m_externalFormat = format; }
	
	virtual unsigned char  GetEnable();
	virtual xr_state SetEnable(unsigned char enable);

private:
	Int32					m_maxInfNum;
	XRVertexLayout          m_vertexLayout;
	Int32					m_indexCount;
	Int32					m_vertexCount;
	CVertexBuffer*			m_vbo;
	CIndexBuffer*			m_ibo;

	AABBox					m_bound;
	Int32					m_id;
	String					m_meshName;
	Void*					m_self;
	Int32					m_bonePalleteId;
    void*                   m_pdata;
	//deprecated
	Void*					m_externalModel;
	UInt32					m_externalFormat;
	unsigned char           m_enable;
};

#endif  //__CMESH_H__
