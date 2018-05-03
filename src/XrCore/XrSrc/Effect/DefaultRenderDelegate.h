#ifndef __RENDERDELEGATE_H__
#define __RENDERDELEGATE_H__

#include "../External/IRenderDelegate.h"
#include "../Common/XrMathEx.h"

class RenderDelegate_Basic : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
		/* [in] */ class IMaterial* pMtl,
		/* [in] */ const XRMat4* pModelMatrix,
		/* [in] */ const XRMat4* pViewMatrix,
		/* [in] */ const XRMat4* pProjMatrix,
		/* [in] */ class CLight* pLight,
		/* [in] */ class IObject* pIObject);
};

class RenderDelegate_UI_Font : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
		/* [in] */ class IMaterial* pMtl,
		/* [in] */ const XRMat4* pModelMatrix,
		/* [in] */ const XRMat4* pViewMatrix,
		/* [in] */ const XRMat4* pProjMatrix,
		/* [in] */ class CLight* pLight,
		/* [in] */ class IObject* pIObject);
};

class RenderDelegate_FlObject : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};
class RenderDelegate_FrObject : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};

class RenderDelegate_Rigid_Texture : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};
class RenderDelegate_RigidColor_Texture : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};
class RenderDelegate_Rigid_Blend: public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};
class RenderDelegate_Color_Plot: public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};
class RenderDelegate_Dynamic_Blend: public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};

class RenderDelegate_Skinned_Texture : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};

class RenderDelegate_SkyBox : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};


class RenderDelegate_Rigid_Bump : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};

class RenderDelegate_Skinned_Bump : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};

class RenderDelegate_Shadow : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};


class RenderDelegate_Shadow_Skinned : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};

class RenderDelegate_FrGlossy : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};
class RenderDelegate_FrGlossyColor : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};
class RenderDelegate_FrGlossyAlpha : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};

class RenderDelegate_FrGlass : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};
class RenderDelegate_FrGlassAlpha : public IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject);
};

#endif  //__RENDERDELEGATE_H__
