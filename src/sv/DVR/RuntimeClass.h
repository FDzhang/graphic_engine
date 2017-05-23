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
#include <string.h>
#include "reuse.h"
#include "log/log.h"
#include "utils/utils.h"

struct CRuntimeClass;
/** 为指定类声明动态类型特性: 定义一个名为class+类名的CRuntimeClass对象并返回该对象地址的虚函数*/
#define DECLARE_DYNAMIC(class_name) \
    public: \
    /** 定义CRuntimeCalss成员变量*/ \
    static const struct CRuntimeClass class##class_name; \
    /** 获取CRuntimeClass变量的接口*/ \
    virtual CRuntimeClass* GetRuntimeClass() const;

/** 实现指定类动态类型特性*/
#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
    IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)
/** 完成对DECLARE_DYNAMIC宏声明的CRuntimeClass变量class##class_name的初始化,以及对GetRuntimeClass()函数的定义*/
#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
    const CRuntimeClass class_name::class##class_name = { \
        #class_name, sizeof(class class_name), wSchema, pfnNew, \
        RUNTIME_CLASS(base_class_name), NULL};  \
    CRuntimeClass* class_name::GetRuntimeClass() const \
    { return RUNTIME_CLASS(class_name);}
/** 对CRuntimeClass进行初始化，使之链接上存有类的信息链表*/
#define RUNTIME_CLASS(class_name) ((CRuntimeClass*)(&class_name::class##class_name))

/** CObject类声明*/
class CObject
{
public:
    CObject();
    virtual ~CObject();
    virtual struct CRuntimeClass* GetRuntimeClass()   const;
    bool IsKindOf(const struct CRuntimeClass* pClass) const;
    static struct CRuntimeClass classCObject;
};

/** 动态类型信息结构体*/
struct CRuntimeClass
{
    char*    m_className;    /** 保存类名称*/
    int      m_ObjectSize;   /** 保存类的实例数据所占内存的的大小*/
    unsigned int m_wSchema;  /** 分类编号(对不可分类的类, 该值为-1)*/
    CObject* (*m_pfnCreateObject)();/** 指向函数的指针,这个函数返回一个CObject  */
    CRuntimeClass* m_pBaseClass; /** 指向基类的运行时结构*/
    CRuntimeClass* m_pNextClass; /** 组成运行时结构链表*/
    //序列化支持 -- 备用,暂不实现
    //void Store(CArchive& ar) const;
    //static CRuntimeClass* Load(CArchive& ar, unsigned int pwSchemaNum);
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _RUNTIME_CLASS_ */
