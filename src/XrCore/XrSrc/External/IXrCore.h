#ifndef __IXRCORE_H__
#define __IXRCORE_H__
#include "xrIntrinsic.h"
#include "../Common/xrDataStruct.h"
#include "../Common/XrAABBox.h"
#include "IMaterial.h"
#include "ICamera.h"
#include "IUINode.h"
#include "ISceneNode.h"
#include "IPostProcessingNode.h"
#include "IRenderTarget.h"
#include "IDeviceManager.h"
#include "IKeyAnimation.h"
#include "IAnimationManager.h"
#include "IAnimationDelegate.h"
#include "IScrollingAnimation.h"
#include "ISpirit.h"
#include "IAProperty.h"
#include "ILayoutPanel.h"
#include "IScrollPanel.h"
#include "ITextLayer.h"
#include "INode.h"
#include "IMesh.h"
#include "ILight.h"
#include "IRenderDelegate.h"
#include "ITextureDelegate.h"
#include "IPicker.h"
#include "IPickerManager.h"
#include "IVertexProgram.h"
#include "IMaterialEx.h"
#include "IFragmentProgram.h"
#include "ITechnique.h"
#include "IPass.h"



class IXrCore
{
public:
	 virtual Int32 CreateRenderNodeUI(
		 /* [in] */ RenderNodeType type,
		 /* [in] */ Int32 RenderTargetID,
		 /* [out] */ IUINode** ppIRenderNodeUI)=0;

	 virtual Int32 CreateRenderNodeScene(
		 /* [in] */ Int32 RenderTargetID,
		 /* [out] */ ISceneNode** ppIRenderNodeScene)=0;

	 virtual Int32 CreatePostProcessingNode(
		 /* [in] */ RenderNodeType type,
		 /* [out] */ IPostProcessingNode** ppIRenderNodeEffect)=0;

	 //virtual Int32 CreateControlPointList(Float32* input,UInt32 ptnum,UInt32 elemNum,
		// /* [out] */ IControlPointList** ppIControlPointList) = 0;

	 virtual xr_state ReleaseRenderNode(
		 /* [in] */ Int32 RenderNodeID)=0;

	virtual xr_state GetDeviceManager(
     /* [out] */ IDeviceManager** ppIDeviceManager)=0;

 	virtual xr_state GetAnimationManager(
     /* [out] */ IAnimationManager** ppIAnimationManager)=0;

	virtual xr_state GetPickerManager(
     /* [out] */ IPickerManager** ppIPickerManager)=0;

	virtual xr_state ProcessEvent()=0;
	virtual xr_state Update()=0;
	virtual xr_state Render()=0;

	virtual xr_state OnTouchEvent(
        /* [in] */ Int32 x,
        /* [in] */ Int32 y,
		/* [in] */ UInt32 type)=0;

	virtual xr_state OnKeyEvent(
        /* [in] */ UInt32 key,
        /* [in] */ UInt32 type)=0;

	virtual xr_state Release()=0;
	virtual Boolean IsLayerHit()=0;
	virtual Void SetClearBackground(Boolean flag)=0;
	virtual Void SetDeferredRendering(Boolean flag)=0;
	virtual xr_state SetScreenROI(
		/* [in] */ Int32 x, 
		/* [in] */ Int32 y, 
		/* [in] */ Int32 width, 
		/* [in] */ Int32 height)=0;

};

void XrGetDeviceContextAndSwapChainFB(CRenderContext** ppCContext, CRenderDevice** ppCDevice, CSwapChain** ppCSwapChain, CRenderTarget** ppFB);
xr_state InitXrSystem(Int32 screenWidth, Int32 screenHeight, Int32 context);
Int32 XrGetScreenWidth();
Int32 XrGetScreenHeight();
xr_state ShutDownXrSystem();
//IVisualTreeManager* GetVisualTreeManagerInterface();
IXrCore* GetXrCoreInterface();

#endif  //__IXRCORE_H__
