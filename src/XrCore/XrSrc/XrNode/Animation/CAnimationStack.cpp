#include "CAnimationStack.h"
#include "../CNode.h"

Boolean CAnimationStack::Update(UInt32 timeStamp)
{
	Int32 i,j,nodeNum;
	CAnimationLayer* pLayer;
	CAnimationNode* pNode;
	Float32 sec= Float32(timeStamp - m_startTime)/1000;
	if (m_activeLayer==-1) return false;
	j=0;
	nodeNum = 0;
	while (j<MAX_ANIMATION_NODE_NUM && nodeNum<m_animationLayer[m_activeLayer].nodeNum) {
		if (!m_animationLayer[m_activeLayer].nodes[j].propertys) {
			j++;
			continue;
		}
		//xrprintf("time=%f", sec);
		UpdateNodeAnimation(&m_animationLayer[m_activeLayer].nodes[j],sec);
		nodeNum++;
		j++;
	}
	if (sec > m_animationLayer[m_activeLayer].duration/2-0.05) m_startTime = timeStamp - 50;
	return true;
}

static APType AP[9]={AP_X,AP_Y,AP_Z,AP_RX,AP_RY,AP_RZ,AP_SX,AP_SY,AP_SZ};
xr_state CAnimationStack::UpdateNodeAnimation(CAnimationNode* node, Float32 currentSec)
{
	Int32 k,l,frameNum;
	Float32 val;
	CAnimationCurve* curve;
	CNode* pNode=node->pTarget;
	for (k=0;k<9;k++) {
		if (AP[k]&node->propertys) {
			frameNum = node->curves[k].frameNum;
			GetSpline(currentSec, &val, (float*)node->curves[k].frames, node->curves[k].frameNum, 1);
			pNode->UpdateProperty(AP[k], val);

			//xrprintf("second=%f, val=%f\n", currentSec, val);
		}
	}
	return XR_OK;
}

xr_state CAnimationStack::SetLayerCount(Int32 count)
{
	if (m_animationLayer) return XR_FAILED;
	m_animationLayer = new CAnimationLayer[count];
	m_layerCount = count;
	m_activeLayer = 0;
	return XR_OK;
}

xr_state CAnimationStack::Start() {
	if (m_activeLayer==-1) return XR_OK;
	m_startTime = XrGetTime();
	m_active = TRUE;
	m_duration = m_animationLayer[m_activeLayer].duration;
}
