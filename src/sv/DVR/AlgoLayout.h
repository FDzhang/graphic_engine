#ifndef _ALGO_LAYOUT_H_ /* { */
#define _ALGO_LAYOUT_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: Algo_Layout.h
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
 * VERSION: 21 6月 2017 dota2_black
 *------------------------------------------------------------------------------------------*/
#include "Layout.h"
#include "GpuElementButton.h"
#include "GpuElementImageStream.h"
#include "IF_Algo.h"

namespace GUI
{
    class AlgoLayout : public ILayout, public IAlgoLayout
    {
        AlgoLayout();
        ~AlgoLayout();
    public:
        static IAlgoLayout* GetLayout();
    public:
        void Init() {};
        void Enable(bool flag) ;
        void EnableApaImageStream(bool flag);
        char* GetApaImageStream(uint32_t* width, uint32_t* height);
        void Sync();
    private:
        uint32_t m_element_size;
        static struct ElementFuntionTable m_element_info[];
    private:
        void InitAlgoExit(IGUIElement* , const GUI_HANDLE_T);
        void OnEventExit(IGUIElement*);
        void InitAlgoLdw(IGUIElement* , const GUI_HANDLE_T);
        void OnEventLdw(IGUIElement*);
        void InitAlgoBsd(IGUIElement* , const GUI_HANDLE_T);
        void OnEventBsd(IGUIElement* );
        void InitAlgoOnline(IGUIElement* , const GUI_HANDLE_T);
        void OnEventOnline(IGUIElement*);
        void InitAlgoApa(IGUIElement* , const GUI_HANDLE_T);
        void OnEventApa(IGUIElement*);
        void InitAlgoRecord(IGUIElement*, const GUI_HANDLE_T);
        void OnEventRecord(IGUIElement*);
        void InitAlgoWifi(IGUIElement*, const GUI_HANDLE_T);
        void OnEventWifi(IGUIElement*, const GUI_HANDLE_T);
        void InitAlgoApaImage(IGUIElement* algoApa_image, const GUI_HANDLE_T parentId);
        void OnEventImage(IGUIElement*);

    private:
        CGPUImageStream* m_algoApaImageStream;
    private:
        static AlgoLayout* m_layout;
    };
};

/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _ALGO_LAYOUT_H_ */
