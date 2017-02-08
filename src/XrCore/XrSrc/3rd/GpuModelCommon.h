#ifndef __GPU_MODEL_COMMON_H__
#define __GPU_MODEL_COMMON_H__

typedef struct Model_SV_Vertex_T
{
   float vertex[3];
   float normal[3];    //nomal [0] is used to store alpha blending cof
   float texture[2];
}Model_SV_Vertex;

typedef  unsigned short index_type;

typedef struct Model_SV_T
{
	int vertex_total;
	int index_total; 
    int clockwise_flag;
    Model_SV_Vertex *vertex_list;//[VERTEX_TOTAL];
    index_type *index_list;//[INDEX_TOTAL];
}Model_SV;
#endif
