/*
 * fsm_automatic.c
 *
 *  Created on: Oct 26, 2026
 *      Author: Hoang
 */
#include "fsm_automatic.h"

int counter;
int status_automatic;

void fsm_automatic_init(){
	status_automatic = AUTO_R_G;
}

void fsm_automatic_run(){
	switch (status_automatic) {
		case AUTO_R_G:
			HAL_GPIO_WritePin(NS_RED_LED_Port, NS_RED_LED_Pin, LED_ON);
			HAL_GPIO_WritePin(NS_YELLOW_LED_Port, NS_YELLOW_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(NS_GREEN_LED_Port, NS_GREEN_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(EW_RED_LED_Port, EW_RED_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(EW_YELLOW_LED_Port, EW_YELLOW_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(EW_GREEN_LED_Port, EW_GREEN_LED_Pin, LED_ON);
			counter = EW_duration[2];
			NS_counter = NS_duration[0];
			EW_counter = EW_duration[2];
			status_automatic = AUTO_R_Y;
			break;

		case AUTO_R_Y:
			HAL_GPIO_WritePin(NS_RED_LED_Port, NS_RED_LED_Pin, LED_ON);
			HAL_GPIO_WritePin(NS_YELLOW_LED_Port, NS_YELLOW_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(NS_GREEN_LED_Port, NS_GREEN_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(EW_RED_LED_Port, EW_RED_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(EW_YELLOW_LED_Port, EW_YELLOW_LED_Pin, LED_ON);
			HAL_GPIO_WritePin(EW_GREEN_LED_Port, EW_GREEN_LED_Pin, LED_OFF);
			counter = EW_duration[1];
			EW_counter = EW_duration[1];
			status_automatic = AUTO_G_R;
			break;

		case AUTO_G_R:
			HAL_GPIO_WritePin(NS_RED_LED_Port, NS_RED_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(NS_YELLOW_LED_Port, NS_YELLOW_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(NS_GREEN_LED_Port, NS_GREEN_LED_Pin, LED_ON);
			HAL_GPIO_WritePin(EW_RED_LED_Port, EW_RED_LED_Pin, LED_ON);
			HAL_GPIO_WritePin(EW_YELLOW_LED_Port, EW_YELLOW_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(EW_GREEN_LED_Port, EW_GREEN_LED_Pin, LED_OFF);
			counter = NS_duration[2];
			NS_counter = NS_duration[2];
			EW_counter = EW_duration[0];
			status_automatic = AUTO_Y_R;
			break;

		case AUTO_Y_R:
			HAL_GPIO_WritePin(NS_RED_LED_Port, NS_RED_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(NS_YELLOW_LED_Port, NS_YELLOW_LED_Pin, LED_ON);
			HAL_GPIO_WritePin(NS_GREEN_LED_Port, NS_GREEN_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(EW_RED_LED_Port, EW_RED_LED_Pin, LED_ON);
			HAL_GPIO_WritePin(EW_YELLOW_LED_Port, EW_YELLOW_LED_Pin, LED_OFF);
			HAL_GPIO_WritePin(EW_GREEN_LED_Port, EW_GREEN_LED_Pin, LED_OFF);
			counter = NS_duration[1];
			NS_counter = NS_duration[1];
			status_automatic = AUTO_R_G;
			break;

		default:
			break;
	}
}

