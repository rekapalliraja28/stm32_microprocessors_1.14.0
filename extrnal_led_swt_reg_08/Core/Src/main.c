/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

#include "stm32f4xx.h"                  // Device header

#define INFINITE_LOOP 1

void delay(int milliseconds);

int main(void)
{
    // Enable clock for GPIOA and GPIOC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

    // Configure PA8 as output (LED)
    GPIOA->MODER |= GPIO_MODER_MODE8_0;  // Set PA8 as output

    // Configure PC9 as input (Switch)
    GPIOC->MODER &= ~(GPIO_MODER_MODE9_Msk);  // Clear the bits
    GPIOC->PUPDR |= GPIO_PUPDR_PUPD9_0;       // Set PC9 as pull-up

    while(INFINITE_LOOP)
    {
        // Check if the switch (PC9) is pressed
        if(GPIOC->IDR & GPIO_IDR_ID9)
        {
            delay(100); // Debounce delay
            // Toggle LED (PA8)
            GPIOA->ODR ^= GPIO_ODR_OD8;
        }
    }

    return 0;
}

void delay(int milliseconds)
{
    // Simple delay function, adjust the actual delay according to your requirements
    for(int i = 0; i < milliseconds * 1000; i++) {} // Adjust this loop for your system clock speed

}
