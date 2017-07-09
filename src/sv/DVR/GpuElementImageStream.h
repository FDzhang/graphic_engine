#ifndef _GPUELEMENTIMAGESTREAM_H_ /* { */
#define _GPUELEMENTIMAGESTREAM_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: GpuElementImageStream.h
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
 * VERSION: 28 6月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "IGUIElement.h"
#include "XrCore/XrSrc/XrUILibrary/CXrBaseView.h"

namespace GUI
{
    /*
     * \brief 图片流控件，动态可变image控件
     */
    class CGPUImageStream : public IGUIElement , private CXrBaseView
    {
    public:
        CGPUImageStream();
        ~CGPUImageStream();

        bool Create(const uint32_t pos_x, const uint32_t pos_y,
                    const uint32_t element_width, const uint32_t element_height);
        void SetTexture(const IGUITexture* effect, const long style);
        //! 获取image raw data, 返回CGPUImageStream 控件创建纹理buf, 用于数据更新
        char* GetImageRawData(uint32_t* width, uint32_t* height);
        //! 更新完image_raw_data, 调用接口更新图片数据
        void  UpdateImage();
        void Enable(bool enable) {m_image_layer->SetEnable(enable);};
    private:
        //重载事件响应
        Boolean OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type);
    private:
        IGUITexture* m_thumbnail_texture;
        IMaterial* m_thumbnailMtl;
        char*      m_raw_image;      //image数据
        IDeviceManager* m_pIdm;
        ILayer* m_image_layer;
    private:
        DECLEAR_DYNAMIC_CLASS(CGPUImageStream, IGUIElement)
    };
};

/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _GPUELEMENTIMAGESTREAM_H_ */
