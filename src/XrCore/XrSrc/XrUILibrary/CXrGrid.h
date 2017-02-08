#ifndef __CXRGRID_H__
#define __CXRGRID_H__
#include "CXrBaseView.h"

class CXrGrid : public CXrBaseView
{
public:
	CXrGrid();
	~CXrGrid();
	virtual Void* GetObject() { return (Void*)this; }
private:
};

#endif  //__CXRGRID_H__
