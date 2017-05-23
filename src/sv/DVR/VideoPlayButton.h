#ifndef VIDEOPLAYBUTTON_H /* { */
#define VIDEOPLAYBUTTON_H
/*------------------------------------------------------------------------------------------*\
 * FILE: VideoPlayButton.h
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
 * VERSION: 11 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "CVideoButton.h"

/** 创建video play button*/
class VideoPlayButton : public CVideoButton
{
public:
    VideoPlayButton()
        :CVideoButton("play")
    {
    }
    ~VideoPlayButton() {}
    void InitNode(ILayoutNode* node)
    {
        CVideoButton::InitNode(node);
        Init(1100, 500, 120, 120, 1, XR_RES_DVR"DVR_play.dds", XR_RES_DVR"DVR_pause.dds");
    }
protected:
    Void OnPress(Int32 id) { DEBUG("button id is %d\n",id);}
    Void OnRelease(Int32 id, Boolean isIn) { DEBUG("button id is %d\n",id);}
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } VIDEOPLAYBUTTON_H */
