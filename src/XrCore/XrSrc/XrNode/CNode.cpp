#include "CNode.h"
//#include "CMesh.h"

#include "../Common/xrDataStruct.cpp"
#include "Scene/CSceneNode.h"

CNode::CNode(CSceneNode* scene):
	m_drawMode(DrawMode_Triangles),
	selfRotation(0),
	selfScale(0),
	preRotation(0),
	postRotation(0),
	m_customTransform(0),
	m_name(0),
	m_currentDrawable(0),
	m_boneType(-1),
	m_instancingCount(0),
	m_instancing(0)
{
	m_self = (Void*)this;
	m_enable = TRUE;
	m_visible = TRUE;
	opacity._Set(1.0);
	brightness._Set(1.0);
	m_owner = scene;
}
 
CNode::~CNode()
{
	if (m_drawable.mesh) m_drawable.mesh->Release();
	if (m_drawable.mtl) m_drawable.mtl->Release();
	CDrawable* drawable = m_drawable.GetNext();
	while (drawable) {
		CDrawable* temp = drawable;
		drawable = drawable->GetNext();
		temp->mesh->Release();
		temp->mtl->Release();
		delete temp;
	}

	if (selfRotation) delete selfRotation;
	if (selfScale) delete selfScale;
	if (m_customTransform) delete m_customTransform;
	if (m_name) delete m_name;
}

xr_state CNode::GenPrimitive(Float32 xs, Float32 ys, Float32 zs, ModelType type, Region* roi)
{
	if (!m_drawable.mesh) {m_drawable.mesh = new CMesh();
	}
	if (!m_drawable.mesh) return XR_FAILED;
	m_drawable.mesh->GenPrimitive(xs, ys, zs, type, roi);
	return XR_OK;
}

xr_state CNode::GenSubdivision(Float32 sx, Float32 sy, Float32 sz, Int32 dx, Int32 dy, Int32 dz, ModelType type, Int32 mtlId)
{
	if (!m_drawable.mesh){ m_drawable.mesh = new CMesh();
		}
	if (!m_drawable.mesh) return XR_FAILED;

	m_drawable.mesh->GenSubdivision(sx, sy, sz, dx, dy, dz, type);
	ResetPosition();
	SetMaterial(mtlId);

	return XR_OK;
}

xr_state CNode::ResetPosition()
{
	this->position.x.Set(0, 0, 0);
	this->position.y.Set(0, 0, 0);
	this->position.z.Set(0, 0, 0);
	this->rotation.x.Set(0, 0, 0);
	this->rotation.y.Set(0, 0, 0);
	this->rotation.z.Set(0, 0, 0);
	this->scale.x.Set(1.0, 0, 0);
	this->scale.y.Set(1.0, 0, 0);
	this->scale.z.Set(1.0, 0, 0);
	if (preRotation) {
		preRotation->MakeIdentity();
	}
	if (postRotation) {
		postRotation->MakeIdentity();
	}

	return XR_OK;
}


Void CNode::SetName(String name)
{
	Int32 len = strlen(name)+1;
	if (!m_name) {m_name = new CHAR[len];
	}
	strcpy(m_name, name);
}


xr_state CNode::SetMaterial(
	/* [in] */ Int32 materialId)
{
	SAFE_RELEASE(m_drawable.mtl);
	m_drawable.mtl = m_owner->GetMaterialObject(materialId);
	m_drawable.mtl->AddRef();

	return XR_OK;
}
xr_state CNode::GetMaterial(
	/* [out] */ IMaterial** ppIMaterial)
{
	if (ppIMaterial) *ppIMaterial = m_drawable.mtl;
	return XR_OK;
}

xr_state CNode::SetX(
    /* [in] */ Float32 x)
{
	this->position.x.Set(x);
	return XR_OK;
}

xr_state CNode::SetY(
    /* [in] */ Float32 y)
{
	this->position.y.Set(y);
	return XR_OK;
}

xr_state CNode::SetZ(
    /* [in] */ Float32 z)
{
	this->position.z.Set(z);
	return XR_OK;
}

xr_state CNode::SetDX(
    /* [in] */ Float32 x)
{
	this->position.x.Delta(x);
	return XR_OK;
}


xr_state CNode::SetDY(
    /* [in] */ Float32 y)
{
	this->position.y.Delta(y);
	return XR_OK;
}

xr_state CNode::SetDZ(
    /* [in] */ Float32 z)
{
	this->position.z.Delta(z);
	return XR_OK;
}

xr_state CNode::SetPosition(
    /* [in] */ Float32 x,
	/* [in] */ Float32 y,
    /* [in] */ Float32 z)
{
	this->position.x.Set(x);
	this->position.y.Set(y);
	this->position.z.Set(z);

	return XR_OK;
}

xr_state CNode::MovePosition(
    /* [in] */ Float32 x,
    /* [in] */ Float32 y,
	/* [in] */ Float32 z)
{
	this->position.x.Delta(x);
	this->position.y.Delta(y);
	this->position.z.Delta(z);

	return XR_OK;
}

xr_state CNode::RotateX(
    /* [in] */ Float32 rx)
{
	this->rotation.x.Set(Deg2Rad(rx));
	return XR_OK;
}


xr_state CNode::RotateY(
    /* [in] */ Float32 ry)
{
	this->rotation.y.Set(Deg2Rad(ry));
	return XR_OK;
}
 
xr_state CNode::RotateZ(
    /* [in] */ Float32 rz)
{
	this->rotation.z.Set(Deg2Rad(rz));
	return XR_OK;
}

xr_state CNode::RotateDX(
    /* [in] */ Float32 rx)
{
	this->rotation.x.Delta(Deg2Rad(rx));
	return XR_OK;
}

xr_state CNode::RotateDY(
    /* [in] */ Float32 ry)
{
	this->rotation.y.Delta(Deg2Rad(ry));
	return XR_OK;
}

xr_state CNode::RotateDZ(
    /* [in] */ Float32 rz)
{
	this->rotation.z.Delta(Deg2Rad(rz));
	return XR_OK;
}

xr_state CNode::Rotate(
		/* [in] */ Float32 rx,
		/* [in] */ Float32 ry,
		/* [in] */ Float32 rz)
{
	this->rotation.x.Set(rx);
	this->rotation.y.Set(ry);
	this->rotation.z.Set(rz);
	return XR_OK;
}

xr_state CNode::SelfRotateX(
    /* [in] */ Float32 rx)
{
	if (InitSelfRotation())  this->selfRotation->x.Set(Deg2Rad(rx));
	return XR_OK;
}


xr_state CNode::SelfRotateY(
    /* [in] */ Float32 ry)
{
	if (InitSelfRotation())  this->selfRotation->y.Set(Deg2Rad(ry));
	return XR_OK;
}
 
xr_state CNode::SelfRotateZ(
    /* [in] */ Float32 rz)
{
	if (InitSelfRotation())  this->selfRotation->z.Set(Deg2Rad(rz));
	return XR_OK;
}

xr_state CNode::SelfRotateDX(
    /* [in] */ Float32 rx)
{
	if (InitSelfRotation()) this->selfRotation->x.Delta(Deg2Rad(rx));
	return XR_OK;
}

xr_state CNode::SelfRotateDY(
    /* [in] */ Float32 ry)
{
	if (InitSelfRotation()) this->selfRotation->y.Delta(Deg2Rad(ry));
	return XR_OK;
}

xr_state CNode::SelfRotateDZ(
    /* [in] */ Float32 rz)
{

	if (InitSelfRotation()) this->selfRotation->z.Delta(Deg2Rad(rz));
	return XR_OK;
}


xr_state CNode::SelfScale(
    /* [in] */ Float32 x,
	/* [in] */ Float32 y,
	/* [in] */ Float32 z)
{
	if (InitSelfScale()) {
		if (x==0 || y==0 || z==0) {
			return XR_OK;
		}
		selfScale->x.Set(x);
		selfScale->y.Set(y);
		selfScale->z.Set(z);
	}

	return XR_OK;
}

xr_state CNode::SetOpacity(
/* [in] */ Float32 opacity)
{
	this->opacity.Set(opacity);
	return XR_OK;
}

xr_state CNode::GetOpacity(
/* [in] */ Float32* opacity)
{
	*opacity = this->opacity.Get();
	return XR_OK;
}


xr_state CNode::SetScale(
	/* [in] */ Float32 sx,
	/* [in] */ Float32 sy,
	/* [in] */ Float32 sz)
{
	this->scale.x.Set(sx);
	this->scale.y.Set(sy);
	this->scale.z.Set(sz);
	return XR_OK;
}

xr_state CNode::SetEnable(
    /* [in] */ Boolean flag)
{
	m_enable = flag;
	return XR_OK;
}

xr_state CNode::SetBrightness(Float32 value)
{
	brightness.Set(value, 0, 0);
	return XR_OK;
}

xr_state CNode::GetBrightness(Float32* value)
{
	*value = brightness.Get();
	return XR_OK;
}

 xr_state CNode::GetMesh(
	/* [in] */ IMesh** ppImesh)
{
	//if (!m_drawable.mesh) m_drawable.mesh = new CMesh();
	if (!m_drawable.mesh) return XR_FAILED;
	if (!ppImesh) return XR_FAILED;
	*ppImesh = m_drawable.mesh;
	return XR_OK;
}

xr_state CNode::SetMesh(
	/* [in] */Int32 meshId)
{
	SAFE_RELEASE(m_drawable.mesh);
	m_drawable.mesh = m_owner->GetMeshObject(meshId);
	m_drawable.mesh->AddRef();
	m_owner->OnCreateModelMesh(this);

	return XR_OK;
}

Void CNode::AddDrawable(CMesh* mesh, CMaterial* mtl)
{
	CDrawable* drawable;
	if (!m_drawable.mesh) {
		m_drawable.mesh = mesh;
		m_drawable.mtl = mtl;
	}
	else {
		drawable = new CDrawable;
		m_drawable.Append(drawable);
		drawable->mesh = mesh;
		drawable->mtl = mtl;
	}
}

BonePallete* CNode::GetMeshBonePallete()
{
	return m_owner->GetBonePallete(m_drawable.mesh->GetBonePalleteId());
}

xr_state CNode::SetDrawModeBits(
    /* [in] */ UInt32 bits)
{
	UInt32 drawStyle = bits & DrawMode_DrawStyle;
	m_drawMode |= bits;
	if (drawStyle) {
		m_drawMode &= ~DrawMode_DrawStyle;
		m_drawMode |= drawStyle;
	}
	return XR_OK;
}

xr_state CNode::SetVisible(
    /* [in] */ Boolean visible)
{
	m_visible = visible;
	return XR_OK;
}

xr_state CNode::ClearDrawModeBits(
    /* [in] */ UInt32 bits)
{
	bits &= ~DrawMode_DrawStyle;
	m_drawMode &= ~(bits&DrawMode_StateDisable);

	return XR_OK;
}

UInt32 CNode::GetDrawModeBits()
{
	return m_drawMode;
}

xr_state CNode::SetCustomTransform(
	/* [in] */ Float32* pMatrix,
	/* [in] */ Boolean transpose)
{
	if (!m_customTransform) {m_customTransform = new Float32[16];
	}
	if (!m_customTransform) return XR_FAILED;
	int x, y, i=0;
	for (x=0;x<4;x++) {
		for (y=0;y<4;y++) {
			if (transpose) m_customTransform[y*4+x] = pMatrix[i];
			else m_customTransform[x*4+y] = pMatrix[i];
			i++;
		}
	}
	return XR_OK;
}

xr_state CNode::SetTransitionStyle(
    /* [in] */ UInt32 duration,
    /* [in] */ AnimationStyle style,
	/* [in] */ UInt32 type)
{
	if (type & AP_X) position.x.SetTransitionStyle(style, duration);
	if (type & AP_Y) position.y.SetTransitionStyle(style, duration);
	if (type & AP_Z) position.z.SetTransitionStyle(style, duration);
	if (type & AP_RX) rotation.x.SetTransitionStyle(style, duration);
	if (type & AP_RY) rotation.y.SetTransitionStyle(style, duration);
	if (type & AP_RZ) rotation.z.SetTransitionStyle(style, duration);
	if (type & AP_SX) scale.x.SetTransitionStyle(style, duration);
	if (type & AP_SY) scale.y.SetTransitionStyle(style, duration);
	if (type & AP_SZ) scale.z.SetTransitionStyle(style, duration);
	if (type & AP_OPACITY) opacity.SetTransitionStyle(style, duration);

	return XR_OK;
}

Void CNode::GetCAProperty(
	/* [in] */ APType type,
	/* [out] */ IAProperty** ppIAProperty)
{
	switch (type) {
		case AP_X:
			*ppIAProperty = &position.x;
			break;
		case AP_Y:
			*ppIAProperty = &position.y;
			break;
		case AP_Z:
			*ppIAProperty = &position.z;
			break;
		case AP_RX:
			*ppIAProperty = &rotation.x;
			break;
		case AP_RY:
			*ppIAProperty = &rotation.y;
			break;
		case AP_RZ:
			*ppIAProperty = &rotation.z;
			break;
		case AP_SX:
			*ppIAProperty = &scale.x;
			break;
		case AP_SY:
			*ppIAProperty = &scale.y;
			break;
		case AP_SZ:
			*ppIAProperty = &scale.z;
			break;
		case AP_SRX:
			if (InitSelfRotation()) *ppIAProperty = &selfRotation->x;
			break;
		case AP_SRY:
			if (InitSelfRotation()) *ppIAProperty = &selfRotation->y;
			break;
		case AP_SRZ:
			if (InitSelfRotation()) *ppIAProperty = &selfRotation->z;
	}
}

xr_state CNode::UpdateProperty(APType type, Float32 val)
{
	switch (type) {
		case AP_X:
			position.x._Set(val);
			break;
		case AP_Y:
			position.y._Set(val);
			break;
		case AP_Z:
			position.z._Set(val);
			break;
		case AP_RX:
			rotation.x._Set(XR_DEG2RAD(val));
			break;
		case AP_RY:
			rotation.y._Set(XR_DEG2RAD(val));
			break;
		case AP_RZ:
			rotation.z._Set(XR_DEG2RAD(val));
			break;
		case AP_SX:
			scale.x._Set(val);
			break;
		case AP_SY:
			scale.y._Set(val);
			break;
		case AP_SZ:
			scale.z._Set(val);
	}
	return XR_OK;

}
const AABBox& CNode::GetBound() const 
{ 
	XrAssert(m_drawable.mesh);
	return m_drawable.mesh->GetBound();
}

xr_state CNode::SetInstancing(
	/* [in] */ Float32* val,
    /* [in] */ UInt32 count)
{
	Int32 i;
	if (m_instancing) delete m_instancing;
	m_instancing = new XRMat4[count];
	Float32* s, *r, *t;
	for (i=0;i<count;i++) {
		s = &val[i*9];
		r = &val[i*9+3];
		t = &val[i*9+6];
		m_instancing[i] = XRMat4::Translation(t[0], t[1], t[2]) * XRMat4::RotationZ(r[2]) * XRMat4::RotationY(r[1]) * XRMat4::RotationX(r[0]) * XRMat4::Scale(s[0], s[1], s[2]);
	}
	m_instancingCount = count;
	return XR_OK;
}

Void CNode::SetPreRotation(Float32 rx, Float32 ry, Float32 rz)
{
	if (rx==0.0 && ry==0.0 && rz==0.0) return;
	InitPreRotation();
	(*preRotation) = XRMat4::RotationX(rx);
	(*preRotation) = XRMat4::RotationY(ry)*(*preRotation);
	(*preRotation) = XRMat4::RotationZ(rz)*(*preRotation);
}

Void CNode::SetPostRotation(Float32 rx, Float32 ry, Float32 rz)
{
	if (rx==0.0 && ry==0.0 && rz==0.0) return;
	InitPostRotation();
	(*postRotation) = XRMat4::RotationX(rx);
	(*postRotation) = XRMat4::RotationY(ry)*(*postRotation);
	(*postRotation) = XRMat4::RotationZ(rz)*(*postRotation);
}
