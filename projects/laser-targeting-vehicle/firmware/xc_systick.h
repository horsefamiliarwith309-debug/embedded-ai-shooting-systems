/*
 * xc_systick.h
 *
 *  Created on: 2024  7  3  
 *      Author: ccvq
 */

#ifndef XC_SYSTICK_H_
#define XC_SYSTICK_H_

extern volatile unsigned int jiffies;

extern volatile unsigned int the_time;

extern unsigned int time;
extern volatile unsigned int stop_test2;
extern volatile unsigned int stop_ta;

void xc_delay(unsigned int ms);
void yc_delay(uint32_t us);

#endif /* XC_SYSTICK_H_ */
