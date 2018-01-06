#include "../XrCore/XrSrc/External/IXrCore.h"
#include "event/AvmEvent.h"
#include "CGpuAvmEventDelegate.h"
#include "gpu_log.h"

CGpuAvmEventDelegate::CGpuAvmEventDelegate(const char* className):m_className(className)
{
	Log_Error("-----------CGpuAvmEventDelegate::CGpuAvmEventDelegate");
    //初始化注册AvmEvent
    if(!RegisterAvmEvent(m_className))
    {
        Log_Error("AvmEvent register failed");
		Log_Error("m_className: %s", m_className);
    }
	m_registType = 0;
}
CGpuAvmEventDelegate::CGpuAvmEventDelegate(AvmEventType eventType)
{
	m_eventType = eventType;

	if (AvmRequestEvent(m_eventType) == NULL)
	{
		Log_Error("Request %d cmd event error!", __func__, eventType);
		m_eventType = AvmEvent::Invalid_Event_Type;
	}
	m_registType = 1;

}

CGpuAvmEventDelegate::~CGpuAvmEventDelegate()
{
	if(m_registType == 0)
    {
    	delete m_className;
	}
}

bool CGpuAvmEventDelegate::RegisterAvmEvent(const char* eventName)
{
    if(eventName == NULL)
    {
        return false;
    }
    //注册事件
    if(AvmGetEventTypeByName(eventName) != AvmEvent::Invalid_Event_Type)
	{
		m_eventType = AvmGetEventTypeByName(eventName);
		
		return true;
	}
	
    m_eventType = AvmRegisterEvent(eventName, sizeof(Layout_Event_Payload_T));
    if(m_eventType == AvmEvent::Invalid_Event_Type)
    {
        Log_Error("%s:Attention: Invalid Event type by %s, please check the exist", __func__, eventName);
        return false;
    }
    
    return true;
}

AvmEvent* CGpuAvmEventDelegate::RequestEvent(Layout_Event_Payload_T** payload)
{
    if(m_eventType == AvmEvent::Invalid_Event_Type)
    {
        Log_Error("%s: a wrong avm event type id", __func__);
        return NULL;
    }
    
    AvmEvent* avm_event = AvmRequestEvent(m_eventType);
    
    RawAvmEvent* raw_event = avm_event->GetRawEvent();
    
    *payload = (Layout_Event_Payload_T*)(raw_event->payload);
    
    return avm_event;
}

bool CGpuAvmEventDelegate::PostEvent(AvmEvent* avm_event)
{
    if(avm_event != NULL)
    {
        AvmPostEvent(*avm_event, NULL);
        AvmEventReleaseAndTrace(*avm_event);
        return true;
    }
    else
    {
        Log_Error("%s: please make sure the avm_event is valid", __func__);
        return false;
    }
    
    return true;
}
bool CGpuAvmEventDelegate::PostEventPayload(Layout_Event_Payload_T* payload)
{
    if(payload == NULL)
    {
        Log_Error("%s: the event payload is null!", __func__);
        return false;
    }
    else
    {
        if(m_eventType == AvmEvent::Invalid_Event_Type)
        {
            Log_Error("%s: a wrong avm event type id", __func__);
            return false;
        }
        
        AvmEvent* avm_event = AvmRequestEvent(m_eventType);
        
        if(avm_event == NULL)
        {
            Log_Error("%s: the avm event requested is failed", __func__);
            return false;
        }
        
        RawAvmEvent* raw_event = avm_event->GetRawEvent();
        
        if(raw_event->payload)
        {
            memcpy((Layout_Event_Payload_T*)raw_event->payload, payload, sizeof(Layout_Event_Payload_T));
        }
        else
        {
            Log_Error("%s: the event payload got is null!", __func__);
            return false;
        }
        
        AvmPostEvent(*avm_event, NULL);
        AvmEventReleaseAndTrace(*avm_event);
    }
    return true;
}
bool CGpuAvmEventDelegate::PostEventPayload(void* payload, uint32_t payloadSize)
{
    if(payload == NULL)
    {
        Log_Error("%s: the event payload is null!", __func__);
        return false;
    }
    else
    {
        if(m_eventType == AvmEvent::Invalid_Event_Type)
        {
            Log_Error("%s: a wrong avm event type id", __func__);
            return false;
        }
        
        AvmEvent* avm_event = AvmRequestEvent(m_eventType);
        
        if(avm_event == NULL)
        {
            Log_Error("%s: the avm event requested is failed", __func__);
            return false;
        }
        
        RawAvmEvent* raw_event = avm_event->GetRawEvent();
        
        if(raw_event->payload)
        {
            memcpy(raw_event->payload, payload, payloadSize);
        }
        else
        {
            Log_Error("%s: the event payload got is null!", __func__);
            return false;
        }
        
        AvmPostEvent(*avm_event, NULL);
        AvmEventReleaseAndTrace(*avm_event);
    }
    return true;
}

/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================
 
 *------------------------------------------------------------------------------------------*/
