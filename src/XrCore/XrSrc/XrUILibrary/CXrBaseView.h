#ifndef __CXRBASEVIEW_H__
#define __CXRBASEVIEW_H__
#include "../External/XrHeaders.h"
#include "../External/IEventResponder.h"
#include "../External/ILayer.h"
#include "../Platform/XrPath.h"
#include "2DShaper.h"
#include "IActionTrigger.h"

class CXrBaseView : public IEventResponder
{
public:
	CXrBaseView();
	virtual xr_state InitView();
	
	virtual xr_state Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x=0, Int32 y=0, Int32 w=0, Int32 h=0);
	
	virtual Void SetEnable(Boolean enable);

	virtual Void SetOpacity(Float32 opacity);

	virtual Boolean OnTouchEvent(
		/* [in] */Int32 layerId,
		/* [in] */Int32 x,
		/* [in] */Int32 y,
		/* [in] */Int32 type);
	
	//virtual class CLayer* GetRoot();
	
	virtual Void SetPosition(Float32 x, Float32 y);
	virtual Void SetDX(Float32 x);
	virtual Void SetDY(Float32 y);
	virtual Void SetSize(Float32 w, Float32 h);
	virtual String GetName(); 
	virtual Int32 GetRootId() { return m_rootId; } 
	virtual ILayer* GetRoot() { return m_root; } 
	virtual Void SetName(
		/* [in] */ String name); 

	virtual Void* GetRealType() { return (Void*)this; }

	virtual Void SetOnClickDelegate(IActionTrigger* trigger);

	virtual Void SetAnchorPoint(
		/* [in] */Float32 x,
		/* [in] */Float32 y);

	virtual Void Show();
	virtual Void Hide();

protected:
	 String				m_name;
	 ILayer*			m_root;
	 Int32				m_rootId;
	 class IUINode*  m_node;
	 IActionTrigger*	m_trigger;
};

#define VIEW_DEFAULT_IMPLEMENTATION                                            \
using CXrBaseView::InitView;                                                     \
using CXrBaseView::AddToRenderNode;                                                    \
using CXrBaseView::GetName;                                                     \
using CXrBaseView::SetName;                                                    \
using CXrBaseView::SetOnClickDelegate;                                                    \
using CXrBaseView::SetDX;	\
using CXrBaseView::SetDY;	\
using CXrBaseView::SetAnchorPoint;	\
using CXrBaseView::Show;	\
using CXrBaseView::Hide;	\

#endif  //__CXRBASEVIEW_H__

