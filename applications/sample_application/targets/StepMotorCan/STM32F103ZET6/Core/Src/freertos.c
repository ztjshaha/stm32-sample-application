/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

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
/* USER CODE BEGIN Variables */
uint8_t u_buf[256];
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ledBlinkTask */
osThreadId_t ledBlinkTaskHandle;
const osThreadAttr_t ledBlinkTask_attributes = {
  .name = "ledBlinkTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for canTask */
osThreadId_t canTaskHandle;
const osThreadAttr_t canTask_attributes = {
  .name = "canTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void ledBlinkTask02(void *argument);
void canTask03(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of ledBlinkTask */
  ledBlinkTaskHandle = osThreadNew(ledBlinkTask02, NULL, &ledBlinkTask_attributes);

  /* creation of canTask */
  canTaskHandle = osThreadNew(canTask03, NULL, &canTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_ledBlinkTask02 */
/**
* @brief Function implementing the ledBlinkTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ledBlinkTask02 */
void ledBlinkTask02(void *argument)
{
  /* USER CODE BEGIN ledBlinkTask02 */
  /* Infinite loop */
  for(;;)
  {
	adiPrintf("Start Led toggle 01!\n");
	HAL_GPIO_TogglePin(led1_GPIO_Port, led1_Pin);
	HAL_GPIO_TogglePin(led0_GPIO_Port, led0_Pin);
	vTaskDelay(pdMS_TO_TICKS(1000));
    osDelay(1);
  }
  /* USER CODE END ledBlinkTask02 */
}

/* USER CODE BEGIN Header_canTask03 */
/**
* @brief Function implementing the canTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_canTask03 */
void canTask03(void *argument)
{
  /* USER CODE BEGIN canTask03 */
  /* Infinite loop */
  for(;;)
  {
	emmV5readMotorSpeed(0x01);
	osDelay(configTICK_RATE_HZ);
    osDelay(1);
  }
  /* USER CODE END canTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

