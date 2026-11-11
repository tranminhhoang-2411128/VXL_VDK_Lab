/*
 * global.h
 *
 *  Created on: Oct 26, 2026
 *      Author: Hoang
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "software_timer.h"

#define NS_RED_LED_Port A0_GPIO_Port
#define NS_RED_LED_Pin A0_Pin
#define NS_YELLOW_LED_Port A1_GPIO_Port
#define NS_YELLOW_LED_Pin A1_Pin
#define NS_GREEN_LED_Port A2_GPIO_Port
#define NS_GREEN_LED_Pin A2_Pin

#define EW_RED_LED_Port A3_GPIO_Port
#define EW_RED_LED_Pin A3_Pin
#define EW_YELLOW_LED_Port A4_GPIO_Port
#define EW_YELLOW_LED_Pin A4_Pin
#define EW_GREEN_LED_Port A5_GPIO_Port
#define EW_GREEN_LED_Pin A5_Pin

#define LED_ON GPIO_PIN_RESET
#define LED_OFF GPIO_PIN_SET

#define AUTOMATIC_MODE 0
#define MANUAL_MODE_RED 1
#define MANUAL_MODE_YELLOW 2
#define MANUAL_MODE_GREEN 3

extern int status;
extern int counter;
extern int NS_counter;
extern int EW_counter;
extern int NS_duration[3];
extern int EW_duration[3];

#endif /* INC_GLOBAL_H_ */
