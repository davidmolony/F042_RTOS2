/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
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
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim17;

UART_HandleTypeDef huart2;

osThreadId defaultTaskHandle;
osThreadId helloWorldHandle;
/* USER CODE BEGIN PV */
uint16_t PWMHigh = 100;
uint16_t PWMLow = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM17_Init(void);
static void MX_TIM1_Init(void);
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart2, (unsigned char *)&ch, 2, 100);
    return ch;
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
  MX_USART2_UART_Init();
  MX_TIM17_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
HAL_TIM_Base_Start_IT(&htim17);

HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,5);
__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,5);
__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,5);



  /* USER CODE END 2 */

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
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of helloWorld */
  osThreadDef(helloWorld, StartTask02, osPriorityIdle, 0, 128);
  helloWorldHandle = osThreadCreate(osThread(helloWorld), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  printf("Hello World from startup");


  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 7;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 256;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
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
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 10;
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
  * @brief TIM17 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM17_Init(void)
{

  /* USER CODE BEGIN TIM17_Init 0 */

  /* USER CODE END TIM17_Init 0 */

  /* USER CODE BEGIN TIM17_Init 1 */

  /* USER CODE END TIM17_Init 1 */
  htim17.Instance = TIM17;
  htim17.Init.Prescaler = 479;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = 1000;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM17_Init 2 */

  /* USER CODE END TIM17_Init 2 */

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
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD3_Pin */
  GPIO_InitStruct.Pin = LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */
static int step=1;
uint32_t tmpccmrx = 0;
int hallStep =0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
hallStep = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)|(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)<<1)|(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)<<2);
//HAL_UART_Transmit(&huart2,(uint8_t) hallStep,2,5);
char lol[32];
sprintf(lol, "lol %u \r", (unsigned int)hallStep);
HAL_UART_Transmit(&huart2, (uint8_t*)lol, strlen(lol),5);
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
int tempARR=0;
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	   tempARR=htim17.Instance->ARR;
	  char lol[32];

	  	  	  	  sprintf(lol, "ARR= %u \r", (unsigned int)tempARR);
	  	  	  	  HAL_UART_Transmit(&huart2, (uint8_t*)lol, strlen(lol),5);
    osDelay(1000);
  }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the helloWorld thread.
* @param argument: Not used
* @retval None
*/
static uint16_t comPeriod=200;
static uint16_t comPeriod2=400;
static uint16_t maxSpd=20;


static int dirPeriod=0;
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */

  /* Infinite loop */
  for(;;)
  {
	  //HAL_UART_Transmit(&huart2, (uint8_t*)"Hello RTOS\r", 12,10);


	  if(comPeriod<50){
		  dirPeriod=1;
	  }
	  if(comPeriod>51){
		  dirPeriod=0;
	  }
	  if(dirPeriod==1){
		  comPeriod=comPeriod+1;
	  }
	  if(dirPeriod==0){
		  comPeriod=comPeriod-1;

	  }
	  if(comPeriod2>maxSpd){
		  comPeriod2=comPeriod2*0.99;
	  }
	  htim17.Instance->ARR=comPeriod2;

	//HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
    osDelay(10);
  }
  /* USER CODE END StartTask02 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM16 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM16) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim->Instance == TIM17) {
	  //HAL_UART_Transmit(&huart2, (uint8_t*)"Hello World\r", 13,10);

	  //char lol[32];
	  //sprintf(lol, "lol %u \r", (unsigned int)10);
	  //HAL_UART_Transmit(&huart2, (uint8_t*)lol, strlen(lol),5);

	  //This is where we put the switch statement for commuting the BLDC
	  switch(step){
	  case 1:
			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC2M;
			tmpccmrx &= ~TIM_CCMR1_CC2S;
			tmpccmrx |= TIM_OCMODE_FORCED_INACTIVE<<8;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER &= ~TIM_CCER_CC2E;  //disable
htim1.Instance->CCER &= ~TIM_CCER_CC2NE;  //disable

		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,PWMHigh);
		  //__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,100);
		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,PWMLow);

			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC1M;
			tmpccmrx &= ~TIM_CCMR1_CC1S;
			tmpccmrx |= TIM_OCMODE_PWM1;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC1E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC1NE;   //enable
		  	tmpccmrx = htim1.Instance->CCMR2;
            tmpccmrx &= ~TIM_CCMR2_OC3M;
            tmpccmrx &= ~TIM_CCMR2_CC3S;
            tmpccmrx |= TIM_OCMODE_PWM1;
htim1.Instance->CCMR2 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC3E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC3NE;   //enable
		  	  	  break;
	  case 2:
		   tmpccmrx = htim1.Instance->CCMR2;
		   tmpccmrx &= ~TIM_CCMR2_OC3M;
		   tmpccmrx &= ~TIM_CCMR2_CC3S;
		   tmpccmrx |= TIM_OCMODE_FORCED_INACTIVE;
htim1.Instance->CCMR2 = tmpccmrx;
htim1.Instance->CCER &= ~TIM_CCER_CC3E;  //disable
htim1.Instance->CCER &= ~TIM_CCER_CC3NE;  //disable

		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,PWMHigh);
		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,PWMLow);
		  //__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,200);

			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC1M;
			tmpccmrx &= ~TIM_CCMR1_CC1S;
			tmpccmrx |= TIM_OCMODE_PWM1;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC1E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC1NE;   //enable
			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC2M;
			tmpccmrx &= ~TIM_CCMR1_CC2S;
			tmpccmrx |= TIM_OCMODE_PWM1<<8;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC2E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC2NE;   //enable
		  	  	  break;
	  case 3:
			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC1M;
			tmpccmrx &= ~TIM_CCMR1_CC1S;
			tmpccmrx |= TIM_OCMODE_FORCED_INACTIVE;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER &= ~TIM_CCER_CC1E;  //disable
htim1.Instance->CCER &= ~TIM_CCER_CC1NE;  //disable

		  //__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,100);
		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,PWMLow);
		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,PWMHigh);

			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC2M;
			tmpccmrx &= ~TIM_CCMR1_CC2S;
			tmpccmrx |= TIM_OCMODE_PWM1<<8;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC2E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC2NE;   //enable
			tmpccmrx = htim1.Instance->CCMR2;
			tmpccmrx &= ~TIM_CCMR2_OC3M;
			tmpccmrx &= ~TIM_CCMR2_CC3S;
			tmpccmrx |= TIM_OCMODE_PWM1;
htim1.Instance->CCMR2 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC3E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC3NE;   //enable
		  		  break;
	  case 4:
			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC2M;
			tmpccmrx &= ~TIM_CCMR1_CC2S;
			tmpccmrx |= TIM_OCMODE_FORCED_INACTIVE<<8;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER &= ~TIM_CCER_CC2E;  //disable
htim1.Instance->CCER &= ~TIM_CCER_CC2NE;  //disable

		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,PWMLow);
		  //__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,200);
		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,PWMHigh);

			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC1M;
			tmpccmrx &= ~TIM_CCMR1_CC1S;
			tmpccmrx |= TIM_OCMODE_PWM1;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC1E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC1NE;   //enable
			tmpccmrx = htim1.Instance->CCMR2;
			tmpccmrx &= ~TIM_CCMR2_OC3M;
			tmpccmrx &= ~TIM_CCMR2_CC3S;
			tmpccmrx |= TIM_OCMODE_PWM1;
htim1.Instance->CCMR2 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC3E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC3NE;   //enable
		  		  break;
	  case 5:
		   tmpccmrx = htim1.Instance->CCMR2;
		   tmpccmrx &= ~TIM_CCMR2_OC3M;
		   tmpccmrx &= ~TIM_CCMR2_CC3S;
		   tmpccmrx |= TIM_OCMODE_FORCED_INACTIVE;
htim1.Instance->CCMR2 = tmpccmrx;
htim1.Instance->CCER &= ~TIM_CCER_CC3E;  //disable
htim1.Instance->CCER &= ~TIM_CCER_CC3NE;  //disable

		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,PWMLow);
		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,PWMHigh);
		  //__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,100);

			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC1M;
			tmpccmrx &= ~TIM_CCMR1_CC1S;
			tmpccmrx |= TIM_OCMODE_PWM1;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC1E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC1NE;   //enable
			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC2M;
			tmpccmrx &= ~TIM_CCMR1_CC2S;
			tmpccmrx |= TIM_OCMODE_PWM1<<8;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC2E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC2NE;   //enable
		  		  break;
	  case 6:
			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC1M;
			tmpccmrx &= ~TIM_CCMR1_CC1S;
			tmpccmrx |= TIM_OCMODE_FORCED_INACTIVE;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER &= ~TIM_CCER_CC1E;  //disable
htim1.Instance->CCER &= ~TIM_CCER_CC1NE;  //disable

		  //__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,200);
		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,PWMHigh);
		  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,PWMLow);

			tmpccmrx = htim1.Instance->CCMR1;
			tmpccmrx &= ~TIM_CCMR1_OC2M;
			tmpccmrx &= ~TIM_CCMR1_CC2S;
			tmpccmrx |= TIM_OCMODE_PWM1<<8;
htim1.Instance->CCMR1 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC2E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC2NE;   //enable
			tmpccmrx = htim1.Instance->CCMR2;
			tmpccmrx &= ~TIM_CCMR2_OC3M;
			tmpccmrx &= ~TIM_CCMR2_CC3S;
			tmpccmrx |= TIM_OCMODE_PWM1;
htim1.Instance->CCMR2 = tmpccmrx;
htim1.Instance->CCER |= TIM_CCER_CC3E;   //enable
htim1.Instance->CCER |= TIM_CCER_CC3NE;   //enable
		  		  break;
	  default:
		  HAL_UART_Transmit(&huart2, (uint8_t*)"shit\r", 7,10);


	  }
	  step = step+1;
	  if(step>6){step=1;
	  HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
}

	  //int tempARR=htim17.Instance->ARR;
	  	  	  //sprintf(lol, "ARR= %u \r", (unsigned int)tempARR);
	  	  	  //HAL_UART_Transmit(&huart2, (uint8_t*)lol, strlen(lol),5);

  }
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
