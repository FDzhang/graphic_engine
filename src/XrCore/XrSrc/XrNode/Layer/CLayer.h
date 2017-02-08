#ifndef __CLAYER_H__
#define __CLAYER_H__
#include "../../Common/XrInternal.h"
#include "../../External/ILayer.h"
#include "../Animation/CAProperty.h"

class CRenderList;
class CMaterial;

class CLayer: virtual public ILayer, public CTreeNode<CLayer>
{
public:
	CLayer(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, CMaterial* pMtl,  Float32 opacity);
	virtual ~CLayer();
    virtual String GetName();
	virtual Void SetName(String name);

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
		/* [in] */ Float32 y);

    virtual xr_state MovePosition(
        /* [in] */ Float32 x,
        /* [in] */ Float32 y);

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

    virtual xr_state SetWidth(
        /* [in] */ Float32 width);

    virtual xr_state SetHeight(
        /* [in] */ Float32 height);

	virtual xr_state SetOpacity(
    /* [in] */ Float32 opacity);

	virtual xr_state SetScale(
		/* [in] */ Float32 xs,
		/* [in] */ Float32 ys);

    virtual xr_state SetEnable(
        /* [in] */ Boolean enable);

    virtual xr_state SetBackColor(
        /* [in] */ UInt32 color);

    virtual xr_state MasksToBound(
        /* [in] */ Boolean flag);

    virtual xr_state SetAnchorPoint(
        /* [in] */ Float32 anchorX,
        /* [in] */ Float32 anchorY);

		
	virtual xr_state SetMaterial(
		/* [in] */ IMaterial* pIMaterial);

	virtual xr_state SetMaterialROI(
		/* [in] */ Region* pRoi);
		
    virtual xr_state Remove();

	virtual xr_state Release();

    virtual xr_state Detach();

    virtual xr_state SetTransitionStyle(
		/* [in] */ UInt32 duration,
		/* [in] */ AnimationStyle style,
		/* [in] */ UInt32 type);

    virtual xr_state BringForward();

    virtual xr_state SendBackward();

    virtual xr_state SendTo(Int32 toIndex, Int32 flag);

    virtual xr_state BringToFront();

    virtual xr_state LayerSendToBack();

	virtual Float32 GetWidth() { return width.GetDst(); }

	virtual Float32 GetHeight() { return height.GetDst(); }

	virtual Float32 GetX() { return x.GetDst(); }

	virtual Float32 GetY() { return y.GetDst(); }

	virtual Float32 GetZ() { return z.GetDst(); }

	virtual xr_state SetEventResponder(class IEventResponder* responder)
	{
		m_responder = responder;
		return XR_OK;
	}

	//Float32 GetXAnchorPoint() { return x.Get() - width.Get()* m_anchorX; }

	//Float32 GetYAnchorPoint() { return y.Get() - height.Get()* m_anchorY; }

	//Float32 GetZAnchorPoint() { return m_z.Get(); }

	Float32 GetAnchorX() { return m_anchorX; }

	Float32 GetAnchorY() { return m_anchorY; }

    virtual Float32 GetAbsoluteX();

    virtual Float32 GetAbsoluteY();

	Void GetAbsolutePosition(Float32* x, Float32* y);

	virtual xr_state SetColor(
         /* [in] */ Float32 r,
		 /* [in] */ Float32 g,
		 /* [in] */ Float32 b);

	virtual xr_state GetColor(
         /* [out] */ Float32* r,
		 /* [out] */ Float32* g,
		 /* [out] */ Float32* b);

    virtual Boolean GetEnable();

	virtual Int32 GetId();

	Void SetOwnerInfo(class CUINode* node, Int32 id) { m_owner = node; m_id = id;}
	
	virtual Boolean OnTouch(TouchPackage* package);

	Void MeasureSize(Float32* width, Float32* height);

	LayerType GetType() { return m_layerType; }

	EventStyle GetEventStyle() { return m_eventStyle; }

	CMaterial* GetMaterial() { return m_pMtl; }

	Float32 GetOpacity() { return opacity.Get(); }
	
	Boolean UseTransform();
	Float32* GetTransform() { return 0; }
	
	Region* GetROI() { return &m_matROI; }

	virtual Void* GetRealType() { return m_self; } 

	class CUINode* GetOwner() { return m_owner; }

	//Void* SetAttachedRenderUI(class CRenderNode* node) { return m_attachedNode = node; }
	virtual	xr_state DivertEvent(Int32 RTNodeId);
	virtual Int32 OnAddMesh(Float32* vBuffer, UInt16* iBuffer, Float32 x, Float32 y, Float32 opacity, Int32* vCount, Int32* iCount);
	virtual Int32 GetVertexCount() { return 4; }
	class CMesh* GetMesh() { return m_mesh; }
	Int32 GetQuadCount();
	Void GetVertexQuad(Float32* vertexPt);	//array size should be 16 
	Void GetQuadRegion(Region* region);
	//Boolean isSimpleRotation() { return rz.Get()== 0 ||  rz.Get()== 90 || rz.Get()== 180 || rz.Get()== 270; }
	Boolean hasMesh() { return !(m_mesh == 0); }

	static Void GetAdaptiveLayerSize(CMaterial* pMtl, Rect* roi, Float32& w, Float32& h, Region& texCoord);
	xr_state SetMaterial(CMaterial* pMtl);

	Boolean isMasksToBound() {
		return m_masksToBound; 
	}

	virtual Void GetCAProperty(
	/* [in] */ APType type,
	/* [out] */ IAProperty** ppIAProperty);

 	CAProperty				x;
	CAProperty				y;
	CAProperty				z;
	CAProperty				rx;
	CAProperty				ry;
	CAProperty				rz;
	CAProperty				width;
	CAProperty				height;
	CAProperty				opacity;
	CAProperty				r;
	CAProperty				g;
	CAProperty				b;

protected:
	Int32					m_id;
	Float32					m_anchorX;
	Float32					m_anchorY;

	Boolean					m_enable;
	Boolean					m_masksToBound;
	Boolean					m_respondEvent;
	class IEventResponder*	m_responder;
	LayerType				m_layerType;
	EventStyle              m_eventStyle;
	class CMesh*			m_mesh;
	CMaterial*				m_pMtl;
	class CRenderNode*		m_attachedNode;
	CUINode*			m_owner;
	Region					m_matROI;
	CHAR					m_name[MaxNameLen]; 
	
	Void*					m_self;
};

#define LAYER_DEFAULT_IMPLEMENTATION                                            \
using CLayer::SetWidth;                                                     \
using CLayer::SetHeight;                                                    \
using CLayer::SetX;                                                         \
using CLayer::SetY;                                                         \
using CLayer::SetZ;															\
using CLayer::SetPosition;                                                 \
using CLayer::MovePosition;                                                 \
using CLayer::SetEnable;                                                   \
using CLayer::SetScale;                                                    \
using CLayer::SetBackColor;                                                 \
using CLayer::MasksToBound;                                                 \
using CLayer::SetAnchorPoint;                                               \
using CLayer::Remove;                                                  \
using CLayer::Detach;                                                       \
using CLayer::SetTransitionStyle;                                       \
using CLayer::BringForward;                                                 \
using CLayer::SendBackward;                                                 \
using CLayer::SendTo;                                                       \
using CLayer::BringToFront;                                                 \
using CLayer::GetWidth;                                                     \
using CLayer::GetHeight;                                                    \
using CLayer::GetX;                                                         \
using CLayer::GetY;                                                         \
using CLayer::GetZ;                                                   \
using CLayer::GetEnable;                                                   \
using CLayer::GetId;                                                   \
using CLayer::GetAbsoluteX;                                                     \
using CLayer::GetAbsoluteY;                                               \
using CLayer::SetEventResponder;											\
using CLayer::SetColor;                                               \
using CLayer::GetColor;											\

#endif  //__CLAYER_H__

