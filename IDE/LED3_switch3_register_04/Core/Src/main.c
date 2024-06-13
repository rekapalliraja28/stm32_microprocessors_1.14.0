#include "stm32f4xx.h"

void delay(int milliseconds);

int main(void)
{
    // Enable clock for GPIOA, GPIOB, and GPIOC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

    // Configure PA7, PA8, and PA9 as output (LEDs)
    GPIOA->MODER |= GPIO_MODER_MODE7_0 | GPIO_MODER_MODE8_0 | GPIO_MODER_MODE9_0;

    // Configure PB8, PB9, and PC9 as input (Switches)
    GPIOB->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE9_Msk);
    GPIOC->MODER &= ~GPIO_MODER_MODE9_Msk;

    while(1)
    {
        // Check if the 1st switch (PB8) is pressed
        if(GPIOB->IDR & GPIO_IDR_ID8)
        {
            // Turn on LED 1 (PA7)
            GPIOA->BSRR |= GPIO_BSRR_BS7;
        }
        // Check if the 2nd switch (PB9) is pressed
        else if(GPIOB->IDR & GPIO_IDR_ID9)
        {
            // Turn on LED 1 (PA7)
            GPIOA->BSRR |= GPIO_BSRR_BS7;
            // Turn on LED 2 (PA8)
            GPIOA->BSRR |= GPIO_BSRR_BS8;
        }
        // Check if the 3rd switch (PC9) is pressed
        else if(GPIOC->IDR & GPIO_IDR_ID9)
        {
            // Turn on LED 1 (PA7)
            GPIOA->BSRR |= GPIO_BSRR_BS7;
            // Turn on LED 2 (PA8)
            GPIOA->BSRR |= GPIO_BSRR_BS8;
            // Turn on LED 3 (PA9)
            GPIOA->BSRR |= GPIO_BSRR_BS9;
        }
        else
        {
            // If no switch is pressed, turn off all LEDs
            GPIOA->BSRR |= (GPIO_BSRR_BR7 | GPIO_BSRR_BR8 | GPIO_BSRR_BR9);
        }

        // Add a small delay for debouncing
        delay(100);
    }

    return 0;
}

// Simple delay function
void delay(int milliseconds)
{
    for(int i = 0; i < milliseconds * 1000; i++);
}
