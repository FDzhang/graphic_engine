#ifndef __CXR_DIVIDER_H__
#define __CXR_DIVIDER_H__
#include "CXrBaseView.h"

class CXrDivider : public CXrBaseView
{
public:
	CXrDivider(Int32 len, Boolean isHorizontal, Boolean isDashed);
	~CXrDivider() {};
	
	virtual xr_state Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x=0, Int32 y=0,Int32 num=1,Int32 interval=0);
	Void InitMaterial(class IUINode* node);
	virtual Void SetLength(Int32 len) { m_len = len; }
	virtual Void* GetObject() { return (Void*)this; }
	Void SetThickness(Int32 thickness);
	Void InitTex();
	Void DeInitTex();
	void Update();
	
	void SetColor(float r,float g,float b);
private:	
	Boolean		    m_isHorizontal;
	Boolean			m_isDashed;
	Int32			m_mtlId;
//	Int32			m_texId;
	Int32			m_len;
    Int32           m_thickness;
};

#endif  //__CXR_DIVIDER_H__
