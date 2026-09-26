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

/* USER CODE BEGIN PV */
static const int SevenSEG_LAT[10] = { //abcdefg
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
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void display7SEG(int num);
void display7SEG_NS(int num);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7SEG_EW(int num)
{
	int bit = SevenSEG_LAT[num];
	//Bitmask to check: bit & (1 >> position), If = 0, returns 0, returns 2^position otherwise

	HAL_GPIO_WritePin(EW_A_GPIO_Port, EW_A_Pin, ((bit & (1 << 6)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);//MSB(a)
	HAL_GPIO_WritePin(EW_B_GPIO_Port, EW_B_Pin, ((bit & (1 << 5)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(EW_C_GPIO_Port, EW_C_Pin, ((bit & (1 << 4)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(EW_D_GPIO_Port, EW_D_Pin, ((bit & (1 << 3)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(EW_E_GPIO_Port, EW_E_Pin, ((bit & (1 << 2)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(EW_F_GPIO_Port, EW_F_Pin, ((bit & (1 << 1)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(EW_G_GPIO_Port, EW_G_Pin, ((bit & (1 << 0)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);//LSB(g)
}

void display7SEG(int num)
{
    int bit = SevenSEG_LAT[num];

    HAL_GPIO_WritePin(NS_A_GPIO_Port, NS_A_Pin, ((bit & (1 << 6)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NS_B_GPIO_Port, NS_B_Pin, ((bit & (1 << 5)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NS_C_GPIO_Port, NS_C_Pin, ((bit & (1 << 4)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NS_D_GPIO_Port, NS_D_Pin, ((bit & (1 << 3)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NS_E_GPIO_Port, NS_E_Pin, ((bit & (1 << 2)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NS_F_GPIO_Port, NS_F_Pin, ((bit & (1 << 1)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(NS_G_GPIO_Port, NS_G_Pin, ((bit & (1 << 0)) > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int state_NS = 0; //0 for RED, 1 for YELLOW, 2 for GREEN
	int state_EW = 2;
	int count_NS = 5;
	int count_EW = 3;
	const int state_count[3] = {5, 2, 3};
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	//North-South light
	if (count_NS <= 0)
	{
		switch (state_NS)
		{
			case 0:
				state_NS = 2;
				break;
			case 1:
				state_NS = 0;
				break;
			case 2:
				state_NS = 1;
				break;
		}
		count_NS = state_count[state_NS];
	}
	count_NS--;

	//East-West light
	if (count_EW <= 0)
	{
		switch (state_EW)
		{
			case 0:
				state_EW = 2;
				break;
			case 1:
				state_EW = 0;
				break;
			case 2:
				state_EW = 1;
				break;
		}
		count_EW = state_count[state_EW];
	}
	count_EW--;

	if (count_NS >= 0)
	{
		switch (state_NS)
		{
			case 0:
				HAL_GPIO_WritePin(NS_RED_GPIO_Port, NS_RED_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(NS_YELLOW_GPIO_Port, NS_YELLOW_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(NS_GREEN_GPIO_Port, NS_GREEN_Pin, GPIO_PIN_SET);
				break;
			case 1:
				HAL_GPIO_WritePin(NS_RED_GPIO_Port, NS_RED_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(NS_YELLOW_GPIO_Port, NS_YELLOW_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(NS_GREEN_GPIO_Port, NS_GREEN_Pin, GPIO_PIN_SET);
				break;
			case 2:
				HAL_GPIO_WritePin(NS_RED_GPIO_Port, NS_RED_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(NS_YELLOW_GPIO_Port, NS_YELLOW_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(NS_GREEN_GPIO_Port, NS_GREEN_Pin, GPIO_PIN_RESET);
				break;
		}
		display7SEG(count_NS + 1);
	}

	if (count_EW >= 0)
	{
		switch (state_EW)
		{
			case 0:
				HAL_GPIO_WritePin(EW_RED_GPIO_Port, EW_RED_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(EW_YELLOW_GPIO_Port, EW_YELLOW_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EW_GREEN_GPIO_Port, EW_GREEN_Pin, GPIO_PIN_SET);
				break;
			case 1:
				HAL_GPIO_WritePin(EW_RED_GPIO_Port, EW_RED_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EW_YELLOW_GPIO_Port, EW_YELLOW_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(EW_GREEN_GPIO_Port, EW_GREEN_Pin, GPIO_PIN_SET);
				break;
			case 2:
				HAL_GPIO_WritePin(EW_RED_GPIO_Port, EW_RED_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EW_YELLOW_GPIO_Port, EW_YELLOW_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(EW_GREEN_GPIO_Port, EW_GREEN_Pin, GPIO_PIN_RESET);
				break;
		}
		display7SEG_EW(count_EW + 1);
	}
	HAL_Delay(1000);
    /* USER CODE END WHILE */
  }
    /* USER CODE BEGIN 3 */
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
  HAL_GPIO_WritePin(GPIOA, NS_RED_Pin|NS_YELLOW_Pin|NS_GREEN_Pin|EW_RED_Pin
                          |EW_YELLOW_Pin|EW_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, NS_A_Pin|NS_B_Pin|NS_C_Pin|EW_D_Pin
                          |EW_E_Pin|EW_F_Pin|EW_G_Pin|NS_D_Pin
                          |NS_E_Pin|NS_F_Pin|NS_G_Pin|EW_A_Pin
                          |EW_B_Pin|EW_C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : NS_RED_Pin NS_YELLOW_Pin NS_GREEN_Pin EW_RED_Pin
                           EW_YELLOW_Pin EW_GREEN_Pin */
  GPIO_InitStruct.Pin = NS_RED_Pin|NS_YELLOW_Pin|NS_GREEN_Pin|EW_RED_Pin
                          |EW_YELLOW_Pin|EW_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : NS_A_Pin NS_B_Pin NS_C_Pin EW_D_Pin
                           EW_E_Pin EW_F_Pin EW_G_Pin NS_D_Pin
                           NS_E_Pin NS_F_Pin NS_G_Pin EW_A_Pin
                           EW_B_Pin EW_C_Pin */
  GPIO_InitStruct.Pin = NS_A_Pin|NS_B_Pin|NS_C_Pin|EW_D_Pin
                          |EW_E_Pin|EW_F_Pin|EW_G_Pin|NS_D_Pin
                          |NS_E_Pin|NS_F_Pin|NS_G_Pin|EW_A_Pin
                          |EW_B_Pin|EW_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
