/*------------------------------------------------------------------------------------------
 * FILE: RuntimeClass.cpp
 *==========================================================================================
 * Copyright 2017  O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION:
 *
 * ABBREVIATIONS:
 *   TODO: List of abbreviations used, or reference(s) to external document(s)
 *
 * TRACEABILITY INFO:
 *   Design Document(s):
 *     TODO: Update list of design document(s)
 *
 *   Requirements Document(s):
 *     TODO: Update list of requirements document(s)
 *
 *   Applicable Standards (in order of precedence: highest first):
 *
 * DEVIATIONS FROM STANDARDS:
 *   TODO: List of deviations from standards in this file, or
 *   None.
 * VERSION: 14 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "RuntimeClass.h"

CObject::CObject()
{
    DEBUG("CObject Constructor.\n");
}
CObject::~CObject()
{
}
bool CObject::IsKindOf(const CRuntimeClass* pClass) const
{
    CRuntimeClass* pClassThis = GetRuntimeClass();
    //! 遍历CRuntimeClass链表节点
    while(pClassThis != NULL)
    {
        if(pClassThis == pClass)
        {
            Log_Debug("%s is %s\n", GetRuntimeClass()->m_className, pClass->m_className);
            return true;
        }
        pClassThis = pClassThis->m_pBaseClass;
    }
    DEBUG("%s is not %s\n", GetRuntimeClass()->m_className, pClass->m_className);
    return false;
}

struct CRuntimeClass CObject::classCObject={
    "COBject",sizeof(CObject),0xFFFF,NULL,NULL,NULL
};
CRuntimeClass* CObject::GetRuntimeClass() const
{
	return &CObject::classCObject;
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
