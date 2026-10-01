/*
 * software_timer.h
 *
 *  Created on: Sep 26, 2026
 *      Author: Hoang
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"
#define TIMER_CYCLE 10

extern int timer0_flag;
extern int timer_EN0_flag;
extern int timer_EN1_flag;
extern int timer_EN2_flag;
extern int timer_EN3_flag;
extern int timer_LEDBuffer_flag;
extern int timer_MatrixBuffer_flag;

void setTimer0(int duration);
void setTimer_EN0(int duration);
void setTimer_EN1(int duration);
void setTimer_EN2(int duration);
void setTimer_EN3(int duration);
void setTimer_LEDBuffer(int duration);
void setTimer_MatrixBuffer(int duration);

void timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
