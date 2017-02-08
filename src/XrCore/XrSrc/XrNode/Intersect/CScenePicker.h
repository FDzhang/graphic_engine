#ifndef _CSCENEPICKER_H
#define _CSCENEPICKER_H
#include "CPicker.h"
#include "../Scene/CSceneVisitor.h"
#include "../../Common/XrMathEx.h"

class IRenderNode;



class CScenePicker : public CPicker
{
public:
	CScenePicker();
	~CScenePicker();

public:
	virtual Void Attach(IRenderNode* pNode);
	virtual Void Detach(IRenderNode* pNode);
	xr_state OnTouchEvent(
		/* [in] */ Int32 x,
        /* [in] */ Int32 y,
		/* [in] */ UInt32 type);
	virtual Void AddResponse(UInt32 response,PICKPROCESSFUNC func);
	Boolean IntersectModel(SceneTraverseInfo* traverseInfo,XRVec3& hitpos,Float32& dst);
	Void Reset(){ this->m_pCurPickedObject = NULL; }
	virtual Void SendEventToAttachNode(Boolean b) { m_bSendEventToAttachNode = b; }
protected:
	virtual Boolean Calculate(Int32 x,Int32 y);
	Boolean TraverseNode(
		/* [in] */ SceneTraverseInfo* traverseInfo,
		/* [in] */ class CScenePickerVisitor* visitor,
		/* [in] */ Boolean visitSibling);
	Void ProcessAttachUINode(
		/* [in] */ Int32 x,
        /* [in] */ Int32 y,
		/* [in] */ UInt32 type);
	Boolean NearCamer(class CCamera* camera,XRVec3& v1,XRVec3&v2) const;
	
protected:
	CArray<IRenderNode*>	m_pRenderNodes;
	class CModel*			m_pCurPickedObject;
	UInt32					m_type;
	Ray						m_CurrentRay;
	PICKPROCESSFUNC			m_pOnPickedFunc;
	PICKPROCESSFUNC			m_pOnDragFunc;
	PICKPROCESSFUNC			m_pOnUnPickFunc;
	Float32					m_dst;
	Boolean					m_bSendEventToAttachNode;
};



class CScenePickerVisitor
{
public:
    CScenePickerVisitor(class CScenePicker* picker)
    {
		m_picker = picker;
        m_continue = TRUE;
    }

	Boolean isContinue() { return m_continue; }
    Int32 isNeedVisit(SceneTraverseInfo& traverseInfo);
    Boolean visitNode(SceneTraverseInfo& traverseInfo,XRVec3& hitpos,Float32& dst);

private:
	CScenePicker* m_picker;
	Boolean m_continue;
};
#endif