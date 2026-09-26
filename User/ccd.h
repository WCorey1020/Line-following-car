#ifndef __CCD_H
#define __CCD_H

#include "stdint.h"
#define CCD_FRAME_SIZE 110
uint16_t CCDReadFrame(void);
int16_t CCD_GetPosition(void);
#endif