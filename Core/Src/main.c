/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "MPU6050.h"
#include "tof.h"
#include "stdint.h"
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
  #define LENGTH 64
  #define UART_LINE_MAX 64
  uint8_t RxBuff[LENGTH];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
  void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
       
  
  HAL_UARTEx_ReceiveToIdle_IT (&huart3 ,RxBuff , LENGTH);
  printf ("当前已开启接收中断，等待数据发送！\r\n");
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
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
		int16_t acc_x,acc_y,acc_z,gy_x,gy_y,gy_z;
		Init_MPU ();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	
		  // HAL_Delay (10);
			// printf("readID\r\n");
			// uint8_t iic_ID = Single_ReadI2C(0x75);
			// HAL_Delay (500);
			// HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);
			// printf("MPU6050 ID = 0x%02X\r\n",iic_ID);
			// printf("获取数据\r\n");
			// acc_x= GetData(ACCEL_XOUT_H);
			// acc_y= GetData(ACCEL_YOUT_H);
			// acc_z= GetData(ACCEL_ZOUT_H);
			// gy_x= GetData(GYRO_XOUT_H);
			// gy_y= GetData(GYRO_YOUT_H);
			// gy_z= GetData(GYRO_ZOUT_H);
    
			// printf("ACC: \r\nX=%d\r\nY=%d\r\nZ=%d \r\n",acc_x,acc_y,acc_z);
			// printf("GYRO: \r\nX=%d\r\nY=%d\r\nZ=%d\r\n",gy_x,gy_y,gy_z);
			// HAL_Delay (2000);  
      //  printf("readID\r\n"); 
      //  tof_read_id();
			
      //HAL_Delay (10);
	    // HAL_UARTEx_RzEventCallback (&huart3, LENGTH);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

/* USER CODE BEGIN 4 */
int fputc (int ch, FILE *f)
{
	HAL_UART_Transmit (&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
	return ch;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART3)
    {
        uart_rx_byte(RxBuff[0]); 
        HAL_UART_Receive_IT(&huart3, RxBuff, 1);
        printf("Received byte: %cMM\r\n", RxBuff[0]);
    }
}














//  void HAL_UARTE3_RzEventCallback (UART_HandleTypeDef *huart, uint16_t Size)
//  {
//    if (huart->Instance==USART3)// 判断发生接收中断的串
//    {
//      printf ("\r\n 已经接收到不定长数据如下:");
//    }
//    HAL_UART_Transmit_IT (&huart3, RxBuff,Size);// 回显发送的数据
//    HAL_UARTEx_ReceiveToIdle_IT (&huart3, RxBuff,LENGTH);
//  }// 使能接收中断


// void HAL_UARTE1_RzEventCallback (UART_HandleTypeDef *huart, uint16_t Size)
// {
//   if (huart->Instance==USART1)// 判断发生接收中断的串 0
//   {
//     printf ("\r\n 已经接收到不定长数据如下:");
//   }
//   HAL_UART_Transmit_IT (&huart1, RxBuff,Size);// 回显发送的数据
//   HAL_UARTEx_ReceiveToIdle_IT (&huart1, RxBuff,LENGTH);
// }// 使能接收中断







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
#ifdef USE_FULL_ASSERT
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
