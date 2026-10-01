/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
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
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {0, 6, 5, 0};
int hour = 15, minute = 8, second = 50;

const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = {
	0x00,	// ROW0 00000000
	0x00,	// ROW1 00000000
	0x18,	// ROW2 00011000
	0x24,	// ROW3 00100100
	0x3C,	// ROW4 00111100
	0x24,	// ROW5 00100100
	0x00,	// ROW6 00000000
	0x00	// ROW7 00000000
};
static const uint16_t ROW_PINS[8] = {ROW0_Pin, ROW1_Pin, ROW2_Pin, ROW3_Pin,
                                     ROW4_Pin, ROW5_Pin, ROW6_Pin, ROW7_Pin};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void display7SEG(int num);
void update7SEG(int index);
void updateClockBuffer();
void toggle7SEG(int led_flag);

void displayLEDMatrix(int index);
void updateLEDMatrix(int index);
void LEDAnimation(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7SEG(int num)
{
    int bit = SevenSEG_LUT[num];

    HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, ((bit & (1 << 6)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, ((bit & (1 << 5)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, ((bit & (1 << 4)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, ((bit & (1 << 3)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, ((bit & (1 << 2)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, ((bit & (1 << 1)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, ((bit & (1 << 0)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void update7SEG(int index)
{
	if (index >= MAX_LED){
		index = 0;
	}
	switch (index) {
		case 0:
			display7SEG(led_buffer[0]);
			break;
		case 1:
			display7SEG(led_buffer[1]);
			break;
		case 2:
			display7SEG(led_buffer[2]);
			break;
		case 3:
			display7SEG(led_buffer[3]);
			break;
		default:
			break;
	}
}

void updateClockBuffer()
{
	led_buffer[0] = hour / 10;
	led_buffer[1] = hour % 10;
	led_buffer[2] = minute / 10;
	led_buffer[3] = minute % 10;
}

void toggle7SEG(int led_flag)
{
	  switch (led_flag) {
		case 0:
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
			break;
		default:
			break;
	}
}

void displayLEDMatrix(int index)
{

	HAL_GPIO_WritePin(GPIOB, ROW0_Pin|ROW1_Pin|ROW2_Pin|ROW3_Pin
	                        |ROW4_Pin|ROW5_Pin|ROW6_Pin|ROW7_Pin, GPIO_PIN_SET);

	uint8_t bit = matrix_buffer[index];

	//Read column state from buffer using bitmask
	HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, ((bit & (1 << 7)) > 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, ((bit & (1 << 6)) > 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, ((bit & (1 << 5)) > 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, ((bit & (1 << 4)) > 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, ((bit & (1 << 3)) > 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, ((bit & (1 << 2)) > 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, ((bit & (1 << 1)) > 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, ((bit & (1 << 0)) > 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOB, ROW_PINS[index], GPIO_PIN_RESET);
}

void updateLEDMatrix(int index)
{
	if (index >= MAX_LED_MATRIX){
		index = 0;
	}
	displayLEDMatrix(index);
}

void LEDAnimation(void)
{
	uint8_t top_row = matrix_buffer[0];
	for (int i = 0; i < 7; i++) {
		matrix_buffer[i] = matrix_buffer[i + 1];
	}
	matrix_buffer[7] = top_row;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  setTimer0(1000);
  setTimer_LEDBuffer(10);
  setTimer_EN0(10);
  setTimer_EN1(250);
  setTimer_EN2(500);
  setTimer_EN3(750);
  setTimer_MatrixBuffer(10);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  if (timer0_flag == 1){
		  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);

		  second++;
		  if (second >= 60){
			  second = 0;
			  minute++;
		  }
		  if (minute >= 60){
			  minute = 0;
			  hour++;
		  }
		  if (hour >= 24){
			  hour = 0;
		  }
		  updateClockBuffer();
		  LEDAnimation();
		  HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		  setTimer0(1000);
	  }

	  if (timer_LEDBuffer_flag == 1){
		  update7SEG(index_led++);
		  if (index_led >= MAX_LED){
		  		index_led = 0;
		  	}
		  setTimer_LEDBuffer(250);
	  }

	  if (timer_EN0_flag == 1){
		  toggle7SEG(0);
		  setTimer_EN0(1000);
	  }
	  if (timer_EN1_flag == 1){
		  toggle7SEG(1);
		  setTimer_EN1(1000);
	  }
	  if (timer_EN2_flag == 1){
		  toggle7SEG(2);
		  setTimer_EN2(1000);
	  }
	  if (timer_EN3_flag == 1){
		  toggle7SEG(3);
		  setTimer_EN3(1000);
	  }

	  if (timer_MatrixBuffer_flag == 1){
		  displayLEDMatrix(index_led_matrix++);
		  if (index_led_matrix >= MAX_LED_MATRIX){
			  index_led_matrix = 0;
		  }
		  setTimer_MatrixBuffer(10);
	  }
	/* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEG3_Pin SEG4_Pin SEG5_Pin
                           SEG6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  timerRun();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
