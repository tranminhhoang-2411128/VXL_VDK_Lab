/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define NS_RED_Pin GPIO_PIN_4
#define NS_RED_GPIO_Port GPIOA
#define NS_YELLOW_Pin GPIO_PIN_5
#define NS_YELLOW_GPIO_Port GPIOA
#define NS_GREEN_Pin GPIO_PIN_6
#define NS_GREEN_GPIO_Port GPIOA
#define EW_RED_Pin GPIO_PIN_7
#define EW_RED_GPIO_Port GPIOA
#define NS_A_Pin GPIO_PIN_0
#define NS_A_GPIO_Port GPIOB
#define NS_B_Pin GPIO_PIN_1
#define NS_B_GPIO_Port GPIOB
#define NS_C_Pin GPIO_PIN_2
#define NS_C_GPIO_Port GPIOB
#define EW_D_Pin GPIO_PIN_10
#define EW_D_GPIO_Port GPIOB
#define EW_E_Pin GPIO_PIN_11
#define EW_E_GPIO_Port GPIOB
#define EW_F_Pin GPIO_PIN_12
#define EW_F_GPIO_Port GPIOB
#define EW_G_Pin GPIO_PIN_13
#define EW_G_GPIO_Port GPIOB
#define EW_YELLOW_Pin GPIO_PIN_8
#define EW_YELLOW_GPIO_Port GPIOA
#define EW_GREEN_Pin GPIO_PIN_9
#define EW_GREEN_GPIO_Port GPIOA
#define NS_D_Pin GPIO_PIN_3
#define NS_D_GPIO_Port GPIOB
#define NS_E_Pin GPIO_PIN_4
#define NS_E_GPIO_Port GPIOB
#define NS_F_Pin GPIO_PIN_5
#define NS_F_GPIO_Port GPIOB
#define NS_G_Pin GPIO_PIN_6
#define NS_G_GPIO_Port GPIOB
#define EW_A_Pin GPIO_PIN_7
#define EW_A_GPIO_Port GPIOB
#define EW_B_Pin GPIO_PIN_8
#define EW_B_GPIO_Port GPIOB
#define EW_C_Pin GPIO_PIN_9
#define EW_C_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
