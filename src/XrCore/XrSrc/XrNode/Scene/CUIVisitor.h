#ifndef __C_GLUI_VISITOR_H__
#define __C_GLUI_VISITOR_H__
#include "../../Common/XrInternal.h"
#include "CRenderNode.h"

class CUINode;

class CUIUpdateVisitor : public CNodeVisitor
{
public:
	CUIUpdateVisitor(CUINode* node) { m_node = node; }
    Int32 isNeedVisit(LayerTraverseInfo& traverseInfo);
    Void visitNode(LayerTraverseInfo& traverseInfo);

private:
	CUINode*	m_node;

};

class CUIEventVisitor : public CNodeVisitor
{
public:
	CUIEventVisitor(CUINode* list) { m_list = list; m_lastHit = 0; m_intersectFlag = FALSE;}
    Int32 isNeedVisit(LayerTraverseInfo& traverseInfo);
    Void visitNode(LayerTraverseInfo& traverseInfo);
	Void InitVisit(TouchPackage* package);
	CLayer* GetLastHitLayer() { return m_lastHit; }

private:
	TouchPackage	m_touch;
	KeyPackage		m_key;
	CUINode*	m_list;
	Boolean			m_intersectFlag;
	CLayer*			m_lastHit;
};

#endif  //__C_GLUI_VISITOR_H__

