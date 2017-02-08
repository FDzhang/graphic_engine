#ifndef __CXR_BORDER_H__
#define __CXR_BORDER_H__
#include "CXrBaseView.h"

class CXrBorder : public CXrBaseView
{
public:
	CXrBorder();
	~CXrBorder();
	virtual Void* GetObject() { return (Void*)this; }
private:
};

#endif  //__CXR_BORDER_H__
