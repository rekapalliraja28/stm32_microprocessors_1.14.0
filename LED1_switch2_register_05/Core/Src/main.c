#include "stm32f4xx.h"

#define DEBOUNCE_DELAY 100

void delay(int milliseconds);

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
    GPIOA->MODER |= GPIO_MODER_MODE7_0;
    GPIOB->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE9_Msk);

    while(1)
    {
        if(GPIOB->IDR & GPIO_IDR_ID8) // Check if the first switch is pressed
        {
            GPIOA->BSRR |= GPIO_BSRR_BS7; // Turn on PA7
        }

        else if(GPIOB->IDR & GPIO_IDR_ID9) // Check if the second switch is pressed
        {
            GPIOA->BSRR |= GPIO_BSRR_BR7; // Turn off PA7 (LED)
        }
        else
        {

        }

        delay(DEBOUNCE_DELAY); // Add a debounce delay
    }

    return 0;
}

void delay(int milliseconds)
{
    for(int i = 0; i < milliseconds * 1000; i++);
}
