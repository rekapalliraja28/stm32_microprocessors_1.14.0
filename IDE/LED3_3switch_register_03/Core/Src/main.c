#include "stm32f4xx.h"

#define DEBOUNCE_DELAY 100

void delay(int milliseconds);

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;
    GPIOA->MODER |= GPIO_MODER_MODE7_0 | GPIO_MODER_MODE8_0 | GPIO_MODER_MODE9_0;
    GPIOB->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE9_Msk);
    GPIOC->MODER &= ~GPIO_MODER_MODE9_Msk;

    while(1)
    {
        if(GPIOB->IDR & GPIO_IDR_ID8)
        {
            GPIOA->BSRR |= GPIO_BSRR_BS7;
        }
        else
        {
            GPIOA->BSRR |= GPIO_BSRR_BR7; // Turn off PA7
        }

        if(GPIOB->IDR & GPIO_IDR_ID9)
        {
            GPIOA->BSRR |= GPIO_BSRR_BS8;
        }
        else
        {
            GPIOA->BSRR |= GPIO_BSRR_BR8; // Turn off PA8
        }

        if(GPIOC->IDR & GPIO_IDR_ID9)
        {
            GPIOA->BSRR |= GPIO_BSRR_BS9;
        }
        else
        {
            GPIOA->BSRR |= GPIO_BSRR_BR9; // Turn off PA9
        }

        delay(DEBOUNCE_DELAY); // Add a debounce delay
    }

    return 0;
}

void delay(int milliseconds)
{
    for(int i = 0; i < milliseconds * 1000; i++);
}
