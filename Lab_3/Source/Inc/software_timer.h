/*
 * software_timer.h
 *
 *  Created on: Oct 26, 2026
 *      Author: Hoang
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define ISR_TICK 10
#define NUMBER_OF_S_TIMERS 3
/*
 * 0: Automatic traffic light (FSM_AUTOMATIC)
 *
 * 1: 7-seg buffer update (FSM_AUTOMATIC)
 *
 * 2: 7-seg scan
 */

extern volatile int timer_flag[NUMBER_OF_S_TIMERS];
extern int timer_counter[NUMBER_OF_S_TIMERS];

void setTimer(int timer_index, int timer_duration);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
