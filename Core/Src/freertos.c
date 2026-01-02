/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

#include "ssd1306.h"
#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"

#include "MyFunctions.h"
#include "ClassSnake.h"

#include "adc.h"
#include "queue.h"
#include <stdio.h>
#include "semphr.h"
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
Snake gSnakeObj;
Snake *mySnake = &gSnakeObj;

volatile uint16_t adc_buf[2];

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for GameLogic */
osThreadId_t GameLogicHandle;
const osThreadAttr_t GameLogic_attributes = {
  .name = "GameLogic",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for Stick */
osThreadId_t StickHandle;
const osThreadAttr_t Stick_attributes = {
  .name = "Stick",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow2,
};
/* Definitions for Screen */
osThreadId_t ScreenHandle;
const osThreadAttr_t Screen_attributes = {
  .name = "Screen",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Command */
osMessageQueueId_t CommandHandle;
const osMessageQueueAttr_t Command_attributes = {
  .name = "Command"
};
/* Definitions for MutexForScreen */
osMutexId_t MutexForScreenHandle;
const osMutexAttr_t MutexForScreen_attributes = {
  .name = "MutexForScreen"
};
/* Definitions for ContinueGame */
osSemaphoreId_t ContinueGameHandle;
const osSemaphoreAttr_t ContinueGame_attributes = {
  .name = "ContinueGame"
};
/* Definitions for NewScreen */
osSemaphoreId_t NewScreenHandle;
const osSemaphoreAttr_t NewScreen_attributes = {
  .name = "NewScreen"
};
/* Definitions for GameOver */
osSemaphoreId_t GameOverHandle;
const osSemaphoreAttr_t GameOver_attributes = {
  .name = "GameOver"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartGameLogic(void *argument);
void StartStick(void *argument);
void StartScreen(void *argument);

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
  /* creation of MutexForScreen */
  MutexForScreenHandle = osMutexNew(&MutexForScreen_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of ContinueGame */
  ContinueGameHandle = osSemaphoreNew(1, 1, &ContinueGame_attributes);

  /* creation of NewScreen */
  NewScreenHandle = osSemaphoreNew(1, 1, &NewScreen_attributes);

  /* creation of GameOver */
  GameOverHandle = osSemaphoreNew(1, 1, &GameOver_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of Command */
  CommandHandle = osMessageQueueNew (1, sizeof(uint16_t), &Command_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of GameLogic */
  GameLogicHandle = osThreadNew(StartGameLogic, NULL, &GameLogic_attributes);

  /* creation of Stick */
  StickHandle = osThreadNew(StartStick, NULL, &Stick_attributes);

  /* creation of Screen */
  ScreenHandle = osThreadNew(StartScreen, NULL, &Screen_attributes);

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
    osDelay(10000);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartGameLogic */
/**
* @brief Function implementing the GameLogic thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGameLogic */
void StartGameLogic(void *argument)
{
  for(;;)
  {
    // Game-over state: wait for user-triggered restart event
    if(mySnake->state == 0)
    {
      if(xSemaphoreTake(ContinueGameHandle, portMAX_DELAY) == pdTRUE)
      {
        if(xSemaphoreTake(MutexForScreenHandle, portMAX_DELAY) == pdTRUE)
        {
          Snake_Restart(mySnake);          // Reinitialise game state
          xSemaphoreGive(NewScreenHandle); // Trigger screen refresh
          xSemaphoreGive(MutexForScreenHandle);
        }
      }
    }
    else
    {
      // Receive latest direction command
      uint16_t dir = 0;
      if (xQueueReceive(CommandHandle, &dir, 0) == pdTRUE)
      {
        switch(dir)
        {
          case 1: Snake_SetDir(mySnake, dUp);    break;
          case 2: Snake_SetDir(mySnake, dDown);  break;
          case 3: Snake_SetDir(mySnake, dLeft);  break;
          case 4: Snake_SetDir(mySnake, dRight); break;
        }
      }

      // Update shared game state
      if(xSemaphoreTake(MutexForScreenHandle, portMAX_DELAY) == pdTRUE)
      {
        Snake_Move(mySnake);
        xSemaphoreGive(MutexForScreenHandle);
      }

      xSemaphoreGive(NewScreenHandle);

      // Signal game-over event
      if(mySnake->state == 0)
      {
        xSemaphoreGive(GameOverHandle);
        osDelay(1000);
        xSemaphoreTake(ContinueGameHandle, 0);
      }
    }

    osDelay(150);
  }

  /* USER CODE END StartGameLogic */
}

/* USER CODE BEGIN Header_StartStick */
/**
* @brief Function implementing the Stick thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartStick */
void StartStick(void *argument)
{
  for(;;)
  {
    uint16_t dir = 0;

    // Get the direction based on the threshold
    if(adc_buf[0] < 1000)
    {
      dir = 1;
      xQueueOverwrite(CommandHandle, &dir); // Keep only latest input
      xSemaphoreGive(ContinueGameHandle);   // Also used to restart game
    }
    else if(adc_buf[0] > 3000)
    {
      dir = 2;
      xQueueOverwrite(CommandHandle, &dir);
      xSemaphoreGive(ContinueGameHandle);
    }
    else if(adc_buf[1] < 1000)
    {
      dir = 3;
      xQueueOverwrite(CommandHandle, &dir);
      xSemaphoreGive(ContinueGameHandle);
    }
    else if(adc_buf[1] > 3000)
    {
      dir = 4;
      xQueueOverwrite(CommandHandle, &dir);
      xSemaphoreGive(ContinueGameHandle);
    }

    osDelay(10);
  }

  /* USER CODE END StartStick */
}

/* USER CODE BEGIN Header_StartScreen */
/**
* @brief Function implementing the Screen thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartScreen */
void StartScreen(void *argument)
{
  for(;;)
  {
    // Event-driven screen update
    if(xSemaphoreTake(NewScreenHandle, portMAX_DELAY) == pdTRUE)
    {
      char str[20];

      // Read shared snake and set the screen buffer
      if(xSemaphoreTake(MutexForScreenHandle, portMAX_DELAY) == pdTRUE)
      {
        sprintf(str, "Score is %d", mySnake->bodyLength);

        ssd1306_Fill(Black);
        ssd1306_SetCursor(0, 0);
        ssd1306_WriteString(str, Font_11x18, White);

        int x = mySnake->screenHeight;
        int y = mySnake->screenLength;

        for(int i = 0; i < x; i++)
        {
          for(int j = 0; j < y; j++)
          {
            if(mySnake->screen[i][j] != 0)
            {
              SetBigPixiv(j, i, 1);
            }
          }
        }

        xSemaphoreGive(MutexForScreenHandle);
      }

      // Display game-over message if signalled
      if (xSemaphoreTake(GameOverHandle, 0) == pdTRUE)
      {
        ssd1306_SetCursor(0, 16);
        ssd1306_WriteString("Game Over", Font_11x18, White);
      }

      // Update screen
      ssd1306_UpdateScreen();
    }

    osDelay(10);
  }

  /* USER CODE END StartScreen */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

