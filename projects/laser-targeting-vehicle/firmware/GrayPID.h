#ifndef GRAYPID_H
#define GRAYPID_H

#include "GrayPID.h"
#include "ti_msp_dl_config.h"

extern volatile uint32_t gray_1;
extern volatile uint32_t gray_2;
extern volatile uint32_t gray_3;
extern volatile uint32_t gray_4;
extern volatile uint32_t gray_5;
extern volatile uint32_t gray_6;
extern volatile uint32_t gray_7;
extern volatile uint32_t gray_8;
extern volatile uint32_t gray_9;
extern volatile uint32_t gray_10;
extern volatile uint32_t gray_11;
extern volatile uint32_t gray_12;
extern volatile uint32_t gray_13;
extern volatile uint32_t gray_14;
extern volatile uint32_t gray_15;
extern volatile uint32_t gray_16;

float GanPID2(void);
float TurnPID(float Point);
float GanPID(void);
float GanPID3(void);
#endif 