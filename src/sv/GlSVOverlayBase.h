#ifndef __GL_SV_OVERLAYBASE_H__
#define __GL_SV_OVERLAYBASE_H__

#include "fileloader.h"
#include "../XrCore/XrSrc/External/XrHeaders.h"

#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"


typedef struct Overlay_Para_T
{
    float vehicle_length;
	float vehicle_width;
	float vehicle_axis_length;
	float vehicle_front_wheel2bumper_length;
	float vehicle_rear_wheel2bumper_length;
	float m_model_bottom;
	
	int dynamic_overlay_point_num;
	float model_scale;
	float m_calib_center_x;   //x means imaage x direction
	float m_calib_center_y;
	float m_calib_mmpp_x;
	float m_calib_mmpp_y;

	float m_front_cam_pos_wld[3];
	float m_rear_cam_pos_wld[3];
	
}Overlay_Para;


#define OLY_DIR_FOWARD  0
#define OLY_DIR_BACKWARD 1
#define OLY_SINGLE_BACKWARD 2
#define OLY_VERTICAL_PARKING 3
#define OLY_PARRAEL_PARKING 4

#define MY_PI 3.1415926


#define calib_3D  0

#define calib_2D_STICH  1
#define calib_2D_SINGLE 2

#define SOLUTION_AVALIBALE 0
#define SOLUTION_UNAVALIBALE  1
#define SKY_CLINDER_RADIUS 3500

enum
{
    CAM_ZONE_LEFT=0,
	CAM_ZONE_TOP=1,
    CAM_ZONE_RIGHT=2,
	CAM_ZONE_BOTTOM=3,	
};

class GlSVOverlayBase 
{
public:
	GlSVOverlayBase();

	virtual int Init(Overlay_Para pConfig);
	
    virtual int SetUpBuffer(void *pData,unsigned int size,unsigned int element_num,unsigned char CalibMode);
	virtual int GetIndexBuffer(int Index,GLushort **pIndexBuffer, unsigned int *BufSize);
	
	virtual int GetVertexBuffer(int Index,float **pVertexBuffer, unsigned int *BufSize);
	virtual void Cal_World_2_Model_Coordinate(float *out_Model_Coord,float *in_world_coord);
	virtual void SaveVertexData(void);

    virtual void ConvertGroundToClinder(float *pInputCoord,float *pOutputCoord,float Clyder_radius,float Scale_y,unsigned char Pos);
	virtual unsigned char SolveSquareEquation(float *solve,float a ,float b,float c);
	void Cal_World_2_Model_Coordinate_3d(float *out_Model_Coord,float *in_world_coord);
	void Set_Cam_Pos(unsigned char pos,float *pCam);
	
	void Set_Cam_Zone(unsigned char pos,float *pCamZone);
	//virtual void Cal_World_2_Model_Coordinate_3d(float *out_Model_Coord,float *in_world_coord);

protected:


	
	


    Overlay_Para m_config;
	void *m_pdata;
	unsigned int m_data_size;
    unsigned int m_element_num;
	unsigned char m_calib_mode;
	unsigned char m_cam_pos; // 0 1 2 3 means front rear left right

    float m_pFrontCamZone[4];
	float m_pRearCamZone[4];


};

#endif //#ifndef __GL_SV_DEMO_H__
