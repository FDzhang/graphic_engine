#ifndef _RuntimeClass_H_ /* { */
#define _RuntimeClass_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: RuntimeClass.h
 *==========================================================================================
 * Copyright 2017   O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION:序列化Layout xml文档中的GUI布局, 在进程中动态创建类对象
 *             功能: 运行时的动态类型检查(RTTI)能力和序列化能力, 后期结合UI designer开发工具可以灵活的解耦
 *             HMI设计与HMI控制逻辑的操作
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
 * VERSION: 13 5月 2017 dota2_black
 *------------------------------------------------------------------------------------------*/
#include <string>
#include <map>
#include "reuse.h"
#include "log/log.h"
#include "utils/utils.h"

/** 指定类声明动态类型特性*/
#define DECLEAR_DYNAMIC_BASE(CRuntimeClass) \
    public: \
    typedef CRuntimeClass* (*ClassGenerate)(); /** 声明函数指针*/ \
    static std::map<std::string, ClassGenerate>* m_class_set; /** 存储子类信息*/ \
    static CRuntimeClass* Create(const std::string& class_name) /**工厂函数*/ \
    { \
        std::map<std::string, ClassGenerate>::iterator iter = m_class_set->find(class_name); \
        if(m_class_set->end() != iter) \
        { \
            return ((*iter).second)();         \
        } \
        else                                    \
        { \
            ERROR("Please Register %s as a Runtimeclass\n", class_name.c_str()); \
        } \
        return NULL; \
    } \
    protected: \
    static void Register(const std::string& class_name, ClassGenerate class_generate) /** 注册函数*/ \
    { \
        if(!m_class_set) \
        {                                                            \
            m_class_set = new  std::map<std::string, ClassGenerate>; \
        } \
        m_class_set->insert(std::map<std::string, ClassGenerate>::value_type(class_name, class_generate)); \
    }

/** 实现指定类动态类型特性*/
#define IMPLEMENT_DYNAMIC_BASE(CRuntimeClass) \
    std::map<std::string, CRuntimeClass::ClassGenerate>* CRuntimeClass::m_class_set;


#define DECLEAR_DYNAMIC_CLASS(CRuntimeClassDerived, CRuntimeClass) \
    public: \
    struct CRuntimeClassDerived##Register /**辅助类, 用于注册*/ \
    { \
        CRuntimeClassDerived##Register() \
        { \
            static bool bRegistered = false; \
            if(!bRegistered) \
            {   \
                CRuntimeClass::Register(#CRuntimeClassDerived, CRuntimeClassDerived::Create); /**注册子类信息*/ \
                bRegistered = true;  \
            } \
        } \
    }; \
    static CRuntimeClass* Create() /**工厂函数*/ \
    { \
        return new CRuntimeClassDerived; \
    } \
    static struct CRuntimeClassDerived##Register m_t##CRuntimeClassDerived##Register;


#define IMPLEMENT_DYNAMIC_CLASS(CRuntimeClassDerived) \
    static struct CRuntimeClassDerived::CRuntimeClassDerived##Register m_t##CRuntimeClassDerived##Register;
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _RUNTIME_CLASS_ */
