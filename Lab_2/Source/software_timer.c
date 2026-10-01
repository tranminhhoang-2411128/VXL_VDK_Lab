/*
 * software_timer.c
 *
 *  Created on: Sep 26, 2026
 *      Author: Hoang
 */

#include "software_timer.h"

int timer0_counter = 0;
int timer0_flag = 0;
int timer_EN0_counter = 0;
int timer_EN0_flag = 0;
int timer_EN1_counter = 0;
int timer_EN1_flag = 0;
int timer_EN2_counter = 0;
int timer_EN2_flag = 0;
int timer_EN3_counter = 0;
int timer_EN3_flag = 0;
int timer_LEDBuffer_counter = 0;
int timer_LEDBuffer_flag = 0;
int timer_MatrixBuffer_counter = 0;
int timer_MatrixBuffer_flag = 0;

void setTimer0(int duration){
	timer0_counter = duration / TIMER_CYCLE;
	timer0_flag = 0;
}
void setTimer_EN0(int duration){
	timer_EN0_counter = duration / TIMER_CYCLE;
	timer_EN0_flag = 0;
}
void setTimer_EN1(int duration){
	timer_EN1_counter = duration / TIMER_CYCLE;
	timer_EN1_flag = 0;
}
void setTimer_EN2(int duration){
	timer_EN2_counter = duration / TIMER_CYCLE;
	timer_EN2_flag = 0;
}
void setTimer_EN3(int duration){
	timer_EN3_counter = duration / TIMER_CYCLE;
	timer_EN3_flag = 0;
}
void setTimer_LEDBuffer(int duration){
	timer_LEDBuffer_counter = duration / TIMER_CYCLE;
	timer_LEDBuffer_flag = 0;
}
void setTimer_MatrixBuffer(int duration){
	timer_MatrixBuffer_counter = duration / TIMER_CYCLE;
	timer_MatrixBuffer_flag = 0;
}

void timerRun(){
	if (timer0_counter > 0){
		timer0_counter--;
		if (timer0_counter <= 0){
			timer0_flag = 1;
		}
	}
	if (timer_EN0_counter > 0){
		timer_EN0_counter--;
		if (timer_EN0_counter <= 0){
			timer_EN0_flag = 1;
		}
	}
	if (timer_EN1_counter > 0){
		timer_EN1_counter--;
		if (timer_EN1_counter <= 0){
			timer_EN1_flag = 1;
		}
	}
	if (timer_EN2_counter > 0){
		timer_EN2_counter--;
		if (timer_EN2_counter <= 0){
			timer_EN2_flag = 1;
		}
	}
	if (timer_EN3_counter > 0){
		timer_EN3_counter--;
		if (timer_EN3_counter <= 0){
			timer_EN3_flag = 1;
		}
	}
	if (timer_LEDBuffer_counter > 0){
		timer_LEDBuffer_counter--;
		if (timer_LEDBuffer_counter <= 0){
			timer_LEDBuffer_flag = 1;
		}
	}
	if (timer_MatrixBuffer_counter > 0){
		timer_MatrixBuffer_counter--;
		if (timer_MatrixBuffer_counter <= 0){
			timer_MatrixBuffer_flag = 1;
		}
	}
}
