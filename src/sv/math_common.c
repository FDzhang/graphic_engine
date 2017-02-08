
#include <stdlib.h>
#include <math.h>
#include "math_common.h"

#define __SUBCNST(x) x##F
#define LM_CNST(x) __SUBCNST(x) // force substitution

#define LM_REAL_MAX  FLT_MAX
#define LM_REAL_MIN -FLT_MAX
#define LM_REAL_EPSILON FLT_EPSILON

#define FABS(x) (((x)>=0.0)? (x) : -(x))

#define Mat(a,i,j,m) (a[(i)*(m)+(j)])


float32_t Mat_Determinant_3by3(float32_t M[9])
{
	return (M[0]*M[4]*M[8]-M[0]*M[5]*M[7]-M[3]*M[1]*M[8]+M[3]*
		M[2]*M[7]+M[6]*M[1]*M[5]-M[6]*M[2]*M[4]);
}


unsigned char Inv_Mat_3by3(float32_t pOut[9], float32_t pIn[9])
{
	float32_t v0, v1, v2, dDet;
	v0 = pIn[4]*pIn[8] - pIn[5]*pIn[7];
	v1 = pIn[5]*pIn[6] - pIn[3]*pIn[8];
	v2 = pIn[3]*pIn[7] - pIn[4]*pIn[6];
	dDet = v0*pIn[0] + v1*pIn[1] + v2*pIn[2];
	if(dDet == 0)
	{
		return 0;
	}
	else
	{
		dDet = (float32_t)1.0/dDet;
		pOut[0] = v0*dDet;
		pOut[1] = (pIn[2]*pIn[7]-pIn[1]*pIn[8])*dDet;
		pOut[2] = (pIn[1]*pIn[5]-pIn[2]*pIn[4])*dDet;
		pOut[3] = v1*dDet;
		pOut[4] = (pIn[0]*pIn[8]-pIn[2]*pIn[6])*dDet;
		pOut[5] = (pIn[2]*pIn[3]-pIn[0]*pIn[5])*dDet;
		pOut[6] = v2*dDet;
		pOut[7] = (pIn[1]*pIn[6]-pIn[0]*pIn[7])*dDet;
		pOut[8] = (pIn[0]*pIn[4]-pIn[1]*pIn[3])*dDet;
	}
	return 1;
}

void Transpose_Mat(float32_t *At, float32_t *A, int row, int col)
{
	int i,j;
	for(i=0; i < row; i++)
	{
		for(j=0; j < col; j++)
		{
			At[j*row+i] = A[i*col+j];
		}
	}
}

void Transpose_Mat_3by3_InPlace_DB(float64_t A[9])
{
	float64_t tmp;
	//swap A[1] A[3]
	tmp = A[1]; A[1] = A[3]; A[3] = tmp;
	//swap A[2] A[6]
	tmp = A[2]; A[2] = A[6]; A[6] = tmp;
	//swap A[5] A[7]
	tmp = A[5]; A[5] = A[7]; A[7] = tmp;
}

void Transpose_Mat_3by3_InPlace(float32_t A[9])
{
	float32_t tmp;
	//swap A[1] A[3]
	tmp = A[1]; A[1] = A[3]; A[3] = tmp;
	//swap A[2] A[6]
	tmp = A[2]; A[2] = A[6]; A[6] = tmp;
	//swap A[5] A[7]
	tmp = A[5]; A[5] = A[7]; A[7] = tmp;
}

void Transpose_Mat_3by3(float32_t At[9], float32_t A[9])
{
	//swap A[1] A[3]
	At[0] = A[0]; At[1] = A[3]; At[2] = A[6];
	//swap A[2] A[6]
	At[3] = A[1]; At[4] = A[4]; At[5] = A[7];
	//swap A[5] A[7]
	At[6] = A[2]; At[7] = A[5]; At[8] = A[8];
}

void Mat_Mul_3by3(float32_t Cout[9], float32_t Ain[9], float32_t Bin[9])
{
	Cout[0] = Ain[0] * Bin[0] + Ain[1] * Bin[3] + Ain[2] * Bin[6];
	Cout[1] = Ain[0] * Bin[1] + Ain[1] * Bin[4] + Ain[2] * Bin[7];
	Cout[2] = Ain[0] * Bin[2] + Ain[1] * Bin[5] + Ain[2] * Bin[8];

	Cout[3] = Ain[3] * Bin[0] + Ain[4] * Bin[3] + Ain[5] * Bin[6];
	Cout[4] = Ain[3] * Bin[1] + Ain[4] * Bin[4] + Ain[5] * Bin[7];
	Cout[5] = Ain[3] * Bin[2] + Ain[4] * Bin[5] + Ain[5] * Bin[8];

	Cout[6] = Ain[6] * Bin[0] + Ain[7] * Bin[3] + Ain[8] * Bin[6];
	Cout[7] = Ain[6] * Bin[1] + Ain[7] * Bin[4] + Ain[8] * Bin[7];
	Cout[8] = Ain[6] * Bin[2] + Ain[7] * Bin[5] + Ain[8] * Bin[8];
}

void Mat_Mul_3by3_DB(float64_t Cout[9], float64_t Ain[9], float64_t Bin[9])
{
	Cout[0] = Ain[0] * Bin[0] + Ain[1] * Bin[3] + Ain[2] * Bin[6];
	Cout[1] = Ain[0] * Bin[1] + Ain[1] * Bin[4] + Ain[2] * Bin[7];
	Cout[2] = Ain[0] * Bin[2] + Ain[1] * Bin[5] + Ain[2] * Bin[8];

	Cout[3] = Ain[3] * Bin[0] + Ain[4] * Bin[3] + Ain[5] * Bin[6];
	Cout[4] = Ain[3] * Bin[1] + Ain[4] * Bin[4] + Ain[5] * Bin[7];
	Cout[5] = Ain[3] * Bin[2] + Ain[4] * Bin[5] + Ain[5] * Bin[8];

	Cout[6] = Ain[6] * Bin[0] + Ain[7] * Bin[3] + Ain[8] * Bin[6];
	Cout[7] = Ain[6] * Bin[1] + Ain[7] * Bin[4] + Ain[8] * Bin[7];
	Cout[8] = Ain[6] * Bin[2] + Ain[7] * Bin[5] + Ain[8] * Bin[8];
}

//mat multi vector: C=A*B, C_31, A_33, B_31
void Mat_Mul_Vec_3by3(float32_t Cout[3], float32_t Ain[9], float32_t Bin[3])
{
	Cout[0] = Ain[0] * Bin[0] + Ain[1] * Bin[1] + Ain[2] * Bin[2];
	Cout[1] = Ain[3] * Bin[0] + Ain[4] * Bin[1] + Ain[5] * Bin[2];
	Cout[2] = Ain[6] * Bin[0] + Ain[7] * Bin[1] + Ain[8] * Bin[2];
}

void Mat_Mul_Vec_3by3_DB(float64_t Cout[3], float64_t Ain[9], float64_t Bin[3])
{
	Cout[0] = Ain[0] * Bin[0] + Ain[1] * Bin[1] + Ain[2] * Bin[2];
	Cout[1] = Ain[3] * Bin[0] + Ain[4] * Bin[1] + Ain[5] * Bin[2];
	Cout[2] = Ain[6] * Bin[0] + Ain[7] * Bin[1] + Ain[8] * Bin[2];
}

void Inverse_RT_InPlace(float32_t R[9], float32_t T[3])
{
	float32_t t[3];
	Transpose_Mat_3by3_InPlace(R);
	Mat_Mul_Vec_3by3(t, R, T);
	T[0] = -t[0]; T[1] = -t[1]; T[2] = -t[2];
}

void Inverse_RT_InPlace_DB(float64_t R[9], float64_t T[3])
{
	float64_t t[3];
	Transpose_Mat_3by3_InPlace_DB(R);
	Mat_Mul_Vec_3by3_DB(t, R, T);
	T[0] = -t[0]; T[1] = -t[1]; T[2] = -t[2];
}

void Inverse_RT(float32_t Rout[9], float32_t Tout[3], float32_t Rin[9], float32_t Tin[3])
{
	Transpose_Mat_3by3(Rout, Rin);
	Mat_Mul_Vec_3by3(Tout, Rout, Tin);
	Tout[0] = -Tout[0]; Tout[1] = -Tout[1]; Tout[2] = -Tout[2];
}

void Cvt_Rotation_To_Angles(const float32_t R[9], float32_t angles[3])
{
	angles[0] = atan2f(R[7], R[8]);
	angles[1] = atan2f(-R[6], sqrt(R[7]*R[7]+R[8]*R[8]));
	angles[2] = atan2f(R[3], R[0]);
}

void Cvt_Angles_To_Rotation(float32_t R[9], const float32_t angles[3])
{
	float32_t cx = cosf(angles[0]), cy = cosf(angles[1]), cz = cosf(angles[2]);
	float32_t sx = sinf(angles[0]), sy = sinf(angles[1]), sz = sinf(angles[2]);
	R[0] = cy*cz;	R[1] = -cx*sz+sx*sy*cz;	R[2] = sx*sz+cx*sy*cz;
	R[3] = cy*sz;	R[4] = cx*cz+sx*sy*sz;	R[5] = -sx*cz+cx*sy*sz;
	R[6] = -sy;		R[7] = sx*cy;			R[8] = cx*cy;
}

void Cvt_Angles_To_Rotation_DB(float64_t R[9], const float64_t angles[3])
{
	float64_t cx = cos(angles[0]), cy = cos(angles[1]), cz = cos(angles[2]);
	float64_t sx = sin(angles[0]), sy = sin(angles[1]), sz = sin(angles[2]);
	R[0] = cy*cz;	R[1] = -cx*sz+sx*sy*cz;	R[2] = sx*sz+cx*sy*cz;
	R[3] = cy*sz;	R[4] = cx*cz+sx*sy*sz;	R[5] = -sx*cz+cx*sy*sz;
	R[6] = -sy;		R[7] = sx*cy;			R[8] = cx*cy;
}
