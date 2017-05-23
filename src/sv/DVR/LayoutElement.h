#ifndef CELEMENT_H /* { */
#define CELEMENT_H
/*------------------------------------------------------------------------------------------*\
 * FILE: CElement.h
 *==========================================================================================
 * Copyright 2017   O-Film Technologies, Inc., All Rights Reserved.
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
 * VERSION: 13 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "RuntimeClass.h"
#include "XrCore/XrSrc/External/IUINode.h"


typedef char*   TextureName;
typedef IUINode ILayoutNode;

class CLayoutElement : public CObject
{
    DECLARE_DYNAMIC(CLayoutElement)
public:
    CLayoutElement();
    virtual ~CLayoutElement();
    /**
     * \brief 为每个Node element 指定所属的LayoutNode (绘制layout)
     *
     * \param[in] node  Layout Node
     */
    void InitElementNode(ILayoutNode* node);
    /**
     * \brief 设置需要绘制的element的general属性
     * \param[in]  pos_x , pos_y  绘制element在layout的位置,UI设计者无需关系底层绘制环境的size
     * \param[in]  element_width ,element_height 绘制元素的size
     * \prram[in]  opacity 绘制元素透明度设置
     */
    virtual void InitElementSize(uint32_t pos_x, uint32_t pos_y,
                                 uint32_t element_width, uint32_t element_height,
                                 uint32_t opacity) = 0;
    /**
     * \brief 设置需要绘制的element的texture属性
     */
    virtual void InitElementTexture(const TextureName* array_texture) = 0;
    virtual bool CreateElement() = 0;
    /**
     * \brief invalid element effect
     */
    void InvalidElementEffect();
    /**
     * \brief valid element effect
     */
    void ValidElementEffect();
protected:
    const ILayoutNode* GetLayoutNode() const;
private:
    bool is_valid;
    ILayoutNode*  m_node;
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } CELEMENT_H */
