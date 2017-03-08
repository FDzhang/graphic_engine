#ifndef __CXRCORE_H__
#define __CXRCORE_H__
#include "../External/IXrCore.h"
#include "CDeviceManager.h"
#include "CAnimationManager.h"
#include "../XrNode/Scene/CUINode.h"
#include "../XrNode/Scene/CSceneNode.h"
#include "../XrNode/Scene/CPostProcessingNode.h"
#include "../Render/CRenderManager.h"
//#include "CPickerManager.h"


extern Int32	g_screenWidth;
extern Int32	g_screenHeight;

inline Int32 GetScreenWidth() { return g_screenWidth; }
inline Int32 GetScreenHeight() { return  g_screenHeight; }

class CXrCore : public IXrCore
{
public:

	CXrCore(Int32 screenWidth, Int32 screenHeight, Int32 context);
	~CXrCore();

	 virtual Int32 CreateRenderNodeUI(
		 /* [in] */ RenderNodeType type,
		 /* [in] */ Int32 RenderTargetID,
		 /* [out] */ IUINode** ppIRenderNodeUI);

	 virtual Int32 CreateRenderNodeScene(
		 /* [in] */ Int32 RenderTargetID,
		 /* [out] */ ISceneNode** ppIRenderNodeScene);

	 virtual Int32 CreatePostProcessingNode(
		/* [in] */ RenderNodeType type,
		/* [out] */ IPostProcessingNode** ppIRenderNodeEffect);

	 //virtual Int32 CreateControlPointList(Float32* input,UInt32 ptnum,UInt32 elemNum,
		// /* [out] */ IControlPointList** ppIControlPointList);

	 virtual xr_state ReleaseRenderNode(
		 /* [in] */ Int32 RenderNodeID);

	 virtual xr_state NodeInsertTo(
	 /* [in] */ RenderNodeType type,
     /* [out] */ IRenderNode** ppIRenderNode);

	virtual xr_state NodeBringForward(
	 /* [in] */ RenderNodeType type,
     /* [out] */ IRenderNode** ppIRenderNode);

	virtual xr_state NodeSendBackward(
	 /* [in] */ RenderNodeType type,
     /* [out] */ IRenderNode** ppIRenderNode);

	virtual xr_state GetDeviceManager(
     /* [out] */ IDeviceManager** ppIDeviceManager);

	 virtual xr_state GetAnimationManager(
     /* [out] */ IAnimationManager** ppIAnimationManager);

	 virtual xr_state GetPickerManager(
     /* [out] */ IPickerManager** ppIPickerManager);


	virtual xr_state ProcessEvent();
	virtual xr_state Update();
	virtual xr_state Render();
	virtual xr_state OnTouchEvent(
        /* [in] */ Int32 x,
        /* [in] */ Int32 y,
		/* [in] */ UInt32 type);

	virtual xr_state OnKeyEvent(
        /* [in] */ UInt32 key,
        /* [in] */ UInt32 type);

	virtual xr_state Release();
	
	CRenderTargetEx* GetRenderTarget(Int32 rtId) { return m_dm.m_renderTarget.Get(rtId); }
	CRenderNode* GetRenderNode(Int32 id) { return m_node.Get(id); }

	Void GetScreenSize(Int32 *w, Int32 *h) { *w = m_screenWidth; *h = m_screenHeight; }
	Int32 GetScreenWidth() { return m_screenWidth; }
	Int32 GetScreenHeight() { return  m_screenHeight; }
    //Void SetDefualtFBId(Int32 id);
	Void SetClearBackground(Boolean flag);
	Void SetDeferredRendering(Boolean flag);
	Void OnRenderFinish();
	Boolean useDeferredRendering() { return m_rm.isDeferredRendering(); }
	virtual xr_state SetScreenROI(
		/* [in] */ Int32 x, 
		/* [in] */ Int32 y, 
		/* [in] */ Int32 width, 
		/* [in] */ Int32 height);

	virtual Boolean IsLayerHit()
	{
		return m_isLayerHit;
	}

private:

	CRenderTargetEx* ResolveRenderTarget(CRenderNode* node);

	CLazySlot<CRenderNode, DefaultNumRenderNode>				m_node;
	CFlushQueue<TouchPackage, DefaultEventNum>					m_eventQueue;
	CXrBiLinkList<CRenderNode>									m_nodeList;
	CXrBiLinkList<CRenderNode>									m_RTnodeList;
	//CLazySlot<CControlPointList, MaxNumCPL>						m_controlPLList;
	CRenderTargetEx*											m_currentRenderTarget;
	CDeviceManager											    m_dm;
	CAnimationManager											m_am;
	CRenderManager												m_rm;
	//CPickerManager												m_pickMngr;
	Int32														m_screenWidth;
	Int32														m_screenHeight;
	Boolean														m_isLayerHit;
	
};

#endif  //__CXRCORE_H__
