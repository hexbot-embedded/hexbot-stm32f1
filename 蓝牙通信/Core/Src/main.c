/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t state=0;
void ledset(void)
{
	int led_time=200;

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1);  //j0灯亮
	HAL_Delay(led_time);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, 1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 1);  //J1
	HAL_Delay(led_time);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, 0);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, 1);  //J2
	HAL_Delay(led_time);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, 0);  //J3
	HAL_Delay(led_time);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, 1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);  //J4
	HAL_Delay(led_time);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, 0);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, 1);  //J5
	HAL_Delay(led_time);

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, 0);


	for(int i=0;i<3;i++)
	{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, 1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, 1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, 1);
	HAL_Delay(led_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14,0);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15,0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3,0);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0,0);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, 0);
	HAL_Delay(led_time);
}
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
  unsigned char uRxDate=0;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  uint8_t  pwmVal=0;
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t f=0;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  if(HAL_UART_Receive(&huart2,&uRxDate, 1, 1000)==HAL_OK)
	 	           {
	 	           HAL_UART_Transmit(&huart2, &uRxDate, 1, 0xffff);
	 	           if(uRxDate==0x00){
	 	        	   state=0;
	 	           }
	 	           else if(uRxDate==0x01)
	 	           {
	 	        	   state=1;
	 	           }
	 	           else if(uRxDate==0x02){
	 	        	   state=2;
	 	           }
	 	           else if(uRxDate==0x03)
	 	           {
	 	        	   state=3;
	 	           }

	 	           }


	  switch(state)
	  {
	  case 0:
		  ledset();break;
	  case 1:
		  if(pwmVal < 40&&f==0){
		  			  pwmVal+=8;
		  			  if(pwmVal==40)
		  				  f=1;
		  			  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,pwmVal);
		  		  }
		  else{
		  			  pwmVal-=8;
		  			  if(pwmVal==0)
		  				  f=0;
		  			  __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,pwmVal);
		  		  }
		    break;
	  case 2:
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2,0);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3,0);
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0,0);
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1,0);break;
	  case 3:
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2,1);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3,0);
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0,1);
		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1,0);break;

	  }















	  /*
	  if(HAL_UART_Receive(&huart2,&uRxDate, 1, 1000)==HAL_OK)
	           {
	           HAL_UART_Transmit(&huart2, &uRxDate, 1, 0xffff);

	           if(uRxDate&0x01)
	           {
                    while(1)
                    {
	        	    for(int i=0;i<50;i++)
	        	     {
	        		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,1);
	        		  delay_us(1);
	        		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,0);
	        		  delay_us(19);
	        	     }
                     HAL_Delay(1);
	        	     for(int i=0;i<50;i++)
	        	     {
	        		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,1);
	        		  delay_us(2);
	        		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,0);
	        		  delay_us(18);
	        	     }
                    }
	           }


	           else if(uRxDate&0x02)
	           {

	           }

	           else if(uRxDate&0x03)
	           {

	           }

	           else if(uRxDate&0x04)
	           {

	           }

	           else
	           {
                ledset();
	           }

	           }

	  */







		  /*


     for(int i=0;i<200;i++)
     {
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,1);
	  delay_us(1);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,0);
	  delay_us(19);
     }

     for(int i=0;i<200;i++)
     {
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,1);
	  delay_us(2);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,0);
	  delay_us(18);
     }

 */



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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV8;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  htim1.Init.Prescaler = 999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 319;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  __HAL_TIM_DISABLE_OCxPRELOAD(&htim1, TIM_CHANNEL_2);
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
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 999;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 319;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  __HAL_TIM_DISABLE_OCxPRELOAD(&htim3, TIM_CHANNEL_2);
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC2 PC3 PC4 PC5
                           PC6 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

}

/* USER CODE BEGIN 4 */
void delay_us(uint16_t us)
{
	uint16_t differ=0xffff-us-5;
	HAL_TIM_Base_Start(&htim3);
	__HAL_TIM_SetCounter(&htim3,differ);
	while(differ<0xffff-5)
	{
		differ=__HAL_TIM_GET_COUNTER(&htim3);

	}

	HAL_TIM_Base_Stop(&htim3);
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
