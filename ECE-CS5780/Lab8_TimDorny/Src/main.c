
#include "stm32f0xx_hal.h"
#include "motor3.h"

// FINAL PROJECT CODE Tim Dorny u0829896 - Gyroscope Control
// I used the Lab 8 code as a template and added my own methods/variables to implement gyroscope functionality

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* Miscellaneous init functions -----------------------------------------------*/
void LED_init(void) {
    // Initialize PC8 and PC9 for LED's
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;                                          // Enable peripheral clock to GPIOC
    GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;                  // Set PC8 & PC9 to outputs
    GPIOC->OTYPER &= ~(GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9);                    // Set to push-pull output type
    GPIOC->OSPEEDR &= ~((GPIO_OSPEEDR_OSPEEDR8_0 | GPIO_OSPEEDR_OSPEEDR8_1) |
                        (GPIO_OSPEEDR_OSPEEDR9_0 | GPIO_OSPEEDR_OSPEEDR9_1));   // Set to low speed
    GPIOC->PUPDR &= ~((GPIO_PUPDR_PUPDR8_0 | GPIO_PUPDR_PUPDR8_1) |
                      (GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR9_1));             // Set to no pull-up/down
    GPIOC->ODR &= ~(GPIO_ODR_8 | GPIO_ODR_9);                                   // Shut off LED's
}

void  button_init(void) {
    // Initialize PA0 for button input
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;                                          // Enable peripheral clock to GPIOA
    GPIOA->MODER &= ~(GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1);               // Set PA0 to input
    GPIOC->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR0_0 | GPIO_OSPEEDR_OSPEEDR0_1);     // Set to low speed
    GPIOC->PUPDR |= GPIO_PUPDR_PUPDR0_1;                                        // Set to pull-down
}


/* Main Program Code -----------------------------------------------*/
int main(void) {
    HAL_Init();  // Reset of all peripherals, Initializes the Flash interface and the Systick. 
    SystemClock_Config();  // Configure the system clock 

    //Init peripherals, blinks PC9 LED in loop as heartbeat.
    LED_init();                             // Initialize LED's
    button_init();                          // Initialize button  
    motor_init();                           // Initialize motor code 
		// ADDITIONS
		// initialize gyroscope/i2c
		//gyro_init();
		gyro_init();
		setup_gyro_interrupt();
		init = 0;
	// variable to control speed of i2c reads
	  count = 0;
	  target_rpm = 0;
    
    while(1) {
        GPIOC->ODR ^= GPIO_ODR_9;           // Toggle LED
        HAL_Delay(128);                     // Delay 1/8th second
    }
}

void gyro_init(void) {
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
	//GPIOC->ODR ^= (1 << 7);
	// Write OUT_X_L address into TXDR
	I2C2->TXDR = 0xA8;
	// Wait for tc flag to be set
	while (!(I2C2->ISR & (1 << 6))){
	}
	GPIOC->ODR ^= (1 << 8);
	return;
}
void i2c_read(void) {
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
	//GPIOC->ODR ^= (1 << 7);
	return;
}
/* Called by SysTick Interrupt
 * Performs button debouncing, changes target speed on button rising edge
 */
void HAL_SYSTICK_Callback(void) {
    static uint32_t debouncer = 0;
    
    debouncer = (debouncer << 1);
    if(GPIOA->IDR & (1 << 0)) {
        debouncer |= 0x1;
    }
		if (count == 100) {
			count = 0;
			I2C2->CR2 &= 0;
			// Setup the 4 reads for x and y values using register A8
			i2c_read_setup();
			// Clear CR2
			I2C2->CR2 &= 0;
			// Read X and Y values from Gyro
			i2c_read();
			// Clear CR2
			I2C2->CR2 &= 0;
			// Setup the 1 read for gyroscope interrupt register
			i2c_int_read_setup();
			// Clear CR2
			I2C2->CR2 &= 0;
			// Read interrupt register from Gyro
			i2c_int_read();

			
			// Process x and y coords
			int16_t x = (xhigh << 8) | (xlow & 0xFF);
			int16_t y = ylow | (yhigh << 8);
			
			// when interrupt occurs, set target_rpm to 200
			if (0) {
				GPIOC->ODR |= (1 << 7);
				target_rpm = 200;
			}
			// Adjust target RPM based on the current and initial position of the board.
			else {
				// tilts in the x direction speed the motor up while tilts in the y direction slow it down
				int rpm_update = ((x + 32768) / 300);
				int rpm_reduce = ((y - 32688) / 300);
				target_rpm += (rpm_update + rpm_reduce);
				if (target_rpm < 0) {
					target_rpm = 0;
				}
				else if (target_rpm > 150) {
					target_rpm = 150;
				}
			}
		}
		else {
			count++;
		}

    //if(debouncer == 0x7FFFFFFF) {
    //switch(target_rpm) {
    //    case 80:
    //        target_rpm = 50;
    //        break;
    //    case 50:
    //        target_rpm = 81;
    //        break;
     //   case 0:
    //        target_rpm = 80;
    //        break;
    //    default:
    //        target_rpm = 0;
    //        break;
    //    }
    //}
    
}
void i2c_int_read_setup(void){
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
	//GPIOC->ODR ^= (1 << 7);
	// Write OUT_X_L address into TXDR
	I2C2->TXDR = 0x31;
	// Wait for tc flag to be set
	while (!(I2C2->ISR & (1 << 6))){
	}
	GPIOC->ODR ^= (1 << 8);
	return;
}
void i2c_int_read(void) {
	// slave address
	I2C2->CR2 |= (0x6B << 1);
	// number of bytes to transmit (4)
	I2C2->CR2 |= (1 << 16);
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
	interrupt = I2C2->RXDR;
	// Wait for tc flag to be set
	while (!(I2C2->ISR & (1 << 6))){
	}
	// All 4 registers read, stop and return
	I2C2->CR2 |= (1 << 14);
	//GPIOC->ODR ^= (1 << 7);
	return;
}
// Sets up the an interrupt to trigger on a centain threshold value of X
void setup_gyro_interrupt(void)
{
	// Write CTRL_REG3 register ********************************8
	// slave address
	I2C2->CR2 |= (0x6B << 1);
	// number of bytes to transmit 
	I2C2->CR2 |= (2 << 16);
	// Set to write operation
	I2C2->CR2 &= ~(1 << 10);
	// Set START bit
	I2C2->CR2 |= (1 << 13);
	// Setup Write to INT1_CFG
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
	// Write CTRL_REG3 address into TXDR
	I2C2->TXDR = 0x22;
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
	// Write to register (10000000) = (80)
	I2C2->TXDR = 0x80;
	// Wait for tc flag to be set
	while (!(I2C2->ISR & (1 << 6))){
	}
	// stop
	I2C2->CR2 |= (1 << 14);
	// Write INT1_CFG register ********************************8
	// slave address
	I2C2->CR2 |= (0x6B << 1);
	// number of bytes to transmit 
	I2C2->CR2 |= (2 << 16);
	// Set to write operation
	I2C2->CR2 &= ~(1 << 10);
	// Set START bit
	I2C2->CR2 |= (1 << 13);
	// Setup Write to INT1_CFG
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
	// Write INT1_CFG address into TXDR
	I2C2->TXDR = 0x30;
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
	// Write to register (00000010) = (2)
	I2C2->TXDR = 0x42;
	// Wait for tc flag to be set
	while (!(I2C2->ISR & (1 << 6))){
	}
	// stop
	I2C2->CR2 |= (1 << 14);
	// setup threshold
	//HAL_Delay();
	setup_int_threshold();
	return;
}
// Sets the x value threshold that triggers an interrupt when the value is greater than or equal
void setup_int_threshold(void)
{
	// Write INT1_THS_XH register ********************************8
	// slave address
	I2C2->CR2 |= (0x6B << 1);
	// number of bytes to transmit 
	I2C2->CR2 |= (2 << 16);
	// Set to write operation
	I2C2->CR2 &= ~(1 << 10);
	// Set START bit
	I2C2->CR2 |= (1 << 13);
	// Setup Write to INT1_THS_XH
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
	// Write INT1_THS_XH address into TXDR
	I2C2->TXDR = 0x32;
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
	// Write to register (10001000) = (0x88)
	I2C2->TXDR = 0x7f;
	// Wait for tc flag to be set
	while (!(I2C2->ISR & (1 << 6))){
	}
	// stop
	I2C2->CR2 |= (1 << 14);
	return;
}
/** System Clock Configuration */
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
		// turn on red led if error occurs
		GPIOC->ODR |= GPIO_ODR_8;
  }
  /* USER CODE END Error_Handler */ 
}

