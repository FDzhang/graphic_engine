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
#include "IF_Algo.h"

namespace GUI
{
    class AlgoLayout : public ILayout , public IAlgoLayout
    {
        AlgoLayout();
        ~AlgoLayout();
    public:
        static IAlgoLayout* GetLayout();
        static void  SetAvmEventType(AvmEventType type) { m_event_type = type; }
    public:
        void Init() {};
        void Enable(bool flag) ;
    protected:
        AvmEventType GetAttachEventType() {return m_event_type; }
    private:
        uint32_t m_element_size;
        static struct ElementFuntionTable m_element_info[];
    private:
        void InitAlgoExit(IGUIElement* , const GUI_HANDLE_T);
        void OnEventExit(IGUIElement* play_button);
        void InitAlgoLdw(IGUIElement* , const GUI_HANDLE_T);
        void OnEventLdw(IGUIElement* play_button);
        void InitAlgoBsd(IGUIElement* , const GUI_HANDLE_T);
        void OnEventBsd(IGUIElement* play_button);
        void InitAlgoOnline(IGUIElement* , const GUI_HANDLE_T);
        void OnEventOnline(IGUIElement* play_button);
        void InitAlgoApa(IGUIElement* , const GUI_HANDLE_T);
        void OnEventApa(IGUIElement* play_button);
    private:
        static AlgoLayout* m_layout;
        static AvmEventType    m_event_type;
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
