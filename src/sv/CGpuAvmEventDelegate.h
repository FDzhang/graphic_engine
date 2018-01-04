#ifndef CGpuAvmEvent_h
#define CGpuAvmEvent_h

#include <stdio.h>
#include "event/RawAvmEvent.h"
#include "event/ofilm_msg_type.h"
#include "event/AvmEventTypes.h"
#include "log/LogHelper.hpp"
#include "log/log.h"
#include "utils/utils.h"
#include "global/config.h"
#include "GpuAvmEvent.h"
#include "IF_Algo.h"

//前置申明
class AvmEvent;

/*
 * \brief 
 */
class CGpuAvmEventDelegate
{

public:
    CGpuAvmEventDelegate(const char* className);
	
	CGpuAvmEventDelegate(AvmEventType eventType);
	
    virtual ~CGpuAvmEventDelegate();

    /*
     * \brief 请求AvmEvent,分配event 对象，用于数据填充
     */
    AvmEvent* RequestEvent(Layout_Event_Payload_T** payload);
    /*
     * \brief 请求post 指定数据
     */
    bool PostEvent(AvmEvent* avm_event);
    
    /*
     * \brief 函数内部已完成event 请求，可直接post 指定数据
     */
    bool PostEventPayload(Layout_Event_Payload_T* payload);

	bool PostEventPayload(void* payload, uint32_t payloadSize);

private:
    /*
     * \brief 绑定AvmEvent
     */
    bool RegisterAvmEvent(const char* eventName);
    
private:
    AvmEventType m_eventType; //AvmEvent事件类型id
    const char* m_className;  //Layout className
    unsigned char m_registType;
};


#endif /* CGpuAvmEvent_hpp */
