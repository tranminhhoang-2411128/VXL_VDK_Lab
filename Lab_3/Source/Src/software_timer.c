/*
 * software_timer.c
 *
 *  Created on: Oct 27, 2026
 *      Author: Hoang
 */
#include "software_timer.h"

volatile int timer_flag[NUMBER_OF_S_TIMERS] = {0, 0, 0};
int timer_counter[NUMBER_OF_S_TIMERS] = {0, 0, 0};

void setTimer(int timer_index, int timer_duration){
	timer_flag[timer_index] = 0;
	timer_counter[timer_index] = timer_duration / ISR_TICK;
}

void timerRun(){
	for (int i = 0; i < NUMBER_OF_S_TIMERS; i++){
		if (timer_counter[i] > 0){
			timer_counter[i]--;
		}
		if (timer_counter[i] == 0){
			timer_flag[i] = 1;
		}
	}
}

