#include "CDVRModel.h"

CDVRModel::CDVRModel()
{
    memset(&m_dvrModel,0,sizeof(DVR_MODEL));
}


CDVRModel::~CDVRModel()
{

}

int CDVRModel::update(DVR_GUI_LAYOUT_INST_EXT* dvrData)
{
    if(!dvrData->pTable) return 0;
    if(dvrData->ObjNum == 0) return 0;
    if(dvrData->curLayout >= GUI_LAYOUT_NUM_EXT) return 0;
    for(int i = 0; i < dvrData->ObjNum; i ++)
    {
        if(dvrData->curLayout == GUI_LAYOUT_RECORD_EXT)
        {
            switch(dvrData->pTable[i].Id)
            {
              case GUI_OBJ_ID_REC_SWITCH_EXT:
                m_dvrModel.recModel.enable_status = dvrData->pTable[i].uStatus.ObjVal;
                break;
              case GUI_OBJ_ID_REC_STATE_EXT:
                m_dvrModel.recModel.dot_status = dvrData->pTable[i].uStatus.ObjVal;
                break;
              case GUI_OBJ_ID_REC_EVENT_RECORD_STATE_EXT:
                m_dvrModel.recModel.event_status = dvrData->pTable[i].bShow;
                break;
              case GUI_OBJ_ID_REC_VIEW_INDEX_EXT:
                m_dvrModel.recModel.view_index = dvrData->pTable[i].uStatus.ObjVal;
                break;
              case GUI_OBJ_ID_REC_VEHICLE_DATA_EXT:
                break;
              default:
                break;
            }
        }
        else if(dvrData->curLayout == GUI_LAYOUT_THUMB_EXT)
        {
            switch(dvrData->pTable[i].Id)
            {
              case GUI_OBJ_ID_THUMB_TAB_EXT:
                m_dvrModel.thumbModel.current_tab = dvrData->pTable[i].uStatus.ObjVal;
                break;
              case GUI_OBJ_ID_THUMB_EDIT_EXT:
                m_dvrModel.thumbModel.edit_status = dvrData->pTable[i].uStatus.ObjVal;
                break;
              case GUI_OBJ_ID_THUMB_EDIT_SEL_CHECKBOX_EXT:
                if(dvrData->pTable[i].uStatus.ptr)
                {
                    GUI_OBJ_THUMB_EDIT_INST_EXT* editInst = (GUI_OBJ_THUMB_EDIT_INST_EXT*)dvrData->pTable[i].uStatus.ptr;
                    for(int i = 0; i < NUM_THUMBNAIL_PER_PAGE_EXT; i ++)
                    {
                        m_dvrModel.thumbModel.selecet_status[i] = editInst->check_box[i] & dvrData->pTable[i].bShow;
                    }
                }
                break;
              case GUI_OBJ_ID_THUMB_FRAME_EXT:
                break;
              case GUI_OBJ_ID_THUMB_CAPACITY_EXT:
                break;
              case GUI_OBJ_ID_THUMB_PAGE_NUM_EXT:
                if(dvrData->pTable[i].uStatus.ptr)
                {
                    GUI_OBJ_THUMB_PAGENUM_INST_EXT* thumbPagenumInst = (GUI_OBJ_THUMB_PAGENUM_INST_EXT*)dvrData->pTable[i].uStatus.ptr;
                    m_dvrModel.thumbModel.current_page = thumbPagenumInst->nCurPage;
                    m_dvrModel.thumbModel.total_page = thumbPagenumInst->nTotalPage;
                    
                }
                break;
              default:
                break;
            }        
        }
        else if(dvrData->curLayout == GUI_LAYOUT_PLAYBACK_VIDEO_EXT)
        {
            switch(dvrData->pTable[i].Id)
            {
              case GUI_OBJ_ID_PB_PLAY_STATE_EXT:
                break;
              case GUI_OBJ_ID_PB_PLAY_TIMER_EXT:
                break;
              case GUI_OBJ_ID_PB_PLAY_SPEED_EXT:
                break;
              case GUI_OBJ_ID_PB_FILENAME_EXT:
                break;
              case GUI_OBJ_ID_PB_VIEW_INDEX_EXT:
                break;
              case GUI_OBJ_ID_PB_DC_SWITCH_EXT:
                break;
              case GUI_OBJ_ID_PB_MODE_EXT:
                break;
              case GUI_OBJ_ID_PB_VEHICLE_DATA_EXT:
                break;
              default:
                break;
            }        
        }
        else if(dvrData->curLayout == GUI_LAYOUT_PLAYBACK_IMAGE_EXT)
        {
            switch(dvrData->pTable[i].Id)
            {
              case GUI_OBJ_ID_PB_VIEW_INDEX_EXT:
                break;
              default:
                break;
            }

        }
        else if(dvrData->curLayout == GUI_LAYOUT_SETUP_EXT)
        {
            switch(dvrData->pTable[i].Id)
            {
              case GUI_OBJ_ID_SETUP_SPLIT_TIME_EXT:
                break;
              case GUI_OBJ_ID_SETUP_VIDEO_QUALITY_EXT:
                break;
              case GUI_OBJ_ID_SETUP_PHOTO_QUALITY_EXT:
                break;
              case GUI_OBJ_ID_SETUP_FORMAT_CARD_EXT:
                break;
              default:
                break;
            }
        }
        else
        {}
    }    
    return 1;
}

int CDVRModel::reset()
{
    memset(&m_dvrModel,0,sizeof(DVR_MODEL));
    return 1;
}



