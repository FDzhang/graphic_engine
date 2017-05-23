/*------------------------------------------------------------------------------------------
 * FILE: LayoutElement.cpp
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
 * VERSION: 13 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "LayoutElement.h"

IMPLEMENT_DYNAMIC(CLayoutElement, CObject)
CLayoutElement::CLayoutElement()
    :CObject()
{
    
}

CLayoutElement::~CLayoutElement()
{
}

void CLayoutElement::InitElementNode(ILayoutNode* node)
{
     m_node = node;
}
void CLayoutElement::InvalidElementEffect()
{
    is_valid = false;
}

void CLayoutElement::ValidElementEffect()
{
    is_valid = true;
}

const ILayoutNode* CLayoutElement::GetLayoutNode() const
{
    return CLayoutElement::m_node;
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
