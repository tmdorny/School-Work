/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
const uint8_t sawtooth_table[32] = {0, 7, 15, 23, 31, 39, 47, 55, 63, 71, 79, 87, 95, 103, 111, 119, 127, 134, 142, 150, 158, 166, 174, 182, 190, 198, 206, 214, 222, 230, 238, 246};
// Threshold values
int t1 = 50;
int t2 = 100;
int t3 = 150;
int t4 = 200;
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  
  // LEDs
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= 0x55000;
	GPIOC->OTYPER &= 0x0;
	GPIOC->OSPEEDR &= 0x0;
	GPIOC->PUPDR &= 0x0;
  
  GPIOC->ODR &= (15 << 6);
  //GPIOC->ODR |= (15 << 6);
  
  // PA0 [ADC]
  GPIOA->MODER |= (3);
  GPIOA->PUPDR &= 0;
  
  // Configure ADC
  ADC1->CFGR1 &= 0;
  // 8-bit res
  ADC1->CFGR1 |= (1 << 4);
  // Continuous Conversion
  ADC1->CFGR1 |= (1 << 13);
  // Hardware triggers disabled
  ADC1->CFGR1 &= ~(3 << 10);
  // Enable ADC channel 0
  ADC1->CHSELR |= 1;
  
  // left aligned
  ADC1->CFGR1 &= ~(1 << 5);
  
  // Calibration
  //Ensure ADEN and DMAEN = 0
  ADC1->CR &= 0;
  ADC1->CFGR1 &= ~(1);
  // Set ADCAL = 1
  ADC1->CR |= (1U << 31);
  // Wait until ADCAL = 0
  while (ADC1->CR & (1U << 31)) {
  }
  // Enable ADC
  ADC1->CR |= 1;
  // Wait for ADC to be ready
  while (!(ADC1->ISR & 1)){
  }
  // Start ADC conversion
  ADC1->CR |= (1 << 2);
  
	// analog mode for PA4 [DAC]
	GPIOA->MODER |= (3 << 8);
	GPIOA->PUPDR &= 0;
	
	// Enable and software trigger
	DAC->CR &= 0;
	DAC->CR |= (1) | (7 << 3);
  /* USER CODE END 2 */
	int index = 0;
  int adc;
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // ADC
    while (!(ADC1->ISR & (1 < 2))){
    }
    // Read values and update LEDs accordingly
    adc = ADC1->DR;
    // 4 leds
    if (adc > t4){
      GPIOC->ODR &= 0;
      GPIOC->ODR |= (15 << 6);
    }
    //3
    else if (adc > t3){
      GPIOC->ODR &= 0;
      GPIOC->ODR |= (7 << 6);
    }
    //2
    else if (adc > t2){
      GPIOC->ODR &= 0;
      GPIOC->ODR |= (3 << 6);
    }
    //1
    else if (adc > t1){
      GPIOC->ODR &= 0;
      GPIOC->ODR |= (1 << 6);
    }
    //0
    else {
      GPIOC->ODR &= 0;
    }
    
    
    
    // DAC
		DAC->DHR8R1 = sawtooth_table[index];
		
		if (index == 31) {
			index = 0;
		}
		else {
			index++;
		}
		HAL_Delay(1);
    //GPIOC->ODR ^= (1 << 6);
		
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
