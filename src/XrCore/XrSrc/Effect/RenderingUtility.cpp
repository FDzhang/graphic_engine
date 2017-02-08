#include "RenderingUtility.h"
#include "../Common/XrMathEx.h"

Void ApplyModelTransform(TransformInfo* pTrans, struct XRMat4& model)
{
	model =  XRMat4::Scale(pTrans->sx, pTrans->sy, pTrans->sz) * model;
	if (pTrans->rx != 0) model = XRMat4::RotationX(pTrans->rx) * model;
	if (pTrans->ry != 0) model = XRMat4::RotationY(pTrans->ry) * model;
	if (pTrans->rz != 0) model = XRMat4::RotationZ(pTrans->rz) * model;
	model =  XRMat4::Translation(pTrans->tx, pTrans->ty, pTrans->tz) * model;
}
