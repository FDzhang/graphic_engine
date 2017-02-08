
#include "CXrCore.h"
#include "../Common/xrDataStruct.cpp"
#include "../Render/XrRender.h"
#include "../XrResource/CDataStream.h"
static CXrCore* g_pXrCore=0;

Int32								g_screenWidth=0;
Int32								g_screenHeight=0;

Int32 XrGetScreenWidth()
{
	return g_screenWidth;
}

Int32 XrGetScreenHeight()
{
	return g_screenHeight;
}

xr_state InitXrSystem(Int32 screenWidth, Int32 screenHeight, Int32 context){
	if (g_pXrCore) return XR_FAILED;
    else {
        g_pXrCore = new CXrCore(screenWidth, screenHeight, context);
    }
	g_screenWidth = screenWidth;
	g_screenHeight = screenHeight;
    return XR_OK;
}

void XrGetDeviceContextAndSwapChainFB(CRenderContext** ppCContext, CRenderDevice** ppCDevice, CSwapChain** ppCSwapChain, CRenderTarget** ppFB)
{
	XRDM->GetDeviceContextAndSwapChain(ppCContext, ppCDevice, ppCSwapChain);
	*ppFB = &g_pXrCore->GetRenderTarget(0)->m_rt;
}

xr_state ShutDownXrSystem()
{
	if (g_pXrCore) delete g_pXrCore;
	g_pXrCore = 0;
    return XR_OK;
}

IXrCore* GetXrCoreInterface()
{
    return g_pXrCore;
}

CXrCore::CXrCore(Int32 screenWidth, Int32 screenHeight, Int32 context)
{
	XrASSERT(sceenWidth != 0);
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_isLayerHit = FALSE;
	XRDM = &m_dm;
	XRAM = &m_am;
	XRRM = &m_rm;
	XrCore = this;
	XrCreateDeviceContextAndSwapChain(screenWidth, screenHeight, context, &m_dm.m_renderContext,&m_dm.m_renderDevice, &m_dm.m_swapChain);

	CRenderTargetEx* defaultRenderTarget = m_rm.GetFrameBuffer();
	XRDM->device()->CreateRenderTargetFromSwapChain(m_dm.m_swapChain, &defaultRenderTarget->m_rt);
	//m_defaultRenderTarget->InitFromSwapChain(screenWidth, screenHeight, m_dm.m_swapChain);
	if (defaultRenderTarget) m_dm.m_renderTarget.Add(defaultRenderTarget);
	m_dm.m_renderContext->SetPrimitiveType(XRPT_TRIANGLE_LIST);
	m_dm.Init();
}

CXrCore::~CXrCore()
{
	for (m_node.First();!m_node.IsDone();m_node.Next()) {
		delete m_node.GetCurrent();
	}

	//for (m_controlPLList.First();!m_controlPLList.IsDone();m_controlPLList.Next()) {
	//	delete m_controlPLList.GetCurrent();
	//}

	XRDM = 0;
	XRAM = 0;
	XRRM = 0;
}

Void CXrCore::SetClearBackground(Boolean flag)
{
	//if (defaultRenderTarget) defaultRenderTarget->clear = flag;
}

Void CXrCore::SetDeferredRendering(Boolean flag)
{
	m_rm.SetUseDeferredRendering(flag);
}

//Void CXrCore::SetDefualtFBId(Int32 id)
//{
//    m_defaultRenderTarget->m_fbo = id;
//}

xr_state CXrCore::SetScreenROI(
		/* [in] */ Int32 x, 
		/* [in] */ Int32 y, 
		/* [in] */ Int32 width, 
		/* [in] */ Int32 height)
{
	//m_defaultRenderTarget->m_roi.Set(x, x+width, y, y+height);
	return XR_OK;
}


Int32 CXrCore::CreateRenderNodeUI(
	 /* [in] */ RenderNodeType type,
	 /* [in] */ Int32 RenderTargetID,
     /* [out] */ IUINode** ppIRenderNodeUI)
{
	CUINode*	node;
	Int32			nid;
	node = new CUINode;
	if (node) nid = m_node.Add(node);
	else return -1;
	
	if (RenderTargetID) {
		node->Init(type, m_dm.m_renderTarget.Get(RenderTargetID));
		m_RTnodeList.AddNode(0, node, InsertFlag_Default);
	}
	else {
		node->Init(type, m_screenWidth, m_screenHeight); 
		m_nodeList.AddNode(0, node, InsertFlag_Default);
	}
	
	*ppIRenderNodeUI = node;
	return nid;

}

Int32 CXrCore::CreateRenderNodeScene(
		 /* [in] */ Int32 RenderTargetID,
		 /* [out] */ ISceneNode** ppIRenderNodeScene)
{
	CSceneNode*	node;
	Int32			nid;
	node = new CSceneNode;
	if (node) nid = m_node.Add(node);
	else return -1;
	
	if (RenderTargetID) {
		node->Init(m_dm.m_renderTarget.Get(RenderTargetID));
		m_RTnodeList.AddNode(0, node, InsertFlag_Default);
	}
	else {
		node->Init(m_screenWidth, m_screenHeight); 
		m_nodeList.AddNode(0, node, InsertFlag_Default);
	}
	
	*ppIRenderNodeScene = node;
	return nid;
}

Int32 CXrCore::CreatePostProcessingNode(
	/* [in] */ RenderNodeType type,
	/* [out] */ IPostProcessingNode** ppIRenderNodeEffect)
{
	CPostProcessingNode*	node;
	Int32			nid;
	node = new CPostProcessingNode();
	if (node) nid = m_node.Add(node);
	else return -1;

	node->Init(); 
	m_nodeList.AddNode(0, node, InsertFlag_Default);

	*ppIRenderNodeEffect = node;
	return nid;
}

xr_state CXrCore::ReleaseRenderNode(
	 /* [in] */ Int32 RenderNodeID)
{
	CRenderNode* node = m_node.Get(RenderNodeID);
	
	m_nodeList.removeNode(node);
	m_node.Delete(RenderNodeID);
	return XR_OK;
}

xr_state CXrCore::GetDeviceManager(
 /* [out] */ IDeviceManager** ppIDeviceManager)
{
	*ppIDeviceManager = &m_dm;
	return XR_OK;
}

xr_state CXrCore::GetAnimationManager(
 /* [out] */ IAnimationManager** ppIAnimationManager)
 {
	*ppIAnimationManager = &m_am;
	return XR_OK;
 }
xr_state CXrCore::GetPickerManager(
     /* [out] */ IPickerManager** ppIPickerManager)
{
	//*ppIPickerManager = &this->m_pickMngr;
	return XR_OK;
}
 xr_state CXrCore::NodeInsertTo(
 /* [in] */ RenderNodeType type,
 /* [out] */ IRenderNode** ppIRenderNode)
 {
	 return XR_OK;
 }

xr_state CXrCore::NodeBringForward(
 /* [in] */ RenderNodeType type,
 /* [out] */ IRenderNode** ppIRenderNode)
{
	return XR_OK;
}

xr_state CXrCore::NodeSendBackward(
 /* [in] */ RenderNodeType type,
 /* [out] */ IRenderNode** ppIRenderNode)
{
	return XR_OK;
}
	 

xr_state CXrCore::Update()
{
	CBiLinkIterator<CRenderNode>* pIter;
	CRenderNode* node;
	pIter = m_RTnodeList.GetBiLinkListIterator();
	for (pIter->First(); !pIter->IsDone(); pIter->Next()) {
		node = pIter->GetCurrent();
		if (!node->GetEnable()) continue;
		node->OnUpdate();
	}

	pIter = m_nodeList.GetBiLinkListIterator();
	for (pIter->First(); !pIter->IsDone(); pIter->Next()) {
		node = pIter->GetCurrent();
		if (!node->GetEnable()) continue;
		node->OnUpdate();
	}
	m_am.Update();

	return XR_OK;
}

xr_state CXrCore::Render()
{
	CBiLinkIterator<CRenderNode>* pIter;
	CRenderNode* node;
	pIter = m_RTnodeList.GetBiLinkListIterator();
	for (pIter->First(); !pIter->IsDone(); pIter->Next()) {
        node = pIter->GetCurrent();
		if (!node->GetEnable()) continue;
		node = pIter->GetCurrent();
		node->OnRender(0);
	}
	

	m_currentRenderTarget = 0;
	pIter = m_nodeList.GetBiLinkListIterator();
	for (pIter->First(); !pIter->IsDone(); pIter->Next()) {
		node = pIter->GetCurrent();
		if (!node->GetEnable()) continue;
		
		node->PreRender();
		node->OnRender(ResolveRenderTarget(node));
	}

	return XR_OK;
}

Void CXrCore::OnRenderFinish()
{

}

CRenderTargetEx* CXrCore::ResolveRenderTarget(CRenderNode* node)
{
	Float32 r,g,b,a;
	CRenderContext* ctx= XRDM->context();
	CRenderTargetEx* rt = m_rm.GetFrameBuffer();
	Region* reg = node->GetRenderROI();
	//node = node->GetNext();
	CRenderNode* resolved=node->GetNext();
	while (resolved && !(resolved->GetType() & RenderNodeType_EFFECT && resolved->GetEnable())) {
		resolved = resolved->GetNext();
	}
	if (resolved) {
		rt = resolved->GetRenderTarget();
		//reg = resolved->GetRenderROI();
	}
	node->GetClearColor(&r,&g,&b,&a);
	if (m_currentRenderTarget != rt) {
		ctx->SetRenderTarget(&rt->m_rt, reg);
		if (node->isClearColor()) ctx->ClearRenderTarget(r,g,b,a);
		if (node->isClearDepth()) ctx->ClearDepthStencil();
		m_currentRenderTarget = rt;
	}
	else {
		if (reg) ctx->SetViewport(reg);
		else ctx->SetViewport(0, 0, m_currentRenderTarget->GetWidth(), m_currentRenderTarget->GetHeight());

		if (node->isClearColor()) ctx->ClearRenderTarget(r,g,b,a);
		if (node->isClearDepth()) ctx->ClearDepthStencil();
	}
	return m_currentRenderTarget;
}

xr_state CXrCore::ProcessEvent()
{
	CBiLinkIterator<CRenderNode>* pIter;
	CRenderNode* node;
	pIter = m_nodeList.GetBiLinkListIterator();
	for (m_eventQueue.First(); !m_eventQueue.IsDone(); m_eventQueue.Next()) {
		TouchPackage* pPackage = m_eventQueue.GetCurrent();
		for (pIter->Last(); !pIter->IsDone(); pIter->Prev()) {
			node = pIter->GetCurrent();
			if (!node->OnEvent(pPackage)) {
				m_isLayerHit = TRUE;
				break;
			}
			m_isLayerHit = FALSE;
		}
	}
	m_eventQueue.Reset();

	pIter = m_RTnodeList.GetBiLinkListIterator();
	for (pIter->First(); !pIter->IsDone(); pIter->Next()) {
		node = pIter->GetCurrent();
		node->ProcessEventQueue();
	}

	return XR_OK;
}


xr_state CXrCore::Release()
{
	return XR_OK;
}

xr_state CXrCore::OnTouchEvent(
    /* [in] */ Int32 x,
    /* [in] */ Int32 y,
	/* [in] */ UInt32 type)
{
	TouchPackage package;
	package.x = (Float32)x;
	package.y = (Float32)y;
	package.touchEvent = (TouchEvent)type;
	m_eventQueue.Add(&package);

	//m_pickMngr.OnTouchEvent(x,y,type);
	return XR_OK;
}

xr_state CXrCore::OnKeyEvent(
    /* [in] */ UInt32 key,
    /* [in] */ UInt32 type)
{
	return XR_OK;
}

//Int32 CXrCore::CreateControlPointList(Float32* input,UInt32 ptnum,UInt32 elemNum,
//		 /* [out] */ IControlPointList** ppIControlPointList)
//{
//	CControlPointList* pointlist = NULL;
//	pointlist = new CControlPointList(input,ptnum*elemNum);
//	Int32 nid = m_controlPLList.Add(pointlist);
//	*ppIControlPointList = pointlist;
//
//	return nid;
//}

//Int32 CXrCore::CreateSkeleton(const String name,ISkeleton** ppSkeletonAnimation)
//{
//	CSkeleton* p = NULL;
//	p = new CSkeleton();
//	Int32 nid = m_skeletonList.Add(p);
//	CFileHandleDataStream stream(name);
//	CPODSkeletonLoader loader(p);
//	loader.Load(stream);
//
//	*ppSkeletonAnimation = p;
//
//	return nid;
//}
