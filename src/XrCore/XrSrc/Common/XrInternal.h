#ifndef __XR_INTERNAL_H__
#define __XR_INTERNAL_H__

#include "xrDataStruct.h"
#include "../External/xrUtility.h"
#include "XRString.h"
#include "../Platform/XrOS.h"
#include "../Platform/xrConfig.h"
#include "../Render/XrRender.h"
//#include "../XrCore/CDeviceManager.h"

extern class CDeviceManager* XRDM;
extern class CAnimationManager* XRAM;
extern class CRenderManager* XRRM;
extern class CXrCore* XrCore;

//extern class CXrSwapChain* XrSwapChain;
//extern class CRenderDevice* XrRenderDevice;
//extern class CRenderContext* XrRenderContext;

class CXrTextureEx : public CTexture, public CXrRef
{
public:
	CXrTextureEx() { isInitialized = 0; }
	~CXrTextureEx();


	Void		Release();
	Void		ForceRelease();
	Int32	    isInitialized;
    Int32		hashA;
    Int32		hashB;
	Void*		extraInfo;
	//class		ITextureDelegate* pDelegate;
	Int32		updateId;
};

class CShaderObjectEx : public CShaderObject, public CXrRef
{
public:
	CShaderObjectEx() {}
	~CShaderObjectEx();

	Void Release();
	Void ForceRelease();

	CUniformBlock           ub;
	CUniformBlock           ub2;
    Int32		hashA;
    Int32		hashB;
	Int32		id;
};

#endif  //__XR_INTERNAL_H__

