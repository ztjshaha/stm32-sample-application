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
	int taskStatus = 0;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t u_buf[256];
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for stallCheck */
osThreadId_t stallCheckHandle;
const osThreadAttr_t stallCheck_attributes = {
  .name = "stallCheck",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for MotorDeviceMutex */
osMutexId_t MotorDeviceMutexHandle;
const osMutexAttr_t MotorDeviceMutex_attributes = {
  .name = "MotorDeviceMutex"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void stallCheckTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of MotorDeviceMutex */
  MotorDeviceMutexHandle = osMutexNew(&MotorDeviceMutex_attributes);

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

  /* creation of stallCheck */
  stallCheckHandle = osThreadNew(stallCheckTask, NULL, &stallCheck_attributes);

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

	  vTaskDelay(pdMS_TO_TICKS(50));
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_stallCheckTask */
/**
* @brief Function implementing the stallCheck thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_stallCheckTask */
void stallCheckTask(void *argument)
{
  /* USER CODE BEGIN stallCheckTask */

  /* Infinite loop */
  for(;;)
  {

	  	  emmV5ReadSysParams(&motor0,S_Conf);
	  	vTaskDelay(pdMS_TO_TICKS(5000));
	  	  if(emmV5ReadSysParams(&motor0,S_FLAG) == SDK_OK)
	  	  {
	  		printf("ReadSysParams success~ \n");
	  	  }
		  while( motor0.status.SM_STALLPRO == 0)
		  {
			  if(emmV5EnControl(&motor0, 1, 0) == SDK_OK)
			  {
				  printf("emmV5EnControl success~ \n");
			  }
			  if(emmV5PosControl(&motor0,0,500,200,railLength,0,0) == SDK_OK)
			  {
			  		printf("emmV5PosControl success~ \n");
			  }
			  vTaskDelay(pdMS_TO_TICKS(5000));

		  	  if(emmV5ReadSysParams(&motor0,S_FLAG) == SDK_OK)
		  	  {
		  		printf("ReadSysParams success~ \n");
		  	  }

		  }
		  if(emmV5ClearStallPro(&motor0) == SDK_OK)
		  {
			  printf("emmV5ClearStallPro success~ \n");
		  }
		  if(emmV5EnControl(&motor0, 0, 0) == SDK_OK)
		  {
			  printf("emmV5DisControl success~ \n");
		  }

		  emmV5ReadSysParams(&motor0,S_FLAG);
  	  	  if( motor0.status.SM_EN == 0){
  	  		 	  	  emmV5EnControl(&motor0, 1, 0);
  	  		  		  emmV5PosControl(&motor0,1,1500,200,railLength/2,0,0);
  	  		  	vTaskDelay(pdMS_TO_TICKS(5000));
  		  }
  	  	  vTaskDelete(NULL);
	  vTaskDelay(pdMS_TO_TICKS(50));
  }
  /* USER CODE END stallCheckTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
