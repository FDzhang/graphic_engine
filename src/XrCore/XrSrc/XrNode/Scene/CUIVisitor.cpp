#include "CUIVisitor.h"
#include "CUINode.h"
#include "../../XrCore/CXrCore.h"

Int32 CUIUpdateVisitor::isNeedVisit(LayerTraverseInfo& traverseInfo)
{
	return traverseInfo.layer->GetEnable() & (traverseInfo.layer->opacity.Get() != 0);
}

Void CUIUpdateVisitor::visitNode(LayerTraverseInfo& traverseInfo)
{
	CLayer* layer = traverseInfo.layer;
    traverseInfo.x += layer->x.Get();
    traverseInfo.y += layer->y.Get();
	traverseInfo.z += layer->z.Get();
	Float32 opacity = layer->opacity.Get();
	traverseInfo.opacity *= opacity;

	if (layer->isMasksToBound()) {
		Rect clip(traverseInfo.x-layer->width.Get()*layer->GetAnchorX(), traverseInfo.y-layer->height.Get()*layer->GetAnchorY(), layer->width.Get(), layer->height.Get());
		traverseInfo.clipRect.Clip(clip);
		if (traverseInfo.clipRect.IsEmpty()) {
			m_continue = FALSE;
			return;
		}
	}
	else {
		Rect clip(traverseInfo.x-layer->width.Get()*layer->GetAnchorX(), traverseInfo.y-layer->height.Get()*layer->GetAnchorY(), layer->width.Get(), layer->height.Get());
		Rect screen(0,0,GetScreenWidth(),GetScreenHeight());
		screen.Clip(clip);
		if (screen.IsEmpty()) {
			m_continue = FALSE;
			return;
		}
	}
	m_continue = TRUE;

    if (layer->GetType() & LayerType_Renderable) {
		m_node->AddUIRender(&traverseInfo);
	}

}


Int32 CUIEventVisitor::isNeedVisit(LayerTraverseInfo& traverseInfo)
{
	return traverseInfo.layer->GetEnable() & (traverseInfo.layer->GetEventStyle() & EventStyle_Receive);
}

Void CUIEventVisitor::visitNode(LayerTraverseInfo& traverseInfo)
{
	CLayer* layer = traverseInfo.layer;
    traverseInfo.x += layer->x.Get();
    traverseInfo.y += layer->y.Get();
	traverseInfo.z += layer->z.Get();

	Float32 l,r,t,b;
	l = traverseInfo.x - layer->width.Get()*layer->GetAnchorX();
	r = l + layer->width.Get();
	t = traverseInfo.y - layer->height.Get()*layer->GetAnchorY();
	b = t + layer->height.Get();
	Region reg(l,r,t,b);

	if (reg.IsIn(this->m_touch.x, this->m_touch.y)) {
		m_lastHit = layer;
		m_continue = TRUE;
	}
	else {
		m_continue = FALSE;
	}

    if (layer->GetEventStyle() & EventStyle_Peek) {
		TouchPackage touch = this->m_touch;
		//touch.x = touch.x - l;
		//touch.y = touch.y - t;
		layer->OnTouch(&touch);
	}

}

Void CUIEventVisitor::InitVisit(TouchPackage* package)
{
	m_intersectFlag = FALSE;
	m_lastHit = 0;
	m_touch = *package;
}
