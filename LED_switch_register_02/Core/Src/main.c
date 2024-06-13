#include "stm32f4xx.h"                  // Device header

#define INFINITE_LOOP 1

int main(void)
{
    // Enable clock for GPIOA and GPIOC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

    // Configure PA8 as output (LED)
    //GPIOA->MODER |= GPIO_MODER_MODE8_0;  // Set PA8 as output
    GPIOA->MODER |= 0x1<<16;

    // Configure PC9 as input (Switch)
    //GPIOC->MODER &= ~(GPIO_MODER_MODE9_Msk);  // Clear the bits
    GPIOC->MODER &= ~ 0x3 << 18;
    while(INFINITE_LOOP)
    {
        // Check if the switch (PC9) is pressed
        //if(GPIOC->IDR & GPIO_IDR_ID9)
        if(GPIOC->IDR & 0x1<<9)
        {
            // Toggle LED (PA8)
            //GPIOA->ODR ^= GPIO_ODR_OD8;
            GPIOA->ODR ^= 0x1<<8;
            // Add some delay to avoid rapid toggling due to switch bounce
            for(int i = 0; i < 1000000; i++) {} // Adjust this loop for your system clock speed
        }
    }

    return 0;
}
