#ifndef __CXGLOWBUTTON_H__
#define __CXGLOWBUTTON_H__
#include "CXrBaseView.h"

class CXrGlowButton : public CXrBaseView
{
public:
	CXrGlowButton();
	~CXrGlowButton();
	
	virtual xr_state Add(class IUINode* node,Int32 targetIndex, InsertFlag flag, Int32 x=0, Int32 y=0, Int32 w=0, Int32 h=0, class IButtonAction* action=0);

	void SetBaseMaterial(Int32 mtlId);
	void SetGlowMaterial(Int32 mtlId);

	virtual void OnButtonPressed();
	
	static Void GetMaterial(class IUINode* node, Int32 * baseMtl, Int32* glowMtl);

	virtual Boolean OnTouchEvent(
		/* [in] */Int32 layerId,
		/* [in] */Int32 x,
		/* [in] */Int32 y,
		/* [in] */Int32 type);
	
	virtual Void* GetRealType() { return (Void*)this; }

	//VIEW_DEFAULT_IMPLEMENTATION

private:
	static Int32			baseMtlId;
	static Int32			glowMtlId;
	Boolean m_isPressed;

	Int32			baseLayerId;
	Int32			glowLayerId;
	ILayer*			glow;
	IButtonAction	*buttonAction;
};

#endif  //__CXGLOWBUTTON_H__

