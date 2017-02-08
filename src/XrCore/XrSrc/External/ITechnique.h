#ifndef _ITECHNIQUE_H
#define _ITECHNIQUE_H

#include "xrTypes.h"
#include "IResource.h"

class IPass;
class ITechnique : virtual public IResource
{
public:
	virtual Void CreatePass(IPass** pp) = 0;
	
};

#endif