/*
 * fsm_manual.c
 *
 *  Created on: Nov 6, 2026
 *      Author: Hoang
 */

#include "fsm_manual.h"

void fsm_manual_init(){
	HAL_GPIO_WritePin(NS_RED_LED_Port, NS_RED_LED_Pin, LED_OFF);
	HAL_GPIO_WritePin(NS_YELLOW_LED_Port, NS_YELLOW_LED_Pin, LED_OFF);
	HAL_GPIO_WritePin(NS_GREEN_LED_Port, NS_GREEN_LED_Pin, LED_OFF);
	HAL_GPIO_WritePin(EW_RED_LED_Port, EW_RED_LED_Pin, LED_OFF);
	HAL_GPIO_WritePin(EW_YELLOW_LED_Port, EW_YELLOW_LED_Pin, LED_OFF);
	HAL_GPIO_WritePin(EW_GREEN_LED_Port, EW_GREEN_LED_Pin, LED_OFF);

	EW_counter = EW_duration[status - 1]; //Main road
	NS_counter = status + 1;
}

void fsm_manual_run(){
	switch (status) {
		case MANUAL_R:
			HAL_GPIO_TogglePin(NS_RED_LED_Port, NS_RED_LED_Pin);
			HAL_GPIO_TogglePin(EW_RED_LED_Port, EW_RED_LED_Pin);
			break;

		case MANUAL_Y:
			HAL_GPIO_TogglePin(NS_YELLOW_LED_Port, NS_YELLOW_LED_Pin);
			HAL_GPIO_TogglePin(EW_YELLOW_LED_Port, EW_YELLOW_LED_Pin);
			break;

		case MANUAL_G:
			HAL_GPIO_TogglePin(NS_GREEN_LED_Port, NS_GREEN_LED_Pin);
			HAL_GPIO_TogglePin(EW_GREEN_LED_Port, EW_GREEN_LED_Pin);
			break;

		default:
			break;
	}
}
