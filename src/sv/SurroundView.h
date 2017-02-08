
#ifndef XR_SV_H_
#define XR_SV_H_


/**
 * This demo goes through 3 demonstration clips and then enters interactive mode.
 * Operations: drag to rotate camera, double click to switch scene
 *
 **/
#include "../XrCore/XrSrc/External/XrHeaders.h"
#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "AVMData.h"
class SVAdjust;
class XRSV
{
public:

	XRSV() {
	}

	virtual ~XRSV() {m_pAdasMdl = NULL;};

	bool init(int width, int height, Smc_Cal_T *pSmcCfg,str_avm_pose_t * pPose);
	bool draw();
	bool update(unsigned int view_control_flag);
	void SingleTouchDown(int x, int y);
	void SingleTouchMove(int x, int y);
	void SingleTouchUp(int x, int y);
	void DoubleTouchDown(int x, int y);
	void DoubleTouchMove(int x, int y);
	void DoubleTouchUp(int x, int y);
	//<<<<<<< HEAD
	void Update3DParam(float *pose);
	void Update2DParam(void *pdata,void *pIndex);

	//=======
	void RightTouchUp(int x, int y);
	void RightTouchDown(int x, int y);
	void KeyDown(int x);
	//>>>>>>> feature_autoparking
	void Pinch(float distance);
	
	void SwitchViewButton(int buttonid);
	bool initVehicleParam(SV_VEHICLE_PARAM_T in_veh_param);
    void initAdasMdlHmi(st_ADAS_Mdl_HMI_T **pAdasMdlHmiHandle,int HmiMdlNum);		
	int m_useHDR;

protected:

	void switchScene();

	int m_internalWidth;
	int m_internalHeight;
	int m_nodeId;

	int prevX;
	int prevY;
	int m_adjust_eanble;
	SVAdjust *m_adjust;
	SV_DATA_CONFIG_T m_sv_data_config;
	st_ADAS_Mdl_HMI_T **m_pAdasMdl;
	int m_adas_mdl_num;

};

#endif /* XR_SV_H_ */
