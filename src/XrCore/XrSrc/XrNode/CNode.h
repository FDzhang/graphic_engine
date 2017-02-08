#ifndef __CNode_H__
#define __CNode_H__
#include "../Common/XrInternal.h"
#include "../External/INode.h"
#include "Material/CMaterial.h"
#include "CBaseNode.h"
#include "Mesh/CMesh.h"

class CDrawable : public CUniLinkNode<CDrawable>
{
public:
	CDrawable() {
		mesh=0;
		mtl=0;
	}

public:
	CMesh* mesh;
	CMaterial* mtl;
}; 

class CNode: virtual public INode, public CBaseNode<CNode>
{
public:
	CNode(class CSceneNode* scene);
	//CNode(Float32 x, Float32 y, Float32 z, Float32 scale, ModelType type, CMaterial* mtl=0);
	virtual ~CNode();
	virtual String GetName() {
		return m_name;
	}
	virtual Void SetName(String name);

	Void SetSceneOwnerInfo(class CSceneNode* node, Int32 id) {
		m_owner = node;
		m_id = id;
	}

	CSceneNode* GetSceneNode() { return m_owner; }
	xr_state GenPrimitive(Float32 xs, Float32 ys, Float32 zs, ModelType type, Region* roi);
	xr_state GenSubdivision(Float32 sx, Float32 sy, Float32 sz, Int32 dx, Int32 dy, Int32 dz, ModelType type, Int32 mtlId);

    virtual xr_state SetX(
        /* [in] */ Float32 x);

    virtual xr_state SetY(
        /* [in] */ Float32 y);

	virtual xr_state SetZ(
        /* [in] */ Float32 z);

	virtual xr_state SetDX(
        /* [in] */ Float32 x);

    virtual xr_state SetDY(
        /* [in] */ Float32 y);

	virtual xr_state SetDZ(
        /* [in] */ Float32 z);

    virtual xr_state SetPosition(
        /* [in] */ Float32 x,
		/* [in] */ Float32 y,
        /* [in] */ Float32 z);

    virtual xr_state MovePosition(
        /* [in] */ Float32 x,
        /* [in] */ Float32 y,
		/* [in] */ Float32 z);

	virtual xr_state RotateX(
        /* [in] */ Float32 rx);

    virtual xr_state RotateY(
        /* [in] */ Float32 ry);

	virtual xr_state RotateZ(
        /* [in] */ Float32 rz);

    virtual xr_state RotateDX(
        /* [in] */ Float32 rx);

    virtual xr_state RotateDY(
        /* [in] */ Float32 ry);

	virtual xr_state RotateDZ(
        /* [in] */ Float32 rz);

	virtual xr_state Rotate(
		/* [in] */ Float32 rx,
		/* [in] */ Float32 ry,
		/* [in] */ Float32 rz);

	virtual xr_state SelfRotateX(
        /* [in] */ Float32 rx);

    virtual xr_state SelfRotateY(
        /* [in] */ Float32 ry);

	virtual xr_state SelfRotateZ(
        /* [in] */ Float32 rz);

	virtual xr_state SelfRotateDX(
        /* [in] */ Float32 rx);

    virtual xr_state SelfRotateDY(
        /* [in] */ Float32 ry);

	virtual xr_state SelfRotateDZ(
        /* [in] */ Float32 rz);

	virtual xr_state SelfScale(
    /* [in] */ Float32 x,
	/* [in] */ Float32 y,
	/* [in] */ Float32 z);

	virtual xr_state SetOpacity(
    /* [in] */ Float32 opacity);

	virtual xr_state GetOpacity(
		/* [out] */ Float32* opacity);

	virtual xr_state SetScale(
		/* [in] */ Float32 sx,
		/* [in] */ Float32 sy,
		/* [in] */ Float32 sz);

	virtual xr_state SetBrightness(
		/* [in] */ Float32 value);

	virtual xr_state GetBrightness(
		/* [out] */ Float32* value);

    virtual xr_state SetEnable(
        /* [in] */ Boolean visible);

	virtual Boolean GetEnable() { return m_enable && opacity.Get(); }

	//Boolean GetVisible()
	//{
	//	Boolean visibleTest = (scale.x.Get() != 0) && (scale.y.Get() != 0)  && (scale.y.Get() != 0) && (opacity.Get() != 0);
	//	return m_enable && visibleTest;
	//}

    virtual xr_state SetVisible(
        /* [in] */ Boolean visible);

	Boolean InitSelfRotation()
	{
		if (!selfRotation) {
			selfRotation = new CAVector3;
			if (selfRotation) {
			selfRotation->x.Set(0,0,0);
			selfRotation->y.Set(0,0,0);
			selfRotation->z.Set(0,0,0);
			}
		}
		return (selfRotation != 0);
	}
	Boolean InitSelfScale()
	{
		if (!selfScale) {
			selfScale = new CAVector3;
			if (selfScale) {
				selfScale->x.Set(1,0,0);
				selfScale->y.Set(1,0,0);
				selfScale->z.Set(1,0,0);
			}
		}
		return (selfScale != 0);
	}
	Boolean InitPreRotation()
	{
		if (!preRotation) {
			preRotation = new XRMat4;
		}
		return (preRotation != 0);
	}
	Boolean InitPostRotation()
	{
		if (!postRotation) {
			postRotation = new XRMat4;
		}
		return (postRotation != 0);
	}
	//xr_state AddMaterial(CMaterial* mtl);

	CMaterial* GetMaterial() { return m_drawable.mtl; }

	virtual Void* GetRealType() { return m_self; } 
	
	CMesh* GetMesh() { return m_drawable.mesh; }

	struct BonePallete* GetMeshBonePallete();

	virtual xr_state GetMesh(
		/* [in] */ IMesh** ppImesh);
	
	virtual xr_state SetMesh(
		/* [in] */ Int32 meshId);

	virtual xr_state SetMaterial(
		/* [in] */ Int32 materialId);

	//virtual xr_state GetMaterial(
	//	/* [out] */ IMaterial** ppImtl);

	virtual xr_state GetMaterial(
		/* [out] */ IMaterial** ppIMaterial);

	virtual xr_state SetDrawModeBits(
        /* [in] */ UInt32 bits);

	virtual xr_state SetInstancing(
	/* [in] */ Float32* val,
    /* [in] */ UInt32 count);

	virtual xr_state ClearDrawModeBits(
        /* [in] */ UInt32 bits);

    virtual UInt32 GetDrawModeBits();
	
	virtual xr_state ResetPosition();

	//Void SetMesh(CMesh* mesh) { m_drawable.mesh = mesh; }
	Void AddDrawable(CMesh* mesh, CMaterial* mtl);

	virtual xr_state SetCustomTransform(
		/* [in] */ Float32* pMatrix,
		/* [in] */ Boolean transpose);

    virtual xr_state SetTransitionStyle(
		/* [in] */ UInt32 duration,
		/* [in] */ AnimationStyle style,
		/* [in] */ UInt32 type);

	Float32* GetCustomTransform() { return m_customTransform; }

	virtual Void GetCAProperty(
		/* [in] */ APType type,
		/* [out] */ IAProperty** ppIAProperty);

	virtual Float32 GetX() { return position.x.Get(); }

    virtual Float32 GetY() { return position.y.Get(); }

	virtual Float32 GetZ() { return position.z.Get(); }

	virtual const class AABBox& GetBound() const ;

	virtual Int32 GetId() { return m_id; }

	Void GetScalingMatrix(XRMat4* mat) {
		*mat = XRMat4::Scale(scale.x.Get(), scale.y.Get(), scale.z.Get());
	}

	Void GetRotationMatrix(XRMat4* mat) {
		(*mat) = XRMat4::RotationX(rotation.x.Get());
		(*mat) = XRMat4::RotationY(rotation.y.Get())*(*mat);
		(*mat) = XRMat4::RotationZ(rotation.z.Get())*(*mat);
		if (postRotation) (*mat) =  (*mat)*(*postRotation);
		if (preRotation) (*mat) =  (*preRotation)*(*mat);
	}

	Void GetTranslationMatrix(XRMat4* mat) {
		*mat = XRMat4::Translation(position.x.Get(), position.y.Get(), position.z.Get());
	}

	Boolean isBone() {
		return m_boneType<0 ? false:true;
	}

	Void FirstDrawable() {
		m_currentDrawable = &m_drawable;
	}

	Boolean DrawableEnds() {
		if (!m_currentDrawable) return TRUE;
		else {
			if (!m_currentDrawable->mesh) return TRUE;
			return FALSE;
		}
	}
	CDrawable* GetCurrentDrawable() {
		return m_currentDrawable;
	}

	Void NextDrawable() {
		if (m_currentDrawable) m_currentDrawable = m_currentDrawable->GetNext();
	}

	xr_state UpdateProperty(APType type, Float32 val);
	
	Int32 GetInstancingCount() {
		return m_instancingCount;
	}
	XRMat4* GetInstancing() {
		return m_instancing;
	}

	Void SetPreRotation(Float32 rx, Float32 ry, Float32 rz);
	Void SetPostRotation(Float32 rx, Float32 ry, Float32 rz);

	CAProperty						opacity;
	CAProperty						brightness;

	//XRMat4*						m_boneInv;

	Int32							m_boneType;

	XRMat4* 						preRotation;
    XRMat4* 						postRotation;
	XRMat4  						m_globalTransform;

protected:

	CAVector3*						selfRotation;
	CAVector3*						selfScale;
	CDrawable						m_drawable;
	CDrawable*						m_currentDrawable;
	CSceneNode*						m_owner;
	UInt32 							m_drawMode;
	Void*							m_self;
	Float32*						m_customTransform;
	XRMat4*							m_instancing;
	UInt32							m_instancingCount;
	String							m_name;
};

#endif  //__CNode_H__

