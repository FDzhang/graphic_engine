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
    switch(dvrData->curLayout)
    {
      case GUI_LAYOUT_RECORD_EXT:
        for(int i = 0; i < dvrData->ObjNum; i ++)
        {
        }
        break;
      case GUI_LAYOUT_THUMB_EXT:
        break;
      case GUI_LAYOUT_PLAYBACK_VIDEO_EXT:
        break;
      case GUI_LAYOUT_PLAYBACK_IMAGE_EXT:
        break;
      case GUI_LAYOUT_SETUP_EXT:
        break;
      default:
        break;
    }
    return 1;
}

int CDVRModel::reset()
{
    memset(&m_dvrModel,0,sizeof(DVR_MODEL));
    return 1;
}



