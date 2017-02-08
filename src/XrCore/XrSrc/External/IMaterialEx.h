#ifndef _IMATERIALEX_H
#define _IMATERIALEX_H

#include "IMaterial.h"

class ITechnique;
class IMaterialEx : virtual public IMaterial
{
public:
	virtual Void CreateTechnique(const String& strName,ITechnique** pp) = 0;
	virtual Void SetCurrentTechnique(const String& strName) = 0;
	
};

#endif