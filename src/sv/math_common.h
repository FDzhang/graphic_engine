#ifndef _MATH_COMMON_H_
#define _MATH_COMMON_H_
//#include "..\common\reuse.h"
#include "reuse_gpu.h"

#ifndef MAX
#define MIN(x,y) ( (x) < (y) ? (x) : (y) )
#define MAX(x,y) ((x)>(y)?(x):(y))
#define SIGN(a) ((a) >= 0.0 ? 1 : -1)
#endif

#ifdef __cplusplus
extern "C" {
#endif
/******************Matrix Operation*******************/
//determinant of a 3by3 matrix
float32_t Mat_Determinant_3by3(float32_t A[9]);

//inverse of 3*3 matrix
unsigned char Inv_Mat_3by3(float32_t pOut[9], float32_t pIn[9]);

//transpose Matrix A[m][n] --> AT [n][m]
void Transpose_Mat(float32_t At[9], float32_t A[9], int row, int col);

//in-place transpose A by A'
void Transpose_Mat_3by3(float32_t At[9], float32_t A[9]);

void Transpose_Mat_3by3_InPlace(float32_t A[9]);

void Transpose_Mat_3by3_InPlace_DB(float64_t A[9]);
//mat multi C=A*B, all are 3*3 matrix
void Mat_Mul_3by3(float32_t Cout[9], float32_t Ain[9], float32_t Bin[9]);

//mat multi vector: C=A*B, C_31, A_33, B_31
void Mat_Mul_Vec_3by3(float32_t Cout[3], float32_t Ain[9], float32_t Bin[3]);

void Mat_Mul_Vec_3by3_DB(float64_t Cout[3], float64_t Ain[9], float64_t Bin[3]);
//R, T will be in-place updated to R', and -R'T
void Inverse_RT_InPlace(float32_t R[9], float32_t T[3]);

void Inverse_RT_InPlace_DB(float64_t R[9], float64_t T[3]);

void Inverse_RT(float32_t Rout[9], float32_t Tout[3], float32_t Rin[9], float32_t Tin[3]);


//convert from angles into rotation matrix, R=Rot(Z)*Rot(Y)*Rot(X), angles in rad
void Cvt_Rotation_To_Angles(const float32_t R[9], float32_t angles[3]);

void Cvt_Angles_To_Rotation_DB(float64_t R[9], const float64_t angles[3]);

//convert from rotation matrix into angles, R=Rot(Z)*Rot(Y)*Rot(X), angles in rad
void Cvt_Angles_To_Rotation(float32_t R[9], const float32_t angles[3]);

#ifdef __cplusplus
}
#endif
#endif
