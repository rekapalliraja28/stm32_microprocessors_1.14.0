#include "stm32f4xx.h"
#include <stdio.h>

#define DEBOUNCE_DELAY 100

void delay(int milliseconds);

int main(void)
{
    int switchState = 0; // Variable to store the state of the switch press
    int numPresses = 0; // Variable to store the number of times the switch is pressed

    // Enable clock for GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configure PA5 as output (LED) and PC13 as input (Switch)
    GPIOA->MODER |= GPIO_MODER_MODE5_0;  // Set PA5 as output
    GPIOA->MODER &= ~(GPIO_MODER_MODE13_Msk);  // Clear the bits for PA13

    while(1)
    {
        if(GPIOA->IDR & GPIO_IDR_ID13)
        {
            delay(DEBOUNCE_DELAY); // Debounce delay

            if(GPIOA->IDR & GPIO_IDR_ID13) // Check again if the switch is still pressed
            {
                numPresses++; // Increment number of presses

                if (switchState == 0) {
                    GPIOA->ODR |= GPIO_ODR_OD5; // Turn on LED
                    printf("LED ON\n");
                } else {
                    GPIOA->ODR &= ~GPIO_ODR_OD5; // Turn off LED
                    printf("LED OFF\n");
                }

                switchState = !switchState; // Toggle switch state

                // Print the number of times switch pressed
                printf("Number of times switch pressed: %d\n", numPresses);
            }

            while(GPIOA->IDR & GPIO_IDR_ID13); // Wait until the switch is released
        }
    }

    return 0;
}

// Simple delay function
void delay(int milliseconds)
{
    for(int i = 0; i < milliseconds * 1000; i++);
}
