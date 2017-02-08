#ifndef _IFRAGMENTPROGRAM_H
#define _IFRAGMENTPROGRAM_H
#include "xrIntrinsic.h"
#include "IResource.h"


class IFragmentProgram : virtual public IResource
{
public:
	virtual Void AddUniform(const String&) = 0;
	virtual Void AddTextureUniform(const String&,UInt32 idx) = 0;
	virtual Void SetFP(const String&) = 0;
};

#endif