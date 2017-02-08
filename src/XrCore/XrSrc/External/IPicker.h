#ifndef _IPICKER_H
#define _IPICKER_H

#include "xrIntrinsic.h"

typedef Void (*PICKPROCESSFUNC)(class IModel*,Int32 x,Int32 y);
typedef Void (*UIPICKPROCESSFUNC)(class ILayer*,Int32 x,Int32 y);
class IRenderNode;
class IPicker
{
public:
	virtual Void Attach(IRenderNode* pNode) = 0;
	virtual Void Detach(IRenderNode* pNode) = 0;
	virtual Void AddResponse(UInt32 response,PICKPROCESSFUNC func) = 0;
	//virtual Void AddResponse(UInt32 response,UIPICKPROCESSFUNC func) = 0;
	virtual Void SendEventToAttachNode(Boolean) = 0;

};




#endif