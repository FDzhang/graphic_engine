#ifndef _BEV_DATA_TYPE_H_
#define _BEV_DATA_TYPE_H_
#ifndef _MSC_VER
#define _MSC_VER 1
#endif 


//#include "../../../source/utility/AVM/avm_mc.h"

#include "stdlib.h"
#include "math.h"
#include "stdio.h"
//#include "../../../source/utility/basic_tools/CvLog.h"
#include "reuse.h"
#include "smc.h"
//#include "..\utility\common\commondef.h"

#ifndef ABS
#define ABS(x) ((x) >= 0 ? (x):-(x))
#endif

#ifndef MAX
#define MAX(x, y) ((x) >= (y)? (x):(y))
#define MIN(x, y) ((x) > (y)?(y):(x))
#endif

typedef struct{
	int _flag_rt ;
	float _pose_front[6] ; 
	float _pose_rear[6] ;
	float _pose_left[6] ;
	float _pose_right[6] ;

	int _flag_hm ;
	float _hm_front[9] ;
	float _hm_rear[9] ;
	float _hm_left[9] ;
	float _hm_right[9] ;

} str_avm_pose_t_data ; 

typedef struct _dat_calib_header
{
	int Flag;                           //0xffffffff INVALID else VALID
	Veh_Param_T veh_param;		//vehicle related parameters
	Camera_Param_Cam_Int_T	  cam_param[4];	//camera intrinsic parameters
	str_avm_pose_t_data	  cam_pose;		//camera pose parameters
}Dat_Calib_Header_T;

#endif
