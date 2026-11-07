/*
 * seven_segment.c
 *
 *  Created on: Oct 28, 2026
 *      Author: Hoang
 */
#include "seven_segment.h"

int currentEnable = 1;

void enable7SEG(int place){
	switch (place) {
		case 0:
			HAL_GPIO_WritePin(ONE_ENABLE_Port, ONE_ENABLE_Pin, SEVEN_SEG_OFF);
			display7SEG_NS(NS_counter / 10);
			display7SEG_EW(EW_counter / 10);
			HAL_GPIO_WritePin(TEN_ENABLE_Port, TEN_ENABLE_Pin, SEVEN_SEG_ON);
			break;

		case 1:
			HAL_GPIO_WritePin(TEN_ENABLE_Port, TEN_ENABLE_Pin, SEVEN_SEG_OFF);
			display7SEG_NS(NS_counter % 10);
			display7SEG_EW(EW_counter % 10);
			HAL_GPIO_WritePin(ONE_ENABLE_Port, ONE_ENABLE_Pin, SEVEN_SEG_ON);
			break;

		default:
			break;
	}
}

static const int SevenSEG_LUT[10] = { //abcdefg
		1,	//0000001
		79, //1001111
		18, //0010010
		6,	//0000110
		76, //1001100
		36, //0100100
		32, //0100000
		15, //0001111
		0,	//0000000
		4	//0000100
};
static const uint16_t NS_SEG_PINS[7] = {NS_7SEG_A, NS_7SEG_B, NS_7SEG_C, NS_7SEG_D, NS_7SEG_E, NS_7SEG_F, NS_7SEG_G};
static const uint16_t EW_SEG_PINS[7] = {EW_7SEG_A, EW_7SEG_B, EW_7SEG_C, EW_7SEG_D, EW_7SEG_E, EW_7SEG_F, EW_7SEG_G};

void display7SEG_NS(int num){
	int bit = SevenSEG_LUT[num];

	for (int i = 0; i < 7; i++) {
		HAL_GPIO_WritePin(NS_7SEG_Port, NS_SEG_PINS[i], (bit & (1 << (6 - i))) ? SEVEN_SEG_OFF : SEVEN_SEG_ON);
	}
}

void display7SEG_EW(int num){
	int bit = SevenSEG_LUT[num];

	for (int i = 0; i < 7; i++) {
		HAL_GPIO_WritePin(EW_7SEG_Port, EW_SEG_PINS[i], (bit & (1 << (6 - i))) ? SEVEN_SEG_OFF : SEVEN_SEG_ON);
	}
}

