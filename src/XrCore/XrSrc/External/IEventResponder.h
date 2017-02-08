#ifndef __IEVENTRESPONDER_H__
#define __IEVENTRESPONDER_H__
#include "IObject.h"

class IEventResponder : public IObject
{
public:
    // Common Layer API
    //
	virtual Boolean OnTouchEvent(
		/* [in] */Int32 layerId,
		/* [in] */Int32 x,
		/* [in] */Int32 y,
		/* [in] */Int32 type)=0;

	//virtual xr_state OnKeyEvent(
	//	/* [in] */UInt32 key,
	//	/* [in] */Int32 type)=0;

};

#endif  //__IEVENTRESPONDER_H__
