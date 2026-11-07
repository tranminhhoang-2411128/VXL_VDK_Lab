/*
 * seven_segment.h
 *
 *  Created on: Oct 28, 2026
 *      Author: Hoang
 */

#ifndef INC_SEVEN_SEGMENT_H_
#define INC_SEVEN_SEGMENT_H_

#include "global.h"

#define NUMBER_OF_ENABLER 2
#define TEN_ENABLE_Port A6_GPIO_Port
#define TEN_ENABLE_Pin A6_Pin
#define ONE_ENABLE_Port A7_GPIO_Port
#define ONE_ENABLE_Pin A7_Pin

#define NS_7SEG_Port GPIOA
#define NS_7SEG_A A9_Pin
#define NS_7SEG_B A10_Pin
#define NS_7SEG_C A11_Pin
#define NS_7SEG_D A12_Pin
#define NS_7SEG_E A13_Pin
#define NS_7SEG_F A14_Pin
#define NS_7SEG_G A15_Pin

#define EW_7SEG_Port GPIOB
#define EW_7SEG_A B3_Pin
#define EW_7SEG_B B4_Pin
#define EW_7SEG_C B5_Pin
#define EW_7SEG_D B6_Pin
#define EW_7SEG_E B7_Pin
#define EW_7SEG_F B8_Pin
#define EW_7SEG_G B9_Pin

#define SEVEN_SEG_ON GPIO_PIN_RESET
#define SEVEN_SEG_OFF GPIO_PIN_SET

void display7SEG_NS(int num);
void display7SEG_EW(int num);

void enable7SEG(int place);

extern int currentEnable;

#endif /* INC_SEVEN_SEGMENT_H_ */
