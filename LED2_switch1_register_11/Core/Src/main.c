#include "stm32f4xx.h"
#include <stdio.h>

#define DEBOUNCE_DELAY 100

void delay(int milliseconds);

int main(void)
{
    int switchState = 0; // Variable to store the state of the switch press
    int numPresses = 0; // Variable to store the number of times the switch is pressed

    // Enable clock for GPIOA and GPIOB
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;

    // Configure PA5 as output (on-board LED) and PB7 as output (external LED)
    GPIOA->MODER |= GPIO_MODER_MODE5_0; // Set PA5 as output
    GPIOB->MODER |= GPIO_MODER_MODE7_0; // Set PB7 as output

    // Configure PC13 as input (switch)
    GPIOC->MODER &= ~(GPIO_MODER_MODE13_Msk); // Clear the bits for PC13

    // Initial state: LED1 ON and LED2 OFF
    GPIOA->BSRR |= GPIO_BSRR_BS5;
    GPIOB->BSRR |= GPIO_BSRR_BR7;

    while(1)
    {
        if(GPIOC->IDR & GPIO_IDR_ID13)
        {
            delay(DEBOUNCE_DELAY); // Debounce delay

            if(GPIOC->IDR & GPIO_IDR_ID13) // Check again if the switch is still pressed
            {
                numPresses++; // Increment number of presses

                // Toggle LED1 and LED2 based on the number of presses
                if(numPresses % 2 == 0)
                {
                    GPIOA->BSRR |= GPIO_BSRR_BS5; // LED1 ON
                    GPIOB->BSRR |= GPIO_BSRR_BR7; // LED2 OFF
                }
                else
                {
                    GPIOA->BSRR |= GPIO_BSRR_BR5; // LED1 OFF
                    GPIOB->BSRR |= GPIO_BSRR_BS7; // LED2 ON
                }

                // Print the number of times switch pressed and LED states
                printf("Number of times switch pressed: %d\n", numPresses);
                printf("LED1 state: %s\n", (numPresses % 2 == 0) ? "ON" : "OFF");
                printf("LED2 state: %s\n", (numPresses % 2 != 0) ? "ON" : "OFF");
            }

            while(GPIOC->IDR & GPIO_IDR_ID13); // Wait until the switch is released
        }
    }

    return 0;
}

// Simple delay function
void delay(int milliseconds)
{
    for(int i = 0; i < milliseconds * 1000; i++);
}
