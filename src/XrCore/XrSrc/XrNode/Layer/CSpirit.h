#ifndef __CSPIRIT_H__
#define __CSPIRIT_H__
#include "../../Common/XrInternal.h"
#include "../../External/ISpirit.h"
#include "CLayer.h"

class CSpirit: public ISpirit, public CLayer
{
public:
	CSpirit(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, CMaterial* pMtl, Float32 opacity);
	virtual ~CSpirit();

	virtual xr_state GenPlaneMesh(
		/* [in] */ Int32 x,
		/* [in] */ Int32 y,
		/* [in] */ Int32 dx,
		/* [in] */ Int32 dy,
		/* [in] */ Float32 texScaleX,
		/* [in] */ Float32 texScaleY);

	LAYER_DEFAULT_IMPLEMENTATION

private:

};

#endif  //__CLAYER_H__

