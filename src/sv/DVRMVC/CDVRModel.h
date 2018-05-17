#ifndef _CDVR_MODEL_H_
#define _CDVR_MODEL_H_

#include "Gpu_Dvr_Interface.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <math.h>

#include <cstring>

using std::memcpy;
using std::memset;
using std::malloc;
using std::free;
using std::printf;

#define MAX_THUMB_NUM 20

typedef struct
{
    unsigned char current_layout;
}DVR_MODEL_BASE;

typedef struct
{
    unsigned char dot_status;
    unsigned char enable_status;
    unsigned char shoot_status;
    unsigned char event_status;
    unsigned char view_index;
}DVR_MODEL_REC;

typedef struct
{
    unsigned char view_index;
    unsigned char dot_status;
    unsigned char play_status;
    unsigned char pre_status;
    unsigned char next_status;
    unsigned char shoot_status;
    unsigned char current_time;
    unsigned char duration_time;
    char* filename;
    float play_process;
}DVR_MODEL_PB;

typedef struct
{
    unsigned char current_tab;
    unsigned char edit_status;
    unsigned char selecet_status[MAX_THUMB_NUM];
    unsigned char list_line;
    unsigned char list_row;
    unsigned char image_enable[MAX_THUMB_NUM];
    void* imagebuff[MAX_THUMB_NUM];
    char* filename[MAX_THUMB_NUM];
    unsigned char current_page;
    unsigned char total_page;
    char* page_char;
}DVR_MODEL_THUMB;

typedef struct
{
    DVR_MODEL_BASE baseModel;
    DVR_MODEL_REC recModel;
    DVR_MODEL_PB pbModel;
    DVR_MODEL_THUMB thumbModel;
}DVR_MODEL;

class CDVRModel
{
  public:
    CDVRModel();
    ~CDVRModel();
    int update(DVR_GUI_LAYOUT_INST_EXT* ptr);
    int reset();

  private:
    DVR_MODEL m_dvrModel;
};

#endif
