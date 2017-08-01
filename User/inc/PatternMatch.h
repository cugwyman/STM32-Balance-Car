#ifndef __PATTERN_MATCH_H
#define __PATTERN_MATCH_H

#include "root.h"

#define MAYBE_BARRIER (!inRing && !ringEndDelay ? WhichBarrier() : Unknown)

int16_t GetRoadType(void);
bool OutOfRoadJudge(void);
void RingCompensateGoLeft(void);
void RingCompensateGoRight(void);
void RingEndCompensateFromLeft(void);
void RingEndCompensateFromRight(void);
void LeftCurveCompensate(void);
void RightCurveCompensate(void);
void CrossRoadCompensate(void);
void LeftBarrierCompensate(void);
void RightBarrierCompensate(void); 
bool StartLineJudge(int16_t row);
bool StraightLineJudge(void);
bool IsCrossRoad(void);
 
extern int16_t ring_offset;
extern int16_t ring_end_offset;
extern int32_t ringDistance;
extern int32_t crossRoadDistance;
extern bool inRing;
extern bool ringEndDelay;
extern int32_t barrierDistance;
extern int32_t barrierDealDistance;
extern bool ringInterval;
extern bool inCrossRoad;
extern bool aroundBarrier;

#endif
