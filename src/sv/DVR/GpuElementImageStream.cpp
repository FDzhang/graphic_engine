/*------------------------------------------------------------------------------------------
 * FILE: GpuElementImageStream.cpp
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
 * VERSION: 28 6月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "GpuElementImageStream.h"

namespace GUI
{
    CGPUImageStream::CGPUImageStream()
        :IGUIElement("CGPUImageStream")
        ,CXrBaseView()
        ,m_thumbnail_texture(NULL)
        ,m_thumbnailMtl(NULL)
        ,m_raw_image(NULL)
    {
    }

    CGPUImageStream::~CGPUImageStream()
    {
        if(m_raw_image != NULL)
        {
            free(m_raw_image);
        }
    }
    
    bool CGPUImageStream::Create(const uint32_t pos_x, const uint32_t pos_y,
                                 const uint32_t element_width, uint32_t element_height)
    {
        const IGUINode* node = GetLayoutNode();
        if(node)
        {
            InsertFlag flag = InsertFlag_Child;
            int32_t parent = GetParent();
            if(parent < 0)
            {
                //控件不存在父节点id
                parent = -1;
                flag = InsertFlag_Default;
                Log_Error("---------------------------------------------------------------------\n");
            }
            
            if(m_raw_image != NULL)
            {
                //从文件中载入缩略图背景图
                IXrCore* core = GetXrCoreInterface();
                core->GetDeviceManager(&m_pIdm);            
                Int32 texId = m_pIdm->CreateTexture(m_raw_image,
                                                    m_thumbnail_texture->element_width,
                                                    m_thumbnail_texture->element_height,
                                                    XR_R8G8B8,
                                                    XR_SAMPLER_CLAMP | XR_SAMPLER_LINEAR, 1);

                Int32 mtlId = node->CreateMaterial(Material_UI_Spirit, &m_thumbnailMtl);
                m_thumbnailMtl->SetDiffuseMap(texId);
                Int32 thumbnailId = node->CreateSpirit(parent, flag,
                                                       mtlId, 1.0,
                                                       m_thumbnail_texture->pos_x,
                                                       m_thumbnail_texture->pos_y,
                                                       0,
                                                       m_thumbnail_texture->element_width,
                                                       m_thumbnail_texture->element_height);
                ILayer* layer = node->GetLayer(thumbnailId);
                layer->SetEventResponder(this);
            }
            else
            {
                Log_Error("------------Alloc raw image buf failed---------------------\n");
            }
        }
    }
    
    void CGPUImageStream::SetTexture(const IGUITexture* effect, const long style)
    {
        m_thumbnail_texture = &(((IGUITexture*)effect)[0]);
        m_raw_image = (char*)malloc(m_thumbnail_texture->element_width * m_thumbnail_texture->element_height * 3);
    }

    char* CGPUImageStream::GetImageRawData(uint32_t* width, uint32_t* height)
    {
        *width =  m_thumbnail_texture->element_width;
        *height = m_thumbnail_texture->element_height;
        return m_raw_image;
    }
    
    void  CGPUImageStream::UpdateImage()
    {
        glBindTexture(GL_TEXTURE_2D,  m_thumbnailMtl->GetDiffuseMap()->texid);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
                        m_thumbnail_texture->element_width,
                        m_thumbnail_texture->element_height, GL_RGB, GL_UNSIGNED_BYTE, m_raw_image);
    }
    Boolean CGPUImageStream::OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type)
    {
        
    }
    IMPLEMENT_DYNAMIC_CLASS(CGPUImageStream)
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
