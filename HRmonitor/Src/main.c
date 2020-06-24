/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "crc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

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
char textTxBuffer[500];
uint8_t rawMpu[14];
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
    uint8_t mpuConfigTx, mpuConfigRx;
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
    MX_CRC_Init();
    MX_USB_DEVICE_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();
    MX_TIM3_Init();
    /* USER CODE BEGIN 2 */

    sprintf(textTxBuffer, "HRmonitor USART1 test\r");
    HAL_UART_Transmit(&huart1, (uint8_t *)textTxBuffer, strlen(textTxBuffer), 500);

    mpuConfigTx = 0b00000000;
    HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x6B, I2C_MEMADD_SIZE_8BIT, &mpuConfigTx, 1, 100);

    HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0x75, I2C_MEMADD_SIZE_8BIT, &mpuConfigRx, 1, 100);
    // sprintf(txBuffer, "Slave Address: %x \r", mpuConfigRx);
    // HAL_UART_Transmit(&huart1, (uint8_t *)txBuffer, strlen(txBuffer), 500);

    HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0x1A, I2C_MEMADD_SIZE_8BIT, &mpuConfigRx, 1, 100);
    // sprintf(txBuffer, "FIFO config: %x \r", mpuConfigRx);
    // HAL_UART_Transmit(&huart1, (uint8_t *)txBuffer, strlen(txBuffer), 500);

    mpuConfigTx = 0b00001000;
    HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x1B, I2C_MEMADD_SIZE_8BIT, &mpuConfigTx, 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0x1B, I2C_MEMADD_SIZE_8BIT, &mpuConfigRx, 1, 100);
    // sprintf(txBuffer, "Gyr cfig: %x \r", mpuConfigRx);
    // HAL_UART_Transmit(&huart1, (uint8_t *)txBuffer, strlen(txBuffer), 500);

    mpuConfigTx = 0b00011000;
    HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x1C, I2C_MEMADD_SIZE_8BIT, &mpuConfigTx, 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0x1C, I2C_MEMADD_SIZE_8BIT, &mpuConfigRx, 1, 100);
    // sprintf(txBuffer, "Acc cfig: %x \r", mpuConfigRx);
    // HAL_UART_Transmit(&huart1, (uint8_t *)txBuffer, strlen(txBuffer), 500);

    HAL_TIM_Base_Start_IT(&htim3);

    /* USER CODE END 2 */

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
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the CPU, AHB and APB busses clocks
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
    /** Initializes the CPU, AHB and APB busses clocks
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
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    HAL_I2C_Mem_Read_IT(&hi2c1, 0xD0, 0x3B, I2C_MEMADD_SIZE_8BIT, rawMpu, 2);
    // static uint32_t i;
    // if (i==10) {
    //     HAL_I2C_Mem_Read_IT(&hi2c1, 0xD0, 0x3B, I2C_MEMADD_SIZE_8BIT, rawMpu, 14);

    //     // static uint32_t n;
    //     // n++;
    //     // sprintf(textTxBuffer, "%05d\r\n", n);
    //     // HAL_UART_Transmit(&huart1, (uint8_t *)textTxBuffer, strlen(textTxBuffer), 500);
    //     i=0;
    // }
    // i++;
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    // static uint32_t seconds, millis;

    // millis = millis + 5;
    // if(millis == 1000) {
    //     millis =0;
    //     seconds++;
    // }

    uint32_t xAcc = (rawMpu[0] << 8) | (0x00F0 & rawMpu[1]);
    // uint32_t yAcc = (rawMpu[2] << 8) | (0x00F0 & rawMpu[3]);
    // uint32_t zAcc = (rawMpu[4] << 8) | (0x00F0 & rawMpu[5]);
    // uint32_t xGyr = (rawMpu[8] << 8) | (0x00FF & rawMpu[9]);
    // uint32_t yGyr = (rawMpu[10] << 8) | (0x00FF & rawMpu[11]);
    // uint32_t zGyr = (rawMpu[12] << 8) | (0x00FF & rawMpu[13]);

    sprintf(textTxBuffer, "%06hd\r", xAcc);
    HAL_UART_Transmit(&huart1, (uint8_t *)textTxBuffer, strlen(textTxBuffer), 500);
    static uint8_t count;
    if (count == 100) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        count=0;
    }
    count++;
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
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
