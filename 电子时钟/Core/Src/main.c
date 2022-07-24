/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "ssd1306.h"
#include "ssd1306_tests.h"
#include <stdbool.h>
#include <stdio.h>
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
I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
int clockmode = 0;
int second = 0;
int minute = 0;
int hour = 0;
int year = 2022;
int month = 5;
int date = 29;
int alarm1[3]={0,0,0},alarm2[3]={0,0,0},alarm3[3]={0,0,0};
int alarm=0;
char line1[12],line2[12],line3[12];
int twinkle = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void mode_check();
void oled_show();
void show_time();
void show_calendar();
void show_alarm();
void show_set();
void show_error();
int check_date();
int check_sw();
void set_date();
void store_time();
void read_time();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2C2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  ssd1306_Init();
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_Base_Start_IT(&htim2);
  read_time();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  mode_check();
	  oled_show();
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 1199;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 59999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

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
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 1199;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 29999;
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
  if (HAL_TIM_OC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC4 PC5 PC6 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SW4_Pin SW3_Pin */
  GPIO_InitStruct.Pin = SW4_Pin|SW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PE14 PE15 PE0 PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : SW2_Pin SW1_Pin */
  GPIO_InitStruct.Pin = SW2_Pin|SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void mode_check(){
	int sw = check_sw();
	if(sw == 0)return;
	if(sw == 1){
		if(clockmode == 0 || clockmode == 1){
			clockmode++;
		}
		else if(clockmode == 2)clockmode = 0;
	}

	//change the alarm being displayed
	if(clockmode == 2){
		if(sw == 3)alarm = 0;
		if(sw == 2)alarm = 1;
	}

	//setmode
	if(sw == 4){
		if(clockmode == 0){
			//set_time
			clockmode = 3;
		}
		else if(clockmode == 1){
			//set_calendar
			clockmode = 4;
		}

		else if(clockmode == 2){
			//set alarm
			clockmode = 5;
		}else if(clockmode == 3){
			store_time();
			clockmode = 0;
		}
		else if(clockmode == 4){
			store_time();
			clockmode = 1;
		}
		else if(clockmode == 5){
			store_time();
			clockmode = 2;
		}
	}
	return;
}

void oled_show(){
	//clock mode
	if(clockmode == 0){
		show_time();
	}
	//calendar mode
	else if(clockmode == 1){
		show_calendar();
	}
	//alarm mode
	else if(clockmode == 2){
		show_alarm();
	}
	//set mode
	else if(clockmode == 3 || clockmode == 4 || clockmode == 5){
		show_set();
	}
	//error mode
	else if(clockmode == 6){
		show_error();
	}
	//unnormal
	else {
		clockmode = 0;
	}

	ssd1306_Fill(Black);
	ssd1306_SetCursor(2,0);
	ssd1306_WriteString(line1, Font_11x18, White);
	ssd1306_SetCursor(2,18);
	ssd1306_WriteString(line2, Font_11x18, White);
	ssd1306_SetCursor(2,36);
	ssd1306_WriteString(line3, Font_11x18, White);
	ssd1306_UpdateScreen();
	return;
}

void show_time(){
	sprintf(line1,"    time   ");
	sprintf(line2," %2d:%2d:%2d ",hour,minute,second);
	sprintf(line3,"           ");
}

void show_alarm(){
	sprintf(line1,"   alarm   ");
	if(alarm == 0){
		if(alarm1[0]) sprintf(line2,"1.%2d:%2d  ON",alarm1[1],alarm1[2]);
		else sprintf(line2,"1.%2d:%2d OFF",alarm1[1],alarm1[2]);
		if(alarm2[0]) sprintf(line3,"2.%2d:%2d  ON",alarm2[1],alarm2[2]);
		else sprintf(line3,"2.%2d:%2d OFF",alarm2[1],alarm2[2]);
	}

	else{
		if(alarm2[0]) sprintf(line2,"2.%2d:%2d  ON",alarm2[1],alarm2[2]);
		else sprintf(line2,"2.%2d:%2d OFF",alarm2[1],alarm2[2]);
		if(alarm3[0]) sprintf(line3,"3.%2d:%2d  ON",alarm3[1],alarm3[2]);
		else sprintf(line3,"3.%2d:%2d OFF",alarm3[1],alarm3[2]);
	}
}

void show_calendar(){
	sprintf(line1,"  calendar ");
	sprintf(line2,"%4d.%2d.%2d",year,month,date);
	sprintf(line3,"           ");
}

void show_set(int set){
	int sw = check_sw();
	static int unit_time = 0;
	static int unit_alarm1 = 0;
	static int unit_alarm2 = 0;
	static int unit_calendar = 0;


	//set time
	if(clockmode == 3){
		if(sw == 1){
			if(unit_time < 2) unit_time++;
			else unit_time = 0;
		}
		if(sw == 4){
			unit_time = 0;
		}
		sprintf(line1,"    time   ");

		//set time of hour
		if(unit_time == 0){
			if(twinkle == 0)sprintf(line2," %2d:%2d:%2d ",hour,minute,second);
			else sprintf(line2,"   :%2d:%2d ",minute,second);
			if(sw == 3){
				if(hour < 24)hour++;
				else hour = 0;
			}
			else if(sw == 2){
				if(hour > 0)hour--;
				else hour = 0;
			}
		}

		//set time of minute
		else if(unit_time == 1){
			if(twinkle == 0)sprintf(line2," %2d:%2d:%2d ",hour,minute,second);
			else sprintf(line2," %2d:  :%2d ",hour,second);
			if(sw == 3){
				if(minute < 60)minute++;
				else minute = 0;
			}
			else if(sw == 2){
				if(minute > 0)minute--;
				else minute = 0;
			}
		}

		//set time of second
		else if(unit_time == 2){
			if(twinkle == 0)sprintf(line2," %2d:%2d:%2d ",hour,minute,second);
			else sprintf(line2," %2d:%2d:   ",hour,minute);
			if(sw == 3){
				second = 0;
				minute++;
				if(minute == 60){
					minute = 0;
					hour++;
				}
			}
			else if(sw == 2){
				second = 0;
			}
		}
		sprintf(line3,"           ");

	}

	//set calendar
	else if(clockmode == 4){
		if(sw == 1){
			if(unit_calendar < 2) unit_calendar++;
			else unit_calendar = 0;
		}
		if(sw == 4){
			unit_calendar = 0;
		}
		sprintf(line1,"  calendar ");

		//set year
		if(unit_calendar == 0){
			if(twinkle == 0)sprintf(line2,"%4d.%2d.%2d",year,month,date);
			else sprintf(line2,"    .%2d.%2d",month,date);
			if(sw == 3){
				year++;
			}
			else if(sw == 2){
				year--;
			}
		}

		//set month
		else if(unit_calendar == 1){
			if(twinkle == 0)sprintf(line2,"%4d.%2d.%2d",year,month,date);
			else sprintf(line2,"%4d.  .%2d",year,date);
			if(sw == 3){
				if(month < 12)month++;
				else month = 12;
			}
			else if(sw == 2){
				if(month > 1)month--;
				else month = 1;
			}
		}

		//set date
		else if(unit_calendar == 2){
			if(twinkle == 0)sprintf(line2,"%4d.%2d.%2d",year,month,date);
			else sprintf(line2,"%4d.%2d.  ",year,month);
			if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
				if(sw == 3){
					if(date <31) date ++;
					else date = 1;
				}
				else if(sw == 2){
					if(date > 1)date--;
					else date = 1;
				}
			}
			else if(month == 4 || month == 6 || month == 9 || month == 11){
				if(sw == 3){
					if(date <30) date ++;
					else date = 1;
				}
				else if(sw == 2){
					if(date > 1)date--;
					else date = 1;
				}
			}
			else if(month == 2){
				if((year % 400 == 0) || ((year % 4 == 0) && !(year % 100 == 0))){
					if(sw == 3){
						if(date <29) date ++;
						else date = 1;
					}
					else if(sw == 2){
						if(date > 1)date--;
						else date = 1;
					}
				}
				else {
					if(sw == 3){
						if(date <28) date ++;
						else date = 1;
					}
					else if(sw == 2){
						if(date > 1)date--;
						else date = 1;
					}
				}
			}
		}
		sprintf(line3,"           ");
	}

	//set alarm
	else if(clockmode == 5){
		if(sw == 1){
			if(unit_alarm2 < 2){
				unit_alarm2++;
			}
			else{
				unit_alarm2 = 0;
				unit_alarm1++;
			}
			if(unit_alarm1 > 2){
				unit_alarm1 = 0;
			}
		}
		if(sw == 4){
			unit_alarm1 = 0;
			unit_alarm2 = 0;
		}

		if(unit_alarm1 == 0){//set alarm1
			if(alarm2[0])sprintf(line3,"2.%2d:%2d  ON",alarm2[1],alarm2[2]);
			else sprintf(line3,"2.%2d:%2d OFF",alarm2[1],alarm2[2]);
			if(unit_alarm2 == 0){
				if(twinkle == 0){
					if(alarm1[0])sprintf(line2,"1.%2d:%2d  ON",alarm1[1],alarm1[2]);
					else sprintf(line2,"1.%2d:%2d OFF",alarm1[1],alarm1[2]);
				}
				else {
					if(alarm1[0])sprintf(line2,"1.  :%2d  ON",alarm1[2]);
					else sprintf(line2,"1.  :%2d OFF",alarm1[2]);
				}

				if(sw == 3){
					if(alarm1[1] < 24)alarm1[1]++;
					else alarm1[1] = 0;
				}
				else if(sw == 2){
					if(alarm1[1] > 0)alarm1[1]--;
					else alarm1[1] = 0;
				}
			}
			else if(unit_alarm2 == 1){
				if(twinkle == 0){
					if(alarm1[0])sprintf(line2,"1.%2d:%2d  ON",alarm1[1],alarm1[2]);
					else sprintf(line2,"1.%2d:%2d OFF",alarm1[1],alarm1[2]);
				}
				else {
					if(alarm1[0])sprintf(line2,"1.%2d:    ON",alarm1[1]);
					else sprintf(line2,"1.%2d:   OFF",alarm1[1]);
				}

				if(sw == 3){
					if(alarm1[2] < 60)alarm1[2]++;
					else alarm1[2] = 0;
				}
				else if(sw == 2){
					if(alarm1[2] > 0)alarm1[2]--;
					else alarm1[2] = 0;
				}
			}
			else if(unit_alarm2 == 2){
				if(twinkle == 0){
					if(alarm1[0])sprintf(line2,"1.%2d:%2d  ON",alarm1[1],alarm1[2]);
					else sprintf(line2,"1.%2d:%2d OFF",alarm1[1],alarm1[2]);
				}
				else {
					if(alarm1[0])sprintf(line2,"1.%2d:%2d    ",alarm1[1], alarm1[2]);
					else sprintf(line2,"1.%2d:%2d    ",alarm1[1], alarm1[2]);
				}

				if(sw == 3){
					if(alarm1[0] == 0)alarm1[0]++;
					else alarm1[0] = 0;
				}
				else if(sw == 2){
					if(alarm1[0] > 0)alarm1[0]--;
					else alarm1[0] = 0;
				}
			}
		}
		else if(unit_alarm1 == 1){//set alarm2
			if(alarm3[0])sprintf(line3,"3.%2d:%2d  ON",alarm3[1],alarm3[2]);
			else sprintf(line3,"3.%2d:%2d OFF",alarm3[1],alarm3[2]);
			if(unit_alarm2 == 0){
				if(twinkle == 0){
					if(alarm2[0])sprintf(line2,"2.%2d:%2d  ON",alarm2[1],alarm2[2]);
					else sprintf(line2,"2.%2d:%2d OFF",alarm2[1],alarm2[2]);
				}
				else {
					if(alarm2[0])sprintf(line2,"2.  :%2d  ON",alarm2[2]);
					else sprintf(line2,"2.  :%2d OFF",alarm2[2]);
				}

				if(sw == 3){
					if(alarm2[1] < 24)alarm2[1]++;
					else alarm2[1] = 0;
				}
				else if(sw == 2){
					if(alarm2[1] > 0)alarm2[1]--;
					else alarm2[1] = 0;
				}
			}
			else if(unit_alarm2 == 1){
				if(twinkle == 0){
					if(alarm2[0])sprintf(line2,"2.%2d:%2d  ON",alarm2[1],alarm2[2]);
					else sprintf(line2,"2.%2d:%2d OFF",alarm2[1],alarm2[2]);
				}
				else {
					if(alarm2[0])sprintf(line2,"2.%2d:    ON",alarm2[1]);
					else sprintf(line2,"2.%2d:   OFF",alarm2[1]);
				}

				if(sw == 3){
					if(alarm2[2] < 60)alarm2[2]++;
					else alarm2[2] = 0;
				}
				else if(sw == 2){
					if(alarm2[2] > 0)alarm2[2]--;
					else alarm2[2] = 0;
				}
			}
			else if(unit_alarm2 == 2){
				if(twinkle == 0){
					if(alarm2[0])sprintf(line2,"2.%2d:%2d  ON",alarm2[1],alarm2[2]);
					else sprintf(line2,"2.%2d:%2d OFF",alarm2[1],alarm2[2]);
				}
				else {
					if(alarm2[0])sprintf(line2,"2.%2d:%2d    ",alarm2[1], alarm2[2]);
					else sprintf(line2,"2.%2d:%2d    ",alarm2[1], alarm2[2]);
				}

				if(sw == 3){
					if(alarm2[0] == 0)alarm2[0]++;
					else alarm2[0] = 0;
				}
				else if(sw == 2){
					if(alarm2[0] > 0)alarm2[0]--;
					else alarm2[0] = 0;
				}
			}
		}
		else if(unit_alarm1 == 2){//set alarm3
			if(alarm2[0])sprintf(line2,"2.%2d:%2d  ON",alarm2[1],alarm2[2]);
			else sprintf(line2,"2.%2d:%2d OFF",alarm2[1],alarm2[2]);
			if(unit_alarm2 == 0){
				if(twinkle == 0){
					if(alarm3[0])sprintf(line3,"3.%2d:%2d  ON",alarm3[1],alarm3[2]);
					else sprintf(line3,"3.%2d:%2d OFF",alarm3[1],alarm3[2]);
				}
				else {
					if(alarm3[0])sprintf(line3,"3.  :%2d  ON",alarm3[2]);
					else sprintf(line3,"3.  :%2d OFF",alarm3[2]);
				}

				if(sw == 3){
					if(alarm3[1] < 24)alarm3[1]++;
					else alarm3[1] = 0;
				}
				else if(sw == 2){
					if(alarm3[1] > 0)alarm3[1]--;
					else alarm3[1] = 0;
				}
			}
			else if(unit_alarm2 == 1){
				if(twinkle == 0){
					if(alarm3[0])sprintf(line3,"3.%2d:%2d  ON",alarm3[1],alarm3[2]);
					else sprintf(line3,"3.%2d:%2d OFF",alarm3[1],alarm3[2]);
				}
				else {
					if(alarm3[0])sprintf(line3,"3.%2d:    ON",alarm3[1]);
					else sprintf(line3,"3.%2d:   OFF",alarm3[1]);
				}

				if(sw == 3){
					if(alarm3[2] < 60)alarm3[2]++;
					else alarm3[2] = 0;
				}
				else if(sw == 2){
					if(alarm3[2] > 0)alarm3[2]--;
					else alarm3[2] = 0;
				}
			}
			else if(unit_alarm2 == 2){
				if(twinkle == 0){
					if(alarm3[0])sprintf(line3,"3.%2d:%2d  ON",alarm3[1],alarm3[2]);
					else sprintf(line3,"3.%2d:%2d OFF",alarm3[1],alarm3[2]);
				}
				else {
					if(alarm3[0])sprintf(line3,"3.%2d:%2d    ",alarm3[1], alarm3[2]);
					else sprintf(line3,"3.%2d:%2d    ",alarm3[1], alarm3[2]);
				}

				if(sw == 3){
					if(alarm3[0] == 0)alarm3[0]++;
					else alarm3[0] = 0;
				}
				else if(sw == 2){
					if(alarm3[0] > 0)alarm3[0]--;
					else alarm3[0] = 0;
				}
			}
		}

	}
}

void show_error(){
	sprintf(line1,"time error ");
	sprintf(line2,"           ");
	sprintf(line3,"           ");
}

int check_date(){
	return 0;
}


//check which sw is pressed
int check_sw(){
	//check if sw1 is pressed
	if(HAL_GPIO_ReadPin(GPIOD, SW1_Pin)){
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOD, SW1_Pin)){
			return 1;
		}
	}

	//check if sw2 is pressed
	if(HAL_GPIO_ReadPin(GPIOD, SW2_Pin)){
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOD, SW2_Pin)){
			return 2;
		}
	}

	//check if sw3 is pressed
	if(HAL_GPIO_ReadPin(GPIOB, SW3_Pin)){
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOB, SW3_Pin)){
			return 3;
		}
	}

	//check if sw4 is pressed
	if(HAL_GPIO_ReadPin(GPIOB, SW4_Pin)){
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOB, SW4_Pin)){
			return 4;
		}
	}
	return 0;
}

//set the date right
void set_date(){

}

//store the time to flash
void store_time(){
	uint32_t Robot_Num_Flash_Add = 0x08010000;

	FLASH_EraseInitTypeDef My_Flash;  //声明 FLASH_EraseInitTypeDef 结构体为 My_Flash
	HAL_FLASH_Unlock();               //解锁Flash

	My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;  //标明Flash执行页面只做擦除操作
	My_Flash.PageAddress = Robot_Num_Flash_Add;  //声明要擦除的地址
	My_Flash.NbPages = 1;                        //说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值
	uint32_t PageError = 0;                    //设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
	HAL_FLASHEx_Erase(&My_Flash, &PageError);  //调用擦除函数擦除

	int Write_Flash_Data[15] = {second, minute, hour, year, month, date, alarm1[0], alarm1[1], alarm1[2], alarm2[0], alarm2[1], alarm2[2], alarm3[0], alarm3[1], alarm3[2]};

		//对Flash进行烧写，FLASH_TYPEPROGRAM_HALFWORD 声明操作的Flash地址的16位的，此外还有32位跟64位的操作，自行翻查HAL库的定义即可
	for(uint32_t i = 0; i < 15; i++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Robot_Num_Flash_Add + i*32, Write_Flash_Data[i]);
	}

	HAL_FLASH_Lock();
}

//read the time from flash
void read_time(){
	uint32_t Robot_Num_Flash_Add = 0x08010000;
	second = (int)*(__IO uint32_t*)( Robot_Num_Flash_Add ); //*(__IO uint16_t *)是读取该地址的参数值,其值为16位数据,一次读取两个字节，*(__IO uint32_t *)就一次读4个字节
	minute = (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32);
	hour =   (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*2);
	year =   (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*3);
	month =  (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*4);
	date =   (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*5);
	alarm1[0] = (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*6);
	alarm1[1] = (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*7);
	alarm1[2] = (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*8);
	alarm2[0] = (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*9);
	alarm2[1] = (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*10);
	alarm2[2] = (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*11);
	alarm3[0] = (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*12);
	alarm3[1] = (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*13);
	alarm3[2] = (int)*(__IO uint32_t*)( Robot_Num_Flash_Add + 32*14);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    if(htim == (&htim2)){
    	if(twinkle == 0){
    		twinkle = 1;
    	}
    	else twinkle = 0;
    }

    if (htim == (&htim1))
    {
    	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_4);
    	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_5);
    	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_0);
    	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_1);
    	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_0);
    	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1);
    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
    	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
    	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
    	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
    	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_15);

    		second++;
    		if(second >= 60){
    			second = 0;
    			minute++;
    		}
    		if(minute>=60){
    			minute = 0;
    			hour++;
    		}
    		if(hour >= 24){
    			hour=0;
    			date++;
    			set_date();
    		}
    		if(second % 10 == 0){
    			store_time();
    		}
    }
    return;
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
