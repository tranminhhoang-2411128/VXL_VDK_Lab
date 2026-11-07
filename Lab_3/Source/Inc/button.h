/*
 * button.h
 *
 *  Created on: Sep 25, 2026
 *      Author: Hoang
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

#define NUMBER_OF_BUTTONS 3
#define BTN_PORT GPIOB
#define BTN_0_PIN B0_Pin
#define BTN_1_PIN B1_Pin
#define BTN_2_PIN B2_Pin

#define NORMAL_STATE GPIO_PIN_SET
#define ACTIVE_STATE GPIO_PIN_RESET
#define TIMER_HOLD_CHECK 200

extern volatile int button_flag[];
extern volatile int hold_flag[];

void btnInit();
void getInput();

#endif /* INC_BUTTON_H_ */
