#ifndef _CPICKER_H
#define _CPICKER_H
#include "../../External/IPicker.h"
#include "../Scene/CSceneVisitor.h"
#include "../../Common/XrMathEx.h"

class IRenderNode;



class CPicker : public IPicker
{
public:
	CPicker(UInt32 type);
	~CPicker();

public:
	virtual Void Attach(IRenderNode* pNode);
	virtual Void Detach(IRenderNode* pNode);
	xr_state OnTouchEvent(
		/* [in] */ Int32 x,
        /* [in] */ Int32 y,
		/* [in] */ UInt32 type);
	virtual Void AddResponse(UInt32 response,PICKPROCESSFUNC func);
	Boolean IntersectModel(SceneTraverseInfo* traverseInfo);
	Void Reset(){ this->m_pCurPickedObject = NULL; }
protected:
	virtual Boolean Calculate(Int32 x,Int32 y);
	Boolean TraverseNode(
		/* [in] */ SceneTraverseInfo* traverseInfo,
		/* [in] */ class CPickerVisitor* visitor,
		/* [in] */ Boolean visitSibling);
	
	virtual Void SendEventToAttachNode(Boolean){return;};
	
protected:
	CArray<IRenderNode*>	m_pRenderNodes;
	class CNode*			m_pCurPickedObject;
	UInt32					m_type;
	Ray						m_CurrentRay;
	PICKPROCESSFUNC			m_pOnPickedFunc;
	PICKPROCESSFUNC			m_pOnDragFunc;
};



class CPickerVisitor
{
public:
    CPickerVisitor(class CPicker* picker)
    {
		m_picker = picker;
        m_continue = TRUE;
    }

	Boolean isContinue() { return m_continue; }
    Int32 isNeedVisit(SceneTraverseInfo& traverseInfo);
    Boolean visitNode(SceneTraverseInfo& traverseInfo);

private:
	CPicker* m_picker;
	Boolean m_continue;
};
#endif
