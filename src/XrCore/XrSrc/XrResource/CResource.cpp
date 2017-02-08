#include "CResource.h"


Void CResource::Release()
{
	Int32 refcnt = DecRef();
	if (refcnt == 0) {
		delete this;
    }
}