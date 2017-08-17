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
#include "GpuElementPanel.h"
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

    private:
        
        void InitAlgoLdw(IGUIElement* , const GUI_HANDLE_T);
        void OnEventLdw(IGUIElement*);
        void InitAlgoBsd(IGUIElement* , const GUI_HANDLE_T);
        void OnEventBsd(IGUIElement* );
        void InitAlgoOnline(IGUIElement* , const GUI_HANDLE_T);
        void OnEventOnline(IGUIElement*);
        void InitAlgoApa(IGUIElement* , const GUI_HANDLE_T);
        void OnEventApa(IGUIElement*);

        void InitAlgoPanel(IGUIElement*, const GUI_HANDLE_T);
        void InitAlgoMedia(IGUIElement*, const GUI_HANDLE_T);
        void OnEventMedia(IGUIElement*);
        void InitAlgoMediaPanel(IGUIElement*, const GUI_HANDLE_T);
        void InitAlgoMediaPlayback(IGUIElement* , const GUI_HANDLE_T);
        void OnEventMediaPlayback(IGUIElement*);
        void InitAlgoMediaRecord(IGUIElement*, const GUI_HANDLE_T);
        void OnEventMediaRecord(IGUIElement*);
        void InitAlgoFCW(IGUIElement*, const GUI_HANDLE_T);
        void OnEventFCW(IGUIElement*);
        void InitAlgoApaIn(IGUIElement*, const GUI_HANDLE_T);
        void OnEventApaIn(IGUIElement*);
        void InitAlgoApaOut(IGUIElement*, const GUI_HANDLE_T);
        void OnEventApaOut(IGUIElement*);
    private:
        CGPUButton *m_record_button, *m_playback_button,
            *m_ldw_button, *m_bsd_button, *m_online_button, *m_apa_button, *m_media_button, *m_fcw_button, *m_apaIn_button, *m_apaOut_button;
        CGPUPanel *m_media_panel;
    private:
        uint32_t m_element_size;
        static struct ElementFuntionTable m_element_info[];
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
