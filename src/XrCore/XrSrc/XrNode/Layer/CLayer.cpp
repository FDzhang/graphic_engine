#include "CLayer.h"
#include "../Scene/CRenderNode.h"
#include "../Material/CMaterial.h"
#include "../../External/IEventResponder.h"
#include "../../XrCore/CXrCore.h"
#include "../../Common/xrDataStruct.cpp"

CLayer::CLayer(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, CMaterial* pMtl,  Float32 opacity):
	m_layerType(LayerType_DefaultLayer),
	m_eventStyle(EventStyle_Receive),
	m_enable(1),
	m_masksToBound(0),
	m_anchorX(0.0f),
	m_anchorY(0.0f),
	m_id(-1),
	m_self(0),
	m_attachedNode(0),
	m_owner(0),
	m_mesh(0),
	m_respondEvent(FALSE),
	m_responder(0)
{
	this->x._Set(x);
	this->y._Set(y);
	this->z._Set(z);
	this->rx._Set(0);
	this->ry._Set(0);
	this->rz._Set(0);
	this->width._Set(width);
	this->height._Set(height);
	this->opacity._Set(opacity);
	SetMaterial(pMtl);
	m_name[0] = 0;
	m_name[1] = 0;
}

CLayer::~CLayer()
{
	if (m_mesh) {
		m_mesh->Release();
	}
	if (m_pMtl) {
		m_pMtl->Release();
	}
}

String CLayer::GetName()
{
	return m_name;
}

Void CLayer::SetName(String name)
{
}

xr_state CLayer::SetX(
    /* [in] */ Float32 x)
{
	this->x.Set(x);
	return XR_OK;
}

xr_state CLayer::SetY(
    /* [in] */ Float32 y)
{
	this->y.Set(y);
	return XR_OK;
}

xr_state CLayer::SetZ(
    /* [in] */ Float32 z)
{
	this->z.Set(z);
	return XR_OK;
}

xr_state CLayer::SetDX(
    /* [in] */ Float32 x)
{
	this->x.Delta(x);
	return XR_OK;
}


xr_state CLayer::SetDY(
    /* [in] */ Float32 y)
{
	this->y.Delta(y);
	return XR_OK;
}

xr_state CLayer::SetDZ(
    /* [in] */ Float32 z)
{
	this->z.Delta(z);
	return XR_OK;
}

xr_state CLayer::SetPosition(
    /* [in] */ Float32 x,
	/* [in] */ Float32 y)
{
	this->x.Set(x);
	this->y.Set(y);

	return XR_OK;
}

xr_state CLayer::MovePosition(
    /* [in] */ Float32 x,
    /* [in] */ Float32 y)
{
	return XR_OK;
}

xr_state CLayer::RotateX(
    /* [in] */ Float32 rx)
{
	this->rx.Set(Deg2Rad(rx));
	return XR_OK;
}


xr_state CLayer::RotateY(
    /* [in] */ Float32 ry)
{
	this->ry.Set(Deg2Rad(ry));
	return XR_OK;
}

xr_state CLayer::RotateZ(
    /* [in] */ Float32 rz)
{
	this->rz.Set(Deg2Rad(rz));
	return XR_OK;
}

xr_state CLayer::RotateDX(
    /* [in] */ Float32 rx)
{
	this->rx.Delta(Deg2Rad(rx),0,0);
	return XR_OK;
}


xr_state CLayer::RotateDY(
    /* [in] */ Float32 ry)
{
	this->ry.Delta(Deg2Rad(ry),0,0);
	return XR_OK;
}

xr_state CLayer::RotateDZ(
    /* [in] */ Float32 rz)
{
	this->rz.Delta(Deg2Rad(rz),0,0);
	return XR_OK;
}

xr_state CLayer::Rotate(
		/* [in] */ Float32 rx,
		/* [in] */ Float32 ry,
		/* [in] */ Float32 rz)
{
	this->rx.Set(rx);
	this->ry.Set(ry);
	this->rz.Set(rz);
	return XR_OK;
}


xr_state CLayer::SetWidth(
    /* [in] */ Float32 width)
{
	this->width.Set(width);
	return XR_OK;
}

xr_state CLayer::SetHeight(
    /* [in] */ Float32 height)
{
	this->height.Set(height);
	return XR_OK;
}

xr_state CLayer::SetOpacity(
    /* [in] */ Float32 opacity)
{
	this->opacity.Set(opacity);
	return XR_OK;
}

xr_state CLayer::SetScale(
	/* [in] */ Float32 xs,
	/* [in] */ Float32 ys)
{
	Float32 w,h;
	if (m_pMtl) {
		m_pMtl->GetSize(&w, &h);
		this->width.Set(w*xs);
		this->height.Set(h*ys);
	}
	return XR_OK;
}

xr_state CLayer::SetEnable(
    /* [in] */ Boolean enable)
{
	m_enable = enable;
	return XR_OK;
}


xr_state CLayer::SetBackColor(
    /* [in] */ UInt32 color)
{
	return XR_OK;
}

xr_state CLayer::MasksToBound(
    /* [in] */ Boolean flag)
{
	m_masksToBound = flag;
	return XR_OK;
}

xr_state CLayer::SetAnchorPoint(Float32 anchorX, Float32 anchorY)
{
	m_anchorX = anchorX;
	m_anchorY = anchorY;
	return XR_OK;
}

	
xr_state CLayer::SetMaterial(IMaterial* pIMaterial)
{

	return XR_OK;
}

xr_state CLayer::SetMaterialROI(
	/* [in] */ Region* pRoi)
{
	if (pRoi) {
		m_matROI = *pRoi;
	}
	else {
		m_matROI.Set(0,1,0,1);
	}
	return XR_OK;
}
	
xr_state CLayer::Remove()
{
	m_owner->RemoveLayer(m_id);
	return XR_OK;
}

xr_state CLayer::Release()
{
	m_owner->RemoveLayer(m_id);
	return XR_OK;
}

xr_state CLayer::Detach()
{
	Isolate();
	return XR_OK;
}

xr_state CLayer::SetTransitionStyle(
    /* [in] */ UInt32 duration,
    /* [in] */ AnimationStyle style,
	/* [in] */ UInt32 type)
{
	if (type & AP_X) x.SetTransitionStyle(style, duration);
	if (type & AP_Y) y.SetTransitionStyle(style, duration);
	if (type & AP_Z) z.SetTransitionStyle(style, duration);
	if (type & AP_RX) rx.SetTransitionStyle(style, duration);
	if (type & AP_RY) ry.SetTransitionStyle(style, duration);
	if (type & AP_RZ) rz.SetTransitionStyle(style, duration);
	if (type & AP_WIDTH) width.SetTransitionStyle(style, duration);
	if (type & AP_HEIGHT) height.SetTransitionStyle(style, duration);
	if (type & AP_OPACITY) opacity.SetTransitionStyle(style, duration);

	return XR_OK;
}

xr_state CLayer::BringForward()
{
	return XR_OK;
}

xr_state CLayer::SendBackward()
{
	return XR_OK;
}

xr_state CLayer::SendTo(Int32 toIndex, Int32 flag)
{
	return XR_OK;
}

xr_state CLayer::BringToFront()
{
	return XR_OK;
}

xr_state CLayer::LayerSendToBack()
{
	return XR_OK;
}

Float32 CLayer::GetAbsoluteX()
{
	return 0;
}

Float32 CLayer::GetAbsoluteY()
{
	return 0;
}

Void CLayer::GetAbsolutePosition(Float32* x, Float32* y)
{
    CLayer* layer = GetSuper();

    *x = GetX();
    *y = GetY();

    while (layer) {
        *x += layer->GetX();
        *y += layer->GetY();
        layer = layer->GetSuper();
    }

    return;
}


xr_state CLayer::SetColor(
     /* [in] */ Float32 r,
	 /* [in] */ Float32 g,
	 /* [in] */ Float32 b)
{
	this->r.Set(r);
	this->g.Set(g);
	this->b.Set(b);
	return XR_OK;
}

xr_state CLayer::GetColor(
     /* [out] */ Float32* r,
	 /* [out] */ Float32* g,
	 /* [out] */ Float32* b)
{
	*r = this->r.GetDst();
	*g = this->g.GetDst();
	*b = this->b.GetDst();
	return XR_OK;
}

Boolean CLayer::GetEnable()
{
	return m_enable;
}

Void CLayer::MeasureSize(Float32* width, Float32* height)
{
	if (m_enable) {
		*width = this->width.GetDst();
		*height= this->height.GetDst();
	}
	else {
		*width = 0;
		*height = 0;
	}
}

Boolean CLayer::UseTransform()
{
	if (0 != rx.Get() ||  0 != ry.Get() || 0 != rz.Get() || m_mesh) return TRUE;
	else return FALSE;
}


Boolean CLayer::OnTouch(TouchPackage* package)
{
	Float32 x, y, l ,t;
	GetAbsolutePosition(&x, &y);
	l = x - width.Get()*GetAnchorX();
	t = y - height.Get()*GetAnchorY();

	//if (package->touchEvent == TouchEvent_Down) {
	//	xrprint("layer %d hitted,(w=%f,h=%f), x=%f, y=%f. \n", this->GetId(), this->GetWidth(), this->GetHeight(), package->x - l, package->y - t);
	//}
	//else if (package->touchEvent == TouchEvent_Move) {
	//	xrprint("layer %d touched,(w=%f,h=%f), x=%f, y=%f. \n", this->GetId(), this->GetWidth(), this->GetHeight(), package->x - l, package->y - t);
	//}
	if (m_responder) {
		m_respondEvent = m_responder->OnTouchEvent(m_id, package->x - l, package->y - t, package->touchEvent);
	}
	
	if (m_attachedNode) {
		TouchPackage pak;
		pak.x = package->x - l;
		pak.y = package->y - t;
		pak.touchEvent = package->touchEvent;
		m_attachedNode->AddTouchEvent(&pak);
		m_respondEvent = TRUE;
	}

	return m_respondEvent;
}

Int32 CLayer::GetId()
{
	return m_id;
}

Int32 CLayer::OnAddMesh(Float32* vBuffer, UInt16* iBuffer, Float32 x, Float32 y, Float32 opacity, Int32* vCount, Int32* iCount)
{

	return 0;
}

Void CLayer::GetAdaptiveLayerSize(CMaterial* pMtl, XrRect* roi, Float32& w, Float32& h, Region& texCoord)
{

	Float32 mtlW=0, mtlH=0;

	if (pMtl) pMtl->GetSize(&mtlW,&mtlH);

	if (w==0) {
		if (roi) w = roi->width*mtlW;
		else w = mtlW;
	}
	if (h==0) {
		if (roi) h = roi->height*mtlH;
		else h = mtlH;
	}

	if (roi && mtlW && mtlH) {
		texCoord.left = roi->x;
		texCoord.right = roi->x+roi->width;
		texCoord.top = roi->y;
		texCoord.bottom = roi->y+roi->height;
	}
	else {
		texCoord.left = 0.0;
		texCoord.right = 1.0;
		texCoord.top = 0.0;
		texCoord.bottom = 1.0;
	}
}


xr_state CLayer::SetMaterial(CMaterial* pMtl)
{
	m_pMtl = pMtl;
	if (pMtl) pMtl->AddRef();
	return XR_OK;
}

xr_state CLayer::DivertEvent(Int32 RTNodeId)
{
	CRenderNode* node = XrCore->GetRenderNode(RTNodeId);
	m_attachedNode = node;
	return XR_OK;
}


Void CLayer::GetCAProperty(
	/* [in] */ APType type,
	/* [out] */ IAProperty** ppIAProperty)
{
	switch (type) {
		case AP_X:
			*ppIAProperty = &x;
			break;
		case AP_Y:
			*ppIAProperty = &y;
			break;
		case AP_Z:
			*ppIAProperty = &z;
			break;
		case AP_RX:
			*ppIAProperty = &rx;
			break;
		case AP_RY:
			*ppIAProperty = &ry;
			break;
		case AP_RZ:
			*ppIAProperty = &rz;
			break;
		case AP_WIDTH:
			*ppIAProperty = &width;
			break;
		case AP_HEIGHT:
			*ppIAProperty = &height;
			break;
		case AP_OPACITY:
			*ppIAProperty = &opacity;
			break;
	}
}
