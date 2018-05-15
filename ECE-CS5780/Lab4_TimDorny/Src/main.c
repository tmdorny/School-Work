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
#include "string.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
void sendChar(char);
void sendString(char *);
void toggleLED(char *);
void actionSelect(char*);
int equals(char * word, char * word2);
int led = 0;

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
int data = 0;
int dataReady = 0;
int wordDone = 0;
char buffer[7] = "";
char word[7] = "";
int second = 0;
char * color;
int i = 0;
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
	
	NVIC_EnableIRQ(USART3_4_IRQn);
	NVIC_SetPriority(USART3_4_IRQn, 0);
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	GPIOB->MODER |= 0xA00000;
	GPIOB->AFR[0] |= 0x4400;
	GPIOB->AFR[1] |= 0x4400;
	GPIOB->OTYPER &= 0x0;
	GPIOB->OSPEEDR &= 0x0;
	GPIOB->PUPDR &= 0x0;
	
	// LEDs for debug
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	GPIOC->MODER |= 0x55000;
	GPIOC->OTYPER &= 0x0;
	GPIOC->OSPEEDR &= 0x0;
	GPIOC->PUPDR &= 0x0;
	
	//GPIOC->ODR |= 0x40;
	
	// USART CONFIG
	USART3->BRR = HAL_RCC_GetHCLKFreq() / 115200;
	// enable transmitter and receiver
	USART3->CR1 |= 0xC;
	// enable read not empty interrupt
	USART3->CR1 |= 0x20;
	// enable USART
	USART3->CR1 |= 0x1;
	
	sendString("Enter Command:\n\r");
	memset(buffer, 0, sizeof(buffer));
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
	//if (USART3->ISR & 0x20){
	//	int val = USART3->RDR;
	//	toggleLED(val);
	//}
	if (wordDone){
		buffer[i+1] = '\0';
		if (second){
			// select on/off/toggle
			actionSelect(buffer);
		}
		else{
			// choose which led to toggle
			toggleLED(buffer);
		}
		// reset buffer index
		i = 0;
	}
	else if (dataReady){
		// write char to buffer
		buffer[i] = data;
		dataReady = 0;
		i++;
	}
		
	//HAL_Delay(200);
	//sendString("hello this is string");
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
void sendChar(char c)
{
	while (1) {
		if (USART3->ISR & 0x80){
			break;
		}
	}
	USART3->TDR = c;
	//oGPIOC->ODR ^= 0xC0;
	return;
}
// Send string to console
void sendString(char * str)
{
	while (*str != '\0'){
		sendChar(*str);
		str++;
	}
}
void toggleLED(char * val)
{
	dataReady = 0;
	wordDone = 0;
	
	if (equals(val, "red")){
		led = 0x40;
		color = "RED";
	}
	else if (equals(val, "green")){
		led = 0x200;
		color = "GREEN";
	}
	else if (equals(val, "blue")){
		led = 0x80;
		color = "BLUE";
	}
	else if (equals(val, "orange")){
		led = 0x100;
		color = "ORANGE";
	}
	else {
		sendString("Invalid Word...\r\n");
		sendString("Enter Command:\r\n");
		memset(buffer, 0, sizeof(buffer));
		return;
	}
	sendString("OFF , ON , or TOGGLE?\r\n");
	memset(buffer, 0, sizeof(buffer));
	// perfrom second command
	second = 1;
	return;
}

void actionSelect(char * word)
{
	dataReady = 0;
	wordDone = 0;
	if (equals(word, "off")){
		GPIOC->ODR &= ~led;
		sendString("Turned OFF ");
		sendString(color);
		sendString(" LED...\r\n");		
	}
	else if (equals(word, "on")){
		GPIOC->ODR |= led;
		sendString("Turned ON ");
		sendString(color);
		sendString(" LED...\r\n");
	}
	else if (equals(word, "toggle")){
		GPIOC->ODR ^= led;
		sendString("TOGGLED ");
		sendString(color);
		sendString(" LED...\r\n");
	}
	else {
		sendString("Invalid Word...\r\n");
	}
	sendString("Enter Command:\r\n");
	memset(buffer, 0, sizeof(buffer));
	// perfrom first command
	second = 0;
	return;
}

void USART3_4_IRQHandler(void)
{
	data = USART3->RDR;
	sendChar(data);
	if (data == 13){
		sendString("\n\r");
		wordDone = 1;
	}
	else {
		dataReady = 1;
	}
}

int equals (char* word, char* word2){
	// check if strings are same length
	if (!(strlen(word) == strlen(word2))){
		return 0;
	}
	int j;
	int length = strlen(word);
	// check that each letter matches
	for (j = 0; j < length; j++){
		if(!(word[j] == word2[j])){
			return 0;
		}
	}
	return 1;
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
