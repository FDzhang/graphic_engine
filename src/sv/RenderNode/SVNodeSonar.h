#ifndef __SV_NODE_SONAR_H__
#define __SV_NODE_SONAR_H__

//#include "fileloader.h"
#include "sv/DataStruct.h"
#include "XrCore/XrSrc/External/XrHeaders.h"

#include "XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "sv/vehicle_motion_model.h"
#define MAX_SONAR_OBJ_NUM 150
#define SONAR_PI   3.1415926
#define EMPTY_POINT_DEFAULT_DIST  8000
#define VIEW_RANGE_BOTTOM  -10000
#define INVALID_OBJ_DIST  0x7FFF
#define DEFAULT_PARALLEL_LOT_WIDTH  1500
#define DEFAULT_VERTICAL_LOT_WIDTH  6000
#define JUMP_POINT_TOP_EDGE     1
#define JUMP_POINT_TOP_EDGE_MAYBE     3
#define JUMP_POINT_BOTTOM_EDGE_MAYBE     4
#define JUMP_POINT_BOTTOM_EDGE  2
#define JUMP_POINT_NON 0
#define JUMP_POINT_IGNORE 5
#define NO_POINT 3
#define K_SLOP_GATE    1

#define FINAL_PARKING_LOT_PARALLEL_LENGTH  5300
#define FINAL_PARKING_LOT_PARALLEL_WIDTH   2100
#define FINAL_PARKING_LOT_VERTICAL_LEGNTH  4000
#define FINAL_PARKING_LOT_VERTICAL_WIDTH   1800
#define SEACHING_SLOT_STEERING_GATE  180
#define MIN_VEHICLE_WIDTH 1650
#define SINGLE_EDGE_PARKING_LOT_LENGTH  7000

#define PARKING_LOT_PARALLEL  0
#define PARKING_LOT_VERTICAL  1
#define PARKING_LOT_NOT_SIUTABLE 2

#define SONAR_INDEX_FRONT_CLOCKWISE       0
#define SONAR_INDEX_FRONT_ANTI_CLOCKWISE  1
#define SONAR_INDEX_REAR_CLOCKWISE        2
#define SONAR_INDEX_REAR_ANTI_CLOCKWISE   3
typedef struct Sonar_Pos_T
{
    float pos[3];
	float angle;

}Sonar_Pos;

enum
{
	SONAR_NO_PARKING_LOT = 0,
	SONAR_PARKING_LOT_PARALLEL,
	SONAR_PARKING_LOT_VERTICAL,
	SONAR_PARKING_LOT_UNKNOWN_START_POINT,
	SONAR_PARKING_LOT_UNKNOWN_END_POINT,
};

enum
{
    EDGE_TYPE_NO_TOP_BOTTOM=0,
	EDGE_TYPE_TOP_TURN,
	EDGE_TYPE_TOP_NO_BOTTOM,
	EDGE_TYPE_BOTTOM_TURN,
	EDGE_TYPE_TOP_BOTTOM,
	EDGE_TYPE_NO_TOP_BOTTOM_TURN,
};
enum
{
	POINT_TYPE_LINE=0,
	POINT_TYPE_WAVE,
	POINT_TYPE_CONOR_TOP_RIGHT,  //--
    POINT_TYPE_CONOR_TOP_LEFT,
    POINT_TYPE_CONOR_BOTTOM_LEFT,
    POINT_TYPE_CONOR_BOTTOM_RIGHT,
	POINT_TYPE_LINE_DISAPPEAR,
	POINT_TYPE_LINE_APPEAR,
};

typedef enum park_lot_property
{
    park_lot_dist_cross=0,
	park_lot_dist_width,
	park_lot_top_before_turn_id,
	park_lot_top_after_turn_id,
	park_lot_bottom_before_turn_id,
	park_lot_bottom_after_turn_id,
	park_lot_width,
	park_lot_length,
	park_lot_drive_dist,
	park_lot_dist_cross_avg,
	park_lot_dist_width_avg,

}park_lot_property;
enum rect_point_index
{
    rect_point_near_top,
	rect_point_far_top,
	rect_point_near_bottom,
	rect_point_far_bottom,

};
		
/**************************************************************************
conor_top_right    conor_top_left   conor_bottom_left   conor_bottom_right

    ____               ____ 
        |             |                 |                       |
        |             |                 |____                ___|
        
***************************************************************************/

typedef struct st_lot_data_Tag
{
    float top_edge_point[2];
	float bottom_edge_point[2];
	int top_edge_index;
	int top_edge_after_turn_index;
	int bottom_edge_index;
	int bottom_edge_after_turn_index;
	int top_edge_flag;
	int bottom_edge_flag;
	float dist_cross;
	float dist_width;
	float drive_dist;
	float park_lot_width;
	float park_lot_length;
	int park_lot_flag;
}st_lot_data_T;

typedef struct st_sonar_parking_lot_Tag
{
    unsigned char parking_lot_type; //parallel or vertical or not siutable for parking
	float lot_start_pos[2];  //start is near to the head  of vehicle
	float lot_end_pos[2];
	float lot_width;
	float lot_length;
	float lot_point[8];
	bool show_flag;
}sonar_parking_lot_t;
#if 0
typedef enum sonar_index
{
    front_left_side_sonar=0,		
	front_left_conor_sonar,
	front_left_middle_sonar,
	front_right_middle_sonar,
	front_right_conor_sonar,	
	front_right_side_sonar,
	rear_left_side_sonar,
	rear_left_conor_sonar,
	rear_left_middle_sonar,
    rear_right_middle_sonar,
    rear_right_conor_sonar,	
	rear_right_side_sonar,
    max_sonar_num,
}sonar_index;
#endif
#define PARKING_LOT_TWIST_THRESHOLD  2000
#define PARKING_LOT_VERTICAL_THRESHOLD_LOW  2000
#define PARKING_LOT_VERTICAL_THRESHOLD_HIGH  4000
#define PARKING_LOT_PARALLEL_THRESHOLD_LOW   5000
#define PARKING_LOT_PARALLEL_THRESHOLD_HIGH  20000
#define PARKING_LOT_PARALLEL_WIDTH_THRES     1800
#define PARKING_LOT_JUMP_WIDTH_THRES  400
#define MAX_PARKING_LOT_NUM max_sonar_num
#define JUMP_POINT_DIST_GATE 200
#define FILTER_DIST_THRESHOLD  1000
#define FILTER_CNT_THERESHOLD  2
#define EMPTY_PATH_CNT_THRESHOLD 1
#define EMPTY_PATH_DIST_THERESHOLD 200
#define CURRENT_POINT_INDEX   0 
#define LAST_POINT_INDEX      1
#define LEFT_SONAR_MEAN_OBJ_INDEX   0
#define RIGHT_SONAR_MEAN_OBJ_INDEX  1

#define SONAR_HALF_FOV 50.0
#define CACHE_NUM  2
#define VEHICLE_STATE_BUFFER_NUM 5
enum
{
	JUMP_POINT,
	JUMP_POINT_NOT_SURE,
	JUMP_POINT_NONE,


};

typedef enum slot_searching_state
{
    slot_searching_not_start=0,		
	slot_searching_find_both_point,
	slot_searching_find_first_point,
	slot_searching_finish,
}slot_searching_state;


typedef struct st_sonar_line_data_Tag
{	
	Float32 *pdatabuffer;
	unsigned int data_size;
    int element_num;
	INode *pNode;
	IMesh *pLineMesh;
	unsigned char Color[3];	
	IMaterial *pLineMtl;
	char show_flag;
}st_sonar_line_data_T;
typedef struct st_stich_rect_data_slot_Tag
{	
	Float32 *pdatabuffer;
	unsigned int data_size;
    int element_num;
	INode *pNode;
	IMaterial *pRectMtl;
	IMesh *pRectMesh;
}st_stich_rect_data_slot_T;

typedef struct st_jump_point_Tag
{
    float f_point_before_jump[6];
	float f_point_after_jump[6];

	unsigned char jump_pint_type;
	int before_jump_point_num;
	int after_jump_point_num;
	
}st_jump_point_T;


class SVNodeSonar 
{
public:
	SVNodeSonar();

	int Init(BEV_CONFIG_T *pConfig,ISceneNode *pStichNode);
	int Update(float steering_wheel_angle,float vehicle_speed,float left_wheel_speed,float right_wheel_speed,unsigned char gear_state,int time_offset,float yaw_rate,float *obj_dist);
	int UpdateVertexBuffer(float*pVertex,int index);
	int  ProcessPreviousPos(COMMON_VEHICLE_DATA_SIMPLE vehicle_state);
	int InitLineMesh(void);
	int  CalcSonarObjPos(float *pos,float obj_dist,sonar_index index);
	float CalcPosDist(float *pFirstPoint,float *pSecPoint);
	void GenerateParkLotRect(sonar_parking_lot_t *park_lot_state,float *pVertex);
    void DrawParkLot(void);
	int InitParkinglotRect(void);
    int ProcessPreviousParkingLot(COMMON_VEHICLE_DATA_SIMPLE vehicle_state);
	void FiltObjData(int filter_num);
	unsigned char  JudgeJumpPoint(int filter_num,int sonar_index,int *obj_id,float *slop=NULL);
	void ProcessSearchingSlot(int filter_time,float *dist,int new_data_flag);
	int FilterDistData(float *pNewPoint,int sonar_index);
	void ResetParkSlotInfo(void);
	unsigned char JudgeObjLine(int filter_num,int sonar_index,int *obj_id,int park_lot_index,int empty_flag);
	void SetParkSlotInfo(int park_lot_index,park_lot_property property_index,void *pData,int active_flag=1);
	unsigned char CheckParkinglotSizewithType(sonar_parking_lot_t *pParklotData);
	void ProcessLotData(int sonar_index,int park_lot_index);
	int CalcMultiSonarObj(float *pos, float *dist_list, sonar_index index);
	int  CalcTwoSonarObjPos(float *pos,float obj1_dist,sonar_index obj1_index,float obj2_dist,sonar_index obj2_index,int clockwiseflag=0);
	int CheckObjInSonarFOV(int sonar1_index,int sonar2_index,float alpha,int sonar_clockwise_flag);
	int InitSoarArc(void);
	int UpdateSonarArc(float dist,sonar_index sonar_pos);
	void SetRadarPLDReslt();
	int TestVehicleMovment(void);
	void InitParkingLotTexture(int sonar_index,Float32 *pDataBuffer);
	void AddNewVehicleState(COMMON_VEHICLE_DATA_SIMPLE vehicle_state);
	int GetPreviousVehicleState(COMMON_VEHICLE_DATA_SIMPLE *vehicle_state,int previous_index);
	void DelayPointProcess(int delay_frame,float *pos);
private:

	Sonar_Pos     m_sonar_pos[max_sonar_num];
	float m_sonar_obj_list[max_sonar_num][2*MAX_SONAR_OBJ_NUM];
	float m_sonar_filter_obj_list[2][2*MAX_SONAR_OBJ_NUM];
    float m_sonar_color_list[3*max_sonar_num];
	int m_sonar_obj_list_end[max_sonar_num];
	int m_sonar_obj_list_start[max_sonar_num];
	float m_sonar_draw_obj_list[max_sonar_num][2*MAX_SONAR_OBJ_NUM];
	int m_new_obj_flag[max_sonar_num];
	int m_sonar_draw_obj_list_end[max_sonar_num];
	int m_sonar_draw_obj_list_start[max_sonar_num];
	VehicleMotion *m_vehicle_motion;
    float32_t m_track;
	float32_t m_t[ 9 ];
	float32_t m_Move_Matrix[ 9 ];
    ISceneNode *m_pStichNode;
	st_sonar_line_data_T m_sonar_data[max_sonar_num];
	unsigned char pre_line_type[MAX_PARKING_LOT_NUM];
	st_sonar_line_data_T m_sonar_arc_data[max_sonar_num];
	sonar_parking_lot_t m_sonar_parking_lot[max_sonar_num];
     unsigned char m_parking_lot_pos;
	
	st_stich_rect_data_slot_T m_sonar_parking_lot_hmi[max_sonar_num];
	float32_t m_obj_jump_point[2][4];
	int m_obj_jump_point_index[2];
	st_lot_data_T m_slot_data[CACHE_NUM][max_sonar_num];
	bool m_sonar_overlap_flag[max_sonar_num][max_sonar_num];
    unsigned char m_track_park_lot_flag;
	int m_filter_time;
    int m_active_buffer_index[max_sonar_num]; 
    COMMON_VEHICLE_DATA_SIMPLE m_vehcle_state_buffer[VEHICLE_STATE_BUFFER_NUM];
	int m_vehicle_state_buffer_index;
};

#endif //#ifndef __GL_SV_DEMO_H__
