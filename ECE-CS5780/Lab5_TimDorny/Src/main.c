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
#include "stdlib.h"

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
void i2c_read(void);
void i2c_read_setup(void);
void i2c_old(void);
void update_leds(int, int);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
// variables for x and y coords
int xlow = 0;
int xhigh = 0;
int ylow = 0;
int yhigh = 0;

// Tilt threshold
int threshold = 100;

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
	//NVIC_EnableIRQ(USART3_4_IRQn);
	//NVIC_SetPriority(USART3_4_IRQn, 0);
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
	GPIOB->MODER |= (1 << 23) | (1 << 27) | (1 << 28);
	GPIOB->OTYPER |= (1 << 11) | (1 << 13);
	GPIOB->OTYPER &= ~(1 << 14);
	GPIOB->AFR[1] |= (1 << 12) | (1 << 20) | (1 << 22);
	GPIOC->MODER |= (1 << 0);
	GPIOC->OTYPER &= 0;
	GPIOB->ODR |= (1 << 14);
	GPIOC->ODR |= (1);
	
	// LEDs for debug
	GPIOC->MODER |= 0x55000;
	GPIOC->OSPEEDR &= 0x0;
	GPIOC->PUPDR &= 0x0;
	// 6 red 7 blue 8 orange 9 green
	//GPIOC->ODR |= (1 << 8);
	I2C2->TIMINGR |= (0x13) | (0xF << 8) | (0x2 << 16) | (0x4 << 20) | (1 << 28);
	I2C2->CR1 |= 1;
	
	// Clear CR2
	I2C2->CR2 &= 0;
	
	
	// Write CTRL_REG1 register ********************************8
	// slave address
	I2C2->CR2 |= (0x6B << 1);
	// number of bytes to transmit 
	I2C2->CR2 |= (2 << 16);
	// Set to write operation
	I2C2->CR2 &= ~(1 << 10);
	// Set START bit
	I2C2->CR2 |= (1 << 13);
	// Setup Write to CTRL_REG1
	// Wait for TXIS/NACKF
	while (1){
		// TXIS
		if (I2C2->ISR & (1 << 1)){
			break;
		}
		// NACKF
		else if (I2C2->ISR & (1 << 4)){
			GPIOC->ODR |= (1 << 6);
			break;
		}
	}
	// Write CTRL_REG1 address into TXDR
	I2C2->TXDR = 0x20;
	// Wait for TXIS/NACKF
	while (1){
		// TXIS
		if (I2C2->ISR & (1 << 1)){
			break;
		}
		// NACKF
		else if (I2C2->ISR & (1 << 4)){
			GPIOC->ODR |= (1 << 6);
			break;
		}
	}
	// Write to register (00001011) = (B)
	I2C2->TXDR = 0xB;
	// Wait for tc flag to be set
	while (!(I2C2->ISR & (1 << 6))){
	}
	// stop
	I2C2->CR2 |= (1 << 14);
	
	//i2c_read_setup();
	
	// From read
	
	// ************************************************
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		// Read x and y from gyro ====================================
		// Clear CR2
		I2C2->CR2 &= 0;
		i2c_read_setup();
		// Clear CR2
		I2C2->CR2 &= 0;
		//GPIOC->ODR ^= (1 << 8);
		i2c_read();
		
		// Process x and y coords
		int x = xlow | (xhigh << 8);
		int y = ylow | (yhigh << 8);
		
		// Update LEDs
		update_leds(x, y);
		
		// Delay
		//GPIOC->ODR |= (1 << 8);
		HAL_Delay(50);
		//GPIOC->ODR |= (1 << 9);
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

void update_leds(int x, int y){
	// determine whether x or y is the larger "tilt"
	int xMax;
	int maxValue;
	int positive;
	if (abs(x) >= abs(y)){
		xMax = 1;
		maxValue = x;
	}
	else {
		xMax = 0;
		maxValue = y;
	}
	// Determine direction of tilt (positive or negative)
	if (maxValue > 0){
		positive = 1;
	}
	else {
		positive = 0;
	}
	// Threshold
	if (maxValue < threshold){
		return;
	}
	// Light leds based on results
	// X positive []
	if (xMax && positive){
		//GPIOC->ODR &= 0;
		GPIOC->ODR |= (1 << 9);
	}
	// X negative []
	else if (xMax && !(positive)){
		//GPIOC->ODR &= 0;
		GPIOC->ODR |= (1 << 8);
	}
	// Y positive []
	else if (!(xMax) && positive){
		//GPIOC->ODR &= 0;
		GPIOC->ODR |= (1 << 6);
	}
	// Y Negative []
	else if (!(xMax) && !(positive)){
		//GPIOC->ODR &= 0;
		GPIOC->ODR |= (1 << 7);
	}
	return;
}

void i2c_read(void){
	// slave address
	I2C2->CR2 |= (0x6B << 1);
	// number of bytes to transmit (4)
	I2C2->CR2 |= (4 << 16);
	// Set to read operation
	I2C2->CR2 |= (1 << 10);
	// Set START bit
	I2C2->CR2 |= (1 << 13);
	// Wait for RXNE or NACKF   [X LOW]
	while (1){
		// RXNE
		if (I2C2->ISR & (1 << 2)){
			break;
			}
		else if (I2C2->ISR & (1 << 4)){
			// error
			GPIOC->ODR |= (1 << 6);
			return;
		}
	}
	// Read next data byte in RXDR
	xlow = I2C2->RXDR;
	// Wait for RXNE or NACKF   [X HIGH]
	while (1){
		// RXNE
		if (I2C2->ISR & (1 << 2)){
			break;
			}
		else if (I2C2->ISR & (1 << 4)){
			// error
			GPIOC->ODR |= (1 << 6);
			return;
		}
	}
	// Read next data byte in RXDR
	xhigh = I2C2->RXDR;
	// Wait for RXNE or NACKF   [Y LOW]
	while (1){
		// RXNE
		if (I2C2->ISR & (1 << 2)){
			break;
			}
		else if (I2C2->ISR & (1 << 4)){
			// error
			GPIOC->ODR |= (1 << 6);
			return;
		}
	}
	// Read next data byte in RXDR
	ylow = I2C2->RXDR;
	// Wait for RXNE or NACKF   [Y HIGH]
	while (1){
		// RXNE
		if (I2C2->ISR & (1 << 2)){
			break;
			}
		else if (I2C2->ISR & (1 << 4)){
			// error
			GPIOC->ODR |= (1 << 6);
			return;
		}
	}
	// Read next data byte in RXDR
	yhigh = I2C2->RXDR;
	// Wait for tc flag to be set
	while (!(I2C2->ISR & (1 << 6))){
	}
	// All 4 registers read, stop and return
	I2C2->CR2 |= (1 << 14);
	GPIOC->ODR ^= (1 << 7);
	return;
}

void i2c_read_setup(void){
	// slave address
	I2C2->CR2 |= (0x6B << 1);
	// number of bytes to transmit ( clear and re-set
	I2C2->CR2 |= (1 << 16);
	// Set to write operation
	I2C2->CR2 &= ~(1 << 10);
	// Set START bit
	I2C2->CR2 |= (1 << 13);
	// Wait for TXIS/NACKF
	while (1){
		// TXIS
		if (I2C2->ISR & (1 << 1)){
			break;
		}
		// NACKF
		else if (I2C2->ISR & (1 << 4)){
			GPIOC->ODR |= (1 << 6);
			return;
		}
	}
	// Write OUT_X_L address into TXDR
	I2C2->TXDR = 0xA8;
	// Wait for tc flag to be set
	while (!(I2C2->ISR & (1 << 6))){
	}
	//GPIOC->ODR ^= (1 << 9);
	return;
}

void i2c_old(void){
	// Reload CR2 register but for read operation
	// slave address
	I2C2->CR2 |= (0x6b << 1);
	// number of bytes to transmit (1)
	I2C2->CR2 |= (1 << 16);
	// Set to read operation
	I2C2->CR2 |= (1 << 10);
	// Set START bit
	I2C2->CR2 |= (1 << 13);
	
	while (1){
		if (I2C2->ISR & (1 << 4)){
			// bad things
			GPIOC->ODR |= (1 << 6);
		}
		else if (I2C2->ISR & (1 << 2)){
			// continue
			// check contents and see if they match!
			GPIOC->ODR |= (1 << 7);
			if (I2C2->RXDR == 0xD4){
				// success!
				GPIOC->ODR |= (15 << 6);
			}
			while (!(I2C2->ISR & (1 << 6))){
				
			}
			// stop hamma time
			I2C2->CR2 |= (1 << 14);
		}
	}
}
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
